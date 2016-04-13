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
        //对的，我是一个IDispatch，把我自己(this)交给你  
        *ppvObject = static_cast<IDispatch*>(this);  
        return S_OK;  
    }  
    else  
        return E_NOINTERFACE; 
}

ULONG __stdcall CMyEventSink::AddRef(void)
{	return 1;	}	// 做个假的就可以，因为反正这个对象在程序结束前是不会退出的

ULONG __stdcall CMyEventSink::Release(void)
{	return 0;	}	// 做个假的就可以，因为反正这个对象在程序结束前是不会退出的

STDMETHODIMP CMyEventSink::GetTypeInfoCount(unsigned int *)
{	return E_NOTIMPL;	}	// 不用实现，反正也不用

STDMETHODIMP CMyEventSink::GetTypeInfo(unsigned int,unsigned long,struct ITypeInfo ** )
{	return E_NOTIMPL;	}	// 不用实现，反正也不用

//JavaScript调用这个对象的方法时，会把方法名，放到rgszNames中，我们需要给这个方法名拟定一个唯一的数字ID，用rgDispId传回给它  
//同理JavaScript存取这个对象的属性时，会把属性名放到rgszNames中，我们需要给这个属性名拟定一个唯一的数字ID，用rgDispId传回给它  
//紧接着JavaScript会调用Invoke，并把这个ID作为参数传递进来  
STDMETHODIMP CMyEventSink::GetIDsOfNames
(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
//(const struct _GUID &,unsigned short ** ,unsigned int,unsigned long,long *)
{	
	//rgszNames是个字符串数组，cNames指明这个数组中有几个字符串，如果不是1个字符串，忽略它  
    if (cNames != 1)  
        return E_NOTIMPL;  
    //如果字符串是ShowMessageBox，说明JavaScript在调用我这个对象的ShowMessageBox方法，我就把我拟定的ID通过rgDispId告诉它  
    if (wcscmp(rgszNames[0], L"ShowMessageBox") == 0)  
    {  
        *rgDispId = FUNCTION_ShowMessageBox;  
        return S_OK;  
    }  
    //同理，如果字符串是GetProcessID，说明JavaScript在调用我这个对象的GetProcessID方法  
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

//JavaScript通过GetIDsOfNames拿到我的对象的方法的ID后，会调用Invoke，dispIdMember就是刚才我告诉它的我自己拟定的ID  
//wFlags指明JavaScript对我的对象干了什么事情！  
//如果是DISPATCH_METHOD，说明JavaScript在调用这个对象的方法，比如cpp_object.ShowMessageBox();  
//如果是DISPATCH_PROPERTYGET，说明JavaScript在获取这个对象的属性，比如var n = cpp_object.num;  
//如果是DISPATCH_PROPERTYPUT，说明JavaScript在修改这个对象的属性，比如cpp_object.num = 10;  
//如果是DISPATCH_PROPERTYPUTREF，说明JavaScript在通过引用修改这个对象，具体我也不懂  
//示例代码并没有涉及到wFlags和对象属性的使用，需要的请自行研究，用法是一样的  
//pDispParams就是JavaScript调用我的对象的方法时传递进来的参数，里面有一个数组保存着所有参数  
//pDispParams->cArgs就是数组中有多少个参数  
//pDispParams->rgvarg就是保存着参数的数组，请使用[]下标来访问，每个参数都是VARIANT类型，可以保存各种类型的值  
//具体是什么类型用VARIANT::vt来判断，不多解释了，VARIANT这东西大家都懂  
//pVarResult就是我们给JavaScript的返回值  
//其它不用管  
STDMETHODIMP CMyEventSink::Invoke(
	DISPID dispIdMember, REFIID riid, LCID lcid,  
    WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{		// 只需要实现这个就足够啦
	
		DWORD aid = 0;
	switch(dispIdMember)	// 根据不同的dispID,完成不同的回调函数
	{
	case 1:
			// 这里就能接收到 COM 发出的事件啦
		break;
	case 2:
			// 事件的代号 dispID 其实就是 IDL 文件中的连接点函数的id(n)的号码
		break;
	case FUNCTION_ShowMessageBox:
		//检查是否只有一个参数  
		break;
	case FUNCTION_GetProcessID:
		aid = CMyEventSink::GetProcessID();

		VARIANT va;  
		va.vt=VT_I4;///指明整型数据  
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
    //MessageBox(msg, L"这是来自javascript的消息");
	
		//::PostMessage(m_pWnd->GetParent(), WM_MYCLICKMESSAGE, 0, 0);
}  