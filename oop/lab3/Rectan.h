// ����: Rectan.h
// ������� ����� ��אַ㣮�쭨�
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.1

#ifndef _RECTAN_H
#define _RECTAN_H

#include "CoPoint.h"
#include "CoList.h"

class CRectangle
{
private :
CList<CCountedPoint> m_list;

//������⢮ ��������஢ ����� ��אַ㣮�쭨�
  static int countreal;

  //��饥 ������⢮ ᮧ������ �����-���� ��������஢
  static int countall;

  //�����䨪���
  int m_id;

public:

  /*
  * ���������
  * x - ����� ������ �窠, y - �ࠢ�� ������
  */
  CRectangle(const CCountedPoint& x, const CCountedPoint& y);

  void MovedXdY (double dx, double dy);
  void MoveToPoint (const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints () { return m_list; }
  const CCountedPoint& getPoint (int index);

  static int getCount() { return countreal; }

  int getId () { return m_id; }

  void GetBorders( double *minx,double *maxx,double *miny,double *maxy );

  /*
  * ��������
  */
  ~CRectangle();

  friend ostream& operator << (ostream& s, CRectangle& r);

};


#endif