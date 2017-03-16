
// DlgProxy.h: header file
//

#pragma once

class CWebcamTestMfcDlg;


// CWebcamTestMfcDlgAutoProxy command target

class CWebcamTestMfcDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CWebcamTestMfcDlgAutoProxy)

	CWebcamTestMfcDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CWebcamTestMfcDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CWebcamTestMfcDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CWebcamTestMfcDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

