
// WebcamTestMfc.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWebcamTestMfcApp:
// See WebcamTestMfc.cpp for the implementation of this class
//

class CWebcamTestMfcApp : public CWinApp
{
public:
	CWebcamTestMfcApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWebcamTestMfcApp theApp;