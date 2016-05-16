// IncrementSystemBFDlg.cpp : implementation file
//
#pragma warning(disable: 4786)
#include "stdafx.h"
#include "IncrementSystemBF.h"
#include "IncrementSystemBFDlg.h"
#include "LogFile.h"
#include "DHTMLEventSink.h"
#include <Wininet.h>  
#include <atlbase.h>
#include <atlcom.h>

#include <vector>
#include <algorithm>
#include <iostream>
              
#pragma comment(lib, "Wininet.lib")  

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
	ON_MESSAGE(WM_MYIEMESSAGE, OnMyIEMessage)
	ON_WM_DESTROY()
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_COPYDATA()
	ON_WM_MENUSELECT()
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

CTime timeStart;
CTime timeNow;

BOOL HttpRequestGet(IN const CString& sHomeUrl, IN const LONG nPort, IN const CString& sPageUrl, OUT CString &sResult)  
{   
    HINTERNET hInternet;  
    DWORD nGetSize;  
    LPSTR lpszData = NULL;  
    DWORD dwSize = 0;  
    DWORD dwDownloaded = 0;  
	/*
   User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko*/
    hInternet = InternetOpen(_T("User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; rv:11.0) like Gecko"),  
        INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);  
    if (NULL == hInternet)  
    {  
        sResult.Format(_T("Open link error. ErrCode=[%u]"), GetLastError());  
        InternetCloseHandle(hInternet);  
        return FALSE;  
    }  
    // 打开http session     
    HINTERNET hSession = InternetConnect(hInternet, sHomeUrl,  
        (INTERNET_PORT)nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);  
  
    CString sHtmlHeader; 
	
	
	/*
   Accept: text/html, application/xhtml+xml, image/jxr, *\/*
   Accept-Encoding: gzip, deflate
   Accept-Language: zh-Hans-CN, zh-Hans; q=0.5
   
   Connection: Keep-Alive
   Host: 132.77.220.134:8081
	*/
    sHtmlHeader = _T("Accept: text/html, application/xhtml+xml, image/jxr, */*\r\n");  
    sHtmlHeader += _T("Accept-Encoding: gzip, deflate\r\n");  
    sHtmlHeader += _T("Accept-Language: zh-Hans-CN, zh-Hans; q=0.5\r\n");  
	sHtmlHeader += _T("Connection: Keep-Alive\r\n");
	CString sHeadConnection;
	sHeadConnection.Format(_T("Host: %s:%ld"), sHomeUrl, nPort);
	sHtmlHeader += sHeadConnection;
  
    DWORD pszResponse = 1024*1024; //1M
	auto_ptr<char> szBuf(new char[pszResponse]);
	memset(szBuf.get(),0,pszResponse);
  
    HINTERNET hRequest = HttpOpenRequest(hSession, _T("GET"), sPageUrl,  
        _T("HTTP/1.0"), _T(""), 0, INTERNET_FLAG_NO_AUTH |  
        INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_NO_CACHE_WRITE, 0);  
  
    int iTimeout = 10000;  
    InternetSetOption(hRequest, INTERNET_OPTION_CONNECT_TIMEOUT,  
        &iTimeout, sizeof(iTimeout));  
    InternetSetOption(hRequest, INTERNET_OPTION_SEND_TIMEOUT,  
        &iTimeout, sizeof(iTimeout));  
    InternetSetOption(hRequest, INTERNET_OPTION_RECEIVE_TIMEOUT,  
        &iTimeout, sizeof(iTimeout));  
    InternetSetOption(hRequest, INTERNET_OPTION_DATA_SEND_TIMEOUT,  
        &iTimeout, sizeof(iTimeout));  
    InternetSetOption(hRequest, INTERNET_OPTION_DATA_RECEIVE_TIMEOUT,  
        &iTimeout, sizeof(iTimeout));  
    InternetSetOption(hRequest, INTERNET_OPTION_LISTEN_TIMEOUT,  
        &iTimeout, sizeof(iTimeout));  
  
    BOOL bResult = HttpSendRequest(hRequest, sHtmlHeader,  
        sHtmlHeader.GetLength(), _T(""), 0);  
    sHtmlHeader.ReleaseBuffer();  
  
    if (FALSE == bResult)  
    {  
        sResult.Format(_T("Send request error. ErrCode=[%u]"), GetLastError());  
  
        InternetCloseHandle(hRequest);  
        InternetCloseHandle(hSession);  
        InternetCloseHandle(hInternet);  
  
        //delete[]pszResponse;  
  
        return FALSE;  
    }  
  
    nGetSize = 0;  
    // 循环读取数据      
    do  
    { // 检查在http response 还有多少字节可以读取   18693837493 
        if (!InternetQueryDataAvailable(hRequest, &dwSize, 0, 0))  
        {  
            break;  
        }  
        // 读取数据    
        //if (FALSE == InternetReadFile(hRequest,  
         //   (LPVOID)&pszResponse[nGetSize], dwSize, &dwDownloaded))  
		if (FALSE == InternetReadFile(hRequest,  
           szBuf.get(), dwSize, &dwDownloaded))  
        {  
           
        }  else{
			 nGetSize += dwSize;  
            if (dwDownloaded == 0 || nGetSize > 1024 * 1024)  
            {// 没有剩余数据    
                break;  
            }  
		}
    } while (FALSE);  
  
    //pszResponse[nGetSize] = 0;  
	sResult.Format("%s", szBuf.get());
    //sResult = ::CA2T(pszResponse);  
  
    InternetCloseHandle(hRequest);  
    InternetCloseHandle(hSession);  
    InternetCloseHandle(hInternet);  
  
	szBuf.release();
//    delete[]pszResponse;  
  

    if (sResult.Find(_T("<html>")) != -1)  
    {  
        sResult = _T("An unknown error occurred.");  
        return FALSE;  
    }  
  
    return TRUE;  
}  


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

