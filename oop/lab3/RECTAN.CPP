// Файл: Rectan.cpp
// Релизация класса Прямоугольник
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.1

#include <iostream.h>
#include "Rectan.h"

CRectangle::CRectangle(const CCountedPoint& x,const CCountedPoint& y)
{
  m_list.insert(x);
  m_list.insert(CCountedPoint(x.getX(), y.getY()));
  m_list.insert(y);
  m_list.insert(CCountedPoint(y.getX(), x.getY()));
  m_list.goFirst();
  cout << "        Rectangle created" << endl;
}

CRectangle::~CRectangle()
{
  cout << "        Rectangle destroyed" << endl;
}

void CRectangle :: MovedXdY (double dx, double dy) {
  // cout << "CPointSet::MovedXdY(" << x << "," << y << ")" << endl;
  m_list.goFirst();
  do{
    m_list.getElem().getValue().MovedXdY(dx, dy);
  }while(m_list.goNext());
}

void CRectangle :: MoveToPoint (const CCountedPoint& P) {
    m_list.goFirst();

    double dx = P.getX() - m_list.getElem().getValue().getX();
    double dy = P.getY() - m_list.getElem().getValue().getY();

    MovedXdY(dx, dy);
}


void CRectangle :: GetBorders( double *minx,double *maxx,double *miny,double *maxy ){
  m_list.goFirst();
  do{
    double x = m_list.getElem().getValue().getX();
    double y = m_list.getElem().getValue().getY();
    if (x < *minx) *minx = x; 
    if (x > *maxx) *maxx = x;
    if (y < *miny) *miny = y;
    if (y > *maxy) *maxy = y;
  }while(m_list.goNext());
}

ostream& operator << (ostream& s, CRectangle& r)
{
  s << "  " << "Rectangle" << ": " << endl;
  r.getPoints().goFirst();
  do{
    s << "    (" << r.getPoints().getElem().getValue() << "), " << endl;
  }while(r.getPoints().goNext());
  s << endl;
  return s;
}


const CCountedPoint& CRectangle :: getPoint (int index) {
     m_list.goFirst();

    for(index;index>1;index--)
      m_list.goNext();

    return m_list.getElem().getValue();
}


