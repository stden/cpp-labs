// 䠩� Ring.h
// �஥�� ����� "�����"
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, ।���� 1.0.

#ifndef _RING_H
#define _RING_H

#include <iostream.h>
#include "CoPoint.h"

class CRing {

  // ������
  double m_R_B;

  double m_R_S;

  //������ �窨
  double m_x;

  //�न��� �窨
  double m_y;

 public:
  /*
  * ���������
  */
  CRing(double _x, double _y, double _R_B, double _R_S);

  /*
  * ��������� ����஢����
  */
  CRing(const CRing&);

  /*
  * ��������
  */
  ~CRing();

  /*
  * ����祭�� ࠤ���
  */
  double getR_B() const;
  double getR_S() const;

  /*
  * ��⠭���� ࠤ���
  */
  void setR_B(const double& value);
  void setR_S(const double& value);

  void GetBorders(double* minx, double* maxx, double* miny, double* maxy);


  /*
  * ���饭�� �窨
  */
  void MovedXdY(double dx, double dy);

  /*
  * ��६�饭�� � �������� ���
  */
  void MoveToPoint(double x, double y);

  double getX() const {
    return m_x;
  };
  double getY() const {
    return m_y;
  };
  void setX(double value) {
    m_x = value;
  };
  void setY(double value) {
    m_y = value;
  };

};

/*
* ������ �뢮�� � ��⮪
*/
ostream& operator << (ostream& s, const CRing& P);

#endif /* CRing_H */
