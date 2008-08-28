// Приложение к лабораторным работам по ОС на C/C++
// Описание необходимых функций и структур данных

//  Приложение 1. Функции и структуры для получения информации о вычислительной системе
// =====================================================================================

VOID GetSystemInfo( //Получение информации о системе
    LPSYSTEM_INFO lpSystemInfo // system information - информация о системе [out]
    );

BOOL GetComputerName( // Определение имени компьютера
    LPTSTR lpBuffer, // computer name - буфер для имени компьютера [in]
    LPDWORD lpnSize // size of name buffer - размер буфера / длина имени [in/out]
    );

BOOL GetComputerNameEx( // Определение имени компьютера
    COMPUTER_NAME_FORMAT NameType, // name type - тип имени [in]
    LPTSTR lpBuffer, // name buffer - буфер для имени компьютера [out]
    LPDWORD lpnSize // size of name buffer- размер буфера / длина имени [in/out]
    );

BOOL GetUserName( // Определение имени пользователя
    LPTSTR lpBuffer, // name buffer - буфер для имени [out]
    LPDWORD nSize // size of name buffer - размер буфера [in/out]
    );

BOOLEAN GetUserNameEx( // Определение имени пользователя
    EXTENDED_NAME_FORMAT NameFormat, // name format - формат имени [in]
    LPTSTR lpNameBuffer, // name buffer - буфер для имени [out]
    PULONG nSize // size of name buffer - размер буфера / длина имени [in/out]
    );

DWORD GetLogicalDrives(VOID); // Определение доступных логических дисков (маска) [out]

DWORD GetLogicalDriveStrings( // Определение доступных логических дисков (строка) [out]
    DWORD nBufferLength, // size of buffer - длина буфера [in]
    LPTSTR lpBuffer // drive strings buffer - буфер для строки [out]
    );

UINT GetDriveType( // Определение тппа устройства [out]
    LPCTSTR lpRootPathName // root directory - имя корневого каталога [in]
    );

BOOL GetDiskFreeSpace( // Определение объема свободного пространства на диске
    LPCTSTR lpRootPathName, // root path - имя корневого каталога [in]
    LPDWORD lpSectorsPerCluster, // sectors per cluster - число секторов в кластере [out]
    LPDWORD lpBytesPerSector, // bytes per sector - число байтов в секторе [out]
    LPDWORD lpNumberOfFreeClusters, // free clusters - число свободных кластеров [out]
    LPDWORD lpTotalNumberOfClusters // total clusters - общее число кластеров [out]
    );

BOOL GetDiskFreeSpaceEx( // Определение объема свободного пространства на диске
    LPCTSTR lpDirectoryName, // directory name- имя каталога [in]
    PULARGE_INTEGER lpFreeBytesAvailable, // bytes available to caller - доступных байтов [out]
    PULARGE_INTEGER lpTotalNumberOfBytes, // bytes on disk - байтов на диске [out]
    PULARGE_INTEGER lpTotalNumberOfFreeBytes // free bytes on disk - свободных байтов [out]
    );

BOOL GetVolumeInformation( // Получение информации о томе
    LPCTSTR lpRootPathName, // root directory -имя корневого каталога [in]
    LPTSTR lpVolumeNameBuffer, // volume name buffer - буфер для имени тома [out]
    DWORD nVolumeNameSize, // length of name buffer - длина буфера [in]
    LPDWORD lpVolumeSerialNumber, // volume serial number - серийный номер тома [out]
    LPDWORD lpMaximumComponentLength, // maximum file name length - макс.длина имени тома [out]
    LPDWORD lpFileSystemFlags, // file system options - флаги файловой системы (ФС) [out]
    LPTSTR lpFileSystemNameBuffer, // file system name buffer - буфер для имени ФС [out]
    DWORD nFileSystemNameSize // length of file system name buffer - длина буфера для имени ФС [in]
    );

//  Структуры данных
// ==================

typedef struct _SYSTEM_INFO {
  DWORD dwOemId;
  struct {
    WORD wProcessorArchitecture; // архитектура процессора
    WORD wReserved;
  }
  DWORD dwPageSize; // размер страницы памяти
  LPVOID lpMinimumApplicationAddress; // нижняя граница доступного адресного пространства
  LPVOID lpMaximumApplicationAddress; // верхняя граница доступного адресного пространства
  DWORD dwActiveProcessorMask; // маска активности процессоров
  DWORD dwNumberOfProcessors; // число процессоров
  DWORD dwProcessorType; // тип процессора
  DWORD dwAllocationGranularity; // гранулярность резервирования регионов памяти
  WORD wProcessorLevel; // уровень процессора
  WORD wProcessorRevision; // дополнительная информация о процессоре
}SYSTEM_INFO, +LPSYSTEM_INFO;

