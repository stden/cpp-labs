// Lab2.cpp : Defines the entry point for the console application.
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


DWORD getParentProcessId(DWORD pid);
std::string getProcessName(DWORD pid);
bool setCurrentDirectoryForProcess(DWORD pid, const char* strPath);
void setCurrentDirectoryForProcessTree(const char* strPath);
void printUsage();
std::string getWindowsDirectory();
std::string getCurrentDirectory();
std::string getLongPathName(const char* strPath);
//--------------------------------------------------------------
DWORD getParentProcessId(DWORD pid /* child PID */) {
  CToolhelp th(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 pe = { sizeof(pe) };

  for( BOOL fProcOk = th.ProcessFirst(&pe);
       fProcOk;
       fProcOk = th.ProcessNext(&pe)) {
    if (pe.th32ProcessID == pid) return pe.th32ParentProcessID;
  }

  return 0;
}
//--------------------------------------------------------------
std::string getProcessName(DWORD pid) {
  CToolhelp th(TH32CS_SNAPPROCESS, 0);
  PROCESSENTRY32 pe = { sizeof(pe) };

  if (th.ProcessFind(pid, &pe))
    return std::string(pe.szExeFile);

  return std::string("<UNKNOWN>");
}
//--------------------------------------------------------------
typedef BOOL (WINAPI* SetCurrentDirectoryProcT)(LPCTSTR);
bool setCurrentDirectoryForProcess(DWORD pid, const char* strPath) {
  int nameLen = lstrlen(strPath);
  HANDLE hProcess = OpenProcess( PROCESS_CREATE_THREAD
                                 | PROCESS_VM_OPERATION
                                 | PROCESS_VM_WRITE
                                 | PROCESS_VM_READ
                                 , FALSE
                                 , pid
                               );

  if (!pid) return false;

  void* remoteBuf = (void*)VirtualAllocEx( hProcess
                    , 0
                    , (nameLen + 1)
                    , MEM_COMMIT
                    , PAGE_READWRITE
                                         );

  if (!remoteBuf) {
    CloseHandle( hProcess );
    return false;
  }

  if (!WriteProcessMemory( hProcess
                           , remoteBuf
                           , (void*)strPath
                           , (nameLen + 1), 0 ) ) {
    VirtualFreeEx( hProcess, remoteBuf, 0, MEM_RELEASE );
    CloseHandle( hProcess );
    return false;
  }

  SetCurrentDirectoryProcT PSetCurrentDirectory =
    (SetCurrentDirectoryProcT)GetProcAddress(
      GetModuleHandle( _T("Kernel32.dll") )
      , "SetCurrentDirectoryA"
    );
  DWORD rc = 0;
  HANDLE hRemoteThread = CreateRemoteThread( hProcess
                         , 0
                         , 0 /*stackSize*/
                         , (LPTHREAD_START_ROUTINE)PSetCurrentDirectory
                         , remoteBuf
                         , 0
                         , &rc
                                           );

  if ( hRemoteThread == NULL ) {
    VirtualFreeEx( hProcess, remoteBuf, 0, MEM_RELEASE );
    CloseHandle( hProcess );
    return false;
  }

  rc = WaitForSingleObject( hRemoteThread, 10000 );
  VirtualFreeEx( hProcess, remoteBuf, 0, MEM_RELEASE );
  CloseHandle( hRemoteThread );
  CloseHandle( hProcess );

  if (rc == WAIT_OBJECT_0) return true;

  return false;
}
//--------------------------------------------------------------
void setCurrentDirectoryForProcessTree(const char* strPath) {
  if (!strPath) return;

  for( DWORD pid = getParentProcessId(GetCurrentProcessId());
       pid != 0;
       pid = getParentProcessId(pid)) {
    if (!setCurrentDirectoryForProcess(pid, strPath))
      break;
  }
}
//--------------------------------------------------------------
std::string getWindowsDirectory() {
  char  ch = 0;
  char* buf = &ch;
  DWORD size = GetWindowsDirectory(buf, 1);
  buf = (char*)_alloca(size);
  GetWindowsDirectory(buf, size);
  return std::string(buf);
}
//--------------------------------------------------------------------
std::string getCurrentDirectory() {
  char  ch = 0;
  char* buf = &ch;
  DWORD size = GetCurrentDirectory(1, buf);
  buf = (char*)_alloca(size);
  GetCurrentDirectory(size, buf);
  return std::string(buf);
}
//--------------------------------------------------------------------
std::string getLongPathName(const char* strPath) {
  char buf[256];
  GetLongPathName((LPTSTR) strPath, buf, 256);
  return std::string(buf);
}
//--------------------------------------------------------------------
int main(int argc, char* argv[]) {
  if (argc < 2) {
    // аргументы не заданы
    cout << "Windows directory : " << toOem(getWindowsDirectory()) << "\n";
    cout << "Current directory : " << toOem(getCurrentDirectory()) << "\n";
    printUsage();
    return 1;
  }

  char* pCmd = argv[1];

  if (*pCmd != '-') {
    cout << "Invalid command\n";
    printUsage();
  }

  ++pCmd;

  switch(*pCmd) {
    case 'd':
      if (argc < 3) {
        cout << "Set Current Directory: "
             "invalid directory name\n";
        return 1;
      }

      setCurrentDirectoryForProcessTree(argv[2]);
      break;

    case 's':
      if (argc < 3) {
        cout << "Show short path name directory: "
             "invalid directory name\n";
        return 1;
      }

      cout << "directory " << toOem(argv[2]) << " is short path name: " << toOem(getLongPathName(argv[2])) << "\n";
      break;

    default:
      cout << "Invalid command\n";
      printUsage();
  };

  return 0;
}
//--------------------------------------------------------------------
void printUsage() {
  cout << "Usage: \n"
       << "-d DirName                  - change current directory\n"
       << "-s DirName                  - Show short path name directory\n";
}