
// WebcamTestMfcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WebcamTestMfc.h"
#include "WebcamTestMfcDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWebcamTestMfcDlg dialog


IMPLEMENT_DYNAMIC(CWebcamTestMfcDlg, CDialogEx);

CWebcamTestMfcDlg::CWebcamTestMfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WEBCAMTESTMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CWebcamTestMfcDlg::~CWebcamTestMfcDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CWebcamTestMfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWebcamTestMfcDlg, CDialogEx)
	ON_MESSAGE(WM_GRAPHNOTIFY, OnGraphMessage)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWebcamTestMfcDlg::OnBnClickedOk)
END_MESSAGE_MAP()



LRESULT CWebcamTestMfcDlg::OnGraphMessage(WPARAM wParam, LPARAM lParam)
{
	HRESULT hr = vcHandleGraphEvent();
	TRACE(L" WM_GRAPH 0x%X\n", hr);
	return 0;
}

// CWebcamTestMfcDlg message handlers

BOOL CWebcamTestMfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	// TODO: Add extra initialization here
	takeWebcamPicture();


	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CWebcamTestMfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWebcamTestMfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWebcamTestMfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CWebcamTestMfcDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CWebcamTestMfcDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CWebcamTestMfcDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CWebcamTestMfcDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CWebcamTestMfcDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// for vcGetCaptureDevices
void CWebcamTestMfcDlg::Msg(TCHAR *szFormat, ...)
{
	TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
	const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
	const int LASTCHAR = NUMCHARS - 1;

	// Format the input string
	va_list pArgs;
	va_start(pArgs, szFormat);

	// Use a bounded buffer size to prevent buffer overruns.  Limit count to
	// character size minus one to allow for a NULL terminating character.
	(void)StringCchVPrintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
	va_end(pArgs);

	// Ensure that the formatted string is NULL-terminated
	szBuffer[LASTCHAR] = TEXT('\0');

	MessageBox(/*NULL,*/ szBuffer, TEXT("PlayCap Message"), MB_OK | MB_ICONERROR);
}

// for vcCaptureVideo
HRESULT CWebcamTestMfcDlg::GetInterfaces(HWND hWnd)
{
	HRESULT hr;

	// Create the filter graph
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
		IID_IGraphBuilder, (void **)& g_pGraph);
	if (FAILED(hr))
		return hr;

	// Create the capture graph builder
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC,
		IID_ICaptureGraphBuilder2, (void **)& g_pCapture);
	if (FAILED(hr))
		return hr;

	// Obtain interfaces for media control and Video Window
	hr = g_pGraph->QueryInterface(IID_IMediaControl, (LPVOID *)& g_pMC);
	if (FAILED(hr))
		return hr;

	hr = g_pGraph->QueryInterface(IID_IVideoWindow, (LPVOID *)& g_pVW);
	if (FAILED(hr))
		return hr;

	hr = g_pGraph->QueryInterface(IID_IMediaEvent, (LPVOID *)& g_pME);
	if (FAILED(hr))
		return hr;

	// Set the window handle used to process graph events
	hr = g_pME->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);

	return hr;
}


HRESULT CWebcamTestMfcDlg::vcHandleGraphEvent(void)
{
	LONG evCode;
	LONG_PTR evParam1, evParam2;
	HRESULT hr = S_OK;

	if (!g_pME)
		return E_POINTER;

	while (SUCCEEDED(g_pME->GetEvent(&evCode, &evParam1, &evParam2, 0))) {
		//
		// Free event parameters to prevent memory leaks associated with
		// event parameter data.  While this application is not interested
		// in the received events, applications should always process them.
		//
		hr = g_pME->FreeEventParams(evCode, evParam1, evParam2);

		// Insert event processing code here, if desired
	}

	return hr;
}

