// lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "myfile.h"
#include "Windows.h"
#include "conio.h"
#include "iostream.h"
#include "myfile2.h"
#include "myf.h"
/////////////////////
#include "stdlib.h"// nuzhno dlja o4istki ekrana!!!!!!!!
/////////////////////

int main(int argc, char* argv[])
{
SetConsoleTitle("Lab#4 Gruppa 0362 Chizhov A.V.  var#2");
WORD choice;
char Fname[256];
HANDLE NewFile;
BOOL bOF;
bOF=FALSE;
	do
	{
	system("cls");
	printf("Press 1 to create file\r\n");
	printf("Press 2 to open file\r\n");
	printf("Press 3 to get file information by handle\r\n");
	printf("Press 4 to get file size\r\n");
	printf("Press 5 to set file attributes\r\n");
	printf("Press 6 to get file time\r\n");
	printf("Press 7 to EXIT\r\n\n\n");
	if (bOF)
		printf("The current opened file is: %s\r\n",Fname);
	//printf(Fname);
	choice=getch();
	switch(choice)
		{
		case '1':
			{
				system("cls");
				printf("Enter name of creating file\r\n");
				getch();
				gets(Fname);
				////////////////////////
				if (!((NewFile=CreateFile(Fname, GENERIC_WRITE, 0,NULL,CREATE_NEW,FILE_ATTRIBUTE_ARCHIVE, NULL ))== INVALID_HANDLE_VALUE))
					{
					if (CloseHandle( NewFile ))
						{
						printf("File created successfully:%s\r\n",Fname);
						bOF=TRUE;
						CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL );
						}
					else 
						{
						MyErrors();
						bOF=FALSE;
						//if(CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL )!=INVALID_HANDLE_VALUE)
						//	bOF=TRUE;
						}
					} 
			   	else 
					{
					MyErrors();
					//bOF=FALSE;
					/*if(!(*/NewFile=CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL );//==INVALID_HANDLE_VALUE))
							bOF=TRUE;
					}

		
				////////////////////////
				//PressAnyKeyToContinue();
				break;
			}
		case '2':
			{
				CloseHandle(NewFile); 
				system("cls");
				printf("Enter name of opening file\r\n");
				getch();
				gets(Fname);
				////////////////////////
				if (!((NewFile=CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE, NULL ))== INVALID_HANDLE_VALUE))
					{
					if (CloseHandle( NewFile ))
						{
						printf("File opened successfully:%s\r\n",Fname);
						bOF=TRUE;
						CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL );
						}
						else 
							{
							MyErrors();
							bOF=FALSE;
							}
						
					} 
			   	else 
					{
					MyErrors();
					bOF=FALSE;
					}

		
				////////////////////////
			//	PressAnyKeyToContinue();
				break;
			}
		case '3':
			{
				BY_HANDLE_FILE_INFORMATION FileInformation;
				if(bOF)
					{
					//NewFile=CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE, NULL );
					printf("Getting file information by handle, on file: %s\r\n",Fname);
					//NewFile=CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE, NULL );
					if((GetFileInformationByHandle( NewFile , &FileInformation))==FALSE)
						MyErrors();
					printf("File attributes:   ");
					PrintAttributes(FileInformation.dwFileAttributes);
					printf("\r\n");
					printf("Creation time: ");
					FileDateTimeToString(&FileInformation.ftCreationTime);
					printf("Last Access Time: ");
					FileDateTimeToString(&FileInformation.ftLastAccessTime);
					printf("Last Write Time:  ");
					FileDateTimeToString(&FileInformation.ftLastWriteTime);
					printf("\r\n");
					printf("Volume Serial Number (HEX): %8lx\r\n",FileInformation.dwVolumeSerialNumber);
					printf("File Size:                  %8lu\r\n",FileInformation.nFileSizeLow);
					printf("Number Of Links:            %8lu\r\n",FileInformation.nNumberOfLinks);
					printf("File Index High (HEX):      %8lx\r\n",FileInformation.nFileIndexHigh);
					printf("FileIndexLow (HEX):         %8lx\r\n",FileInformation.nFileIndexLow);
					//CloseHandle( NewFile );
					//CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL );
					}
				else
					printf("Open or create file, before getting information\r\n");
				break;
			}
		case '4':
			{
				DWORD FileSizeHigh;
				DWORD Size;
				//HANDLE File;
				system("cls");
				if(bOF)
					{
					
					printf("Getting file size for file: %s\r\n",Fname);
				
					Size=GetFileSize(NewFile,&FileSizeHigh);
					if (!(Size == -1))
						cout<<"File size: "<<Size<<" bytes"<<endl;
					else
						MyErrors();
					break;
					}
				else
					printf("Open or create file, before getting information\r\n");
			}
		case '5':
			{
				BY_HANDLE_FILE_INFORMATION FileInformation;
				DWORD FileAttributes;
				char atr;
				system("cls");
				if(bOF)
					{
					do
						{
						system("cls");
						printf("Setting file attributes for file: %s\r\n",Fname);
						GetFileInformationByHandle( NewFile , &FileInformation);
						printf("File attributes:   ");
						PrintAttributes(FileInformation.dwFileAttributes);
						FileAttributes=FileInformation.dwFileAttributes;
						printf("\r\nR-readonly, H-hidden, S-system, A-archive\r\n");
						printf("Press 'r', 'h', 's' or 'a' to change attributes\r\n");
						printf("or 'q' to EXIT\r\n");
						printf("If attribute is set - '+' is shown, otherwise '-'\r\n");
						atr=getch();
						switch(atr)
							{
								case 'a':  FileAttributes^=0x20;
									break;
								case 'h':  FileAttributes^=0x02; 
									break;
								case 's':  FileAttributes^=0x04;
									break;
								case 'r':  FileAttributes^=0x01;
									break;
							}
						SetFileAttributes(Fname, FileAttributes);
						}while(atr!='q');
					}
				else
					printf("Open or create file, before getting information\r\n");
					break;
			}
		case '6':
			{
				SYSTEMTIME SystemTime;
				FILETIME Tcreate,Tlastacc,Tlastwr;
				system("cls");
				if(bOF)
					{
					//NewFile=CreateFile(Fname, GENERIC_WRITE, 0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_ARCHIVE, NULL );
					printf("Getting file time\r\n");
					printf("Using 'file time to system time'\r\n");
					GetFileTime( NewFile , &Tcreate, &Tlastacc, &Tlastwr);
					FileTimeToSystemTime( &Tcreate, &SystemTime);
					///////////////
					printf("Creation time:\r\n");
					cout<<SystemTime.wDay<<"."<<SystemTime.wMonth<<"."<<SystemTime.wYear<<endl;
					cout<<SystemTime.wHour<<":"<<SystemTime.wMinute<<":"<<SystemTime.wSecond<<endl;
					/////////////////////
					printf("Last access time:\r\n");
					FileTimeToSystemTime( &Tlastacc, &SystemTime);  
					cout <<SystemTime.wDay<<"."<<SystemTime.wMonth<<"." << SystemTime.wYear<<endl ;
					cout<<SystemTime.wHour<<":"<<SystemTime.wMinute<<":"<<SystemTime.wSecond<<endl;
					////////////////////
					printf("Last write time:\r\n");
					FileTimeToSystemTime( &Tlastwr, &SystemTime);  
					cout <<SystemTime.wDay<<"."<<SystemTime.wMonth<<"." << SystemTime.wYear<<endl ;
					cout<<SystemTime.wHour<<":"<<SystemTime.wMinute<<":"<<SystemTime.wSecond<<endl;
					//////////////////////////
					DOSDATE Tcr,Tlas,Twr;
					FILETIME Tfile;
					BY_HANDLE_FILE_INFORMATION FileInformation;
					GetFileInformationByHandle( NewFile , &FileInformation);
					//CloseHandle( NewFile );
					//cout << endl<< endl;
					PressAnyKeyToContinue();
					system("cls");
					//printf("File time by using 'file time to dos date time'\r\n");
				




					cout << "CreationTime:                         ";//<<endl;
					cout<<endl;
					DosTime(FileInformation.ftCreationTime, &Tcr);
				
					cout << endl;
					/*cout << "FILETIME stucture that was got by 'GetFileInformationByHandle': "<< endl; 
					cout << endl;
					cout <<"HighDateTime:  ";
					cout << FileInformation.ftCreationTime.dwHighDateTime<< endl;
					cout << "LowDateTime:  ";
					cout << FileInformation.ftCreationTime.dwLowDateTime << endl;*/
				
					Tfile = ConvertDosDate(Tcr);

					//cout << endl <<endl<<"dos date time to file time:" << endl;
					//cout << endl;
					//cout << "FILETIME structure that was converted from DOS date: "<< endl;
					//cout << endl;
					cout <<"HighDateTime:  ";
					cout  << Tfile.dwHighDateTime << endl;
					cout <<"LowDateTime:   ";
					cout << Tfile.dwLowDateTime << endl<< endl;
					getch();
					system("cls");









					cout << "LastAccessTime :                      ";
					cout<<endl;
					DosTime(FileInformation.ftLastAccessTime, &Tlas);
				
					cout << endl;
					/*cout << "FILETIME stucture that was got by 'GetFileInformationByHandle': "<< endl; 
					cout << endl;
					cout <<"HighDateTime:  ";
					cout << FileInformation.ftLastAccessTime.dwHighDateTime<< endl;
					cout << "LowDateTime:   ";
					cout << FileInformation.ftLastAccessTime.dwLowDateTime << endl;*/
				
					Tfile = ConvertDosDate(Tlas );

					//cout << endl <<endl<<"dos date time to file time:" << endl;
					//cout << endl;
					//cout << "FILETIME structure that was converted from DOS date: "<< endl;
					//cout << endl;
					cout <<"HighDateTime:  ";
					cout  << Tfile.dwHighDateTime << endl;
					cout <<"LowDateTime:   ";
					cout << Tfile.dwLowDateTime << endl << endl;
					getch();///////////////////////////////////////sdfsdfsdfsdf
					system("cls");







					cout << "LastWriteTime:                        ";
					cout<<endl;
					DosTime(FileInformation.ftLastWriteTime, &Twr);
 			
					cout << endl;
					/*cout <<"FILETIME stucture that was got by 'GetFileInformationByHandle': "<< endl; 
					cout << endl;
					cout <<"HighDateTime:  ";
					cout << FileInformation.ftLastWriteTime.dwHighDateTime<< endl;
					cout <<"LowDateTime:   ";
					cout << FileInformation.ftLastWriteTime.dwLowDateTime << endl;*/
					
					Tfile = ConvertDosDate(Twr );
					//cout << endl <<endl<<"dos date time to file time:" << endl;
					//cout << endl;
					//cout << "FILETIME structure that was converted from DOS date : "<< endl;
					//cout << endl;
					cout <<"HighDateTime:  ";
					cout  << Tfile.dwHighDateTime << endl;
					cout <<"LowDateTime:   ";
					cout << Tfile.dwLowDateTime << endl;
					}
				else
					printf("Open or create file, before getting information\r\n");
				break;
			}
;		}
		//CloseHandle( NewFile );
		PressAnyKeyToContinue();
		system("cls");
	}while(choice!='7');
	return 0;
}
