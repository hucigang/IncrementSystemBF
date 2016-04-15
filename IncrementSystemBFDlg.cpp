// IncrementSystemBFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IncrementSystemBF.h"
#include "IncrementSystemBFDlg.h"
#include "LogFile.h"
#include "DHTMLEventSink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFDlg dialog

CIncrementSystemBFDlg::CIncrementSystemBFDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIncrementSystemBFDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIncrementSystemBFDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIncrementSystemBFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIncrementSystemBFDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_MyIE);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIncrementSystemBFDlg, CDialog)
	//{{AFX_MSG_MAP(CIncrementSystemBFDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MYMESSAGE, OnMyMessage)
	ON_MESSAGE(WM_MYCLIPMESSAGE, OnMyClipMessage)
	ON_MESSAGE(WM_MYCLICKMESSAGE, OnMyClickMessage)
	ON_WM_DESTROY()
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString szCharUrl;
CString szCharUrlTest;
CString log;
char telPhone[12] = {0};
int telPos = 0;


typedef BOOL (CALLBACK *LOADHOOK)();
typedef BOOL (CALLBACK *UNLOADHOOK)();

HINSTANCE hDLL=NULL;
LOADHOOK loadhook;
UNLOADHOOK unloadhook;
HWND m_hView;
bool bRun;
int PaintTime=0;;
struct scale
{
double xs1;
double ys1;
double xs2;
double ys2;
};
scale s[100];
int i=0;
int WindowWidth;
int WindwoHeight;
int xOffset;
int yOffset;

BOOL CALLBACK EnumWindowsProc( 
HWND hwnd, // handle to parent window 
LPARAM lParam // application-defined value 
) 
{ 
	CLogFile::WriteLog("EnumWindowsProc");
	CRect rc;
	::GetWindowRect(hwnd,&rc);
	rc.left -= xOffset;
	rc.right -= xOffset;
	rc.top -= yOffset;
	rc.bottom -= yOffset;
	s[i].xs1=(double)rc.left/(double)WindowWidth;
	s[i].ys1=(double)rc.top/(double)WindwoHeight;
	s[i].xs2=(double)rc.Width()/(double)WindowWidth;
	s[i].ys2=(double)rc.Height()/(double)WindwoHeight;
	i++;
	return TRUE; 
} 

BOOL CALLBACK SetWindowRectProc( 
HWND hwnd, // handle to parent window 
long lParam // application-defined value 
) 
{ 
	CHAR szClassName[500];
	GetClassName(hwnd, szClassName, 500);

	//CString logTemp;
	//logTemp.Format(" SetWindowRectProc [%s]", szClassName);
	//CLogFile::WriteLog(logTemp);
	CRect rc;
	rc.left=WindowWidth*s[i].xs1;
	rc.top=WindwoHeight*s[i].ys1;
	rc.right=WindowWidth*s[i].xs1+WindowWidth*s[i].xs2;
	rc.bottom=WindwoHeight*s[i].ys1+WindwoHeight*s[i].ys2;
	//::MoveWindow(hwnd,rc.left,rc.top,rc.Width(),rc.Height(),1);
	::MoveWindow(hwnd,0,0,cSystem.Width,cSystem.Height,1);
	i++;
	return TRUE; 
} 

LRESULT CIncrementSystemBFDlg::OnMyClickMessage(WPARAM wParam, LPARAM lParam)
{
	
	CComDispatchDriver spScript;
	IDispatch * pDocDisp = NULL;
   
   // get the DOM
   IHTMLDocument2  *pDoc=NULL;
   pDocDisp = m_MyIE.GetDocument(); 
   
   if (pDocDisp != NULL) 
   {
      // Obtained the document object by specifying the IHTMLDocument2 Interface.
		HRESULT hr= pDocDisp->QueryInterface( IID_IHTMLDocument2, (void**)&pDoc );
		
		pDoc->get_Script(&spScript);

		CComVariant var1 = 10, var2 = 20, varRet;  
		spScript.Invoke2(L"Add", &var1, &var2, &varRet); 

		CComDispatchDriver spData = varRet.pdispVal; 
		CComVariant varValue1, varValue2, varValue3;  
		spData.GetPropertyByName(L"result", &varValue1);  
		spData.GetPropertyByName(L"str", &varValue2); 
		spData.GetPropertyByName(L"str1", &varValue3); 

		CString strResult = _com_util::ConvertBSTRToString((_bstr_t)varValue3);

		szCharUrlTest.Format("Test %s", strResult);
		CLogFile::WriteLog(szCharUrlTest);
		//szCharUrl.Format("http://www.baidu.com/s?wd=%s", strResult);
		//szCharUrl.Format("http://132.90.101.25:7001/portal");
		szCharUrl.Format("http://132.77.51.11:7700/salemanm/salemanm?service=page/silverservice.silverJobExec.goldUnfinishedFrame&listener=initFrame&PROVINCEID=0011&STAFF_ID=yujp21&PASSWORD=H3B5VVJk0JFroCYwhWHbA9C8yes=&LOGIN_TYPE=KFSYS&inModeCode=1&cond_CONFIG=job&cond_FLAG=all&closeNavMethod=close&JOB_STATUS=1&VALID_FLAG=1&EPARCHY_CODE=0010&SERVER_NUMBER=18612452378");
		
		m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);
   }
   	PostMessage(WM_SIZE,0,0);
   return 1;
}

