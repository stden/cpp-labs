// �ਫ������ � �������� ࠡ�⠬ �� �� �� C/C++
// ���ᠭ�� ����室���� �㭪権 � ������� ������

//  �ਫ������ 1. �㭪樨 � �������� ��� ����祭�� ���ଠ樨 � ���᫨⥫쭮� ��⥬�
// =====================================================================================

VOID GetSystemInfo( //����祭�� ���ଠ樨 � ��⥬�
  LPSYSTEM_INFO lpSystemInfo // system information - ���ଠ�� � ��⥬� [out]
);

BOOL GetComputerName( // ��।������ ����� ��������
  LPTSTR lpBuffer, // computer name - ���� ��� ����� �������� [in]
  LPDWORD lpnSize // size of name buffer - ࠧ��� ���� / ����� ����� [in/out]
);

BOOL GetComputerNameEx( // ��।������ ����� ��������
  COMPUTER_NAME_FORMAT NameType, // name type - ⨯ ����� [in]
  LPTSTR lpBuffer, // name buffer - ���� ��� ����� �������� [out]
  LPDWORD lpnSize // size of name buffer- ࠧ��� ���� / ����� ����� [in/out]
);

BOOL GetUserName( // ��।������ ����� ���짮��⥫�
  LPTSTR lpBuffer, // name buffer - ���� ��� ����� [out]
  LPDWORD nSize // size of name buffer - ࠧ��� ���� [in/out]
);

BOOLEAN GetUserNameEx( // ��।������ ����� ���짮��⥫�
  EXTENDED_NAME_FORMAT NameFormat, // name format - �ଠ� ����� [in]
  LPTSTR lpNameBuffer, // name buffer - ���� ��� ����� [out]
  PULONG nSize // size of name buffer - ࠧ��� ���� / ����� ����� [in/out]
);

DWORD GetLogicalDrives(VOID); // ��।������ ����㯭�� �����᪨� ��᪮� (��᪠) [out]

DWORD GetLogicalDriveStrings( // ��।������ ����㯭�� �����᪨� ��᪮� (��ப�) [out]
  DWORD nBufferLength, // size of buffer - ����� ���� [in]
  LPTSTR lpBuffer // drive strings buffer - ���� ��� ��ப� [out]
);

UINT GetDriveType( // ��।������ ⯯� ���ன�⢠ [out]
  LPCTSTR lpRootPathName // root directory - ��� ��୥���� ��⠫��� [in]
);

BOOL GetDiskFreeSpace( // ��।������ ��ꥬ� ᢮������� ����࠭�⢠ �� ��᪥
  LPCTSTR lpRootPathName, // root path - ��� ��୥���� ��⠫��� [in]
  LPDWORD lpSectorsPerCluster, // sectors per cluster - �᫮ ᥪ�஢ � ������ [out]
  LPDWORD lpBytesPerSector, // bytes per sector - �᫮ ���⮢ � ᥪ�� [out]
  LPDWORD lpNumberOfFreeClusters, // free clusters - �᫮ ᢮������ �����஢ [out]
  LPDWORD lpTotalNumberOfClusters // total clusters - ��饥 �᫮ �����஢ [out]
);

BOOL GetDiskFreeSpaceEx( // ��।������ ��ꥬ� ᢮������� ����࠭�⢠ �� ��᪥
  LPCTSTR lpDirectoryName, // directory name- ��� ��⠫��� [in]
  PULARGE_INTEGER lpFreeBytesAvailable, // bytes available to caller - ����㯭�� ���⮢ [out]
  PULARGE_INTEGER lpTotalNumberOfBytes, // bytes on disk - ���⮢ �� ��᪥ [out]
  PULARGE_INTEGER lpTotalNumberOfFreeBytes // free bytes on disk - ᢮������ ���⮢ [out]
);

