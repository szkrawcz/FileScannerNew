#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <cstring>
#include <io.h>
#include <iostream>
#include <stdio.h>

using namespace std;

// GetLastWriteTime - Retrieves the last-write time and converts
//                    the time to a string
//
// Return value - TRUE if successful, FALSE otherwise
// hFile      - Valid file handle
// lpszString - Pointer to buffer to receive string



using namespace std;





typedef long long long64;
/**Don´t forget to use delete*/
LPCWSTR convStringToLPCWSTR(string String)
{
	char *cString = &String[0u];
	long64 size = strlen(cString);
	wchar_t* wString = new wchar_t[size];
	for (long64 i = 0; i < size; i++)
	{
		wString[i] = cString[i];
	}
	wString[size] = 0; //important, otherwise Windows will print whatever next in memmory until it finds a zero.
	return wString;
}


BOOL GetLastWriteTime(HANDLE hFile, LPTSTR lpszString, DWORD dwSize)
{
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stUTC, stLocal;
	DWORD dwRet;

	// Retrieve the file times for the file.
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))
		return FALSE;

	// Convert the last-write time to local time.
	FileTimeToSystemTime(&ftWrite, &stUTC);
	//FileTimeToSystemTime(&ftAccess, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

	// Build a string showing the date and time.
	dwRet = StringCchPrintf(lpszString, dwSize,
		TEXT("%02d/%02d/%d  %02d:%02d"),
		stLocal.wMonth, stLocal.wDay, stLocal.wYear,
		stLocal.wHour, stLocal.wMinute);

	if (S_OK == dwRet)
		return TRUE;
	else return FALSE;
}

int  ShowLastWriteTime(string FileName)
{
	HANDLE hFile;
	TCHAR szBuf[MAX_PATH];

	/* if( argc != 2 )
	{
	printf("This sample takes a file name as a parameter\n");
	return 0;
	}*/


	
	hFile = CreateFile(convStringToLPCWSTR(FileName),            // file to open
		GENERIC_READ,          // open for reading
		FILE_SHARE_READ,       // share for reading
		NULL,                  // default security
		OPEN_EXISTING,         // existing file only
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // normal file
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile failed with %d\n", GetLastError());
		return 0;
	}
	if (GetLastWriteTime(hFile, szBuf, MAX_PATH))
		_tprintf(TEXT("Last write time is: %s\n"), szBuf);
	

//	std::cin >> a;
	CloseHandle(hFile);
	return 0;

}


int _tmain(int argc, TCHAR *argv[])
{
	ShowLastWriteTime("F:\\lib.zip");
	ShowLastWriteTime("F:\\VC_RED.cab");
	ShowLastWriteTime("F:\\honda\\08cbr1000rr_sm.pdf");
	ShowLastWriteTime("F:\\honda\\08cbr1000rr_sm.pdf");
	ShowLastWriteTime("F:\\honda\\08cbr1000rr_sm.pdf");
	int a;
	std::cin >> a;
	return 0;

}
