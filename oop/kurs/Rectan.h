// Файл: Rectan.h
// Объявление класса Прямоугольник
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#ifndef _RECTAN_H
#define _RECTAN_H

#include "CoPoint.h"
#include "CoList.h"
#include "debug.h"

class CRectangle {
 private:
  CList<CCountedPoint> m_list;

 public:

  /*
  * Конструктор
  * x - левая нижняя точка, y - правая верхняя
  */
  CRectangle(const CCountedPoint& x, const CCountedPoint& y) {
    m_list.insert(x);
    m_list.insert(CCountedPoint(x.getX(), y.getY()));
    m_list.insert(y);
    m_list.insert(CCountedPoint(y.getX(), x.getY()));
    assert(m_list.size() == 4);
    m_list.goFirst();
    cout << "      Rectangle created " << *this;
  };

  void MovedXdY(double dx, double dy) {
    cout << "CRectangle::MovedXdY(" << dx << "," << dy << ")" << endl;

    for (m_list.goFirst(); m_list.hasNext(); m_list.goNext())
      m_list.getValue().MovedXdY(dx, dy);
  };

  void MoveToPoint(const CCountedPoint& P) {
    m_list.goFirst();

    double dx = P.getX() - m_list.getValue().getX();
    double dy = P.getY() - m_list.getValue().getY();

    MovedXdY(dx, dy);
  };

  const CList<CCountedPoint>& getPoints() const {
    return m_list;
  }
  const CCountedPoint& getPoint(int index);

  void GetBorders(double* minx, double* maxx, double* miny, double* maxy);

  /*
  * Деструктор
  */
  ~CRectangle();

  friend ostream& operator << (ostream& s, CRectangle& r);
};


#endif