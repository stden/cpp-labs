//Файл : CStand.h
//Проект класса "стенд"
//Автор : Монько А.О.
//Дата : 22.05.2010 Редакция : 1.0

#ifndef CSTAND_H
#define CSTAND_H

#include <iostream.h>
#include "CPoint.h"
#include "CList.h"
#include "CTria.h"


class CStand {
protected:
  CircleList<CPoint> MainPoints;
  CTriangle Stand;
private:
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
virtual  void  AddPoints ();
public:

				/*Конструкторы*/
	//-------------------------------------------------
     	CStand(CPoint _P1,double _P1P2,CPoint _P3);
      	CStand(); // Constructor without parametrs
	//-------------------------------------------------

				/*Деструктор*/
	//-------------------------------------------------
       	virtual ~CStand();
	//-------------------------------------------------


	/**/

  virtual int invStand ();	// Инвариант
 virtual  void RefreshPoints ();

  //---------------------------------------------------
 virtual  void SetP(double,double);
 virtual  void SetP(CPoint); // Задание точки P1
 virtual  void MoveStand (double,double); // Плоскопараллельное перемещение на dx dy
 const CircleList<CPoint>& CStand :: GetPoints ()  const;
 const CTriangle& CStand :: GetStand() const;
  int isIn (const CircleList<CPoint>& Points) const;

  //---------------------------------------------------

 virtual  void Print ();
 virtual  void SetDebug (unsigned int);
 virtual   unsigned int GetID ();
 virtual   unsigned int GetCurrent();
 virtual   unsigned int GetTotal();


};



#endif