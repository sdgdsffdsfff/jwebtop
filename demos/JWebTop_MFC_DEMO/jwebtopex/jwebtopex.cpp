#include "jwebtopex.h"
#include "include/cef_parser.h"

//JWebTopEx::JWebTopEx()
//{
//}


//namespace jw{
//bool parseMessageJSON(wstring jsonString, long &hWnd, wstring &taskId, wstring &parsedJsonString){
//	CefRefPtr<CefValue> v = CefParseJSON(CefString(jsonString), JSON_PARSER_RFC);  // ���н���
//	if (v == NULL)return false;
//	CefRefPtr<CefDictionaryValue> value = v->GetDictionary();// ��JSON�ֵ�����ȡ
//	taskId = value->GetString("taskId").ToWString();  // ȡ��ĳ�ַ��� 
//	hWnd = value->GetInt("hWnd");
//	parsedJsonString = value->GetString("jo").ToWString();
//	return true;
//}

//wstring wrapAsTaskJSON(long hWnd, wstring &taskId, wstring &someJsonString){
//	CefRefPtr<CefDictionaryValue> value = CefDictionaryValue::Create();
//	if (taskId.size() > 0)value->SetString(CefString("taskId"), CefString(taskId));
//	value->SetInt(CefString("hWnd"), hWnd);
//	value->SetString(CefString("jo"), CefString(someJsonString));
//	CefRefPtr<CefValue> node = CefValue::Create();
//	node->SetDictionary(value);
//	CefString result = CefWriteJSON(node, JSON_WRITER_DEFAULT);
//	return result.ToWString();
//}
//}