// ����: GlassR.cpp
// �������� �����: �⠪�� � ����殬
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, �������: 1.0

#include <iostream.h>
#include <conio.h>
#include "GlassR.h"


// x - ���न���� ������� ������ 㣫� �᭮����� �⠪���
// y - ���न���� ������ ���孥�� 㣫� �⠪��� (�࠯�樨)
// bottom - �ਭ� �᭮�����
// hBottom - ���� �᭮�����
// lessSide - ⮫騭� �⥭�� (������ ��஭� ��ࠫ�����ࠬ��)
CGlassR::CGlassR(int id, const CCountedPoint& x, const CCountedPoint& y,
                 const double& bottom, const double& hBottom, const double& lessSide):
  // ������ �⠪�� ��� �����
  CGlass(id, x, y, bottom, hBottom, lessSide),
  // � ������塞 �����
  // ����� "�����" ᮢ������ � �窮� ����祭�� ���������� "������ �⠪���"
  // X-���न��� 業��
  m_ring(x.getX() + bottom / 2.0,
         0, // Y-���न��� �㤥� ������ ������� (��᪮��� �� ᫮��� ���᫨��)
         // ������� ���譥� ���㦭��� "�����" ࠢ�� �������� �����
         // "�࠯�樨" ��ࠧ��饩 "������� �⠪���"
         // �� ��।�� � ��������� ࠤ��� ���譥� ���㦭���, ����� ࠢ�� �⢥��
         (y.getY() - x.getY() - hBottom) / 4.0,
         0.9 * (y.getY() - x.getY() - hBottom) / 4.0) {
  // ����塞 ����� ����讣� ��㣮�쭨��
  double HBig = y.getY() - x.getY() - hBottom;
  // ����塞 �᭮����� ����讣� ��㣮�쭨��
  double LBig = x.getX() - y.getX() + bottom;
  // �᭮����� �����쪮�� ��㣮�쭨��
  double LSmall = bottom / 2;
  // ���� �����쪮�� ��㣮�쭨��
  double HSmall = HBig / LBig * LSmall; // ��᪮��� ��㣮�쭨�� �������
  // � �⮣� ���न��� Y 業�஢ ���㦭��⥩ �㤥�
  double Y = x.getY() + hBottom + HSmall;

  m_ring.setY(Y);

  cout << " Glass with ring created" << endl;
}

void CGlassR::MoveToPoint(const CCountedPoint& point) {
  // ����砥� ⥪�騥 ���न���� ������ ������� 㣫� �᭮�����
  CCountedPoint basePoint = m_bottom.getPoint(0);

  // ����塞 ��᪮�쪮 ���� ᤢ����� 䨣���, �⮡� ����� ������ �窠
  // ��⠫� � ������� ���न����
  double dx = point.getX() - basePoint.getX();
  double dy = point.getY() - basePoint.getY();

  // ������� �� ���᫥��� ����� (dx; dy)
  MovedXdY(dx, dy);
}

void CGlassR::MovedXdY(double x, double y) {
  cout << "CGlassR::MovedXdY(" << x << "," << y << ")" << endl;
  // ������� ��᫥����⥫쭮 �� "���窨" �⠪���
  m_bottom.MovedXdY(x, y); // �᭮�����
  m_cage.MovedXdY(x, y); // ������� �⠪���
  m_leftSide.MovedXdY(x, y); // ����� �⥭��
  m_rightSide.MovedXdY(x, y); // �ࠢ�� �⥭��
  m_ring.MovedXdY(x, y); // �����
}

CGlassR::~CGlassR(void) {
  cout << " CGlassR destroyed" << endl;
}

