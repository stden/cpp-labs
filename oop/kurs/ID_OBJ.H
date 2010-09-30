// Файл: ID_Obj.h
// Объявление класса
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _ID_OBJ_H
#define _ID_OBJ_H

class ID_Object {
  // Количество экземпляров класса стакан
  static int countreal;

  // Общее количество созданных когда-либо экземпляров
  static int countall;

  // Идентификатор
  int m_id;

public:
  int getID() const { return m_id; };

  /*
  * Получить количество экземпляров класса
  */
  static int getCount() {
    return countreal;
  }

  static int getTotal() {
    return countall;
  }

  /*
  * Конструктор
  */
  ID_Object() :
    m_id(++countall) /* Присваиваем очередной идентификатор */
  {
    countreal++;
  };

  /*
  * Деструктор
  */
  ~ID_Object() {
    countreal--;
  };
};

#endif