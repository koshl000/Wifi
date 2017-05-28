#pragma once

#include "stdafx.h"
#include <windows.h>
#include <wlanapi.h>
#include <Windot11.h>           // for DOT11_SSID struct
#include<iostream>
#include <stdlib.h>
#include <vector>
// Need to link with Wlanapi.lib and Ole32.lib
#pragma comment(lib, "wlanapi.lib")
#pragma comment(lib, "ole32.lib")

typedef DWORD Log;
using namespace std;

class AutoWifi
{
private:
	/*Public Params*/
	DWORD dwResult = 0;
	vector<WLAN_NOTIFICATION_CALLBACK> callbackList;

	/*WlanOpenHandle Function Params*/
	DWORD dwClientVersion = 2;
	DWORD dwCurVersion = 0;
	HANDLE hClient = NULL;

	/*WlanEnumInterfaces Function Params*/
	PWLAN_INTERFACE_INFO_LIST pInterfaceLists = NULL;
	WLAN_INTERFACE_INFO pInterfaceInfo = { 0 };
	GUID interfaceGUID = { 0 };

	/*WlanGetAvailableNetworkList Function Params*/
	PWLAN_AVAILABLE_NETWORK_LIST pAvail_lists = NULL;
	_WLAN_AVAILABLE_NETWORK Avail_network = { 0 };

	/*WlanConnect Function Params*/
	WLAN_CONNECTION_PARAMETERS Conn_params;

	/*WlanRegisterNotification Function Params*/
	PWLAN_CONNECTION_NOTIFICATION_DATA pCallbackContext = NULL;

public:
	AutoWifi();
	void ResisterNotification(_In_ WLAN_NOTIFICATION_CALLBACK funcCallback);
	void Connect();
	void AddCallbackandResister(WLAN_NOTIFICATION_CALLBACK callback);
};