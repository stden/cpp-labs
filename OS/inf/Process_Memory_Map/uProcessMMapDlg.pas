////////////////////////////////////////////////////////////////////////////////
//
//  ****************************************************************************
//  * Project   : Process Memory Map Sample
//  * Unit Name : uProcessMMapDlg
//  * Purpose   : ���������������� ������ ���������
//  *           : ����� ������ ���������� ��������
//  * Author    : ��������� (Rouse_) ������
//  * Copyright : � Fangorn Wizards Lab 1998 - 2009.
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

// ��� ����������� ���������� �������, ����� � ��������, � ���� �������
// =============================================================================
{$I 'native.inc'}

//  ������� �������� ���������� ���������� ��� ��������,
//  � ��������� ������ ����� �������� ��� csrss.exe,
//  svchost.exe � �.�. ����� �����
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

//  ������� �������� ���� � �������������� ���������� ������ � ����������� ����
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
  // �������������� ��������� ��� ������ ZwOpenFile
  RtlInitUnicodeString(@US, StringToOleStr(Value));
  // ������ ������� InitializeObjectAttributes
  FillChar(OA, SizeOf(OBJECT_ATTRIBUTES), #0);
  OA.Length := SizeOf(OBJECT_ATTRIBUTES);
  OA.ObjectName := @US;
  OA.Attributes := OBJ_CASE_INSENSITIVE;
  // ������� ZwOpenFile �������� ��������� �����, ���� � ������� �����������
  // � �������������� ���������� ������, ��������:
  // \SystemRoot\System32\ntdll.dll
  // \??\C:\Windows\System32\ntdll.dll
  // \Device\HarddiskVolume1\WINDOWS\system32\ntdll.dll
  // ������� ����� ������������ �� ��� ��������� ������
  NTSTAT := ZwOpenFile(@hFile, FILE_READ_DATA or SYNCHRONIZE, @OA, @IO,
    FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
    FILE_SYNCHRONOUS_IO_NONALERT);
  if NTSTAT = STATUS_SUCCESS then
  try
    // ���� ������, ������ ������� ��� ��������������� ����
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
      // ���� �� �������� ����� ZwOpenFile ����
      // ������������ � ���� \Device\HarddiskVolume�\���-���
      // �������� ������ ��� ����������� � �������� ������
      SetLength(Buff, DriveTotalSize);
      Count := GetLogicalDriveStrings(DriveTotalSize, @Buff[1]) div DriveNameSize;
      for I := 0 to Count - 1 do
      begin
        Volume := PChar(@Buff[(I * DriveNameSize) + 1]);
        Volume[3] := #0;
        // ����������� ��� ������� ����� � ���������� ������ �
        // ���������� � ����������������� �����
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

//  ������� ������� ����� ������� � ��������
//  � ��������� �� ��������� �������������
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

//  ������� ������� ����������� ����� ������� � ��������
//  � ��������� �� ��������� �������������
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

//  ��������� ��������� � ���������� TListItem ������� � �����������
//  � ��������� �������� � ���������� ������� � ��������
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

//  ������� ����������� ���������� ������������� ����� �
//  ��������� ������ ����������, ������������� �� ������ ���������� ������ 
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
    // �������� ����� ����������
    if (ImageDirectoryEntryToDataEx(ImageInfo.MappedAddress,
      False, I, dwDirSize, ish) <> nil) and (ish <> nil) then
    begin
      // �������, ��������� �� �� � ������� ��������
      // ������������ ������ � ����������� TLS,
      // ��� ��������� �������� �� ���� ��������,
      // ��� ���� ���������� � ���� ������� ��� ��...
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

//  ������� ��������� �������������� ������ � ���������� ����,
//  �������� �� ������ ���������� ���
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

//  ������� ��������� �������������� ������ � ���������� ����,
//  �������� �� ������ �� ������ ���
//  �������� �� ������ �������������������� ������
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

//  ������� ���������� ������ ������ � ������ ������������,
//  ���������� � PE ���������.
//  ������, ���������� ��� �������� ����� IMAGE_SCN_ALIGN_���BYTES � ������,
//  ������� ���������� �������������� ������������, �� ������...
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

//  ������� ���������� ������ �� ����� �� �������� ������
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

  // ��������� ���������, ����������� �� ������ ������ � ������� ��������,
  // � ���� ��, �� �������� ������ � ������ � �������������� � ��� ���������
  // � ListView
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
        // ���� ��� ���� ������, �������� ���������� ���� ����
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
  // �������� ���������� ������� � �������,
  // � ������� �� ����� ������������� ����� �� �����
  if (lpBuffer.State = MEM_FREE) or (lpBuffer.State = MEM_RESERVE) or
    (DWORD(lpBuffer.BaseAddress) <= MM_LOWEST_USER_ADDRESS) then
    Exit;
  // ���������� ����� ��������� �������� � ������� �������� �����
  BaseAddr := pSectionAddr;
  // ���������� ����� � ��� �������, ��� ��������� ����������
  if MapAndLoad(PChar(NormalizePath(ImagePath)), nil, @ImageInfo, True, True) then
  try
    // �������� - �������� �� ����� PE ������?
    if ImageInfo.FileHeader^.Signature = IMAGE_NT_SIGNATURE then
    begin
      Result := True;
      GrayedRow := not GrayedRow;
      // ���� ��� � �������, ��������� ���������� � ��������� �� ���������
      AItem := ListView.Items.Add;
      AItem.Data := Pointer(GrayedRow);
      with AItem do
      begin
        // ����� ������
        Caption := IntToHex(DWORD(lpBuffer.BaseAddress), 8);
        // ������ �� ������ ����� ���� ������� ��������� ������,
        // ���� ������� ������� ��������
        if lpBuffer.RegionSize < ImageInfo.Sections^.VirtualAddress then
          SubItems.Add(IntToHex(lpBuffer.RegionSize, 8))
        else
          SubItems.Add(IntToHex(ImageInfo.Sections^.VirtualAddress, 8));
        // ��� ������
        SubItems.Add(ExtractFileName(ImagePath));
        SubItems.Add('');
        SubItems.Add('PE Header');
        // ��������� �������� � ������
        DisplayStateAndProtect(AItem, lpBuffer);
        // ���� � ������������ ������
        if GetMappedFileName(hProcess, lpBuffer.BaseAddress,
          @MappedName[0], MAX_PATH) > 0 then
          SubItems.Add(NormalizePath(string(MappedName)))
        else
          SubItems.Add('');
      end;
    end
    else
      Exit;
    // ����������� ��� ������ ������ � ������������ �� � ���������� ������ 
    ImageSectionHeader := ImageInfo.Sections;
    MovedSectionCount := 0;
    SectionEnd := lpBuffer.RegionSize;
    dwLength := SizeOf(TMemoryBasicInformation);
    // ������ ���� �� ��� ���, ���� �� ��������� ������
    while DWORD(MovedSectionCount) < ImageInfo.NumberOfSections do
    begin
      // ������������ ������
      MoveSectionsToPage;
      // ������������� �� ��������� ��������
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

//  ��������� ��������� ������ ���������
//  � ���������� �� �������� ��������� ��������
// =============================================================================
procedure TProcDumpDlg.btnRefreshClick(Sender: TObject);
begin
  FillProcessList;
  if CurrentPid > 4 then
    FillProcessMemoryMap(CurrentPid);
end;

//  ������������ ������ ������ �������,
//  �������� ������� FillProcessMemoryMap ��� ���������� ����� ��������
// =============================================================================
procedure TProcDumpDlg.cbProcessChange(Sender: TObject);
begin
  if cbProcess.ItemIndex >= 0 then
    FillProcessMemoryMap(DWORD(cbProcess.Items.Objects[cbProcess.ItemIndex]));
end;

//  ��������� ����������� ���� ��������
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
  // �.�. ������ Heap32ListFirst, Heap32ListNext, Heap32First, Heap32Next
  // �������� ���������� ��������, ��-�� ����������� ������
  // RtlQueryProcessDebugInformation �� ������ ��������, �� ������� �� �����
  // ����������� ����� ��� ��������� �������
  // ������� ���������� ������
  pDbgBuffer := RtlCreateQueryDebugBuffer(0, False);
  if pDbgBuffer <> nil then
  try
    // ����������� ���������� �� ������ ��� ��������
    if RtlQueryProcessDebugInformation(CurrentPid,
      RTL_QUERY_PROCESS_HEAP_SUMMARY or RTL_QUERY_PROCESS_HEAP_ENTRIES,
      pDbgBuffer) = STATUS_SUCCESS then
    begin
      // �������� ��������� �� ���� �� ���������
      pHeapInformation := @pDbgBuffer^.Heaps^.Heaps[0];
      // ����������� ��� �� �����...
      for I := 0 to pDbgBuffer^.Heaps^.NumberOfHeaps - 1 do
      begin
        // ������� � ������ �������
        pHeapEntry := pHeapInformation^.Entries;
        dwAddr := DWORD(pHeapEntry^.u.s2.FirstBlock) +
          pHeapInformation^.EntryOverhead;
        dwLastSize := 0;
        for A := 0 to pHeapInformation^.NumberOfEntries - 1 do
        begin
          hit_seg_count := 0;
          while (pHeapEntry^.Flags and RTL_HEAP_SEGMENT) = RTL_HEAP_SEGMENT do
          begin
            // ���� ���� ������� ������ RTL_HEAP_SEGMENT,
            // �� ������������ ����� �����
            dwAddr := DWORD(pHeapEntry^.u.s2.FirstBlock) +
              pHeapInformation^.EntryOverhead;
            Inc(pHeapEntry);
            Inc(hit_seg_count);
            // �������� ������ �� ������� ������
            if A + hit_seg_count >=
              Integer(pHeapInformation^.NumberOfEntries - 1) then
              Continue;
          end;
          // ���� ���� �� ����� ������ � ��������, �� ������� ����� ����� �����,
          // ������ ����������� ����� + ������ ����������� �����
          if hit_seg_count = 0 then
            Inc(dwAddr, dwLastSize);
          // ��������� ��������� � ������
          if I = 0 then
            AddNewData('Heap ID: 0 (default)', dwAddr)
          else
            AddNewData('Heap ID: ' + IntToStr(I), dwAddr);
         // ���������� ����� ���������� �����
         dwLastSize := pHeapEntry^.Size;
         // ��������� � ���������� �����
         Inc(pHeapEntry);
        end;
        // ��������� � ��������� ����
        Inc(pHeapInformation);
      end;
    end;
  finally
    RtlDestroyQueryDebugBuffer(pDbgBuffer);
  end;
end;

//  ��������� �������� ���������� �� PEB ��������
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

//  ��������� �������� ��������� ������� �������� ���������
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
    // ����������� ������ ��������� ������
    if NtQuerySystemInformation(
      SystemProcessesAndThreadsInformation,
      nil, 0, ReturnLength) <> STATUS_INFO_LENGTH_MISMATCH then Exit;
    if ReturnLength > 0 then
    begin
      // �������� ������
      GetMem(SystemInformation, ReturnLength);
      try
        // �������� ������ ���������
        if NtQuerySystemInformation(SystemProcessesAndThreadsInformation,
          SystemInformation, ReturnLength, ReturnLength) = 0 then
        begin
          // ����� �� ������ � ������� ������ � ������
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

//  ��������� ����������� ��� �������� ������ ��������
//  � ������� ���������� � ��� � ListView
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
    // ��������� ������� �� ������
    hProcess := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ,
      False, PID);
    if hProcess = 0 then
      RaiseLastOSError;
    try
      // ����������� ��� ���� ��������,
      // ���������� ������ �� ����� � TLS ������
      FillThreadsInfo(hProcess);
      // ������� ���������� �� ����� ��������� ��������
      FillPEBInfo(hProcess);
      // ����������� ��� ���� ��������
      FillHeapsInfo;
      pSectionAddr := 0;
      dwLength := SizeOf(TMemoryBasicInformation);
      LastShowImage := False;
      GrayedRow := False;
      // ���������� � ����� ��� �������� ������ �� �������,
      // �� ����������� ��������� ������������ 
      while pSectionAddr < MM_USER_PROBE_ADDRESS do
      begin
        // ������� ��������� ��������
        if VirtualQueryEx(hProcess,
          Pointer(pSectionAddr), lpBuffer, dwLength) <> dwLength then
          RaiseLastOSError;

        // ��������, ����� �� ���������� ����������������� � ������ ��������?
        InvalidPage := False;
        if not cbShowFreeMem.Checked then
          if lpBuffer.State = MEM_FREE then
            InvalidPage := True;
        if not cbShowReserve.Checked then
          if lpBuffer.State = MEM_RESERVE then
            InvalidPage := True;
        if InvalidPage then
        begin
          // ���� �� ����� - ��������� � ��������� ��������
          Inc(pSectionAddr, lpBuffer.RegionSize);
          Continue;
        end;

        // �������, ����������� �� �������� ������-���� ������
        if GetModuleFileNameEx(hProcess, THandle(lpBuffer.BaseAddress),
          @OwnerName[0], MAX_PATH) > 0 then
          // �� �������� �������� �� ����,
          // ������� ������ �� ���� � ��������� ���������
          if DisplayImageData(lvMemoryMap, hProcess, String(OwnerName),
            lpBuffer, pSectionAddr, GrayedRow) then
          begin
            LastShowImage := True;
            Continue;
          end;

        // ��������� ������ �����,
        // ��� ����������� ������������ ������� � ListView,
        // ����������� ������ ��������� ������ ���� �� ����� ��� ����������� 
        if LastShowImage then
        begin
          LastShowImage := False;
          GrayedRow := not GrayedRow;
        end;

        Inc(pSectionAddr, lpBuffer.RegionSize);

        // ��������� ������ �� �������� � ListView
        AItem := lvMemoryMap.Items.Add;
        AItem.Data := Pointer(GrayedRow);
        with AItem do
        begin
          // ����� ��������
          Caption := IntToHex(DWORD(lpBuffer.BaseAddress), 8);
          // ����� ��������
          SubItems.Add(IntToHex(lpBuffer.RegionSize, 8));
          // �������� (����������� ��� ������ ������ �� ������)
          SubItems.Add('');
          //  ������ (����������� ��� ������ ������ �� ������)
          SubItems.Add('');
          // ���������� �������� ����������� �� ������� ������� ����� ��������
          ContainStr := '';
          for I := 0 to AdvDataLen - 1 do
          begin
            // ���� ����� ����� ���� ��� ��� TLS ������ ������ �� ���������,
            // ������� ���������� � ��������������� �������
            if (AdvData[I].Addr >= DWORD(lpBuffer.BaseAddress)) and
             (AdvData[I].Addr < DWORD(lpBuffer.BaseAddress) +
             lpBuffer.RegionSize) then
              ContainStr := AdvData[I].Description;
          end;
          SubItems.Add(ContainStr);
          // ��������� �������� � ��������� �������
          DisplayStateAndProtect(AItem, lpBuffer);
          // �������� ������������ ������
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

