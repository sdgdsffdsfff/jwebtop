#ifndef _Included_org_jwebtop_dll4csharp
#define _Included_org_jwebtop_dll4csharp
#include <string>
#include <Windows.h>

#define EXPORT __declspec(dllexport)

extern "C" {
	// ����һ���½��̣����ص�����Ϊ���������̵߳�id
	// ����һ���½��̣����ص�����Ϊ���������̵߳�id
	EXPORT long WINAPI nCreateSubProcess(LPTSTR subProcess, LPTSTR szCmdLine, int waitFor);

	/*
	* �÷������ڴ���һ��fastipc�����
	* serverName	���������
	* blockSize		�������ͻ���ͨ��ʱÿ�ε�������
	* result		�������������Ƿ񴴽��ɹ���0=�ɹ�
	* return		������Server��ָ��
	*/
	EXPORT long WINAPI nCreateServer(LPTSTR serverName, int blockSize, int& result);

	// ����һ���ص�������csharp��ʵ�ִ˻ص�����
	typedef void *(CALLBACK *CSharpCallBack)(int msgType, char* packId,
		int userMsgType, long userValue, char* userShortStr,
		char* data, int dataLen);

	/*
	* �÷������ڿ���fastipc����˵Ķ�ȡ�������ɹ���������ڴ˴�
	* nativeServer	ָ������ʵ����ָ��
	* listener		��Ӧ��ȡ������ָ��
	*/
	EXPORT void WINAPI nStartRead(int nativeServer, CSharpCallBack callBack);

	/*
	* �÷������ڹر�fastipc����ˣ�ִ�к�nStartRead��������ֹͣ
	* nativeServer	ָ������ʵ����ָ��
	*/
	EXPORT void WINAPI nCloseServer(int nativeServer);

	/*
	* �÷������ڴ���һ��fastipc�ͻ���
	* serverName	�ͻ��˶�Ӧ�ķ���˵�����
	* blockSize		�������ͻ���ͨ��ʱÿ�ε�������
	* result		�������������Ƿ񴴽��ɹ���0=�ɹ�
	* return		������Client��ָ��
	*/
	EXPORT int WINAPI nCreateClient(LPTSTR serverName, int blockSize, int& result);

	/*
	* �÷���������fastipc�ͻ���д�����ݣ�����д��ɺ󣬻ᴥ������˵�����
	* nativeClient	ָ��ͻ���ʵ����ָ��
	* data			Ҫд�������
	* return		�ɹ�д������ݳ���
	*/
	EXPORT int WINAPI nWriteClient(int nativeClient, int userMsgType, int userValue, LPTSTR userShortStr, LPTSTR data);

	/*
	* �÷������ڹر�fastipcnWriteClient
	* nativeClient	ָ��ͻ���ʵ����ָ��
	*/
	EXPORT void WINAPI nCloseClient(int nativeClient);
}
#endif