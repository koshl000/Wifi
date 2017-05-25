#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main(int argc, char* argv[])
{

	
	char a[3] = { 'a','b','c' };
	char* str = a;
	printf("%s", str);
	cout << str << endl;

}