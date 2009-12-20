const
  ntdll = 'ntdll.dll';

const
  RTL_QUERY_PROCESS_HEAP_SUMMARY = $00000004;
  RTL_QUERY_PROCESS_HEAP_TAGS = $00000008;
  RTL_QUERY_PROCESS_HEAP_ENTRIES = $00000010;

  RTL_HEAP_SEGMENT = 2;

  STATUS_SUCCESS = 0;

type
  SYSINF_PAGE_COUNT = ULONG;
  
  PSYSTEM_BASIC_INFORMATION = ^SYSTEM_BASIC_INFORMATION;
  SYSTEM_BASIC_INFORMATION = packed record
    Reserved: ULONG;
    TimerResolution: ULONG;
    PageSize: ULONG;
    NumberOfPhysicalPages: SYSINF_PAGE_COUNT;
    LowestPhysicalPageNumber: SYSINF_PAGE_COUNT;
    HighestPhysicalPageNumber: SYSINF_PAGE_COUNT;
    AllocationGranularity: ULONG;
    MinimumUserModeAddress: Pointer;
    MaximumUserModeAddress: ULONG; // ULONG_PTR;
    ActiveProcessorsAffinityMask: ULONG; // ULONG_PTR;
    NumberOfProcessors: Byte;
    unknown: array [0..2] of Byte;
  end;


  TSystem_Basic_Information = packed record
    dwUnknown1: DWORD;
    uKeMaximumIncrement: ULONG;
    uPageSize: ULONG;
    uMmNumberOfPhysicalPages: ULONG;
    uMmLowestPhysicalPage: ULONG;
    uMmHighestPhysicalPage: ULONG;
    uAllocationGranularity: ULONG;
    pLowestUserAddress: Pointer;
    pMmHighestUserAddress: Pointer;
    uKeActiveProcessors: ULONG;
    bKeNumberProcessors: byte;
    bUnknown2: byte;
    wUnknown3: word;
  end;


  PSYSTEM_THREADS = ^SYSTEM_THREADS;
  SYSTEM_THREADS  = packed record
    KernelTime: LARGE_INTEGER;
    UserTime: LARGE_INTEGER;
    CreateTime: LARGE_INTEGER;
    WaitTime: ULONG;
    StartAddress: Pointer;
    UniqueProcess: DWORD;
    UniqueThread: DWORD;
    Priority: Integer;
    BasePriority: Integer;
    ContextSwitchCount: ULONG;
    State: Longint;
    WaitReason: Longint;
  end;

  PSYSTEM_PROCESS_INFORMATION = ^SYSTEM_PROCESS_INFORMATION;
  SYSTEM_PROCESS_INFORMATION = packed record
    NextOffset: ULONG;
    ThreadCount: ULONG;
    Reserved1: array [0..5] of ULONG;
    CreateTime: FILETIME;
    UserTime: FILETIME;
    KernelTime: FILETIME;
    ModuleNameLength: WORD;
    ModuleNameMaxLength: WORD;
    ModuleName: PWideChar;
    BasePriority: ULONG;
    ProcessID: ULONG;
    InheritedFromUniqueProcessID: ULONG;
    HandleCount: ULONG;
    Reserved2 : array[0..1] of ULONG;
    PeakVirtualSize : ULONG;
    VirtualSize : ULONG;
    PageFaultCount : ULONG;
    PeakWorkingSetSize : ULONG;
    WorkingSetSize : ULONG;
    QuotaPeakPagedPoolUsage : ULONG;
    QuotaPagedPoolUsage : ULONG;
    QuotaPeakNonPagedPoolUsage : ULONG;
    QuotaNonPagedPoolUsage : ULONG;
    PageFileUsage : ULONG;
    PeakPageFileUsage : ULONG;
    PrivatePageCount : ULONG;
    ReadOperationCount : LARGE_INTEGER;
    WriteOperationCount : LARGE_INTEGER;
    OtherOperationCount : LARGE_INTEGER;
    ReadTransferCount : LARGE_INTEGER;
    WriteTransferCount : LARGE_INTEGER;
    OtherTransferCount : LARGE_INTEGER;
    ThreadInfo: array [0..0] of SYSTEM_THREADS;
  end;

