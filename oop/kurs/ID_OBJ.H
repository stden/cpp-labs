// ����: ID_Obj.h
// ������� �����
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _ID_OBJ_H
#define _ID_OBJ_H

#include "debug.h"

class ID_Object {
  // ��饥 ������⢮ ᮧ������ �����-���� ��������஢
  static int countall;

  ID_Object() {};

 public:
  static int GenID() {
    return ++countall;
  }

  static int getTotal() {
    return countall;
  }
};

#endif