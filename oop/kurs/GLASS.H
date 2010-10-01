// Файл: Glass.h
// Объявление класса Стакан
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _GLASS_H
#define _GLASS_H

#include "Parallel.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Ring.h"
#include <conio.h>
#include <values.h>
#include "id_obj.h"

class CGlass {
protected:
  // Дно
  CRectangle m_bottom;

  // Полость
  CTrapezium m_cage;

  // Левая стенка
  CParallelogram m_leftSide;

  // Правая стенка
  CParallelogram m_rightSide;

  // Идентификатор
  const int m_id;

public:
  int getID() const { return m_id; }

  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя, bottom - Длина основания,
  * hBottom - высота основания, lessSide - длина меньшего ребра боковой стенки
  */
  CGlass(int id, const CCountedPoint& x, const CCountedPoint& y,
         const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * Деструктор
  */
  ~CGlass(void);

  CCountedPoint getBasePoint() {
    return m_bottom.getPoint(0);
  }

  /*
  * Перемещение
  */
  virtual void MoveToPoint(const CCountedPoint& point) {
    CCountedPoint basePoint = m_bottom.getPoint(0);

    double dx = point.getX() - basePoint.getX();
    double dy = point.getY() - basePoint.getY();

    MovedXdY(dx, dy);
  };

  /*
  * Смещение
  */
  virtual void MovedXdY(double dX, double dY) {
    cout << "Glass #" << getID() << " MovedXdY(" << dX << "," << dY << ")" << endl;
    m_bottom.MovedXdY(dX, dY);
    m_cage.MovedXdY(dX, dY);
    m_leftSide.MovedXdY(dX, dY);
    m_rightSide.MovedXdY(dX, dY);
  };

  /*
  * Оператор вывода в поток
  */
  friend ostream& operator << (ostream& s, CGlass& r) {
    return r.Write(s);
  }

  virtual ostream& Write(ostream& s) {
    s << "    Glass #" << getID() << ": " << endl
    << "      Bottom: " << m_bottom;
    s << "      Cage: " << m_cage;
    s << "      Left side: " << m_leftSide;
    s << "      Right side: " << m_rightSide;
    getch();
    return s;
  }

  /*
  * Получение границ (прямоугольника, описывающего всю фигуру)
  */
  void GetBorders(double *minx, double *maxx, double *miny, double *maxy) {
    m_bottom.GetBorders(minx, maxx, miny, maxy);
    m_cage.GetBorders(minx, maxx, miny, maxy);
    m_leftSide.GetBorders(minx, maxx, miny, maxy);
    m_rightSide.GetBorders(minx, maxx, miny, maxy);
  };

};

#endif