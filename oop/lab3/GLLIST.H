// ����: CGlassList.h
// ������� ����� �����
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _GLASSLIST_H
#define _GLASSLIST_H

#include "CoPoint.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Glass.h"
#include <conio.h>

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
    List.goFirst();

    while (List.getCurrent() != NULL) {
      if (List.getValue()->getID() == glassID)
        return List.getValue();

      List.goNext();
    }

    return NULL;
  }

  friend ostream& operator << (ostream& s, CGlassList& list);
};

#endif
