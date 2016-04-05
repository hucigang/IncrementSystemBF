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

class CIncrementSystemBFApp : public CWinApp
{
public:
	CIncrementSystemBFApp();

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