LRESULT CIncrementSystemBFDlg::OnMyClipMessage(WPARAM wParam, LPARAM lParam)
{
	char *str;
	str = (char *)lParam;
	CString tempStr(str);
	szCharUrl.Format("http://www.baidu.com/s?wd=%s", tempStr.Left(11));
	CLogFile::WriteLog(szCharUrl);
	
	m_MyIE.Navigate("Y:\\Downloads\\TelEscrowTest.htm", NULL, NULL, NULL, NULL);
	//m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);

	//m_MyIE.GetDocument();
	return 1;
}

LRESULT CIncrementSystemBFDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
		// lParam&0x800000，如果结果是1，表示是被释放的，也就是抬起的。

	if ( !(lParam & 0X80000000)) {

		if ((wParam >= 0x30 && wParam <= 0x39)
		||(wParam >= 0x60 && wParam <= 0x69)){
			if (telPos == 0){
				memset(&telPhone, 1, sizeof(telPhone) );
			}
			CString tempCode;
			tempCode.Format("%c", wParam);
			//log.Format("%d [%s]%c -- [%s]%p", telPos, cc, wParam, telPhone, telPhone);
			//CLogFile::WriteLog(log);
			memcpy(&telPhone[telPos], tempCode, 1);
			telPos++;
		}

		if (wParam == 0x8){
			CLogFile::WriteLog("Enter Back");
				
			telPos--;
		}
		if (wParam == 0x2E){
			CLogFile::WriteLog("Enter Del");
			telPos = 0;
		}
		
	}	

	if (telPos >= 11){
		telPos = 0;
		telPhone[12] = '\0';
			
		log.Format("look : [%s]%p",  telPhone, telPhone);
		CLogFile::WriteLog(log); 

		//15811043447szCharUrl.Format("http://www.baidu.com/s?wd=%s", telPhone);
		
		log.Format("szCharUrl %s", szCharUrl);
		CLogFile::WriteLog(log);
		m_MyIE.Navigate("Y:\\Downloads\\TelEscrowTest.htm", NULL, NULL, NULL, NULL);
		//m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);
	}
	return 1;
}


/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFDlg message handlers

BOOL CIncrementSystemBFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
  

	bRun = true;
	//PostMessage(WM_SIZE,0,0);
	SetWindowText(cSystem.Title);
	SetWindowPos(&wndTopMost, 0, 0, cSystem.Width, cSystem.Height, SWP_NOMOVE|SWP_SHOWWINDOW);
	CenterWindow();
	
	//::RegisterHotKey(m_hWnd, WM_USER,MOD_ALT, VK_F4);
	// TODO: Add extra initialization here
	m_hView = SetClipboardViewer();
	hDLL=::LoadLibrary(_T("TelEscrowBJ.dll"));       //加载DLL

	if (hDLL!=NULL){
		loadhook=(LOADHOOK)::GetProcAddress (hDLL,"EnableKeyboardCapture");
		unloadhook=(UNLOADHOOK)::GetProcAddress (hDLL,"DisableKeyboardCapture");
	}
	loadhook();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIncrementSystemBFDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIncrementSystemBFDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIncrementSystemBFDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	ChangeClipboardChain(m_hView);
}

void CIncrementSystemBFDlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter) 
{
	CDialog::OnChangeCbChain(hWndRemove, hWndAfter);
	
	// TODO: Add your message handler code here
	if ((HWND)hWndRemove == m_hView){
		m_hView = hWndAfter;
	}
}

