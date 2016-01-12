#pragma once
#ifndef CEF_JWEBTOP_WIN_CTRL_H_
#define CEF_JWEBTOP_WIN_CTRL_H_
#include <Windows.h>
#include <string>

namespace jw{
	_declspec(dllexport) void  setCenter(HWND hWnd);                             // setToCenter(handler);// �ô�����ʾ����Ļ����
	_declspec(dllexport) void  setCenter(HWND hWnd, int x, int y, int w, int h); // setToCenter(handler);// �ô�����ʾ����Ļ����
	_declspec(dllexport) POINT getPos(HWND hWnd);                                // getPos(handler);//��ô���λ�ã�����ֵΪһobject����ʽ����{x:13,y:54}
	_declspec(dllexport) void  setSize(HWND hWnd, int w, int h);                 // setSize(x, y, handler);//���ô��ڴ�С
	_declspec(dllexport) POINT getSize(HWND hWnd);                               // getSize(handler);//��ô��ڴ�С������ֵΪһobject����ʽ����{width:130,height:54}
	_declspec(dllexport) POINT getScreenSize();                                  // getScreenSize();//��ȡ��Ļ��С������ֵΪһobject����ʽ����{width:130,height:54}
	_declspec(dllexport) void  move(HWND hWnd, int x, int y);                    // move(x, y, handler);//�ƶ�����
	_declspec(dllexport) void  setBound(HWND hWnd, int x, int y, int w, int h);  // setBound(x, y,w ,h, handler);// ͬʱ���ô��ڵ�����ʹ�С
	_declspec(dllexport) RECT  getBound(HWND hWnd);                              // getBound(handler);//��ȡ������Ϣ������ֵΪ�����ϽǺ����½ǵ���Ļ����
	_declspec(dllexport) void  setTitle(HWND hWnd, std::wstring title);          // setTitle(title, handler);// ���ô�������
	_declspec(dllexport) std::wstring getTitle(HWND hWnd);                       // getTitle(handler);// ��ȡ�������ƣ�����ֵΪһ�ַ���

	_declspec(dllexport) void bringToTop(HWND hWnd);		// bringToTop(handler);//�����Ƶ����
	_declspec(dllexport) void focus(HWND hWnd);				// focus(handler);//ʹ���ڻ�ý���
	_declspec(dllexport) void showWindow(HWND hWnd, int);	// ���ô�����ʾ״̬
	_declspec(dllexport) void hide(HWND hWnd);				// hide(handler);//���ش���
	_declspec(dllexport) void maxWin(HWND hWnd);		    // max(handler);//��󻯴���
	_declspec(dllexport) void mini(HWND hWnd);				// mini(hander);//��С������
	_declspec(dllexport) void restore(HWND hWnd);			// restore(handler);//��ԭ���ڣ���Ӧ��hide����
	_declspec(dllexport) BOOL isVisible(HWND hWnd);			// �����Ƿ�����ʾ
	_declspec(dllexport) void setTopMost(HWND hWnd);		// setTopMost(handler);//�����ö����˺�����bringToTop���������ڴ˺�����ʹ������Զ�ö�������������һ�����ڵ������ö�����

	_declspec(dllexport) void setWindowStyle(HWND hWnd, int style);	// setWindowStyle(exStyle, handler);//�߼����������ô��ڶ������ԣ������ö�֮�ࡣ
	_declspec(dllexport) void setWindowExStyle(HWND hWnd, int exStyle);  // setWindowExStyle(exStyle, handler)
}
#endif