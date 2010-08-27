// Файл: GlassC.h
// Объявление класса: Glass case - Витрина
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#ifndef _GLASSC_H
#define _GLASSC_H

#include "CoPoint.h"
#include "CoList.h"

// "Витрина" имеет форму прямоугольника
class CGlassCase
{
private :
  // Нижний левый и верхний правый угол витрины
  CCountedPoint m_leftBottom,m_rightTop;

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
  int InGlassCase(double minx,double maxx,double miny,double maxy){
    return (m_leftBottom.getX()<=minx) && (m_leftBottom.getY()<=miny) &&
     (m_rightTop.getX()>=maxx) && (m_rightTop.getY()>=maxy);
  };

friend ostream& operator << (ostream& s, CGlassCase& r)
{
  s << "  " << "Витрина: " << r.m_leftBottom << " " << r.m_rightTop << endl;
  return s;
}

};


#endif