//  ��������� ����������� ��� ���� �������� � ��������� ���������� �����
//  ����������� � ������� ����� ������ ���� � ������� TLS ������
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
  // ������ ������ ����� � �������
  hSnap := CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
  if hSnap <> INVALID_HANDLE_VALUE then
  try
    ThreadEntry.dwSize := SizeOf(TThreadEntry32);
    if Thread32First(hSnap, ThreadEntry) then
    repeat
      // ��������� �������������� ���� ���������� ��������
      if ThreadEntry.th32OwnerProcessID = CurrentPid then
      begin
        // ��������� ����
        hThread := OpenThread(THREAD_ALL_ACCESS,
          False, ThreadEntry.th32ThreadID);
        if hThread <> 0 then
        try
          // ���� ������ �� ��� ������� - ������������� ������ ����
          if CurrentPid <> GetCurrentProcessId then
            SuspendThread(hThread);
          try
            // �������� ���������� �� ����
            if NtQueryInformationThread(hThread, ThreadBasicInformation, @TBI,
              SizeOf(TThreadBasicInformation), nil) = 0 then
            begin
              // ������ �� ���������� ��������� ������������
              // TIB (Thread Information Block) �������� ����
              if not ReadProcessMemory(hProcess,
                TBI.TebBaseAddress, @TIB, SizeOf(NT_TIB),
                lpNumberOfBytesRead) then
                RaiseLastOSError;
              // ��������� � ������ ����� �����

              if AdvDataLen = 1 then
                AddNewData('Stack of main thread', TIB.StackLimit)
              else
                AddNewData('Stack of thread: ' + IntToHex(ThreadEntry.th32ThreadID, 8), TIB.StackLimit);
              // ��������� � ������ ����� TLS (Thread Local Storage)
              if AdvDataLen = 2 then
                AddNewData('TLS of main thread', TBI.TebBaseAddress)
              else
                AddNewData('TLS of thread: ' +
                    IntToHex(ThreadEntry.th32ThreadID, 8), TBI.TebBaseAddress);
            end;
          finally
            // ��������������� ������ ����
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

//  ������������� ����������
// =============================================================================
procedure TProcDumpDlg.FormCreate(Sender: TObject);
begin
  SetDebugPriv;
  FillProcessList;
  lvMemoryMap.DoubleBuffered := True;
  GrayedRow := False;
  CurrentPid := 0;
end;

//  ���������� ����� ListView, ���������� ���� ������ ������� �� ������
// =============================================================================
procedure TProcDumpDlg.lvMemoryMapCustomDrawItem(Sender: TCustomListView;
  Item: TListItem; State: TCustomDrawState; var DefaultDraw: Boolean);
begin
  if Boolean(Item.Data) then  
    Sender.Canvas.Brush.Color := RGB(235, 235, 235);
end;

end.
