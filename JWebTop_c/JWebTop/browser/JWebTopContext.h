// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
#ifndef CEF_JWEBTOP_BROWSER_CONTEXT_H_
#define CEF_JWEBTOP_BROWSER_CONTEXT_H_

#include <list>
#include <set>
#include "include/cef_client.h"
#include "include/wrapper/cef_message_router.h"
#include "JWebTop/config/JWebTopConfigs.h"
namespace jw{
	namespace ctx{
		//// ����JSON�����ú�����JWebTop
		//void startJWebTopByJSON(std::wstring cfgJson);
		// �����ļ������ú�����JWebTop
		void startJWebTopByFile(std::wstring cfgFile);
		// �ر�cef��ص�����
		void closeJWebtopContext();
		
		JWebTopConfigs * getDefaultConfigs();
					 
		void setDefaultConfigs(JWebTopConfigs *);

		int getBrowserCount();
		void addBrowser(CefRefPtr<CefBrowser> browser);

		void removeBrowser(CefRefPtr<CefBrowser> browser);

		// �ر����д򿪵������
		void CloseAllBrowsers(bool force_close);

		// �������д����˵������
		typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
	}
}
#endif  // CEF_JWEBTOP_BROWSER_CONTEXT_H_
