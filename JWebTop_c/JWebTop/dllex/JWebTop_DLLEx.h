#ifndef CEF_JWEBTOP_EXE_DLLEX_H_
#define CEF_JWEBTOP_EXE_DLLEX_H_
#include <string>
#include "include/cef_browser.h"
#define B2R_MSG_NAME L"jwebtop_b2r"
using namespace std;
namespace jw{
	namespace dllex{// ��DLL���н����������չ����
		// �Ƿ���dll��չ
		bool ex();
		void setAsEx();

		int startIPCServer(wstring &serverName,DWORD blockSize,DWORD processId);
		void closeIPCServer();
		void OnContextInitialized();

		// ����������Ѵ�����Ϣ���ͻ���
		void sendBrowserCreatedMessage(wstring taskId,long browserHWnd);
		
		// js����dll�ķ�����������غ󣬻�ִ����Ӧ��callback
		void invokeRemote_CallBack(HWND browserHWnd, CefString json, CefString callBackFunName);

		// �����ʱlock����������render��ǰ������������
		//CefString invokeRemote_Wait(HWND browserHWnd, CefString json);
		
		// js����dll�ķ����������ȴ����ؽ��
		void invokeRemote_NoWait(HWND browserHWnd, CefString json);

		// ��render�˰�ͬ����ʽ����js������js��ִ�н��ͨ����Ϣ��ʽ���͵�dll��
		void render_processMsg(CefRefPtr<CefBrowser> browser, CefProcessId source_process, CefRefPtr<CefProcessMessage> message);

		// �������ģʽʱ����FastIPCServerInfo��render���̣��Ա㴴��render�˵�IPCClient
		void sendIPCServerInfo(HWND browserHWnd);
	}
}
#endif