BOOL GetVolumeInformation( // ����祭�� ���ଠ樨 � ⮬�
  LPCTSTR lpRootPathName, // root directory -��� ��୥���� ��⠫��� [in]
  LPTSTR lpVolumeNameBuffer, // volume name buffer - ���� ��� ����� ⮬� [out]
  DWORD nVolumeNameSize, // length of name buffer - ����� ���� [in]
  LPDWORD lpVolumeSerialNumber, // volume serial number - �਩�� ����� ⮬� [out]
  LPDWORD lpMaximumComponentLength, // maximum file name length - ����.����� ����� ⮬� [out]
  LPDWORD lpFileSystemFlags, // file system options - 䫠�� 䠩����� ��⥬� (��) [out]
  LPTSTR lpFileSystemNameBuffer, // file system name buffer - ���� ��� ����� �� [out]
  DWORD nFileSystemNameSize // length of file system name buffer - ����� ���� ��� ����� �� [in]
);

//  �������� ������
// ==================

typedef struct _SYSTEM_INFO {
  DWORD dwOemId;
  struct {
    WORD wProcessorArchitecture; // ���⥪��� ������
    WORD wReserved;
  }
  DWORD dwPageSize; // ࠧ��� ��࠭��� �����
  LPVOID lpMinimumApplicationAddress; // ������ �࠭�� ����㯭��� ���᭮�� ����࠭�⢠
  LPVOID lpMaximumApplicationAddress; // ������ �࠭�� ����㯭��� ���᭮�� ����࠭�⢠
  DWORD dwActiveProcessorMask; // ��᪠ ��⨢���� �����஢
  DWORD dwNumberOfProcessors; // �᫮ �����஢
  DWORD dwProcessorType; // ⨯ ������
  DWORD dwAllocationGranularity; // �࠭��୮��� १�ࢨ஢���� ॣ����� �����
  WORD wProcessorLevel; // �஢��� ������
  WORD wProcessorRevision; // �������⥫쭠� ���ଠ�� � ������
} SYSTEM_INFO, +LPSYSTEM_INFO;

//  �ਫ������ 2. �㭪樨 � �������� ��� ����権 ��� ��ॢ�� ��⠫����
// ======================================================================

DWORD GetCurrentDirectory( // ��।������ ⥪�饣� ��⠫��� [out]
  DWORD nBufferLength, // size of directory buffer - ࠧ��� ���� ��� ��⠫��� [in]
  LPTSTR lpBuffer // directory buffer - ���� ��� ��⠫��� [out]
);

BOOL SetCurrentDirectory( // ��⠭���� ⥪�饣� ��⠫���
  LPCTSTR lpPathName // new directory name - ����� ��� ��⠫��� [in]
);

UINT GetSystemDirectory( // ��।������ ��⥬���� ��⠫��� [out]
  LPTSTR lpBuffer, // buffer for system directory - ���� ��� ��⥬���� ��⠫��� [out]
  UINT uSize // size of directory buffer- ࠧ��� ���� [in]
);

UINT GetWindowsDirectory( // ��।������ ��⠫��� Windows [out]
  LPTSTR lpBuffer, // buffer for Windows directory - ���� ��� ��⠫��� Windows [out]
  UINT uSize // size of directory buffer - ࠧ��� ���� [in]
);

DWORD GetFullPathName( // ��।������ ������� ��� � 䠩�� [out]
  LPCTSTR lpFileName, // file name - ��� 䠩�� [in]
  DWORD nBufferLength, // size of path buffer - ࠧ��� ���� ��� ��� [in]
  LPTSTR lpBuffer, // path buffer - ���� ��� ��� [out]
  LPTSTR* lpFilePart // address of file name in path - ���� ����� 䠩�� � ��� [out]
);

DWORD GetLongPathName( // �८�ࠧ������ ��� � ������� ��� [out]
  LPCTSTR lpszShortPath, // file name - ��室�� (���⪨�) ���� [in]
  LPTSTR lpszLongPath, // path buffer - ���� �������� ��� [out]
  DWORD cchBuffer // size of path buffer - ࠧ��� ���� �������� ��� [in]
);

DWORD GetShortPathName( �८�ࠧ������ ��� � ������ ��� [out]
                        LPCTSTR lpszLongPath, // null-terminated path string - ��室�� (������) ���� [in]
                        LPTSTR lpszShortPath, // short form buffer - [in/out] - ���� ��� ���⪮�� ��� [out]
                        DWORD cchBuffer // size of short form buffer - ࠧ��� ���� ��� ���⪮�� ��� [in]
                      );

