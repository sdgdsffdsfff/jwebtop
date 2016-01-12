//////////////////////////////////////////////////////////////////////////  
/// ����fastipc�Ķ�Ӧ��jni��ط���
/// 
/// Դ�룺http://git.oschina.net/washheart/fastipc
/// Դ�룺https://github.com/washheart/fastipc
/// ˵����https://github.com/washheart/fastipc/wiki
/// @version	1.0 
/// @author		washheart@163.com
/// @date       2015-10-31  
////////////////////////////////////////////////////////////////////////// 
#include "jni_jdk1_6_24/jni.h"
//#include "jni_jdk1_6_24\jni_md.h"
//#include "jni_jdk1_6_24\jawt_md.h"

#ifndef _Included_org_fastipc_FastIPCNative
#define _Included_org_fastipc_FastIPCNative

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ��Ӧorg.fastipc.FastIPCNative���nCreateServer����
	* �÷������ڴ���һ��fastipc�����
	* serverName	���������
	* blockSize		�������ͻ���ͨ��ʱÿ�ε�������
	* return		����һ��int[2]���顣0=�Ƿ񴴽��ɹ���1=������Server��ָ��
	*/
	JNIEXPORT jintArray JNICALL Java_org_fastipc_FastIPCNative_nCreateServer
		(JNIEnv *, jclass, jstring serverName, jint blockSize);

	/*
	* ��Ӧorg.fastipc.FastIPCNative���nStartRead����
	* �÷������ڿ���fastipc����˵Ķ�ȡ�������ɹ���������ڴ˴�
	* nativeServer	ָ������ʵ����ָ��
	* listener		��Ӧ��ȡ������ָ��
	*/
	JNIEXPORT void JNICALL Java_org_fastipc_FastIPCNative_nStartRead
		(JNIEnv *, jclass, jint nativeServer, jobject listener);

	/*
	* ��Ӧorg.fastipc.FastIPCNative���nCloseServer����
	* �÷������ڹر�fastipc����ˣ�ִ�к�nStartRead��������ֹͣ
	* nativeServer	ָ������ʵ����ָ��
	*/
	JNIEXPORT void JNICALL Java_org_fastipc_FastIPCNative_nCloseServer
		(JNIEnv *, jclass, jint nativeServer);

	/*
	* ��Ӧorg.fastipc.FastIPCNative���nCreateClient����
	* �÷������ڴ���һ��fastipc�ͻ���
	* serverName	�ͻ��˶�Ӧ�ķ���˵�����
	* blockSize		�������ͻ���ͨ��ʱÿ�ε�������
	* return		����һ��int[2]���顣0=�Ƿ񴴽��ɹ���1=������Client��ָ��
	*/
	JNIEXPORT jintArray JNICALL Java_org_fastipc_FastIPCNative_nCreateClient
		(JNIEnv *, jclass, jstring serverName, jint blockSize);

	/*
	* ��Ӧorg.fastipc.FastIPCNative���nWriteClient����
	* �÷���������fastipc�ͻ���д�����ݣ�����д��ɺ󣬻ᴥ������˵�����
	* nativeClient	ָ��ͻ���ʵ����ָ��
	* data			Ҫд�������
	* return		�ɹ�д������ݳ���
	*/
	JNIEXPORT jint JNICALL Java_org_fastipc_FastIPCNative_nWriteClient
		(JNIEnv * env, jclass, jint nativeClient, jint userMsgType, jlong userValue, jstring userShortStr, jstring data);

	/*
	* ��Ӧorg.fastipc.FastIPCNative���nCloseClient����
	* �÷������ڹر�fastipc�ͻ���
	* nativeClient	ָ��ͻ���ʵ����ָ��
	*/
	JNIEXPORT void JNICALL Java_org_fastipc_FastIPCNative_nCloseClient
		(JNIEnv *, jclass, jint nativeClient);
#ifdef __cplusplus
}
#endif
#endif
