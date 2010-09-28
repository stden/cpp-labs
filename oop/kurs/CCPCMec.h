// Файл: CPСMec.h
// Проект класса "клиент - стакан с кольцом"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#ifndef CCPCMEC_H
#define CCPCMEC_H

#include <iostream.h>
#include "CPoint.h"
#include "CPCMec.h"
#include "CClient.h"


class CClientClosedPistonMechanism : public CClosedPistonMechanism, public CClient {
public:
  CClientClosedPistonMechanism(const CClosedPistonMechanism& mec);
        CClientClosedPistonMechanism(CPoint,double,double,double,double,double,double,double,double,double,double);
        CClientClosedPistonMechanism(double,double,double,double,double,double,double,double,double,double,double,double);
        CClientClosedPistonMechanism();

        virtual ~CClientClosedPistonMechanism();
  void Move(double dx, double dy);
  void SetP1(CPoint P0);
        virtual int MovePiston (double);
  void Print() const;
        int getID();
private:
  void Action(int _type, const CInfo& info);
};

#endif