DWORD SearchPath( // ���� ��� [out]
  LPCTSTR lpPath, // search path - ��室�� ���� ��� ���᪠ [in]
  LPCTSTR lpFileName, // file name - ��� 䠩�� [in]
  LPCTSTR lpExtension, // file extension - ���७�� ����� 䠩�� [in]
  DWORD nBufferLength, // size of buffer - ࠧ��� ���� ��� �᪮���� ��� [in]
  LPTSTR lpBuffer, // found file name buffer - ���� ��� �᪮���� ��� [out]
  LPTSTR* lpFilePart // file component - ���� ��砫� ����� 䠩�� [out]
);

//  �ਫ������ 3. �㭪樨 � �������� ��� ����権 ��� ��⠫����� � 䠩����
// =========================================================================

BOOL CreateDirectory( //�������� ��⠫���
  LPCTSTR lpPathName, // directory name - ��� ᮧ��������� ��⠫��� [in]
  LPSECURITY_ATTRIBUTES lpSecurityAttributes // SD - ���ਯ�� ������᭮�� [in/out]
);

BOOL CreateDirectoryEx( // �������� ��⠫���
  LPCTSTR lpTemplateDirectory, // template directory - ��ࠧ�� ��⠫��� [in]
  LPCTSTR lpNewDirectory, // directory name - ��� ᮧ��������� ��⠫��� [in]
  LPSECURITY_ATTRIBUTES lpSecurityAttributes // SD - ���ਯ�� ������᭮�� [in]
);

BOOL RemoveDirectory( // �������� ��⠫���
  LPCTSTR lpPathName // directory name - ���� [in]
);

BOOL CopyFile( // ����஢���� 䠩��
  LPCTSTR lpExistingFileName, // name of an existing file - ��� �������饣� 䠩�� [in]
  LPCTSTR lpNewFileName, // name of new file - ��� ������ 䠩�� [in]
  BOOL bFailIfExists // operation if file exists - ��� �������� � ���� ������ [in]
);
BOOL CopyFileEx( // ����஢���� 䠩��
  LPCTSTR lpExistingFileName, // name of existing file - ��� �������饣� 䠩�� [in]
  LPCTSTR lpNewFileName, // name of new file - ��� ������ 䠩�� [in]
  LPPROGRESS_ROUTINE lpProgressRoutine, // callback function - ��ࠡ��稪 [in]
  LPVOID lpData, // callback parameter - ����� ��� ��ࠡ��稪� [in]
  LPBOOL pbCancel, // cancel status - �⪠� �� ��ࠡ�⪨ [in]
  DWORD dwCopyFlags // copy options - 䫠�� ����஢���� [in]
);

