// IncrementSystemBFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IncrementSystemBF.h"
#include "IncrementSystemBFDlg.h"
#include "LogFile.h"

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
	ON_WM_DESTROY()
	ON_WM_CHANGECBCHAIN()
	ON_WM_DRAWCLIPBOARD()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString szCharUrl;
CString log;

LRESULT CIncrementSystemBFDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	char *str;
	str = (char *)lParam;
	CString s(str);
	log.Format("s %s", s);
	CLogFile::WriteLog(log);
	WritePrivateProfileString("Student","CCtelPhone",s.Left(11),"c:\\setting.ini");
	szCharUrl.Format("http://www.baidu.com/s?wd=%s", s.Left(11));
	log.Format("p %p", str);
	CLogFile::WriteLog(log);
	m_MyIE.Navigate(szCharUrl, NULL, NULL, NULL, NULL);
	return 1;
}

typedef BOOL (CALLBACK *LOADHOOK)();
typedef BOOL (CALLBACK *UNLOADHOOK)();

HINSTANCE hDLL=NULL;
LOADHOOK loadhook;
UNLOADHOOK unloadhook;
HWND m_hView;

/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFDlg message handlers

BOOL CIncrementSystemBFDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	SetWindowPos(&wndTopMost, 0, 0, 800, 600, SWP_NOMOVE|SWP_SHOWWINDOW);
	// TODO: Add extra initialization here
	m_hView = SetClipboardViewer();
	hDLL=::LoadLibrary(_T("TelEscrowBJ.dll"));       //º”‘ÿDLL

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

		PostMessage(WM_MYMESSAGE, 0, (LPARAM)lpStr);

		GlobalUnlock(hMem);
		CloseClipboard();
		break;
	}
}