void CWebcamTestMfcDlg::CloseInterfaces(void)
{
	// Stop previewing data
	if (g_pMC)
		g_pMC->StopWhenReady();

	g_psCurrent = Stopped;

	// Stop receiving events
	if (g_pME)
		g_pME->SetNotifyWindow(NULL, WM_GRAPHNOTIFY, 0);

	// Relinquish ownership (IMPORTANT!) of the video window.
	// Failing to call put_Owner can lead to assert failures within
	// the video renderer, as it still assumes that it has a valid
	// parent window.
	if (g_pVW) {
		g_pVW->put_Visible(OAFALSE);
		g_pVW->put_Owner(NULL);
	}

#ifdef REGISTER_FILTERGRAPH
	// Remove filter graph from the running object table
	if (g_dwGraphRegister)
		RemoveGraphFromRot(g_dwGraphRegister);
#endif

	// Release DirectShow interfaces
	SAFE_RELEASE(g_pMC);
	SAFE_RELEASE(g_pME);
	SAFE_RELEASE(g_pVW);
	SAFE_RELEASE(g_pGraph);
	SAFE_RELEASE(g_pCapture);
}

/////////////////////////////////////////////////////////////////////////////////////
void CWebcamTestMfcDlg::vcGetCaptureDevices(CComboBox& adaptersBox)
{
	adaptersBox.ResetContent();

	// Create the System Device Enumerator.
	HRESULT hr;
	ICreateDevEnum *pSysDevEnum = NULL;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void **)& pSysDevEnum);
	if (FAILED(hr)) {
		Msg(TEXT("CoCreateInstance() hr=0x%x"), hr);
		return;
	}

	// Obtain a class enumerator for the video compressor category.
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);

	if (hr == S_OK) {
		// Enumerate the monikers.
		IMoniker *pMoniker = NULL;
		ULONG cFetched;
		while (pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK) {
			IPropertyBag *pPropBag;
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
				(void **)& pPropBag);
			if (SUCCEEDED(hr)) {
				// To retrieve the filter's friendly name, do the following:
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				if (SUCCEEDED(hr)) {
					adaptersBox.AddString(varName.bstrVal);
					
					//int len = wcslen((wchar_t*)varName.pbstrVal);
					//char * strval = (char *)malloc(len);
					//wcstombs(strval, (wchar_t*)varName.pbstrVal, len + 1);
					//adaptersBox.AddString(strval);
					/*
					USES_CONVERSION;
					LPCTSTR str = W2CA(varName.bstrVal);
					adaptersBox.AddString(str);
					*/
				}
				VariantClear(&varName);

				// To create an instance of the filter, do the following:
				IBaseFilter *pFilter;
				hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
					(void **)& pFilter);
				// Now add the filter to the graph.
				//Remember to release pFilter later.
				pPropBag->Release();
			}
			pMoniker->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();

	adaptersBox.SetCurSel(0);
}

HRESULT CWebcamTestMfcDlg::FindCaptureDevice(IBaseFilter** ppSrcFilter, unsigned int devIndex)
{
	HRESULT hr = S_OK;
	IBaseFilter* pSrc = NULL;
	IMoniker* pMoniker = NULL;
	ICreateDevEnum* pDevEnum = NULL;
	IEnumMoniker* pClassEnum = NULL;

	if (!ppSrcFilter) {
		return E_POINTER;
	}

	// Create the system device enumerator
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
		IID_ICreateDevEnum, (void **)& pDevEnum);
	if (FAILED(hr)) {
		Msg(TEXT("Couldn't create system enumerator!  hr=0x%x"), hr);
	}

	// Create an enumerator for the video capture devices

	if (SUCCEEDED(hr)) {
		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
		if (FAILED(hr)) {
			Msg(TEXT("Couldn't create class enumerator!  hr=0x%x"), hr);
		}
	}

	if (SUCCEEDED(hr)) {
		// If there are no enumerators for the requested type, then
		// CreateClassEnumerator will succeed, but pClassEnum will be NULL.
		if (pClassEnum == NULL) {
			MessageBox(/*NULL,*/ TEXT("No video capture device was detected.\r\n\r\n")
				TEXT("The software requires a video capture device, such as a USB WebCam,\r\n")
				TEXT("Transaction will pass by without security measures that are required."),
				TEXT("No Video Capture Hardware"), MB_OK | MB_ICONINFORMATION);
			hr = E_FAIL; // APP WILL BE CLOSED !!!
		}
	}

	// Find the [devIndex] video capture device on the device list.
	// Note that if the Next() call succeeds but there are no monikers,
	// it will return S_FALSE (which is not a failure).  Therefore, we
	// check that the return code is S_OK instead of using SUCCEEDED() macro.

	if (SUCCEEDED(hr)) {
		for (unsigned int i = 0; i < devIndex; i++) {
			hr = pClassEnum->Next(1, &pMoniker, NULL);
			if (hr == S_FALSE) {
				Msg(TEXT("Unable to access video capture device!"));
				hr = E_FAIL; // APP WILL BE CLOSED
				break;
			}
		}
	}

	if (SUCCEEDED(hr)) {
		// Bind Moniker to a filter object
		hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void **)& pSrc);
		if (FAILED(hr)) {
			Msg(TEXT("Couldn't bind moniker to filter object!  hr=0x%x"), hr);
		}
	}

	// Copy the found filter pointer to the output parameter.
	if (SUCCEEDED(hr)) {
		*ppSrcFilter = pSrc;
		(*ppSrcFilter)->AddRef();
	}

	SAFE_RELEASE(pSrc);
	SAFE_RELEASE(pMoniker);
	SAFE_RELEASE(pDevEnum);
	SAFE_RELEASE(pClassEnum);

	return hr;
}

