// ����: GlassR.h
// ������� �����: �⠪�� � ����殬
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _GLASSR_H
#define _GLASSR_H

#include "Parallel.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Ring.h"
#include "Glass.h"
#include "values.h"
#include "debug.h"
#include <conio.h>

// "������ �⠪�� � ����殬"
class CGlassR : public CGlass { // �ᯮ������ ���⮥ ��᫥�������
 protected:
  // ����� - ��� ���業���᪨� ���㦭��� � "������ �⠪���"
  CRing m_ring;

 public:
  /*
  * ���������
  * x - ����� ������ �窠, y - ����� ������, bottom - ����� �᭮�����,
  * hBottom - ���� �᭮�����, lessSide - ����� ����襣� ॡ� ������� �⥭��
  */
  CGlassR(int id, const CCountedPoint& x, const CCountedPoint& y,
          const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * ��������
  */
  ~CGlassR(void);

  /*
  * ��६�饭��
  */
  virtual void MoveToPoint(const CCountedPoint& point);

  /*
  * ���饭��
  */
  virtual void MovedXdY(double x, double y);

  /*
  * ����祭�� �࠭�� (��אַ㣮�쭨��, ����뢠�饣� ��� 䨣���)
  */
  void GetBorders(double* minx, double* maxx, double* miny, double* maxy) {
    *minx = MAXDOUBLE;
    *maxx = MINDOUBLE;
    *miny = MAXDOUBLE;
    *maxy = MINDOUBLE;
    m_bottom.GetBorders(minx, maxx, miny, maxy);
    m_cage.GetBorders(minx, maxx, miny, maxy);
    m_leftSide.GetBorders(minx, maxx, miny, maxy);
    m_rightSide.GetBorders(minx, maxx, miny, maxy);
    m_ring.GetBorders(minx, maxx, miny, maxy);
    cout << "GlassR borders: x [" << minx << ".." << maxx << "] " << "y [" << miny << ".." << maxy << "] " << endl;
  };

  /*
  * ������ �뢮�� � ��⮪
  */
  friend ostream& operator << (ostream& s, CGlassR& r) {
    return r.Write(s);
  }

  virtual ostream& Write(ostream& s) {
    s << "    Glass with Ring #" << getID() << ": " << endl
      << "      Bottom: " << m_bottom;
    s << "      Cage: " << m_cage;
    s << "      Left side: " << m_leftSide;
    s << "      Right side: " << m_rightSide;
    s << "      Ring : " << m_ring;
    getch();
    return s;
  }

};


#endif