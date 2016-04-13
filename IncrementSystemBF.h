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

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIncrementSystemBFApp:
// See IncrementSystemBF.cpp for the implementation of this class
//
//const char* g_pStr = _T("Hello World!");
#define CONFIG_PSTR _T("IncrementSystem.ini")
#define CMAX_LEN 100
#define UMAX_LEN 500

struct configSystem
{
	/*
Title = ��ϸ������ƽ̨
#����ʱ��(�������û���ʾ��Ϣ)
WorkingTime = 8��00-18��30
#����������ѯ��ʱ�䣬��λΪ��
PollingInterval =300
#������Ŀ��
Width = 568
#������ĸ߶�
Height = 570
#��¼��ʱʱ�䣬��λΪ��
Timeout = 20
#��ѯ���¼�ʱ��ʱ�䣬��λΪ��
QueryElapse = 5
#�Ƿ�������������(0:�����ã�1:����)
Beep = 1
#�Ƿ����ùرհ�ť(0:�����ã�1:����)
ShowClose = 1
#�Ƿ�ֻ����һ��Ӧ�ó���ʵ������(0:��������1:ֻ����һ��)
SingleApp = 1
#�Ƿ񱣴���־(0:��������־��1:������־)
SaveLog = 1
#��־�ļ�����ʱ�䣬��λΪ��
ReserveDays = 30
	*/
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
};

struct configOfficeNetworkBF
{
	/*
	#��¼ʹ�õ�Web��ַ
Logon =http://10.161.18.251:8080/popup/LoginService!login.action?
#��¼�ɹ�������ʹ�õ�Web��ַ
Http1 =http://10.161.18.251:8080/popup/MatchWebFailService.action?
#��֤ʹ�õ�Web��ַ
Authentication =http://10.161.18.251:8080/popup/LoginService!smsAuth.action? 
#��������ʹ�õ�Web��ַ
QueryPhoneType =http://10.161.18.251:8080/popup/web/sales/QueryTelephone!QuerytelType.action?
#������ʶʹ�õ�Web��ַ
QueryPopup =http://10.161.18.251:8080/popup/web/sales/QueryTelephone!QueryIfAlert.action?
#�Զ����������ѯ�Ƿ����Ƽ�ҵ��ʹ�õ�Web��ַ 
QueryPhone =http://10.161.18.251:8080/popup/web/sales/QueryTelephone.action?
#������ѯʹ�õ�Web��ַ
Heartbeat =http://10.161.18.251:8080/popup/LoginService!onlineChk.action?
#��������ʹ�õ�Web��ַ
ResetPassword =http://10.161.18.251:8080/popup/web/sales/GuideRecommend!resetUserPassword.action?
#�ǳ�ʹ�õ�Web��ַ
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
};

class CIncrementSystemBFApp : public CWinApp
{
public:
	CIncrementSystemBFApp();
	configSystem cSystem;
	configOfficeNetworkBF cUrls;
	

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
