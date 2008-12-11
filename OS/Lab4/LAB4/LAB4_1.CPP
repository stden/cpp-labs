// lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream.h>
#include <conio.h>
HANDLE File;
void main(void)
{
	
   //HANDLE CreateFile(	// Создание файла							[out]
    
	   
	char FileName[50];                         // file name - имя файла						[in]
    DWORD DesiredAccess=GENERIC_READ|GENERIC_WRITE;                      // access mode - права доступа					[in]
    DWORD ShareMode=FILE_SHARE_READ|FILE_SHARE_WRITE;                          // share mode	 - режим разделения файла			[in]
    LPSECURITY_ATTRIBUTES SecurityAttributes=0; // SD - атрибуты ьезопасности			[in]
    DWORD CreationDisposition=CREATE_NEW;                // how to create - коллизии с существующим файлом		[in]
    DWORD FlagsAndAttributes=0;                 // file attributes - флаги и атрибуты файла			[in]
    HANDLE TemplateFile=0;                      // handle to template file - хэндл файла-образца			[in]
    
    int Flags=0;
    int menu=0;

 do
 {
	printf("\n1-create file");
 printf("\n2-informations by handle");
 printf("\n3-set flags and attributes");
 printf("\n4-System time to file time"); 
 printf("\n5-Dos time and compare ");
 printf("\n6-Exit");
 scanf("%d",&menu);
	switch(menu)
{
case 1:
    printf("\n Enter file name to create: ");
      scanf("%s",FileName);
   
	
 File=CreateFile(FileName,DesiredAccess,ShareMode,SecurityAttributes,CreationDisposition,FlagsAndAttributes,TemplateFile);

 

do
{	  
	
	//system("cls");

	printf("\n Enter file attributes: ");
    printf("\n 1-ARCHIVE    ");  
    printf("\n 2-HIDDEN     ");  
    printf("\n 3-NORMAL     ");  
    printf("\n 4-OFFLINE    ");  
    printf("\n 5-READONLY   ");
    printf("\n 6-SYSTEM     ");
    printf("\n 7-TEMPORARY  ");
    printf("\n 8-contini    ");
	scanf("%d",&Flags);  
	switch(Flags)
	  {
      case 1:
    FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_ARCHIVE ;
      break;
      case 2:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_HIDDEN ;
      break; 
      case 3:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_NORMAL ;
      break;
	  case 4:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_OFFLINE ; 
	  break;
	  case 5:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_READONLY;  
      break;
      case 6:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_SYSTEM; 
	  break;
	  case 7:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_TEMPORARY ;
	  break;
		case 8:
	   break;
 		  }
	}
	while(Flags!=8);
	SetFileAttributes(FileName,FlagsAndAttributes);
	break;
	
case 2:
/////////////////////////////////////////////////////////////////////
	BY_HANDLE_FILE_INFORMATION fileInformation;

	SYSTEMTIME fTime;
					WORD fatDate;//DOS format date
					WORD fatTime;//DOS format time
			
					
					if(!GetFileInformationByHandle(File, &fileInformation)){
						cout<<"Error\n";
					}
					else{
						cout<<"File attributes:\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_ARCHIVE) cout<<"  Archive\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_COMPRESSED) cout<<"  Compressed\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_ENCRYPTED) cout<<"  Encrypted\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN) cout<<"  Hidden\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_NORMAL) cout<<"  Normal\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_OFFLINE) cout<<"  Offline\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_READONLY) cout<<"  Read-Only\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_SYSTEM) cout<<"  System\n";
						if(fileInformation.dwFileAttributes&FILE_ATTRIBUTE_TEMPORARY) cout<<"  Temporary\n";

						cout<<"Windows format: \n";
						if(FileTimeToSystemTime(&fileInformation.ftCreationTime, &fTime)){
							cout<<"	Creation Time: "<<fTime.wDay<<"."<<fTime.wMonth<<"."<<fTime.wYear<<" ";
							cout<<fTime.wHour<<":"<<fTime.wMinute<<":"<<fTime.wSecond<<endl;
						}
						else cout<<"Error\n";
						if(FileTimeToSystemTime(&fileInformation.ftLastAccessTime, &fTime)){
							cout<<"	Last Access Time: "<<fTime.wDay<<"."<<fTime.wMonth<<"."<<fTime.wYear<<" ";
							cout<<fTime.wHour<<":"<<fTime.wMinute<<":"<<fTime.wSecond<<endl;
						}
						else cout<<"Error\n";
						if(FileTimeToSystemTime(&fileInformation.ftLastWriteTime, &fTime)){
							cout<<"	Last Write Time: "<<fTime.wDay<<"."<<fTime.wMonth<<"."<<fTime.wYear<<" ";
							cout<<fTime.wHour<<":"<<fTime.wMinute<<":"<<fTime.wSecond<<endl;
						}
						else cout<<"Error\n";

						cout<<"DOS format: \n";
						if(FileTimeToDosDateTime(&fileInformation.ftCreationTime, &fatDate, &fatTime)){
							cout<<"	Creation Time: "<<(fatDate&0x1F)<<"."<<((fatDate&0x1E0)>>5)<<"."<<(((fatDate>>9)&0x7F)+1980)<<" ";
							cout<<((fatTime&0xF800)>>11)<<":"<<((fatTime&0x7E0)>>5)<<":"<<((fatTime&0x1F)*2)<<endl;
						}
						else cout<<"Error\n";
						if(FileTimeToDosDateTime(&fileInformation.ftLastAccessTime, &fatDate, &fatTime)){
							cout<<"	Last Access Time: "<<(fatDate&0x1F)<<"."<<((fatDate&0x1E0)>>5)<<"."<<(((fatDate>>9)&0x7F)+1980)<<" ";
							cout<<((fatTime&0xF800)>>11)<<":"<<((fatTime&0x7E0)>>5)<<":"<<((fatTime&0x1F)*2)<<endl;
						}
						else cout<<"Error\n";
						if(FileTimeToDosDateTime(&fileInformation.ftLastWriteTime, &fatDate, &fatTime)){
							cout<<"	Last Write Time: "<<(fatDate&0x1F)<<"."<<((fatDate&0x1E0)>>5)<<"."<<(((fatDate>>9)&0x7F)+1980)<<" ";
							cout<<((fatTime&0xF800)>>11)<<":"<<((fatTime&0x7E0)>>5)<<":"<<((fatTime&0x1F)*2)<<endl;
						}
						else cout<<"Error\n";

						cout<<"Volume Serial Number: "<<fileInformation.dwVolumeSerialNumber<<endl;
						cout<<"File Size High: "<<fileInformation.nFileSizeHigh<<endl;
						cout<<"File Size Low: "<<fileInformation.nFileSizeLow<<endl;
						cout<<"Number Of Links: "<<fileInformation.nNumberOfLinks<<endl;
						cout<<"File Index High: "<<fileInformation.nFileIndexHigh<<endl;
						cout<<"File Index Low: "<<fileInformation.nFileIndexLow<<endl;
						
					}
