//���� : CPColl.h
//������ ������ "����� ��������� ����������"
//����� : ������ �.�.
//���� : 22.02.2010 �������� : 1.0

#ifndef CPCOLL_H
#define CPCOLL_H

#include <iostream.h>
#include "CPoint.h"
#include "CPMec.h"
#include "CList.h"
#include "CListN.h"


class CPistonCollection {
protected:
 // CircleList<CPoint> MainPoints;
  CircleList<CPistonMechanism*> Collection;
  unsigned int Length;
private:
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
public:

				/*������������*/
	//-------------------------------------------------
      	CPistonCollection(); // Constructor without parametrs
	//-------------------------------------------------

				/*����������*/
	//-------------------------------------------------
       virtual	~CPistonCollection();
	//-------------------------------------------------


	/**/
  virtual int invColl();
 // virtual void RefreshPoints ();

  //---------------------------------------------------
virtual void SetP1(double,double);
virtual void SetP1(CPoint); // ������� ����� P1
virtual void Move (double,double); // ������������������ ����������� �� dx dy
virtual void MovePiston (double);
//virtual  const CircleList<CPoint>& GetPoints () const;
  const CircleList<CPistonMechanism*>& GetCollection () const;

virtual  void Add (CPistonMechanism*);
  void Delete (int);
  unsigned int GetLength () const;

  //---------------------------------------------------

virtual  void Print ();

virtual  void SetDebug (unsigned int);
virtual  unsigned int GetID ();
virtual  unsigned int GetCurrent();
virtual  unsigned int GetTotal();

};



#endif