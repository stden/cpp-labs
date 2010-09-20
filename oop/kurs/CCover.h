//Файл : CCover.h
//Проект класса "крышка"
//Автор : Монько А.О.
//Дата : 22.02.2010 Редакция : 1.0

#ifndef CCOVER_H
#define CCOVER_H

#include <iostream.h>
#include "CPoint.h"
#include "CRect.h"
#include "CList.h"
#include "CListN.h"


class CCover {
private:
  CircleList<CPoint> MainPoints;
  CRectangle Hole;
  CRectangle Cover;
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
public:

				/*Конструкторы*/
	//-------------------------------------------------
	CCover(CPoint,double cover_width,double cover_height, double hole_width); // P1 width heigth length
	CCover(); // Constructor without parametrs
	//-------------------------------------------------

				/*Деструктор*/
	//-------------------------------------------------
      	~CCover();
	//-------------------------------------------------


	/**/

  int inv ();	// Инвариант
  void RefreshPoints ();

  //---------------------------------------------------
  void SetP1(double,double);
  void SetP1(CPoint P0); // Задание точки P1
  void Move (double dx, double dy); // Плоскопараллельное перемещение на dx dy
  const CircleList<CPoint>& GetPoints () const;
  CRectangle GetHole() const;
  CRectangle GetCover() const;


  //---------------------------------------------------

  void Print ();
  void SetDebug (unsigned int);
  unsigned int GetID ();
  unsigned int GetCurrent();
  unsigned int GetTotal();

};



#endif