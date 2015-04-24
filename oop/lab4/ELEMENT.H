// Файл: ELEMENT.H
// Класс Элемент списка
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, редакция 1.0.

#ifndef _ELEMENT
#define _ELEMENT

#include <iostream.h>


template<class elemType>
class CElem {
  //Значение элемента списка
  elemType  m_value;

  //Указатель на следующий элемент
  CElem<elemType>* m_next;

  //Количество экземпляров класса Элемент списка
  static int countreal;

  //Общее количество созданных когда-либо экземпляров
  static int countall;

  //Идентификатор
  int m_id;

 public:
  /*
  * Конструтор
  */
  CElem(const elemType& elem) : m_value(elem), m_id(countall++) {
    countreal++;
    m_next = NULL;
    // cout << "  Element num = " << countreal << " created" << endl;
  }


  /*
  * Конструтор копирования
  */
  CElem(const CElem& elem) : m_value(elem.m_value), m_id(countall++) {
    countreal++;
    m_next = NULL;
    // cout << "  Element num = " << countreal << " copyed" << endl;
  }

  /*
  * Получить значение
  */
  elemType& getValue() {
    return m_value;
  }

  /*
  * Заменить значение
  */
  void setValue(const elemType& elem) {
    m_value = elem;
  }

  /*
  * Получить указатель на следующий элемент
  */
  CElem<elemType>* getNext() const {
    return m_next;
  }

  /*
  * Указать слудующий элемент
  */
  void setNext(CElem* elem) {
    m_next = elem;
  }

  /*
  * Получить количество экземпляров класса
  */
  static int getCount() {
    return countall;
  }

  /*
  * Деструктор
  */
  ~CElem() {
    countreal--;
    //cout << "  Element destroyed (remain " << countreal << ") " << endl;
  }

};

template <class elemType>
int CElem<elemType> :: countreal = 0;
template <class elemType>
int CElem<elemType> :: countall = 0;

#endif