// Lab4.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#define STRICT
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

#include <windows.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "tooem.h"
#include "findFile.h"
#include "fmtErr.h"

using std::cout;
using std::setw;
using std::setfill;
using std::uppercase;
using std::hex;
using std::dec;

void printUsage();
//--------------------------------------------------------------
bool createNewFile(const char *fileName)
   {
    if (!fileName || !lstrlen(fileName))
       {
        cout<<"Failed to create new file: invalid file name\n";
        return false;
       }
    HANDLE hFile = CreateFile(  fileName
                              , GENERIC_WRITE
                              , 0 /* dwShareMode */
                              , 0 /* lpSecurityAttributes */
                              , CREATE_NEW
                              , FILE_ATTRIBUTE_NORMAL
                              , 0
                             );
    if (hFile==INVALID_HANDLE_VALUE)
       {
        cout<<"Failed to create file '"<<fileName<<"': "
            <<toOem(formatMessage())<<"\n";
        return false;       
       }
    CloseHandle(hFile);
    return true;   
   }
 //--------------------------------------------------------------
int main(int argc, char *argv[])

{
    char buf[256];
	char *pCmd="";
    char *nameOrMask="";
	DWORD atrr=0;
    DWORD attrMask = 0;
	WIN32_FIND_DATA FileData;
	BOOL fFinished = FALSE;
	switch(argc)
		{
			case 1:
					nameOrMask = "*.*";
					break;
			case 2:
				{	
					nameOrMask = argv[1];
					if (*nameOrMask=='-')
						{
							cout<<"Invalid command\n";
							printUsage();
							return 1;
						}	
					break;
				}
			case 3:
					{
						pCmd = argv[1];
						nameOrMask = argv[2];
						if (*pCmd!='-')
							{
								cout<<"Invalid command\n";
								printUsage();
							return 1;
							}	
							break;	
					}
			case 4:
					{
						pCmd = argv[1];
						nameOrMask = argv[2];
						DWORD i=0;
						while (argv[3][i]!=0)
							{	
								switch(argv[3][i])
								{
								case 'A': 
										{
											atrr=atrr|FILE_ATTRIBUTE_ARCHIVE;
											break;
										}
									case 'H': 
										{
											atrr=atrr|FILE_ATTRIBUTE_HIDDEN;
											break;
										}
									case 'S': 
										{
											atrr=atrr|FILE_ATTRIBUTE_SYSTEM;
											break;
										}
									case 'R': 
										{
											atrr=atrr|FILE_ATTRIBUTE_READONLY;
											break;
										}
									case 'C': 
										{
											atrr=atrr|FILE_ATTRIBUTE_COMPRESSED;
											break;
										}
									case 'E': 
										{
											atrr=atrr|FILE_ATTRIBUTE_ENCRYPTED;
											break;
										}
									case 'D': 
										{
											atrr=atrr|FILE_ATTRIBUTE_DIRECTORY;
											break;
										}
									case 'T': 
										{
											atrr=atrr|FILE_ATTRIBUTE_TEMPORARY;
											break;
										}
									case 'O': 
										{
											atrr=atrr|FILE_ATTRIBUTE_OFFLINE;
											break;
										}
									case 'P': 
										{
											atrr=atrr|FILE_ATTRIBUTE_REPARSE_POINT;
											break;
										}
									case 'F': 
										{
											atrr=atrr|FILE_ATTRIBUTE_SPARSE_FILE;
											break;
										}
									default: break;
								}
								i++;
							}

						if (*pCmd!='-')
							{
								cout<<"Invalid command\n";
								printUsage();
							return 1;
							}	
							break;	
					}
			default:
					std::cout<<"Invalid command\n";
					printUsage();
		}
    ++pCmd;
	switch(*pCmd)
       {
        case 'C':
		case 'c':
				{	
					createNewFile(nameOrMask);
					break;
				}
        case 's':
		case 'S':
				{	
					HANDLE	hSearch = FindFirstFile(nameOrMask, &FileData); 
					if (hSearch == INVALID_HANDLE_VALUE) std::cout<<" No "<< nameOrMask <<" files found!";
					while (!fFinished) 
						{ 
							SetFileAttributes(FileData.cFileName,atrr);
							std::cout<<"File: "<<FileData.cFileName<<" attributes change\n";
							if (!FindNextFile(hSearch, &FileData))  
							{
								std::cout<<"Couldn't find next file."; 
								fFinished = TRUE;
							}
						}
					FindClose(hSearch);
					break;
				}
		case 't':
		case 'T':
				{	
					FILETIME fc;
					FILETIME fa;
					FILETIME fw;
					SYSTEMTIME st;
					WORD DosData,DosTime;
					HANDLE hFile=CreateFile(nameOrMask,GENERIC_READ,0,NULL,OPEN_EXISTING,0,NULL);
					if (hFile!=INVALID_HANDLE_VALUE) 
						{ 
							GetFileTime(hFile,&fc,&fa,&fw);
							std::cout<<"File time to system time format "<<fileTimeStrDateTime(fc)<< "\n";
							FileTimeToDosDateTime(&fc,&DosData,&DosTime);
							std::cout<<"File time to dos time format    "
								<<(DosData&0x001F)<<"/"<<((DosData&0x01E0)>>5)<<"/"<<(((DosData&0xFE00)>>9)+1980)<< " "
								<<((DosTime&0xFF00)>>11)<<":"<<((DosTime&0x07E0)>>5)<<":"<<((DosTime&0x001F)<<1)<< "\n";
					//	DosDateTimeToFileTime();
						}
					break;
				}
		default:
				{	
					std::cout<<fileInfoGetCaptionString()<<"\n";
					enumFiles(COstreamPrintFileInfo(std::cout), nameOrMask);
				}	
		};
  	return 0;
   }
//--------------------------------------------------------------
void printUsage()
   {
    std::cout<<"Usage:\n"
             <<"   lab4                    - for list files in current directory\n"
			 <<"   lab4 mask               - list files by taken mask\n"
			 <<"   lab4 -c	filename       - crate file\n"
			 <<"   lab4 -s	mask attr      - set file Atribut\n"
			 <<"   lab4 -t	filename       - time file\n"
			 <<"Attributes\n"
             <<"   A':  -  FILE_ATTRIBUTE_ARCHIVE\n"
             <<"   H':  -  FILE_ATTRIBUTE_HIDDEN\n"
             <<"   S':  -  FILE_ATTRIBUTE_SYSTEM\n"
             <<"   R':  -  FILE_ATTRIBUTE_READONLY\n"
             <<"   C':  -  FILE_ATTRIBUTE_COMPRESSED\n"
             <<"   E':  -  FILE_ATTRIBUTE_ENCRYPTED\n"
             <<"   D':  -  FILE_ATTRIBUTE_DIRECTORY\n"
             <<"   T':  -  FILE_ATTRIBUTE_TEMPORARY\n"
             <<"   O':  -  FILE_ATTRIBUTE_OFFLINE\n"
             <<"   P':  -  FILE_ATTRIBUTE_REPARSE_POINT\n"
             <<"   F':  -  FILE_ATTRIBUTE_SPARSE_FILE\n";
 }