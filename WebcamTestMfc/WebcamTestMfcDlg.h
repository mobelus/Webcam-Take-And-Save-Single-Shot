
// WebcamTestMfcDlg.h : header file
//

#pragma once
//*
// EXTRA PROJECT SETTINGS:
// Config Properties -> Linker -> General -- "Per-user Redirection" SET IT TO "No"

#include <dshow.h>
#include <strsafe.h>
#include "qedit.h"

#include <gdiplus.h>
#include <stdio.h>
#include <vector>
using namespace std;

#include "afxrendertarget.h"

#pragma comment(lib,"strmiids.lib")
#pragma comment(lib,"gdiplus.lib")
//*/


#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

class CWebcamTestMfcDlgAutoProxy;


// CWebcamTestMfcDlg dialog
class CWebcamTestMfcDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebcamTestMfcDlg);
	friend class CWebcamTestMfcDlgAutoProxy;

public:
	HRESULT vcHandleGraphEvent(void);

	//////////////////////////////////////////////////////////////////////
	IMediaControl * g_pMC = NULL;
	IVideoWindow  * g_pVW = NULL;
	IMediaEventEx * g_pME = NULL;
	IGraphBuilder * g_pGraph = NULL;
	ICaptureGraphBuilder2 * g_pCapture = NULL;

	// Application-defined message to notify app of filtergraph events
#define WM_GRAPHNOTIFY  WM_APP+1

	enum PLAYSTATE { Stopped, Paused, Running, Init };
	PLAYSTATE g_psCurrent = Stopped;


	void Msg(TCHAR *szFormat, ...);
	HRESULT GetInterfaces(HWND hWnd);
	void CloseInterfaces(void);

	void vcGetCaptureDevices(CComboBox& adaptersBox);
	HRESULT FindCaptureDevice(IBaseFilter** ppSrcFilter, unsigned int devIndex = 1);

	HRESULT vcCaptureVideo(HWND msgWindow, HWND prvWindow, unsigned int devIndex = 1); //devIndex = 1,2,3 ...
	void vcStopCaptureVideo();

	//////////////////////////////////////////////////////////////////////
	IBaseFilter *pGrabberFilter = NULL;
	ISampleGrabber *pGrabber = NULL;

	unsigned char* pBuffer = 0;
	long pBufferSize = 0;

	Gdiplus::Bitmap *pCapturedBitmap = 0;
	unsigned int gWidth = 0;
	unsigned int gHeight = 0;
	unsigned int gChannels = 0;

	// mwthods
	IBaseFilter* sgGetSampleGrabber();
	void sgCloseSampleGrabber();

	HRESULT sgAddSampleGrabber(IGraphBuilder *pGraph);
	HRESULT sgSetSampleGrabberMediaType();
	HRESULT sgGetSampleGrabberMediaType();

	HRESULT SetupVideoWindow(HWND hWnd);

	unsigned char* sgGrabData();            //call grab data first
	Gdiplus::Bitmap* sgGetBitmap();        //fill bitmap with grabbed data


	int sgSetBitmapData(Gdiplus::Bitmap* pBitmap, const unsigned char* pData);
	void sgFlipUpDown(unsigned char* pData);
	void sgFreeMediaType(AM_MEDIA_TYPE& mt);
	//////////////////////////////////////////////////////////////////////

	bool sgSaveDataToFile(Gdiplus::Bitmap *pBitmap);
	bool sgGrabDataAndSaveToFile();
	void takeWebcamPicture();


// Construction
public:
	CWebcamTestMfcDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CWebcamTestMfcDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBCAMTESTMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CWebcamTestMfcDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnGraphMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedOk();
};
