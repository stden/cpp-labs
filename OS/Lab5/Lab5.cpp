// Lab5.cpp : Defines the entry point for the console application.
//
#include "tooem.h"
#include "fmtErr.h"

#include <conio.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>

#define WIN32_LEAN_AND_MEAN
#define STRICT
#define CMP_RETURN_VAL(val, cmp) if (val==cmp) return std::string(#cmp)

using std::cout;
using std::cin;
using std::setw;
using std::setfill;
using std::uppercase;
using std::hex;
using std::dec;
using std::ios_base;
using std::ostream;

HANDLE hHeaps[25];
char *AllocMem=NULL;
//--------------------------------------------------------------
inline char getChar()
   {
    char ch;
    std::cin.get(ch);
    return ch;   
   }
//--------------------------------------------------------------
inline void msgGetChar(const char *msg = "\nPress ENTER key to continue\n")
   {
    cout<<msg;
    getChar();
   }
//--------------------------------------------------------------
int getInput()
   {
    char ch = getChar();
    if (ch<'0' || ch>'9') return -1;
    return ch-'0';
   }
//--------------------------------------------------------------
void printMenu()
   {
    cout<<"\n\n";
    cout<<"1 - Query virtual memory status\n";
    cout<<"2 - Allocation of virtual memory\n";
    cout<<"3 - Clearing of virtual memory\n";
    cout<<"4 - Create Heap\n";
    cout<<"5 - Allocates a block of memory from a heap\n";
    cout<<"6 - Frees a memory block allocated from a heap \n";
	cout<<"7 - Delete a Heap\n";
    cout<<"0 - Quit\n";
   }
//--------------------------------------------------------------
void queryVirtualMemoryStatus()
   {
    /*   
	MEMORYSTATUS ms;
    GlobalMemoryStatus(&ms);
    cout<<"\n";
    cout<<"Memory Used               : "<<ms.dwMemoryLoad <<"%\n";
    cout<<"Physical Memory Total     : "<<ms.dwTotalPhys/1024 <<" Kb\n";
    cout<<"Physical Memory Avail     : "<<ms.dwAvailPhys/1024 <<" Kb\n";
    cout<<"Commited Memory Limit     : "<<ms.dwTotalPageFile/1024 <<" Kb\n";
    cout<<"Available Mem to Commit   : "<<ms.dwAvailPageFile/1024 <<" Kb\n";
    cout<<"User Mode Address Space   : "<<ms.dwTotalVirtual/1024 <<" Kb\n";
    cout<<"User Mode Available Space : "<<ms.dwAvailVirtual/1024 <<" Kb\n";
	*/
	SYSTEM_INFO si;
    GetSystemInfo(&si);
    cout<<"      Page size: "<<si.dwPageSize<<" bytes\n";
    cout<<std::uppercase<<hex;
    cout<<"      Minimum Application Address: 0x"<<setw(8)<<setfill('0')<<si.lpMinimumApplicationAddress<<"\n";
    cout<<"      Maximum Application Address: 0x"<<setw(8)<<setfill('0')<<si.lpMaximumApplicationAddress<<"\n";
    cout<<setw(0)<<setfill(' ')<<dec;
    cout<<"\n";
    cout<<"      Allocation granularity: "<<si.dwAllocationGranularity<<"\n";
    msgGetChar();
   }
//--------------------------------------------------------------
void queryVirtualAlloc()
{
	cout<<"\n";
    std::string strSize;
    cout<<"Enter memory block size to allocate or reserve: ";
    cin>>strSize;
    if (strSize.empty())
       {
        msgGetChar("\nInvalid block size taken, press ENTER key to continue\n");
        return;
       }
    SIZE_T blockSize = (SIZE_T)strtol( strSize.c_str(), 0, 0);
    if (!blockSize)
       {
        msgGetChar("\nInvalid block size taken, press ENTER key to continue\n");
        return;
       }
    LPVOID mem = VirtualAlloc( 0, blockSize,MEM_RESERVE,PAGE_READWRITE );
    if (!mem)
       {
        cout<<"VirtualAlloc failed: "<<toOem(formatMessage())<<"\n";
        msgGetChar();
        return;
       }
   cout<<"Memory allocated in address: 0x"<<setw(8)<<setfill('0')<<mem;
   msgGetChar(", press ENTER key to continue\n");
 }