void CIncrementSystemBFDlg::OnDrawClipboard() 
{
	CDialog::OnDrawClipboard();
	
	// TODO: Add your message handler code here
	CString sText;
	HGLOBAL hMem;
	LPTSTR lpStr;
	UINT nFormats[] = {CF_BITMAP,CF_DSPBITMAP,CF_TEXT};
	int nFormat = GetPriorityClipboardFormat(nFormats, sizeof(nFormats));
	switch (nFormat){
	case CF_TEXT:
		OpenClipboard();
		hMem = GetClipboardData(CF_TEXT);
		lpStr = (LPTSTR)GlobalLock(hMem);
		CLogFile::WriteLog(lpStr);

		PostMessage(WM_MYCLIPMESSAGE, 0, (LPARAM)lpStr);

		GlobalUnlock(hMem);
		CloseClipboard();
		break;
	}

}


//#include <mshtml.h>
//#include   <Mshtmdid.h>
// {E950DCE1-AF79-49c5-8D55-68F5C63E8D5A}3050f60f-98b5-11cf-bb82-00aa00bdce0b

#include "MyEventSink.h"
#include <comdef.h>
static const GUID DIID_HTMLElementEvents2 = 
{ 0x3050f60f, 0x98b5, 0x11cf, { 0xbb, 0x82, 0x00, 0xaa, 0x00, 0xbd, 0xce, 0x0b } };
static const GUID DIID_HTMLinputTextElementEvents2 = 
//{ 0xb6f9c783, 0x34d3, 0x4139, { 0xa6, 0x62, 0x7e, 0x44, 0xe4, 0x34, 0xb7, 0xb2} };
{ 0x3050f618, 0x98b5, 0x11cf, { 0xbb, 0x82, 0x00, 0xaa, 0x00, 0xbd, 0xce, 0x0b } };
//{ 0x3050F1C5, 0x98b5, 0x11cf, { 0xbb, 0x82, 0x0, 0xaa, 0x0, 0xbd, 0xce, 0x0b } };

void CIncrementSystemBFDlg::ConnectButton1(IHTMLElement *pButtonElem)
{
	HRESULT hr = 0; 
	IConnectionPointContainer* pCPC = NULL; 
	IConnectionPoint* pCP = NULL; 
	IUnknown* pUnk = NULL; 
	DWORD dwCookie; 
	// Check that this is a connectable object. 
	hr = pButtonElem->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC); 
	if (hr == S_OK) 
	{ 
		//AfxMessageBox("ConnectionPointContainer"); 
		// Find the connection point. 
		IEnumConnectionPoints *ppEnum=NULL;
		hr=pCPC->EnumConnectionPoints(&ppEnum);

	//	ppEnum->Next()
	//	if( hr == S_OK)
		{
			//ppEnum->Next()
		}
		hr = pCPC->FindConnectionPoint(DIID_HTMLinputTextElementEvents2/*DIID_HTMLButtonElementEvents2*/, &pCP); 
	//	hr = pCPC->FindConnectionPoint(__uuidof(IID_HTMLElementEvents2)/*DIID_HTMLButtonElementEvents2*/, &pCP); 
		if   ( SUCCEEDED(hr)) 
		{                         
			//AfxMessageBox( "Find   connection   point   "); 
			//   Advise   the   connection   point. 
			//   pUnk   is   the   IUnknown   interface   pointer   for   your   event   sink 
			
			//CDHTMLEventSink*   pSink   =   new CDHTMLEventSink;// CMyEventSink;// ;   
			//pSink->SetParent(this); 
			//IUnknown*   pUnk   = pSink->GetInterface(&IID_IUnknown);
			
			CMyEventSink* pSink = new CMyEventSink;
			hr   =   pCP->Advise(pSink,   &dwCookie); 
			pCP->Release(); 
		} 
		pCPC->Release(); 
	} 

	
}

