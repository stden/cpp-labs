// Файл: CGlassList.h
// Объявление класса набор
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _GLASSLIST_H
#define _GLASSLIST_H

#include "CoPoint.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Glass.h"
#include <conio.h>

class CGlassList {
protected:
  CList<CGlass*> List;

public:
  CGlassList();
  ~CGlassList();

  /*
  * Добавление в список новых стаканов
  */
  void insert(CGlass* gl) { List.insert(gl); }
  void insertBegin(CGlass* gl) { List.insertBegin(gl); }

  /*
  * Перемещение
  */
  void MoveToPoint(const CCountedPoint& point);

  /*
  * Смещение
  */
  void MovedXdY(double x, double y);

  /*
  *
  */
  CGlass* getFirst() {
    List.goFirst();
    return List.getValue();
  }

  CGlass* getByID(int glassID) {
    for (List.goFirst();List.hasNext();List.goNext())
      if (List.getValue()->getID() == glassID)
        return List.getValue();
    return NULL;
  }

  int Delete(int glassID) {
    for (List.goFirst();List.hasNext();List.goNext())
      if (List.getValue()->getID() == glassID) {
        List.dispose();
        return 1;
      }
    return 0;
  }

  friend ostream& operator << (ostream& s, CGlassList& list);
};

#endif