/////////////////////////////////////////////////////////////////////////////////////
HRESULT CWebcamTestMfcDlg::vcCaptureVideo(HWND msgWindow, HWND prvWindow, unsigned int devIndex)
{
	if (devIndex == 0)
		devIndex = 1;

	HRESULT hr;
	IBaseFilter *pSrcFilter = NULL;

	// Get DirectShow interfaces
	hr = GetInterfaces(msgWindow);
	if (FAILED(hr)) {
		Msg(TEXT("Failed to get video interfaces!  hr=0x%x"), hr);
		return hr;
	}

	// Attach the filter graph to the capture graph
	hr = g_pCapture->SetFiltergraph(g_pGraph);
	if (FAILED(hr)) {
		Msg(TEXT("Failed to set capture filter graph!  hr=0x%x"), hr);
		return hr;
	}

	// Use the system device enumerator and class enumerator to find
	// a video capture/preview device, such as a desktop USB video camera.
	hr = FindCaptureDevice(&pSrcFilter);
	if (FAILED(hr)) {
		// Don't display a message because FindCaptureDevice will handle it
		return hr;
	}


	// Add Capture filter to our graph.
	hr = g_pGraph->AddFilter(pSrcFilter, L"Video Capture");
	if (FAILED(hr))
	{
		Msg(TEXT("Couldn't add the capture filter to the graph!  hr=0x%x\r\n\r\n")
			TEXT("If you have a working video capture device, please make sure\r\n")
			TEXT("that it is connected and is not being used by another application.\r\n\r\n")
			TEXT("The sample will now close."), hr);
		pSrcFilter->Release();
		return hr;
	}

	hr = sgAddSampleGrabber(g_pGraph);
	if (FAILED(hr)) {
		Msg(TEXT("Couldn't add the SampleGrabber filter to the graph!  hr=0x%x"), hr);
		return hr;
	}
	hr = sgSetSampleGrabberMediaType();
	if (FAILED(hr)) {
		Msg(TEXT("Couldn't set the SampleGrabber media type!  hr=0x%x"), hr);
		return hr;
	}
	IBaseFilter* pGrabberLocal = sgGetSampleGrabber();


	// Render the preview pin on the video capture filter
	// Use this instead of g_pGraph->RenderFile
	hr = g_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
								pSrcFilter, pGrabberLocal/*NULL*/, NULL);

	if (FAILED(hr)) {
		Msg(TEXT("Couldn't render the video capture stream.  hr=0x%x\r\n")
			TEXT("The capture device may already be in use by another application.\r\n\r\n")
			TEXT("The sample will now close."), hr);
		pSrcFilter->Release();
		return hr;
	}

	hr = sgGetSampleGrabberMediaType();

	// Now that the filter has been added to the graph and we have
	// rendered its stream, we can release this reference to the filter.
	pSrcFilter->Release();

	//*/// Set video window style and position
		hr = SetupVideoWindow(prvWindow);
		if (FAILED(hr)) {
			Msg(TEXT("Couldn't initialize video window!  hr=0x%x"), hr);
			return hr;
		}
	//*/