BEGIN_EVENTSINK_MAP(CIncrementSystemBFDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CIncrementSystemBFDlg)
	ON_EVENT(CIncrementSystemBFDlg, IDC_EXPLORER1, 259 /* DocumentComplete */, OnDocumentCompleteExplorer1, VTS_DISPATCH VTS_PVARIANT)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CIncrementSystemBFDlg::ProcessElementCollection(IHTMLElementCollection* pElemColl, CString id)
{	
	IDispatch* pElemDisp = NULL;
	IHTMLElement* pElem = NULL;
	VARIANT vID;
	VARIANT vIdx;

	VariantInit(&vID);
	vID.vt=VT_BSTR;
	vID.bstrVal=_bstr_t(id);

	VariantInit(&vIdx);
			  
	vIdx.vt=VT_I4;
	vIdx.lVal=0;

	HRESULT hr = pElemColl->item( vID, vIdx, &pElemDisp );
	if ( SUCCEEDED(hr) && pElemDisp != 0x0)
	{
		hr = pElemDisp->QueryInterface( IID_IHTMLElement, (void**)&pElem );
		if ( SUCCEEDED(hr) )
		{
			// Obtained element with ID of "myID".
			BSTR bsHtml;
			pElem->get_outerHTML(&bsHtml);
			CLogFile::WriteLog(bsHtml);

			ConnectButton1( pElem );
			pElem->Release();	
		}
		pElemDisp->Release();
	}
	pElemColl->Release();
}

void CIncrementSystemBFDlg::OnDocumentCompleteExplorer1(LPDISPATCH pDisp, VARIANT FAR* URL) 
{
	// TODO: Add your control notification handler code here
	IDispatch * pDocDisp = NULL;
   
	// get the DOM
	IHTMLDocument2  *pDoc=NULL;
	pDocDisp = m_MyIE.GetDocument(); 
   
	if (pDocDisp != NULL) 
	{
      // Obtained the document object by specifying the IHTMLDocument2 Interface.
		HRESULT hr= pDocDisp->QueryInterface( IID_IHTMLDocument2, (void**)&pDoc );
		
		IHTMLElement* pBody = NULL;
		BSTR bstrBody;
		pDoc->get_body(&pBody);

		pBody->get_innerHTML(&bstrBody);

		if ( SUCCEEDED(hr) )
		{
			// Obtained the IHTMLDocument2 interface for the document object
			IHTMLElementCollection* pElemColl = NULL;
			hr = pDoc->get_all( &pElemColl );
			if ( SUCCEEDED(hr) )//ec
			{
				CComDispatchDriver spScript; 
				pDoc->get_Script(&spScript);  
				CComVariant var(static_cast<IDispatch*>(new CMyEventSink));  
				spScript.Invoke1(L"SaveCppObject", &var); 
				// Obtained element collection.
				/*
#define LOGON_HTML_ID _T("Logon")
#define HTTP1_HTML_ID _T("Http1")
#define AUTH_HTML_ID _T("Authentication")
#define QUERYPT_HTML_ID _T("QueryPhoneType")
#define QUERYPOP_HTML_ID _T("QueryPopup")
#define QUERYPHONE_HTML_ID _T("QueryPhone")
#define HB_HTML_ID _T("Heartbeat")
#define RESETPWD_HTML_ID _T("ResetPassword")
#define LOGOFF_HTML_ID _T("Logoff")
				*/
				ProcessElementCollection( pElemColl, "myid");
				ProcessElementCollection( pElemColl, LOGON_HTML_ID);
			}
		}
		//ProcessDocument( pDocDisp );
	}
	pDocDisp->Release();
}

void CIncrementSystemBFDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	isActive=nState;
}

BOOL CIncrementSystemBFDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
	if (isActive && WM_SYSKEYDOWN == pMsg->message
// WM_SYSKEYDOWN  表示ALT键按下
		&& VK_F4 == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CIncrementSystemBFDlg::OnSize(UINT nType, int cx, int cy) 
{
	if(bRun){
		if(PaintTime == 0){
			PaintTime++;
			i=0;
			CRect rc1;
			GetClientRect(&rc1);
			WindowWidth=rc1.Width();
			WindwoHeight=rc1.Height();
			CRect rc2=rc1;
			ClientToScreen(&rc2);
			xOffset=rc2.left-rc1.left;
			yOffset=rc2.top-rc1.top;
			EnumChildWindows(this->GetSafeHwnd(),EnumWindowsProc,0); 
			ShowWindow(SW_NORMAL);
		}else{
			CRect rc1;
			GetClientRect(&rc1);
			WindowWidth=rc1.Width();
			WindwoHeight=rc1.Height();
			ClientToScreen(&rc1);
			i=0;
			EnumChildWindows(this->GetSafeHwnd(),SetWindowRectProc,0); 
		}
	}

	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
}
