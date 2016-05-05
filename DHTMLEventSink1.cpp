// DHTMLEventSink1.cpp : implementation file
//

#include "stdafx.h"
#include "IncrementSystemBF.h"
#include "DHTMLEventSink1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDHTMLEventSink

IMPLEMENT_DYNCREATE(CDHTMLEventSink, CCmdTarget)

CDHTMLEventSink::CDHTMLEventSink()
{
	EnableAutomation();
}

CDHTMLEventSink::~CDHTMLEventSink()
{
}


void CDHTMLEventSink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CDHTMLEventSink, CCmdTarget)
	//{{AFX_MSG_MAP(CDHTMLEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define DISPID_CLICK                    (-600)
BEGIN_DISPATCH_MAP(CDHTMLEventSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CDHTMLEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	DISP_FUNCTION_ID(CDHTMLEventSink,"onclick",DISPID_CLICK,Invoke,VT_EMPTY, VTS_DISPATCH)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IDHTMLEventSink to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {A32BD542-7B67-4600-AA03-D98E9E5A1BF9}
static const IID IID_IDHTMLEventSink =
{ 0xB6F9C783, 0x34D3, 0x4139, { 0xA6, 0x62, 0x7e, 0x44, 0xe4, 0x34, 0xb7, 0xb2} };
//{ 0xa32bd542, 0x7b67, 0x4600, { 0xaa, 0x3, 0xd9, 0x8e, 0x9e, 0x5a, 0x1b, 0xf9 } };

BEGIN_INTERFACE_MAP(CDHTMLEventSink, CCmdTarget)
	INTERFACE_PART(CDHTMLEventSink, IID_IDHTMLEventSink, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDHTMLEventSink message handlers
STDMETHODIMP CDHTMLEventSink::Invoke(
            DISPID dispidMember,
            REFIID riid,
            LCID lcid,
            WORD wFlags,
            DISPPARAMS* pdispparams,
            VARIANT* pvarResult,
            EXCEPINFO* pexcepinfo,
            UINT* puArgErr)
{
	
		AfxMessageBox("ok");
	AfxMessageBox(dispidMember);
    switch ( dispidMember )
    {
		 //case DISPID_HTMLELEMENTEVENTS2_ONCLICK:
	//     OnClick();
		//	AfxMessageBox("ok");
        //break;

    default:
        break;
    }
    return S_OK;
}

void CDHTMLEventSink::OnClick(DISPID pEvtObj)
{
  // 鼠标点击处理代码...详见下节
	AfxMessageBox("onc  lick");
}

