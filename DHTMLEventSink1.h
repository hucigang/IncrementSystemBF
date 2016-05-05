#if !defined(AFX_DHTMLEVENTSINK_H__A8CB5883_B706_43B5_85EE_A7652AC4AF6B__INCLUDED_)
#define AFX_DHTMLEVENTSINK_H__A8CB5883_B706_43B5_85EE_A7652AC4AF6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DHTMLEventSink1.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDHTMLEventSink command target

class CDHTMLEventSink : public CCmdTarget
{
	DECLARE_DYNCREATE(CDHTMLEventSink)

	CDHTMLEventSink();           // protected constructor used by dynamic creation

// Attributes
public:

	CWnd*   m_pWnd;
// Operations
public:
//void OnBDblClick(IHTMLEventObj *pEvtObj); 
//CWnd* m_pWnd; 
	void SetParent(CWnd* objWnd){
		m_pWnd = objWnd;
	}

	STDMETHOD(Invoke)(DISPID dispIdMember, REFIID, LCID, WORD, DISPPARAMS* pDisp, VARIANT* test, EXCEPINFO *, UINT *); 
	void OnClick(DISPID pEvtObj);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDHTMLEventSink)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDHTMLEventSink();

	// Generated message map functions
	//{{AFX_MSG(CDHTMLEventSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDHTMLEventSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DHTMLEVENTSINK_H__A8CB5883_B706_43B5_85EE_A7652AC4AF6B__INCLUDED_)
