// ����: Ring.cpp
// �������� ����� "�����"
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.1

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
  // ��ਭ� ����� ࠢ����� ����� ����⮩ ������� ���譥� ���㦭��� "�����"
  s << "Ring: " << P.getX() << ", " << P.getY() << "  R(big)  = " << P.getR_B()
    << "  R(small) = " << P.getR_S() << endl;

  return (s);
}

void CRing :: GetBorders(double* minx, double* maxx, double* miny, double* maxy) {
  // "����뢠�騩 ��אַ㣮�쭨�" ��� ���㦭��� - �� ������
  // 業�� ���ண� � 業�� ���㦭���, � ��஭� ������ �� ࠤ��� �� �� ��஭�
  if (m_x - m_R_B < *minx) *minx = m_x - m_R_B;

  if (m_x + m_R_B > *maxx) *maxx = m_x + m_R_B;

  if (m_y - m_R_B < *miny) *miny = m_y - m_R_B;

  if (m_y + m_R_B > *maxy) *maxy = m_y + m_R_B;

  // �� ��直� ��砩 �஢��� �� ��������� ���न���� ����� ���ᨬ�����
  // �.�. �� �᫮��� ��� ���⠢���� ��୮
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

