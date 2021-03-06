// ����: CoPoint.cpp
// �������� ����� ��窠
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.1

#define _USE_MATH_DEFINES

#include <math.h>
#include "CoPoint.h"

CCountedPoint::CCountedPoint(double x, double y) : m_x(x), m_y(y) {
  // cout << "          Point number " << m_count << " created" << endl;
}

CCountedPoint::CCountedPoint(const CCountedPoint& point) {
  m_x = point.m_x;
  m_y = point.m_y;
  // cout << "          Point number " << m_count << " copyed" << endl;
}

CCountedPoint::~CCountedPoint() {
  // cout << "          Point destroyed (remain " << m_count << ")"  << endl;
}

void CCountedPoint::MovedXdY(double x, double y) {
  // cout << "move " << m_x << " " << m_y << " -> " << x << " " << y << endl;
  m_x += x;
  m_y += y;
}

void CCountedPoint::round(const CCountedPoint& point, int angle) {
  double tmpX = point.getX();
  double tmpY = point.getY();

  tmpX = m_x - tmpX;
  tmpY = m_y - tmpY;
  double R = sqrt(tmpX * tmpX + tmpY * tmpY);
  double f = 90;

  if (tmpX != 0)
    f = atan2(tmpY, tmpX) * 180 / M_PI;

  f = f + angle;
  tmpY = R * sin(f * M_PI / 180);
  tmpX = R * cos(f * M_PI / 180);
  m_x = point.getX();
  m_y = point.getY();
  m_x = m_x + tmpX;
  m_y = m_y + tmpY;
}

double CCountedPoint::getX() const {
  return m_x;
}

double CCountedPoint::getY() const {
  return m_y;
}

void CCountedPoint::setX(const double& value) {
  m_x = value;
}

void CCountedPoint::setY(const double& value) {
  m_y = value;
}

ostream& operator << (ostream& s, const CCountedPoint& P) {
  s << "(" << P.getX() << ";" << P.getY() << ") ";
  return s;
}

