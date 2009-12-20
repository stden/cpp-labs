////////////////////////////////////////////////////////////////////////////////
//
//  ****************************************************************************
//  * Project   : Process Memory Map Sample
//  * Unit Name : uProcessMMapDlg
//  * Purpose   : Демонстрационный пример получения
//  *           : карты памяти выбранного процесса
//  * Author    : Александр (Rouse_) Багель
//  * Copyright : © Fangorn Wizards Lab 1998 - 2009.
//  * Version   : 1.02
//  * Home Page : http://rouse.drkb.ru
//  ****************************************************************************
//

unit uProcessMMapDlg;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ComCtrls;

type
  TAdvancedInfo = record
    Description: string;
    Addr: DWORD;
  end;
  TAdvancedInfos = array of TAdvancedInfo;

  TProcDumpDlg = class(TForm)
    lblHint: TLabel;
    cbProcess: TComboBox;
    lvMemoryMap: TListView;
    pnProcess: TPanel;
    cbShowFreeMem: TCheckBox;
    cbShowReserve: TCheckBox;
    btnRefresh: TButton;
    procedure FormCreate(Sender: TObject);
    procedure cbProcessChange(Sender: TObject);
    procedure btnRefreshClick(Sender: TObject);
    procedure lvMemoryMapCustomDrawItem(Sender: TCustomListView;
      Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
  private
    CurrentPid: DWORD;
    GrayedRow: Boolean;
    AdvDataLen: Integer;
    AdvData: TAdvancedInfos;
    procedure AddNewData(const Description: string; Addr: DWORD); overload;
    procedure AddNewData(const Description: string; Addr: Pointer); overload;
    procedure FillProcessList;
    procedure FillProcessMemoryMap(const PID: DWORD);
    procedure FillPEBInfo(const hProcess: THandle);
    procedure FillThreadsInfo(const hProcess: THandle);
    procedure FillHeapsInfo;
  end;

var
  ProcDumpDlg: TProcDumpDlg;

implementation

uses
  TlHelp32;

{$R *.dfm}

// Все необходимые обьявления функций, типов и структур, в этом инклуде
// =============================================================================
{$I 'native.inc'}

//  Функция включает отладочные привилегии для процесса,
//  в противном случае такие процессы как csrss.exe,
//  svchost.exe и т.п. датут отлуп
// =============================================================================
function SetDebugPriv: Boolean;
var
  Token: THandle;
  tkp: TTokenPrivileges;
begin
  Result := false;
  if OpenProcessToken(GetCurrentProcess,
    TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY, Token) then
  begin
    if LookupPrivilegeValue(nil, PChar('SeDebugPrivilege'),
      tkp.Privileges[0].Luid) then
    begin
      tkp.PrivilegeCount := 1;
      tkp.Privileges[0].Attributes := SE_PRIVILEGE_ENABLED;
      Result := AdjustTokenPrivileges(Token, False,
        tkp, 0, PTokenPrivileges(nil)^, PDWord(nil)^);
    end;
  end;
end;

//  Функция приводит пути с использованием символьных ссылок к нормальному виду
// =============================================================================
function NormalizePath(const Value: string): string;
const
  OBJ_CASE_INSENSITIVE         = $00000040;
  STATUS_SUCCESS               = 0;
  FILE_SYNCHRONOUS_IO_NONALERT = $00000020;
  FILE_READ_DATA = 1;
  ObjectNameInformation = 1;
  DriveNameSize = 4;
  VolumeCount = 26;
  DriveTotalSize = DriveNameSize * VolumeCount;
var
  US: UNICODE_STRING;
  OA: OBJECT_ATTRIBUTES;
  IO: IO_STATUS_BLOCK;
  hFile: THandle;
  NTSTAT, dwReturn: DWORD;
  ObjectNameInfo: TOBJECT_NAME_INFORMATION;
  Buff, Volume: String;
  I, Count, dwQueryLength: Integer;
  lpQuery: array [0..MAX_PATH - 1] of Char;
begin
  Result := Value;
  // Подготавливаем параметры для вызова ZwOpenFile
  RtlInitUnicodeString(@US, StringToOleStr(Value));
  // Аналог макроса InitializeObjectAttributes
  FillChar(OA, SizeOf(OBJECT_ATTRIBUTES), #0);
  OA.Length := SizeOf(OBJECT_ATTRIBUTES);
  OA.ObjectName := @US;
  OA.Attributes := OBJ_CASE_INSENSITIVE;
  // Функция ZwOpenFile спокойно открывает файлы, путь к которым представлен
  // с использованием символьных ссылок, например:
  // \SystemRoot\System32\ntdll.dll
  // \??\C:\Windows\System32\ntdll.dll
  // \Device\HarddiskVolume1\WINDOWS\system32\ntdll.dll
  // Поэтому будем использовать ее для получения хэндла
  NTSTAT := ZwOpenFile(@hFile, FILE_READ_DATA or SYNCHRONIZE, @OA, @IO,
    FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
    FILE_SYNCHRONOUS_IO_NONALERT);
  if NTSTAT = STATUS_SUCCESS then
  try
    // Файл открыт, теперь смотрим его формализованный путь
    NTSTAT := NtQueryObject(hFile, ObjectNameInformation,
      @ObjectNameInfo, MAX_PATH * 2, @dwReturn);
    if NTSTAT = STATUS_SUCCESS then
    begin
      SetLength(Result, MAX_PATH);
      WideCharToMultiByte(CP_ACP, 0,
        @ObjectNameInfo.Name.Buffer[ObjectNameInfo.Name.MaximumLength -
        ObjectNameInfo.Name.Length],
        ObjectNameInfo.Name.Length, @Result[1],
        MAX_PATH, nil, nil);
      // Путь на открытый через ZwOpenFile файл
      // возвращается в виде \Device\HarddiskVolumeХ\бла-бла
      // Осталось только его сопоставить с реальным диском
      SetLength(Buff, DriveTotalSize);
      Count := GetLogicalDriveStrings(DriveTotalSize, @Buff[1]) div DriveNameSize;
      for I := 0 to Count - 1 do
      begin
        Volume := PChar(@Buff[(I * DriveNameSize) + 1]);
        Volume[3] := #0;
        // Преобразуем имя каждого диска в символьную ссылку и
        // сравниваем с формализированным путем
        QueryDosDevice(PChar(Volume), @lpQuery[0], MAX_PATH);
        dwQueryLength := Length(string(lpQuery));
        if Copy(Result, 1, dwQueryLength) = string(lpQuery) then
        begin
          Volume[3] := '\';
          if lpQuery[dwQueryLength - 1] <> '\' then
            Inc(dwQueryLength);
          Delete(Result, 1, dwQueryLength);
          Result := Volume + Result;
          Break;
        end;
      end;
    end;
  finally
    ZwClose(hFile);
  end;
end;

//  Функция смотрит флаги доступа к странице
//  и возращает их строковое представление
// =============================================================================
function ExtractInitialAccessString(const Value: DWORD): string;
begin
  Result := '';
  if (Value and PAGE_EXECUTE) = PAGE_EXECUTE then Result := 'E';
  if (Value and PAGE_EXECUTE_READ) = PAGE_EXECUTE_READ then Result := 'RE';
  if (Value and PAGE_EXECUTE_READWRITE) = PAGE_EXECUTE_READWRITE then
     Result := 'RWE';
  if (Value and PAGE_EXECUTE_WRITECOPY) = PAGE_EXECUTE_WRITECOPY then
    Result := 'RWE';
  if (Value and PAGE_NOACCESS) = PAGE_NOACCESS then Result := 'No access';
  if (Value and PAGE_READONLY) = PAGE_READONLY then Result := 'R';
  if (Value and PAGE_READWRITE) = PAGE_READWRITE then Result := 'RW';
  if (Value and PAGE_WRITECOPY) = PAGE_WRITECOPY then Result := 'W';
  if Result = '' then
    Result := 'Unknown: 0x' + IntToHex(Value, 8);
end;

//  Функция смотрит расширенные флаги доступа к странице
//  и возращает их строковое представление
// =============================================================================
function ExtractAccessString(const Value: DWORD): string;
const
  PAGE_WRITECOMBINE = $400;
begin
  Result := ExtractInitialAccessString(Value);
  if (Value and PAGE_GUARD) = PAGE_GUARD then
    Result := Result + ', Guarded';
  if (Value and PAGE_NOCACHE) = PAGE_NOCACHE then
    Result := Result + ', No cache';
  if (Value and PAGE_WRITECOMBINE) = PAGE_WRITECOMBINE then
    Result := Result + ', Write Combine';
end;

//  Процедура добавляет в переданный TListItem колонки с информацией
//  о состоянии страницы и параметрми доступа к странице
// =============================================================================
procedure DisplayStateAndProtect(const AItem: TListItem;
  const lpBuffer: TMemoryBasicInformation);
begin
  with AItem do
  begin
    case lpBuffer.State of
      MEM_FREE: SubItems.Add('FREE');
      MEM_RESERVE: SubItems.Add('RESERVE');
      MEM_COMMIT:
      case lpBuffer.Type_9 of
        MEM_IMAGE: SubItems.Add('Image');
        MEM_MAPPED: SubItems.Add('Map');
        MEM_PRIVATE: SubItems.Add('Private');
      end;
    end;
    SubItems.Add(ExtractAccessString(lpBuffer.Protect));
    SubItems.Add(ExtractInitialAccessString(lpBuffer.AllocationProtect));
  end;
end;

//  Функция перечисляет директории отображенного файла и
//  возращает список директорий, расположенных по адресу переданной секции 
// =============================================================================
function GetContainsDirectory(const Code, Data: Boolean;
  const ImageInfo: LOADED_IMAGE; const SectionAddr, SectionSize: DWORD): string;
const
  DirectoryStr: array [0..14] of String =
    ('export', 'import', 'resource', 'exception',
    'security', 'basereloc', 'debug', 'copyright',
    'globalptr', 'tls', 'load_config', 'bound_import',
    'iat', 'delay_import', 'com');
var
  dwDirSize: DWORD;
  ish: PImageSectionHeader;
  I: Integer;
  Done: Boolean;
begin
  if Code then
    Result := 'code'
  else
    Result := '';
  if Data then
    if Result = '' then
      Result := 'data'
    else
      Result := Result + ', data';
  for I := 0 to 14 do
  begin
    // Получаем адрес директории
    if (ImageDirectoryEntryToDataEx(ImageInfo.MappedAddress,
      False, I, dwDirSize, ish) <> nil) and (ish <> nil) then
    begin
      // Смотрим, совпадает ли он с адресом страницы
      // Единственный момент с директорией TLS,
      // она постоянно сьезжает на одну страницу,
      // тут надо посмотреть у Мэта Питрека что за...
      if I = IMAGE_DIRECTORY_ENTRY_TLS then
        Done := ish^.VirtualAddress = SectionAddr + SectionSize
      else
        Done := ish^.VirtualAddress = SectionAddr;
      if Done then
      begin
        if Result = '' then
          Result := DirectoryStr[I]
        else
          Result := Result + ', ' + DirectoryStr[I];
      end;
    end;
  end;
end;

//  Функция проверяет характеристики секции и возвращает флаг,
//  содержит ли секция исполяемый код
// =============================================================================
function IsExecute(const Value: DWORD): Boolean;
const
  IMAGE_SCN_CNT_CODE = $00000020;
  IMAGE_SCN_MEM_EXECUTE = $20000000;
begin
  Result := False;
  if (Value and IMAGE_SCN_CNT_CODE) =
    IMAGE_SCN_CNT_CODE then Result := True;
  if (Value and IMAGE_SCN_MEM_EXECUTE) =
    IMAGE_SCN_MEM_EXECUTE then Result := True;
end;

//  Функция проверяет характеристики секции и возвращает флаг,
//  доступна ли секция на запись или
//  содержит ли секция неинициализированные данные
// =============================================================================
function IsWrite(const Value: DWORD): Boolean;
const
  IMAGE_SCN_CNT_UNINITIALIZED_DATA = $00000080;
  IMAGE_SCN_MEM_WRITE = $80000000;
begin
  Result := False;
  if (Value and IMAGE_SCN_CNT_UNINITIALIZED_DATA) =
    IMAGE_SCN_CNT_UNINITIALIZED_DATA then Result := True;
  if (Value and IMAGE_SCN_MEM_WRITE) = IMAGE_SCN_MEM_WRITE then
    Result := True;
end;

//  Функция возвращает размер секции с учетом выравнивания,
//  указанного в PE заголовка.
//  Вообще, правильней еще смотреть флаги IMAGE_SCN_ALIGN_ХХХBYTES у секции,
//  которые выставляют индивидуальное выравнивание, но лениво...
// =============================================================================
function AlignedSectionSize(const ImageInfo: LOADED_IMAGE;
  const Value: DWORD): DWORD;
begin
  if Value = 0 then
  begin
    Result := 0;
    Exit;
  end;
  with ImageInfo.FileHeader^.OptionalHeader do
  begin
    if SectionAlignment mod Value = 0 then
      Result := Value
    else
    begin
      Result := Value div SectionAlignment;
      Inc(Result);
      Result := Result * SectionAlignment;
    end;
  end;
end;

//  Функция отображает секции РЕ файла на страницы памяти
// =============================================================================
function DisplayImageData(const ListView: TListView;
  const hProcess: DWORD;  ImagePath: String;
  lpBuffer: TMemoryBasicInformation; var pSectionAddr: DWORD;
  var GrayedRow: Boolean): Boolean;
var
  ImageInfo: LOADED_IMAGE;
  MovedSectionCount: Integer;
  ImageSectionHeader: PImageSectionHeader;
  dwLength: DWORD;
  AItem: TListItem;
  BaseAddr, SectionEnd: DWORD;

  // Процедура проверяет, расположена ли секция образа в текущей странице,
  // и если да, то помещает данные о секции и сопоставленной с ней страницей
  // в ListView
  procedure MoveSectionsToPage;
  var
    S: string;
  begin
    if ImageSectionHeader^.VirtualAddress < SectionEnd then
    begin
      AItem := ListView.Items.Add;
      AItem.Data := Pointer(GrayedRow);
      with AItem do
      begin
        Caption := IntToHex(DWORD(BaseAddr +
          ImageSectionHeader^.VirtualAddress), 8);
        SubItems.Add(IntToHex(AlignedSectionSize(
          ImageInfo, ImageSectionHeader^.Misc.VirtualSize), 8));
        SubItems.Add(ExtractFileName(ImagePath));
        S := PChar(@ImageSectionHeader^.Name[0]);
        S := Copy(S, 1, IMAGE_SIZEOF_SHORT_NAME);
        SubItems.Add(S);
        SubItems.Add(GetContainsDirectory(
          IsExecute(ImageSectionHeader^.Characteristics),
          IsWrite(ImageSectionHeader^.Characteristics),
          ImageInfo, ImageSectionHeader^.VirtualAddress,
          AlignedSectionSize(ImageInfo, ImageSectionHeader^.Misc.VirtualSize)));
        DisplayStateAndProtect(AItem, lpBuffer);
        SubItems.Add('');
        Inc(ImageSectionHeader);
        Inc(MovedSectionCount);
        // Если еще есть секции, вызываем рекурсивно сами себя
        if DWORD(MovedSectionCount) < ImageInfo.NumberOfSections then
          MoveSectionsToPage;
      end;
    end;
  end;

const
  MM_LOWEST_USER_ADDRESS = $10000;
var
  MappedName: array [0..MAX_PATH - 1] of Char;
begin
  Result := False;
  // Проверка аттрибутов страниц и адресов,
  // в которых не может распологаться образ РЕ файла
  if (lpBuffer.State = MEM_FREE) or (lpBuffer.State = MEM_RESERVE) or
    (DWORD(lpBuffer.BaseAddress) <= MM_LOWEST_USER_ADDRESS) then
    Exit;
  // Запоминаем адрес начальной страницы с которой размещен образ
  BaseAddr := pSectionAddr;
  // Отображаем образ в наш процесс, для получения информации
  if MapAndLoad(PChar(NormalizePath(ImagePath)), nil, @ImageInfo, True, True) then
  try
    // Проверка - является ли образ PE файлом?
    if ImageInfo.FileHeader^.Signature = IMAGE_NT_SIGNATURE then
    begin
      Result := True;
      GrayedRow := not GrayedRow;
      // Если все в порядке, добавляем информацию о найденном РЕ заголовке
      AItem := ListView.Items.Add;
      AItem.Data := Pointer(GrayedRow);
      with AItem do
      begin
        // Адрес секции
        Caption := IntToHex(DWORD(lpBuffer.BaseAddress), 8);
        // Размер РЕ секции равен либо оффсету следующей секции,
        // либо размеру текущей страницы
        if lpBuffer.RegionSize < ImageInfo.Sections^.VirtualAddress then
          SubItems.Add(IntToHex(lpBuffer.RegionSize, 8))
        else
          SubItems.Add(IntToHex(ImageInfo.Sections^.VirtualAddress, 8));
        // Имя образа
        SubItems.Add(ExtractFileName(ImagePath));
        SubItems.Add('');
        SubItems.Add('PE Header');
        // Параметры страницы и доступ
        DisplayStateAndProtect(AItem, lpBuffer);
        // Путь к отмапленному образу
        if GetMappedFileName(hProcess, lpBuffer.BaseAddress,
          @MappedName[0], MAX_PATH) > 0 then
          SubItems.Add(NormalizePath(string(MappedName)))
        else
          SubItems.Add('');
      end;
    end
    else
      Exit;
    // Перечисляем все секции образа и сопоставляем их с страницами памяти 
    ImageSectionHeader := ImageInfo.Sections;
    MovedSectionCount := 0;
    SectionEnd := lpBuffer.RegionSize;
    dwLength := SizeOf(TMemoryBasicInformation);
    // Крутим цикл до тех пор, пока не кончаться секции
    while DWORD(MovedSectionCount) < ImageInfo.NumberOfSections do
    begin
      // Сопоставляем секции
      MoveSectionsToPage;
      // Переключаемся на следующую страницу
      Inc(pSectionAddr, lpBuffer.RegionSize);
      if VirtualQueryEx(hProcess,
        Pointer(pSectionAddr), lpBuffer, dwLength) <> dwLength then
        RaiseLastOSError;
      Inc(SectionEnd, lpBuffer.RegionSize);
    end;
  finally
    UnMapAndLoad(@ImageInfo);
  end;
end;
         
procedure TProcDumpDlg.AddNewData(const Description: string; Addr: DWORD);
begin
  if Addr > 0 then
  begin
    Inc(AdvDataLen);
    SetLength(AdvData, AdvDataLen);
    AdvData[AdvDataLen - 1].Description := Description;
    AdvData[AdvDataLen - 1].Addr := Addr;
  end;
end;

procedure TProcDumpDlg.AddNewData(const Description: string; Addr: Pointer);
begin
  AddNewData(Description, DWORD(Addr));
end;

//  Процедура обновляет список процессов
//  и информацию по текущему открытому процессу
// =============================================================================
procedure TProcDumpDlg.btnRefreshClick(Sender: TObject);
begin
  FillProcessList;
  if CurrentPid > 4 then
    FillProcessMemoryMap(CurrentPid);
end;

//  Пользователь выбрал другой процесс,
//  вызываем функцию FillProcessMemoryMap для построения карты процесса
// =============================================================================
procedure TProcDumpDlg.cbProcessChange(Sender: TObject);
begin
  if cbProcess.ItemIndex >= 0 then
    FillProcessMemoryMap(DWORD(cbProcess.Items.Objects[cbProcess.ItemIndex]));
end;

//  Процедура перечисляет кучи процесса
// =============================================================================
procedure TProcDumpDlg.FillHeapsInfo;
var
  I, A: Integer;
  pDbgBuffer: PRtlDebugInformation;
  pHeapInformation: PRtlHeapInformation;
  pHeapEntry: PRtrHeapEntry;
  dwAddr, dwLastSize: DWORD;
  hit_seg_count: Integer;
begin
  // Т.к. связка Heap32ListFirst, Heap32ListNext, Heap32First, Heap32Next
  // работает достаточно медленно, из-за постоянного вызова
  // RtlQueryProcessDebugInformation на каждой итерации, мы заменим ее вызов
  // аналогичным кодом без ненужного дубляжа
  // Создаем отладочный буффер
  pDbgBuffer := RtlCreateQueryDebugBuffer(0, False);
  if pDbgBuffer <> nil then
  try
    // Запрашиваем информацию по списку куч процесса
    if RtlQueryProcessDebugInformation(CurrentPid,
      RTL_QUERY_PROCESS_HEAP_SUMMARY or RTL_QUERY_PROCESS_HEAP_ENTRIES,
      pDbgBuffer) = STATUS_SUCCESS then
    begin
      // Получаем указатель на кучу по умолчанию
      pHeapInformation := @pDbgBuffer^.Heaps^.Heaps[0];
      // перечисляем все ее блоки...
      for I := 0 to pDbgBuffer^.Heaps^.NumberOfHeaps - 1 do
      begin
        // начиная с самого первого
        pHeapEntry := pHeapInformation^.Entries;
        dwAddr := DWORD(pHeapEntry^.u.s2.FirstBlock) +
          pHeapInformation^.EntryOverhead;
        dwLastSize := 0;
        for A := 0 to pHeapInformation^.NumberOfEntries - 1 do
        begin
          hit_seg_count := 0;
          while (pHeapEntry^.Flags and RTL_HEAP_SEGMENT) = RTL_HEAP_SEGMENT do
          begin
            // Если блок отмечен флагом RTL_HEAP_SEGMENT,
            // то рассчитываем новый адрес
            dwAddr := DWORD(pHeapEntry^.u.s2.FirstBlock) +
              pHeapInformation^.EntryOverhead;
            Inc(pHeapEntry);
            Inc(hit_seg_count);
            // проверка выхода за границы блоков
            if A + hit_seg_count >=
              Integer(pHeapInformation^.NumberOfEntries - 1) then
              Continue;
          end;
          // Если блок не самый первый в сегменте, то текущий адрес блока равен,
          // адресу предыдущего блока + размер предыдущего блока
          if hit_seg_count = 0 then
            Inc(dwAddr, dwLastSize);
          // Добавляем результат к списку
          if I = 0 then
            AddNewData('Heap ID: 0 (default)', dwAddr)
          else
            AddNewData('Heap ID: ' + IntToStr(I), dwAddr);
         // Запоминаем адрес последнего блока
         dwLastSize := pHeapEntry^.Size;
         // Переходим к следующему блоку
         Inc(pHeapEntry);
        end;
        // Переходим к следующей куче
        Inc(pHeapInformation);
      end;
    end;
  finally
    RtlDestroyQueryDebugBuffer(pDbgBuffer);
  end;
end;

//  Процедура получает информацию из PEB процесса
// =============================================================================
procedure TProcDumpDlg.FillPEBInfo(const hProcess: THandle);
var
  pProcBasicInfo: PROCESS_BASIC_INFORMATION;
  ReturnLength: DWORD;
  ProcessParameters: RTL_USER_PROCESS_PARAMETERS;
  pPeb: PEB;
  SBI: SYSTEM_BASIC_INFORMATION;
begin
  if NtQueryInformationProcess(hProcess, 0,
    @pProcBasicInfo, SizeOf(PROCESS_BASIC_INFORMATION),
    @ReturnLength) <> STATUS_SUCCESS then
    RaiseLastOSError;
  AddNewData('Process Entry Block', pProcBasicInfo.PebBaseAddress);

  if not ReadProcessMemory(hProcess, pProcBasicInfo.PebBaseAddress,
    @pPeb, SizeOf(PEB), ReturnLength) then
    RaiseLastOSError;
  AddNewData('Process Parameters', pPeb.ProcessParameters);
  AddNewData('SubSystemData', pPeb.SubSystemData);
  AddNewData('KernelCallbackTable', pPeb.KernelCallbackTable);
  AddNewData('ReadOnlySharedMemoryBase', pPeb.ReadOnlySharedMemoryBase);
  AddNewData('ReadOnlySharedMemoryHeap', pPeb.ReadOnlySharedMemoryHeap);
  AddNewData('ReadOnlyStaticServerData', pPeb.ReadOnlyStaticServerData);
  AddNewData('AnsiCodePageData', pPeb.AnsiCodePageData);
  AddNewData('OemCodePageData', pPeb.OemCodePageData);
  AddNewData('UnicodeCaseTableData', pPeb.UnicodeCaseTableData);
  AddNewData('GdiSharedHandleTable', pPeb.GdiSharedHandleTable);

  if not ReadProcessMemory(hProcess, pPeb.ProcessParameters,
    @ProcessParameters, SizeOf(RTL_USER_PROCESS_PARAMETERS), ReturnLength) then
    RaiseLastOSError;
  AddNewData('Process Environments', ProcessParameters.Environment);
  if NtQuerySystemInformation(0, @SBI, SizeOf(SYSTEM_BASIC_INFORMATION),
    ReturnLength) <> STATUS_SUCCESS then
    RaiseLastOSError;
  AddNewData('KE_USER_SHARED_DATA', SBI.MaximumUserModeAddress and $FFFF0000);
end;

//  Процедура запоняет комбобокс списком активных процессов
// =============================================================================
procedure TProcDumpDlg.FillProcessList;
const
  SystemProcessesAndThreadsInformation = 5;
  STATUS_INFO_LENGTH_MISMATCH = $C0000004;
var
  SystemInformation, Temp: PSYSTEM_PROCESS_INFORMATION;
  ReturnLength: DWORD;
begin
  cbProcess.Items.BeginUpdate;
  try
    cbProcess.Items.Clear;
    ReturnLength := 0;
    // Запрашиваем размер требуемой памяти
    if NtQuerySystemInformation(
      SystemProcessesAndThreadsInformation,
      nil, 0, ReturnLength) <> STATUS_INFO_LENGTH_MISMATCH then Exit;
    if ReturnLength > 0 then
    begin
      // Выделяем память
      GetMem(SystemInformation, ReturnLength);
      try
        // Получаем список процессов
        if NtQuerySystemInformation(SystemProcessesAndThreadsInformation,
          SystemInformation, ReturnLength, ReturnLength) = 0 then
        begin
          // Бежим по списку и заносим каждый в список
          Temp := SystemInformation;
          repeat
            if Temp^.ModuleName = nil then
              cbProcess.Items.AddObject('System Idle Process', nil)
            else
              cbProcess.Items.AddObject(Temp^.ModuleName, Pointer(Temp^.ProcessID));
            Temp := Pointer(DWORD(Temp) + Temp^.NextOffset);
          until Temp^.NextOffset = 0;
        end;
      finally
        FreeMem(SystemInformation);
      end;
    end;
  finally
    cbProcess.Items.EndUpdate;
  end;
end;

//  Процедура перечисляет все страницы памяти процесса
//  и выводит информацию о них в ListView
// =============================================================================
procedure TProcDumpDlg.FillProcessMemoryMap(const PID: DWORD);
const
  KSEG0_BASE = $80000000;
  MM_HIGHEST_USER_ADDRESS = $7FFEFFFF;   
  MM_USER_PROBE_ADDRESS = $7FFF0000;
  MM_SYSTEM_RANGE_START = KSEG0_BASE;
var
  hProcess: THandle;
  pSectionAddr: DWORD;
  lpBuffer: TMemoryBasicInformation;
  dwLength: DWORD;
  OwnerName: array [0..MAX_PATH - 1] of Char;
  AItem: TListItem;
  I: Integer;
  InvalidPage, LastShowImage: Boolean;
  ContainStr: String;
begin
  CurrentPid := PID;
  AdvDataLen := 0;
  SetLength(AdvData, 0);
  lvMemoryMap.Items.BeginUpdate;
  try
    lvMemoryMap.Clear;
    // Открываем процесс на чтение
    hProcess := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ,
      False, PID);
    if hProcess = 0 then
      RaiseLastOSError;
    try
      // Перечисляем все нити процесса,
      // запоминаем адреса их стэка и TLS секций
      FillThreadsInfo(hProcess);
      // Выводим информацию из блока окружения процесса
      FillPEBInfo(hProcess);
      // Перечисляем все кучи процесса
      FillHeapsInfo;
      pSectionAddr := 0;
      dwLength := SizeOf(TMemoryBasicInformation);
      LastShowImage := False;
      GrayedRow := False;
      // Перебираем в цикле все страницы памяти от нулевой,
      // до максимально доступной пользователю 
      while pSectionAddr < MM_USER_PROBE_ADDRESS do
      begin
        // Смотрим параметры страницы
        if VirtualQueryEx(hProcess,
          Pointer(pSectionAddr), lpBuffer, dwLength) <> dwLength then
          RaiseLastOSError;

        // Проверка, нужно ли отображать зарезервированные и пустые страницы?
        InvalidPage := False;
        if not cbShowFreeMem.Checked then
          if lpBuffer.State = MEM_FREE then
            InvalidPage := True;
        if not cbShowReserve.Checked then
          if lpBuffer.State = MEM_RESERVE then
            InvalidPage := True;
        if InvalidPage then
        begin
          // Если не нужно - переходим к следующей странице
          Inc(pSectionAddr, lpBuffer.RegionSize);
          Continue;
        end;

        // Смотрим, принадлежит ли страница какому-либо образу
        if GetModuleFileNameEx(hProcess, THandle(lpBuffer.BaseAddress),
          @OwnerName[0], MAX_PATH) > 0 then
          // на страницу отмаплен РЕ файл,
          // выводим данные по нему в отдельной процедуре
          if DisplayImageData(lvMemoryMap, hProcess, String(OwnerName),
            lpBuffer, pSectionAddr, GrayedRow) then
          begin
            LastShowImage := True;
            Continue;
          end;

        // Небольшая правка флага,
        // для правильного переключения заливки в ListView,
        // разделяющей цветом отдельные модули друг от друга для наглядности 
        if LastShowImage then
        begin
          LastShowImage := False;
          GrayedRow := not GrayedRow;
        end;

        Inc(pSectionAddr, lpBuffer.RegionSize);

        // Добавляем данные по странице в ListView
        AItem := lvMemoryMap.Items.Add;
        AItem.Data := Pointer(GrayedRow);
        with AItem do
        begin
          // Адрес страницы
          Caption := IntToHex(DWORD(lpBuffer.BaseAddress), 8);
          // Разме страницы
          SubItems.Add(IntToHex(lpBuffer.RegionSize, 8));
          // Владелец (заполняется при выводе данных по образу)
          SubItems.Add('');
          //  Секция (заполняется при выводе данных по образу)
          SubItems.Add('');
          // Содержимое страницы проверяется по массиву адресов нитей процесса
          ContainStr := '';
          for I := 0 to AdvDataLen - 1 do
          begin
            // Если адрес стека нити или его TLS секции совпал со страницей,
            // выводим информацию в соответствующую колонку
            if (AdvData[I].Addr >= DWORD(lpBuffer.BaseAddress)) and
             (AdvData[I].Addr < DWORD(lpBuffer.BaseAddress) +
             lpBuffer.RegionSize) then
              ContainStr := AdvData[I].Description;
          end;
          SubItems.Add(ContainStr);
          // Аттрибуты страницы и параметры доступа
          DisplayStateAndProtect(AItem, lpBuffer);
          // Проверка отмапленного образа
          if GetMappedFileName(hProcess, lpBuffer.BaseAddress,
            @OwnerName[0], MAX_PATH) > 0 then
            SubItems.Add(NormalizePath(string(OwnerName)))
          else
            SubItems.Add('');
        end;
      end;
    finally
      CloseHandle(hProcess);
    end;
  finally
    lvMemoryMap.Items.EndUpdate;
  end;
end;

//  Процедура перечисляет все нити процесса и заполняет переданный масив
//  информацией о адресах стека каждой нити и адресах TLS секций
// =============================================================================
procedure TProcDumpDlg.FillThreadsInfo(const hProcess: THandle);
const
  THREAD_ALL_ACCESS = STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $3FF;
  ThreadBasicInformation = 0;
var
  hSnap, hThread: THandle;
  ThreadEntry: TThreadEntry32;
  TBI: TThreadBasicInformation;
  TIB: NT_TIB;
  lpNumberOfBytesRead: DWORD;
begin
  // Делаем снимок нитей в системе
  hSnap := CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  if hSnap <> INVALID_HANDLE_VALUE then
  try
    ThreadEntry.dwSize := SizeOf(TThreadEntry32);
    if Thread32First(hSnap, ThreadEntry) then
    repeat
      // Проверяем принадлежность нити требуемому процессу
      if ThreadEntry.th32OwnerProcessID = CurrentPid then
      begin
        // Открываем нить
        hThread := OpenThread(THREAD_ALL_ACCESS,
          False, ThreadEntry.th32ThreadID);
        if hThread <> 0 then
        try
          // Если открыт не наш процесс - останавливаем работу нити
          if CurrentPid <> GetCurrentProcessId then
            SuspendThread(hThread);
          try
            // Получаем информацию по нити
            if NtQueryInformationThread(hThread, ThreadBasicInformation, @TBI,
              SizeOf(TThreadBasicInformation), nil) = 0 then
            begin
              // Читаем из удаленного адресного пространства
              // TIB (Thread Information Block) открытой нити
              if not ReadProcessMemory(hProcess,
                TBI.TebBaseAddress, @TIB, SizeOf(NT_TIB),
                lpNumberOfBytesRead) then
                RaiseLastOSError;
              // Добавляем в массив адрес стэка

              if AdvDataLen = 1 then
                AddNewData('Stack of main thread', TIB.StackLimit)
              else
                AddNewData('Stack of thread: ' + IntToHex(ThreadEntry.th32ThreadID, 8), TIB.StackLimit);
              // Добавляем в массив адрес TLS (Thread Local Storage)
              if AdvDataLen = 2 then
                AddNewData('TLS of main thread', TBI.TebBaseAddress)
              else
                AddNewData('TLS of thread: ' +
                    IntToHex(ThreadEntry.th32ThreadID, 8), TBI.TebBaseAddress);
            end;
          finally
            // Восстанавливаем работу нити
            if CurrentPid <> GetCurrentProcessId then
              ResumeThread(hThread);
          end;
        finally
          CloseHandle(hThread);
        end;
      end;
    until not Thread32Next(hSnap, ThreadEntry);
  finally
     CloseHandle(hSnap);
  end;
end;

//  Инициализация приложения
// =============================================================================
procedure TProcDumpDlg.FormCreate(Sender: TObject);
begin
  SetDebugPriv;
  FillProcessList;
  lvMemoryMap.DoubleBuffered := True;
  GrayedRow := False;
  CurrentPid := 0;
end;

//  Раскрасска строк ListView, отделяющая одну группу страниц от другой
// =============================================================================
procedure TProcDumpDlg.lvMemoryMapCustomDrawItem(Sender: TCustomListView;
  Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
begin
  if Boolean(Item.Data) then  
    Sender.Canvas.Brush.Color := RGB(235, 235, 235);
end;

end.
