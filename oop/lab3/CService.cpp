// Файл: Сservice.cpp
// Реализация класса Стакан
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#include <conio.h>
#include <iostream.h>
#include "CService.h"

void CService :: CService () {
  cout << "Service created"<<endl;
}

void CService :: ~CService () {
  cout << "Service deleted"<<endl;
}


void CService::MoveToPoint(const CCountedPoint& point)
{
  List.goFirst();
  do{
    List.getElem().getValue().MoveToPoint(point);
  }while(List.goNext());
  List.getElem().getValue().MoveToPoint(point);
}

void CService::MovedXdY(double x, double y)
{
  cout << "CService::MovedXdY(" << x << "," << y << ")" << endl;
  List.goFirst();
  do{
    List.getElem().getValue().MovedXdY(x, y);
  } while(List.goNext());
}

ostream& operator << (ostream& s, CService& service)
{
  s << "  " << "Service" << ": " << endl;
  service.List.goFirst();
  do{
    s << "    (" << service.List.getElem().getValue() << "), " << endl;
  }while(service.List.goNext());
  s << "    (" << service.List.getElem().getValue() << ")";
  s << endl;

  return (s);
}
