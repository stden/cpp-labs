// Файл: Glass.h
// Объявление класса Стакан
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

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

class CClientGlass : public CClient, public CGlass {
public:
  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя, bottom - Длина основания,
  * hBottom - высота основания, lessSide - длина меньшего ребра боковой стенки
  */
  CClientGlass(const CCountedPoint& x, const CCountedPoint& y,
               const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * Деструктор
  */
  ~CClientGlass(void);

  /*
  * Перемещение
  */
  virtual void MoveToPoint(const CCountedPoint& point) {
    CClient :: SendMessage(ACTION, CInfo(cmd_MoveToPoint, dx, dy), getServer()->getID());
  };

  /*
  * Смещение
  */
  virtual void MovedXdY(double dX, double dY) {
    CClient :: SendMessage(ACTION, CInfo(cmd_MovedXdY, dX, dY), getServer()->getID());
  };

  void Action(int _type, const CInfo& info) {
    switch (info.command) {
      case cmd_MoveToPoint:
        cout << "Client is handling action with code = " << info.command << "(Setting P1)" << endl
             << "And parametrs = ";info.Print(); cout << endl;
        CGlass :: MoveToPoint(info.p);
        break;
      case cmd_MoveddXdY:
        cout << "Client is handling action with code = " << info.command << "(Moving by dx, dy)" << endl
             << "And parametrs = ";info.Print(); cout << endl;
        CGlass :: Move(info.dx, info.dy);
        break;
      default:
        cout << "Client could not handle action with code = " << info.command << endl
             << "case of unknown code " << endl << endl;
        break;
    }
  }


  /*
  * Оператор вывода в поток
  */
  friend ostream& operator << (ostream& s, CGlass& r) {
    return r.Write(s);
  }

  virtual ostream& Write(ostream& s) {
    s << "    Client Glass #" << getID() << ": " << endl
    << "      Bottom: " << m_bottom;
    s << "      Cage: " << m_cage;
    s << "      Left side: " << m_leftSide;
    s << "      Right side: " << m_rightSide;
    getch();
    return s;
  }
};

#endif