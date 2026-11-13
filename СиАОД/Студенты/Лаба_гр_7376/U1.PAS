Unit U1;
Interface
type List = ^LTem;
     LTem = record
       Value: Char;
       next: List;
       prev: List;
     end;
var
  tek:List;
procedure LtCreate( var L: List );
procedure LtGoBegin ( var L: List );
procedure LtGoEnd( var L: List );
procedure LtShow( var L: List );
procedure LtClear( var L: List );
procedure LtInsert( var L: List; NewElem: LTem);
procedure LtDelete( var L: List );
procedure LtReplace( var L:List; NewElem: LTem);
procedure LtGoNext(var L: List);
procedure LtGoPrior( var L: List);
function LtCurrent ( var L: List ): Char;
function LtNotEmpty( var L: List ) : Boolean;
function LtNotFull( var L: List): Boolean;
function LtAtBegin( var L: List): Boolean;
function LtAtEnd( var L: List): Boolean;

Implementation

procedure LtCreate( var L: List );
begin
  L := nil;
  tek := nil;
end;
procedure LtGoBegin ( var L: List );
begin
  if L <> nil then
    While (tek^.prev <> nil) do
    tek := tek^.prev
end;
procedure LtGoEnd( var L: List );
begin
   if L <> nil then
    While (tek^.next <> nil) do
    tek := tek^.next;
end;
procedure LtShow( var L: List );
  var Next: List;
begin
  if L <> nil then
    begin
      Next := L;
      Repeat
        Write(Next^.Value,' ');
        Next := Next^.next;
      Until Next = nil;
    end;
  WriteLn;
end;
procedure LtClear( var L: List );
  var Back, Next: List;
begin
  if L <> nil then
    begin
      Back := tek^.prev;
      repeat
        Next := tek^.next;
        Dispose(tek);
        tek := Next;
      Until Next = nil;
      tek := Back;
      if tek <> nil then
      repeat
        Back := tek^.prev;
        Dispose(tek);
        tek := Back;
      Until Back = nil;
    end;
 L := nil;
end;
procedure LtInsert( var L: List; NewElem: LTem);
var Example: List;
begin
    begin
    if L = nil then
     begin
      New(L);
      L^.next := nil;
      L^.prev := nil;
      L^.Value := NewElem.Value;
      tek := L;
     end
  else
     begin
      if tek^.next <> nil then
        begin
          New(Example);
          Example^.Value := NewElem.Value;
          Example^.next := tek^.next;
          Example^.prev := tek;
          tek^.next^.prev := Example;
          tek^.next := Example;
          tek := Example;
        end
      else
        begin
          New(Example);
          Example^.Value := NewElem.Value;
          Example^.next := tek^.next;
          Example^.prev := tek;
          tek^.next := Example;
          tek := Example;
        end;
    end;
  end;
end;
procedure LtDelete( var L: List );
  var Temp: List;
begin
  if L <> nil then
    begin
      if (tek^.prev = nil) and (tek^.next = nil) then
        LtClear(L)
      else
      if tek^.prev = nil then
        begin
          tek^.next^.prev := nil;
          Temp := tek^.next;
          Dispose(tek);
          tek := Temp;
          L := Temp;
        end
      else
      if tek^.next = nil then
        begin
          tek^.prev^.next := nil;
          Temp := tek^.prev;
          Dispose(tek);
          tek := Temp;
          LtGoBegin( L );
        end
      else
        begin
          tek^.prev^.next := tek^.next;
          tek^.next^.prev := tek^.prev;
          Temp := tek^.next;
          Dispose(tek);
          tek := Temp;
        end;
    end;
end;
procedure LtReplace( var L:List; NewElem: LTem);
begin
  tek^.Value := NewElem.Value;
end;
procedure LtGoNext(var L: List);
begin
  if (L <> nil) and (tek^.next <> nil) then
    begin
      tek := tek^.next;
      WriteLn(tek^.Value);
    end;
end;
procedure LtGoPrior( var L: List);
begin
  if (L <> nil) and (tek^.prev <> nil) then
    begin
      tek := tek^.prev;
      WriteLn(tek^.Value);
    end;
end;
function LtCurrent ( var L: List ): Char;
begin
  if L <> nil then
    LtCurrent := tek^.Value
  else LtCurrent := #0;
end;
function LtNotEmpty( var L: List ) : Boolean;
begin
  if L <> nil
     then LtNotEmpty := true
  else LtNotEmpty := false;
end;
function LtNotFull( var L: List): Boolean;
begin
  if MaxAvail >= SizeOf(LTem) then
    LtNotFull := true
  else
    LtNotFull := false;
end;
function LtAtBegin( var L: List): Boolean;
begin
  if L <> nil then
    begin
      if tek^.prev = nil
         then LtAtBegin := true
     else LtAtBegin := false
    end;
end;
function LtAtEnd( var L: List): Boolean;
begin
  if L <> nil then
    begin
      if tek^.next = nil then LtAtEnd := true
      else LtAtEnd := false
    end;
end;
begin
end.