#ifndef jwebtop_common_OS_H_
#define jwebtop_common_OS_H_
#include <string>
#include <Windows.h>

using namespace std;
namespace jw{
	namespace os{
		namespace file{			
			// �����ļ�����ȡ�ļ�����·��
			_declspec(dllexport) wstring GetFilePath(wstring appDefFile);

			// �õ���������Ŀ¼
			_declspec(dllexport) wstring GetExePath();

			// �������·����ȡ����·��
			// ���relativePath�Ѿ��Ǿ���·������ֱ�ӷ���
			// ���򽫷���appPath+relativePath
			_declspec(dllexport) wstring getAbsolutePath(wstring &relativePath, wstring &appPath);
		};// End file namespace

		namespace process{
			// ����һ���½��̣����ص�����Ϊ���������̵߳�id
			_declspec(dllexport) DWORD createSubProcess(LPTSTR subProcess, LPTSTR szCmdLine);
		};// End process namespace
	}// End os namespace
}// End jw namespace
#endif