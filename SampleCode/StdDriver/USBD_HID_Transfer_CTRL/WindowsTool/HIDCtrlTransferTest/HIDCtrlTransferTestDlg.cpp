// HIDCtrlTransferTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HIDCtrlTransferTest.h"
#include "HIDCtrlTransferTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern "C" {

// This file is in the Windows DDK available from Microsoft.
#include "hidsdi.h"

#include "setupapi.h"
#include <dbt.h>
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHIDCtrlTransferTestDlg dialog

CHIDCtrlTransferTestDlg::CHIDCtrlTransferTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHIDCtrlTransferTestDlg::IDD, pParent)
{
	
	m_ProductIDString = _T("0520");
	m_VendorIDString = _T("0416");

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//Application global variables 


HIDP_CAPS							Capabilities;
PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
HANDLE								DeviceHandle;
DWORD								dwError;
HANDLE								hEventObject;
HANDLE								hDevInfo;
GUID								HidGuid;
OVERLAPPED							HIDOverlapped;
char								InputReport[256];
ULONG								Length;
LPOVERLAPPED						lpOverLap;
bool								MyDeviceDetected = FALSE; 
CString								MyDevicePathName;
DWORD								NumberOfBytesRead;
char								OutputReport[256];
HANDLE								ReadHandle;
ULONG								Required;
HANDLE								WriteHandle;


int VendorID = 0x0416;
int ProductID = 0x5020;

void CHIDCtrlTransferTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_VendorIDString);
	DDX_Text(pDX, IDC_EDIT2, m_ProductIDString);
	DDX_Control(pDX, IDC_BUTTON3, m_SendAndReceive);
	DDX_Control(pDX, IDC_LIST2, m_ResultsList);
}

BEGIN_MESSAGE_MAP(CHIDCtrlTransferTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_BUTTON1, &CHIDCtrlTransferTestDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT2, &CHIDCtrlTransferTestDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHIDCtrlTransferTestDlg::OnBnClickedButton3)
	ON_WM_TIMER()

	ON_MESSAGE(WM_DEVICECHANGE, Main_OnDeviceChange)
END_MESSAGE_MAP()


// CHIDCtrlTransferTestDlg message handlers

BOOL CHIDCtrlTransferTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	MyDeviceDetected=FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHIDCtrlTransferTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHIDCtrlTransferTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHIDCtrlTransferTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHIDCtrlTransferTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//The timer event.
	//Read and Write one pair of reports.

	ReadAndWriteToDevice();
	CDialog::OnTimer(nIDEvent);
}

void CHIDCtrlTransferTestDlg::DisplayData(CString cstrDataToDisplay)
{
	//Display data in the log List Box

	USHORT	Index;
	Index=m_ResultsList.InsertString(-1, (LPCTSTR)cstrDataToDisplay);
	ScrollToBottomOfListBox(Index);
}

BOOL CHIDCtrlTransferTestDlg::DeviceNameMatch(LPARAM lParam)
{

	// Compare the device path name of a device recently attached or removed 
	// with the device path name of the device we want to communicate with.
	
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;

	DisplayData(_T("MyDevicePathName = ") + MyDevicePathName);

	if (lpdb->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) 
	{
		
		PDEV_BROADCAST_DEVICEINTERFACE lpdbi = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;

		
		CString DeviceNameString;

		//The dbch_devicetype parameter indicates that the event applies to a device interface.
		//So the structure in LParam is actually a DEV_BROADCAST_INTERFACE structure, 
		//which begins with a DEV_BROADCAST_HDR.

		//The dbcc_name parameter of DevBroadcastDeviceInterface contains the device name. 
 
		//Compare the name of the newly attached device with the name of the device 
		//the application is accessing (myDevicePathName).

		DeviceNameString = lpdbi->dbcc_name;

		DisplayData(_T("DeviceNameString = ") + DeviceNameString);


		if ((DeviceNameString.CompareNoCase(MyDevicePathName)) == 0)

		{
			//The name matches.

            return true;
		}
		else
		{
            //It's a different device.

            return false;
    	}
		
	}
	else
	{
		return false;
	}	
}