//  Приложение 2. Функции и структуры для операций над деревом каталогов
// ======================================================================

DWORD GetCurrentDirectory( // Определение текущего каталога [out]
    DWORD nBufferLength, // size of directory buffer - размер буфера для каталога [in]
    LPTSTR lpBuffer // directory buffer - буфер для каталога [out]
    );

BOOL SetCurrentDirectory( // Установка текущего каталога
    LPCTSTR lpPathName // new directory name - новое имя каталога [in]
    );

UINT GetSystemDirectory( // Определение системного каталога [out]
    LPTSTR lpBuffer, // buffer for system directory - буфер для системного каталога [out]
    UINT uSize // size of directory buffer- размер буфера [in]
    );

UINT GetWindowsDirectory( // Определение каталога Windows [out]
    LPTSTR lpBuffer, // buffer for Windows directory - буфер для каталога Windows [out]
    UINT uSize // size of directory buffer - размер буфера [in]
    );

DWORD GetFullPathName( // Определение полного пути к файлу [out]
    LPCTSTR lpFileName, // file name - имя файла [in]
    DWORD nBufferLength, // size of path buffer - размер буфера для пути [in]
    LPTSTR lpBuffer, // path buffer - буфер для пути [out]
    LPTSTR *lpFilePart // address of file name in path - адрес имени файла в пути [out]
    );

DWORD GetLongPathName( // Преобразование пути в длинную форму [out]
    LPCTSTR lpszShortPath, // file name - исходный (короткий) путь [in]
    LPTSTR lpszLongPath, // path buffer - буфер длинного пути [out]
    DWORD cchBuffer // size of path buffer - размер буфера длинного пути [in]
    );

DWORD GetShortPathName( Преобразование пути в короткую форму [out]
    LPCTSTR lpszLongPath, // null-terminated path string - исходный (длинный) путь [in]
    LPTSTR lpszShortPath, // short form buffer - [in/out] - буфер для короткого пути [out]
    DWORD cchBuffer // size of short form buffer - размер буфера для короткого пути [in]
);

DWORD SearchPath( // Поиск пути [out]
    LPCTSTR lpPath, // search path - исходный путь для поиска [in]
    LPCTSTR lpFileName, // file name - имя файла [in]
    LPCTSTR lpExtension, // file extension - расширение имени файла [in]
    DWORD nBufferLength, // size of buffer - размер буфера для искомого пути [in]
    LPTSTR lpBuffer, // found file name buffer - буфер для искомого пути [out]
    LPTSTR *lpFilePart // file component - адрес начала имени файла [out]
    );

//  Приложение 3. Функции и структуры для операций над каталогами и файлами
// =========================================================================

BOOL CreateDirectory( //Создание каталога
    LPCTSTR lpPathName, // directory name - имя создаваемого каталога [in]
    LPSECURITY_ATTRIBUTES lpSecurityAttributes // SD - дескриптор безопасности [in/out]
    );

BOOL CreateDirectoryEx( // Создание каталога
    LPCTSTR lpTemplateDirectory, // template directory - образец каталога [in]
    LPCTSTR lpNewDirectory, // directory name - имя создаваемого каталога [in]
    LPSECURITY_ATTRIBUTES lpSecurityAttributes // SD - дескриптор безопасности [in]
    );

BOOL RemoveDirectory( // Удаление каталога
    LPCTSTR lpPathName // directory name - путь [in]
    );

BOOL CopyFile( // Копирование файла
    LPCTSTR lpExistingFileName, // name of an existing file - имя существующего файла [in]
    LPCTSTR lpNewFileName, // name of new file - имя нового файла [in]
    BOOL bFailIfExists // operation if file exists - учет коллизий с новым именем [in]
    );
BOOL CopyFileEx( // Копирование файла
    LPCTSTR lpExistingFileName, // name of existing file - имя существующего файла [in]
    LPCTSTR lpNewFileName, // name of new file - имя нового файла [in]
    LPPROGRESS_ROUTINE lpProgressRoutine, // callback function - обработчик [in]
    LPVOID lpData, // callback parameter - данные для обработчика [in]
    LPBOOL pbCancel, // cancel status - отказ от обработки [in]
    DWORD dwCopyFlags // copy options - флаги копирования [in]
    );

