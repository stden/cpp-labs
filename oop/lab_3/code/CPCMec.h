//���� : CP�Mec.h
//������ ������ "�������� ��������� ��������"
//����� : ������ �.�.
//���� : 22.05.2010 �������� : 1.0

#ifndef CPCMEC_H
#define CPCMEC_H

#include <iostream.h>
#include "CPoint.h"
#include "CPMec.h"
#include "CCover.h"
#include "CList.h"
#include "CListN.h"


class CClosedPistonMechanism : public CPistonMechanism {
 private:
  CircleList<CPoint> MainPoints;
  CCover Cover;
  void  AddPoints ();
 public:

  /*������������*/
  //-------------------------------------------------
  CClosedPistonMechanism(CPoint, double, double, double, double, double, double, double, double, double, double);
  CClosedPistonMechanism(double, double, double, double, double, double, double, double, double, double, double, double);
  CClosedPistonMechanism(); // Constructor without parametrs
  //-------------------------------------------------

  /*����������*/
  //-------------------------------------------------
  virtual ~CClosedPistonMechanism();
  //-------------------------------------------------


  /**/
  int inv (); // ���������
  void RefreshPoints ();

  //---------------------------------------------------
  void SetP1(double, double);
  void SetP1(CPoint); // ������� ����� P1
  void Move (double, double); // ������������������ ����������� �� dx dy
  const CircleList<CPoint>& GetPoints () const;
  const CCover& GetCover() const;

  //---------------------------------------------------

  void Print ();


  friend ostream& operator<<( ostream& output, const CClosedPistonMechanism&);

};



#endif