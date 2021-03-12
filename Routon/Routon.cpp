// Routon.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Routon.h"
#include "shellapi.h"
#include <process.h>
#include "Util.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

#define WM_TRAY (WM_USER + 100)
#define WM_TASKBAR_CREATED RegisterWindowMessage(TEXT("TaskbarCreated"))
#define APP_NAME	TEXT("���̳���")
#define APP_TIP		TEXT("Win32 API ʵ��ϵͳ���̳���")
NOTIFYICONDATA nid;		//��������
HMENU hMenu;			//���̲˵�
//��ʼ������
void InitTray(HINSTANCE hInstance, HWND hWnd);

//Web�����߳�
bool port_14725;
void WebThread_14725(PVOID param);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣
	Util util;
	port_14725 = util.CheckPort("127.0.0.1", 14725);
	if (port_14725 == true)
	{
		MessageBox(nullptr, _T("�˿ڱ�ռ�ã���������ʧ��"), _T("��ʾ��Ϣ"), MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
		return 0;
	}else
	{
		_beginthread(WebThread_14725, 0, NULL);
	}



    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROUTON, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROUTON));

    MSG msg;

    // ����Ϣѭ��: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROUTON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROUTON);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_HIDE);
   UpdateWindow(hWnd);
   InitTray(hInstance, hWnd);			//ʵ��������

   return TRUE;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_TRAY:
		switch (lParam)
			{
			case WM_RBUTTONDOWN:
			{
				//��ȡ�������
				POINT pt; GetCursorPos(&pt);

				//����ڲ˵��ⵥ������˵�����ʧ������
				SetForegroundWindow(hWnd);

				//ʹ�˵�ĳ����
				//EnableMenuItem(hMenu, ID_SHOW, MF_GRAYED);	

				//��ʾ����ȡѡ�еĲ˵�
				int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hWnd,
					NULL);
				if (cmd == IDM_ABOUT)
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				if (cmd == IDM_EXIT)
					PostMessage(hWnd, WM_DESTROY, NULL, NULL);
			}
			break;
			}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: �ڴ˴����ʹ�� hdc ���κλ�ͼ����...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		//��������ʱɾ������
		Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
	
	if (message == WM_TASKBAR_CREATED)
	{
		//ϵͳExplorer��������ʱ�����¼�������
		Shell_NotifyIcon(NIM_ADD, &nid);
	}

    return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


//ʵ��������
void InitTray(HINSTANCE hInstance, HWND hWnd)
{
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd;
	nid.uID = IDI_SMALL;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	nid.uCallbackMessage = WM_TRAY;
	nid.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	lstrcpy(nid.szTip, APP_NAME);

	hMenu = CreatePopupMenu();//�������̲˵�
							  //Ϊ���̲˵��������ѡ��
	AppendMenu(hMenu, MF_STRING, IDM_ABOUT, TEXT("����"));
	AppendMenu(hMenu, MF_STRING, IDM_EXIT, TEXT("�˳�"));

	Shell_NotifyIcon(NIM_ADD, &nid);
}

void WebThread_14725(PVOID param) {
	Util util;
	util.Http(14725);
}
