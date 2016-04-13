// IncrementSystemBF.cpp : Defines the class behaviors for the application.
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
// CIncrementSystemBFApp

BEGIN_MESSAGE_MAP(CIncrementSystemBFApp, CWinApp)
	//{{AFX_MSG_MAP(CIncrementSystemBFApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFApp construction

#define MAX_LENGTH 500

CString CIncrementSystemBFApp::ReturnPath()  
{   
   CString    sPath;   
   GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
   sPath.ReleaseBuffer    ();   
   int    nPos;   
   nPos=sPath.ReverseFind('\\');   
   sPath=sPath.Left(nPos);   
   return    sPath;   
}

CString CIncrementSystemBFApp::setConfig(CString section, CString name)
{
	CString path;
	path = ReturnPath();
	CString configFile;
	configFile.Format("%s\\%s", path, CONFIG_PSTR);
	CString temp;
	::GetPrivateProfileString(section,name,"",temp.GetBuffer(MAX_LENGTH),MAX_LENGTH,configFile);

	return temp;
}

CIncrementSystemBFApp::CIncrementSystemBFApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	memset(&cSystem,0,sizeof(configSystem));
	memset(&cUrls,0,sizeof(configOfficeNetworkBF));
	cSystem.Beep = atoi(setConfig("System", "Beep"));
	strncpy(cSystem.Title,(LPCTSTR)setConfig("System", "Title"),sizeof(cSystem.Title));
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIncrementSystemBFApp object

CIncrementSystemBFApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFApp initialization

BOOL CIncrementSystemBFApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CIncrementSystemBFDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
