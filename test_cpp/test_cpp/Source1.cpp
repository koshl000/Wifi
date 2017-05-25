#include<Windows.h>
#include<vector>
#include<iostream>
#include<string>
#include<locale>
#include<stdio.h>
using namespace std;
/*
#define FILE_ATTRIBUTE_READONLY             0x000000010
#define FILE_ATTRIBUTE_HIDDEN               0x000000021
#define FILE_ATTRIBUTE_SYSTEM               0x000000042
#define FILE_ATTRIBUTE_DIRECTORY            0x000000104
#define FILE_ATTRIBUTE_ARCHIVE              0x000000205
#define FILE_ATTRIBUTE_DEVICE               0x000000406
#define FILE_ATTRIBUTE_NORMAL               0x000000807
#define FILE_ATTRIBUTE_TEMPORARY            0x000001008
#define FILE_ATTRIBUTE_SPARSE_FILE          0x000002009
#define FILE_ATTRIBUTE_REPARSE_POINT        0x0000040010
#define FILE_ATTRIBUTE_COMPRESSED           0x0000080011
#define FILE_ATTRIBUTE_OFFLINE              0x0000100012
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED  0x0000200013
#define FILE_ATTRIBUTE_ENCRYPTED            0x0000400014
#define FILE_ATTRIBUTE_INTEGRITY_STREAM     0x0000800015
#define FILE_ATTRIBUTE_VIRTUAL              0x0001000016
#define FILE_ATTRIBUTE_NO_SCRUB_DATA        0x0002000017
#define FILE_ATTRIBUTE_EA                   0x0004000018
*/

/*
void main()
{
	
	wcout.imbue(locale("korean"));
	vector<WIN32_FIND_DATA> vdata;
	WIN32_FIND_DATA attr;
	HANDLE handle;
	string filename;
	string str;
	handle = FindFirstFile(TEXT("D:\\animation\\[BD.720p]이야기(모노가타리)시리즈\\*"), &attr);
	vdata.push_back(attr);
	while (FindNextFile(handle, &attr) != 0)
	{
		vdata.push_back(attr);
	}
	for (auto& iter : vdata)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (iter.dwFileAttributes&(1<<i))
			{
				switch (i)
				{
				case 0:
					str += "READONLY|";
					break;
				case 1:
					str += "HIDDEN|";
					break;
				case 2:
					str += "SYSTEM|";
					break;
				case 4:
					str += "DIRECTORY|";
					break;
				case 5:
					str += "ARCHIVE|";
					break;
				case 6:
					str += "DEVICE|";
					break;
				case 7:
					str += "NORMAL|";
					break;
				case 8:
					str += "TEMPORARY|";
					break;
				case 9:
					str += "SPARSE_FILE|";
					break;
				case 10:
					str += "REPARSE_POINT|";
					break;
				case 11:
					str += "COMPRESSED|";
					break;
				case 12:
					str += "OFFLINE|";
					break;
				case 13:
					str += "NOT_CONTENT_INDEXED|";
					break;
				case 14:
					str += "ENCRYPTED|";
					break;
				case 15:
					str += "INTEGRITY_STREAM|";
					break;
				case 16:
					str += "VIRTUAL|";
					break;
				case 17:
					str += "NO_SCRUB_DATA|";
					break;
				case 18:
					str += "EA";
					break;
				}

			}
		}
		
		wstring ws(iter.cFileName);
		wcout << ws;
		cout<< " , " << str << endl;
		str.clear();
	}
}
*/
