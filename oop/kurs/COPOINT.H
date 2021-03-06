// ����: CoPoint.h
// �஥�� ����� "��窠"
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, ।���� 1.0.

#ifndef _COPOINT_H
#define _COPOINT_H

#include <iostream.h>

class CCountedPoint {
 protected:
  //������ �窨
  double m_x;

  //�न��� �窨
  double m_y;

 public:

  /*
  * ���������
  */
  CCountedPoint(double _x = 0, double _y = 0);

  /*
  * ��������� ����஢����
  */
  CCountedPoint(const CCountedPoint&);


  /*
  * ���饭�� �窨
  */
  void MovedXdY(double dx, double dy);


  /*
  * ������ �窨 �⭮�⥫쭮 �窨
  */
  void round(const CCountedPoint&, int);

  /*
  * ����祭�� ������� �窨
  */
  double getX() const;

  /*
  * ����祭�� �न���� �窨
  */
  double getY() const;

  /*
  * ��⠭���� ������� �窨
  */
  void setX(const double& value);

  /*
  * ��⠭���� �न���� �窨
  */
  void setY(const double& value);

  /*
  * ��������
  */
  ~CCountedPoint();
};

/*
* ������ �뢮�� � ��⮪
*/
ostream& operator << (ostream& s, const CCountedPoint& P);

#endif