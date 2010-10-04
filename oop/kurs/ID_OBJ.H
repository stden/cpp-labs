// Файл: ID_Obj.h
// Объявление класса
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _ID_OBJ_H
#define _ID_OBJ_H

#include "debug.h"

class ID_Object {
  // Общее количество созданных когда-либо экземпляров
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