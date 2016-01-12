#ifndef jwebtop_multi_process_jwebtop_msg_H_
#define jwebtop_multi_process_jwebtop_msg_H_

#define __JWM        100    // ����һ����Ϣ��ʼֵ

#define JWM_IPC_CLIENT_OK		(__JWM+101)  // IPC��Ӧ�Ŀͻ����ѳɹ�����
#define JWM_SET_ERR_URL			(__JWM+102)  // ���ô���ҳ��

#define JWM_STARTJWEBTOP		(__JWM+301)  // ����JWebTop����
#define JWM_CFGJWEBTOP_FILE		(__JWM+302)  // 
//#define JWM_CFGJWEBTOP_JSON		(__JWM+303)  // 
#define JWM_CEF_APP_INITED		(__JWM+304)  // CEF������ѳ�ʼ���
#define JWM_CEF_ExitAPP			(__JWM+305)  // �ر�CEF���������

#define JWM_CREATEBROWSER_JSON	(__JWM+401)  // �������������Ϣ		��ͬ�����ͣ�
#define JWM_CREATEBROWSER_FILE	(__JWM+402)  // �������������Ϣ		��ͬ�����ͣ�
#define JWM_BROWSER_CREATED		(__JWM+403)  // CEF������ѳ�ʼ���
#define JWM_CLOSEBROWSER		(__JWM+404)  // �ر����������Ϣ		���첽���ͣ�

#define JWM_JS_EXECUTE_WAIT		(__JWM+201)  // DLL����CEF�ˣ���Ҫִ�в��ȴ���JS���� 
#define JWM_JS_EXECUTE_RETURN	(__JWM+202)  // 
#define JWM_JSON_EXECUTE_WAIT	(__JWM+211)  // DLL����CEF�ˣ���Ҫִ�в��ȴ���JSON���� 
#define JWM_JSON_EXECUTE_RETURN	(__JWM+212)  // 
#define JWM_DLL_EXECUTE_WAIT	(__JWM+221)  // CEF����DLL�ˣ���Ҫִ�в��ȴ������� 
#define JWM_DLL_EXECUTE_RETURN	(__JWM+222)  // CEF����DLL�ˣ���Ҫִ�е�CEF����ȴ������� 
#define JWM_RESULT_RETURN	    (__JWM+231)  

#define JWM_M_SETURL			(__JWM+501)  // �����������URL��ͨ��JS��ʽ����ʱ�����ܻ���JS�������������⣩
#define JWM_M_APPEND_JS			(__JWM+502)  // Ϊ���������һЩJS���룬���ӵĴ�����ҳ���������������Ч

// B2R=Browser to Renderer
#define JWM_B2R_SERVERINFO		(__JWM+601)  // ��render���̷���FastIPC����˲���
#define JWM_B2R_TASKRESULT		(__JWM+602)  // ��render���̷���Զ������ִ�н��

#endif