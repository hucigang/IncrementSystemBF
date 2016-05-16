// IncrementSystemBFDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES

#if !defined(AFX_INCREMENTSYSTEMBFDLG_H__179C6FE2_F0FE_4EE1_AF6E_A076B6A6FB25__INCLUDED_)
#define AFX_INCREMENTSYSTEMBFDLG_H__179C6FE2_F0FE_4EE1_AF6E_A076B6A6FB25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#import "C:\windows\system32\mshtml.tlb" 

#include <comdef.h>
#include <map>
#include <vector>
#include <atlbase.h>
#include <atlcom.h>
#include <MsHTML.h>
#include "mshtml.h"
#include "mshtmdid.h"
#include "resource.h"
#include <afxwin.h>
using namespace std;

#pragma warning(disable : 4146) //see Q231931 for explaintation
#import <mshtml.tlb> no_auto_exclude

#define WM_MYMESSAGE         (WM_USER+100)
#define WM_MYCLIPMESSAGE         (WM_MYMESSAGE+1)
#define WM_MYCLICKMESSAGE	 (WM_MYMESSAGE+2)
#define WM_MYIEMESSAGE		 (WM_MYMESSAGE+3)


/////////////////////////////////////////////////////////////////////////////1860837383728
// CIncrementSystemBFDlg dialog

class CIncrementSystemBFDlg : public CDialog
{
// Construction
public:
	CIncrementSystemBFDlg(CWnd* pParent = NULL);	// standard constructor
	void ConnectButton1(IHTMLElement* pButtonElem);
// Dialog Data
	//{{AFX_DATA(CIncrementSystemBFDlg)
	enum { IDD = IDD_INCREMENTSYSTEMBF_DIALOG };
	CWebBrowser2	m_MyIE;
	UINT isActive;
	//}}AFX_DATA
	

	// ClassWizard generated virtual function overrides15811043447
	//{{AFX_VIRTUAL(CIncrementSystemBFDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual void ProcessElementCollection(IHTMLElementCollection* pElemColl, CString id);
	virtual void DocumentCompleteExplorerSelectItem(LPDISPATCH pDisp, VARIANT* URL);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIncrementSystemBFDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnMyMessage(WPARAM w, LPARAM l);
	afx_msg LRESULT OnMyClipMessage(WPARAM w, LPARAM l);
	afx_msg LRESULT OnMyClickMessage(WPARAM w, LPARAM l);
	afx_msg LRESULT OnMyIEMessage(WPARAM w, LPARAM l);
	afx_msg void OnDestroy();
	afx_msg void OnChangeCbChain(HWND hWndRemove, HWND hWndAfter);
	afx_msg void OnDrawClipboard();
	afx_msg void OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCREMENTSYSTEMBFDLG_H__179C6FE2_F0FE_4EE1_AF6E_A076B6A6FB25__INCLUDED_)