BOOL checkPhoneIsUnicom(CString phone)
{
	//strcmp(s1, s2)==0
	// 130，131，132，155，156，185，186，145，176
	if (phone.GetLength() < 11){
		return false;
	}
	using namespace std;
	vector<std::string>::iterator result = find(cUrls.phoneHeads.begin(),cUrls.phoneHeads.end(),(LPCTSTR)phone.Left(3));

	if ( result == cUrls.phoneHeads.end( ) ) {
		return false;
	}else{
		return true;
	}
	/*
	if (strcmp(phone.Left(3), "130") == 0
		|| strcmp(phone.Left(3), "131") == 0
		|| strcmp(phone.Left(3), "132") == 0
		|| strcmp(phone.Left(3), "155") == 0
		|| strcmp(phone.Left(3), "156") == 0
		|| strcmp(phone.Left(3), "185") == 0
		|| strcmp(phone.Left(3), "186") == 0
		|| strcmp(phone.Left(3), "145") == 0
		|| strcmp(phone.Left(3), "176") == 0
		){
		return true;
	}
	return false;
	*/
}


LRESULT CIncrementSystemBFDlg::OnMyClickMessage(WPARAM wParam, LPARAM lParam)
{
	
	CComDispatchDriver spScript;
	IDispatch * pDocDisp = NULL;
   
   IHTMLDocument2  *pDoc=NULL;
   pDocDisp = m_MyIE.GetDocument(); 
   
   if (pDocDisp != NULL) 
   {
      // Obtained the document object by specifying the IHTMLDocument2 Interface.
		HRESULT hr= pDocDisp->QueryInterface( IID_IHTMLDocument2, (void**)&pDoc );
		
		pDoc->get_Script(&spScript);

		CComVariant varRet;  
		spScript.Invoke0(L"NoticeClient", &varRet); 

		CComDispatchDriver spData = varRet.pdispVal; 
		CComVariant varValue1;
		spData.GetPropertyByName(L"phone", &varValue1);

		CString strResult = _com_util::ConvertBSTRToString((_bstr_t)varValue1);

		szCharUrl.Format("%s%s", cUrls.QueryPhone, strResult);
		//szCharUrl.Format("http://www.baidu.com/s?wd=%s", strResult);
		//szCharUrl.Format("http://132.90.101.25:7001/portal");
		//szCharUrl.Format("http://132.77.51.11:7700/salemanm/salemanm?service=page/silverservice.silverJobExec.goldUnfinishedFrame&listener=initFrame&PROVINCEID=0011&STAFF_ID=yujp21&PASSWORD=H3B5VVJk0JFroCYwhWHbA9C8yes=&LOGIN_TYPE=KFSYS&inModeCode=1&cond_CONFIG=job&cond_FLAG=all&closeNavMethod=close&JOB_STATUS=1&VALID_FLAG=1&EPARCHY_CODE=0010&SERVER_NUMBER=18612452378");
		 
		CString sResult(_T(""));  
  
		// http://132.77.220.134:8081/window/servlet/CheckSerialNumber?serial_number=132.77.220.134
		

		//CString ip(tempUrl.Left(pos).rig);

		HttpRequestGet("132.77.220.134", 8081, "window/servlet/CheckSerialNumber?serial_number="+strResult, sResult);
		///m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);

   		//PostMessage(WM_SIZE,0,0);
   }
   return 1;
}

