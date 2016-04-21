// IncrementSystemBF.h : main header file for the INCREMENTSYSTEMBF application
//

#if !defined(AFX_INCREMENTSYSTEMBF_H__33595C59_5340_438E_9442_B7AF6E44EF35__INCLUDED_)
#define AFX_INCREMENTSYSTEMBF_H__33595C59_5340_438E_9442_B7AF6E44EF35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define CONFIG_PSTR _T("IncrementSystem.ini")

#define LOGON_HTML_ID _T("Logon")
#define HTTP1_HTML_ID _T("Http1")
#define AUTH_HTML_ID _T("Authentication")
#define QUERYPT_HTML_ID _T("QueryPhoneType")
#define QUERYPOP_HTML_ID _T("QueryPopup")
#define QUERYPHONE_HTML_ID _T("querySerialNumber")
#define HB_HTML_ID _T("Heartbeat")
#define RESETPWD_HTML_ID _T("ResetPassword")
#define LOGOFF_HTML_ID _T("Logoff")
#define PHONEHEAD_ID _T("PhoneHead")

#define CMAX_LEN 100
#define UMAX_LEN 500
#pragma warning(disable: 4786)
#include <vector>
#include <string>

typedef struct configSystem
{
	/*
Title = 精细化助销平台
#工作时间(用于向用户提示信息)
WorkingTime = 8：00-18：30
#发起心跳查询的时间，单位为秒
PollingInterval =300
#主界面的宽度
Width = 568
#主界面的高度
Height = 570
#登录超时时间，单位为秒
Timeout = 20
#查询重新计时的时间，单位为秒
QueryElapse = 5
#是否启用声音报警(0:不启用；1:启用)
Beep = 1
#是否启用关闭按钮(0:不启用；1:启用)
ShowClose = 1
#是否只允许一个应用程序实例运行(0:允许多个；1:只允许一个)
SingleApp = 1
#是否保存日志(0:不保存日志；1:保存日志)
SaveLog = 1
#日志文件保留时间，单位为天
ReserveDays = 30
	*/
	char Title[CMAX_LEN];
	char WorkingTime[CMAX_LEN];
	int PollingInterval;
	int Width;
	int Height;
	int Timeout;
	int PressTimeout;
	int QueryElapse;
	int Beep;
	int ShowClose;
	int SingleApp;
	int SaveLog;
	int ReserveDays;
} WinBFConfig;

typedef struct configOfficeNetworkBF
{
	/*
	#登录使用的Web地址
Logon =http://10.161.18.251:8080/popup/LoginService!login.action?
#登录成功后依次使用的Web地址
Http1 =http://10.161.18.251:8080/popup/MatchWebFailService.action?
#验证使用的Web地址
Authentication =http://10.161.18.251:8080/popup/LoginService!smsAuth.action? 
#号码类型使用的Web地址
QueryPhoneType =http://10.161.18.251:8080/popup/web/sales/QueryTelephone!QuerytelType.action?
#弹窗标识使用的Web地址
QueryPopup =http://10.161.18.251:8080/popup/web/sales/QueryTelephone!QueryIfAlert.action?
#自动捕获号码后查询是否有推荐业务使用的Web地址 
QueryPhone =http://10.161.18.251:8080/popup/web/sales/QueryTelephone.action?
#心跳查询使用的Web地址
Heartbeat =http://10.161.18.251:8080/popup/LoginService!onlineChk.action?
#重置密码使用的Web地址
ResetPassword =http://10.161.18.251:8080/popup/web/sales/GuideRecommend!resetUserPassword.action?
#登出使用的Web地址
Logoff =http://10.161.18.251:8080/popup/web/sales/GuideRecommend!userQuite.action?
	*/
	char Logon[UMAX_LEN];
	char Http1[UMAX_LEN];
	char Authentication[UMAX_LEN];
	char QueryPhoneType[UMAX_LEN];
	char QueryPopup[UMAX_LEN];
	char QueryPhone[UMAX_LEN];
	char Heartbeat[UMAX_LEN];
	char ResetPassword[UMAX_LEN];
	char Logoff[UMAX_LEN];
	std::vector<std::string> phoneHeads;
} WinBFUrls;

extern WinBFConfig cSystem;
extern WinBFUrls cUrls;


/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFApp:
// See IncrementSystemBF.cpp for the implementation of this class
//
//const char* g_pStr = _T("Hello World!");

class CIncrementSystemBFApp : public CWinApp
{
public:
	CIncrementSystemBFApp();
	
	CString ReturnPath();
	CString setConfig(CString section, CString name);
private:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncrementSystemBFApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIncrementSystemBFApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCREMENTSYSTEMBF_H__33595C59_5340_438E_9442_B7AF6E44EF35__INCLUDED_)
