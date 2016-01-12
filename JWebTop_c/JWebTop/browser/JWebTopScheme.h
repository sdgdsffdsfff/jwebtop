#ifndef CEF_JWEBTOP_Scheme_H_
#define CEF_JWEBTOP_Scheme_H_
#include <set>
#include "include/cef_app.h"
#include "include/wrapper/cef_message_router.h"
namespace jw{
	namespace jb{// jb=jwebtop browser���������ص�һЩ������ͷ���

		// ��ȡ�������Ӷ�Ӧ��mime����
		std::string GetMimeType(const std::string& url);

		// ע��jwebtop://Э�鵽���������Ҫ���ڶ�ȡ�����ļ�
		void RegisterSchemeHandlers();
	}
}
#endif  // CEF_JWEBTOP_APP_H_