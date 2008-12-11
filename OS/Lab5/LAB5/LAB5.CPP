// lab5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Функции ----------------------------------------------------------------------------
void ClearScreen();

int main(int argc, char* argv[])
{

	BOOL Flag = 1, FCom;
	char Buffer[100], Path[100];
	DWORD SizePath;
	SYSTEM_INFO SystemInfo;
	MEMORYSTATUS MemStatus;
	LPVOID Address = NULL; MEMORY_BASIC_INFORMATION Buff;

	ClearScreen();
	do{
		SizePath = GetCurrentDirectory(100, Path);
		cout << Path << '>';

		cin >> Buffer;
		ClearScreen(); FCom = 0;

		if(memcmp(Buffer, "gsysinf", 7) == 0){
			GetSystemInfo(&SystemInfo); FCom = 1;
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) cout << "PROCESSOR ARCHITECTURE INTEL" << endl;
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MIPS) cout << "PROCESSOR ARCHITECTURE MIPS" << endl;
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA) cout << "PROCESSOR ARCHITECTURE ALPHA" << endl;
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_PPC) cout << "PROCESSOR ARCHITECTURE PPC" << endl;
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN) cout << "PROCESSOR ARCHITECTURE UNKNOWN" << endl;
 			cout << "Page size used by the VirtualAlloc function - " << SystemInfo.dwPageSize << "Bytes (" << SystemInfo.dwPageSize/1024 << "Kb)" << endl;;
 			cout << "lowest memory address accessible to applications and DLLs - " << SystemInfo.lpMinimumApplicationAddress << endl;
 			cout << "highest memory address accessible to applications and DLLs - " << SystemInfo.lpMaximumApplicationAddress << endl;
 			cout << "Number of processors in the system - " << SystemInfo.dwNumberOfProcessors << endl;
 			cout << "Type of processor in the system - ";
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_INTEL_386) cout << "INTEL 386";
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_INTEL_486) cout << "INTEL 486";
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_INTEL_PENTIUM) cout << "INTEL PENTIUM";
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_MIPS_R4000) cout << "MIPS R4000";
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ALPHA_21064) cout << "ALPHA 21064";
			cout << endl;
 			cout << "Allocation Granularity - " << SystemInfo.dwAllocationGranularity << "Bytes (" << SystemInfo.dwAllocationGranularity/1024 << "Kb)" << endl;
 			cout << "Processor Level - ";
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL){
//				cout << SystemInfo.wProcessorLevel;
				if(SystemInfo.wProcessorLevel == 3) cout << "Intel 80386";
				if(SystemInfo.wProcessorLevel == 4) cout << "Intel 80486";
				if(SystemInfo.wProcessorLevel == 5) cout << "Pentium";
			}
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_MIPS){
				if(SystemInfo.wProcessorLevel == 4) cout << "MIPS R4000";
			}
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ALPHA){
				if(SystemInfo.wProcessorLevel == 21064) cout << "Alpha 21064";
				if(SystemInfo.wProcessorLevel == 21066) cout << "Alpha 21066";
				if(SystemInfo.wProcessorLevel == 21164) cout << "Alpha 21164";
			}
			if(SystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_PPC){
				if(SystemInfo.wProcessorLevel == 1) cout << "PPC 601";
				if(SystemInfo.wProcessorLevel == 3) cout << "PPC 603";
				if(SystemInfo.wProcessorLevel == 4) cout << "PPC 604";
				if(SystemInfo.wProcessorLevel == 6) cout << "PPC 603+";
				if(SystemInfo.wProcessorLevel == 9) cout << "PPC 604+";
				if(SystemInfo.wProcessorLevel == 20) cout << "PPC 620";
			}
			cout << endl;
		}

		if(memcmp(Buffer, "memstat", 6) == 0){
			GlobalMemoryStatus(&MemStatus); FCom = 1;
 			cout << "Sizeof(MEMORYSTATUS) - " << MemStatus.dwLength << "Bytes (" << MemStatus.dwLength/1024/1000 << "Mb)" << endl;;
 			cout << "Percent of memory in use - " << MemStatus.dwMemoryLoad << endl;
 			cout << "Bytes of physical memory - " << MemStatus.dwTotalPhys << "Bytes (" << MemStatus.dwTotalPhys/1024/1000 << "Mb)" << endl;;
 			cout << "Free physical memory bytes - " << MemStatus.dwAvailPhys << "Bytes (" << MemStatus.dwAvailPhys/1024/1000 << "Mb)" << endl;;
 			cout << "Bytes of paging file - " << MemStatus.dwTotalPageFile << "Bytes (" << MemStatus.dwTotalPageFile/1024/1000 << "Mb)" << endl;;
 			cout << "Free bytes of paging file - " << MemStatus.dwAvailPageFile << "Bytes (" << MemStatus.dwAvailPageFile/1024/1000 << "Mb)" << endl;;
 			cout << "User bytes of address space - " << MemStatus.dwTotalVirtual << "Bytes (" << MemStatus.dwTotalVirtual/1024/1000 << "Mb)" << endl;;
 			cout << "Free user bytes - " << MemStatus.dwAvailVirtual << "Bytes (" << MemStatus.dwAvailVirtual/1024/1000 << "Mb)" << endl;;
		}

		if(memcmp(Buffer, "virtq", 5) == 0 && Address != NULL){
			VirtualQuery(Address, &Buff, sizeof(Buff)); FCom = 1;
 			cout << "Address of regionb - " << Address << endl;
 			cout << "base address of region - " << Buff.BaseAddress << endl;
 			cout << "allocation base address - " << Buff.AllocationBase << endl;
			cout << "Protect - ";
			switch(Buff.AllocationProtect){
				case PAGE_READONLY: cout << "READONLY ";
				case PAGE_READWRITE: cout << "READWRITE ";
				case PAGE_WRITECOPY: cout << "WRITECOPY ";
				case PAGE_EXECUTE: cout << "EXECUTE ";
				case PAGE_EXECUTE_READ: cout << "EXECUTE_READ ";
				case PAGE_EXECUTE_READWRITE: cout << "EXECUTE_READWRITE ";
				case PAGE_EXECUTE_WRITECOPY: cout << "EXECUTE_WRITECOPY ";
				case PAGE_GUARD: cout << "GUARD ";
				case PAGE_NOACCESS: cout << "NOACCESS ";
				case PAGE_NOCACHE: cout << "NOCACHE ";
			}
			cout << endl;
 			cout << "RegionSize - " << Buff.RegionSize << endl;
			cout << "State - ";
			switch(Buff.State){
				case MEM_COMMIT: cout << "MEM_COMMIT ";
				case MEM_FREE: cout << "MEM_FREE ";
				case MEM_RESERVE: cout << "MEM_RESERVE ";
			}
			cout << endl;
			cout << "Type - ";
			switch(Buff.Type){
				case MEM_IMAGE: cout << "MEM_IMAGE ";
				case MEM_MAPPED: cout << "MEM_MAPPED ";
				case MEM_PRIVATE: cout << "MEM_PRIVATE ";
			}
			cout << endl;
		}

		if(memcmp(Buffer, "virta", 5) == 0 && Address == NULL){
			FCom = 1;
			if((Address = VirtualAlloc(NULL, 256, MEM_COMMIT, PAGE_READWRITE)) == NULL)
				cout << "Fail."; else cout << "Ok." << endl;
		}

		if(memcmp(Buffer, "virtf", 5) == 0 && Address != NULL){
			VirtualFree(Address, 256, MEM_DECOMMIT); Address = NULL; FCom = 1;
			cout << "Ok." << endl;
		}
// 			cout << "" <<  << endl;
		
		if(memcmp(Buffer, "exit", 4) == 0 && Address == NULL){ Flag = 0; FCom = 1;}
		if(FCom == 0) cout << "Invalid command." << endl;
	}while(Flag == 1);

	return 0;
}

void ClearScreen()
{
	for(unsigned int i=0;i<25;i++) cout << endl;
}

