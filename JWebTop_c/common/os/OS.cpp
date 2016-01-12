#include "OS.h"
#include <sstream>
#include "common/util/StrUtil.h"
#include "common/tests/TestUtil.h"

using namespace std;
namespace jw{
	namespace os{
		namespace file{
			// �����ļ�����ȡ�ļ�����·��
			wstring GetFilePath(wstring appDefFile){
				const int BUFSIZE = 4096;
				TCHAR  buffer[BUFSIZE] = TEXT("");
				GetFullPathName(LPCWSTR(appDefFile.data()), BUFSIZE, buffer, NULL);// ��ȡ�ļ��ľ���·��
				wstring pp(buffer);
				int p = pp.find_last_of('\\');
				if (p != -1)pp = pp.substr(0, p + 1);
				return pp;
			}

			// �õ���������Ŀ¼
			wstring GetExePath(){
				TCHAR   szPath[1000];
				GetModuleFileName(NULL, szPath, MAX_PATH);
				wstring path(szPath);
				path = path.substr(0, path.find_last_of('\\') + 1);
				return path;
			}

			// �������·����ȡ����·��
			// ���relativePath�Ѿ��Ǿ���·������ֱ�ӷ���
			// ���򽫷���appPath+relativePath
			wstring getAbsolutePath(wstring &relativePath, wstring &appPath){
				if (relativePath.find(L":") == -1){// ���ָ����·�������·��
					wstring _path(appPath);
					_path.append(relativePath);
					return _path;
				}
				return relativePath;
			}
		}// End file namespace
		namespace process{
			// ����һ���½��̣����ص�����Ϊ���������̵߳�id
			DWORD createSubProcess(LPTSTR subProcess, LPTSTR szCmdLine){
				std::wstring cmd;
				if (subProcess[0] == L'"'){// ���url������˫���ſ�ͷ����ô����Ͳ������˫����
					cmd.append(subProcess);
				}
				else{// ���ӽ�����˫���Ű�����������������������
					cmd.append(L"\"");
					cmd.append(subProcess);
					cmd.append(L"\"");
				}
				cmd += L" "; cmd += szCmdLine;// ׷��һ���ո��������в�����ǰ�棬�����½��̵�szCmdLine��ȡ��������

				STARTUPINFO sui;
				ZeroMemory(&sui, sizeof(STARTUPINFO)); // ��һ���ڴ������㣬�����ZeroMemory, �����ٶ�Ҫ����memset
				sui.cb = sizeof(STARTUPINFO);

				PROCESS_INFORMATION pi; // �������������ӽ��̵���Ϣ
				//DWORD dwCreationFlags = DETACHED_PROCESS | CREATE_NEW_PROCESS_GROUP;
				DWORD dwCreationFlags = CREATE_NEW_PROCESS_GROUP;
				if (CreateProcess(NULL, LPTSTR(cmd.c_str()), // ��һ�������ÿգ���ִ���ļ��������зŵ�һ���������������
					NULL, NULL, FALSE,//������̳� 
					dwCreationFlags, //ʹ���������ȼ� 
					NULL, //ʹ�ø����̵Ļ������� 
					NULL, //ָ������Ŀ¼ 
					&sui, &pi))
				{
					CloseHandle(pi.hProcess); // �ӽ��̵Ľ��̾��
					CloseHandle(pi.hThread);  // �ӽ��̵��߳̾����windows�н��̾���һ���̵߳�������ÿ������������һ���߳���ִ��
					return pi.dwThreadId;
				}
				//else{// else�Ĵ�����Ҫ��Ϊ�˷�����VS�����µ��Գ�����ΪVS�������ĳ���Ĭ�ϵĹ���Ŀ¼��$(ProjectDir)�������Ϊ$(SolutionDir)$(Configuration)\����Ҫelse�Ĵ���
				//	TCHAR   szPath[1000];
				//	GetModuleFileName(NULL, szPath, MAX_PATH);
				//	std::wstring path(szPath);
				//	path = path.substr(0, path.find_last_of('\\') + 1);
				//	path += subProcess;
				//	if (CreateProcess(path.c_str(), LPTSTR(cmd.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &sui, &pi))
				//	{
				//		CloseHandle(pi.hProcess); // �ӽ��̵Ľ��̾��
				//		CloseHandle(pi.hThread);  // �ӽ��̵��߳̾����windows�н��̾���һ���̵߳�������ÿ������������һ���߳���ִ��
				//		return pi.dwThreadId;
				//	}
				//}
				return 0;
			}
		}// End process namespace
	}// End os namespace
}// End jw namespace