#include <windows.h>
#include <iostream.h>
#include <stdlib.h> 
#include <winbase.h>

HANDLE file;

void createfile()
{
	char name[255];
    cout << "Name for file: ";
	cin >> name;
	file=CreateFile(name,0,FILE_SHARE_WRITE,0,OPEN_ALWAYS,FILE_ATTRIBUTE_ARCHIVE,0);
	cout << "OK!!!\n";
}	
void fileinformation()
{
	BY_HANDLE_FILE_INFORMATION info;
	if(GetFileInformationByHandle(file,&info)==0) cout << "Error!!";
	cout << "Attributes " << info.dwFileAttributes << "\n";
    cout << "Creation time " << info.ftCreationTime.dwHighDateTime << info.ftCreationTime.dwLowDateTime << "\n";
	cout << "Last access time " << info.ftLastAccessTime.dwHighDateTime << info.ftLastAccessTime.dwLowDateTime << "\n";
	cout << "Last write time " << info.ftLastWriteTime.dwHighDateTime << info.ftLastWriteTime.dwLowDateTime << "\n";
	cout << "Serial Number " << info.dwVolumeSerialNumber << "\n";
	cout << "File size high " << info.nFileSizeHigh << "\n";
	cout << "File size low " << info.nFileSizeLow << "\n";
	cout << "Number of links " << info.nNumberOfLinks << "\n";
	cout << "File index high " << info.nFileIndexHigh << "\n";
	cout << "File index low " << info.nFileIndexLow << "\n";
  
}
void getfileattrib()



void systemtime();
{
	SYSTEMTIME time;
	GetSystemTime(&time);
	cout << time.wYear << " " << time.wMonth << " " << time.wDayOfWeek << " " ;
	cout << time.wDay << " " << time.wHour << " " << time.wMinute << " ";
	cout << time.wSecond << " " << time.wMilliseconds << "\n";
}

void getfiletime()
{
    FILETIME time1,time2,time3;
	if(GetFileTime(file,&time1,&time2,&time3)==0) cout << "Error";
	else 
	{
	cout << "Creation time : " << time1.dwHighDateTime << time1.dwLowDateTime << "\n";
         cout << "Last access time : " << time2.dwHighDateTime << time2.dwLowDateTime << "\n";
	cout << "Last write time : " << time3.dwHighDateTime << time3.dwLowDateTime << "\n";
  	  } 
         cout << "File time to dos date time: \n";
	WORD time,date;
  	if(FileTimeToDosDateTime(&time1,&date,&time)==0) cout << "Error";
	else 
		cout << "date :" << date << "  time :" << time << "\n";
	DosDateTimeToFileTime(date,time,&time1);
	if(FileTimeToDosDateTime(&time2,&date,&time)==0) cout << "Error";
	else 
		cout << "date :" << date << "  time :" << time << "\n";
	DosDateTimeToFileTime(date,time,&time2);
	if(FileTimeToDosDateTime(&time3,&date,&time)==0) cout << "Error";
	else 
		cout << "date :" << date << "  time :" << time << "\n";
	DosDateTimeToFileTime(date,time,&time3);
	cout << "File time to dos date time: \n";
	cout << time1.dwHighDateTime << time1.dwLowDateTime << "\n";
    	cout << time2.dwHighDateTime << time2.dwLowDateTime << "\n";
    	cout << time3.dwHighDateTime << time3.dwLowDateTime << "\n";
}

void set()
{
  	FILETIME time1,time2,time3;
	cout << "Creation time : "; 
   	cin >> time1.dwHighDateTime >> time1.dwLowDateTime;
	cout << "\n" << "Last access time : ";
	cin >> time2.dwHighDateTime >> time2.dwLowDateTime; 
	cout << "\n" << "Last write time : ";
	cin >> time3.dwHighDateTime >> time3.dwLowDateTime;
	cout << "\n";
    if(SetFileTime(file,&time1,&time2,&time3)==0) cout << "Error";
	else 
	cout << "ok!!!\n";
}

void menu()
{
	system("cls"); 
	cout << "\n";
	cout << "1 - Create file\n";
	cout << "2 - File information\n";
    cout << "3 - Set file attributes\n";
	cout << "4 - System Time\n";
	cout << "5 - Get file time\n";
	cout << "6 - Exit\n";
    cout << "\n";
}

void main()
{
	char a;
	menu();
         cin >> a;
	while (a!='6')
	{
		switch (a)
		{
		case '1' : createfile(); break;
		case '2' : fileinformation(); break; 
		case '3' : getfileattrib(); break;
        case '4' : systemtime(); break;
		case '5' : getfiletime(); break;
		default : break;
		};
		menu();
		cin >> a;
	}
}




