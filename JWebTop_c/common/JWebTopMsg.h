#ifndef jwebtop_multi_process_jwebtop_msg_H_
#define jwebtop_multi_process_jwebtop_msg_H_
#include <string>

#include "include/cef_parser.h"
#include "common/process/MultiProcess.h"

#define JWEBTOP_MSG_EXECJS			MPMSG_USER+1    // JWebTop������DLLͨ��ʱ����Ϣֵ��ִ��JS�ű�
#define JWEBTOP_MSG_EXECJSON		MPMSG_USER+2    // JWebTop������DLLͨ��ʱ����Ϣֵ��ִ��JSON
#define JWEBTOP_MSG_LOADURL			MPMSG_USER+11   // ����MPMSG_MINI��MPMSG_LARGE��msgId����ʼֵ

#define JWEBTOP_MSG_EXECUTE_WAIT	MPMSG_USER+201  // ��Ҫִ�в��ȴ������� 
#define JWEBTOP_MSG_EXECUTE_RETURN	MPMSG_USER+202  // 
#define JWEBTOP_MSG_RESULT_RETURN	MPMSG_USER+203  
namespace jw{
	// �Ӵ����JSON�ַ���(jsonString)�н���������id(taskId)�;����JSON�ַ���(parsedJO)���Ѿ��ظ���Ϣ�Ĵ��ھ��
	// jsonString�Ľṹ���£�{"id":"task id string","hWnd":123456,"jo":"parsed json string"}
	// hWnd��taskId��parsedJsonStringΪ���������ֱֵ�ӷ��ء������ɹ��󷵻�true������ʧ�ܻ᷵��false
	bool parseMessageJSON(std::wstring jsonString,long &hWnd, std::wstring &taskId, std::wstring &parsedJsonString);

	// ������Ĵ�������Ϣ�Ĵ��ھ��������id(taskId)��JSON�ַ���(someJsonString)��װΪ�µ�json�ַ���
	// ����json�Ľṹ���£�{"id":"task id string","hWnd":123456,"jo":"some json string"}
	// taskId��someJsonStringʹ�õ��Ǵ��������ʽ��Ŀ��ֻ�Ǽ������ܿ������ڷ����в�Ӧ�޸���ֵ
	std::wstring wrapAsTaskJSON(long hWnd, std::wstring &taskId, std::wstring &someJsonString);
}
#endif