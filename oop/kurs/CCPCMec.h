//Файл : CPСMec.h
//Проект класса "клиент - закрытый поршневой механизм"
//Автор : Монько А.О.
//Дата : 1.06.2010 Редакция : 1.0

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
        unsigned int GetID();
private:
	void Action(unsigned int _type, const CInfo& info);
};

#endif



