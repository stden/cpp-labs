// Файл: CService.h
// Объявление класса набор
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _CSERVICE_H
#define _CSERVICE_H

#include "CoPoint.h"
#include "Scene.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include <conio.h>

class CService {
private:
  CList<CScene> List;

public:
  CService();
  ~CService();

  /*
  *
  */
  void insert(const CScene& gl){ List.insert(gl); }

  void insertBegin(const CScene& gl){ List.insertBegin(gl); }
  void print(){ List.print(); }

  /*
  * Перемещение
  */
  void MoveToPoint(const CCountedPoint& point);

  /*
  * Смещение
  */
  void MovedXdY(double x, double y);


  friend ostream& operator << (ostream& s, CService& service);
};

#endif