LRESULT CIncrementSystemBFDlg::OnMyClipMessage(WPARAM wParam, LPARAM lParam)
{
	char *str;
	str = (char *)lParam;
	CString tempStr(str);

	if (!checkPhoneIsUnicom(tempStr.Left(11))){
		
		timeStart = CTime::GetCurrentTime();
		return 0;	
	}
	
	//CString logStr;
	//logStr.Format("匹配号码段成功[%s]", tempStr.Left(11));
	//CLogFile::WriteLog(logStr);
	
	szCharUrl.Format("%s%s", cUrls.QueryPhone, tempStr.Left(11));
	//szCharUrl.Format("http://www.baidu.com/s?wd=%s", tempStr.Left(11));
	CLogFile::WriteLog(szCharUrl);
	
	m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);
	PostMessage(WM_SIZE,0,0);
	ShowWindow(SW_RESTORE);
	
	timeStart = CTime::GetCurrentTime();
	//m_MyIE.GetDocument();
	return 1;
}

LRESULT CIncrementSystemBFDlg::OnMyIEMessage(WPARAM wParam, LPARAM lParam)
{
	CString str;
	str = (LPSTR)lParam;

	MessageBox(str);
	return 1;
}

// 处理键盘捕捉的数字按键信息
LRESULT CIncrementSystemBFDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
		// lParam&0x800000，如果结果是1，表示是被释放的，也就是抬起的。 

	if ( !(lParam & 0X80000000)) {

		if ((wParam >= 0x30 && wParam <= 0x39)
		||(wParam >= 0x60 && wParam <= 0x69)){
			timeNow = CTime::GetCurrentTime();
			CTimeSpan t = timeNow - timeStart;
			if (t.GetSeconds() >= cSystem.PressTimeout){
				CString logTime;
				logTime.Format(_T("输入间隔超过%d秒，此次按键为号码首位!"), cSystem.PressTimeout);
				CLogFile::WriteLog(logTime);
				telPos = 0;
				timeStart = CTime::GetCurrentTime();
			}
			
			if (telPos == 0){
				memset(&telPhone, 1, sizeof(telPhone) );
			}
			CString tempCode;
			tempCode.Format("%c", wParam);
			memcpy(&telPhone[telPos], tempCode, 1);
			
			CString logStr;
			logStr.Format("%d %c -- [%s]%p", telPos, wParam, telPhone, telPhone);
			CLogFile::WriteLog(logStr);
			telPos++;
		}

		if (wParam == 0x8){
			CLogFile::WriteLog("Enter Back");

			CString logStr;
			if (telPos <= 1){
				telPos = 1;
			}
			telPhone[telPos-1] = '\0';  
			logStr.Format("当前号码串为: [%s]", telPhone);
			CLogFile::WriteLog(logStr);
				
			telPos--;
			if (telPos < 0){
				telPos = 0;
			}
		}
		if (wParam == 0x1B){
			CLogFile::WriteLog(_T("接收ESC按键 重置输入信息, 下个数字为号码首位!"));
			telPos = 0;
		}
		
	}	



	if (telPos >= 11){
		telPos = 0;
		telPhone[12] = '\0';
			
		log.Format("Server Phone Number : [%s]",  telPhone);
		CLogFile::WriteLog(log); 

		if (!checkPhoneIsUnicom(telPhone)){
			return 0;	
		}
		//szCharUrl.Format("http://www.baidu.com/s?wd=%s", telPhone); 
		szCharUrl.Format("%s%s", cUrls.QueryPhone, telPhone);
		
		m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);
		PostMessage(WM_SIZE,0,0);
		ShowWindow(SW_RESTORE);
		
		timeStart = CTime::GetCurrentTime();
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
	//ShowWindow(SW_SHOWMINIMIZED);
	
	//::RegisterHotKey(m_hWnd, WM_USER,MOD_ALT, VK_F4);
	// TODO: Add extra initialization here
	m_hView = SetClipboardViewer();
	hDLL=::LoadLibrary(_T("TelEscrowBJ.dll"));       //加载DLL

	if (hDLL!=NULL){
		loadhook=(LOADHOOK)::GetProcAddress (hDLL,"EnableKeyboardCapture");
		unloadhook=(UNLOADHOOK)::GetProcAddress (hDLL,"DisableKeyboardCapture");
	}
	//loadhook();

	
	//m_MyIE.Navigate("http://www.baidu.com", NULL, NULL, NULL, NULL);
	m_MyIE.Navigate(cUrls.Logon, NULL, NULL, NULL, NULL);
	PostMessage(WM_SIZE,0,0);
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
	DocumentCompleteExplorerSelectItem(pDisp, URL);
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
				//spScript.Invoke1(L"SaveCppObject", &var); 
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
				// buttonChangePassword   querySerialNumber
				
				ProcessElementCollection( pElemColl, "querySerialNumber");
			}
		}
		//ProcessDocument( pDocDisp );
	}
	pDocDisp->Release();
}

