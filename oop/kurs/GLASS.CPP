// Файл: Glass.cpp
// Релизация класса Стакан
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <iostream.h>
#include <conio.h>
#include "Glass.h"
#include "debug.h"

CGlass::CGlass(int id, const CCountedPoint& x, const CCountedPoint& y,
               const double& bottom, const double& hBottom, const double& lessSide):
    m_id(id), /* Присваиваем стакану очередной идентификатор */
    m_bottom(x, CCountedPoint(x.getX() + bottom, x.getY() + hBottom)),
    m_cage(CCountedPoint(x.getX() + lessSide, x.getY() + hBottom),
           CCountedPoint(y.getX() + lessSide, y.getY()),
           bottom - 2 * lessSide),
    m_leftSide(CCountedPoint(x.getX(), x.getY() + hBottom),
               y, lessSide),
    m_rightSide(CCountedPoint(x.getX() + bottom - lessSide, x.getY() + hBottom),
                CCountedPoint(y.getX() + bottom + 2 * (x.getX() - y.getX()) - lessSide, y.getY()),
                lessSide) {
  // VERBOSE_OUT &&
  cout << " Glass #" << getID() << " created" << endl;
}

CGlass::~CGlass(void) {
  cout << " Glass #" << getID() << " destroyed" << endl;
}

