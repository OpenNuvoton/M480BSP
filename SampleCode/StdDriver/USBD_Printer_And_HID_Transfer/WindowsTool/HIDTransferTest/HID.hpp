#ifndef INC__HID_HPP__
#define INC__HID_HPP__

#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include "dbt.h"

extern "C" {
#include "setupapi.h"
#include "hidsdi.h"
}


#define HID_MAX_PACKET_SIZE_EP 64
#define V6M_MAX_COMMAND_LENGTH (HID_MAX_PACKET_SIZE_EP - 2)

class CHidIO
{
protected:
	HANDLE m_hReadHandle;
	HANDLE m_hWriteHandle;
	HANDLE m_hReadEvent;
	HANDLE m_hWriteEvent;
	HANDLE m_hAbordEvent;
public:

	CHidIO()
		: m_hReadHandle(INVALID_HANDLE_VALUE)
		, m_hWriteHandle(INVALID_HANDLE_VALUE)
		, m_hAbordEvent(CreateEvent(NULL,TRUE,FALSE,NULL))
		, m_hReadEvent(CreateEvent(NULL,TRUE,FALSE,NULL))
		, m_hWriteEvent(CreateEvent(NULL,TRUE,FALSE,NULL))
	{
	}
	virtual ~CHidIO()
	{
		CloseDevice();
		CloseHandle(m_hWriteEvent);
		CloseHandle(m_hReadEvent);
		CloseHandle(m_hAbordEvent);
	}

