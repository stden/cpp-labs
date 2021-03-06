// ����: Rectangle.h
// ����� ����� �����
// �����: ������� �.
// ����: 16.05.10, ��������: 1.0

#ifndef _POINTSET_H
#define _POINTSET_H

#include <string.h>
#include "CoList.h"
#include "CoPoint.h"
#include "Constant.h"

template<class T>
class CPointSet {
 protected:
  //������ �����, ���������� �������������
  CList<CCountedPoint> m_list;

  //���������� ����������� ������ ��������
  static int countreal;

  //����� ���������� ��������� �����-���� �����������
  static int countall;

  //�������������
  int m_id;

  //��� ������ �����
  char* m_name;
 public:

  CPointSet(): m_id(countall++) {
    countreal++;
  }

  /*
  * ����������� �����������
  */
  CPointSet(const CPointSet& s) {
    countreal++;
    m_list = s.m_list;
    m_name = s.m_name;
  }

  ~CPointSet() {
    countreal--;
  }

  /*
  * �������� ���������� ����������� ������
  */
  static int getCount() {
    return countreal;
  }

  /*
  * ����������� ������ �����
  */
  void MoveToPoint(const CCountedPoint& point) {
    m_list.goFirst();

    double dx = point.getX() - m_list.getElem().getValue().getX();
    double dy = point.getY() - m_list.getElem().getValue().getY();

    MovedXdY(dx, dy);
  }

  /*
  * �������� ������ �����
  */
  void MovedXdY(double x, double y) {
    // cout << "CPointSet::MovedXdY(" << x << "," << y << ")" << endl;
    m_list.goFirst();

    do {
      m_list.getElem().getValue().move(x, y);
    } while (m_list.goNext());
  }

  /*
  * ��������� ����� �� ������
  */
  CCountedPoint& getPoint(int num) {
    m_list.goFirst();

    for (num; num > 1; num--)
      m_list.goNext();

    return m_list.getElem().getValue();
  }

  /*
  * �������� ������ � �����
  */
  //  template<class C>
  friend ostream& operator<< (ostream& s, CPointSet<T>& P);
};

template<class C>
ostream& operator << (ostream& s, CPointSet<C>& r) {
  s << "  " << r.m_name << ": " << endl;
  r.m_list.goFirst();

  do {
    s << "    (" << r.m_list.getElem().getValue() << "), " << endl;
  } while (r.m_list.goNext());

  s << "    (" << r.m_list.getElem().getValue() << ")";
  s << endl;

  return (s);
}

#endif