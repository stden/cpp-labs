// Файл: Ring.cpp
// Релизация класса "Кольцо"
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#define _USE_MATH_DEFINES

#include <math.h>
#include "Ring.h"

CRing::CRing(double x,double y,double R) : CCountedPoint(x,y), m_R(R)
{
  cout << "          Ring number " << m_count << " created" << endl;
  m_count++;
}

CRing::CRing(const CRing& ring)
{
  m_id=++countall;
  m_x=ring.m_x;
  m_y=ring.m_y;
  m_R=ring.m_R;
  cout << "          Ring number " << m_count << " copyed" << endl;
  m_count++;
}

CRing::~CRing()
{
  m_count--;
  cout << "          Ring destroyed (remain " << m_count << ")"  << endl;
}


double CRing::getR() const
{
  return m_R;
}

void CRing::setR(const double& value)
{
  m_R = value;
}

ostream& operator << (ostream& s, const CRing& P)
{
  s << "Ring: " << P.getX() << ", " << P.getY() << "  R(big)  = " << P.getR() << "  R(small) = " << P.getR()*0.9;
  return (s);
}

