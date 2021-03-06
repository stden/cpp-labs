// ����: CGlass.h
// ������� ����� �⠪�� ��� ������
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _CLIENT_GLASS_H
#define _CLIENT_GLASS_H

#include "Parallel.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Ring.h"
#include <conio.h>
#include <values.h>
#include "glass.h"
#include "cclient.h"

class CClientGlass : public CClient, public CGlass {
 public:
  int getID() const {
    return CClient::getID();
  };

  /*
  * ���������
  * x - ����� ������ �窠, y - ����� ������, bottom - ����� �᭮�����,
  * hBottom - ���� �᭮�����, lessSide - ����� ����襣� ॡ� ������� �⥭��
  */
  CClientGlass(int id,
               const CCountedPoint& x, const CCountedPoint& y,
               const double& bottom, const double& hBottom, const double& lessSide) :
    CGlass(id, x, y, bottom, hBottom, lessSide),
    CClient(id) {
    // VERBOSE_OUT &&
    cout << "Client Glass #" << CClient::getID() << endl;
  };

  /*
  * ��������
  */
  ~CClientGlass(void) {};

  /*
  * ��६�饭��
  */
  virtual void MoveToPoint(const CCountedPoint& point) {
    CClient :: SendMessage(ACTION_MOVETOPOINT,
                           CInfo(0, 0, point), 1);
  };

  /*
  * ���饭��
  */
  virtual void MovedXdY(double dX, double dY) {
    CClient :: SendMessage(ACTION_MOVEDXDY,
                           CInfo(dX, dY), 1);
  };

  virtual void Action(int _type, const CInfo& info) {
    switch (_type) {
      case ACTION_MOVETOPOINT:
        cout << "Client is handling action with code = " << _type << "(Move To Point)" << endl
             << "And parametrs = " << info << endl;
        CGlass :: MoveToPoint(info.p);
        break;

      case ACTION_MOVEDXDY:
        cout << "Client is handling action with code = " << _type << "(Moving by dx, dy)" << endl
             << "And parametrs = " << info << endl;
        CGlass :: MovedXdY(info.dx, info.dy);
        break;

      default:
        cout << "Client could not handle action with code = " << _type << endl
             << "case of unknown code " << endl << endl;
        break;
    }
  }


  /*
  * ������ �뢮�� � ��⮪
  */
  friend ostream& operator << (ostream& s, CClientGlass& r) {
    return r.Write(s);
  }

  virtual ostream& Write(ostream& s) {
    s << "    Client Glass #" << CGlass::getID() << ": " << endl
      << "      Bottom: " << m_bottom;
    s << "      Cage: " << m_cage;
    s << "      Left side: " << m_leftSide;
    s << "      Right side: " << m_rightSide;
    getch();
    return s;
  }
};

#endif