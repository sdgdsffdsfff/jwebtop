#ifndef CEF_JWEBTOP_ex_H_
#define CEF_JWEBTOP_ex_H_
#pragma once
#include "common/fastipc/server.h"
#include "common/fastipc/client.h"
#include "common/util/StrUtil.h"
#include "common/JWebTopMsg.h"
#include "JWebTop/config/JWebTopConfigs.h"

#include <string>
#include <map>
#include <sstream>
/**
* ��JWebTop���̳ɹ���������ã�ֻ���ڴ�ʱ���֮�󣬲ſ��Թ��������
*/
class JWebTopAppInited {
public:
	virtual void onJWebTopAppInited() = 0;
};

/**
* ��ָ������������������
* @param browserHWnd �ɹ�������������Ĵ��ھ��
*/
class JWebTopBrowserCreated {
public:
	virtual void onJWebTopBrowserCreated(long browserHWnd)=0;
};

/**
* jsִ�к��ִ�н��
* @param uuid       ִ��JSʱ���ݵ�uuid�����ݴ���Ҫ����һ��JWebTopJSReturn�д�����JS���ؽ�������
* @param jsonString ִ�н������������������һ��JSON�ַ���
*/
class JWebTopJSReturn {
public:
	virtual void onJWebTopJSReturn(wstring jsonString) = 0;
};
class JWebtopJSONDispater{
public:
	/**
	* ���������������json���ݣ������ؽ��
	*
	* @param browserHWnd
	*            ��Ҫִ��json����������
	* @param json
	*            ������˷�����Ҫִ������
	* @return ���ش����Ľ��
	*/
	wstring dispatcher(long browserHWnd, wstring json);
};

class JWebTopContext
{
private:
	typedef map<wstring, JWebTopJSReturn * > DefJSReturnMap;			// ����һ���洢�������չ״̬��Map��
	DefJSReturnMap jsReturnListners;
	std::wstring serverName;	// ���������
	DWORD blockSize;			// һ�δ���ʱ�����ݴ�С
	fastipc::Server* server;	// IPC�����
	fastipc::Client* client;	// IPC�ͻ���
	JWebtopJSONDispater* jsonHandler;	// ��Ӧ��������̷�����JSON���ݲ����д���

	DWORD _write(LONG userMsgType, LONG userValue,  wstring data){
		string _data=jw::w2s(data);
		return client->write(userMsgType, userValue, NULL, LPSTR(_data.c_str()), _data.size());
	}
	DWORD _write(LONG userMsgType, LONG userValue, wstring userShortStr, wstring data){
		string _ustr = jw::w2s(userShortStr);
		string _data = jw::w2s(data);
		return client->write(userMsgType, userValue, LPSTR(_ustr.c_str()), LPSTR(_data.c_str()), _data.size());
	}
	wstring createTaskId(){
		return jw::GenerateGuidW();
	}
public:
	JWebTopContext(){};
	~JWebTopContext(){ closeContext(); };

	/**
	 * ����JWebTop���̣��ɹ���ص�JWebTopAppInited������
	 *
	 * @param processPath
	 * @param cfgFile
	 * @param appInitListner
	 */
	void createJWebTopByCfgFile(wstring processPath, wstring cfgFile, JWebTopAppInited* appInitListner);

	/**
	 * ���������ļ�������������ɹ���ص�JWebTopBrowserCreated������
	 *
	 * @param browserCfgFile
	 */
	void createBrowserByFile(wstring browserCfgFile, JWebTopBrowserCreated* createListener);

	/**
	* �������ö�����������������ɹ���ص�JWebTopBrowserCreated������
	* @param configs  ����������Ķ���
	*/
	void createBrowser(JWebTopConfigs* configs, JWebTopBrowserCreated* createListener);

	/**
	* ����JSON�����ַ���������������ɹ���ص�JWebTopBrowserCreated������
	* @param browerCfgJSON  JSON�����ַ���
	*/
	void createBrowserByJSON(wstring browerCfgJSON, JWebTopBrowserCreated* createListener);

	// �ر�ָ�������
	void closeBrowser(long browserHWnd);

