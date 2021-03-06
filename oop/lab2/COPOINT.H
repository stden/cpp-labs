// 䠩� Point
// �஥�� ����� "�窠"
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, ।���� 1.0.

#ifndef _POINT_H
#define _POINT_H

#include <iostream.h>

class CCountedPoint {
  //������ �窨
  double m_x;

  //�न��� �窨
  double m_y;

  //������⢮ ��������஢ ����� ��窠
  static int m_count;

  //��饥 ������⢮ ᮧ������ �����-���� ��������஢
  static int countall;

  //�����䨪���
  int m_id;

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
  * ������� ������⢮ ��������஢ �����
  */
  static int getCount() {
    return m_count;
  }

  /*
  * ���饭�� �窨
  */
  void move(double dx, double dy);


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

#endif /* CCountedPoint_H */