// Файл: CService.h
// Объявление класса набор
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _CSERVICE_H
#define _CSERVICE_H

#include "CoPoint.h"
#include "Glass.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include <conio.h>

class CService {
 private:
  CList<CGlass> GlassList;

 public:
  CService();
  ~CService();



  void insert(const CGlass& gl) {
    GlassList.insert(gl);
  }
  void insertBegin(const CGlass& gl) {
    GlassList.insert(gl);
  }
  void print() {
    GlassList.print();
  }

  /*
  * Перемещение
  */
  void MoveToPoint(const CCountedPoint& point);

  /*
  * Смещение
  */
  void MovedXdY(double x, double y);



  friend ostream& operator << (ostream& s, CService& service) {
    s << "  " << "Service" << ": " << endl;
    service.GlassList.goFirst();

    do {
      s << "    (" << service.GlassList.getElem().getValue() << "), " << endl;
    } while (service.GlassList.goNext());

    s << "    (" << service.GlassList.getElem().getValue() << ")";
    s << endl;

    return (s);
  }

};

#endif
