// Файл: Rectan.cpp
// Релизация класса Прямоугольник
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.1

#include <iostream.h>
#include "Rectan.h"

CRectangle::CRectangle(const CCountedPoint& x, const CCountedPoint& y) {
  m_list.insert(x);
  m_list.insert(CCountedPoint(x.getX(), y.getY()));
  m_list.insert(y);
  m_list.insert(CCountedPoint(y.getX(), x.getY()));
  assert(m_list.size() == 4);
  m_list.goFirst();
  cout << "      Rectangle created " << *this;
}

CRectangle::~CRectangle() {
  cout << "      Rectangle destroyed" << *this;
}

void CRectangle :: GetBorders(double *minx, double *maxx, double *miny, double *maxy) {
  m_list.goFirst();
  do {
    double x = m_list.getValue().getX();
    double y = m_list.getValue().getY();
    if (x < *minx) *minx = x;
    if (x > *maxx) *maxx = x;
    if (y < *miny) *miny = y;
    if (y > *maxy) *maxy = y;
  } while (m_list.goNext());
}

ostream& operator << (ostream& s, CRectangle& r) {
  s << "  " << "Rectangle: ";
  for (r.getPoints().goFirst();r.getPoints().hasNext();r.getPoints().goNext())
    s << r.getPoints().getValue() << " ";
  s << endl;
  return s;
}

const CCountedPoint& CRectangle :: getPoint(int index) {
  m_list.goFirst();

  for (index;index > 1;index--)
    m_list.goNext();

  return m_list.getValue();
}


