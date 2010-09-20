// Файл: CMsg.h
// Реализация класса "сообщение"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CMsg.h"
#include <iostream.h>

int CMessage :: current = 0;
int CMessage :: total = 0;
int CMessage :: debug = 0;

CMessage :: CMessage(int _FromID, int _ToID,
                     int _Type, double _Info, Direction _dir) :
FromID(_FromID), ToID(_ToID), Type(_Type), Info(_Info), id(++total),
direction(_dir) {
  ++current;
  if (debug) Print("created");
}

CMessage :: CMessage(const CMessage &msg):id(++total), FromID(msg.getFromID()), ToID(msg.getToID()),
Type(msg.getType()), Info(msg.getInfo()), direction(msg.getDirection()) {
  ++current;
  if (debug) Print("copied");
}

CMessage :: ~CMessage() {
  --current;
  if (debug) Print("deleted");
}

void CMessage :: setFromID(int _FromID){
  FromID = _FromID;
}

void CMessage :: setToID(int _ToID){
  ToID = _ToID;
}

void CMessage :: setInfo(double _Info){
  Info = _Info;
}

const char* CMessage :: InterpritateType(int type) const {
  switch(type){
    case Confirmation: return "CONFIRMATION";
    case Report: return "REPORT";
    default: return "ACTION";
  }
}

void CMessage :: Print(char *prompt) const{
  cout << InterpritateType(Type) << " message #" << id << " " << prompt << " ";
  if (direction == Server_to_Client) 
    cout << "from server #" << FromID << " to client #" << ToID;
  else 
    cout << "from client #" << FromID << " to server #" << ToID;
  cout << " Info = " << Info << endl << endl;
}



