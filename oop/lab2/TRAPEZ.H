// ����: Rectangle.h
// ���������� ������ �������� (�����������)
// �����: ������� �.
// ����: 16.05.10, ��������: 1.0
#ifndef _TRAPEZ_H_
#define _TRAPEZ_H_


#include "CoPoint.h"
#include "CoList.h"

class CTrapezium  {
 private:
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
  * x - ����� ������ �����, y - ����� ������� �����, l - ����� �������� ���������
  */
  CTrapezium(const CCountedPoint& x, const CCountedPoint& y, const double& l);

  ~CTrapezium(void);


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


  friend ostream& operator << (ostream& s, CTrapezium& r) {
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