BOOL MoveFile( // ��६�饭�� 䠩��
  LPCTSTR lpExistingFileName, // file name - ��� �������饣� 䠩�� [in]
  LPCTSTR lpNewFileName // new file name - ��� ������ 䠩�� [in]
);
BOOL MoveFileEx( // ��६�饭�� 䠩��
  LPCTSTR lpExistingFileName, // file name - ��� �������饣� 䠩�� [in]
  LPCTSTR lpNewFileName, // new file name - ��� ������ 䠩�� [in]
  DWORD dwFlags // move options - 䫠�� ��६�饭�� [in]


  BOOL ReplaceFile( // ����饭�� 䠩��
    LPCTSTR lpReplacedFileName, // file name - ��� ����頥���� 䠩�� [in]
    LPCTSTR lpReplacementFileName, // replacement file - ��� ������饣� 䠩�� [in]
    LPCTSTR lpBackupFileName, // optional backup file - ��� ��࠭塞��� 䠩�� [in]
    DWORD dwReplaceFlags, // replace options - 䫠�� ����饭�� [in]
    LPVOID lpExclude, // reserved - १�� [in]
    LPVOID lpReserved // reserved - १�� [in]
  );

  BOOL DeleteFile( // �������� 䠩��
    LPCTSTR lpFileName // file name - ��� 䠩�� [in]
  );

  //  �ਫ������ 4. �㭪樨 � �������� ��� ����権 ��� �ࠪ���⨪��� 䠩���
  // ============================================================================

  HANDLE CreateFile( // �������� 䠩�� [out]
    LPCTSTR lpFileName, // file name - ��� 䠩�� [in]
    DWORD dwDesiredAccess, // access mode - �ࠢ� ����㯠 [in]
    DWORD dwShareMode, // share mode - ०�� ࠧ������� 䠩�� [in]
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, // SD - ��ਡ��� 쥧���᭮�� [in]
    DWORD dwCreationDisposition, // how to create - �������� � �������騬 䠩��� [in]
    DWORD dwFlagsAndAttributes, // file attributes - 䫠�� � ��ਡ��� 䠩�� [in]
    HANDLE hTemplateFile); // handle to template file - ��� 䠩��-��ࠧ� [in]


  BOOL GetFileInformationByHandle( // ����祭�� ���ଠ樨 � 䠩�� �� ����
    HANDLE hFile, // handle to file - ��� 䠩�� [in]
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation); // buffer - ���ଠ�� � 䠩�� [out]


  DWORD GetFileType( // ��।������ ⨯� 䠩�� [out]
    HANDLE hFile); // handle to file - ��� 䠩�� [in]


  DWORD GetFileSize( // ��।������ ࠧ��� 䠩�� [out]
    HANDLE hFile, // handle to file - ��� 䠩�� [in]
    LPDWORD lpFileSizeHigh); // high-order word of file size - ����� ���� ᫮�� ࠧ��� 䠩�� [out]

  BOOL GetFileSizeEx( // ��।������ ࠧ��� 䠩��
    HANDLE hFile, // handle to file - ��� 䠩�� [in]
    PLARGE_INTEGER lpFileSize); // file size - ࠧ��� 䠩�� [out]

  DWORD GetFileAttributes( // ����祭�� ��ਡ�⮢ 䠩�� [out]
    LPCTSTR lpFileName); // name of file or directory - ��� 䠩�� ��� ��⠫��� [in]

  BOOL GetFileAttributesEx( // ����祭�� ��ਡ�⮢ 䠩��
    LPCTSTR lpFileName, // file or directory name - ��� 䠩�� ��� ��⠫��� [in]
    GET_FILEEX_INFO_LEVELS fInfoLevelId, // attribute - ��ꥬ ���ଠ樨 [in]
    LPVOID lpFileInformation); // attribute information - ���ଠ�� �� ��ਡ��� [out]

  BOOL SetFileAttributes( // ��⠭���� ��ਡ�⮢ 䠩��
    LPCTSTR lpFileName, // file name - ��� 䠩�� [in]
    DWORD dwFileAttributes); // attributes - ��ਡ��� 䠩�� [in]


  void GetSystemTime( // ����祭�� �⬥⮪ �६��� � �ଠ� SystemTime
    LPSYSTEMTIME lpSystemTime); // ��⥬��� �६� [out]


  BOOL GetFileTime( // ����祭�� �⬥⮪ �६��� � �ଠ� FileTime
    HANDLE hFile, // ��� 䠩�� [in]
    LPFILETIME lpCreationTime, // �६� ᮧ����� [out]
    LPFILETIME lpLastAccessTime, // �६� ��᫥����� ����㯠 [out]
    LPFILETIME lpLastWriteTime); // �६� ��᫥���� ����� [out]

  BOOL SetFileTime( // ��⠭���� �⬥⮪ �६��� � �ଠ� FileTime
    HANDLE hFile, // ��� 䠩�� [in]
    const FILETIME* lpCreationTime, // �६� ᮧ����� [in]
    const FILETIME* lpLastAccessTime, // �६� ��᫥����� ����㯠 [in]
    const FILETIME* lpLastWriteTime); // �६� ��᫥���� ����� [in]


  BOOL SystemTimeToFileTime( // �८�ࠧ������ �ଠ⮢ �६���
    const SYSTEMTIME* lpSystemTime, // �⬥⪠ �६��� � �ଠ� SystemTime [in]
    LPFILETIME lpFileTime); // �⬥⪠ �६��� � �ଠ� FileTime [out]
  BOOL FileTimeToSystemTime( // �८�ࠧ������ �ଠ⮢ �६���
    const FILETIME* lpFileTime, // �⬥⪠ �६��� � �ଠ� FileTime [in]
    LPSYSTEMTIME lpSystemTime); // �⬥⪠ �६��� � �ଠ� SystemTime [out]


  BOOL FileTimeToDosDateTime( // �८�ࠧ������ �ଠ⮢ �६���
    CONST FILETIME* lpFileTime, // file time - �⬥⪠ �६��� � �ଠ� FileTime [in]
    LPWORD lpFatDate, // MS-DOS date - �⬥⪠ �६��� � �ଠ� FatDate [out]
    LPWORD lpFatTime); // MS-DOS time - �⬥⪠ �६��� � �ଠ� FatTime [out]


  BOOL DosDateTimeToFileTime( // �८�ࠧ������ �ଠ⮢ �६���
    WORD wFatDate, // 16-bit MS-DOS date - �⬥⪠ �६��� � �ଠ� FatDate [in]
    WORD wFatTime, // 16-bit MS-DOS time - �⬥⪠ �६��� � �ଠ� FatTime [in]
    LPFILETIME lpFileTime); // file time - �⬥⪠ �६��� � �ଠ� FileTime [out]


  LONG CompareFileTime( // Cࠢ����� 2-� �⬥⮪ �६��� � �ଠ� FileTime [out]
    const FILETIME* lpFileTime1, // 1-� �⬥⪠ �६��� [in]
    const FILETIME* lpFileTime2); // 2-� �⬥⪠ �६��� [in]

  //  �������� ������
  // ==================

typedef struct _BY_HANDLE_FILE_INFORMATION { // ����祭�� ���ଠ樨 � 䠩�� �� ��� ����
  DWORD dwFileAttributes; // ��ਡ��� 䠩��
  FILETIME ftCreationTime; // �६� ᮧ�����
  FILETIME ftLastAccessTime; // �६� ��᫥����� ����㯠
  FILETIME ftLastWriteTime; // �६� ��᫥���� ����� (����䨪�樨)
  DWORD dwVolumeSerialNumber; // �਩�� ����� ⮬�
  DWORD nFileSizeHigh; // ࠧ��� 䠩�� (��.�.)
  DWORD nFileSizeLow; // ࠧ��� 䠩�� (��.�.)
  DWORD nNumberOfLinks; // �᫮ ��뫮�
  DWORD nFileIndexHigh; // ������ 䠩�� (��.�.)
  DWORD nFileIndexLow; // ������ 䠩�� (��.�.)
} BY_HANDLE_FILE_INFORMATION;

typedef struct _SYSTEMTIME { // st
  WORD wYear;
  WORD wMonth;
  WORD wDayOfWeek;
  WORD wDay;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliseconds;
} SYSTEMTIME;

typedef struct _FILETIME { // ft
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME;

//  �ਫ������ 5. �㭪樨 � �������� ��� ����権 ��� ����㠫쭮� �������
// ========================================================================

VOID GlobalMemoryStatus( // ��।������ ���ﭨ� ������쭮� �����
  LPMEMORYSTATUS lpBuffer); // memory status structure - ���� ���ﭨ� ������쭮� ����� [out]

BOOL GlobalMemoryStatusEx( // ��।������ ���ﭨ� ������쭮� �����
  LPMEMORYSTATUSEX lpBuffer); // memory status structure- ���� ���ﭨ� ������쭮� ����� [in/out]


LPVOID VirtualAlloc( // �뤥����� ����㠫쭮� �����
  LPVOID lpAddress, // region to reserve or commit - ���� ॣ���� [in]
  SIZE_T dwSize, // size of region - ࠧ��� ॣ���� [in]
  DWORD flAllocationType, // type of allocation - ⨯ �뤥����� [in]
  DWORD flProtect); // type of access protection - ⨯ ����� ����㯠 [in]
LPVOID VirtualAllocEx( // �뤥����� ����㠫쭮� �����
  HANDLE hProcess, // process to allocate memory - ��� ����� [in]
  LPVOID lpAddress, // desired starting address - ������� ���⮢� ���� [in]
  SIZE_T dwSize, // size of region to allocate - ࠧ��� ॣ���� [in]
  DWORD flAllocationType, // type of allocation - ⨯ �뤥����� [in]
  DWORD flProtect); // type of access protection - ⨯ ����� ����㯠 [in]

BOOL VirtualFree( // �᢮�������� ����㠫쭮� �����
  LPVOID lpAddress, // address of region - ���� ॣ���� [in]
  SIZE_T dwSize, // size of region - ࠧ��� ॣ���� [in]
  DWORD dwFreeType); // operation type - ⨯ ����樨 [in]
BOOL VirtualFreeEx( // �᢮�������� ����㠫쭮� �����
  HANDLE hProcess, // handle to process - ��� ����� [in]
  LPVOID lpAddress, // starting address of memory region - ���⮢� ���� ॣ���� [in]
  SIZE_T dwSize, // size of memory region - ࠧ��� ॣ���� [in]
  DWORD dwFreeType); // operation type - ⨯ ����樨 [in]

DWORD VirtualQuery( // ����� ����㠫쭮� ����� [out]
  LPCVOID lpAddress, // address of region - ���� ॣ���� [in]
  PMEMORY_BASIC_INFORMATION lpBuffer, // information buffer - ���� ��� ���ଠ樨 [out]
  SIZE_T dwLength); // size of buffer - ࠧ��� ���� [in]

DWORD VirtualQueryEx( // ����� ����㠫쭮� ����� [out]
  HANDLE hProcess, // handle to process - ��� ����� [in]
  LPCVOID lpAddress, // address of region - ���� ॣ���� [in]
  PMEMORY_BASIC_INFORMATION lpBuffer, // information buffer - ���� ��� ���ଠ樨 [out]
  SIZE_T dwLength); // size of buffer - ࠧ��� ���� [in]


// �ਬ�砭��: Heap - �������᪠� ������� ����� (���)

HANDLE GetProcessHeap(VOID); // ����祭�� ���� ��� ����� [out]

DWORD GetProcessHeaps( // ����祭�� ����� ��� ����� [out]
  DWORD NumberOfHeaps, // maximum number of heap handles - ���ᨬ��쭮� �᫮ ����� [in]
  PHANDLE ProcessHeaps); // buffer for heap handles - ���� ��� ����� ��� ����� [out]


LPVOID HeapAlloc( // �뤥����� ���
  HANDLE hHeap, // handle to private heap block - ��� ��� [in]
  DWORD dwFlags, // heap allocation control - �ࠢ����� �뤥������ ��� [in]
  SIZE_T dwBytes); // number of bytes to allocate - �᫮ ����訢����� ���⮢ [in]


HANDLE HeapCreate( // �������� ��� [out]
  DWORD flOptions, // heap allocation attributes - ��ਡ��� ��� [in]
  SIZE_T dwInitialSize, // initial heap size - ��砫�� ࠧ��� ��� [in]
  SIZE_T dwMaximumSize); // maximum heap size - ���ᨬ���� ࠧ��� ��� [in]


BOOL HeapDestroy( // �����襭�� ���
  HANDLE hHeap); // handle to heap - ��� ��� [in]


BOOL HeapFree( // �᢮�������� ���
  HANDLE hHeap, // handle to heap - ��� ��� [in]
  DWORD dwFlags, // heap free options - ��樨 �᢮�������� [in]
  LPVOID lpMem); // pointer to memory - 㪠��⥫� �� ��� [in]

LPVOID HeapReAlloc( // �����।������ ���
  HANDLE hHeap, // handle to heap block - ��� ��� [in]
  DWORD dwFlags, // heap reallocation options - ��樨 �����।������ ��� [in]
  LPVOID lpMem, // pointer to memory to reallocate - 㪠��⥫� �� �����।��塞�� ��� [in]
  SIZE_T dwBytes); // number of bytes to reallocate - �᫮ �����।��塞�� ���⮢ ��� [in]

DWORD HeapSize( // ��।������ ࠧ��� ��� [out]
  HANDLE hHeap, // handle to heap - ��� ��� [in]
  DWORD dwFlags, // heap size options - ��樨 ࠧ��� ��� [in]
  LPCVOID lpMem); // pointer to memory - 㪠��⥫� �� ��� [in]

//  �������� ������
// ==================

typedef struct _SYSTEM_INFO {
  DWORD dwOemId;
  struct {
    WORD wProcessorArchitecture; // ���⥪��� ������
    WORD wReserved;
  }
  DWORD dwPageSize; // ࠧ��� ��࠭��� �����
  LPVOID lpMinimumApplicationAddress; // ������ �࠭�� ����㯭��� ���᭮�� ����࠭�⢠
  LPVOID lpMaximumApplicationAddress; // ������ �࠭�� ����㯭��� ���᭮�� ����࠭�⢠
  DWORD dwActiveProcessorMask; // ��᪠ ��⨢���� �����஢
  DWORD dwNumberOfProcessors; // �᫮ �����஢
  DWORD dwProcessorType; // ⨯ ������
  DWORD dwAllocationGranularity; // �࠭��୮��� १�ࢨ஢���� ॣ����� �����
  WORD wProcessorLevel; // �஢��� ������
  WORD wProcessorRevision; // �������⥫쭠� ���ଠ�� � ������
} SYSTEM_INFO, *LPSYSTEM_INFO;

typedef struct _MEMORYSTATUS {
  DWORD dwLength;
  DWORD dwMemoryLoad;
  SIZE_T dwTotalPhys;
  SIZE_T dwAvailPhys;
  SIZE_T dwTotalPageFile;
  SIZE_T dwAvailPageFile;
  SIZE_T dwTotalVirtual;
  SIZE_T dwAvailVirtual;
} MEMORYSTATUS, *LPMEMORYSTATUS;

typedef struct _MEMORYSTATUSEX {
  DWORD dwLength;
  DWORD dwMemoryLoad;
  DWORDLONG ullTotalPhys;
  DWORDLONG ullAvailPhys;
  DWORDLONG ullTotalPageFile;
  DWORDLONG ullAvailPageFile;
  DWORDLONG ullTotalVirtual;
  DWORDLONG ullAvailVirtual;
  DWORDLONG ullAvailExtendedVirtual;
} MEMORYSTATUSEX, *LPMEMORYSTATUSEX;

//  �ਫ������ 6. �㭪樨 � �������� ��� �⮡ࠦ���� 䠩��� � ������
// ===================================================================

HANDLE CreateFileMapping( // �������� ��ꥪ� <�⮡ࠦ���� 䠩�> [out]
  HANDLE hFile, // handle to file - ��� 䠩�� [in]
  LPSECURITY_ATTRIBUTES lpAttributes, // security - ��ਡ��� ������᭮�� [in]
  DWORD flProtect, // protection - ���� [in]
  DWORD dwMaximumSizeHigh, // high-order DWORD of size - ���ᨬ���� ࠧ��� (��.ࠧ�.) [in]
  DWORD dwMaximumSizeLow, // low-order DWORD of size - ���ᨬ���� ࠧ��� (��.ࠧ�.) [in]
  LPCTSTR lpName // object name - ��� ��ꥪ� [in]
);

HANDLE OpenFileMapping( // ����⨥ ������������ ��ꥪ� <�⮡ࠦ���� 䠩�> [out]
  DWORD dwDesiredAccess, // access mode - ०�� ����㯠 [in]
  BOOL bInheritHandle, // inherit flag - 䫠�� ��᫥������� [in]
  LPCTSTR lpName // object name - ��� ��ꥪ� [in]
);

LPVOID MapViewOfFile( // �⮡ࠦ���� ������ 䠩��
  HANDLE hFileMappingObject, // handle to file-mapping object - ��� ��ꥪ� [in]
  DWORD dwDesiredAccess, // access mode - ०�� ����㯠 [in]
  DWORD dwFileOffsetHigh, // high-order DWORD of offset - ᬥ饭�� (��.ࠧ�.) [in]
  DWORD dwFileOffsetLow, // low-order DWORD of offset - ᬥ饭�� (��.ࠧ�.) [in]
  SIZE_T dwNumberOfBytesToMap // number of bytes to map - �᫮ �⮡ࠦ����� ���⮢ [in]
);
LPVOID MapViewOfFileEx( // �⮡ࠦ���� ������ 䠩��
  HANDLE hFileMappingObject, // handle to file-mapping object - ��� ��ꥪ� [in]
  DWORD dwDesiredAccess, // access mode - ०�� ����㯠 [in]
  DWORD dwFileOffsetHigh, // high-order DWORD of offset - ᬥ饭�� (��.ࠧ�.) [in]
  DWORD dwFileOffsetLow, // low-order DWORD of offset - ᬥ饭�� (��.ࠧ�.) [in]
  SIZE_T dwNumberOfBytesToMap, // number of bytes to map - �᫮ �⮡ࠦ����� ���⮢ [in]
  LPVOID lpBaseAddress // starting address - ������ ���� [in]
);

BOOL UnmapViewOfFile( // �⬥�� �⮡ࠦ���� ������ 䠩��
  LPCVOID lpBaseAddress // starting address - ���⮢� ���� [in]
);

BOOL CloseHandle( // ����⮦���� ���� ��ꥪ�
  HANDLE hObject // Object handle - ��� ��ꥪ� [in]
);

//  �ਫ������ 7. �㭪樨 � �������� ��� ��᫥������� ����ᮢ � ��⮪��
// ========================================================================

HANDLE WINAPI CreateToolhelp32Snapshot( // �������� ��ꥪ� <᭨��� ��⥬�> [out]
  DWORD dwFlags, // - 䫠�� [in]
  DWORD th32ProcessID // - �����䨪��� ����� [in]
);

BOOL WINAPI Process32First( // ����祭�� ���ଠ樨 � ��ࢮ� ����� � ᯨ᪥ ����ᮢ
  HANDLE hSnapshot, // ��� ᭨��� [in]
  LPPROCESSENTRY32 lppe // 㪠��⥫� �� �������� <���ଠ�� � �����> [in/out]
);

BOOL WINAPI Process32Next( // ����祭�� ���ଠ樨 � ᫥���饬 ����� � ᯨ᪥ ����ᮢ
  HANDLE hSnapshot, // ��� ᭨��� [in]
  LPPROCESSENTRY32 lppe // 㪠��⥫� �� �������� <���ଠ�� � �����> [out]
);

BOOL WINAPI Thread32First( // ����祭�� ���ଠ樨 � ��ࢮ� ��⮪� � ᯨ᪥ ��⮪��
  HANDLE hSnapshot, // ��� ᭨��� [in]
  LPTHREADENTRY32 lpte // 㪠��⥫� �� �������� <���ଠ�� � ��⮪�> [in/out]
);

BOOL WINAPI Thread32Next( // ����祭�� ���ଠ樨 � ᫥���饬 ��⮪� � ᯨ᪥ ��⮪��
  HANDLE hSnapshot, // ��� ᭨��� [in]
  LPTHREADENTRY32 lpte // 㪠��⥫� �� �������� <���ଠ�� � ��⮪�> [out]
);

typedef struct tagPROCESSENTRY32 {
  DWORD dwSize;
  - ࠧ��� ��������
  DWORD cntUsage; - ���稪 ��뫮� �� �����
  DWORD th32ProcessId; - �����䨪��� �����
  DWORD th32DefaultHeapId; - �����䨪��� ��� �� 㬮�砭��
  DWORD th32ModuleId; - �����䨪��� �����
  DWORD cntThreads; - �᫮ ��⮪�� �����
  DWORD th32ParentProcessId; - �����䨪��� த�⥫�᪮�� �����
  LONG pcPriClassBase; - ������ ����� �ਮ���
  DWORD dwFlags; - 䫠��
  char szExeFile[MAX_PATH]; - ���� � 䠩��
} PROCESSENTRY32;
typedef PROCESSENTRY32* PPROCESSENTRY32;
typedef PROCESSENTRY32* LPPROCESSENTRY32;

typedef struct tagTHREADENTRY32 {
  DWORD dwSize;
  - ࠧ��� ��������
  DWORD cntUsage; - ���稪 ��뫮� �� ��⮪
  DWORD th32ThreadId; - �����䨪��� ��⮪
  DWORD th32OwnerProcessId; - �����䨪��� ����� -��������
  LONG tpBasePri; - ⥪�騩 �ਮ��� ��⮪�
  LONG tpDeltaPri; - �⭮�⥫�� �ਮ��� ��⮪�
  DWORD dwFlags; - 䫠��
} THREADENTRY32;
typedef THREADENTRY32* PTHREADENTRY32;
typedef THREADENTRY32* LPTHREADENTRY32;