void CHIDCtrlTransferTestDlg::CloseHandles()
{
	//Close open handles.

	if (DeviceHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(DeviceHandle);
	}

	if (ReadHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(ReadHandle);
	}

	if (WriteHandle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(WriteHandle);
	}
}

LRESULT CHIDCtrlTransferTestDlg::Main_OnDeviceChange(WPARAM wParam, LPARAM lParam)  
{
  
	//DisplayData("Device change detected.");

	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;

	switch(wParam) 
	{
		// Find out if a device has been attached or removed.
		// If yes, see if the name matches the device path name of the device we want to access.

		case DBT_DEVICEARRIVAL:
			DisplayData(_T("A device has been attached."));

			if (DeviceNameMatch(lParam))
			{
				DisplayData(_T("Device has been attached."));
			}
		
			return TRUE; 
	
		case DBT_DEVICEREMOVECOMPLETE:
			DisplayData(_T("Device has been removed."));

			if (DeviceNameMatch(lParam))
			{
				DisplayData(_T("Device has been removed."));

				// Look for the device on the next transfer attempt.

				MyDeviceDetected = false;
			}
			return TRUE; 
	
		default:
			return TRUE; 
	} 
}

void CHIDCtrlTransferTestDlg::GetDeviceCapabilities()
{
	//Get the Capabilities structure for the device.
	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	API function: HidD_GetPreparsedData
	Returns: a pointer to a buffer containing the information about the device's capabilities.
	Requires: A handle returned by CreateFile.
	There's no need to access the buffer directly,
	but HidP_GetCaps and other API functions require a pointer to the buffer.
	*/

	HidD_GetPreparsedData (DeviceHandle, &PreparsedData);

	/*
	API function: HidP_GetCaps
	Learn the device's capabilities.
	For standard devices such as joysticks, you can find out the specific
	capabilities of the device.
	For a custom device, the software will probably know what the device is capable of,
	and the call only verifies the information.
	Requires: the pointer to the buffer returned by HidD_GetPreparsedData.
	Returns: a Capabilities structure containing the information.
	*/
	
	HidP_GetCaps(PreparsedData, &Capabilities);	
	HidD_FreePreparsedData(PreparsedData);
}

void CHIDCtrlTransferTestDlg::DisplayInputReport()
{
	USHORT	ByteNumber;
	CHAR	ReceivedByte;

	//Display the received data in the log and the Bytes Received List boxes.
	//Start at the top of the List Box.

	//	m_ResultsList.ResetContent();

	//Step through the received bytes and display each.

	for (ByteNumber=0; ByteNumber < Capabilities.InputReportByteLength; ByteNumber++)
	{
		//Get a byte.
		ReceivedByte = InputReport[ByteNumber];

		//Display it.
		if(ByteNumber>0)
			DisplayReceivedData(ReceivedByte);
	}
	DisplayData(_T("HID Transfer test ok!"));
}

void CHIDCtrlTransferTestDlg::DisplayReceivedData(char ReceivedByte)
{
	//Display data received from the device.

	CString	strByteRead;

	//Convert the value to a 2-character Cstring.

	strByteRead.Format(_T("%02X"), ReceivedByte);
	strByteRead = strByteRead.Right(2); 

	//Display the value in the Bytes Received List Box.
	m_ResultsList.InsertString(-1, strByteRead);
}

void CHIDCtrlTransferTestDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	ConnectHID();
}

