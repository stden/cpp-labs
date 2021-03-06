// ����: LIST.H
// ����� ���᮪
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, ।���� 1.0.

#ifndef _COUTNED_LIST_H
#define _COUTNED_LIST_H

#include <iostream.h>
#include "Element.h"

template<class type>
class CList {
  //�����⥫� �� ⥪�騩 ������� ᯨ᪠
  CElem<type>* m_current;

  //�����⥫� �� �������� ������� ᯨ᪠
  CElem<type>* m_first;

  //������⢮ ��������஢ ����� ���᮪
  static int countreal;

  //��饥 ������⢮ ᮧ������ �����-���� ��������஢
  static int countall;

  //�����䨪���
  int m_id;

 public:
  /*
  * ���������
  */
  CList() : m_id(countall++) {
    m_current = NULL;
    m_first  = NULL;
    countreal++;

    // cout << "Linear list number " << countreal << " created" << endl;
  }

  /*
  * ��������� ����஢����
  */
  CList(const CList& list) : m_id(countall++) {
    countreal++;
    m_current = NULL;
    m_first  = NULL;
    CElem<type>* cur = list.m_first;

    while (cur != NULL) {
      insert(cur->getValue());
      cur = cur->getNext();
    }

    // cout << "Linear list number " << countreal << " copyed" << endl;
  }

  /*
  * �������� ������� � ����� ᯨ᪠
  */
  void insert(const type& elem) {
    CElem<type>* tmp = new CElem<type>(elem);

    while (goNext()) {}

    if (m_current != NULL)
      m_current->setNext(tmp);
    else
      m_first = tmp;

    m_current = tmp;
  }

  /*
  * �������� ������� � ��砫� ᯨ᪠
  */
  void insertBegin(const type& elem) {
    CElem<type>* tmp = new CElem<type>(elem);

    tmp->setNext(m_first);
    m_first = tmp;
  }

  /*
  * ���� �� ᯨ᮪?
  */
  int isEmpty() {
    return (m_first == NULL);
  }

  /*
  * ������� �������
  */
  int dispose() {
    if (m_current == NULL)
      return 0;

    CElem<type>* next = m_current->getNext();
    delete(m_current);
    m_current = next;

    return 1;
  }

  /*
  * ������� �������
  */
  CElem<type>& getElem() {
    return *m_current;
  }

  /*
  * ������� 㪠��⥫� �� ⥪�騩 �������
  */
  CElem<type>* getCurrent() {
    return m_current;
  }

  /*
  * �������� �������
  */
  void setElem(const type& elem) {
    if (m_current != NULL)
      m_current->setValue(elem);
  }

  /*
  * ��६������� �� ������� ��ࠢ�
  */
  int goNext() {
    if (m_current != NULL) {
      if (m_current->getNext() != NULL)
        m_current = m_current->getNext();
      else
        return 0;
    } else
      return 0;

    return 1;
  }

  /*
  * ��६������� �� �������� ������� ᯨ᪠
  */
  void goFirst() {
    m_current = m_first;
  }
  /*
  * ������� ������⢮ ��������஢ �����
  */
  static int getCount() {
    return countall;
  }

  /*
  * ��������
  */
  ~CList() {
    countreal--;
    goFirst();

    while (dispose()) {}

    //cout << "Linear list destroyed... (remain " << countreal << ")" << endl;
  }

  /*
  * ������� �᫮ ������⮢ ᯨ᪠
  */
  size_t size() {
    CElem<type>* tmp = m_current;
    size_t i = 0;

    goFirst();

    while (goNext())
      ++i;

    if (m_first != NULL)
      ++i;

    return i;
  }

  /*
  * ��ॣ�㧪� ������ ��ᢠ������
  */
  CList& operator=(const CList& list) {
    CElem<type>* cur = list.m_first;

    while (cur != NULL) {
      insert(cur->getValue());
      cur = cur->getNext();
    }

    return *this;
  }

  void print() {
    CElem<type>* cur = m_first;

    while (cur != NULL) {
      cout << cur->getValue() << ", ";
      cur = cur->getNext();
    }

    cout << endl;
  }
};

template <class type>
int CList<type> :: countreal = 0;
template <class type>
int CList<type> :: countall = 0;

#endif