//////////////////////////////////////////////////////////////////////			
		 break; 
	
	case 3:
/////////////////////////////////////////////////////////////////////	
		printf("\n Set flags and attributes: ");
		
	 printf("\n Enter file name to create: ");
      scanf("%s",FileName);
   
 CreationDisposition=OPEN_EXISTING;	
 File=CreateFile(FileName,DesiredAccess,ShareMode,SecurityAttributes,CreationDisposition,FlagsAndAttributes,TemplateFile);
do
{	  

	//system("cls");

	printf("\n Enter file attributes: ");
    printf("\n 1-ARCHIVE    ");  
    printf("\n 2-HIDDEN     ");  
    printf("\n 3-NORMAL     ");  
    printf("\n 4-OFFLINE    ");  
    printf("\n 5-READONLY   ");
    printf("\n 6-SYSTEM     ");
    printf("\n 7-TEMPORARY  ");
    printf("\n 8-contini    ");
	scanf("%d",&Flags);  
	switch(Flags)
	  {
      case 1:
    FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_ARCHIVE ;
      break;
      case 2:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_HIDDEN ;
      break; 
      case 3:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_NORMAL ;
      break;
	  case 4:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_OFFLINE ; 
	  break;
	  case 5:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_READONLY;  
      break;
      case 6:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_SYSTEM; 
	  break;
	  case 7:
	FlagsAndAttributes=FlagsAndAttributes|FILE_ATTRIBUTE_TEMPORARY ;
	  break;
		case 8:
	   break;
 		  }
	}
	while(Flags!=8);
	SetFileAttributes(FileName,FlagsAndAttributes);
	
	break; 