bool isLogon = false;

void CIncrementSystemBFDlg::DocumentCompleteExplorerSelectItem(LPDISPATCH pDisp, VARIANT* URL)
{
	CString url = URL->bstrVal;

	if (url.Find(cUrls.Logon) > 0){
		TRACE("UnLoadhook");
		unloadhook();
		isLogon = true;
	}
	if (isLogon){
		if (url.Find(cUrls.Http1) > 0){
			TRACE("Loadhook");
			loadhook();
			isLogon = false;
		}
	}
    IUnknown*  pUnk;  
    LPDISPATCH lpWBDisp;  
    HRESULT    hr;  
 
    pUnk = m_MyIE.GetControlUnknown();  
    ASSERT(pUnk);  
 
    hr = pUnk->QueryInterface(IID_IDispatch, (void**)&lpWBDisp);  
    ASSERT(SUCCEEDED(hr));  
 
    if (pDisp == lpWBDisp )  
    {
        //TRACE("Web document is finished downloading/n");//这里就是最佳获取时机的判断
    }
    pUnk->Release();
    lpWBDisp->Release();
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
	
	
	if (isActive && WM_SYSKEYDOWN){	
// WM_SYSKEYDOWN  表示ALT键按下
		if (pMsg->message && VK_F4 == pMsg->wParam)
		{
			return TRUE;
		}
		switch(pMsg->wParam)  
        {  
            case VK_ESCAPE: //Esc按键事件  
                return true;  
            case VK_RETURN: //Enter按键事件  
                return true;  
            default:  
                ;  
        }
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

void CIncrementSystemBFDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default 
	if ((nID & 0xFFF0) == SC_CLOSE){
		CString tempInfo;
		tempInfo.Format("请确认是否退出 %s 系统!", cSystem.Title);
		if (IDOK == ::MessageBox(m_hWnd, tempInfo, "确认框", MB_OKCANCEL)){
			unloadhook();
		}else{
			return;
		}
	}

	CDialog::OnSysCommand(nID, lParam);
}

BOOL CIncrementSystemBFDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CString tempStr=(LPSTR)pCopyDataStruct->lpData;
	// 获得实际长度的字符串
	tempStr=tempStr.Left(pCopyDataStruct->cbData);
	// 更新数据
	UpdateData(FALSE);

	if (!checkPhoneIsUnicom(tempStr.Left(11))){
		
		timeStart = CTime::GetCurrentTime();
		return 0;	
	}
	
	//CString logStr;
	//logStr.Format("匹配号码段成功[%s]", tempStr.Left(11));
	//CLogFile::WriteLog(logStr);
	
	szCharUrl.Format("%s%s", cUrls.QueryPhone, tempStr.Left(11));
	//szCharUrl.Format("http://www.baidu.com/s?wd=%s", tempStr.Left(11));
	CLogFile::WriteLog(szCharUrl);
	
	m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);

	PostMessage(WM_SIZE,0,0);
	ShowWindow(SW_RESTORE);
	
	timeStart = CTime::GetCurrentTime();

	return CDialog::OnCopyData(pWnd, pCopyDataStruct);
}

void CIncrementSystemBFDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
	CDialog::OnMenuSelect(nItemID, nFlags, hSysMenu);
	
	// TODO: Add your message handler code here
	
}