BOOL MoveFile( // Перемещение файла
    LPCTSTR lpExistingFileName, // file name - имя существующего файла [in]
    LPCTSTR lpNewFileName // new file name - имя нового файла [in]
    );
BOOL MoveFileEx( // Перемещение файла
    LPCTSTR lpExistingFileName, // file name - имя существующего файла [in]
    LPCTSTR lpNewFileName, // new file name - имя нового файла [in]
    DWORD dwFlags // move options - флаги перемещения [in]


    BOOL ReplaceFile( // Замещение файла
        LPCTSTR lpReplacedFileName, // file name - имя замещаемого файла [in]
        LPCTSTR lpReplacementFileName, // replacement file - имя замещающего файла [in]
        LPCTSTR lpBackupFileName, // optional backup file - имя сохраняемого файла [in]
        DWORD dwReplaceFlags, // replace options - флаги замещения [in]
        LPVOID lpExclude, // reserved - резерв [in]
        LPVOID lpReserved // reserved - резерв [in]
    );

BOOL DeleteFile( // Удаление файла
    LPCTSTR lpFileName // file name - имя файла [in]
    );

//  Приложение 4. Функции и структуры для операций над характеристиками файлов
// ============================================================================

HANDLE CreateFile( // Создание файла [out]
    LPCTSTR lpFileName, // file name - имя файла [in]
    DWORD dwDesiredAccess, // access mode - права доступа [in]
    DWORD dwShareMode, // share mode - режим разделения файла [in]
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, // SD - атрибуты ьезопасности [in]
    DWORD dwCreationDisposition, // how to create - коллизии с существующим файлом [in]
    DWORD dwFlagsAndAttributes, // file attributes - флаги и атрибуты файла [in]
    HANDLE hTemplateFile); // handle to template file - хэндл файла-образца [in]


BOOL GetFileInformationByHandle( // Получение информации о файле по хэндлу
    HANDLE hFile, // handle to file - хэндл файла [in]
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation); // buffer - информация о файле [out]


DWORD GetFileType( // Определение типа файла [out]
    HANDLE hFile); // handle to file - хэндл файла [in]


DWORD GetFileSize( // Определение размера файла [out]
    HANDLE hFile, // handle to file - хэндл файла [in]
    LPDWORD lpFileSizeHigh); // high-order word of file size - старшая часть слова размера файла [out]

BOOL GetFileSizeEx( // Определение размера файла
    HANDLE hFile, // handle to file - хэндл файла [in]
    PLARGE_INTEGER lpFileSize); // file size - размер файла [out]

DWORD GetFileAttributes( // Получение атрибутов файла [out]
    LPCTSTR lpFileName); // name of file or directory - имя файла или каталога [in]

BOOL GetFileAttributesEx( // Получение атрибутов файла
    LPCTSTR lpFileName, // file or directory name - имя файла или каталога [in]
    GET_FILEEX_INFO_LEVELS fInfoLevelId, // attribute - объем информации [in]
    LPVOID lpFileInformation); // attribute information - информация об атрибутах [out]

BOOL SetFileAttributes( // Установка атрибутов файла
    LPCTSTR lpFileName, // file name - имя файла [in]
    DWORD dwFileAttributes); // attributes - атрибуты файла [in]


void GetSystemTime( // Получение отметок времени в формате SystemTime
    LPSYSTEMTIME lpSystemTime); // системное время [out]


BOOL GetFileTime( // Получение отметок времени в формате FileTime
    HANDLE hFile, // хэндл файла [in]
    LPFILETIME lpCreationTime, // время создания [out]
    LPFILETIME lpLastAccessTime, // время последнего доступа [out]
    LPFILETIME lpLastWriteTime); // время последней записи [out]

BOOL SetFileTime( // Установка отметок времени в формате FileTime
    HANDLE hFile, // хэндл файла [in]
    const FILETIME *lpCreationTime, // время создания [in]
    const FILETIME *lpLastAccessTime, // время последнего доступа [in]
    const FILETIME *lpLastWriteTime); // время последней записи [in]


BOOL SystemTimeToFileTime( // Преобразование форматов времени
    const SYSTEMTIME *lpSystemTime, // Отметка времени в формате SystemTime [in]
    LPFILETIME lpFileTime); // Отметка времени в формате FileTime [out]
BOOL FileTimeToSystemTime( // Преобразование форматов времени
    const FILETIME *lpFileTime, // Отметка времени в формате FileTime [in]
    LPSYSTEMTIME lpSystemTime); // Отметка времени в формате SystemTime [out]


BOOL FileTimeToDosDateTime( // Преобразование форматов времени
    CONST FILETIME *lpFileTime, // file time - отметка времени в формате FileTime [in]
    LPWORD lpFatDate, // MS-DOS date - отметка времени в формате FatDate [out]
    LPWORD lpFatTime); // MS-DOS time - отметка времени в формате FatTime [out]


BOOL DosDateTimeToFileTime( // Преобразование форматов времени
    WORD wFatDate, // 16-bit MS-DOS date - отметка времени в формате FatDate [in]
    WORD wFatTime, // 16-bit MS-DOS time - отметка времени в формате FatTime [in]
    LPFILETIME lpFileTime); // file time - отметка времени в формате FileTime [out]


LONG CompareFileTime( // Cравнение 2-х отметок времени в формате FileTime [out]
    const FILETIME *lpFileTime1, // 1-я отметка времени [in]
    const FILETIME *lpFileTime2); // 2-я отметка времени [in]

//  Структуры данных
// ==================

typedef struct _BY_HANDLE_FILE_INFORMATION { // Получение информации о файле по его хэндлу
  DWORD dwFileAttributes; // атрибуты файла
  FILETIME ftCreationTime; // время создания
  FILETIME ftLastAccessTime; // время последнего доступа
  FILETIME ftLastWriteTime; // время последней записи (модификации)
  DWORD dwVolumeSerialNumber; // серийный номер тома
  DWORD nFileSizeHigh; // размер файла (ст.р.)
  DWORD nFileSizeLow; // размер файла (мл.р.)
  DWORD nNumberOfLinks; // число ссылок
  DWORD nFileIndexHigh; // индекс файла (ст.р.)
  DWORD nFileIndexLow; // индекс файла (мл.р.)
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

//  Приложение 5. Функции и структуры для операций над виртуальной памятью
// ========================================================================

VOID GlobalMemoryStatus( // Определение состояния глобальной памяти
    LPMEMORYSTATUS lpBuffer); // memory status structure - буфер состояния глобальной памяти [out]

BOOL GlobalMemoryStatusEx( // Определение состояния глобальной памяти
    LPMEMORYSTATUSEX lpBuffer); // memory status structure- буфер состояния глобальной памяти [in/out]


LPVOID VirtualAlloc( // Выделение виртуальной памяти
    LPVOID lpAddress, // region to reserve or commit - адрес региона [in]
    SIZE_T dwSize, // size of region - размер региона [in]
    DWORD flAllocationType, // type of allocation - тип выделения [in]
    DWORD flProtect); // type of access protection - тип защиты доступа [in]
LPVOID VirtualAllocEx( // Выделение виртуальной памяти
    HANDLE hProcess, // process to allocate memory - хэндл процесса [in]
    LPVOID lpAddress, // desired starting address - желаемый стартовый адрес [in]
    SIZE_T dwSize, // size of region to allocate - размер региона [in]
    DWORD flAllocationType, // type of allocation - тип выделения [in]
    DWORD flProtect); // type of access protection - тип защиты доступа [in]

BOOL VirtualFree( // Освобождение виртуальной памяти
    LPVOID lpAddress, // address of region - адрес региона [in]
    SIZE_T dwSize, // size of region - размер региона [in]
    DWORD dwFreeType); // operation type - тип операции [in]
BOOL VirtualFreeEx( // Освобождение виртуальной памяти
    HANDLE hProcess, // handle to process - хэндл процесса [in]
    LPVOID lpAddress, // starting address of memory region - стартовый адрес региона [in]
    SIZE_T dwSize, // size of memory region - размер региона [in]
    DWORD dwFreeType); // operation type - тип операции [in]

DWORD VirtualQuery( // Запрос виртуальной памяти [out]
    LPCVOID lpAddress, // address of region - адрес региона [in]
    PMEMORY_BASIC_INFORMATION lpBuffer, // information buffer - буфер для информации [out]
    SIZE_T dwLength); // size of buffer - размер буфера [in]

DWORD VirtualQueryEx( // Запрос виртуальной памяти [out]
    HANDLE hProcess, // handle to process - хэндл процесса [in]
    LPCVOID lpAddress, // address of region - адрес региона [in]
    PMEMORY_BASIC_INFORMATION lpBuffer, // information buffer - буфер для информации [out]
    SIZE_T dwLength); // size of buffer - размер буфера [in]


// Примечание: Heap - Динамическая область памяти (ДОП)

HANDLE GetProcessHeap(VOID); // Получение хэндла ДОП процесса [out]

DWORD GetProcessHeaps( // Получение хэндлов ДОП процесса [out]
    DWORD NumberOfHeaps, // maximum number of heap handles - максимальное число хэндлов [in]
    PHANDLE ProcessHeaps); // buffer for heap handles - буфер для хэндлов ДОП процесса [out]


LPVOID HeapAlloc( // Выделение ДОП
    HANDLE hHeap, // handle to private heap block - хэндл ДОП [in]
    DWORD dwFlags, // heap allocation control - управление выделением ДОП [in]
    SIZE_T dwBytes); // number of bytes to allocate - число запрашиваемых байтов [in]


HANDLE HeapCreate( // Создание ДОП [out]
    DWORD flOptions, // heap allocation attributes - атрибуты ДОП [in]
    SIZE_T dwInitialSize, // initial heap size - начальный размер ДОП [in]
    SIZE_T dwMaximumSize); // maximum heap size - максимальный размер ДОП [in]


BOOL HeapDestroy( // Разрушение ДОП
    HANDLE hHeap); // handle to heap - хэндл ДОП [in]


BOOL HeapFree( // Освобождение ДОП
    HANDLE hHeap, // handle to heap - хэндл ДОП [in]
    DWORD dwFlags, // heap free options - опции освобождение [in]
    LPVOID lpMem); // pointer to memory - указатель на ДОП [in]

LPVOID HeapReAlloc( // Перераспределение ДОП
    HANDLE hHeap, // handle to heap block - хэндл ДОП [in]
    DWORD dwFlags, // heap reallocation options - опции перераспределения ДОП [in]
    LPVOID lpMem, // pointer to memory to reallocate - указатель на перераспределяемую ДОП [in]
    SIZE_T dwBytes); // number of bytes to reallocate - число перераспределяемых байтов ДОП [in]

DWORD HeapSize( // Определение размера ДОП [out]
    HANDLE hHeap, // handle to heap - хэндл ДОП [in]
    DWORD dwFlags, // heap size options - опции размера ДОП [in]
    LPCVOID lpMem); // pointer to memory - указатель на ДОП [in]

//  Структуры данных
// ==================

typedef struct _SYSTEM_INFO {
  DWORD dwOemId;
  struct {
    WORD wProcessorArchitecture; // архитектура процессора
    WORD wReserved;
  }
  DWORD dwPageSize; // размер страницы памяти
  LPVOID lpMinimumApplicationAddress; // нижняя граница доступного адресного пространства
  LPVOID lpMaximumApplicationAddress; // верхняя граница доступного адресного пространства
  DWORD dwActiveProcessorMask; // маска активности процессоров
  DWORD dwNumberOfProcessors; // число процессоров
  DWORD dwProcessorType; // тип процессора
  DWORD dwAllocationGranularity; // гранулярность резервирования регионов памяти
  WORD wProcessorLevel; // уровень процессора
  WORD wProcessorRevision; // дополнительная информация о процессоре
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

//  Приложение 6. Функции и структуры для отображения файлов в память
// ===================================================================

HANDLE CreateFileMapping( // Создание объекта <отображаемый файл> [out]
    HANDLE hFile, // handle to file - хэндл файла [in]
    LPSECURITY_ATTRIBUTES lpAttributes, // security - атрибуты безопасности [in]
    DWORD flProtect, // protection - защита [in]
    DWORD dwMaximumSizeHigh, // high-order DWORD of size - максимальный размер (ст.разр.) [in]
    DWORD dwMaximumSizeLow, // low-order DWORD of size - максимальный размер (мл.разр.) [in]
    LPCTSTR lpName // object name - имя объекта [in]
    );

HANDLE OpenFileMapping( // Открытие именованного объекта <отображаемый файл> [out]
    DWORD dwDesiredAccess, // access mode - режим доступа [in]
    BOOL bInheritHandle, // inherit flag - флаги наследования [in]
    LPCTSTR lpName // object name - имя объекта [in]
    );

LPVOID MapViewOfFile( // Отображение данных файла
    HANDLE hFileMappingObject, // handle to file-mapping object - хэндл объекта [in]
    DWORD dwDesiredAccess, // access mode - режим доступа [in]
    DWORD dwFileOffsetHigh, // high-order DWORD of offset - смещение (ст.разр.) [in]
    DWORD dwFileOffsetLow, // low-order DWORD of offset - смещение (мл.разр.) [in]
    SIZE_T dwNumberOfBytesToMap // number of bytes to map - число отображаемых байтов [in]
    );
LPVOID MapViewOfFileEx( // Отображение данных файла
    HANDLE hFileMappingObject, // handle to file-mapping object - хэндл объекта [in]
    DWORD dwDesiredAccess, // access mode - режим доступа [in]
    DWORD dwFileOffsetHigh, // high-order DWORD of offset - смещение (ст.разр.) [in]
    DWORD dwFileOffsetLow, // low-order DWORD of offset - смещение (мл.разр.) [in]
    SIZE_T dwNumberOfBytesToMap, // number of bytes to map - число отображаемых байтов [in]
    LPVOID lpBaseAddress // starting address - базовый адрес [in]
    );

BOOL UnmapViewOfFile( // Отмена отображения данных файла
    LPCVOID lpBaseAddress // starting address - стартовый адрес [in]
    );

BOOL CloseHandle( // Уничтожение хэндла объекта
    HANDLE hObject // Object handle - хэндл объекта [in]
    );

//  Приложение 7. Функции и структуры для исследования процессов и потоков
// ========================================================================

HANDLE WINAPI CreateToolhelp32Snapshot( // Создание объекта <снимок системы> [out]
    DWORD dwFlags, // - флаги [in]
    DWORD th32ProcessID // - идентификатор процесса [in]
);

BOOL WINAPI Process32First( // Получение информации о первом процессе в списке процессов
    HANDLE hSnapshot, // хэндл снимка [in]
    LPPROCESSENTRY32 lppe // указатель на структуру <информация о процессе> [in/out]
);

BOOL WINAPI Process32Next( // Получение информации о следующем процессе в списке процессов
    HANDLE hSnapshot, // хэндл снимка [in]
    LPPROCESSENTRY32 lppe // указатель на структуру <информация о процессе> [out]
);

BOOL WINAPI Thread32First( // Получение информации о первом потоке в списке потоков
    HANDLE hSnapshot, // хэндл снимка [in]
    LPTHREADENTRY32 lpte // указатель на структуру <информация о потоке> [in/out]
);

BOOL WINAPI Thread32Next( // Получение информации о следующем потоке в списке потоков
    HANDLE hSnapshot, // хэндл снимка [in]
    LPTHREADENTRY32 lpte // указатель на структуру <информация о потоке> [out]
);

typedef struct tagPROCESSENTRY32 {
  DWORD dwSize;
  - размер структуры
  DWORD cntUsage; - счетчик ссылок на процесс
  DWORD th32ProcessId; - идентификатор процесса
  DWORD th32DefaultHeapId; - идентификатор ДОП по умолчанию
  DWORD th32ModuleId; - идентификатор модуля
  DWORD cntThreads; - число потоков процесса
  DWORD th32ParentProcessId; - идентификатор родительского процесса
  LONG pcPriClassBase; - базовый класс приоритета
  DWORD dwFlags; - флаги
  char szExeFile[MAX_PATH]; - путь к файлу
}PROCESSENTRY32;
typedef PROCESSENTRY32 *PPROCESSENTRY32;
typedef PROCESSENTRY32 *LPPROCESSENTRY32;

typedef struct tagTHREADENTRY32 {
  DWORD dwSize;
  - размер структуры
  DWORD cntUsage; - счетчик ссылок на поток
  DWORD th32ThreadId; - идентификатор поток
  DWORD th32OwnerProcessId; - идентификатор процесса-владельца
  LONG tpBasePri; - текущий приоритет потока
  LONG tpDeltaPri; - относительный приоритет потока
  DWORD dwFlags; - флаги
}THREADENTRY32;
typedef THREADENTRY32 *PTHREADENTRY32;
typedef THREADENTRY32 *LPTHREADENTRY32;