//////////////////////////////////////////////////////////////	
	case 4:
	////////////////////////////////////////////
		
		printf("System time:\n");

		
		FILETIME creationTime;
					FILETIME lastAccessTime;
					FILETIME lastWriteTime;

					cout<<"Input New Creation Time:\n";
					cout<<"  Year: ";
					cin>>fTime.wYear;
					cout<<"  Month: ";
					cin>>fTime.wMonth;
					cout<<"  Day Of Week: ";
					cin>>fTime.wDayOfWeek;
					cout<<"  Day: ";
					cin>>fTime.wDay;
					cout<<"  Hour: ";
					cin>>fTime.wHour;
					cout<<"  Minute: ";
					cin>>fTime.wMinute;
					cout<<"  Second: ";
					cin>>fTime.wSecond;
					fTime.wMilliseconds=0;
					if(!SystemTimeToFileTime(&fTime, &creationTime))
						cout<<"Error";

					cout<<"Input New Last Access Time:\n";
					cout<<"  Year: ";
					cin>>fTime.wYear;
					cout<<"  Month: ";
					cin>>fTime.wMonth;
					cout<<"  Day Of Week: ";
					cin>>fTime.wDayOfWeek;
					cout<<"  Day: ";
					cin>>fTime.wDay;
					cout<<"  Hour: ";
					cin>>fTime.wHour;
					cout<<"  Minute: ";
					cin>>fTime.wMinute;
					cout<<"  Second: ";
					cin>>fTime.wSecond;
					fTime.wMilliseconds=0;
					if(!SystemTimeToFileTime(&fTime, &lastAccessTime))
						cout<<"Error";

					cout<<"Input New Last Write Time:\n";
					cout<<"  Year: ";
					cin>>fTime.wYear;
					cout<<"  Month: ";
					cin>>fTime.wMonth;
					cout<<"  Day Of Week: ";
					cin>>fTime.wDayOfWeek;
					cout<<"  Day: ";
					cin>>fTime.wDay;
					cout<<"  Hour: ";
					cin>>fTime.wHour;
					cout<<"  Minute: ";
					cin>>fTime.wMinute;
					cout<<"  Second: ";
					cin>>fTime.wSecond;
					fTime.wMilliseconds=0;
					if(!SystemTimeToFileTime(&fTime, &lastWriteTime))
						cout<<"Error";

					if(!SetFileTime(File, &creationTime, &lastAccessTime, &lastWriteTime))
						cout<<"Error"<<endl;
					else{
						cout<<"New File Time:\n";

						if(!GetFileInformationByHandle(File, &fileInformation))
							cout<<"Error";

						if(FileTimeToSystemTime(&fileInformation.ftCreationTime, &fTime)){
							cout<<"	Creation Time: "<<fTime.wDay<<"."<<fTime.wMonth<<"."<<fTime.wYear<<" ";
							cout<<fTime.wHour<<":"<<fTime.wMinute<<":"<<fTime.wSecond<<endl;
						}
						else cout<<"Error\n";
						if(FileTimeToSystemTime(&fileInformation.ftLastAccessTime, &fTime)){
							cout<<"	Last Access Time: "<<fTime.wDay<<"."<<fTime.wMonth<<"."<<fTime.wYear<<" ";
							cout<<fTime.wHour<<":"<<fTime.wMinute<<":"<<fTime.wSecond<<endl;
						}
						else cout<<"Error\n";
						if(FileTimeToSystemTime(&fileInformation.ftLastWriteTime, &fTime)){
							cout<<"	Last Write Time: "<<fTime.wDay<<"."<<fTime.wMonth<<"."<<fTime.wYear<<" ";
							cout<<fTime.wHour<<":"<<fTime.wMinute<<":"<<fTime.wSecond<<endl;
						}
						else cout<<"Error\n";

					}
		////////////////////////////////////////////////
		break; 
	case 5:
	
		FILETIME CreationTime ;
		FILETIME LastAccessTime ;
		FILETIME LastWriteTime ;
		
		GetFileTime(File, &CreationTime, &LastAccessTime, &LastWriteTime) ;

		WORD Date = 0 ;
		WORD Time = 0 ;
		 
		
		FileTimeToDosDateTime(&CreationTime, &Date, &Time) ;
		printf("\n Dos Creation Date = %d  Dos Creation Time = %d\n", Date, Time) ;
		

		FILETIME newCreationTime ;
		DosDateTimeToFileTime(Date, Time, &newCreationTime) ;
		
		if ( CompareFileTime(&CreationTime, &newCreationTime)==0 )
			printf("\n Compare OK");
		else
			printf("\nCompare NOT OK");

		break; 
}
}
while(menu!=6);
}

