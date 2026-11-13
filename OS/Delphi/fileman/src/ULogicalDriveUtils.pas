unit ULogicalDriveUtils;

interface

uses 
  SysUtils, WinTypes, WinProcs, Messages, Classes;

function UpdateAvailableDrives():TStrings;

implementation

function UpdateAvailableDrives():TStrings;
var 
  a, r: LongInt; 
  lpBuffer: array[0..255] of char; 
  currDrive: array[0..255] of char;
  lpDrives: pchar; 
  tmp: TStrings;
begin
  getmem(lpDrives, 256); 
  fillchar(lpBuffer, 64, #32);
  tmp := TStringList.Create;
  r := GetLogicalDriveStrings(255, lpBuffer);

  if r <> 0 then 
    begin 
      strlcopy(lpBuffer, lpBuffer, r);
      for a := 0 to r do 
        lpDrives[a] := lpBuffer[a];
        lpBuffer[r + 1] := #0;
        repeat
          strlcopy(currDrive, lpDrives, 1);
          //lpDrives := @lpDrives[4];
          tmp.AddObject(lpDrives[0]+':', TObject(lpDrives[0]));
          lpDrives := @lpDrives[4];
      until lpDrives[0] = #0;
    end;            
    Result := tmp;
end; 

end.
