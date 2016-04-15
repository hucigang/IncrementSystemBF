// MyEventSink.h: interface for the CMyEventSink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYEVENTSINK_H__69602C3A_AD8B_43FD_A929_32A401CA448A__INCLUDED_)
#define AFX_MYEVENTSINK_H__69602C3A_AD8B_43FD_A929_32A401CA448A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyEventSink : public IDispatch  
{
public:
	CMyEventSink();
	virtual ~CMyEventSink();
DWORD CMyEventSink::GetProcessID();
void CMyEventSink::ShowMessageBox(const wchar_t *msg, const wchar_t *msg1);
STDMETHODIMP QueryInterface(const struct _GUID &iid,void ** ppv);
ULONG __stdcall AddRef(void);
ULONG __stdcall Release(void);
STDMETHODIMP GetTypeInfoCount(unsigned int *);
STDMETHODIMP GetTypeInfo(unsigned int,unsigned long,struct ITypeInfo ** );
STDMETHODIMP GetIDsOfNames(const struct _GUID &,unsigned short ** ,unsigned int,unsigned long,long *);
STDMETHODIMP Invoke(
	long dispID,
	const struct _GUID &,
	unsigned long,
	unsigned short,
	struct tagDISPPARAMS * pParams,
	struct tagVARIANT *,
	struct tagEXCEPINFO *,
	unsigned int *);

};

#endif // !defined(AFX_MYEVENTSINK_H__69602C3A_AD8B_43FD_A929_32A401CA448A__INCLUDED_)
