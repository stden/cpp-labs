// ����: CMessage.h
// �஥�� ����� "ᮮ�饭��"
// ����: ���뭪� �. ��. ��. 7304
// ���: 20.09.2010 �������: 1.0

#ifndef CMSG_H
#define CMSG_H

#include <iostream.h>
#include "CoPoint.h"

// ���ଠ�� � ᮮ�饭��
class CInfo {
public:
  double dx;
  double dy;
  CCountedPoint p;
  CInfo(double _dx = 0, double _dy = 0,
        const CCountedPoint& _p = CCountedPoint()) :
      dx(_dx), dy(_dy), p(_p) {}

  /*
  * ������ �뢮�� � ��⮪
  */
  friend ostream& operator << (ostream& s, const CInfo& Info) {
    s << "(dx = " << Info.dx << ", dy = " << Info.dy
    << ", Point = " << Info.p << ")" << endl;
    return s;
  }
};

// ���ࠢ����� ��।��: �ࢥ�->������, ������->�ࢥ�,
// ������->������ �१ �ࢥ�
enum Direction { Server_to_Client, Client_to_Server,
                 Client_to_Client
               };

// ⨯ ᮮ�饭��: ��⠫�� ���� - ����� ����⢨� (ACTION)
const int CONFIRMATION = 0; // ���⢥ত���� �ਥ��
const int REPORT = 1; // ���� � �믮������ �������
const int ACTION_NOCOMMAND = 2;
const int ACTION_MOVEDXDY = 3; // ��ࠫ���쭮� ��६�饭�� �� dx,dy
const int ACTION_MOVETOPOINT = 4;  // ����饭�� � ���

// ������� ����� ����饭��
class CMessage {
private:
  const int id; // id ᮮ�饭��
  int FromID; // id �� ���� ᮮ�饭��
  int ToID; // id ���� ᮮ�饭��
  CInfo Info; // ���ଠ樮���� ���� ᮮ�饭��
  int Type; // ⨯ ᮮ�饭�� (CONFIRMATION, REPORT, ACTION)
  Direction direction; // ���ࠢ����� ��।��
  static int debug;
  static int total;
  static int current;
public:
  CMessage(int _FromID, int _ToID, int _Type, const CInfo& _Info, Direction _dir);
  CMessage(const CMessage& msg);
  ~CMessage();

  const char* InterpritateType(int type) const;

  int getID() const { return id; }
  int getFromID() const { return FromID; }
  int getToID() const { return ToID; }
  int getType() const { return Type; }
  const CInfo& getInfo() const { return Info; }
  Direction getDirection() const { return direction; }

  void setFromID(int _FromID) { FromID = _FromID; };
  void setToID(int _ToID) { ToID = _ToID; };
  void setType(int _Type) { Type = _Type; };
  void setInfo(CInfo& _Info) { Info = _Info; };
  void setDirection(Direction _dir) { direction = _dir; }

  static void setDebug(int d) { debug = d; }

  static int getCurrent() { return current; }
  static int getTotal() { return total; }
  static int getDebug() { return debug; }

  /*
  * ������ �뢮�� � ��⮪
  */
  friend ostream& operator << (ostream& s, CMessage& m) {
    s << " " << m.InterpritateType(m.Type) << "-" << m.Type
    << " #" << m.id << " ";
    switch (m.direction) {
      case Server_to_Client:
        s << "S -> C" << m.ToID;
        break;
      case Client_to_Server:
        s << "C" << m.FromID << " -> S";
        break;
      case Client_to_Client:
        s << "C" << m.FromID << " -> S -> C" << m.ToID;
        break;
    }
    s << " Info=" << m.Info << " ";
    return s;
  }
};

#endif