const
  IMAGE_ORDINAL_FLAG = DWORD($80000000);
  IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   = 11;
  IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   = 13;

type
  PVOID = Pointer;

  PIMAGE_IMPORT_BY_NAME = ^IMAGE_IMPORT_BY_NAME;
  {$EXTERNALSYM PIMAGE_IMPORT_BY_NAME}
  _IMAGE_IMPORT_BY_NAME = record
    Hint: Word;
    Name: array [0..0] of Char;
  end;
  {$EXTERNALSYM _IMAGE_IMPORT_BY_NAME}
  IMAGE_IMPORT_BY_NAME = _IMAGE_IMPORT_BY_NAME;
  {$EXTERNALSYM IMAGE_IMPORT_BY_NAME}
  TImageImportByName = IMAGE_IMPORT_BY_NAME;
  PImageImportByName = PIMAGE_IMPORT_BY_NAME;

  PIMAGE_THUNK_DATA32 = ^IMAGE_THUNK_DATA32;
  {$EXTERNALSYM PIMAGE_THUNK_DATA32}
  _IMAGE_THUNK_DATA32 = record
    case Integer of
      0: (ForwarderString: PBYTE);
      1: (Function_: PDWORD);
      2: (Ordinal: DWORD);
      3: (AddressOfData: PIMAGE_IMPORT_BY_NAME);
  end;
  {$EXTERNALSYM _IMAGE_THUNK_DATA32}
  IMAGE_THUNK_DATA32 = _IMAGE_THUNK_DATA32;
  {$EXTERNALSYM IMAGE_THUNK_DATA32}
  TImageThunkData32 = IMAGE_THUNK_DATA32;
  PImageThunkData32 = PIMAGE_THUNK_DATA32;

  TIIDUnion = record
    case Integer of
      0: (Characteristics: DWORD);
      1: (OriginalFirstThunk: PIMAGE_THUNK_DATA32);
  end;

  PIMAGE_IMPORT_DESCRIPTOR = ^IMAGE_IMPORT_DESCRIPTOR;
  {$EXTERNALSYM PIMAGE_IMPORT_DESCRIPTOR}
  _IMAGE_IMPORT_DESCRIPTOR = record
    Union: TIIDUnion;
    TimeDateStamp: DWORD;                  // 0 if not bound,
                                           // -1 if bound, and real date\time stamp
                                           //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
                                           // O.W. date/time stamp of DLL bound to (Old BIND)

    ForwarderChain: DWORD;                 // -1 if no forwarders
    Name: DWORD;
    FirstThunk: PIMAGE_THUNK_DATA32;         // RVA to IAT (if bound this IAT has actual addresses)
  end;
  {$EXTERNALSYM _IMAGE_IMPORT_DESCRIPTOR}
  IMAGE_IMPORT_DESCRIPTOR = _IMAGE_IMPORT_DESCRIPTOR;
  {$EXTERNALSYM IMAGE_IMPORT_DESCRIPTOR}
  TImageImportDescriptor = IMAGE_IMPORT_DESCRIPTOR;
  PImageImportDescriptor = PIMAGE_IMPORT_DESCRIPTOR;


  {$EXTERNALSYM ImgDelayDescr}
  ImgDelayDescr = packed record
    grAttrs: DWORD;                 // attributes
    szName: DWORD;                  // pointer to dll name
    phmod: PDWORD;                  // address of module handle
    { TODO : probably wrong declaration }
    pIAT: TImageThunkData32;          // address of the IAT
    { TODO : probably wrong declaration }
    pINT: TImageThunkData32;          // address of the INT
    { TODO : probably wrong declaration }
    pBoundIAT: TImageThunkData32;     // address of the optional bound IAT
    { TODO : probably wrong declaration }
    pUnloadIAT: TImageThunkData32;    // address of optional copy of original IAT
    dwTimeStamp: DWORD;             // 0 if not bound,
                                    // O.W. date/time stamp of DLL bound to (Old BIND)
  end;
  TImgDelayDescr = ImgDelayDescr;
  PImgDelayDescr = ^ImgDelayDescr;


  PloadedImage = ^TLoadedImage;
  {$EXTERNALSYM _LOADED_IMAGE}
  _LOADED_IMAGE = record
    ModuleName: LPSTR;
    hFile: THandle;
    MappedAddress: PChar;
    FileHeader: PImageNtHeaders;
    LastRvaSection: PImageSectionHeader;
    NumberOfSections: ULONG;
    Sections: PImageSectionHeader;
    Characteristics: ULONG;
    fSystemImage: ByteBool;
    fDOSImage: ByteBool;
    Links: TListEntry;
    SizeOfImage: ULONG;
  end;
  {$EXTERNALSYM LOADED_IMAGE}
  LOADED_IMAGE = _LOADED_IMAGE;
  LoadedImage = _LOADED_IMAGE;
  TLoadedImage = _Loaded_IMAGE;

  UNICODE_STRING = record
    Length: WORD;
    MaximumLength: WORD;
    Buffer: PWideChar;
  end;
  PUNICODE_STRING = ^UNICODE_STRING;

  TUNICODE_STRING = packed record
    Length : WORD;
    MaximumLength : WORD;
    Buffer : array [0..MAX_PATH - 1] of WideChar;
  end;

  POBJECT_NAME_INFORMATION = ^TOBJECT_NAME_INFORMATION;
  TOBJECT_NAME_INFORMATION = packed record
    Name : TUNICODE_STRING;
  end;

  OBJECT_ATTRIBUTES = record
    Length: ULONG;
    RootDirectory: THandle;
    ObjectName: PUNICODE_STRING;
    Attributes: ULONG;
    SecurityDescriptor: Pointer;
    SecurityQualityOfService: Pointer;
  end;
  POBJECT_ATTRIBUTES = ^OBJECT_ATTRIBUTES;

  IO_STATUS_BLOCK = record
    case integer of
      0:
       (Status: DWORD);
      1:
       (Pointer: Pointer;
        Information: ULONG);
  end;
  PIO_STATUS_BLOCK = ^IO_STATUS_BLOCK;

  NTSTATUS = DWORD;

  PNT_TIB = ^_NT_TIB;
  _NT_TIB = record
    ExceptionList: Pointer; // ^_EXCEPTION_REGISTRATION_RECORD
    StackBase,
      StackLimit,
      SubSystemTib: Pointer;
    case Integer of
      0: (
        FiberData: Pointer
        );
      1: (
        Version: ULONG;
        ArbitraryUserPointer: Pointer;
        Self: PNT_TIB;
        )
  end;
  NT_TIB = _NT_TIB;
  PPNT_TIB = ^PNT_TIB;

  HANDLE = THandle;

  _CLIENT_ID = record
    UniqueProcess: HANDLE;
    UniqueThread: HANDLE;
  end;
  CLIENT_ID = _CLIENT_ID;
  PCLIENT_ID = ^CLIENT_ID;
  TClientID = CLIENT_ID;
  PClientID = ^TClientID;

  KAFFINITY = ULONG;
  PKAFFINITY = ^KAFFINITY;
  KPRIORITY = DWORD;

  _THREAD_BASIC_INFORMATION = record // Information Class 0
    ExitStatus: NTSTATUS;
    TebBaseAddress: PNT_TIB;
    ClientId: CLIENT_ID;
    AffinityMask: KAFFINITY;
    Priority: KPRIORITY;
    BasePriority: KPRIORITY;
  end;
  THREAD_BASIC_INFORMATION = _THREAD_BASIC_INFORMATION;
  PTHREAD_BASIC_INFORMATION = ^THREAD_BASIC_INFORMATION;
  TThreadBasicInformation = THREAD_BASIC_INFORMATION;
  PThreadBasicInformation = ^TThreadBasicInformation;

  USHORT = Word;

  TSettableAndTag = record
    Settable: ULONG;
    Tag: ULONG;
  end;

  TCommittedSizeAndBlock = record
    CommittedSize: ULONG;
    FirstBlock: Pointer;
  end;

  THeapEntryUnion = record
  case Integer of
    0: (s1: TSettableAndTag);
    1: (s2: TCommittedSizeAndBlock);
  end;

  _RTL_HEAP_ENTRY = record
    Size: ULONG;
    Flags: USHORT;
    AllocatorBackTraceIndex: USHORT;
    u: THeapEntryUnion;
  end;
  RTL_HEAP_ENTRY = _RTL_HEAP_ENTRY;
  PRTL_HEAP_ENTRY = ^RTL_HEAP_ENTRY;
  TRtrHeapEntry = RTL_HEAP_ENTRY;
  PRtrHeapEntry = PRTL_HEAP_ENTRY;
  
