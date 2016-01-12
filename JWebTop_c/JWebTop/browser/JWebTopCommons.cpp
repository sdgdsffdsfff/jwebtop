#include "JWebTopCommons.h"
#include <Windows.h>
#include <string>
#include "JWebTopClient.h"
#include "include/cef_app.h"
#include "include/cef_parser.h"
#include "include/cef_browser.h"
#include "include/wrapper/cef_helpers.h"
#include "JWebTop/wndproc/JWebTopWndProc.h"
#include "JWebTopContext.h"
#include "common/util/StrUtil.h"
#include "common/winctrl/JWebTopWinCtrl.h"
#ifdef JWebTopLog
#include "common/tests/TestUtil.h"
#endif
using namespace std;
const char kTestMessageName[] = "close";
bool excuteJSON(const CefString& request){
	CefRefPtr<CefValue> v = CefParseJSON(request, JSON_PARSER_RFC);          // ���н���
	if (v == NULL){
		//callback->Failure(1, CefString(L"�����JSON��ʽ"));
		return false;
	}
#ifdef JWebTopLog 
	wstringstream log;
	log << L"JWebTopCommons#Handler#OnQuery jsons=" << request.ToWString() << L"\r\n";
	writeLog(log.str());
#endif
	CefRefPtr<CefDictionaryValue> value = v->GetDictionary();// ��JSON�ֵ�����ȡ
	wstring methodName = value->GetString("m").ToWString();  // ȡ��ĳ�ַ��� 
	 if (methodName == L"loadUrl"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		CefRefPtr<CefValue> url = value->GetValue("url");
		if (url == NULL)return false;
		jb::loadUrl((HWND)handler->GetInt(), url->GetString().ToWString());
	}
	else if (methodName == L"reload"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		jb::reload((HWND)handler->GetInt());
	}
	//// (true|false,[handler]);// ��������϶�
	//extensionCode << "JWebTop.=function(enable,handler){JWebTop.cefQuery({m:'enableDrag',enable:enable,handler:(handler?handler:JWebTop.handler)})};" << endl;
	//// ([handler]);// ��ʼ�����϶�
	//extensionCode << "JWebTop.=function(handler){JWebTop.cefQuery({m:'startDrag',handler:(handler?handler:JWebTop.handler)})};" << endl;
	//// ([handler]);// ֹͣ�϶�
	//extensionCode << "JWebTop.=function(handler){JWebTop.cefQuery({m:'stopDrag',handler:(handler?handler:JWebTop.handler)})};" << endl;
	else if (methodName == L"enableDrag"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		CefRefPtr<CefValue> enable = value->GetValue("enable");
		if (enable == NULL)return false;
		jb::enableDrag((HWND)handler->GetInt(), enable->GetBool());
	}
	else if (methodName == L"startDrag"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		jb::startDrag((HWND)handler->GetInt());
	}
	else if (methodName == L"stopDrag"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		jb::stopDrag((HWND)handler->GetInt());
	}
	else if (methodName == L"reloadIgnoreCache"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		jb::stopDrag((HWND)handler->GetInt());
	}
	else if (methodName == L"runApp"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		CefRefPtr<CefValue> app = value->GetValue("app");
		CefRefPtr<CefValue> parentWin = value->GetValue("parentWin");
		jb::runApp((HWND)handler->GetInt(), app->GetString().ToWString(), parentWin == NULL ? 0 : parentWin->GetInt()
			,NULL,NULL,NULL,-1,-1,-1,-1);
	}
	else if (methodName == L"runAppMore"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		CefRefPtr<CefValue> app = value->GetValue("app");
		CefRefPtr<CefValue> parentWin = value->GetValue("parentWin");
		CefRefPtr<CefValue> url = value->GetValue("url");
		CefRefPtr<CefValue> title = value->GetValue("title");
		CefRefPtr<CefValue> icon = value->GetValue("icon");
		CefRefPtr<CefValue> x = value->GetValue("x");
		CefRefPtr<CefValue> y = value->GetValue("y");
		CefRefPtr<CefValue> w = value->GetValue("w");
		CefRefPtr<CefValue> h = value->GetValue("h");
		jb::runApp((HWND)handler->GetInt(), app->GetString().ToWString(), parentWin == NULL ? 0 : parentWin->GetInt()
			, (url == NULL ? NULL : LPTSTR(url->GetString().ToWString().c_str()))
			, (title == NULL ? NULL : LPTSTR(title->GetString().ToWString().c_str()))
			, (icon == NULL ? NULL : LPTSTR(icon->GetString().ToWString().c_str()))
			, (x == NULL ? -1 : x->GetInt())
			, (y == NULL ? -1 : y->GetInt())
			, (w == NULL ? -1 : w->GetInt())
			, (h == NULL ? -1 : h->GetInt()));
	}
	else if(methodName == L"close"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		jb::close((HWND)handler->GetInt());
	}
	else if (methodName == L"showDev"){
		CefRefPtr<CefValue> handler = value->GetValue("handler");
		if (handler == NULL)return false;
		jb::showDev((HWND)handler->GetInt());
	}
	else{
		return false;
	}
	return true;
}
namespace jc/*jc=JWebTop Client*/{
	class Handler : public CefMessageRouterBrowserSide::Handler {
	public:
		Handler() {}

