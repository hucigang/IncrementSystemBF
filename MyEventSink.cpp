// MyEventSink.cpp: implementation of the CMyEventSink class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IncrementSystemBF.h"
#include "MyEventSink.h"
#include "LogFile.h"
#include <comdef.h>

#include "IncrementSystemBFDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

enum  
{  
    FUNCTION_ShowMessageBox = 10,  
    FUNCTION_GetProcessID = 20,  
};  

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyEventSink::CMyEventSink()
{

}

CMyEventSink::~CMyEventSink()
{

}
STDMETHODIMP CMyEventSink::QueryInterface(const struct _GUID &iid,void ** ppvObject)
{
	if (iid == IID_IDispatch || iid == IID_IUnknown)  
    {  
        //�Եģ�����һ��IDispatch�������Լ�(this)������  
        *ppvObject = static_cast<IDispatch*>(this);  
        return S_OK;  
    }  
    else  
        return E_NOINTERFACE; 
}

ULONG __stdcall CMyEventSink::AddRef(void)
{	return 1;	}	// �����ٵľͿ��ԣ���Ϊ������������ڳ������ǰ�ǲ����˳���

ULONG __stdcall CMyEventSink::Release(void)
{	return 0;	}	// �����ٵľͿ��ԣ���Ϊ������������ڳ������ǰ�ǲ����˳���

STDMETHODIMP CMyEventSink::GetTypeInfoCount(unsigned int *)
{	return E_NOTIMPL;	}	// ����ʵ�֣�����Ҳ����

STDMETHODIMP CMyEventSink::GetTypeInfo(unsigned int,unsigned long,struct ITypeInfo ** )
{	return E_NOTIMPL;	}	// ����ʵ�֣�����Ҳ����

//JavaScript�����������ķ���ʱ����ѷ��������ŵ�rgszNames�У�������Ҫ������������ⶨһ��Ψһ������ID����rgDispId���ظ���  
//ͬ��JavaScript��ȡ������������ʱ������������ŵ�rgszNames�У�������Ҫ������������ⶨһ��Ψһ������ID����rgDispId���ظ���  
//������JavaScript�����Invoke���������ID��Ϊ�������ݽ���  
STDMETHODIMP CMyEventSink::GetIDsOfNames
(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
//(const struct _GUID &,unsigned short ** ,unsigned int,unsigned long,long *)
{	
	//rgszNames�Ǹ��ַ������飬cNamesָ������������м����ַ������������1���ַ�����������  
    if (cNames != 1)  
        return E_NOTIMPL;  
    //����ַ�����ShowMessageBox��˵��JavaScript�ڵ�������������ShowMessageBox�������ҾͰ����ⶨ��IDͨ��rgDispId������  
    if (wcscmp(rgszNames[0], L"ShowMessageBox") == 0)  
    {  
        *rgDispId = FUNCTION_ShowMessageBox;  
        return S_OK;  
    }  
    //ͬ������ַ�����GetProcessID��˵��JavaScript�ڵ�������������GetProcessID����  
    else if (wcscmp(rgszNames[0], L"GetProcessID") == 0)  
    {  
        *rgDispId = FUNCTION_GetProcessID;  
        return S_OK;  
    }  
    else  
        return E_NOTIMPL;  
}

#define DISPID_CLICK                    (-600)
#define DISPID_DBLCLICK                 (-601)
#define DISPID_KEYDOWN                  (-602)
#define DISPID_KEYPRESS                 (-603)
#define DISPID_KEYUP                    (-604)
#define DISPID_MOUSEDOWN                (-605)
#define DISPID_MOUSEMOVE                (-606)
#define DISPID_MOUSEUP                  (-607)
#define DISPID_ERROREVENT               (-608)
#define DISPID_READYSTATECHANGE         (-609)
#define DISPID_CLICK_VALUE              (-610)
#define DISPID_RIGHTTOLEFT              (-611)
#define DISPID_TOPTOBOTTOM              (-612)
#define DISPID_THIS                     (-613)

//JavaScriptͨ��GetIDsOfNames�õ��ҵĶ���ķ�����ID�󣬻����Invoke��dispIdMember���Ǹղ��Ҹ����������Լ��ⶨ��ID  
//wFlagsָ��JavaScript���ҵĶ������ʲô���飡  
//�����DISPATCH_METHOD��˵��JavaScript�ڵ����������ķ���������cpp_object.ShowMessageBox();  
//�����DISPATCH_PROPERTYGET��˵��JavaScript�ڻ�ȡ�����������ԣ�����var n = cpp_object.num;  
//�����DISPATCH_PROPERTYPUT��˵��JavaScript���޸������������ԣ�����cpp_object.num = 10;  
//�����DISPATCH_PROPERTYPUTREF��˵��JavaScript��ͨ�������޸�������󣬾�����Ҳ����  
//ʾ�����벢û���漰��wFlags�Ͷ������Ե�ʹ�ã���Ҫ���������о����÷���һ����  
//pDispParams����JavaScript�����ҵĶ���ķ���ʱ���ݽ����Ĳ�����������һ�����鱣�������в���  
//pDispParams->cArgs�����������ж��ٸ�����  
//pDispParams->rgvarg���Ǳ����Ų��������飬��ʹ��[]�±������ʣ�ÿ����������VARIANT���ͣ����Ա���������͵�ֵ  
//������ʲô������VARIANT::vt���жϣ���������ˣ�VARIANT�ⶫ����Ҷ���  
//pVarResult�������Ǹ�JavaScript�ķ���ֵ  
//�������ù�  
STDMETHODIMP CMyEventSink::Invoke(
	DISPID dispIdMember, REFIID riid, LCID lcid,  
    WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{		// ֻ��Ҫʵ��������㹻��
	
		DWORD aid = 0;
	switch(dispIdMember)	// ���ݲ�ͬ��dispID,��ɲ�ͬ�Ļص�����
	{
	case 1:
			// ������ܽ��յ� COM �������¼���
		break;
	case 2:
			// �¼��Ĵ��� dispID ��ʵ���� IDL �ļ��е����ӵ㺯����id(n)�ĺ���
		break;
	case FUNCTION_ShowMessageBox:
		//����Ƿ�ֻ��һ������  
		break;
	case FUNCTION_GetProcessID:
		aid = CMyEventSink::GetProcessID();

		VARIANT va;  
		va.vt=VT_I4;///ָ����������  
		va.lVal=aid;
        *pVarResult = va; 
		break;
	case DISPID_CLICK:
		AfxMessageBox("click event");
		HWND h_Wnd;
		h_Wnd = FindWindow(NULL, "IncrementSystemBF");
		::PostMessage(h_Wnd, WM_MYCLICKMESSAGE, 0, 0);
		break;
	default:
		break;
	}
	return S_OK;
}


DWORD CMyEventSink::GetProcessID()  
{  
		HWND h_Wnd;
		h_Wnd = FindWindow(NULL, "IncrementSystemBF");
		DWORD dwPID;
		DWORD dwThreadID = ::GetWindowThreadProcessId(h_Wnd, &dwPID);
		return dwPID;
}  
  
void CMyEventSink::ShowMessageBox(const wchar_t *msg)  
{  
    //MessageBox(msg, L"��������javascript����Ϣ");
	
		//::PostMessage(m_pWnd->GetParent(), WM_MYCLICKMESSAGE, 0, 0);
}  