#ifdef REGISTER_FILTERGRAPH
	// Add our graph to the running object table, which will allow
	// the GraphEdit application to "spy" on our graph
	hr = AddGraphToRot(g_pGraph, &g_dwGraphRegister);
	if (FAILED(hr)) {
		Msg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
		g_dwGraphRegister = 0;
	}
#endif

	// Start previewing video data
	hr = g_pMC->Run();
	if (FAILED(hr)) {
		Msg(TEXT("Couldn't run the graph!  hr=0x%x"), hr);
		return hr;
	}

	// Remember current state
	g_psCurrent = Running;

	return S_OK;
}

void CWebcamTestMfcDlg::vcStopCaptureVideo()
{
	sgCloseSampleGrabber();
	CloseInterfaces();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//vcCaptureVideo
IBaseFilter* CWebcamTestMfcDlg::sgGetSampleGrabber()
{
	return pGrabberFilter;
}
//vcStopCaptureVideo
void CWebcamTestMfcDlg::sgCloseSampleGrabber()
{
	if (pBuffer != 0) {
		delete[] pBuffer;
		pBuffer = 0;
		pBufferSize = 0;
	}

	if (pCapturedBitmap != 0) {
		::delete pCapturedBitmap;
		pCapturedBitmap = 0;
	}

	SAFE_RELEASE(pGrabberFilter);
	SAFE_RELEASE(pGrabber);

	gWidth = 0;
	gHeight = 0;
	gChannels = 0;
}

// for vcCaptureVideo
HRESULT CWebcamTestMfcDlg::sgAddSampleGrabber(IGraphBuilder *pGraph)
{
	// Create the Sample Grabber.
	HRESULT hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (void**)& pGrabberFilter);
	if (FAILED(hr)) {
		return hr;
	}
	hr = pGraph->AddFilter(pGrabberFilter, L"Sample Grabber");
	if (FAILED(hr)) {
		return hr;
	}

	pGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&pGrabber);
	return hr;
}
// for vcCaptureVideo
HRESULT CWebcamTestMfcDlg::sgSetSampleGrabberMediaType()
{
	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	HRESULT hr = pGrabber->SetMediaType(&mt);
	if (FAILED(hr)) {
		return hr;
	}
	hr = pGrabber->SetOneShot(FALSE);
	hr = pGrabber->SetBufferSamples(TRUE);
	return hr;
}
// for vcCaptureVideo
HRESULT CWebcamTestMfcDlg::sgGetSampleGrabberMediaType()
{
	AM_MEDIA_TYPE mt;
	HRESULT hr = pGrabber->GetConnectedMediaType(&mt);
	if (FAILED(hr)) {
		return hr;
	}

	VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER *)mt.pbFormat;
	gChannels = pVih->bmiHeader.biBitCount / 8;
	gWidth = pVih->bmiHeader.biWidth;
	gHeight = pVih->bmiHeader.biHeight;

	sgFreeMediaType(mt);
	return hr;
}

HRESULT CWebcamTestMfcDlg::SetupVideoWindow(HWND hWnd)
{
	HRESULT hr;

	// Set the video window to be a child of the main window
	hr = g_pVW->put_Owner((OAHWND)hWnd);
	if (FAILED(hr))
		return hr;

	// Set video window style
	hr = g_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if (FAILED(hr))
		return hr;

	// Use helper function to position video window in client rect
	// of main application window
	//::ResizeVideoWindow(hWnd);
	//void ResizeVideoWindow(HWND hWnd)
	{
		// Resize the video preview window to match owner window size
		if (g_pVW) {
			RECT rc;

			// Make the preview video fill our window
			::GetClientRect(hWnd, &rc);
			g_pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
		}
	}


	// Make the video window visible, now that it is properly positioned
	hr = g_pVW->put_Visible(OATRUE);
	if (FAILED(hr))
		return hr;

	return hr;
}



//long sgGetBufferSize()
//{
//	return pBufferSize;
//}

