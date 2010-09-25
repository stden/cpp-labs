// Файл: Rectan.h
// Объявление класса Прямоугольник
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#ifndef _RECTAN_H
#define _RECTAN_H

#include "CoPoint.h"
#include "CoList.h"

class CRectangle
{
private :
  CList<CCountedPoint> m_list;

public:

  /*
  * Конструктор
  * x - левая нижняя точка, y - правая верхняя
  */
  CRectangle(const CCountedPoint& x, const CCountedPoint& y);

  void MovedXdY (double dx, double dy);
  void MoveToPoint (const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints() const { return m_list; }
  const CCountedPoint& getPoint(int index);

  void GetBorders( double *minx,double *maxx,double *miny,double *maxy );

  /*
  * Деструктор
  */
  ~CRectangle();

  friend ostream& operator << (ostream& s, CRectangle& r);
};


#endif