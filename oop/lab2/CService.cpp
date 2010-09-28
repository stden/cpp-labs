// Файл: Сservice.cpp
// Реализация класса Стакан
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#include <conio.h>
#include <iostream.h>
#include "CService.h"



void CService :: CService() {
  cout << "Service created" << endl;
}

void CService :: ~CService() {
  cout << "Service deleted" << endl;
}


void CService::MoveToPoint(const CCountedPoint& point) {
  GlassList.goFirst();

  do {
    GlassList.getElem().getValue().MoveToPoint(point);
  } while (GlassList.goNext());

  GlassList.getElem().getValue().MoveToPoint(point);
}

void CService::MovedXdY(double x, double y) {
  cout << "CService::MovedXdY(" << x << "," << y << ")" << endl;

  GlassList.goFirst();
  do {
    //  cout << "!1!" << endl;
    GlassList.getElem().getValue().MovedXdY(x, y);
  } while (GlassList.goNext());

//  cout << "!2!" << endl;
//  GlassList.getElem().getValue().MovedXdY(x, y);
}