	void CloseDevice()
	{
		if(m_hReadHandle != INVALID_HANDLE_VALUE)
			CancelIo(m_hReadHandle);
		if(m_hWriteHandle != INVALID_HANDLE_VALUE)
			CancelIo(m_hWriteHandle);
		if(m_hReadHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hReadHandle);
			m_hReadHandle = INVALID_HANDLE_VALUE;
		}
		if(m_hWriteHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hWriteHandle);
			m_hWriteHandle = INVALID_HANDLE_VALUE;
		}
	}

	HIDP_CAPS	Capabilities;

	BOOL OpenDevice(USHORT usVID, USHORT usPID)
	{				
        DWORD                               DeviceUsage; 
		TCHAR MyDevPathName[MAX_PATH];
		//Get the Capabilities structure for the device.   	   
		PHIDP_PREPARSED_DATA    PreparsedData;   

		//定義一個GUID的結構體HidGuid來保存HID設備的接口類GUID。
		GUID HidGuid;
		//定義一個DEVINFO的句柄hDevInfoSet來保存獲取到的設備信息集合句柄。
		HDEVINFO hDevInfoSet;
		//定義MemberIndex，表示當前搜索到第幾個設備，0表示第一個設備。
		DWORD MemberIndex;
		//DevInterfaceData，用來保存設備的驅動接口信息
		SP_DEVICE_INTERFACE_DATA DevInterfaceData;
		//定義一個BOOL變量，保存函數調用是否返回成功
		BOOL Result;
		//定義一個RequiredSize的變量，用來接收需要保存詳細信息的緩衝長度。
		DWORD RequiredSize;
		//定義一個指向設備詳細信息的結構體指針。
		PSP_DEVICE_INTERFACE_DETAIL_DATA	pDevDetailData;
		//定義一個用來保存打開設備的句柄。
		HANDLE hDevHandle;
		//定義一個HIDD_ATTRIBUTES的結構體變量，保存設備的屬性。
		HIDD_ATTRIBUTES DevAttributes;
		
		//初始化設備未找到
		BOOL MyDevFound=FALSE;
		
		//初始化讀、寫句柄為無效句柄。
		m_hReadHandle=INVALID_HANDLE_VALUE;
		m_hWriteHandle=INVALID_HANDLE_VALUE;
		
		//對DevInterfaceData結構體的cbSize初始化為結構體大小
		DevInterfaceData.cbSize=sizeof(DevInterfaceData);
		//對DevAttributes結構體的Size初始化為結構體大小
		DevAttributes.Size=sizeof(DevAttributes);
		
		//調用HidD_GetHidGuid函數獲取HID設備的GUID，並保存在HidGuid中。
		HidD_GetHidGuid(&HidGuid);
		
		//根據HidGuid來獲取設備信息集合。其中Flags參數設置為
		//DIGCF_DEVICEINTERFACE|DIGCF_PRESENT，前者表示使用的GUID為
		//接口類GUID，後者表示只列舉正在使用的設備，因為我們這裡只
		//查找已經連接上的設備。返回的句柄保存在hDevinfo中。注意設備
		//信息集合在使用完畢後，要使用函數SetupDiDestroyDeviceInfoList
		//銷毀，不然會造成內存洩漏。
		hDevInfoSet=SetupDiGetClassDevs(&HidGuid,
			NULL,
			NULL,
			DIGCF_DEVICEINTERFACE|DIGCF_PRESENT);
		
		//AddToInfOut("開始查找設備");
		//然後對設備集合中每個設備進行列舉，檢查是否是我們要找的設備
		//當找到我們指定的設備，或者設備已經查找完畢時，就退出查找。
		//首先指向第一個設備，即將MemberIndex置為0。
		MemberIndex=0;
		while(1)
		{
			//調用SetupDiEnumDeviceInterfaces在設備信息集合中獲取編號為
			//MemberIndex的設備信息。
			Result=SetupDiEnumDeviceInterfaces(hDevInfoSet,
				NULL,
				&HidGuid,
				MemberIndex,
				&DevInterfaceData);
			
			//如果獲取信息失敗，則說明設備已經查找完畢，退出循環。
			if(Result==FALSE) break;
			
			//將MemberIndex指向下一個設備
			MemberIndex++;
			
			//如果獲取信息成功，則繼續獲取該設備的詳細信息。在獲取設備
			//詳細信息時，需要先知道保存詳細信息需要多大的緩衝區，這通過
			//第一次調用函數SetupDiGetDeviceInterfaceDetail來獲取。這時
			//提供緩衝區和長度都為NULL的參數，並提供一個用來保存需要多大
			//緩衝區的變量RequiredSize。
			Result=SetupDiGetDeviceInterfaceDetail(hDevInfoSet,
				&DevInterfaceData,
				NULL,
				NULL,
				&RequiredSize,
				NULL);
			
			//然後，分配一個大小為RequiredSize緩衝區，用來保存設備詳細信息。
			pDevDetailData=(PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(RequiredSize);
			if(pDevDetailData==NULL) //如果內存不足，則直接返回。
			{
				//MessageBox("內存不足!");
				SetupDiDestroyDeviceInfoList(hDevInfoSet);
				return FALSE;
			}
			
			//並設置pDevDetailData的cbSize為結構體的大小（注意只是結構體大小，
			//不包括後面緩衝區）。
			pDevDetailData->cbSize=sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			
			//然後再次調用SetupDiGetDeviceInterfaceDetail函數來獲取設備的
			//詳細信息。這次調用設置使用的緩衝區以及緩衝區大小。
			Result=SetupDiGetDeviceInterfaceDetail(hDevInfoSet,
				&DevInterfaceData,
				pDevDetailData,
				RequiredSize,
				NULL,
				NULL);
			
			//將設備路徑複製出來，然後銷毀剛剛申請的內存。
			//MyDevPathName=pDevDetailData->DevicePath;
			//_tcscpy(MyDevPathName, pDevDetailData->DevicePath);
			wcscpy_s(MyDevPathName, pDevDetailData->DevicePath);
            free(pDevDetailData);
			
			//如果調用失敗，則查找下一個設備。
			if(Result==FALSE) continue;
			
			//如果調用成功，則使用不帶讀寫訪問的CreateFile函數
			//來獲取設備的屬性，包括VID、PID、版本號等。
			//對於一些獨佔設備（例如USB鍵盤），使用讀訪問方式是無法打開的，
			//而使用不帶讀寫訪問的格式才可以打開這些設備，從而獲取設備的屬性。
			hDevHandle=CreateFile(MyDevPathName, 
				NULL,
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			
			//如果打開成功，則獲取設備屬性。
			if(hDevHandle!=INVALID_HANDLE_VALUE)
			{
				//獲取設備的屬性並保存在DevAttributes結構體中
				Result=HidD_GetAttributes(hDevHandle,
					&DevAttributes);
				
				//關閉剛剛打開的設備
				//CloseHandle(hDevHandle);
				
				//獲取失敗，查找下一個
				if(Result==FALSE) continue;
				
				//如果獲取成功，則將屬性中的VID、PID以及設備版本號與我們需要的
				//進行比較，如果都一致的話，則說明它就是我們要找的設備。
				if(DevAttributes.VendorID == usVID
					&& DevAttributes.ProductID == usPID){
						
	                        // 利用HID Report Descriptor來辨識HID Transfer裝置 
							HidD_GetPreparsedData(hDevHandle, &PreparsedData);   
			   
							HidP_GetCaps(PreparsedData, &Capabilities);   
		
							HidD_FreePreparsedData(PreparsedData);  
							 DeviceUsage = (Capabilities.UsagePage * 256) + Capabilities.Usage;   
   
							if (DeviceUsage != 0xFF0001)   // Report Descriptor
								continue;

							MyDevFound=TRUE; //設置設備已經找到
							//AddToInfOut("設備已經找到");
							
							//那麼就是我們要找的設備，分別使用讀寫方式打開之，並保存其句柄
							//並且選擇為異步訪問方式。
							
							//讀方式打開設備
							m_hReadHandle=CreateFile(MyDevPathName, 
								GENERIC_READ,
								FILE_SHARE_READ|FILE_SHARE_WRITE, 
								NULL,
								OPEN_EXISTING,
								//FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
								//if(hReadHandle!=INVALID_HANDLE_VALUE)AddToInfOut("讀訪問打開設備成功");
								//else AddToInfOut("讀訪問打開設備失敗");
							
							//寫方式打開設備
							m_hWriteHandle=CreateFile(MyDevPathName, 
								GENERIC_WRITE,
								FILE_SHARE_READ|FILE_SHARE_WRITE, 
								NULL,
								OPEN_EXISTING,
								//FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED,
								FILE_ATTRIBUTE_NORMAL,
								NULL);
								//if(hWriteHandle!=INVALID_HANDLE_VALUE)AddToInfOut("寫訪問打開設備成功");
								//else AddToInfOut("寫訪問打開設備失敗");
							
						
							//手動觸發事件，讓讀報告線程恢復運行。因為在這之前並沒有調用
							//讀數據的函數，也就不會引起事件的產生，所以需要先手動觸發一
							//次事件，讓讀報告線程恢復運行。
							//SetEvent(ReadOverlapped.hEvent);
							
							//顯示設備的狀態。
							//SetDlgItemText(IDC_DS,"設備已打開");
							
							//找到設備，退出循環。本程序只檢測一個目標設備，查找到後就退出
							//查找了。如果你需要將所有的目標設備都列出來的話，可以設置一個
							//數組，找到後就保存在數組中，直到所有設備都查找完畢才退出查找
							break;
						}
			}
			//如果打開失敗，則查找下一個設備
			else //continue;
			{
				CloseHandle(hDevHandle);
				continue;
			}
		}
		
		//調用SetupDiDestroyDeviceInfoList函數銷毀設備信息集合
		SetupDiDestroyDeviceInfoList(hDevInfoSet);
	
		//如果設備已經找到，那麼應該使能各操作按鈕，並同時禁止打開設備按鈕
		return MyDevFound;
	}


	BOOL ReadFile(char *pcBuffer, DWORD szMaxLen, DWORD *pdwLength, DWORD dwMilliseconds)
	{
		HANDLE events[2] = {m_hAbordEvent, m_hReadEvent};

		OVERLAPPED overlapped;
		memset(&overlapped, 0, sizeof(overlapped));
		overlapped.hEvent = m_hReadEvent;

		if(pdwLength != NULL)
			*pdwLength = 0;
		
		if(!::ReadFile(m_hReadHandle, pcBuffer, szMaxLen, NULL, &overlapped))
			return FALSE;
		DWORD dwIndex = WaitForMultipleObjects(2, events, FALSE, dwMilliseconds);
		if(dwIndex == WAIT_OBJECT_0
			|| dwIndex == WAIT_OBJECT_0 + 1)
		{
			ResetEvent(events[dwIndex - WAIT_OBJECT_0]);

			if(dwIndex == WAIT_OBJECT_0)
				return FALSE;	//Abort event
			else
			{
				DWORD dwLength = 0;
				//Read OK
				GetOverlappedResult(m_hReadHandle, &overlapped, &dwLength, TRUE);
				if(pdwLength != NULL)
					*pdwLength = dwLength;
				return TRUE;
			}				
		}
		else
			return FALSE;
	}

	BOOL WriteFile(const char *pcBuffer, DWORD szLen, DWORD *pdwLength, DWORD dwMilliseconds)
	{
		HANDLE events[2] = {m_hAbordEvent, m_hWriteEvent};
        
		OVERLAPPED overlapped;
		memset(&overlapped, 0, sizeof(overlapped));
		overlapped.hEvent = m_hWriteEvent;

		if(pdwLength != NULL)
			*pdwLength = 0;

		DWORD dwStart2 = GetTickCount();

		if(!::WriteFile(m_hWriteHandle, pcBuffer, szLen, NULL, &overlapped))
			return FALSE;

		DWORD dwIndex = WaitForMultipleObjects(2, events, FALSE, dwMilliseconds);
		
		if(dwIndex == WAIT_OBJECT_0
			|| dwIndex == WAIT_OBJECT_0 + 1)
		{
			ResetEvent(events[dwIndex - WAIT_OBJECT_0]);

			if(dwIndex == WAIT_OBJECT_0)
				return FALSE;	//Abort event
			else
			{
				DWORD dwLength = 0;
				//Write OK
				GetOverlappedResult(m_hWriteHandle, &overlapped, &dwLength, TRUE);
				if(pdwLength != NULL)
					*pdwLength = dwLength;
				return TRUE;
			}				
		}
		else
			return FALSE;
	}
};



class CHidCmd
{
protected:
	CHAR	m_acBuffer[HID_MAX_PACKET_SIZE_EP + 1];
	CHidIO	m_hidIO;
public:
	CHidCmd()
		: m_hidIO()
	{
	}
	virtual ~CHidCmd()
	{
	}

	void CloseDevice()
	{
		m_hidIO.CloseDevice();
	}

	BOOL OpenDevice(USHORT usVID, USHORT usPID)
	{
		return m_hidIO.OpenDevice(usVID, usPID);
	}

	BOOL ReadFile(unsigned char *pcBuffer, size_t szMaxLen, DWORD *pdwLength, DWORD dwMilliseconds)
	{
        BOOL bRet;

        bRet = m_hidIO.ReadFile(m_acBuffer, sizeof(m_acBuffer), pdwLength, dwMilliseconds);
        (*pdwLength)--;
        memcpy(pcBuffer, m_acBuffer+1, *pdwLength);

		return bRet;
	}

	BOOL WriteFile(unsigned char *pcBuffer, DWORD dwLen, DWORD *pdwLength, DWORD dwMilliseconds)
	{
		/* Set new package index value */
		DWORD dwCmdLength = dwLen;
		if(dwCmdLength > sizeof(m_acBuffer) - 1)
			dwCmdLength = sizeof(m_acBuffer) - 1;
        
        memset(m_acBuffer, 0xCC, sizeof(m_acBuffer));
		m_acBuffer[0] = 0x00;	//Always 0x00
        memcpy(m_acBuffer+1  , pcBuffer, dwCmdLength);
		BOOL bRet = m_hidIO.WriteFile(m_acBuffer, 65, pdwLength, dwMilliseconds);
        if(bRet)
        {
                *pdwLength = *pdwLength - 1;
        }

        return bRet;
	}

};



#endif