//struct rtl_heap_tag
//{
//    uint32_t NumberOfAllocations;
//    uint32_t NumberOfFrees;
//    size_t BytesAllocated;
//    uint16_t TagIndex;
//    uint16_t CreatorBackTraceIndex;
//    wchar_t TagName[ 24 ];
//} ;


  _RTL_HEAP_INFORMATION = record
    BaseAddress: Pointer;
    Flags: ULONG;
    EntryOverhead: USHORT;
    CreatorBackTraceIndex: USHORT;
    BytesAllocated: ULONG;
    BytesCommitted: ULONG;
    NumberOfTags: ULONG;
    NumberOfEntries: ULONG;
    NumberOfPseudoTags: ULONG;
    PseudoTagGranularity: ULONG;
    Reserved: array [0..4] of ULONG;
    Tags: Pointer;
    Entries: PRTL_HEAP_ENTRY;
  end;
  RTL_HEAP_INFORMATION = _RTL_HEAP_INFORMATION;
  PRTL_HEAP_INFORMATION = ^RTL_HEAP_INFORMATION;
  TRtlHeapInformation = RTL_HEAP_INFORMATION;
  PRtlHeapInformation = ^TRtlHeapInformation;

  _RTL_PROCESS_HEAPS = record
    NumberOfHeaps: ULONG;
    Heaps: array [0..0] of RTL_HEAP_INFORMATION;
  end;
  RTL_PROCESS_HEAPS = _RTL_PROCESS_HEAPS;
  PRTL_PROCESS_HEAPS = ^RTL_PROCESS_HEAPS;
  TRtlProcessHeaps = RTL_PROCESS_HEAPS;
  PRtlProcessHeaps = ^TRtlProcessHeaps;

  _RTL_PROCESS_VERIFIER_OPTIONS = record
    SizeStruct: ULONG;
    Option: ULONG;
    OptionData: UCHAR;
  end;
  RTL_PROCESS_VERIFIER_OPTIONS = _RTL_PROCESS_VERIFIER_OPTIONS;
  PRTL_PROCESS_VERIFIER_OPTIONS = ^RTL_PROCESS_VERIFIER_OPTIONS;

  _RTL_DEBUG_INFORMATION = record
    SectionHandleClient: HANDLE;
    ViewBaseClient: PVOID;
    ViewBaseTarget: PVOID;
    ViewBaseDelta: ULONG;
    EventPairClient: HANDLE;
    EventPairTarget: PVOID;
    TargetProcessId: HANDLE;
    TargetThreadHandle: HANDLE;
    Flags: ULONG;
    OffsetFree: ULONG;
    CommitSize: ULONG;
    ViewSize: ULONG;
    {
    union
    {
        PRTL_PROCESS_MODULES Modules;
        PRTL_PROCESS_MODULE_INFORMATION_EX ModulesEx;
    }
    Modules: PVOID;
    BackTraces: PVOID; // PRTL_PROCESS_BACKTRACES
    Heaps: PRTL_PROCESS_HEAPS;
    Locks: PVOID; // PRTL_PROCESS_LOCKS
    SpecificHeap: HANDLE;
    TargetProcessHandle: HANDLE;
    VerifierOptions: RTL_PROCESS_VERIFIER_OPTIONS;
    ProcessHeap: HANDLE;
    CriticalSectionHandle: HANDLE;
    CriticalSectionOwnerThread: HANDLE;
    Reserved: array [0..3] of PVOID;
  end;
  RTL_DEBUG_INFORMATION = _RTL_DEBUG_INFORMATION;
  PRTL_DEBUG_INFORMATION = ^RTL_DEBUG_INFORMATION;
  TRtlDebugInformation = RTL_DEBUG_INFORMATION;
  PRtlDebugInformation = ^TRtlDebugInformation;

  RTL_DRIVE_LETTER_CURDIR = record
    Flags: Word;
    Length: Word;
    TimeStamp: Cardinal;
    DosPath: UNICODE_STRING;
  end;

  PRTL_USER_PROCESS_PARAMETERS = ^RTL_USER_PROCESS_PARAMETERS;
  RTL_USER_PROCESS_PARAMETERS = record
    MaximumLength: Cardinal;
    Length: Cardinal;
    Flags: Cardinal;
    DebugFlags: Cardinal;
    ConsoleHandle: Pointer;
    ConsoleFlags: Cardinal;
    StdInputHandle: Cardinal;
    StdOutputHandle: Cardinal;
    StdErrorHandle: Cardinal;
    CurrentDirectoryPath: UNICODE_STRING;
    CurrentDirectoryHandle: Cardinal;
    DllPath: UNICODE_STRING;
    ImagePathName: UNICODE_STRING;
    CommandLine: UNICODE_STRING;
    Environment: Pointer;
    StartingPositionLeft: Cardinal;
    StartingPositionTop: Cardinal;
    Width: Cardinal;
    Height: Cardinal;
    CharWidth: Cardinal;
    CharHeight: Cardinal;
    ConsoleTextAttributes: Cardinal;
    WindowFlags: Cardinal;
    ShowWindowFlags: Cardinal;
    WindowTitle: UNICODE_STRING;
    DesktopName: UNICODE_STRING;
    ShellInfo: UNICODE_STRING;
    RuntimeData: UNICODE_STRING;
    DLCurrentDirectory: array [0..31] of RTL_DRIVE_LETTER_CURDIR
  end;

  PPEB=^PEB;
  PEB = record
    InheritedAddressSpace: Boolean;
    ReadImageFileExecOptions: Boolean;
    BeingDebugged: Boolean;
    Spare: Boolean;
    Mutant: Cardinal;
    ImageBaseAddress: Pointer;
    LoaderData: Pointer; //PPEB_LDR_DATA;
    ProcessParameters: PRTL_USER_PROCESS_PARAMETERS;
    SubSystemData: Pointer;
    ProcessHeap: Pointer;
    FastPebLock: Pointer;
    FastPebLockRoutine: Pointer;
    FastPebUnlockRoutine: Pointer;
    EnvironmentUpdateCount: Cardinal;
    KernelCallbackTable: PPointer;
    EventLogSection: Pointer;
    EventLog: Pointer;
    FreeList: Pointer; //PPEB_FREE_BLOCK;
    TlsExpansionCounter: Cardinal;
    TlsBitmap: Pointer;
    TlsBitmapBits: array[0..1] of Cardinal;
    ReadOnlySharedMemoryBase: Pointer;
    ReadOnlySharedMemoryHeap: Pointer;
    ReadOnlyStaticServerData: PPointer;
    AnsiCodePageData: Pointer;
    OemCodePageData: Pointer;
    UnicodeCaseTableData: Pointer;
    NumberOfProcessors: Cardinal;
    NtGlobalFlag: Cardinal;
    Spare2: array[0..3] of Byte;
    CriticalSectionTimeout: LARGE_INTEGER;
    HeapSegmentReserve: Cardinal;
    HeapSegmentCommit: Cardinal;
    HeapDeCommitTotalFreeThreshold: Cardinal;
    HeapDeCommitFreeBlockThreshold: Cardinal;
    NumberOfHeaps: Cardinal;
    MaximumNumberOfHeaps: Cardinal;
    ProcessHeaps: Pointer;
    GdiSharedHandleTable: Pointer;
    ProcessStarterHelper: Pointer;
    GdiDCAttributeList: Pointer;
    LoaderLock: Pointer;
    OSMajorVersion: Cardinal;
    OSMinorVersion: Cardinal;
    OSBuildNumber: Cardinal;
    OSPlatformId: Cardinal;
    ImageSubSystem: Cardinal;
    ImageSubSystemMajorVersion: Cardinal;
    ImageSubSystemMinorVersion: Cardinal;
    GdiHandleBuffer: array [0..33] of Cardinal;
    PostProcessInitRoutine: Cardinal;
    TlsExpansionBitmap: Cardinal;
    TlsExpansionBitmapBits: array [0..127] of Byte;
    SessionId: Cardinal;
  end;

  PPROCESS_BASIC_INFORAMTION=^PROCESS_BASIC_INFORMATION;
  PROCESS_BASIC_INFORMATION = record
    ExitStatus: NTStatus;
    PebBaseAddress: PPEB;
    AffinityMask: PCardinal;
    BasePriority: Cardinal;
    uUniqueProcessId: Cardinal;
    uInheritedFromUniqueProcessId: Cardinal;
  end;  

  function NtQuerySystemInformation(
    SystemInformationClass: DWORD;
    SystemInformation : Pointer;
    SystemInformationLength : DWORD;
    var ReturnLength: DWORD
    ): DWORD; stdcall; external 'ntdll.dll';

  function GetModuleFileNameEx(hProcess: THandle; hModule: HINST;
    lpFilename: PChar; nSize: DWORD): DWORD; stdcall; external 'psapi.dll'
    name 'GetModuleFileNameExA';

  function GetMappedFileName(hProcess: HANDLE; lpv: Pointer; lpFilename: LPWSTR;
    nSize: DWORD): DWORD; stdcall; external 'psapi.dll'
    name 'GetMappedFileNameA';

  function OpenThread(dwDesiredAccess: DWORD; bInheritHandle: BOOL;
    dwThreadId: DWORD): THandle; stdcall; external kernel32;

  function MapAndLoad(ImageName, DllPath: LPSTR; LoadedImage: PLoadedImage;
    DotDll, ReadOnly: Bool): Bool; stdcall; external 'Imagehlp.dll';

  function ImageDirectoryEntryToDataEx(Base: Pointer; MappedAsImage: ByteBool;
    DirectoryEntry: Word; var Size: ULONG;
    var FoundHeader: PImageSectionHeader): Pointer; stdcall;
    external 'Imagehlp.dll';
    
  function UnMapAndLoad(LoadedImage: PLoadedImage): Bool; stdcall;
    external 'Imagehlp.dll';

  procedure RtlInitUnicodeString(
    DestinationString : PUNICODE_STRING;
    SourceString : LPCWSTR); stdcall; external ntdll;

  function ZwClose(AHandle: THandle): DWORD; stdcall; external ntdll;

  function ZwOpenFile(FileHandle: PHANDLE; DesiredAccess: ACCESS_MASK;
    ObjectAttributes: POBJECT_ATTRIBUTES; IoStatusBlock: PIO_STATUS_BLOCK;
    ShareAccess: ULONG; OpenOptions: ULONG): DWORD; stdcall; external ntdll;

  function NtQueryObject(ObjectHandle: THandle;
    ObjectInformationClass: DWORD; ObjectInformation: Pointer;
    ObjectInformationLength: ULONG;
    ReturnLength: PDWORD): DWORD; stdcall; external ntdll;

  function NtQueryInformationThread(ThreadHandle: THandle;
    ThreadInformationClass: DWORD;
    ThreadInformation: Pointer; ThreadInformationLength: ULONG;
    ReturnLength: PULONG): DWORD; stdcall; external ntdll;

  function RtlCreateQueryDebugBuffer(
    Size: ULONG; EventPair: BOOLEAN): PRtlDebugInformation; stdcall;
    external ntdll;

  function RtlQueryProcessDebugInformation(
    ProcessId: ULONG; DebugInfoClassMask: ULONG;
    DebugBuffer: PRtlDebugInformation): NTSTATUS; stdcall; external ntdll;

  function RtlDestroyQueryDebugBuffer(
    DebugBuffer: PRtlDebugInformation): NTSTATUS; stdcall; external ntdll;

  function NtQueryInformationProcess(ProcessHandle: Cardinal;
    ProcessInformationClass: Integer;
    ProcessInformation: Pointer;
    ProcessInformationLength: Cardinal;
    ReturnLength: PCardinal): NTStatus; stdcall; external ntdll;
