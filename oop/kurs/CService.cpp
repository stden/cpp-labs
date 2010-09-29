// Файл: Сservice.cpp
// Реализация класса Стакан
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#include <conio.h>
#include <iostream.h>
#include "GlList.h"

void CGlassList :: CGlassList() {
  VERBOSE_OUT && cout << "GlassList created" << endl;
}

void CGlassList :: ~CGlassList() {
  VERBOSE_OUT && cout << "GlassList deleted" << endl;
}

void CGlassList::MoveToPoint(const CCountedPoint& point) {
  for (List.goFirst();List.hasNext();List.goNext())
    List.getElem().getValue()->MoveToPoint(point);
}

void CGlassList::MovedXdY(double x, double y) {
  cout << "CGlassList::MovedXdY(" << x << "," << y << ")" << endl;
  for (List.goFirst();List.hasNext();List.goNext())
    List.getElem().getValue()->MovedXdY(x, y);
}

ostream& operator << (ostream& s, CGlassList& service) {
  s << "  " << "Service" << ": " << endl;
  for (service.List.goFirst();service.List.hasNext();service.List.goNext())
    s << "    (" << service.List.getElem().getValue() << "), " << endl;
  s << endl;
  return (s);
}
