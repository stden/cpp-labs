unit Functions;

interface

uses SysUtils, Windows;

        //function StringSize(a: Cardinal) : String;
        function StringSize(a: TLargeInteger) : String;
implementation



{function StringSize(a: Cardinal) : String;
begin
  if (a < 1000) then
		result:= IntToStr(a)+' B'
	else if (a < 1000 * 1024) then
    result:= IntToStr(a div 1024)+' kB'
  else if (a < 1000 * 1048576) then
    result:= IntToStr(a div 1048576)+' MB'
  else
	  result:= IntToStr(a div 1073741824)+' GB';
end;  }

function StringSize(a: TLargeInteger) : String;
begin
  if (a < 1000) then
		result:= IntToStr(a)+' B'
	else if (a < 1000 * 1024) then
    result:= IntToStr(a div 1024)+' kB'
  else if (a < 1000 * 1048576) then
    result:= IntToStr(a div 1048576)+' MB'
  else
	  result:= IntToStr(a div 1073741824)+' GB';
end;

end.
