// Файл: GlassR.cpp
// Релизация класса: Стакан с кольцом
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <iostream.h>
#include <conio.h>
#include "GlassR.h"


// x - координаты нижнего левого угла основания стакана
// y - координаты левого верхнего угла стакана (трапеции)
// bottom - ширина основания
// hBottom - высота основания
// lessSide - толщина стенки (меньшая сторона параллелограмма)
CGlassR::CGlassR(const CCountedPoint& x, const CCountedPoint& y,
   const double& bottom, const double& hBottom, const double& lessSide):
  // Создаём стакан без кольца
  CGlass(x,y,bottom,hBottom,lessSide),
  // И добавляем кольцо
  // Центр "кольца" совпадает с точкой пересечения диагоналей "полости стакана"
  // X-координата центра 
  m_ring(x.getX()+bottom/2.0,
    0, // Y-координата будет задана позднее (поскольку её сложно вычислить)
    // Диаметр внешней окружности "кольца" равен половине высоты 
    // "трапеции" образующей "полость стакана" 
    // Мы передаём в конструктор радиус внешней окружности, который равен четверти
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
  // Получаем текущие координаты левого нижнего угла основания
  CCountedPoint basePoint = m_bottom.getPoint(0);

  // Вычисляем насколько надо сдвинуть фигуру, чтобы левая нижняя точка
  // встала в заданные координаты
  double dx = point.getX() - basePoint.getX();
  double dy = point.getY() - basePoint.getY();

  // Двигаем на вычисленный вектор (dx; dy)
  MovedXdY(dx, dy);
}

void CGlassR::MovedXdY(double x, double y)
{
  cout << "CGlassR::MovedXdY(" << x << "," << y << ")" << endl;
  // Двигаем последовательно все "кусочки" стакана
  m_bottom.MovedXdY(x, y); // основание
  m_cage.MovedXdY(x, y); // полость стакана
  m_leftSide.MovedXdY(x, y); // левую стенку
  m_rightSide.MovedXdY(x, y); // правую стенку
  m_ring.MovedXdY(x, y); // кольцо
}

CGlassR::~CGlassR(void) 
{
  cout << " GlassR destroyed" << endl;
}

