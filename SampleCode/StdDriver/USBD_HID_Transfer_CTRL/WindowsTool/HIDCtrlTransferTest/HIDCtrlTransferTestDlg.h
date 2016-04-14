// HIDCtrlTransferTestDlg.h : header file
//



#pragma once


// CHIDCtrlTransferTestDlg dialog
class CHIDCtrlTransferTestDlg : public CDialog {
// Construction
public:
    CHIDCtrlTransferTestDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
    enum { IDD = IDD_HIDCTRLTRANSFERTEST_DIALOG };

    CEdit    m_VendorID;
    CEdit    m_ProductID;
    CButton  m_SendAndReceive;
    CListBox m_ResultsList;
    //CString    m_strReceived;
    CString  m_ProductIDString;
    CString  m_VendorIDString;
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()





public:
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnBnClickedButton1();
    afx_msg void OnEnChangeEdit2();

    BOOL DeviceNameMatch(LPARAM lParam);
    bool ConnectHID();
    LRESULT Main_OnDeviceChange(WPARAM wParam, LPARAM lParam);
    void CloseHandles();
    void DisplayCurrentTime();
    void DisplayData(CString cstrDataToDisplay);
    void DisplayFeatureReport();
    void DisplayInputReport();
    void DisplayLastError(CString Operation);
    void DisplayReceivedData(char ReceivedByte);
    void GetDeviceCapabilities();
    void PrepareForOverlappedTransfer();
    void ScrollToBottomOfListBox(USHORT idx);
    void ReadAndWriteToDevice();
    void ReadFeatureReport();
    void ReadInputReport();
    void RegisterForDeviceNotifications();
    void WriteFeatureReport();
    void WriteOutputReport();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
