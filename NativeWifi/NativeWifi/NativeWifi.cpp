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
#include<winhttp.h>

// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

HANDLE hClient = NULL;
GUID interfaceGUID = { 0 };
VOID WINAPI Noti_Callback(PWLAN_NOTIFICATION_DATA data, PVOID context);
void HttpRequest();

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

	DOT11_SSID dot11_ssid = { 0 };
	//variable used for WlanConnect

	PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
	PWLAN_INTERFACE_INFO pIfInfo = NULL;
	// variables used for WlanQueryInterfaces for opcode = wlan_intf_opcode_current_connection

	PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

	WLAN_CONNECTION_NOTIFICATION_DATA* connect_noti_data;

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
				if(!pBssEntry->bSecurityEnabled)
					ussid = (pBssEntry->dot11Ssid.ucSSID);
				
			}
			
		}
	}

	if (pIfList != NULL) {
		WlanFreeMemory(pIfList);
		pIfList = NULL;
	}	
	while (1);
	
	return dwRetVal;
}

VOID WINAPI Noti_Callback(PWLAN_NOTIFICATION_DATA data, PVOID context)
{
	DWORD dwResult = 0;
	WLAN_CONNECTION_PARAMETERS conn_params;
	memset(&conn_params, 0, sizeof(WLAN_CONNECTION_PARAMETERS));

	WLAN_MSM_NOTIFICATION_DATA* conn_data = NULL;
	WCHAR* ssid = NULL;

	if ((data->NotificationSource) == WLAN_NOTIFICATION_SOURCE_MSM) {
		switch (data->NotificationCode) {
		case wlan_notification_msm_roaming_start:
			if (context == NULL)
				wprintf(L"Callback context NULL");
			conn_data = (WLAN_MSM_NOTIFICATION_DATA*)data->pData;
			conn_params.dot11BssType = conn_data->dot11BssType;
			conn_params.pDot11Ssid = &conn_data->dot11Ssid;
			conn_params.strProfile = conn_data->strProfileName;
			conn_params.wlanConnectionMode = conn_data->wlanConnectionMode;
			WlanConnect(hClient, &interfaceGUID, &conn_params, NULL);
			if (dwResult != ERROR_SUCCESS) {
				wprintf(L"WlanOpenHandle failed with error: %u\n", dwResult);
				return;
			}
			memset(&conn_params, 0, sizeof(WLAN_CONNECTION_PARAMETERS));
			break;

		default:
			break;
		}
	}
}

void HttpRequest()
{

}


