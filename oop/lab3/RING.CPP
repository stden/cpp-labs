// Файл: Ring.cpp
// Релизация класса "Кольцо"
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#define _USE_MATH_DEFINES

#include <math.h>
#include <assert.h>
#include "Ring.h"

CRing::CRing(double x,double y,double R) : CCountedPoint(x,y), m_R(R)
{
  cout << "          Ring created" << endl;
  m_count++;
}

CRing::CRing(const CRing& ring)
{
  m_id=++countall;
  m_x=ring.m_x;
  m_y=ring.m_y;
  m_R=ring.m_R;
  m_count++;
}

CRing::~CRing()
{
  m_count--;
}


double CRing::getR() const
{
  return m_R;
}

void CRing::setR(const double& value)
{
  assert( value >= 0 );
  m_R = value;
}

ostream& operator << (ostream& s, const CRing& P)
{
  s << "Ring: " << P.getX() << ", " << P.getY() << "  R(big)  = " << P.getR() << "  R(small) = " << P.getR()*0.9 << endl;
  return (s);
}

void CRing :: GetBorders( double *minx,double *maxx,double *miny,double *maxy ){
  if ( m_x-m_R < *minx) *minx = m_x-m_R;
  if ( m_x+m_R > *maxx) *maxx = m_x+m_R;
  if ( m_y-m_R < *miny) *miny = m_y-m_R;
  if ( m_y+m_R > *maxy) *maxy = m_y+m_R;
  assert( *minx < *maxx );
  assert( *miny < *maxy );
}


