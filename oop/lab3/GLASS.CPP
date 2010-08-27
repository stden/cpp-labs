// Файл: Glass.cpp
// Релизация класса Стакан
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <iostream.h>
#include <conio.h>
#include "Glass.h"

int CGlass :: countreal = 0;
int CGlass :: countall = 0;

CGlass::CGlass(const CCountedPoint& x, const CCountedPoint& y,
   const double& bottom, const double& hBottom, const double& lessSide):
  m_id(++countall) /* Присваиваем стакану очередной идентификатор */,
  m_bottom(x, CCountedPoint(x.getX() + bottom, x.getY() + hBottom)),
  m_cage(CCountedPoint(x.getX() + lessSide, x.getY() + hBottom),
   CCountedPoint(y.getX() + lessSide, y.getY()),
   bottom - 2 * lessSide),
  m_leftSide(CCountedPoint(x.getX(), x.getY() + hBottom),
       y, lessSide),
  m_rightSide(CCountedPoint(x.getX() + bottom - lessSide, x.getY() + hBottom),
  CCountedPoint(y.getX() + bottom + 2 * (x.getX() - y.getX()) - lessSide, y.getY()),
  lessSide)
{
  countreal++;
  cout << " Glass #" << m_id << " created" << endl;
}

void CGlass::MoveToPoint(const CCountedPoint& point)
{
  CCountedPoint basePoint = m_bottom.getPoint(0);

  double dx = point.getX() - basePoint.getX();
  double dy = point.getY() - basePoint.getY();

  MovedXdY(dx, dy);
}

void CGlass::MovedXdY(double x, double y)
{

  cout << "Glass #" << m_id << " MovedXdY(" << x << "," << y << ")" << endl;
  m_bottom.MovedXdY(x, y);
  m_cage.MovedXdY(x, y);
  m_leftSide.MovedXdY(x, y);
  m_rightSide.MovedXdY(x, y);
}

CGlass::~CGlass(void)
{
  cout << " Glass #" << m_id << " destroyed" << endl;
  countreal--;
}