//--------------------------------------------------------------
void queryVirtualFree()
{
	cout<<"\n";
    std::string strAddr;
    cout<<"Enter memory address to free: ";
    cin>>strAddr;
    if (strAddr.empty())
       {
        msgGetChar("\nInvalid address taken, press ENTER key to continue\n");
        return;
       }
    LPVOID requestedAddr = (LPVOID)(WORD)strtol( strAddr.c_str(), 0, 0);
    if (!VirtualFree( requestedAddr, 0, MEM_RELEASE))
       {
        cout<<"Failed to free memory: "<<toOem(formatMessage())<<"\n";
        msgGetChar();
        return;
       }
    msgGetChar("\nMemory released, press ENTER key to continue\n");
}

//--------------------------------------------------------------
void queryGetProcessHeaps()
{
	DWORD dwHeaps = GetProcessHeaps(25, hHeaps); 
	if (dwHeaps > 25) cout<< "Process has more 25 Heaps \n";
	else cout<<"Process has "<<dwHeaps<<" Heaps\n";
	
}
//--------------------------------------------------------------
void queryHeapCreate()
{
	queryGetProcessHeaps();
	cout<<"\n";
    std::string strBeginSize,strMaxSize;
    cout<<"Enter begin size Heap: ";
    cin>>strBeginSize;
	cout<<"Enter Maxsimum size Heap: ";
    cin>>strMaxSize;
    DWORD BeginSize = (DWORD)strtol( strBeginSize.c_str(), 0, 0);
    DWORD MaxSize = (DWORD)strtol( strMaxSize.c_str(), 0, 0);
    if (BeginSize>MaxSize) MaxSize=0;
    HANDLE NewHeap=HeapCreate(0,BeginSize ,MaxSize);
	if (NewHeap==NULL)cout<<"\nNew Heap don not create \n";
	else cout<<"New Heap create /n"; 
	queryGetProcessHeaps();
	msgGetChar();
}
//--------------------------------------------------------------
void queryHeapAlloc()
{
	queryGetProcessHeaps();
	cout<<"\n";
	std::string strSize,strHeaps;
    cout<<"Enter size block: ";
    cin>>strSize;
	DWORD Size = (DWORD)strtol( strSize.c_str(), 0, 0);
   	DWORD dwHeaps = GetProcessHeaps(25, hHeaps);
	AllocMem=(char*)HeapAlloc(hHeaps[dwHeaps-1],0,Size);
	if (AllocMem!=NULL) cout<<"\n not Allocates a block of memory from a heap \n";
	else cout<<"Allocates a block 0x"<<setw(8)<<setfill('0')<<Size<<" of memory from a heap\n";
	msgGetChar();
}
//--------------------------------------------------------------
void queryHeapFree()
{
	DWORD dwHeaps = GetProcessHeaps(25, hHeaps);
	if (HeapFree(hHeaps[dwHeaps-1],0,AllocMem)==0)cout << "Error Free \n";
	else cout<<" Free allocates of memory from a heap!\n";
	msgGetChar();
}
//--------------------------------------------------------------
void queryHeapDestroy()
{
	DWORD dwHeaps = GetProcessHeaps(25, hHeaps);
	if (HeapDestroy(hHeaps[dwHeaps-1])==0)cout << "Error delete Heap \n";
	else cout<<" delete a Heap!\n";
	msgGetChar();
}
//--------------------------------------------------------------
   int main(int argc, char *argv[])
  {
    int userChoise = -1;
    do {
        printMenu();
        userChoise = getInput();
        if (userChoise<=0)
           {
            if (userChoise<0)
               {
                msgGetChar("\nInvalid choise, press ENTER key to continue\n");
               }
            continue;
           }
        switch(userChoise)
           {
            case 1:
                    queryVirtualMemoryStatus();
                    break;
            case 2:
                    queryVirtualAlloc(); 
                    break;
            case 3:
                    queryVirtualFree();
                    break;
            case 4: 
                    queryHeapCreate();
                    break;
            case 5:
                    queryHeapAlloc();
                    break;
            case 6:
                    queryHeapFree(); 
                    break;
            case 7:
                    queryHeapDestroy();
                    break;
            default:
                    msgGetChar("\nInvalid choise,"
                               " press ENTER key to continue\n");
           }
       } while(userChoise);   
    return 0;   
   }
//--------------------------------------------------------------