// Lab3.cpp : Defines the entry point for the console application.
#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <malloc.h>
#include "Toolhelp.h"
#include "tooem.h"
#include "fmtErr.h"

using std::cout;
using std::setw;
using std::setfill;
using std::uppercase;
using std::hex;
using std::dec;


std::string getWindowsDirectory();
std::string getCurrentDirectory();

bool moveFile(const char *src, const char* dst);
bool deleteFile(const char *fileName);
bool createNewDirDirectory(const char *fileName);
bool removeDirectory(const char *dirName);
void printUsage();

//--------------------------------------------------------------
std::string getWindowsDirectory()
   {
    char  ch = 0;
    char *buf = &ch;
    DWORD size = GetWindowsDirectory(buf, 1);
    buf = (char*)_alloca(size);
    GetWindowsDirectory(buf, size);
    return std::string(buf);
   }
//--------------------------------------------------------------------
std::string getCurrentDirectory()
   {
    char  ch = 0;
    char *buf = &ch;
    DWORD size = GetCurrentDirectory(1, buf);
    buf = (char*)_alloca(size);
    GetCurrentDirectory(size, buf);
    return std::string(buf);
   }
//--------------------------------------------------------------------
bool moveFile(const char *src, const char* dst)
   {
    if (!src || !lstrlen(src))
       {
        cout<<"Failed to move file: invalid source name\n";
        return false;
       }
    if (!dst || !lstrlen(dst))
       {
        cout<<"Failed to move file: invalid destination name\n";
        return false;
       }
    if (MoveFile(src, dst))
       return true;
    cout<<"Failed to move '"<<src<<"' to '"<<dst<<"': "
        <<toOem(formatMessage())<<"\n";
    return false;
   }
   //--------------------------------------------------------------------
   bool createNewDirDirectory(const char *dirName)
   {
    if (!CreateDirectory( dirName,NULL ))
       {
        cout<<"Failed to create directory '"<<dirName<<"': "
            <<toOem(formatMessage())<<"\n";
        return false;
       }
    return true;
   }
//--------------------------------------------------------------------
bool removeDirectory(const char *dirName)
   {
    if (!dirName || !lstrlen(dirName))
       {
        cout<<"Failed to remove directory: invalid directory name\n";
        return false;
       }
    if (!RemoveDirectory( dirName ))
       {
        cout<<"Failed to remove directory '"<<dirName<<"': "
            <<toOem(formatMessage())<<"\n";
        return false;
       }
    return true;
   }
//--------------------------------------------------------------------
bool deleteFile(const char *fileName)
   {
    if (!fileName || !lstrlen(fileName))
       {
        cout<<"Failed to remove directory: invalid directory name\n";
        return false;
       }
    if (!DeleteFile( fileName ))
       {
        cout<<"Failed to delete file '"<<fileName<<"': "
            <<toOem(formatMessage())<<"\n";
        return false;
       }
    return true;
   }
//--------------------------------------------------------------------
int main(int argc, char *argv[])
	{
    if (argc<2)
       { // аргументы не заданы
        cout<<"Windows directory : "<<toOem(getWindowsDirectory())<<"\n";
        cout<<"Current directory : "<<toOem(getCurrentDirectory())<<"\n";
        printUsage();
        return 1;
       }

    char *pCmd = argv[1];
    if (*pCmd!='-')
       {
        cout<<"Invalid command\n";
        printUsage();
       }
    ++pCmd;
    switch(*pCmd)
       {
        case 'c':
		case 'C':
				  if (argc<3)
                     {
                      cout<<"Create: invalid source or destination\n";
                      return 1;
                     }
                  createNewDirDirectory(argv[2]);
                  break;

        case 'm':
                  if (argc<4)
                     {
                      cout<<"Move: invalid source or destination\n";
                      return 1;
                     }
                  moveFile(argv[2], argv[3]);
                  break;

        case 'r':
                  if (argc<3)
                     {
                      cout<<"Remove Directory: invalid directory name\n";
                      return 1;
                     }
                  removeDirectory(argv[2]);
                  break;
        case 'd':
                  if (argc<3)
                     {
                      cout<<"Delete file: invalid directory name\n";
                      return 1;
                     }
                  deleteFile(argv[2]);
                  break;
        default:
                  cout<<"Invalid command\n";
                  printUsage();
       };

    return 0;
   }
//--------------------------------------------------------------------
void printUsage()
   {
    cout<<"Usage: \n"
        <<"-c Directory name           - create directory\n"
        <<"-m Source Destination       - move file\n"
        <<"-r DirName                  - remove directory\n"
		<<"-d File name                - delete file\n"; 

   }
