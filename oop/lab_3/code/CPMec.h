//���� : CPMec.h
//������ ������ "������"
//����� : ������ �.�.
//���� : 22.02.2010 �������� : 1.0

#ifndef CPMEC_H
#define CPMEC_H

#include <iostream.h>
#include "CPoint.h"
#include "CPiston.h"
#include "CCup.h"
#include "CList.h"
#include "CListN.h"


class CPistonMechanism {
 protected:
  CircleList<CPoint> MainPoints;
  CPiston Piston;
  CCup Cup;
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
  void  AddPoints ();
 public:

  /*������������*/
  //-------------------------------------------------
  CPistonMechanism(CPoint, double, double, double, double, double, double, double, double);
  CPistonMechanism(double, double, double, double, double, double, double, double, double, double);
  CPistonMechanism(const CCup& _cup, const CPiston& _piston);
  CPistonMechanism(); // Constructor without parametrs
  //-------------------------------------------------

  /*����������*/
  //-------------------------------------------------
  ~CPistonMechanism();
  //-------------------------------------------------


  /**/

  virtual int inv (); // ���������
  virtual  void RefreshPoints ();

  //---------------------------------------------------
  virtual  void SetP1(double, double);
  virtual   void SetP1(CPoint); // ������� ����� P1
  virtual   void Move (double, double); // ������������������ ����������� �� dx dy
  int MovePiston (double); // ����������� ������ ������ ���������
  virtual  const CircleList<CPoint>& GetPoints () const;
  const CCup& GetCup() const;
  const CPiston& GetPiston() const;

  //---------------------------------------------------

  virtual void Print ();
  virtual void SetDebug (unsigned int);
  virtual  unsigned int GetID ();
  virtual  unsigned int GetCurrent();
  virtual  unsigned int GetTotal();

  friend ostream& operator<<( ostream& output, const CPistonMechanism&);

};



#endif