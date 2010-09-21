// Файл: COLIST.H
// Класс Список
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, редакция 1.0.

#ifndef _CO_LIST_H
#define _CO_LIST_H

#include <iostream.h>
#include "Element.h"
#include <assert.h>

template<class type>
class CList
{
  //Указатель на текущий элемент списка
  CElem<type>* m_current;

  //Указатель на головной элемент списка
  CElem<type>* m_first;

  //Количество экземпляров класса Список
  static int countreal;

  //Общее количество созданных когда-либо экземпляров
  static int countall;

  //Идентификатор
  int m_id;

public:
  /*
  * Конструктор
  */
  CList() : m_id(countall++)
  {
    m_current=NULL;
    m_first  =NULL;
    countreal++;    
    
   // cout << "Linear list # " << countreal << " created" << endl;
  }

  /*
  * Конструктор копирования
  */
  CList(const CList& list) : m_id(countall++)
  {
    countreal++;
    m_current=NULL;
    m_first  =NULL;
    CElem<type>* cur=list.m_first;

    while(cur!=NULL) {
      insert(cur->getValue());
      cur=cur->getNext();
    }

   // cout << "Linear list # " << countreal << " copyed" << endl;
  }

  /*
  * Добавить элемент в конец списка
  */
  void insert(const type& elem)
  {
    CElem<type>* tmp = new CElem<type>(elem);

    while(goNext()) {}

    if(m_current!=NULL)
      m_current->setNext(tmp);
    else
      m_first=tmp;
    m_current=tmp;
  }

  /*
  * Добавить элемент в начало списка
  */
  void insertBegin(const type& elem)
  {
    CElem<type>* tmp = new CElem<type>(elem);
    tmp->setNext(m_first);
    m_first=tmp;
    if(m_current == NULL)
      m_current = m_first;
  }

  /*
  * Пуст ли список?
  */
  int isEmpty()
  {
    return (m_first==NULL);
  }

  /*
  * Удалить элемент
  */
  int dispose() {
    if(m_current==NULL)
      return 0;

    CElem<type>* for_delete = m_current;

    if(m_first == m_current){
      m_first = m_current->getNext();
      m_current = m_first;
    } else {
      CElem<type>* prev = m_first;
      while(prev->getNext() != m_current)
	prev = prev->getNext();
      prev->setNext(m_current->getNext());

      if(m_current->getNext() != NULL)
	m_current = m_current->getNext();
      else
	m_current = prev;
    }

    delete(for_delete);

    return 1;
  }

  /*
  * Получить элемент
  */
  CElem<type>& getElem() {
    assert( m_current != NULL );
    return *m_current;
  }

  /*
  * Получить указатель на текущий элемент
  */
  CElem<type>* getCurrent() {
    return m_current;
  }

  type getValue(){
    assert( m_current != NULL );
    return (*m_current).getValue();
  }

  /*
  * Заменить элемент
  */
  void setElem(const type& elem)
  {
    if(m_current!=NULL)
      m_current->setValue(elem);
  }

  /*
  * Переместиться на элемент вправо
  */
  int goNext()
  {
    if(m_current!=NULL)
    {
      if(m_current->getNext()!=NULL)
  m_current=m_current->getNext();
      else
  return 0;
    }
    else
      return 0;
    return 1;
  }

  /*
  * Переместиться на головной элемент списка
  */
  int goFirst() {
    m_current = m_first;
    return m_current != NULL;
  }

  /*
  * Получить количество экземпляров класса
  */
  static int getCount()
  {
    return countall;
  }

  /*
  * Деструктор
  */
  ~CList()
  {
    countreal--;
    goFirst();
    while(dispose())
    {}

    //cout << "Linear list destroyed... (remain " << countreal << ")" << endl;
  }

  /*
  * Получить число элементов списка
  */
  size_t size()
  {
    CElem<type>* tmp = m_current;
    size_t i = 0;
    goFirst();
    while(goNext())
      ++i;
    if(m_first != NULL)
      ++i;
    m_current = tmp;
    return i;
  }

  /*
  * Перегрузка оператора присваивания
  */
  CList& operator=(const CList& list)
  {
    CElem<type>* cur=list.m_first;

    while(cur!=NULL) 
    {
      insert(cur->getValue());
      cur=cur->getNext();
    }
    return *this;
  }

  void Print() {
    CElem<type>* cur=m_first;
    while(cur!=NULL) {
      cout << cur->getValue() << ", ";
      cur=cur->getNext();
    }
    cout << endl;
  }
};

template <class type>
int CList<type> :: countreal = 0;
template <class type>
int CList<type> :: countall = 0;

#endif