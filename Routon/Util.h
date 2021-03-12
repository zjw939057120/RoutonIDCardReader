#pragma once
#include "httplib.h"
#include "base64.h"
#include <direct.h> // _getcwd
#include "sdtapi.h"
#include <exception> 
#include <sstream> 
#pragma comment(lib, "Sdtapi.lib")
class Util
{
public:
	Util();
	~Util();
	std::wstring Util::stringToWstring(const std::string& str);
	std::string Util::wstringToString(const std::wstring& wstr);
	std::string Util::string_To_UTF8(const std::string & str);
	std::string Util::wstring_To_UTF8(const std::wstring & wstr);
	std::string Util::LoadFile(char * pFilePath);
	std::string Util::GetAppWorkingDirectory();
	void Http(int iPort);
	std::string Read(int iPort = 1001);

	bool CheckPort(const std::string & host, int port);

private:

};