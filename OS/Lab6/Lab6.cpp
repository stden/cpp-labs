// Lab6.cpp : Defines the entry point for the console application.
//

#define _WIN32_WINNT 0x0500
#define WIN32_LEAN_AND_MEAN
#define STRICT
#define CHECK_PE_CHARACTERICTIC(CHARSVAR, FLAG, INFO) if ((CHARSVAR)&(FLAG)) cout<<"                 "<< INFO <<"\n"
#include <windows.h>
#include <winnt.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <time.h>

#include "tooem.h"
#include "fmtErr.h"

using std::cout;
using std::cin;
using std::setw;
using std::setfill;
using std::uppercase;
using std::nouppercase;
using std::hex;
using std::dec;

//--------------------------------------------------------------
inline void msgGetChar(const char* msg = "\nPress ENTER key to continue\n") {
  char ch;
  cout << msg;
  std::cin.get(ch);
  std::cin.get(ch);
}
//--------------------------------------------------------------
bool checkExe(void* pMem) {
  IMAGE_DOS_HEADER* pImageDosHeader = (IMAGE_DOS_HEADER*)pMem;

  if (pImageDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
    cout << "MZ signature not found\n";
    return false;
  }

  IMAGE_NT_HEADERS* ntHeadrs =
    (IMAGE_NT_HEADERS*)(((char*)pMem) + pImageDosHeader->e_lfanew);

  if (ntHeadrs->Signature == IMAGE_OS2_SIGNATURE) {
    cout << "File is Win16 NewExecutable\n";
    return true;
  } else if (ntHeadrs->Signature == IMAGE_OS2_SIGNATURE_LE) {
    cout << "File is OS/2 Linear Executable\n";
    return true;
  } else if (ntHeadrs->Signature == IMAGE_NT_SIGNATURE)
    cout << "File is Win32 Portable Executable\n";

  cout << "Target CPU: ";

  switch (ntHeadrs->FileHeader.Machine) {
    case IMAGE_FILE_MACHINE_I386     :
      cout << "Intel 386 (x86)" ;
      break;

    case IMAGE_FILE_MACHINE_R3000    :
      cout << "MIPS little-endian (R3000)" ;
      break;

    case 0x160                       :
      cout << "MIPS big-endian" ;
      break;

    case IMAGE_FILE_MACHINE_R4000    :
      cout << "MIPS little-endian (R4000)" ;
      break;

    case IMAGE_FILE_MACHINE_R10000   :
      cout << "MIPS little-endian (R10000)" ;
      break;

    case IMAGE_FILE_MACHINE_WCEMIPSV2:
      cout << "MIPS little-endian WCE v2" ;
      break;

    case IMAGE_FILE_MACHINE_ALPHA    :
      cout << "Alpha AXP" ;
      break;

    case IMAGE_FILE_MACHINE_SH3      :
      cout << "SH3 little-endian" ;
      break;

    case IMAGE_FILE_MACHINE_SH3E     :
      cout << "SH3E little-endian" ;
      break;

    case IMAGE_FILE_MACHINE_SH4      :
      cout << "SH4 little-endian" ;
      break;

    case IMAGE_FILE_MACHINE_ARM      :
      cout << "ARM Little-Endian" ;
      break;

    case IMAGE_FILE_MACHINE_THUMB    :
      cout << "<THUMB?>" ;
      break;

    case IMAGE_FILE_MACHINE_POWERPC  :
      cout << "IBM PowerPC Little-Endian" ;
      break;

    case IMAGE_FILE_MACHINE_IA64     :
      cout << "Intel Architecture 64" ;
      break;

    case IMAGE_FILE_MACHINE_MIPS16   :
      cout << "MIPS16" ;
      break;

    case IMAGE_FILE_MACHINE_ALPHA64  :
      cout << "Alpha AXP64" ;
      break;

    case IMAGE_FILE_MACHINE_MIPSFPU  :
      cout << "MIPSFPU" ;
      break;

    case IMAGE_FILE_MACHINE_MIPSFPU16:
      cout << "MIPSFPU16" ;
      break;

    default :
      cout << "<UNKNOWN>";
  }

  cout << "\n";
  struct tm tmCreationTime;
  _tzset();
  cout << "File created (by linker) at "
       << ctime( (time_t*)&ntHeadrs->FileHeader.TimeDateStamp );
  cout << "Num of symbols in symbol table: "
       << ntHeadrs->FileHeader.NumberOfSymbols << "\n";
  cout << "Characterictics: \n";
#define CHECK_PE_CHARACTERICTIC2(flag, str) \
  CHECK_PE_CHARACTERICTIC( ntHeadrs->FileHeader.Characteristics, \
                           flag, str)

  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_RELOCS_STRIPPED        ,
                           "Relocation information is stripped "
                           "from the file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_EXECUTABLE_IMAGE       ,
                           "The file is executable (there are "
                           "no unresolved external references)");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_LINE_NUMS_STRIPPED     ,
                           "Line numbers are stripped from the file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_LOCAL_SYMS_STRIPPED    ,
                           "Local symbols are stripped from file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_AGGRESIVE_WS_TRIM      ,
                           "Aggressively trim the working set");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_LARGE_ADDRESS_AWARE    ,
                           "The application can handle addresses "
                           "larger than 2 GB");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_BYTES_REVERSED_LO      ,
                           "Bytes of the word are reversed");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_32BIT_MACHINE          ,
                           "Computer supports 32-bit words");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_DEBUG_STRIPPED         ,
                           "Debugging information is stored separately "
                           "in a .dbg file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP,
                           "If the image is on removable media, "
                           "copy and run from the swap file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_NET_RUN_FROM_SWAP      ,
                           "If the image is on the network, "
                           "copy and run from the swap file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_SYSTEM                 ,
                           "System file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_DLL                    ,
                           "DLL file");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_UP_SYSTEM_ONLY         ,
                           "File should be run only on a "
                           "uniprocessor computer");
  CHECK_PE_CHARACTERICTIC2(IMAGE_FILE_BYTES_REVERSED_HI      ,
                           "ReversedHi");

  if (ntHeadrs->FileHeader.SizeOfOptionalHeader
      == IMAGE_SIZEOF_ROM_OPTIONAL_HEADER &&
      ntHeadrs->OptionalHeader.Magic == IMAGE_ROM_OPTIONAL_HDR_MAGIC)
    cout << "Type: ROM Image\n";

  if (ntHeadrs->FileHeader.SizeOfOptionalHeader
      == IMAGE_SIZEOF_NT_OPTIONAL64_HEADER &&
      ntHeadrs->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
    cout << "Type: PE/64 Image\n";

  if (ntHeadrs->FileHeader.SizeOfOptionalHeader
      == IMAGE_SIZEOF_NT_OPTIONAL32_HEADER &&
      ntHeadrs->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    cout << "Type: PE/32 Image\n";
    cout << "Linker version: "
         << (unsigned)ntHeadrs->OptionalHeader.MajorLinkerVersion << "."
         << (unsigned)ntHeadrs->OptionalHeader.MinorLinkerVersion << "\n";
    cout << "Code size: " << ntHeadrs->OptionalHeader.SizeOfCode << "\n";
    cout << "Initialized data size: "
         << ntHeadrs->OptionalHeader.SizeOfInitializedData << "\n";
    cout << "Uninitialized data size: "
         << ntHeadrs->OptionalHeader.SizeOfUninitializedData << "\n";
    cout << hex << uppercase << setfill('0') << setw(8);
    cout << "Entry point (RVA): 0x"
         << ntHeadrs->OptionalHeader.AddressOfEntryPoint << "\n";
    cout << "Code base address (RVA): 0x"
         << ntHeadrs->OptionalHeader.BaseOfCode << "\n";
    cout << "Image base address: 0x"
         << ntHeadrs->OptionalHeader.ImageBase << "\n";
    cout << dec << nouppercase << setfill(' ') << setw(0);
    cout << "Min subsystem version: "
         << ntHeadrs->OptionalHeader.MajorSubsystemVersion << "."
         << ntHeadrs->OptionalHeader.MinorSubsystemVersion << "\n";
  }

  return true;
}
//--------------------------------------------------------------
int main(int argc, char* argv[]) {
  cout << "\n";
  char FileName[255];
  cout << "Enter file name: ";
  cin >> FileName;
  HANDLE hFile = CreateFile((LPTSTR)FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

  if (hFile == INVALID_HANDLE_VALUE) {
    cout << "Failed to open file\n";
    msgGetChar();
    return 1;
  }

  HANDLE hMap = CreateFileMapping( hFile, 0, PAGE_READWRITE, 0, sizeof(hFile), FileName);

  if (hMap == NULL) {
    cout << "Failed to create file mapping\n";
    msgGetChar();
    return 1;
  }

  char* pMem = (char*)MapViewOfFile( hMap, FILE_MAP_WRITE, 0, 0, sizeof(hFile));

  if (pMem == NULL) {
    cout << "Failed to map file to memory\n";
    msgGetChar();
    return 1;
  }

  if (!checkExe(pMem)) cout << "File '" << FileName << "' is not an executable file\n";

  msgGetChar();
  UnmapViewOfFile( (LPCVOID)pMem );
  CloseHandle(hFile);
  return 0;
}
//--------------------------------------------------------------