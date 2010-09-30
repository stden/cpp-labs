// Файл: GlassC.h
// Объявление класса: Glass case - Витрина
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#ifndef _GLASSC_H
#define _GLASSC_H

#include "CoPoint.h"
#include "CoList.h"
#include <assert.h>

// "Витрина" имеет форму прямоугольника
class CGlassCase {
private :
  // Нижний левый и верхний правый угол витрины
  CCountedPoint m_leftBottom, m_rightTop;

  double m_Height; // Высота витрины
  double m_Width; // Ширина витрины

public:

  /*
  * Конструктор
  * leftBottom - левая нижняя точка, rightTop - правая верхняя
  */
  CGlassCase(const CCountedPoint& leftBottom, const CCountedPoint& rightTop);

  /*
  * Деструктор
  */
  ~CGlassCase();

  /*
  * Проверка, помещается ли прямоугольник с заданными координатами внутри витрины
  */
  int InGlassCase(double minx, double maxx, double miny, double maxy) {
    return (m_leftBottom.getX() <= minx) && (m_leftBottom.getY() <= miny) &&
           (m_rightTop.getX() >= maxx) && (m_rightTop.getY() >= maxy);
  };

  /*
  * Получить высоту витрины
  */
  double getHeight() {
    return m_rightTop.getY() - m_leftBottom.getY();
    // return m_Height;
  }

  /*
  * Установить высоту витрины
  */
  void setHeight(double value) {
    m_Height = value;
    m_rightTop.setY(m_leftBottom.getY() + value);
  }

  /*
  * Получить ширину витрины
  */
  double getWidth() {
    return m_rightTop.getX() - m_leftBottom.getX();
    // return m_Width;
  }

  /*
  * Установить ширину витрины
  */
  void setWidth(double value) {
    m_Width = value;
    m_rightTop.setX(m_leftBottom.getX() + value);
  }

  /*
  * Проверка инварианта
  */
  void checkInv() {
    assert(m_rightTop.getX() - m_leftBottom.getX() == m_Width);
    assert(m_rightTop.getX() - m_leftBottom.getX() == getWidth());
    assert(m_rightTop.getY() - m_leftBottom.getY() == m_Height);
    assert(m_rightTop.getY() - m_leftBottom.getY() == getHeight());
  }

  /*
  * Перемещение левого нижнего угла в точку
  */
  virtual void MoveToPoint(const CCountedPoint& point) {
    CCountedPoint basePoint = m_leftBottom;

    double dx = point.getX() - basePoint.getX();
    double dy = point.getY() - basePoint.getY();

    MovedXdY(dx, dy);
  };

  /*
  * Смещение на dX dY
  */
  virtual void MovedXdY(double dX, double dY) {
    checkInv();
    m_rightTop.MovedXdY(dX, dY);
    m_leftBottom.MovedXdY(dX, dY);
    checkInv();
  };

  /*
  * Вывод параметров витрины в поток
  */
  friend ostream& operator << (ostream& s, CGlassCase& r) {
    s << "  " << "Витрина: " << r.m_leftBottom << " " << r.m_rightTop
    << " Высота " << r.getHeight() << "  Ширина " << r.getWidth() << endl;
    return s;
  }
};


#endif