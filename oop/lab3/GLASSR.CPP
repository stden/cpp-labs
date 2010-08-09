// Файл: GlassR.cpp
// Релизация класса: Стакан с кольцом
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <iostream.h>
#include <conio.h>
#include "GlassR.h"


CGlassR::CGlassR(const CCountedPoint& x, const CCountedPoint& y,
   const double& bottom, const double& hBottom, const double& lessSide):
  CGlass(x,y,bottom,hBottom,lessSide),
  m_ring(x.getX()+bottom/2.0,
    0, // Y-координата будет задана позднее
    (y.getY()-x.getY()-hBottom)/4.0)
{
  // Вычисляем высоту большого треугольника
  double HBig = y.getY()-x.getY()-hBottom;
  // Вычисляем основание большого треугольника
  double LBig = x.getX()-y.getX()+bottom;
  // Основание маленького треугольника
  double LSmall = bottom/2;
  // Высота маленького треугольника
  double HSmall = HBig/LBig*LSmall; // Поскольку треугольники подобны
  // В итоге координата Y центров окружностей будет
  double Y = x.getY() + hBottom + HSmall;

  m_ring.setY(Y);

  cout << " GlassR created" << endl;
}

void CGlassR::MoveToPoint(const CCountedPoint& point)
{
  CCountedPoint basePoint = m_bottom.getPoint(0);

  double dx = point.getX() - basePoint.getX();
  double dy = point.getY() - basePoint.getY();

  MovedXdY(dx, dy);
}

void CGlassR::MovedXdY(double x, double y)
{
  cout << "CGlassR::MovedXdY(" << x << "," << y << ")" << endl;
//  CGlass::MovedXdY(x, y);
  m_bottom.MovedXdY(x, y);
  m_cage.MovedXdY(x, y);
  m_leftSide.MovedXdY(x, y);
  m_rightSide.MovedXdY(x, y);
  m_ring.MovedXdY(x, y);
}

CGlassR::~CGlassR(void)
{
 cout << " GlassR destroyed" << endl;
}

