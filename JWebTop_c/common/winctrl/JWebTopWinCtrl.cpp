#include "JWebTopWinCtrl.h"

#include "common/util/StrUtil.h"
#ifdef JWebTopLog
#include "common/tests/TestUtil.h"
#endif
//
namespace jw{
	// setToCenter(handler);// �ô�����ʾ����Ļ����
	void setCenter(HWND hWnd){
		RECT rt;
		GetWindowRect(hWnd, &rt);
		MoveWindow(hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, FALSE);
	}

	// setToCenter(handler);// �ô�����ʾ����Ļ����
	void setCenter(HWND hWnd, int x, int y, int w, int h){
		POINT p = getScreenSize();
		if (p.x <= w){
			x = 0;
			w = p.x;
		}
		else{
			x = (p.x - w) / 2;
		}
		if (p.y < h){
			y = 0;
			h = p.y;
		}
		else{
			y = (p.y - h) / 2;
		}
		MoveWindow(hWnd, x, y, w, h, FALSE);
	}
	// getPos(handler);//��ô���λ�ã�����ֵΪһobject����ʽ����{x:13,y:54}
	POINT getPos(HWND hWnd){
		RECT rt = getBound(hWnd);
		POINT p;
		p.x = rt.left;
		p.y = rt.top;
		return p;
	}
	// setSize(x, y, handler);//���ô��ڴ�С
	void setSize(HWND hWnd, int w, int h){
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, w, h, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);// ֻ�ı䴰�ڴ�С�����ı䴰������ʹ������ڲ��
	}
	// getSize(handler);//��ô��ڴ�С������ֵΪһobject����ʽ����{width:130,height:54}
	POINT getSize(HWND hWnd){
		RECT rt = getBound(hWnd);
		POINT p;
		p.x = rt.right;
		p.y = rt.bottom;
		return p;
	}
	// getScreenSize();//��ȡ��Ļ��С������ֵΪһobject����ʽ����{width:130,height:54}
	POINT getScreenSize(){
		POINT p;
		p.x = GetSystemMetrics(SM_CXFULLSCREEN);
		p.y = GetSystemMetrics(SM_CYFULLSCREEN) + GetSystemMetrics(SM_CYCAPTION);
		return p;
	}
	// move(x, y, handler);//�ƶ�����
	void move(HWND hWnd, int x, int y){
		::SetWindowPos(hWnd, HWND_TOPMOST, x, y, 0, 0, SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS | SWP_NOSIZE | SWP_NOZORDER | SWP_NOSENDCHANGING);// �ƶ����ڣ������ı䴰�ڴ�С�ʹ������ڲ��
	}
	// setBound(x, y,w ,h, handler);// ͬʱ���ô��ڵ�����ʹ�С
	void setBound(HWND hWnd, int x, int y, int w, int h){
		::MoveWindow(hWnd, x, y, w, h, false);
	}
	// ��ȡ������Ϣ������ֵΪ�����ϽǺ����½ǵ���Ļ����
	RECT getBound(HWND hWnd){
		RECT rt;
		GetWindowRect(hWnd, &rt);
		return rt;
	}
	// setTitle(title, handler);// ���ô�������
	void setTitle(HWND hWnd, wstring title){
		SetWindowText(hWnd, title.c_str());
	}
	// getTitle(handler);// ��ȡ�������ƣ�����ֵΪһ�ַ���
	wstring getTitle(HWND hWnd){
		TCHAR title[1000];// ��������ʼ��
		::GetWindowText(hWnd, title, sizeof(title));// ��ȡ��������
		return title;
	}
	// bringToTop(handler);//�����Ƶ����
	void bringToTop(HWND hWnd){
		SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
	}
	// focus(handler);//ʹ���ڻ�ý���
	void focus(HWND hWnd){
		SetFocus(hWnd);
	}
	void showWindow(HWND hWnd,int style){
		ShowWindow(hWnd, style);
	}
	// hide(handler);//���ش���
	void hide(HWND hWnd){
		ShowWindow(hWnd, SW_HIDE);
	}
	// max(handler);//��󻯴���
	void maxWin(HWND hWnd){
		//setBound(hWnd, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN) + GetSystemMetrics(SM_CYCAPTION));
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	// mini(hander);//��С������
	void mini(HWND hWnd){
		if (GetWindowLong(hWnd, GWL_EXSTYLE)&WS_EX_TOOLWINDOW){
			ShowWindow(hWnd, SW_HIDE);
		}
		else{
			ShowWindow(hWnd, SW_MINIMIZE);
		}
	}
	// restore(handler);//��ԭ���ڣ���Ӧ��hide����
	void restore(HWND hWnd){
		ShowWindow(hWnd, SW_RESTORE);
	}

	BOOL isVisible(HWND hWnd){
		return IsWindowVisible(hWnd);
	}
	// setTopMost(handler);//�����ö����˺�����bringToTop���������ڴ˺�����ʹ������Զ�ö�������������һ�����ڵ������ö�����
	void setTopMost(HWND hWnd){
		DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);//��ȡ����ʽ  
		DWORD dwNewExStyle = WS_EX_TOPMOST;
		dwNewExStyle |= dwExStyle;//��λ�뽫����չ��ʽȥ��  
		SetWindowLong(hWnd, GWL_EXSTYLE, dwNewExStyle);//�����µ���չ��ʽ
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}

	//setWindowStyle(style, handler);//�߼����������ô��ڶ������ԣ���Ӧ�������ڵ�dwStyle��
	void setWindowStyle(HWND hWnd, int style){
		SetWindowLong(hWnd, GWL_STYLE, style);//�����µ���չ��ʽ  
	}

	//setWindowExStyle(exStyle, handler);//�߼����������ô��ڶ������ԣ���Ӧ�������ڵ�dwExStyle��
	void setWindowExStyle(HWND hWnd, int exStyle){
		SetWindowLong(hWnd, GWL_EXSTYLE, exStyle);//�����µ���չ��ʽ  
	}
}