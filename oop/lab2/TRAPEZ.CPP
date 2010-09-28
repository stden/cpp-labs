// Файл: Rectangle.cpp
// Релизация класса Трапеция
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <math.h>
#include <iostream.h>
#include "Trapez.h"

int CTrapezium::countreal = 0;
int CTrapezium::countall = 0;

CTrapezium :: CTrapezium(const CCountedPoint& x, const CCountedPoint& y, const double& l) : m_id(++countall) {

  m_list.insert(x);
  m_list.insert(y);
  m_list.insert(CCountedPoint(y.getX() + l + abs(x.getX() - y.getX()) * 2, y.getY()));
  m_list.insert(CCountedPoint(x.getX() + l, x.getY()));
  m_list.goFirst();

  cout << "        Trapezium number " << countreal << " created" << endl;
  ++countreal;
}

CTrapezium::~CTrapezium(void) {
  cout << "        Trapezium destroyed (remain " << countreal << ")" << endl;
  --countreal;
}

void CTrapezium :: MovedXdY(double dx, double dy) {
  // cout << "CPointSet::MovedXdY(" << x << "," << y << ")" << endl;
  m_list.goFirst();

  do {
    m_list.getElem().getValue().move(dx, dy);
  } while (m_list.goNext());
}

void CTrapezium :: MoveToPoint(const CCountedPoint& P) {
  m_list.goFirst();

  double dx = P.getX() - m_list.getElem().getValue().getX();
  double dy = P.getY() - m_list.getElem().getValue().getY();

  MovedXdY(dx, dy);
}

const CCountedPoint& CTrapezium :: getPoint(int index) {
  m_list.goFirst();

  for (index;index > 1;index--)
    m_list.goNext();

  return m_list.getElem().getValue();
}

