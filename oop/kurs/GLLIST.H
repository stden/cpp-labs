// ����: CGlassList.h
// ������� ����� �����
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _GLASSLIST_H
#define _GLASSLIST_H

#include <conio.h>

#include "CoPoint.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Glass.h"
#include "debug.h"

class CGlassList {
 protected:
  CList<CGlass*> List;

 public:
  CGlassList();
  ~CGlassList();

  /*
  * ���������� � ᯨ᮪ ����� �⠪����
  */
  void insert(CGlass* gl) {
    List.insert(gl);
  }
  void insertBegin(CGlass* gl) {
    List.insertBegin(gl);
  }

  /*
  * ��६�饭��
  */
  void MoveToPoint(const CCountedPoint& point);

  /*
  * ���饭��
  */
  void MovedXdY(double x, double y);

  /*
  *
  */
  CGlass* getFirst() {
    List.goFirst();
    return List.getValue();
  }

  CGlass* getByID(int glassID) {
    for (List.goFirst(); List.hasNext(); List.goNext())
      if (List.getValue()->getID() == glassID)
        return List.getValue();

    return NULL;
  }

  int Delete(int glassID) {
    for (List.goFirst(); List.hasNext(); List.goNext())
      if (List.getValue()->getID() == glassID) {
        List.dispose();
        return 1;
      }

    return 0;
  }

  size_t size() const {
    return List.size();
  }

  friend ostream& operator << (ostream& s, CGlassList& list);
};

#endif
