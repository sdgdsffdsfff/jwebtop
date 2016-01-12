#include "Demo.h"
#include "common/fastipc/Server.h"
#include "common/fastipc/Client.h"
#include "common/util/StrUtil.h"
#include "common/os/OS.h"
#include <thread>
#include <string>
#include <sstream>
#include "jwebtopex/jwebtopex.h"

extern std::wstring serverName;	// ���������
extern fastipc::Server server;  // IPC�����
extern DWORD blockSize;			// һ�δ���ʱ�����ݴ�С

// �õ������ļ�
wstring DemoCtrl::getListAppFile(){
	LPTSTR path = L"res/list/index.app";
	if (_waccess(path, 0) != 0){// ����������������
		path = L"../../res/list/index.app";
	}
	wchar_t fullpath[1024];
	_wfullpath(fullpath, path, 1024);
	wstring rtn(fullpath);
	delete[] fullpath;
	return rtn;
}	

// �õ������ļ�
wstring DemoCtrl::getDetailAppFile(){
	LPTSTR path = L"res/deatil/index.app";
	if (_waccess(path, 0) != 0){// ����������������
		path = L"../../res/deatil/index.app";
	}
	wchar_t fullpath[1024];
	_wfullpath(fullpath, path, 1024);
	wstring rtn(fullpath);
	delete[]fullpath;
	return rtn;
}
// �õ�JWebTop.exe��·��
wstring DemoCtrl::getJWebTopExe(){
	return L"JWebTop.exe";
}

void DemoCtrl::_startJWebTop(){
	wstring appFile = this->getListAppFile();
	ctx->createJWebTopByCfgFile(this->getJWebTopExe(), appFile, this);
}

void DemoCtrl::init(){
	if (ctx != NULL)return;
	ctx = new JWebTopContext();
	thread th(std::mem_fn(&DemoCtrl::_startJWebTop), this);
	th.detach(); //�����߳�  
}

void DemoCtrl::onJWebTopAppInited(){
	wstring appFile = this->getListAppFile();
	JWebTopConfigs * configs = new JWebTopConfigs();
	configs->appDefFile = appFile;
	configs->name = L"�б�ҳ";
	ctx->createBrowser(configs, this);
}

void DemoCtrl::onJWebTopBrowserCreated(long browserHWnd){
	this->listBrowser = (HWND)browserHWnd;
}

//DWORD startJWebTopProcess(std::wstring clientExe, std::wstring serverName, DWORD blockSize){
//	STARTUPINFO sui;
//	ZeroMemory(&sui, sizeof(STARTUPINFO));
//	sui.cb = sizeof(STARTUPINFO);
//	PROCESS_INFORMATION pi; // �������������ӽ��̵���Ϣ
//	DWORD dwCreationFlags = CREATE_NEW_PROCESS_GROUP;
//	// ����������
//	std::wstringstream wss; wss << clientExe << L" " << serverName << L" " << blockSize;
//	if (CreateProcess(NULL, LPTSTR(wss.str().c_str()), // ��һ�������ÿգ���ִ���ļ��������зŵ�һ���������������
//		NULL, NULL, FALSE, dwCreationFlags, NULL, NULL, &sui, &pi)){
//		CloseHandle(pi.hProcess);
//		CloseHandle(pi.hThread);
//		return pi.dwThreadId;
//	}
//	return 0;
//}
//
//
//int startJWebTop(){
//	std::wstring clientExee = L"JWebTop.exe";// ��������̵�·��
//	if (_waccess(LPTSTR(clientExee.c_str()), 0) != 0){
//		serverName.append(L"�ļ��Ҳ�����");
//		MessageBox(NULL, LPTSTR(serverName.c_str()), L"��Ϣ", 0);// ����ļ�������
//		return 2;
//	} else{
//		if (startJWebTopProcess(clientExee, serverName, blockSize) == 0){// �����ӽ��̣�ʧ�ܺ󷵻�
//			return 3;
//		}
//	}
//	return 0;
//}
//
//int initJWebTop(){
//	blockSize = 2048;// 
//	blockSize = 2000;// ָ��һ���������ռ䣬���ں���������̽�������
//	int r = startIPCServer();
//	if (r != 0)return r;// ��һ�����������̵�FastIPCServer
//	r = startJWebTop();
//	if (r != 0){
//		server.close();
//		return r;
//	}
//	return 0;
//}