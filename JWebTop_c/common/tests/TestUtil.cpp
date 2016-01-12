#ifdef JWebTopLog
#include "TestUtil.h"
#include <Windows.h>
#include <string>
#include "common/util/StrUtil.h"

HANDLE hFile;// ����ʱ���������־�ļ�
DWORD filePos = 0;// ����ʱ���������־�ļ�
LPTSTR LOG_FILE_NAME = L"jwebtop.log";

void setLogFileName(std::wstring logFileName){
	LOG_FILE_NAME = LPTSTR(logFileName.c_str());
}

void checFile(){
	if (hFile == NULL){
		hFile = CreateFile(LOG_FILE_NAME, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	}
}
void writeLog(std::wstring str){
	checFile();
	std::string s = jw::w2s(str);
	WriteFile(hFile, s.c_str(), s.size(), &filePos, NULL);
	FlushFileBuffers(hFile);
}
void writeLog(std::string s){
	checFile();
	WriteFile(hFile, s.c_str(), s.size(), &filePos, NULL);
	FlushFileBuffers(hFile);
}
#endif