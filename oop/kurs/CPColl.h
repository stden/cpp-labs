// ����: CPColl.h
//������ ������ "����� ��������� ����������"
// �����: ������� �. ��. ��. 7304
// ����: 22.02.2010 ��������: 1.0

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
  int Length;
private:
  static int debug;
  static int total;
  int id;
  static int current;
public:

  /*������������*/
  //-------------------------------------------------
  CPistonCollection(); // Constructor without parametrs
  //-------------------------------------------------

  /*����������*/
  //-------------------------------------------------
  virtual ~CPistonCollection();
  //-------------------------------------------------


  /**/
  virtual int invColl();
// virtual void RefreshPoints ();

  //---------------------------------------------------
  virtual void SetP1(double, double);
  virtual void SetP1(CPoint); // ������� ����� P1
  virtual void Move(double, double); // ������������������ ����������� �� dx dy
  virtual void MovePiston(double);
//virtual  const CircleList<CPoint>& GetPoints () const;
  const CircleList<CPistonMechanism*>& GetCollection() const;

  virtual  void Add(CPistonMechanism*);
  void Delete(int);
  int GetLength() const;

  //---------------------------------------------------

  virtual  void Print();

  virtual  void setDebug(int);
  virtual  int getID();
  virtual  int GetCurrent();
  virtual  int GetTotal();

};



#endif