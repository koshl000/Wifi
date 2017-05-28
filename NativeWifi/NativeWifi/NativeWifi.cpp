#include "NativeWifi.h"

/*

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

	PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
	PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
	PWLAN_AVAILABLE_NETWORK pBssEntry = NULL;

	WLAN_CONNECTION_NOTIFICATION_DATA* connect_noti_data;

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
			wprintf(L"Connected....\n");
			memset(&conn_params, 0, sizeof(WLAN_CONNECTION_PARAMETERS));
			break;

		default:
			break;
		}
	}
	wprintf(L"0x%x \n", data->NotificationSource);
	wprintf(L"%d \n", data->NotificationCode);
}

void HttpRequest()
{

}

*/

AutoWifi::AutoWifi()
{
	memset(&Conn_params, 0, sizeof(PWLAN_CONNECTION_PARAMETERS));
	callbackList.reserve(20);
	try {
		dwResult = WlanOpenHandle(dwClientVersion, NULL, &dwCurVersion, &hClient);
		dwResult = WlanEnumInterfaces(hClient, NULL, &pInterfaceLists);
		if (dwResult != ERROR_SUCCESS) {
			throw dwResult;
		}
		for (unsigned int i = 0; i < pInterfaceLists->dwNumberOfItems; ++i)
		{
			//Ignore rest interface.Only use first Interface 
			if (i >= 1)
				continue;
			pInterfaceInfo = pInterfaceLists->InterfaceInfo[i];
			interfaceGUID = pInterfaceInfo.InterfaceGuid;
			wcout << "Interface Name : " << pInterfaceInfo.strInterfaceDescription << endl;
		}
	}
	catch (Log e) {
		cout << "error :" << e << endl;
	}
}

void AutoWifi::Connect()
{
	switch (pInterfaceInfo.isState) {
	case wlan_interface_state_connected:
		wcout << "Connected..." << endl;
		//continueTracking() //use thread
		break;
	case wlan_interface_state_disconnected:
		wcout << "Disconnected..." << endl;
		//conect()
		break;
	default:
		wcout << "Need to confirm Interface state..." << endl;
	}

	if (pInterfaceInfo.isState == wlan_interface_state_disconnected)
	{
		try {
			dwResult = WlanScan(hClient, &interfaceGUID, NULL, NULL, NULL);
			if (dwResult != ERROR_SUCCESS) {
				throw dwResult;
			}
			dwResult = WlanGetAvailableNetworkList(hClient, &interfaceGUID, WLAN_AVAILABLE_NETWORK_INCLUDE_ALL_ADHOC_PROFILES, NULL, &pAvail_lists);
			if (dwResult != ERROR_SUCCESS) {
				throw dwResult;
			}
			for (unsigned int i = 0; i < pAvail_lists->dwNumberOfItems; ++i)
			{
				if (pInterfaceInfo.isState == wlan_interface_state_connected) {
					break;
				}

				Avail_network = pAvail_lists->Network[i];
				if (!Avail_network.bNetworkConnectable || Avail_network.bSecurityEnabled) {
					continue;
				}
				if (!strcmp((CHAR*)Avail_network.dot11Ssid.ucSSID, "T wifi zone") || !strcmp((CHAR*)Avail_network.dot11Ssid.ucSSID, "Pubilc WIFI Free")) {
					
					Conn_params.strProfile = Avail_network.strProfileName;
					Conn_params.dot11BssType = Avail_network.dot11BssType;
					Conn_params.pDot11Ssid = &(Avail_network.dot11Ssid);
					Conn_params.wlanConnectionMode = wlan_connection_mode_profile;
					dwResult = WlanConnect(hClient, &interfaceGUID,  &Conn_params, NULL);
					if (dwResult != ERROR_SUCCESS) {
						throw dwResult;
					}
				}	
			}
			wcout << "Connected..." << endl;
		}
		catch (Log e) {
			cout << "error :" << e << endl;
		}	
	}
}

void AutoWifi::AddCallbackandResister(WLAN_NOTIFICATION_CALLBACK callback)
{
	callbackList.push_back(callback);

}

void AutoWifi::ResisterNotification(_In_ WLAN_NOTIFICATION_CALLBACK funcCallback)
{
	try {
		dwResult = WlanRegisterNotification(hClient, WLAN_NOTIFICATION_SOURCE_ALL, TRUE, funcCallback, (PVOID*)&pCallbackContext, NULL, NULL);
		if (dwResult != ERROR_SUCCESS) {
			throw dwResult;
		}
	}
	catch (Log e) {
		cout << "error :" << e << endl;
	}
}

VOID WINAPI Noti_Callback(PWLAN_NOTIFICATION_DATA data, PVOID context)
{

}