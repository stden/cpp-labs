//Файл : CTria.h
//Проект класса "типоугольный треугольник"
//Автор : Монько А.О.
//Дата : 22.05.2010 Редакция : 1.0

#ifndef TRIA_H
#define TRIA_H

#include <iostream.h>
#include "CPoint.h"



class CTriangle {
private:
  CPoint P1, P2, P3;
  double P1P2, P2P3, P3P1;
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
public:

				/*Конструкторы*/
	//-------------------------------------------------
	CTriangle(CPoint _P1,double _P1P2,CPoint _P3); // P1 length(p1,p2) P3
	CTriangle(); // Constructor without parametrs
	//-------------------------------------------------

				/*Деструктор*/
	//-------------------------------------------------
	~CTriangle();
	//-------------------------------------------------


	/**/

  int inv ();	// Инвариант

  //---------------------------------------------------
  void SetP1(double,double);
  void SetP1(CPoint); // Задание точки P1
  void Move (double,double); // Плоскопараллельное перемещение на dx dy
  CPoint GetP1() const;
  CPoint GetP2() const;
  CPoint GetP3() const;
  double GetP1P2() const;
  double GetP2P3() const;
  double GetP3P1() const;

  int isIn (CPoint P) const; // Проверка принадлежности триугольнику

  //---------------------------------------------------

  void Print ();
  void SetDebug (unsigned int);
  unsigned int GetID ();
  unsigned int GetCurrent();
  unsigned int GetTotal();



};



#endif