// IncrementSystemBF.cpp : Defines the class behaviors for the application.
//
#include "stdafx.h"
#include "IncrementSystemBF.h"
#include "IncrementSystemBFDlg.h"
#include "Resource.h"

#include "LogFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
WinBFConfig cSystem;
WinBFUrls cUrls;

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

//字符串分割函数
std::vector<std::string> split(std::string str,std::string pattern)
{
  std::string::size_type pos;
  std::vector<std::string> result;
  str+=pattern;//扩展字符串以方便操作
  int size=str.size();
 
  for(int i=0; i<size; i++)
  {
    pos=str.find(pattern,i);
    if(pos<size)
    {
      std::string s=str.substr(i,pos-i);
      result.push_back(s);
      i=pos+pattern.size()-1;
    }
  }
  return result;
}

CIncrementSystemBFApp::CIncrementSystemBFApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
//	memset(&cSystem,0,sizeof(configSystem));
//	memset(&cUrls,0,sizeof(configOfficeNetworkBF));
	/*
		char Title[CMAX_LEN];
	char WorkingTime[CMAX_LEN];
	int PollingInterval;
	int Width;
	int Height;
	int Timeout;
	int QueryElapse;
	int Beep;
	int ShowClose;
	int SingleApp;
	int SaveLog;
	int ReserveDays;
	*/
	strncpy(cSystem.Title,(LPCTSTR)setConfig("System", "Title"),sizeof(cSystem.Title));
	cSystem.Beep = atoi(setConfig("System", "Beep"));
	strncpy(cSystem.WorkingTime,(LPCTSTR)setConfig("System", "WorkingTime"),sizeof(cSystem.WorkingTime));
	cSystem.PollingInterval = atoi(setConfig("System", "PollingInterval"));
	cSystem.Width = atoi(setConfig("System", "Width"));
	cSystem.Height = atoi(setConfig("System", "Height"));
	cSystem.Timeout = atoi(setConfig("System", "Timeout"));
	cSystem.PressTimeout = atoi(setConfig("System", "PressTimeout"));
	cSystem.QueryElapse = atoi(setConfig("System", "QueryElapse"));
	cSystem.Beep = atoi(setConfig("System", "Beep"));
	cSystem.ShowClose = atoi(setConfig("System", "ShowClose"));
	cSystem.SingleApp = atoi(setConfig("System", "SingleApp"));
	cSystem.SaveLog = atoi(setConfig("System", "SaveLog"));
	cSystem.ReserveDays = atoi(setConfig("System", "ReserveDays"));

	/*
	char Logon[UMAX_LEN];
	char Http1[UMAX_LEN];
	char Authentication[UMAX_LEN];
	char QueryPhoneType[UMAX_LEN];
	char QueryPopup[UMAX_LEN];
	char QueryPhone[UMAX_LEN];
	char Heartbeat[UMAX_LEN];
	char ResetPassword[UMAX_LEN];
	char Logoff[UMAX_LEN];
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
	strncpy(cUrls.Logon,(LPCTSTR)setConfig("OfficeNetwork", LOGON_HTML_ID),sizeof(cUrls.Logon));
	strncpy(cUrls.Http1,(LPCTSTR)setConfig("OfficeNetwork", HTTP1_HTML_ID),sizeof(cUrls.Http1));
	strncpy(cUrls.Authentication,(LPCTSTR)setConfig("OfficeNetwork", AUTH_HTML_ID),sizeof(cUrls.Authentication));
	strncpy(cUrls.QueryPhoneType,(LPCTSTR)setConfig("OfficeNetwork", QUERYPT_HTML_ID),sizeof(cUrls.QueryPhoneType));
	strncpy(cUrls.QueryPopup,(LPCTSTR)setConfig("OfficeNetwork", QUERYPOP_HTML_ID),sizeof(cUrls.QueryPopup));
	strncpy(cUrls.QueryPhone,(LPCTSTR)setConfig("OfficeNetwork", QUERYPHONE_HTML_ID),sizeof(cUrls.QueryPhone));
	strncpy(cUrls.Heartbeat,(LPCTSTR)setConfig("OfficeNetwork", HB_HTML_ID),sizeof(cUrls.Heartbeat));
	strncpy(cUrls.ResetPassword,(LPCTSTR)setConfig("OfficeNetwork", RESETPWD_HTML_ID),sizeof(cUrls.ResetPassword));
	strncpy(cUrls.Logoff,(LPCTSTR)setConfig("OfficeNetwork", LOGOFF_HTML_ID),sizeof(cUrls.Logoff));
	char temp[UMAX_LEN];
	strncpy(temp, (LPCTSTR)setConfig("OfficeNetwork", PHONEHEAD_ID),sizeof(temp));
	CLogFile::WriteLog(temp);
	string tempStr;
	tempStr = temp;
	string s=",";
    cUrls.phoneHeads =split(tempStr,s);
	//for(vector<string>::iterator it=cUrls.phoneHeads.begin(); it!=cUrls.phoneHeads.end();it++){
	//	CLogFile::WriteLog(*it->_p);
	//}
	CLogFile::WriteLog("配置文件加载完成。"); 
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIncrementSystemBFApp object

CIncrementSystemBFApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFApp initialization

BOOL CIncrementSystemBFApp::InitInstance()
{

	CreateMutex(NULL,true,MY_GUID); 
	if(GetLastError() == ERROR_ALREADY_EXISTS) 
	{ 
		AfxMessageBox(_T("应用程序不可以重复启动!"),MB_OK | MB_APPLMODAL | MB_ICONSTOP); 
		return(false); 
	}

	CString path;
	path = ReturnPath();
	CString updatePath;
	updatePath.Format("%s\\%s", path, "Update.exe");
	

	PROCESS_INFORMATION piProcInfoGPS;
    STARTUPINFO siStartupInfo;
    SECURITY_ATTRIBUTES saProcess, saThread;
    ZeroMemory( &siStartupInfo, sizeof(siStartupInfo) );
    siStartupInfo.cb = sizeof(siStartupInfo);
    saProcess.nLength = sizeof(saProcess);
    saProcess.lpSecurityDescriptor = NULL;
    saProcess.bInheritHandle = true;
    saThread.nLength = sizeof(saThread);
    saThread.lpSecurityDescriptor = NULL;
    saThread.bInheritHandle = true;
    CreateProcess( NULL, (LPTSTR)(LPSTR)(LPCTSTR)updatePath, &saProcess, &saThread, false, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &siStartupInfo,&piProcInfoGPS );

	WaitForSingleObject(piProcInfoGPS.hProcess,INFINITE);
  
	DWORD   ExitCode;
	GetExitCodeProcess(piProcInfoGPS.hProcess,&ExitCode);

	//if (ExitCode != 0){
	//	AfxMessageBox(_T("自动更新失败，不能启动程序!!"),MB_OK | MB_APPLMODAL | MB_ICONSTOP); 
	//	return (false);
	//}

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
