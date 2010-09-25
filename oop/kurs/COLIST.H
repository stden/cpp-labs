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

  int getID() const { return m_id; }

  /*
  * Конструктор
  */
  CList() : m_id(countall++) {
    m_current = NULL;
    m_first   = NULL;
    countreal++;
    // cout << "Linear list #" << m_id << " created" << endl;
  }

  /*
  * Конструктор копирования
  */
  CList(const CList& list) : m_id(countall++) {
    countreal++;
    m_current = NULL;
    m_first   = NULL;

    for(CElem<type>* cur=list.m_first; cur!=NULL; cur=cur->getNext())
      insert(cur->getValue());

   // cout << "Linear list # " << countreal << " copyed" << endl;
  }

  /*
  * Добавить элемент в конец списка
  */
  void insert(const type& elem) {
    CElem<type>* tmp = new CElem<type>(elem);

    if(m_first==NULL){
      m_first = tmp;
    } else {
      CElem<type>* cur = m_first;
      while(cur!=NULL && cur->getNext()!=NULL)
        cur = cur->getNext();
      cur->setNext(tmp);
    };
    m_current=tmp;
  }

  /*
  * Добавить элемент в начало списка
  */
  void insertBegin(const type& elem) {
    CElem<type>* new_el = new CElem<type>(elem);
    new_el->setNext(m_first);
    m_first=new_el;
    if(m_current == NULL)
      m_current = m_first;
  }

  /*
  * Пуст ли список?
  */
  int isEmpty() const {
    return m_first==NULL;
  }

  /*
  * Удалить текущий элемент
  */
  int dispose() {
    // Если текущего элемента нет, то удалять нечего и возвращаем 0
    if(m_current==NULL)
      return 0;

    CElem<type>* for_delete = m_current; // Запоминаем элемент для удаления

    // Правильное перекидывание ссылок
    if(m_first == m_current){ // Если удаляем первый элемент
      m_current = m_current->getNext(); // Делаем текущим элементом следующий
      m_first = m_current; // И первым становится также он
    } else { // Если удаляем не первый элемент
      // То нам нужен элемент перед текущим (надо изменить у него ссылку)
      // Ищем этот предыдущий элемент начиная с первого
      CElem<type>* prev = m_first;
      while(prev->getNext() != m_current)
      	prev = prev->getNext();
      // Сейчас prev - тот самый предыдущий элемент
      // И теперь он должен ссылаться на тот элемент, на который ссылался
      // удаляемый элемент
      prev->setNext(m_current->getNext());

      // Остаётся правильно указать текущий элемент в списке
      // Если мы удаляли не последний элемент
      if(m_current->getNext() != NULL)
        // то текущим станет элемент, который сдвинется на место удаляемого
      	m_current = m_current->getNext();
      else
        // а если удаляли последний, то текущим станет предпоследний
      	m_current = prev;
    }

    delete(for_delete); // Собственно удаление элемента из дин. памяти

    // Возвращаем 1 потому что операция удаления удалась
    return 1;
  }

  /*
  * Получить элемент
  */
  CElem<type>& getElem() const {
    assert( m_current != NULL );
    return *m_current;
  }

  /*
  * Получить указатель на текущий элемент
  */
  CElem<type>* getCurrent() const {
    return m_current;
  }

  /*
  * Получить значение текущего элемента
  */
  type& getValue() const {
    assert( m_current != NULL );
    return (*m_current).getValue();
  }

  /*
  * Заменить элемент
  */
  void setElem(const type& elem) {
    assert( m_current != NULL );
    m_current->setValue(elem);
  }

  /*
  * Переместиться на элемент вправо
  */
  int goNext() {
    if(m_current==NULL) return 0;
    m_current = m_current->getNext();
    if (m_current->getNext()==NULL) return 0;
    return 1;
  }

  int hasNext() {
    return m_current!=NULL;
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
  static int getCount() {
    return countall;
  }

  /*
  * Деструктор
  */
  ~CList() {
    countreal--;
    goFirst();
    while(dispose())
    {}

    //cout << "Linear list destroyed... (remain " << countreal << ")" << endl;
  }

  /*
  * Получить число элементов списка
  */
  size_t size() const {
    CElem<type>* tmp = m_first;
    size_t count = 0;
    while(tmp!=NULL){
      count++;
      tmp=tmp->getNext();
    }
    return count;
  }

  /*
  * Перегрузка оператора присваивания
  */
  CList& operator=(const CList& list) {
    m_id = list.getID();
    for( CElem<type>* c=list.m_first; c!=NULL; c=c->getNext())
      insert(c->getValue());
    return *this;
  }

  /*
  * Print list
  */
  void Print() const {
    for( CElem<type>* c=m_first; c!=NULL; c=c->getNext() )
      cout << c->getValue() << ", ";
    cout << endl;
  }
};

template <class type>
int CList<type> :: countreal = 0;
template <class type>
int CList<type> :: countall = 0;

#endif