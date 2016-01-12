#ifndef CEF_JWEBTOP_WIN_WNDPROC_H_
#define CEF_JWEBTOP_WIN_WNDPROC_H_
#include <sstream>
#include <string>
#include "include/cef_browser.h"
#include "JWebTop/config/JWebTopConfigs.h"

using namespace std;
// ���ڵ��Թ��ߴ��ڵ�cefclient���������JWebTopHandler��Ѷ�JWebTop�Ĵ���������DEBUG��ҲӦ��һ�Σ�
class DEBUG_Handler : public CefClient{ IMPLEMENT_REFCOUNTING(DEBUG_Handler); };
class BrowserWindowInfo{
public:
	HWND hWnd = NULL;					// CEF��������ⲿ����
	HWND bWnd = NULL;					// CEF�ڲ����������
	HWND rWnd = NULL;					// CEF�ڲ�����������
	bool isWsChild = false;				// �Ƿ���WS_CHILD���

	LONG oldMainProc;                   // ���������������֮ǰ����Ϣ������
	LONG oldBrowserProc;                // ���������֮ǰ����Ϣ������
	LONG oldRenderProc;                 // �ڲ����ƴ���֮ǰ����Ϣ������

	CefRefPtr<CefBrowser> browser;      // ���ڹ������������

	bool enableDrag = true;				// �Ƿ��������϶�
	bool isDraging = false;			    // �Ƿ������϶�����
	LONG dragX = 0, dragY = 0;			// �����϶���ʼʱ��x��y����λ��
};
BrowserWindowInfo * getBrowserWindowInfo(HWND hWnd);

typedef map<HWND, BrowserWindowInfo*> BrowserWindowInfoMap;// ����һ���洢BrowserWindowInfo��Map

// ��CEF��������ڵ���Ϣ��������
LRESULT CALLBACK JWebTop_BrowerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// ����������Ϣ(configs)�Զ��㴰�ں�ʵ����������ڽ�������
void renderBrowserWindow(CefRefPtr<CefBrowser> browser, JWebTopConfigs * configs);


// 
namespace jb{
	void close(HWND hWnd);      // close(handler);// �رմ���

	void setWindowStyle(HWND hWnd, int exStyle);	//setWindowStyle(exStyle, handler);//�߼����������ô��ڶ������ԣ������ö�֮�ࡣ

	void loadUrl(HWND hWnd, wstring url);	//loadUrl(url, handler);//������ҳ��urlΪ��ҳ·��
	void reload(HWND hWnd);	//reload(handler);//���¼��ص�ǰҳ��
	void reloadIgnoreCache(HWND hWnd);	//reloadIgnoreCache(handler);//���¼��ص�ǰҳ�沢���Ի���
	void showDev(HWND hWnd);	//showDev(handler);//�򿪿����߹���

	void ExecJS(HWND hWnd, string js);
	void ExecJS(HWND hWnd, wstring js);

	void enableDrag(HWND hWnd, bool enable);
	void startDrag(HWND hWnd);
	void stopDrag(HWND hWnd);

	void runApp(HWND hWnd, wstring appDefFile, long parentWin, const LPTSTR url, const LPTSTR &title, const LPTSTR &icon, const  int x, const  int y, const  int w, const  int h);

	void checkAndSetResizeAblity(HWND hWnd);// ��鴰���Ƿ����϶��ı��С
}
#endif