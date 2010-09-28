// Файл: Trapez.cpp
// Релизация класса Трапеция
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <math.h>
#include <iostream.h>
#include "Trapez.h"

CTrapezium::~CTrapezium(void) {
  VERBOSE_OUT && cout << "      Trapezium destroyed " << *this;
}

void CTrapezium :: MovedXdY(double dx, double dy) {
  // cout << "CPointSet::MovedXdY(" << x << "," << y << ")" << endl;
  for (m_list.goFirst();m_list.hasNext();m_list.goNext())
    m_list.getValue().MovedXdY(dx, dy);
}

void CTrapezium :: MoveToPoint(const CCountedPoint& P) {
  m_list.goFirst();

  double dx = P.getX() - m_list.getValue().getX();
  double dy = P.getY() - m_list.getValue().getY();

  MovedXdY(dx, dy);
}

const CCountedPoint& CTrapezium :: getPoint(int index) {
  m_list.goFirst();
  for (index;index > 1;index--)
    m_list.goNext();
  return m_list.getValue();
}

ostream& operator << (ostream& s, CTrapezium& r) {
  s << "Trapez: ";
  for (r.getPoints().goFirst();r.getPoints().hasNext();r.getPoints().goNext())
    s << r.getPoints().getValue() << " ";
  s << endl;
  return s;
}

void CTrapezium :: GetBorders(double *minx, double *maxx, double *miny, double *maxy) {
  for (getPoints().goFirst();getPoints().hasNext();getPoints().goNext()) {
    double x = m_list.getValue().getX();
    double y = m_list.getValue().getY();
    if (x < *minx) *minx = x;
    if (x > *maxx) *maxx = x;
    if (y < *miny) *miny = y;
    if (y > *maxy) *maxy = y;
  };
}