		// ��Ӧrender���̷��͹�������Ϣ
		virtual bool OnQuery(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int64 query_id,
			const CefString& request,// requestΪ��ϢJSON����{request:msg}��msg���֣�������չһ��JSON���������н��������������룺cef_message_router.cc=��CefMessageRouterRendererSideImpl��
			bool persistent, CefRefPtr<Callback> callback) OVERRIDE{
			return excuteJSON(request);
		}
	};
	void CreateBrowserSideMessageHandlers(MessageHandlerSet& handlers) {
		handlers.insert(new Handler());
	}
}
namespace jw{
	extern JWebTopConfigs * g_configs;  // Ӧ������ʱ�ĵ�һ�����ñ���
}

void createNewBrowser(JWebTopConfigs * configs){
	createNewBrowser(configs, wstring());
}
void createNewBrowser(JWebTopConfigs * configs,wstring taskId){
	CEF_REQUIRE_UI_THREAD();
	if (configs == NULL)configs = jw::ctx::getDefaultConfigs();
	// ���ڹ������ش��ڵ�������Ϣ
	CefWindowInfo window_info;
#if defined(OS_WIN)
	// On Windows we need to specify certain flags that will be passed to
	window_info.SetAsPopup((HWND)configs->parentWin, configs->name);
#endif
	if (configs->dwStyle != 0)window_info.style = configs->dwStyle;
	if (configs->dwExStyle != 0)window_info.ex_style = configs->dwExStyle;
	window_info.width = configs->w == -1 ? CW_USEDEFAULT : configs->w;
	window_info.height = configs->h == -1 ? CW_USEDEFAULT : configs->h;
	POINT p = jw::getScreenSize();
	if (configs->x == -1){							// δָ��x����
		if (p.x <= configs->w){			            // ���õĿ�ȳ�������Ļ���
			window_info.x = 0;						// ����x����Ϊ0
			window_info.width = p.x;				// �������ÿ��Ϊ��Ļ���
		}
		else if (configs->w != -1){				    // �����ô��ڿ��
			window_info.x = (p.x - configs->w) / 2; // ������Ļ��Ⱥʹ��ڿ�ȼ���x����λ��
		}
		else{
			window_info.x = CW_USEDEFAULT;			// δ���ô��ڿ�ȣ���ôx����ȡĬ��ֵ
		}
	}
	else{
		window_info.x = configs->x;					// ��ָ��x���꣬��ôֱ��ȡx�����ֵ
	}
	if (configs->y == -1){							// δָ��y����
		if (p.y <= configs->h){			            // ���õĸ߶ȳ�������Ļ�߶�
			window_info.y = 0;						// ����y����Ϊ0
			window_info.height = p.y;				// �������ø߶�Ϊ��Ļ�߶�
		}
		else if (configs->h != -1){				    // �����ô��ڸ߶�
			window_info.y = (p.y - configs->h) / 2; // ������Ļ�߶Ⱥʹ��ڸ߶ȼ���y����λ��
		}
		else{
			window_info.y = CW_USEDEFAULT;			// δ���ô��ڸ߶ȣ���ôy����ȡĬ��ֵ
		}
	}
	else{
		window_info.y = configs->y;					// ��ָ��y���꣬��ôֱ��ȡy�����ֵ
	}
#ifdef JWebTopLog 
	std::wstringstream log;
	log << L"processId=" << GetCurrentProcessId() << L" threadId=" << GetCurrentThreadId() << " title=" << configs->name.ToWString() << L"\r\n";
	log << L"JWebTopCommons createNewBrowser parentWin=" << configs->parentWin << L"\r\n";
	log << L"\tconfigs[x=" << configs->x << ",y=" << configs->y << ",w=" << configs->w << ",h=" << configs->h << "]\r\n"
		<< L"\tsetings[x=" << window_info.x << ",y=" << window_info.y << ",w=" << window_info.width << ",h=" << window_info.height << "]\r\n"
		<< L"\tstyle=" << window_info.style << ",ex_style=" << window_info.ex_style << "]\r\n"
		<< L"\tscreninfo[x="<<p.x <<",y=" << p.y << L"]\r\n";
	writeLog(log.str());
#endif
	CefRefPtr<JWebTopClient>  handler = new JWebTopClient();
	handler->setJWebTopConfigs(configs);
	handler->setTaskId(taskId);
	CefBrowserSettings browser_settings;
	browser_settings.web_security = cef_state_t::STATE_DISABLED;                      // ����ҳ�氲ȫ�����ã�������������Դ
	browser_settings.universal_access_from_file_urls = cef_state_t::STATE_ENABLED;
	browser_settings.file_access_from_file_urls = cef_state_t::STATE_ENABLED;
	browser_settings.application_cache = cef_state_t::STATE_DISABLED;// ��ֹ���������
	// �������������
	CefBrowserHost::CreateBrowser(
		window_info, handler.get(), 
		configs->getAbsolutePath(configs->url.ToWString()),
		browser_settings, NULL);
}