// Файл: Ring.cpp
// Релизация класса "Кольцо"
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#define _USE_MATH_DEFINES

#include <math.h>
#include <assert.h>
#include "Ring.h"

CRing::CRing(double x, double y, double R_B, double R_S) :
  m_x(x), m_y(y), m_R_B(R_B), m_R_S(R_S) {
  cout << "          Ring created" << endl;
}

CRing::CRing(const CRing& ring) {
  m_x = ring.m_x;
  m_y = ring.m_y;
  m_R_B = ring.m_R_B;
  m_R_S = ring.m_R_S;
}

CRing::~CRing() { }


double CRing::getR_B() const {
  return m_R_B;
}

double CRing::getR_S() const {
  return m_R_S;
}

void CRing::setR_B(const double& value) {
  assert(value >= 0);
  m_R_B = value;
}

void CRing::setR_S(const double& value) {
  assert(value >= 0);
  m_R_S = value;
}

ostream& operator << (ostream& s, const CRing& P) {
  // Ширина кольца равняется одной десятой диаметра внешней окружности "кольца"
  s << "Ring: " << P.getX() << ", " << P.getY() << "  R(big)  = " << P.getR_B()
    << "  R(small) = " << P.getR_S() << endl;

  return (s);
}

void CRing :: GetBorders(double* minx, double* maxx, double* miny, double* maxy) {
  // "Описывающий прямоугольник" для окружности - это квадрат
  // центр которого в центре окружности, а стороны отстоят на радиус во все стороны
  if (m_x - m_R_B < *minx) *minx = m_x - m_R_B;

  if (m_x + m_R_B > *maxx) *maxx = m_x + m_R_B;

  if (m_y - m_R_B < *miny) *miny = m_y - m_R_B;

  if (m_y + m_R_B > *maxy) *maxy = m_y + m_R_B;

  // На всякий случай проверям что минимальные координаты меньше максимальных
  // т.е. что условия выше расставлены верно
  assert(*minx < *maxx);
  assert(*miny < *maxy);
}

void CRing :: MoveToPoint(double x, double y) {
  m_x = x;
  m_y = y;
}

void CRing::MovedXdY(double x, double y) {
  // cout << "move " << m_x << " " << m_y << " -> " << x << " " << y << endl;
  m_x += x;
  m_y += y;
}

