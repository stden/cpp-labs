
#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "conio.h"

BY_HANDLE_FILE_INFORMATION lpFileInformation;
DWORD NewFileAttr;
SYSTEMTIME lpLastWriteSystemTime, lpSystemTime; 
FILETIME lpLastWriteLocalTime, lpCreationTime, lpLastAccessTime, lpLastWriteTime;
HANDLE hfFile;
char cc, c, szFileName[128];
DWORD dwFileAttr;

void printtime(SYSTEMTIME st)
{
	printf ("\nYear: %d  ", st.wYear); 
	printf ("\tMonth:  %d  ", st.wMonth); 
	printf ("\tDayOfWeek: %d  ", st.wDayOfWeek); 
	printf ("\tDay:          %d", st.wDay); 
	printf ("\nHour: %d  ", st.wHour); 
	printf ("\tMinute: %d  ", st.wMinute); 
	printf ("\tSecond:    %d  ", st.wSecond); 
	printf ("\tMilliseconds: %d\n", st.wMilliseconds); 
} 

void printattrib(void)
{	
	printf ("ARCHIVE\t\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_ARCHIVE) printf("[x]\n");	else printf("[ ]\n");
	printf ("COMPRESSED\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_COMPRESSED) printf("[x]\n"); else printf("[ ]\n");
	printf ("DIRECTORY\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) printf("[x]\n"); else printf("[ ]\n");
	printf ("HIDDEN\t\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN) printf("[x]\n"); else printf("[ ]\n");
	printf ("NORMAL\t\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_NORMAL) printf("[x]\n"); else printf("[ ]\n");
	printf ("OFFLINE\t\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_OFFLINE) printf("[x]\n"); else printf("[ ]\n");
	printf ("READONLY\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_READONLY) printf("[x]\n"); else printf("[ ]\n");
	printf ("SYSTEM\t\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_SYSTEM) printf("[x]\n"); else printf("[ ]\n");
	printf ("TEMPORARY\t");
	if (lpFileInformation.dwFileAttributes&FILE_ATTRIBUTE_TEMPORARY) printf("[x]\n"); else printf("[ ]\n");
}
	
void err_msg(void)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL);
	MessageBox( NULL, (char*)lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );
	LocalFree( lpMsgBuf );
}

void getfileinfo(void)
{
	OFSTRUCT lpReOpenBuff;
	hfFile=(HANDLE)OpenFile(szFileName, &lpReOpenBuff, NULL);
	if (hfFile==(HANDLE)HFILE_ERROR) {err_msg();exit(0);}				// exit if error
	GetFileInformationByHandle(hfFile, &lpFileInformation);
	FileTimeToLocalFileTime(&lpFileInformation.ftLastWriteTime, &lpLastWriteLocalTime);
	FileTimeToSystemTime(&lpLastWriteLocalTime, &lpLastWriteSystemTime);

	GetFileTime(hfFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);
	FileTimeToSystemTime(&lpCreationTime, &lpSystemTime);
	lpSystemTime.wYear=2010;
	SystemTimeToFileTime(&lpSystemTime, &lpCreationTime);
	SetFileTime(hfFile, &lpCreationTime, &lpLastAccessTime, &lpLastWriteTime);


	printf ("\n\nFile size: %d",lpFileInformation.nFileSizeLow);
	printf ("\n---LastWriteTime---");
	printtime(lpLastWriteSystemTime);
	printf ("---FileAttributes---\n");
	printattrib();
	CloseHandle(hfFile);
}

void main(void)
{
	printf("Input Filename\n");
	scanf("%128s",&szFileName);
	fflush (stdin);
	while (true)
	{
		getfileinfo();
		NewFileAttr=0;
		printf ("\n1 - Change File Attributes\n0 - Exit\n");
		scanf("%d",&c);
		fflush (stdin);

		switch(c)
		{
			case 0: return;
			case 1: {	printf ("\nSet ARCHIVE\t\t (Y/N):");
						if (cc=getch(),cc=='y'||cc=='Y') NewFileAttr|=FILE_ATTRIBUTE_ARCHIVE;
						printf ("\nSet HIDDEN\t\t (Y/N):");
						if (cc=getch(),cc=='y'||cc=='Y') NewFileAttr|=FILE_ATTRIBUTE_HIDDEN;
						printf ("\nSet READONLY\t\t (Y/N):");
						if (cc=getch(),cc=='y'||cc=='Y') NewFileAttr|=FILE_ATTRIBUTE_READONLY;
						printf ("\nSet SYSTEM\t\t (Y/N):");
						if (cc=getch(),cc=='y'||cc=='Y') NewFileAttr|=FILE_ATTRIBUTE_SYSTEM;
						SetFileAttributes(szFileName, NewFileAttr);
						break;
					}

		}


	}


}

