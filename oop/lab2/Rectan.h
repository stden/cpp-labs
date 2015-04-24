// ����: Rectangle.h
// ���������� ������ �������������
// �����: ������� �.
// ����: 16.05.10, ��������: 1.1

#ifndef _RECTAN_H
#define _RECTAN_H

#include "CoPoint.h"
#include "CoList.h"

class cRectangle {
 private :
  CList<CCountedPoint> m_list;

  //���������� ����������� ������ �������������
  static int countreal;

  //����� ���������� ��������� �����-���� �����������
  static int countall;

  //�������������
  int m_id;

 public:

  /*
  * �����������
  * x - ����� ������ �����, y - ������ �������
  */
  cRectangle(const CCountedPoint& x, const CCountedPoint& y);

  void MovedXdY(double dx, double dy);
  void MoveToPoint(const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints() {
    return m_list;
  }
  const CCountedPoint& getPoint(int index);

  static int getCount() {
    return countreal;
  }

  int getId() {
    return m_id;
  }



  /*
  * ����������
  */
  ~cRectangle();

  friend ostream& operator << (ostream& s, cRectangle& r) {
    s << "  " << "Rectangle" << ": " << endl;
    r.getPoints().goFirst();

    do {
      s << "    (" << r.getPoints().getElem().getValue() << "), " << endl;
    } while (r.getPoints().goNext());

    s << "    (" << r.getPoints().getElem().getValue() << ")";
    s << endl;

    return (s);
  }

};


#endif