// for sgGetBitmap
int CWebcamTestMfcDlg::sgSetBitmapData(Gdiplus::Bitmap* pBitmap, const unsigned char* pData)
{
	Gdiplus::BitmapData bitmapData;
	bitmapData.Width = pBitmap->GetWidth();
	bitmapData.Height = pBitmap->GetHeight();
	bitmapData.Stride = 3 * bitmapData.Width;
	bitmapData.PixelFormat = pBitmap->GetPixelFormat();
	bitmapData.Scan0 = (VOID*)pData;
	bitmapData.Reserved = NULL;

	Gdiplus::Status s = pBitmap->LockBits(&Gdiplus::Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
		Gdiplus::ImageLockModeWrite | Gdiplus::ImageLockModeUserInputBuf,
		PixelFormat24bppRGB, &bitmapData
	);
	if (s == Gdiplus::Ok)
		pBitmap->UnlockBits(&bitmapData);

	return s;
}

// for sgGrabData
void CWebcamTestMfcDlg::sgFlipUpDown(unsigned char* pData)
{
	unsigned char* scan0 = pData;
	unsigned char* scan1 = pData + ((gWidth * gHeight * gChannels) - (gWidth * gChannels));

	for (unsigned int y = 0; y < gHeight / 2; y++) {
		for (unsigned int x = 0; x < gWidth * gChannels; x++) {
			swap(scan0[x], scan1[x]);
		}
		scan0 += gWidth * gChannels;
		scan1 -= gWidth * gChannels;
	}

}

