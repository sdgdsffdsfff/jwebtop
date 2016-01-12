#include "DLLExState.h"

#ifdef JWebTopLog
#include "common/tests/TestUtil.h"
#endif 

namespace jw{
	namespace dllex{// ��DLL���н����������չ����
		wstring DLLExState::getAppendJS(){
			return this->appendJS;
		}
		void DLLExState::setAppendJS(wstring js){
			this->appendJS = js;// ��¼�����������븽��JS�Ĺ���			
		}		

		// ��̬�����뷽��
		DLLExState::DefBrowserSateMap DLLExState::browserStateMap;			// �����������չ״̬����̬������

		DLLExState * DLLExState::findWithoutCreate(HWND browserHWnd){
			DLLExState * rtn = NULL;
			DefBrowserSateMap::iterator it = browserStateMap.find(browserHWnd);
			if (browserStateMap.end() != it) {
				rtn = it->second;
			}
			return rtn;
		}

		DLLExState * DLLExState::findOrCreateExState(HWND browserHWnd){
			DLLExState * rtn = NULL;
			DefBrowserSateMap::iterator it = browserStateMap.find(browserHWnd);
			if (browserStateMap.end() != it) {
				rtn = it->second;
			}
			else{
				rtn = new DLLExState();
				browserStateMap.insert(pair<HWND, DLLExState* >(browserHWnd, rtn));// ��¼��������������չ״̬�Ĺ���
			}
			return rtn;
		}

		void DLLExState::unlockBrowserLocks(HWND browserHwnd){
			DLLExState *  exState = findWithoutCreate(browserHwnd);
			if (exState == NULL)return;
		}
		void DLLExState::removeBrowserSetting(HWND browserHwnd){
			DLLExState *  exState = findWithoutCreate(browserHwnd);
			if (exState == NULL)return;
			unlockBrowserLocks(browserHwnd);
			browserStateMap.erase(browserHwnd);
		}

		void DLLExState::appendBrowserJS(HWND browserHwnd, const CefRefPtr<CefFrame> frame){
			DLLExState *  exState = findWithoutCreate(browserHwnd);
			if (exState == NULL)return;
			wstring js = exState->getAppendJS();
#ifdef JWebTopLog
			writeLog(L"���ӵ�JS====="); writeLog(js); writeLog(L"\r\n");
#endif
			if (!js.empty())frame->ExecuteJavaScript(js, "", 0);
		}
	}// End dllex namespace
}// End jw namespace