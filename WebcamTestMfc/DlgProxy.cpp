
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "WebcamTestMfc.h"
#include "DlgProxy.h"
#include "WebcamTestMfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWebcamTestMfcDlgAutoProxy

IMPLEMENT_DYNCREATE(CWebcamTestMfcDlgAutoProxy, CCmdTarget)

CWebcamTestMfcDlgAutoProxy::CWebcamTestMfcDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CWebcamTestMfcDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CWebcamTestMfcDlg)))
		{
			m_pDialog = reinterpret_cast<CWebcamTestMfcDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CWebcamTestMfcDlgAutoProxy::~CWebcamTestMfcDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CWebcamTestMfcDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CWebcamTestMfcDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CWebcamTestMfcDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IWebcamTestMfc to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {7523AA71-9DE0-45F9-AF43-80CC3BD22E4A}
static const IID IID_IWebcamTestMfc =
{ 0x7523AA71, 0x9DE0, 0x45F9, { 0xAF, 0x43, 0x80, 0xCC, 0x3B, 0xD2, 0x2E, 0x4A } };

BEGIN_INTERFACE_MAP(CWebcamTestMfcDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CWebcamTestMfcDlgAutoProxy, IID_IWebcamTestMfc, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {C0B4B066-DF21-4C5D-AF65-28C799EEEF82}
IMPLEMENT_OLECREATE2(CWebcamTestMfcDlgAutoProxy, "WebcamTestMfc.Application", 0xc0b4b066, 0xdf21, 0x4c5d, 0xaf, 0x65, 0x28, 0xc7, 0x99, 0xee, 0xef, 0x82)


// CWebcamTestMfcDlgAutoProxy message handlers
