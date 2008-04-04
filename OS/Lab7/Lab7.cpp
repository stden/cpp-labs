// Lab7.cpp : Defines the entry point for the console application.
//
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using std::cout;
using std::cin;
using std::string;


//------------------------------------------------------
inline void msgGetChar(const char *msg = "\nPress ENTER key to continue\n")
   {
    char ch;
	cout<<msg;
    std::cin.get(ch);
	std::cin.get(ch);
   }
//--------------------------------------------------------------

void printError( TCHAR* msg )
{
  DWORD eNum;
  TCHAR sysMsg[256];
  TCHAR* p;

  eNum = GetLastError( );
  FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, eNum,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         sysMsg, 256, NULL );
  p = sysMsg;
  while( ( *p > 31 ) || ( *p == 9 ) )
    ++p;
  do { *p-- = 0; } while( ( p >= sysMsg ) &&
                          ( ( *p == '.' ) || ( *p < 33 ) ) );
  printf( "\n  WARNING: %s failed with error %d (%s)", msg, eNum, sysMsg );
}

//------------------------------------------------------
int main(int argc, char *argv[])
{
PROCESSENTRY32 pe32;
PROCESSENTRY32 array[100];
WORD i=0;

	HANDLE hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( hProcessSnap == INVALID_HANDLE_VALUE )
		{
		  printError( "CreateToolhelp32Snapshot (of processes)" );
   		  return(1);
		}
    pe32.dwSize = sizeof( PROCESSENTRY32 );
	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		printError( "Process32First" );
		CloseHandle( hProcessSnap );
		return(1);
	}
	array[i]=pe32;
	while( Process32Next( hProcessSnap, &pe32 ) )
	{
		i++	;
		array[i]=pe32;
	} 
	WORD k;
	for (WORD j=0;j!=i ;j++)
	{
		k=j;
		for (WORD z=j+1;z!=i+1; z++)
		{
			if (array[k].cntThreads>array[z].cntThreads) k=z;

		}
		pe32=array[j];
		array[j]=array[k];
		array[k]=pe32;
	}
	printf( "\n=====================================================" );
	printf( "\nNumber \t PROCESS NAME \t Number of threads");
	for (WORD j=0;j!=i+1 ;j++) 
	{
		if (strlen(array[j].szExeFile)>13) printf( "\n %02d \t %s \t %03d",j,array[j].szExeFile,array[j].cntThreads);
		else printf( "\n %02d \t %s \t\t %03d",j,array[j].szExeFile,array[j].cntThreads);
	}
	cout<<"\n";
    std::string Num;
    cout<<"Enter number process: ";
    cin>>Num;
	j = (WORD)strtol( Num.c_str(), 0, 0);
   	if (j>i)
	{
		cout<<"Error!! ";
    	return 1;
	}
  
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
	THREADENTRY32 te32; 
	THREADENTRY32 tearray[300];
	hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 ); 
	if( hThreadSnap == INVALID_HANDLE_VALUE ) return( FALSE ); 
	te32.dwSize = sizeof(THREADENTRY32 ); 
	if( !Thread32First( hThreadSnap, &te32 ) ) 
	{
		printError( "Thread32First" );
		CloseHandle( hThreadSnap );
		return 1;
	}
	i=0;
	do 
	{ 
		if( te32.th32OwnerProcessID == array[j].th32ProcessID )
		{
			tearray[i]=te32;
			i++;
		}
	} while( Thread32Next(hThreadSnap, &te32 ) ); 

	for (WORD j=0;j!=i ;j++)
	{
		k=j;
		for (WORD z=j+1;z!=i+1; z++)
		{
			if (tearray[k].th32ThreadID >tearray[z].th32ThreadID) k=z;

		}
		te32=tearray[j];
		tearray[j]=tearray[k];
		tearray[k]=te32;
	}
	printf( "\n=====================================================" );
	printf( "\n Number \t thread identifier \t Priority a stream ");
	for (WORD j=0;j!=i ;j++) 
	{
		printf( "\n %03d \t\t\t %04d \t\t\t %02d",j+1,tearray[j].th32ThreadID,tearray[j].tpBasePri);
		
	}
	msgGetChar();
	CloseHandle( hThreadSnap );
	CloseHandle( hProcessSnap );
}