bool CHIDCtrlTransferTestDlg::ConnectHID()
{
	//Use a series of API calls to find a HID with a specified Vendor IF and Product ID.

	HIDD_ATTRIBUTES						Attributes;
	DWORD								DeviceUsage;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	int									MemberIndex = 0;
	LONG								Result;	
	CString								UsageDescription;
	CString								DebugStr;

	Length = 0;
	detailData = NULL;
	DeviceHandle=NULL;

	/*
	API function: HidD_GetHidGuid
	Get the GUID for all system HIDs.
	Returns: the GUID in HidGuid.
	*/

	HidD_GetHidGuid(&HidGuid);	
	
	/*
	API function: SetupDiGetClassDevs
	Returns: a handle to a device information set for all installed devices.
	Requires: the GUID returned by GetHidGuid.
	*/
	
	hDevInfo=SetupDiGetClassDevs 
		(&HidGuid, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		
	devInfoData.cbSize = sizeof(devInfoData);

	//Step through the available devices looking for the one we want. 
	//Quit on detecting the desired device or checking all available devices without success.

	MemberIndex = 0;
	LastDevice = FALSE;

	do
	{
		/*
		API function: SetupDiEnumDeviceInterfaces
		On return, MyDeviceInterfaceData contains the handle to a
		SP_DEVICE_INTERFACE_DATA structure for a detected device.
		Requires:
		The DeviceInfoSet returned in SetupDiGetClassDevs.
		The HidGuid returned in GetHidGuid.
		An index to specify a device.
		*/

		Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo, 
			0, 
			&HidGuid, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{
			//A device has been detected, so get more information about it.

			/*
			API function: SetupDiGetDeviceInterfaceDetail
			Returns: an SP_DEVICE_INTERFACE_DETAIL_DATA structure
			containing information about a device.
			To retrieve the information, call this function twice.
			The first time returns the size of the structure in Length.
			The second time returns a pointer to the data in DeviceInfoSet.
			Requires:
			A DeviceInfoSet returned by SetupDiGetClassDevs
			The SP_DEVICE_INTERFACE_DATA structure returned by SetupDiEnumDeviceInterfaces.
			
			The final parameter is an optional pointer to an SP_DEV_INFO_DATA structure.
			This application doesn't retrieve or use the structure.			
			If retrieving the structure, set 
			MyDeviceInfoData.cbSize = length of MyDeviceInfoData.
			and pass the structure's address.
			*/
			
			//Get the Length value.
			//The call will return with a "buffer too small" error which can be ignored.

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				NULL, 
				0, 
				&Length, 
				NULL);

			//Allocate memory for the hDevInfo structure, using the returned Length.

			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
			
			//Set cbSize in the detailData structure.

			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//Call the function again, this time passing it the returned buffer size.

			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				detailData, 
				Length, 
				&Required, 
				NULL);

			// Open a handle to the device.
			// To enable retrieving information about a system mouse or keyboard,
			// don't request Read or Write access for this handle.

			/*
			API function: CreateFile
			Returns: a handle that enables reading and writing to the device.
			Requires:
			The DevicePath in the detailData structure
			returned by SetupDiGetDeviceInterfaceDetail.
			*/

			DeviceHandle=CreateFile 
				(detailData->DevicePath, 
				0, 
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING, 
				0, 
				NULL);

			/*
			API function: HidD_GetAttributes
			Requests information from the device.
			Requires: the handle returned by CreateFile.
			Returns: a HIDD_ATTRIBUTES structure containing
			the Vendor ID, Product ID, and Product Version Number.
			Use this information to decide if the detected device is
			the one we're looking for.
			*/

			//Set the Size to the number of bytes in the structure.

			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes 
				(DeviceHandle, 
				&Attributes);

			//Is it the desired device?

			MyDeviceDetected = FALSE;
					
			if (Attributes.VendorID == VendorID)
			{
				if (Attributes.ProductID == ProductID)
				{
					//Both the Vendor ID and Product ID match.

					MyDeviceDetected = TRUE;
					MyDevicePathName = detailData->DevicePath;
					DisplayData(_T("Device detected"));

					//Register to receive device notifications.

					RegisterForDeviceNotifications();

					//Get the device's capablities.
					GetDeviceCapabilities();

					// 利用HID Report Descriptor來辨識HID Transfer裝置   
					DeviceUsage = (Capabilities.UsagePage * 256) + Capabilities.Usage;   

					if (DeviceUsage != 0xFF0001)   // Report Descriptor
						continue;

					// Get a handle for writing Output reports.
					WriteHandle=CreateFile 
						(detailData->DevicePath, 
						GENERIC_WRITE, 
						FILE_SHARE_READ|FILE_SHARE_WRITE, 
						(LPSECURITY_ATTRIBUTES)NULL,
						OPEN_EXISTING, 
						0, 
						NULL);

					// Prepare to read reports using Overlapped I/O.

					PrepareForOverlappedTransfer();

				} //if (Attributes.ProductID == ProductID)

				else
					//The Product ID doesn't match.

					CloseHandle(DeviceHandle);

			} //if (Attributes.VendorID == VendorID)

			else
				//The Vendor ID doesn't match.

				CloseHandle(DeviceHandle);

		//Free the memory used by the detailData structure (no longer needed).

		free(detailData);

		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.
			LastDevice=TRUE;

		//If we haven't found the device yet, and haven't tried every available device,
		//try the next one.

		MemberIndex = MemberIndex + 1;

	} //do

	while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));

	if (MyDeviceDetected == FALSE)
		DisplayData(_T("Device not detected"));
	else
		DisplayData(_T("Device detected"));

	//Free the memory reserved for hDevInfo by SetupDiClassDevs.
	SetupDiDestroyDeviceInfoList(hDevInfo);

	return MyDeviceDetected;
}

void CHIDCtrlTransferTestDlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CString ProductIDtext;
    
	// Get the text in the edit box.
	CEdit* m_ProductID1 = (CEdit*) GetDlgItem(IDC_EDIT2);
	m_ProductID1->GetWindowText(ProductIDtext); 

	// Convert the hex string in the edit box to an integer.
	ProductID = wcstoul(ProductIDtext, 0, 16);

	MyDeviceDetected=false;
}

void CHIDCtrlTransferTestDlg::RegisterForDeviceNotifications()
{

	// Request to receive messages when a device is attached or removed.
	// Also see WM_DEVICECHANGE in BEGIN_MESSAGE_MAP(CUsbhidiocDlg, CDialog).

	DEV_BROADCAST_DEVICEINTERFACE DevBroadcastDeviceInterface;
	HDEVNOTIFY DeviceNotificationHandle;

	DevBroadcastDeviceInterface.dbcc_size = sizeof(DevBroadcastDeviceInterface);
	DevBroadcastDeviceInterface.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	DevBroadcastDeviceInterface.dbcc_classguid = HidGuid;

	DeviceNotificationHandle =
		RegisterDeviceNotification(m_hWnd, &DevBroadcastDeviceInterface, DEVICE_NOTIFY_WINDOW_HANDLE);

}

void CHIDCtrlTransferTestDlg::ScrollToBottomOfListBox(USHORT Index)
{
	/* 
	Scroll to the bottom of the list box. 
	To do so, add a line and set it as the current selection,
	possibly scrolling the window.
	Then deselect the line, 
	leaving the list box scrolled to the bottom with nothing selected.
	*/

	m_ResultsList.SetCurSel( Index );
	m_ResultsList.SetCurSel( -1 );
}

void CHIDCtrlTransferTestDlg::PrepareForOverlappedTransfer()
{
	//Get a handle to the device for the overlapped ReadFiles.

	ReadHandle=CreateFile 
		(detailData->DevicePath, 
		GENERIC_READ, 
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);


	//Get an event object for the overlapped structure.

	/*API function: CreateEvent
	Requires:
	  Security attributes or Null
	  Manual reset (true). Use ResetEvent to set the event object's state to non-signaled.
	  Initial state (true = signaled) 
	  Event object name (optional)
	Returns: a handle to the event object
	*/

	if (hEventObject == 0)
	{
		hEventObject = CreateEvent 
						(NULL, 
						TRUE, 
						TRUE, 
						_T(""));

		//Set the members of the overlapped structure.
		HIDOverlapped.hEvent = hEventObject;
		HIDOverlapped.Offset = 0;
		HIDOverlapped.OffsetHigh = 0;
	}
}
void CHIDCtrlTransferTestDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//Click the Continuous button to
	//begin or stop requesting and sending periodic reports.

	CString Caption;

	//Find out whether Continuous is currently selected 
	//and take appropriate action.

	m_SendAndReceive.GetWindowText(Caption);
    //ReadAndWriteToDevice();

	 if (Caption == _T("Start"))
	 {
		//Enable periodic exchanges of reports.
		//Change the button caption.

		m_SendAndReceive.SetWindowText(_T("Stop"));

		//Start by reading and writing one pair of reports.

		ReadAndWriteToDevice();

		//Enable the timer to cause periodic exchange of reports.
		//The second parameter is the number of milliseconds between report requests.

		SetTimer(ID_CLOCK_TIMER, 5000, NULL);
	}
	else
	{
		//Stop periodic exchanges of reports.
		//Change the button caption.

		m_SendAndReceive.SetWindowText(_T("Start"));

		//Disable the timer.

		KillTimer(ID_CLOCK_TIMER);
	}
}

