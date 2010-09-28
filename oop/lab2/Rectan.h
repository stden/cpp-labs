// Файл: Rectangle.h
// Объявление класса Прямоугольник
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#ifndef _RECTAN_H
#define _RECTAN_H

#include "CoPoint.h"
#include "CoList.h"

class cRectangle {
private :
  CList<CCountedPoint> m_list;

//Количество экземпляров класса прямоугольник
  static int countreal;

  //Общее количество созданных когда-либо экземпляров
  static int countall;

  //Идентификатор
  int m_id;

public:

  /*
  * Конструктор
  * x - левая нижняя точка, y - правая верхняя
  */
  cRectangle(const CCountedPoint& x, const CCountedPoint& y);

  void MovedXdY(double dx, double dy);
  void MoveToPoint(const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints() { return m_list; }
  const CCountedPoint& getPoint(int index);

  static int getCount() { return countreal; }

  int getId() { return m_id; }



  /*
  * Деструктор
  */
  ~cRectangle();

  friend ostream& operator << (ostream& s, cRectangle& r) {
    s << "  " << "Rectangle" << ": " << endl;
    r.getPoints().goFirst();

    do {
      s << "    (" << r.getPoints().getElem().getValue() << "), " << endl;
    } while (r.getPoints().goNext());

    s << "    (" << r.getPoints().getElem().getValue() << ")";
    s << endl;

    return (s);
  }

};


#endif