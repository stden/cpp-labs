//Файл : CView.h
//Проект класса "Вид на стенд с замкнутыми поршневыми механизмами"
//Автор : Монько А.О.
//Дата : 22.05.2010 Редакция : 1.0

#ifndef CVIEW_H
#define CVIEW_H

#include <iostream.h>
#include "CPColl.h"
#include "CStand.h"
#include "CPoint.h"
#include "CList.h"


class CView : public CPistonCollection, public CStand {
private:

public:

				/*Конструкторы*/
	//-------------------------------------------------
	CView(CPoint _P1,double _P1P2,CPoint _P3); // P1 width heigth length
	CView(); // Constructor without parametrs
	//-------------------------------------------------

				/*Деструктор*/
	//-------------------------------------------------
      	~CView();
	//-------------------------------------------------


	/**/

  int inv ();	// Инвариант

  //---------------------------------------------------
  void SetCollectionP1(CPoint P0); // Задание точки P1
  void SetStandP1 (CPoint P0);
  void MoveCollection (double dx, double dy); // Плоскопараллельное перемещение на dx dy
  void MoveStand (double dx, double dy); // Плоскопараллельное перемещение на dx dy
  void Add(CPistonMechanism*) const;
  void Add(const CPistonCollection& C) const;
  int isOnStand (CPistonMechanism*) const;


  //---------------------------------------------------

  void Print ();
  void PrintView ();


};



#endif