void CHIDCtrlTransferTestDlg::ReadAndWriteToDevice()
{
	//If necessary, find the device and learn its capabilities.
	//Then send a report and request a report.
	DisplayData(_T("***HID Test Report***"));

	//If the device hasn't been detected already, look for it.

	if (MyDeviceDetected == FALSE)
	{
		MyDeviceDetected = ConnectHID();
	}

	// Do nothing if the device isn't detected.

	if (MyDeviceDetected==TRUE)
	{
		// Output and Input Reports

		//Write a report to the device.
		WriteOutputReport();

		//Read a report from the device.
		ReadInputReport();	
	}
}


void CHIDCtrlTransferTestDlg::WriteOutputReport()
{
	//Send a report to the device.

	DWORD	BytesWritten = 0;
	INT		Index =0;
	ULONG	Result;
	CString	strBytesWritten = _T("");
	INT BufSize = 0;

	UpdateData(true);

	for(int i = 0; i < 64; i++)
		OutputReport[i] = i;
	BufSize = 64;

	//Send a report to the device.

	/*
	HidD_SetOutputReport
	Sends a report to the device.
	Returns: success or failure.
	Requires:
	The device handle returned by CreateFile.
	A buffer that holds the report.
	The Output Report length returned by HidP_GetCaps,
	*/

	if (WriteHandle != INVALID_HANDLE_VALUE)
	{
		Result = HidD_SetOutputReport
		(WriteHandle,
		OutputReport,
		Capabilities.OutputReportByteLength);
	}

	if (Result)
	{
		DisplayData(_T("An Output report was written to the device."));
	}
	else
	{
		//The write attempt failed, so close the handles, display a message,
		//and set MyDeviceDetected to FALSE so the next attempt will look for the device.
		CloseHandles();
		DisplayData(_T("Can't write to device"));
		MyDeviceDetected = FALSE;
	}
}

void CHIDCtrlTransferTestDlg::ReadInputReport()
{

	// Retrieve an Input report from the device.

	CString	ByteToDisplay = _T("");

	DWORD	Result;

	// Find out if the "Use Control Transfers Only" check box is checked.

	UpdateData(true);

	//Read a report from the device using a control transfer.
	
	/*
	HidD_GetInputReport
	Returns:
	True on success
	Requires: 
	A device handle returned by CreateFile.
	A buffer to hold the report.
	The report length returned by HidP_GetCaps in Capabilities.InputReportByteLength.
	*/
	
	if (ReadHandle != INVALID_HANDLE_VALUE)
	{
		Result = HidD_GetInputReport
		(ReadHandle,
		InputReport,
		Capabilities.InputReportByteLength);
	}
	else
	{
		Result = FALSE;
	}

	if (!Result)
	{
		//The read attempt failed, so close the handles, display a message,
		//and set MyDeviceDetected to FALSE so the next attempt will look for the device.
		CloseHandles();
		DisplayData(_T("Can't read from device"));
		MyDeviceDetected = FALSE;
	}
	else
	{
		DisplayData(_T("Received Input report: "));
		
		//Display the report data.
		DisplayInputReport();
	
	}
}
