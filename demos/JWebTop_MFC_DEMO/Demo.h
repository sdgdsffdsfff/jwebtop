//////////////////////////////////////////////////////////////////////////  
/// �������fatipc��������ͻ���ͨ��ʱ��Ҫ�Ĵ��ڡ��������Լ�������
///  
/// Դ�룺https://github.com/washheart/jwebtop
/// ˵����https://github.com/washheart/jwebtop/wiki
/// @version	1.0 
/// @author		washheart@163.com
/// @date       2015-10-22  
////////////////////////////////////////////////////////////////////////// 
#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include "jwebtopex/jwebtopex.h"

#define BTN_ADD_NOTE		101
#define BTN_DEL_NOTE		102

#define MARGIN				10
#define BAR_HEIGHT			24
#define BTN_WIDTH			120

// �������ں���
void createWin(HINSTANCE hInstance);

class DemoCtrl :JWebTopAppInited, JWebTopBrowserCreated, JWebTopJSReturn, JWebtopJSONDispater {
private:
	JWebTopContext * ctx = NULL;
	HWND listBrowser = NULL;
	HWND detailBrowser = NULL;

	void _startJWebTop();
public :
	void init();

	wstring getListAppFile();	// �õ������ļ�
	wstring getDetailAppFile();	// �õ������ļ�
	wstring getJWebTopExe();	// �õ�JWebTop.exe��·��
	HWND getListBrowser(){ return this->listBrowser; };
	HWND getDetailBrowser(){ return this->detailBrowser; };
	void addNote(wstring note);
	void delNote();

	void onJWebTopAppInited();
	void onJWebTopBrowserCreated(long browserHWnd);
	void onJWebTopJSReturn(wstring jsonString);
	wstring onDispatcher(long browserHWnd, wstring json);

};