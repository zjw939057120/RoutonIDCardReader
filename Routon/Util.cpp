#include "Util.h"
Util::Util()
{
}

Util::~Util()
{
}


std::wstring Util::stringToWstring(const std::string& str)
{
	LPCSTR pszSrc = str.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);
	if (nLen == 0)
		return std::wstring(L"");

	wchar_t* pwszDst = new wchar_t[nLen];
	if (!pwszDst)
		return std::wstring(L"");

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pwszDst, nLen);
	std::wstring wstr(pwszDst);
	delete[] pwszDst;
	pwszDst = NULL;

	return wstr;
}

std::string Util::wstringToString(const std::wstring& wstr)
{
	LPCWSTR pwszSrc = wstr.c_str();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
		return std::string("");

	char* pszDst = new char[nLen];
	if (!pszDst)
		return std::string("");

	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	std::string str(pszDst);
	delete[] pszDst;
	pszDst = NULL;

	return str;
}

std::string Util::string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (nwLen == 0)
		return std::string("");
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	if (!pwBuf)
		return std::string("");
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	if (nLen == 0)
		return std::string("");
	char* pBuf = new char[nLen + 1];
	if (!pBuf)
		return std::string("");

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[] pwBuf;
	delete[] pBuf;
	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

std::string Util::wstring_To_UTF8(const std::wstring & wstr)
{
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, NULL, NULL, NULL);
	if (nLen == 0)
		return std::string("");
	char* pBuf = new char[nLen + 1];
	if (!pBuf)
		return std::string("");
	::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), nLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[] pBuf;
	pBuf = NULL;

	return retStr;
}

std::string Util::LoadFile(char * pFilePath)
{
	// 1. 只读打开图片文件
	std::ifstream is(pFilePath, std::ifstream::in | std::ios::binary);
	if (!is)
		throw "打开照片失败";

	// 2. 计算图片长度
	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);
	// 3. 创建内存缓存区
	char * buffer = new char[length];
	// 4. 读取图片
	is.read(buffer, length);
	// 到此，图片已经成功的被读取到内存（buffer）中
	std::string str(base64_encode((unsigned char*)buffer, length));
	delete[] buffer;
	buffer = NULL;
	return str;
}

std::string Util::GetAppWorkingDirectory() {
	char szWorkingDir[MAX_PATH + 1];
	if (_getcwd(szWorkingDir, MAX_PATH) == NULL) {
		szWorkingDir[0] = 0;
	}
	else {
		// Add trailing path separator.
		size_t len = strlen(szWorkingDir);
		szWorkingDir[len] = '\\';
		szWorkingDir[len + 1] = 0;
	}
	return szWorkingDir;
}

void Util::Http(int iPort)
{
	httplib::Server svr;
	svr.set_error_handler([](const auto& req, auto& res) {
		Util util;
		std::string body = "{\"code\":1,\"msg\":\"错误\",\"data\":[]}";
		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_content(util.string_To_UTF8(body), "application/json;charset=utf-8");
	});

	svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
		Util util;
		std::string body = "{\"code\":1,\"msg\":\"欢迎使用\",\"data\":[]}";
		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_content(util.string_To_UTF8(body), "application/json;charset=utf-8");
	});
	svr.Get("/read", [](const httplib::Request &, httplib::Response &res) {
		Util util;
		std::string body = util.Read();
		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_content(util.string_To_UTF8(body), "application/json;charset=utf-8");
	});

	svr.Get(R"(/read/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
		auto numbers = req.matches[1];
		Util util;
		std::string body = util.Read(std::stoi(numbers));
		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_content(util.string_To_UTF8(body), "application/json;charset=utf-8");
	});

	svr.listen("0.0.0.0", iPort);
}


std::string Util::Read(int iPort)
{
	try {
		if ((iPort < 1 || iPort > 16) && (iPort < 1001 || iPort > 10016))
			return std::string("{\"code\":0,\"msg\":\"无效端口号\",\"data\":[]}");

		int ret = 0;
		ret = InitComm(iPort);
		if (ret != 1) {
			CloseComm();
			return std::string("{\"code\":0,\"msg\":\"端口初始化失败\",\"data\":[]}");
		}

		Authenticate();

		char Name[31] = { 0 };
		char Gender[3] = { 0 };
		char Folk[10] = { 0 };
		char BirthDay[9] = { 0 };
		char Code[19] = { 0 };
		char Address[71] = { 0 };
		char Agency[31] = { 0 };
		char ExpireStart[9] = { 0 };
		char ExpireEnd[9] = { 0 };

		unsigned char pMsg[192] = { 0 };
		int* len = NULL;
		char * directory = NULL;
		//ret = ReadBaseInfosPhoto(Name, Gender, Folk, BirthDay, Code, Address, Agency, ExpireStart, ExpireEnd, "D:\\IDtemp");
		ret = ReadBaseMsgPhoto(pMsg, len, directory);
		if (ret != 1) {
			CloseComm();
			return std::string("{\"code\":0,\"msg\":\"读卡失败\",\"data\":[]}");
		}

		char* Msg = (char*)pMsg;
		memcpy_s(Name, 31, &Msg[0], 31);//姓名31
		memcpy_s(Gender, 3, &Msg[31], 3);//性别3
		memcpy_s(Folk, 10, &Msg[34], 10);//民族10
		memcpy_s(BirthDay, 9, &Msg[44], 9);//姓名9
		memcpy_s(Address, 71, &Msg[53], 71);//住址71
		memcpy_s(Code, 19, &Msg[124], 19);//公民身份号码19
		memcpy_s(Agency, 31, &Msg[143], 31);//签发机关31
		memcpy_s(ExpireStart, 9, &Msg[174], 9);//有效期起始日期9
		memcpy_s(ExpireEnd, 9, &Msg[183], 9);//有效期截止日期9

		std::string Image = LoadFile("photo.bmp");
		std::stringstream ss;
		ss << "{\"code\":1,\"msg\":\"读卡成功\",\"data\":{"
			<< "\"name\":\""
			<< Name << "\","
			<< "\"sex\":\""
			<< Gender << "\","
			<< "\"nation\":\""
			<< Folk << "\","
			<< "\"birth\":\""
			<< BirthDay << "\","
			<< "\"id\":\""
			<< Code << "\","
			<< "\"addr\":\""
			<< Address << "\","
			<< "\"dept\":\""
			<< Agency << "\","
			<< "\"start\":\""
			<< ExpireStart << "\","
			<< "\"end\":\""
			<< ExpireEnd << "\","
			<< "\"image\":\"data:image/bmp;base64,"
			<< Image << "\""
			<< "}}";
		CloseComm();
		return std::string(ss.str());

	}
	catch (const char* msg) {
		//异常抛出
		CloseComm();
		return std::string("{\"code\":0,\"msg\":\"" + std::string(msg) + "\",\"data\":[]}");
	}
	catch (std::exception e) {
		//异常抛出
		CloseComm();
		return std::string("{\"code\":0,\"msg\":\"" + std::string(e.what()) + "\",\"data\":[]}");
	}
}

bool Util::CheckPort(const std::string &host, int port) {
	httplib::Client cli(host, port);
	auto res = cli.Get("/");
	if (res)
		return true;
	else
		return false;
}