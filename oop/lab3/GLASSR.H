// Файл: GlassR.h
// Объявление класса: Стакан с кольцом
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _GLASSR_H
#define _GLASSR_H

#include "Parallel.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Ring.h"
#include "Glass.h"
#include "values.h"
#include <conio.h>

// "Тонкий стакан с кольцом"
class CGlassR : public CGlass { // Используется простое наследование
  // Кольцо - две концентрические окружности в "полости стакана"
  CRing m_ring;

 public:
  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя, bottom - Длина основания,
  * hBottom - высота основания, lessSide - длина меньшего ребра боковой стенки
  */
  CGlassR(const CCountedPoint& x, const CCountedPoint& y,
          const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * Деструктор
  */
  ~CGlassR(void);

  /*
  * Перемещение
  */
  virtual void MoveToPoint(const CCountedPoint& point);

  /*
  * Смещение
  */
  virtual void MovedXdY(double x, double y);

  /*
  * Получение границ (прямоугольника, описывающего всю фигуру)
  */
  void GetBorders(double* minx, double* maxx, double* miny, double* maxy) {
    *minx = MAXDOUBLE;
    *maxx = MINDOUBLE;
    *miny = MAXDOUBLE;
    *maxy = MINDOUBLE;
    m_bottom.GetBorders(minx, maxx, miny, maxy);
    m_cage.GetBorders(minx, maxx, miny, maxy);
    m_leftSide.GetBorders(minx, maxx, miny, maxy);
    m_rightSide.GetBorders(minx, maxx, miny, maxy);
    m_ring.GetBorders(minx, maxx, miny, maxy);
    //    cout << "GlassR borders: minx " << minx << " " << " "
  };

  /*
  * Оператор вывода в поток
  */
  friend ostream& operator << (ostream& s, CGlassR& r) {
    return r.Write(s);
  }

  virtual ostream& Write(ostream& s) {
    s << "    Glass with Ring #" << getID() << ": " << endl
      << "      Bottom: " << m_bottom;
    s << "      Cage: " << m_cage;
    s << "      Left side: " << m_leftSide;
    s << "      Right side: " << m_rightSide;
    s << "      Ring : " << m_ring;
    getch();
    return s;
  }

};


#endif