//for sgGetSampleGrabberMediaType
void CWebcamTestMfcDlg::sgFreeMediaType(AM_MEDIA_TYPE& mt)
{
	if (mt.cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL)
	{
		// Unecessary because pUnk should not be used, but safest.
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//takeWebcamPicture
Gdiplus::Bitmap* CWebcamTestMfcDlg::sgGetBitmap()
{
	if (pGrabber == 0 || pBuffer == 0 || gChannels != 3)
		return 0;

	if (pCapturedBitmap == 0)
	{
		pCapturedBitmap = ::new Gdiplus::Bitmap(gWidth, gHeight, PixelFormat24bppRGB);
	}
	else if (gWidth != pCapturedBitmap->GetWidth() || gHeight != pCapturedBitmap->GetHeight())
	{
		//int w = pCapturedBitmap->GetWidth();
		//int h = pCapturedBitmap->GetHeight();

		::delete pCapturedBitmap;
		//delete pCapturedBitmap;
		pCapturedBitmap = ::new Gdiplus::Bitmap(gWidth, gHeight, PixelFormat24bppRGB);
	}
	
	if (pBufferSize != gWidth * gHeight * gChannels)
		return 0;

	//sgSetBitmapData(pCapturedBitmap, pBuffer);
	//return pCapturedBitmap;

	if (sgSetBitmapData(pCapturedBitmap, pBuffer) == 0)
		return pCapturedBitmap;
	else
		return 0;
}

//takeWebcamPicture
unsigned char* CWebcamTestMfcDlg::sgGrabData()
{
	HRESULT hr;

	if (pGrabber == 0)
		return 0;

	long Size = 0;
	hr = pGrabber->GetCurrentBuffer(&Size, NULL);
	if (FAILED(hr))
		return 0;
	else if (Size != pBufferSize)
	{
		pBufferSize = Size;
		if (pBuffer != 0)
			delete[] pBuffer;
		pBuffer = new unsigned char[pBufferSize];
	}

	hr = pGrabber->GetCurrentBuffer(&pBufferSize, (long*)pBuffer);
	if (FAILED(hr))
		return 0;
	else
	{
		sgFlipUpDown(pBuffer);
		return pBuffer;
	}
}

bool CWebcamTestMfcDlg::sgGrabDataAndSaveToFile()
{
	bool ret = false;
	HRESULT hr;

	if (pGrabber == 0)
		return ret;

	long Size = 0;
	hr = pGrabber->GetCurrentBuffer(&Size, NULL);
	if (FAILED(hr))
	{
		return ret;
	}
	else if (Size != pBufferSize)
	{
		pBufferSize = Size;
		if (pBuffer != 0)
			delete[] pBuffer;
		pBuffer = new unsigned char[pBufferSize];
	}

	hr = pGrabber->GetCurrentBuffer(&pBufferSize, (long*)pBuffer);
	if (FAILED(hr))
	{
		return ret;
	}
	else
	{
		// https://www.codeproject.com/Articles/43024/Capture-image-from-a-streaming-URL-using-different
		// Save the grabed Data to a JGP-file
		AM_MEDIA_TYPE mt;
		ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
		hr = pGrabber->GetConnectedMediaType(&mt);
		if (FAILED(hr))
		{
			// Return error code.
			return ret;
		}
		// Examine the format block.
		VIDEOINFOHEADER *pVih_ = NULL;
		if ((mt.formattype == FORMAT_VideoInfo) &&
			(mt.cbFormat >= sizeof(VIDEOINFOHEADER)) &&
			(mt.pbFormat != NULL))
		{
			pVih_ = (VIDEOINFOHEADER*)mt.pbFormat;
		}
		else
		{
			return ret;
		}

		// Simply save image data as a Bitmap.
		HANDLE hFile;
		BITMAPFILEHEADER bmphdr;
		DWORD nWritten;

		memset(&bmphdr, 0, sizeof(bmphdr));

		bmphdr.bfType = ('M' << 8) | 'B';
		bmphdr.bfSize = sizeof(bmphdr) + sizeof(BITMAPINFOHEADER) + pBufferSize;
		bmphdr.bfOffBits = sizeof(bmphdr) + sizeof(BITMAPINFOHEADER);

		hFile = CreateFile(_T("file.jpg"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			//delete[] pBuffer; // sgCloseSampleGrabber
			return ret;
		}

		if (
			WriteFile(hFile, &bmphdr, sizeof(bmphdr), &nWritten, NULL)
			&& WriteFile(hFile, &pVih_->bmiHeader, sizeof(BITMAPINFOHEADER), &nWritten, NULL)
			&& WriteFile(hFile, pBuffer, pBufferSize, &nWritten, NULL)
			)
		{
			ret = true;
		}
		
		CloseHandle(hFile);
		//delete[] pBuffer; // sgCloseSampleGrabber
	}

	return ret;
}

//takeWebcamPicture
bool CWebcamTestMfcDlg::sgSaveDataToFile(Gdiplus::Bitmap *pBitmap)
{
	bool ret = false;
	
	if (pBitmap == 0)
		return ret;

	CLSID pBmpEncoderType;
	//Save to PNG
	CLSIDFromString(L"{557CF406-1A04-11D3-9A73-0000F81EF32E}", &pBmpEncoderType);
	//and here's IDs for other formats:
	//bmp: {557cf400 - 1a04 - 11d3 - 9a73 - 0000f81ef32e}
	//jpg: {557cf401 - 1a04 - 11d3 - 9a73 - 0000f81ef32e}
	//gif: {557cf402 - 1a04 - 11d3 - 9a73 - 0000f81ef32e}
	//tif: {557cf405 - 1a04 - 11d3 - 9a73 - 0000f81ef32e}
	//png: {557cf406 - 1a04 - 11d3 - 9a73 - 0000f81ef32e}

	if (pBmpEncoderType != GUID_NULL)
	{
		if( Gdiplus::Status::Ok == pBitmap->Save(L"file.png", &pBmpEncoderType, NULL) )
		{
			ret = true;
		}
	}

	return ret;
}


void CWebcamTestMfcDlg::takeWebcamPicture()
{
	HRESULT hr;

	HWND curHwnd = NULL;
	HWND nxtHwnd = NULL;
	hr = vcCaptureVideo(curHwnd, nxtHwnd);
	if (hr != S_OK)
	{
		vcStopCaptureVideo();
		return;
	}

	int num_of_cycles = 100;
	//Sleep(3000);

	while (true)
	{
		Sleep(10);

		/*
		unsigned char* pData = sgGrabData();
		if (pData != 0)
		{
			if(sgSaveDataToFile(sgGetBitmap()))
				break;
		}
		//*/

		if (sgGrabDataAndSaveToFile())
			break;

		num_of_cycles--;
		if (!num_of_cycles)
			break;
	}

	//Close Capture
	vcStopCaptureVideo();
}

/*
void CWebcamTestMfcDlg::StartWebcam()
{
	//int vType;
	// If Previous mode is Video then Close all interfaces
	//if (vType == 0)
		CloseInterfaces();
	vType = 1; // Initializing current capture device to WebCam

			   // Initializing Interfaces and Capture using WebCam
	HRESULT hr = CaptureVideoByMoniker();
	if (FAILED(hr))
	{
		//AfxMessageBox("No Webcam Found.!") ;
		return;
	}
}
*/