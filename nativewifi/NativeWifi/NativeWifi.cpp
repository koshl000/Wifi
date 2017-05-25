// NativeWifi.cpp : Defines the entry point for the console application.
//

/*
5516	1089.172097	192.168.27.153	180.134.255.8	HTTP	185	GET /?ip=218.239.222.40&mac=08d40ced16fb&url=http://www.msftncsi.com&ap_mac=18bdad133e70 HTTP/1.1

*/
#pragma once

#include <windows.h>
#include <wlanapi.h>
#include <Windot11.h>           // for DOT11_SSID struct
#include <objbase.h>
#include <wtypes.h>

//#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#include<adhoc.h>
#include<process.h>
#include<map>

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")


VOID WINAPI Noti_Callback(PWLAN_NOTIFICATION_DATA data, PVOID context);

typedef struct _threadparams {
	HANDLE networkHandle;
	GUID networkGUID;
}threadparams;

unsigned __stdcall detectConnected(void *pArguments)
{
	threadparams* params = (threadparams*)pArguments;
	

	return 0;
}


int wmain()
{

	// Declare and initialize variables.


	HANDLE ThreadHandle=NULL;
	unsigned threadID=0;

	HANDLE hClient = NULL;
	DWORD dwMaxClient = 2;      //    
	DWORD dwCurVersion = 0;
	DWORD dwResult = 0;
	DWORD dwRetVal = 0;
	int iRet = 0;
	UCHAR* ussid=nullptr;
	char* ssid=nullptr;

	WCHAR GuidString[39] = { 0 };
	TCHAR ssID[25] = { 0 };
	// variables used for WlanEnumInterfaces

	GUID interfaceGUID = { 0 };
	DOT11_SSID dot11_ssid = { 0 };
	//variable used for WlanConnect


	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;
	// variables used for WlanQueryInterfaces for opcode = wlan_intf_opcode_current_connection

	PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

	WLAN_CONNECTION_NOTIFICATION_DATA* connect_noti_data;

	std::map<unsigned int, const TCHAR*> phyType;
	
	phyType.insert(std::pair<unsigned int,const TCHAR*>(0, L"dot11_phy_type_unknown"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(1, L"dot11_phy_type_fhss"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(2, L"dot11_phy_type_dsss"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(3, L"dot11_phy_type_irbaseband"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(4, L"dot11_phy_type_ofdm"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(5, L"dot11_phy_type_hrdsss"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(6, L"dot11_phy_type_erp"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(7, L"dot11_phy_type_ht"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(8, L"dot11_phy_type_vht"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(0x80000000, L"dot11_phy_type_IHV_start"));
	phyType.insert(std::pair<unsigned int, const TCHAR*>(0xffffffff, L"dot11_phy_type_IHV_end"));

	dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);
	if (dwResult != ERROR_SUCCESS) {
		wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
		return 1;
	}

	WlanRegisterNotification(hClient, WLAN_NOTIFICATION_SOURCE_ALL, TRUE, Noti_Callback, (WLAN_CONNECTION_NOTIFICATION_DATA*)&connect_noti_data, NULL, NULL);

	dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
	if (dwResult != ERROR_SUCCESS) {
		wprintf(L"WlanEnumInterfaces failed with error: %u\n", dwResult);
		return 1;
	}
	else {
		for (int i = 0; i < (int)pIfList->dwNumberOfItems; i++) {
			pIfInfo = (WLAN_INTERFACE_INFO *)& pIfList->InterfaceInfo[i];
			interfaceGUID = pIfInfo->InterfaceGuid;
			wprintf(L"  Interface Index[%u]:\t %lu\n", i, i);
			iRet = StringFromGUID2(pIfInfo->InterfaceGuid, (LPOLESTR)& GuidString, sizeof(GuidString) / sizeof(*GuidString));			
			if (iRet == 0)
				wprintf(L"StringFromGUID2 failed\n");
			else {
				wprintf(L"  InterfaceGUID[%d]:\t %ws\n", i, GuidString);
			}

			wprintf(L"  Interface Description[%d]: %ws", i, pIfInfo->strInterfaceDescription);
			wprintf(L"\n");
			wprintf(L"  Interface State[%d]:\t ", i);
			switch (pIfInfo->isState) {
			case wlan_interface_state_not_ready:
				wprintf(L"Not ready\n");
				break;
			case wlan_interface_state_connected:
				wprintf(L"Connected\n");
				break;
			case wlan_interface_state_ad_hoc_network_formed:
				wprintf(L"First node in a ad hoc network\n");
				break;
			case wlan_interface_state_disconnecting:
				wprintf(L"Disconnecting\n");
				break;
			case wlan_interface_state_disconnected:
				wprintf(L"Not connected\n");
				break;
			case wlan_interface_state_associating:
				wprintf(L"Attempting to associate with a network\n");
				break;
			case wlan_interface_state_discovering:
				wprintf(L"Auto configuration is discovering settings for the network\n");
				break;
			case wlan_interface_state_authenticating:
				wprintf(L"In process of authenticating\n");
				break;
			default:
				wprintf(L"Unknown state %ld\n", pIfInfo->isState);
				break;
			}
			wprintf(L"\n");
			
			dwResult = WlanGetAvailableNetworkList(hClient, &interfaceGUID, WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_MANUAL_HIDDEN_PROFILES
				, NULL, &pBssList);

			if (dwResult != ERROR_SUCCESS) {
				wprintf(L"WlanGetAvailableNetworkList failed with error: %u\n",
					dwResult);
				dwRetVal = 1;
				// You can use FormatMessage to find out why the function failed
			}
			for (unsigned int i = 0; i < pBssList->dwNumberOfItems; i++) {
				pBssEntry = &pBssList->Network[i];
				//for(unsigned int i=0;pBssEntry->dot11Ssid.uSSIDLength;++i)
				ussid = (pBssEntry->dot11Ssid.ucSSID);
				
			}
			
		}
	}

	if (pIfList != NULL) {
		WlanFreeMemory(pIfList);
		pIfList = NULL;
	}
	
	PWLAN_CONNECTION_PARAMETERS conn_params = { wlan_connection_mode_auto ,NULL,pBssEntry->dot11Ssid, };

	WlanConnect(hClient, &interfaceGUID, conn_params, NULL);
	
	while (1);
	
	return dwRetVal;
}

VOID WINAPI Noti_Callback(PWLAN_NOTIFICATION_DATA data, PVOID context)
{
	WLAN_CONNECTION_NOTIFICATION_DATA* conn_data = NULL;
	if ((data->NotificationSource) == WLAN_NOTIFICATION_SOURCE_ACM) {
		switch (data->NotificationCode) {
		case wlan_notification_acm_autoconf_disabled:
			if (context == NULL)
				wprintf(L"context NULL");
			wprintf(L"===============CALLBACK_CALL!!================ \n");
			wprintf(L"disConnected...\n");
			break;
		default:
			break;
		}
	}
	MessageBeep(MB_OK);
	wprintf(L"0%d\t", data->NotificationSource);
	wprintf(L"0%d\n", data->NotificationCode);
}
