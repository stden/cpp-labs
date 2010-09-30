// Файл: CGlassR.h
// Объявление класса Стакан с кольцом как клиент
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _CLIENT_GLASSR_H
#define _CLIENT_GLASSR_H

#include <conio.h>
#include <values.h>
#include "GlassR.h"

class CClientGlassR : public CClient, public CGlassR {
public:
  int getID() const { return CClient::getID(); };

  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя, bottom - Длина основания,
  * hBottom - высота основания, lessSide - длина меньшего ребра боковой стенки
  */
  CClientGlassR(const CCountedPoint& x, const CCountedPoint& y,
                const double& bottom, const double& hBottom, const double& lessSide) :
      CGlassR(x, y, bottom, hBottom, lessSide) {
    VERBOSE_OUT && cout << "Client Glass with ring #" << CClient::getID() << endl;
  };

  /*
  * Деструктор
  */
  ~CClientGlassR(void) {};

  /*
  * Перемещение
  */
  virtual void MoveToPoint(const CCountedPoint& point) {
    CClient :: SendMessage(ACTION_MOVETOPOINT,
                           CInfo(0, 0, point), CClient::getID());
  };

  /*
  * Смещение
  */
  virtual void MovedXdY(double dX, double dY) {
    CClient :: SendMessage(ACTION_MOVEDXDY,
                           CInfo(dX, dY), CClient::getID());
  };

  void Action(int _type, const CInfo& info) {
    switch (_type) {
      case ACTION_MOVETOPOINT:
        cout << "Client is handling action with code = " << _type << "(Setting P1)" << endl
             << "And parametrs = " << info << endl;
        CGlassR :: MoveToPoint(info.p);
        break;
      case ACTION_MOVEDXDY:
        cout << "Client is handling action with code = " << _type << "(Moving by dx, dy)" << endl
             << "And parametrs = " << info << endl;
        CGlassR :: MovedXdY(info.dx, info.dy);
        break;
      default:
        cout << "Client could not handle action with code = " << _type << endl
             << "case of unknown code " << endl << endl;
        break;
    }
  }

  /*
  * Оператор вывода в поток
  */
  friend ostream& operator << (ostream& s, CClientGlassR& r) {
    return r.Write(s);
  }

  virtual ostream& Write(ostream& s) {
    s << "    Client Glass with Ring #" << CClient::getID() << ": " << endl
    << "      Bottom: " << m_bottom;
    s << "      Cage: " << m_cage;
    s << "      Left side: " << m_leftSide;
    s << "      Right side: " << m_rightSide;
    s << "      Ring: " << m_ring;
    getch();
    return s;
  }
};

#endif