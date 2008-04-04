// Lab1.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#define STRICT
#include <windows.h>

#include <string>
#include <iostream>
#include <iomanip>
#include "Lmcons.h"
#include "tooem.h"

using std::cout;
using std::setw;
using std::setfill;
using std::uppercase;
using std::hex;
using std::dec;

//--------------------------------------------------------------
std::string getUserName()
   {
    char buf[UNLEN + 1];
    DWORD size = sizeof(buf);
    if (!GetUserName( buf, &size)) 
       return std::string("<UNKNOWN>");
    return std::string(buf);
   }
//--------------------------------------------------------------
std::string getProcessorArchitectureStr(WORD pa)
   {
    switch(pa)
       {
        case PROCESSOR_ARCHITECTURE_INTEL: 
             return std::string("INTEL");
        case PROCESSOR_ARCHITECTURE_MIPS:  
             return std::string("MIPS");
        case PROCESSOR_ARCHITECTURE_ALPHA: 
             return std::string("ALPHA");
        case PROCESSOR_ARCHITECTURE_PPC:   
             return std::string("PPC");
        case PROCESSOR_ARCHITECTURE_IA64:  
             return std::string("IA64");
        case PROCESSOR_ARCHITECTURE_AMD64: 
             return std::string("AMD64");
        default: 
             return std::string("UNKNOWN");       
       };
   }
//--------------------------------------------------------------
std::string getLogicalDriveTypeStr(UINT lgType)
   {
    switch(lgType)
       {
        case DRIVE_REMOVABLE:   
             return std::string("Diskette/Flash Drive");
        case DRIVE_FIXED:       
             return std::string("HDD");
        case DRIVE_REMOTE:      
             return std::string("Network");
        case DRIVE_CDROM:       
             return std::string("CD/DVD-ROM");
        case DRIVE_RAMDISK:     
             return std::string("RAM-Disk");
        case DRIVE_NO_ROOT_DIR: 
             return std::string("Root path is invalid ", "(no volume is mounted)");
        default: 
             return std::string("The drive type cannot be determined");
       }
   }
//--------------------------------------------------------------
int main(int argc, char* argv[])
   {
    cout<<"User name: "<<toOem(getUserName())<<"\n\n";
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    cout<<"System Information\n";
    cout<<"      Processor Architecture: "<<getProcessorArchitectureStr(si.wProcessorArchitecture)<<"\n";
    cout<<"      Level: "<<si.wProcessorLevel;
    if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL)
       {
        if (si.wProcessorLevel>4)
           {
            cout<<"   Model: "<<((si.wProcessorRevision>>8)&0xFF)<<"   Stepping: "<<(si.wProcessorRevision&0xFF)<<"\n";
           }
        else
           {
            WORD xx = (si.wProcessorRevision>>8)&0xFF;
            if (xx==0xFF)
               { 
                cout<<"   Model: "<<((si.wProcessorRevision>>4)&0x0F)<<"   Stepping: "<<(si.wProcessorRevision&0x0F)<<"\n";
               }
            else
               { 
                cout<<"   Stepping: "<<(char('A'+(si.wProcessorRevision>>4)&0x0F))<<"."<<(si.wProcessorRevision&0x0F)<<"\n";
               }
           }
       }
    else
       {
        cout<<"   Revision: "<<si.wProcessorRevision<<"\n";
       }

    cout<<"      Page size: "<<si.dwPageSize<<" bytes\n";
    cout<<std::uppercase<<hex;
    cout<<"      Minimum Application Address: 0x"<<setw(8)<<setfill('0')<<si.lpMinimumApplicationAddress<<"\n";
    cout<<"      Maximum Application Address: 0x"<<setw(8)<<setfill('0')<<si.lpMaximumApplicationAddress<<"\n";
    cout<<setw(0)<<setfill(' ')<<dec;
    cout<<"      Number of processors: "<<si.dwNumberOfProcessors<<"\n";cout<<"      Active processors: ";
    bool first = true;

    for(int activeProcessor=0; activeProcessor<32; ++activeProcessor)
       {
        if (si.dwActiveProcessorMask&1)
           {
            if (!first) cout<<", ";
            cout<<"#"<<activeProcessor+1;
            first = false;
           }
        si.dwActiveProcessorMask>>=1;
       }
    cout<<"\n";
    cout<<"      Allocation granularity: "<<si.dwAllocationGranularity<<"\n";

    cout<<"\nLogical Drive Information\n";
    
	char DriveBuf[109];
	GetLogicalDriveStrings(108,DriveBuf);
    char driveNameBuf[4] ;
	WORD i=0; 
	while( DriveBuf[i*4] != 0 )
       {
			driveNameBuf[0] = DriveBuf[i*4+0];
			driveNameBuf[1] = DriveBuf[i*4+1];
			driveNameBuf[2] = DriveBuf[i*4+2];
			driveNameBuf[3] = DriveBuf[i*4+3];
            
			cout<<driveNameBuf<<" - "<<getLogicalDriveTypeStr(GetDriveType( driveNameBuf ));
            cout<<"\n";
			
			char NameBuffer[MAX_PATH], SysNameBuffer[MAX_PATH];
			DWORD VSNumber ,MCLength ,FileSF;
			if (GetVolumeInformation(driveNameBuf,NameBuffer, sizeof(NameBuffer),&VSNumber,&MCLength,&FileSF,SysNameBuffer,sizeof(SysNameBuffer)))
				{
					cout << "             Volume name: "<< NameBuffer << "\n";
					cout << "        File system name: "<< SysNameBuffer << "\n";
					cout << "    Volume serial number: "<< VSNumber << "\n";
					cout << "Maximum file name length: "<< MCLength << "\n";
				}
           i++;      
       }
    cout<<"\n";
    return 0;
   }
//--------------------------------------------------------------