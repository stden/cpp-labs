// Файл: Rectangle.h
// Объявление класса Стакан
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _GLASS_H
#define _GLASS_H

#include "Parallel.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include <conio.h>

class CGlass {
  // Дно
  cRectangle m_bottom;

  // Полость
  CTrapezium m_cage;

  // Левая стенка
  CParallelogram m_leftSide;

  // Правая стенка
  CParallelogram m_rightSide;

public:
  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя, bottom - Длина основания,
  * hBottom - высота основания, lessSide - длина меньшего ребра боковой стенки
  */
  CGlass(const CCountedPoint& x, const CCountedPoint& y,
         const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * Деструктор
  */
  ~CGlass(void);

  /*
   * Перемещение
   */
  void MoveToPoint(const CCountedPoint& point);

  /*
  * Смещение
  */
  void MovedXdY(double x, double y);

  /*
  * Оператор вывода в поток
  */
  friend ostream& operator << (ostream& s, CGlass& r) {
    s << "Glass: "
    << "  Bottom: " << r.m_bottom; getch();
    s  << "  Cage: " << r.m_cage; getch();
    s << "  Left side: " << r.m_leftSide; getch();
    s  << "  Right side: " << r.m_rightSide;
    getch();

    return s;
  }

};


#endif