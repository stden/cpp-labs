// Файл: Rectangle.cpp
// Релизация класса Прямоугольник
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.1

#include <iostream.h>
#include "Rectan.h"

int cRectangle::countreal = 0;
int cRectangle::countall = 0;



cRectangle::cRectangle(const CCountedPoint& x, const CCountedPoint& y) : m_id(++countall) {
  m_list.insert(x);
  m_list.insert(CCountedPoint(x.getX(), y.getY()));
  m_list.insert(y);
  m_list.insert(CCountedPoint(y.getX(), x.getY()));
  m_list.goFirst();

  cout << "        Rectangle number " << countreal << " created" << endl;
  ++countreal;

}

cRectangle::~cRectangle() {
  countreal--;
  cout << "        Rectangle destroyed (remain " << countreal << ")" << endl;
}

void cRectangle :: MovedXdY(double dx, double dy) {
  // cout << "CPointSet::MovedXdY(" << x << "," << y << ")" << endl;
  m_list.goFirst();

  do {
    m_list.getElem().getValue().move(dx, dy);
  } while (m_list.goNext());
}

void cRectangle :: MoveToPoint(const CCountedPoint& P) {
  m_list.goFirst();

  double dx = P.getX() - m_list.getElem().getValue().getX();
  double dy = P.getY() - m_list.getElem().getValue().getY();

  MovedXdY(dx, dy);
}

const CCountedPoint& cRectangle :: getPoint(int index) {
  m_list.goFirst();

  for (index; index > 1; index--)
    m_list.goNext();

  return m_list.getElem().getValue();
}