	// �˳�JWebTop����
	void ExitJWebTop();

	// �رյ�ǰContext���е�FastIPC����ˡ��ͻ��ˣ��Լ����������
	void closeContext();

	/**
	* ����һ������ҳ��
	*
	* @param url
	*/
	void setErrorUrl(wstring url) {
		_write(JWM_SET_ERR_URL, 0, url);
	};

	bool isStable() {
		return server != NULL && server->isStable();
	};

	void setUrl(long browserHWnd, wstring url) {
		_write(JWM_M_SETURL, browserHWnd,  url);
	};

	void setAppendJS(long browserHWnd, wstring js) {
		_write(JWM_M_APPEND_JS, browserHWnd, js);
	};

	/**
	* ִ��js�����ͺ�ȴ����ݵķ��ء�<br/>
	* ���﷢���ǰ�װ��JSON���ݣ������JS�ű��е�invokeByDLL(jsonvalue)����
	*
	* @param browserHWnd
	*            ���ĸ������ִ��
	* @param jsonstring
	*            ��ִ�е�JSON����
	* @param jsReturn
	*            JSִ�н����������
	* @param uuid
	*            ִ��jsʱ���ڻ�ȡ���ؽ�������jsReturn�ǹ��õģ���ô���Ը��ݴ�uuid�����ֲ�ͬ�ĵ���
	*/
	void executeJSON_Wait(long browserHWnd, wstring jsonstring, JWebTopJSReturn* jsReturn, wstring uuid) {
		wstring taskId = (uuid.length() == 0) ? createTaskId() : uuid;
		jsReturnListners.insert(pair<wstring, JWebTopJSReturn* >(taskId, jsReturn));
		_write(JWM_JSON_EXECUTE_WAIT, browserHWnd, taskId, jsonstring);
	};

	/**
	* ִ��js�������ȴ����ݵķ��ء�<br/>
	* ���﷢���ǰ�װ��JSON���ݣ������JS�ű��е�invokeByDLL(jsonvalue)����
	*
	* @param jsonstring
	*/
	void executeJSON_NoWait(long browserHWnd, wstring jsonstring) {
		_write(JWM_JSON_EXECUTE_RETURN, browserHWnd,  jsonstring);
	};

	/**
	* ִ��js�����ȴ����ݵķ��ء�<br/>
	* �Ƽ�ʹ��executeJSON_Wait�������Լ����ַ���ת��������
	*
	* @param browserHWnd
	*            ���ĸ������ִ��
	* @param script
	*            ��ִ�е�JS�ű�
	* @param jsReturn
	*            JSִ�н����������
	* @param uuid
	*            ִ��jsʱ���ڻ�ȡ���ؽ�������jsReturn�ǹ��õģ���ô���Ը��ݴ�uuid�����ֲ�ͬ�ĵ���
	*/
	void executeJS_Wait(long browserHWnd, wstring script, JWebTopJSReturn* jsReturn, wstring uuid) {
		wstring taskId = (uuid.length() == 0) ? createTaskId() : uuid;
		jsReturnListners.insert(pair<wstring, JWebTopJSReturn* >(taskId, jsReturn));
		_write(JWM_JS_EXECUTE_WAIT, browserHWnd, taskId, script);
	};

	/**
	* ִ��js�������ȴ����ݵķ��ء� <br/>
	* �Ƽ�ʹ��executeJSON_NoWait�������Լ����ַ���ת��������
	*
	* @param script
	* @return
	*/
	void executeJS_NoWait(long browserHWnd, wstring script) {
		_write(JWM_JS_EXECUTE_RETURN, browserHWnd, script);
	};

	wstring getServerName(){ return this->serverName; };
	void setServerName(wstring serverName) { this->serverName = serverName; };
	int getBlockSize() { return blockSize; };
	void setBlockSize(int blockSize) { this->blockSize = blockSize; };
	JWebtopJSONDispater* getJsonHandler(){ return this->jsonHandler; };
	void setJsonHandler(JWebtopJSONDispater* jsonHandler) { this->jsonHandler = jsonHandler; };
};
#endif