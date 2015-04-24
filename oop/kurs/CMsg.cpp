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
                     int _Type, const CInfo& _Info, Direction _dir) :
  id(++total), FromID(_FromID), ToID(_ToID), Type(_Type),
  Info(_Info), direction(_dir) {
  ++current;

  if (debug) cout << "Created: " << *this;
}

CMessage :: CMessage(const CMessage& msg): id(++total), FromID(msg.getFromID()), ToID(msg.getToID()),
  Type(msg.getType()), Info(msg.getInfo()), direction(msg.getDirection()) {
  ++current;

  if (debug) cout << "Copied: " << *this;
}

CMessage :: ~CMessage() {
  --current;

  if (debug) cout << "Deleted: " << *this;
}

const char* CMessage :: InterpritateType(int type) const {
  switch (type) {
    case CONFIRMATION:
      return "CONFIRMATION";

    case REPORT:
      return "REPORT";

    default:
      return "ACTION";
  }
}




