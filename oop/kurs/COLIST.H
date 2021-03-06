// ����: COLIST.H
// ����� ���᮪
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, ।���� 1.0.

#ifndef _CO_LIST_H
#define _CO_LIST_H

#include <iostream.h>
#include "Element.h"
#include <assert.h>

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

  int getID() const {
    return m_id;
  }

  /*
  * ���������
  */
  CList() : m_id(countall++) {
    m_current = NULL;
    m_first   = NULL;
    countreal++;
    // cout << "Linear list #" << m_id << " created" << endl;
  }

  /*
  * ��������� ����஢����
  */
  CList(const CList& list) : m_id(countall++) {
    countreal++;
    m_current = NULL;
    m_first   = NULL;

    for (CElem<type>* cur = list.m_first; cur != NULL; cur = cur->getNext())
      insert(cur->getValue());

    // cout << "Linear list # " << countreal << " copyed" << endl;
  }

  /*
  * �������� ������� � ����� ᯨ᪠
  */
  void insert(const type& elem) {
    CElem<type>* tmp = new CElem<type>(elem);

    if (m_first == NULL)
      m_first = tmp;
    else {
      CElem<type>* cur = m_first;

      while (cur != NULL && cur->getNext() != NULL)
        cur = cur->getNext();

      cur->setNext(tmp);
    };

    m_current = tmp;
  }

  /*
  * �������� ������� � ��砫� ᯨ᪠
  */
  void insertBegin(const type& elem) {
    CElem<type>* new_el = new CElem<type>(elem);
    new_el->setNext(m_first);
    m_first = new_el;

    if (m_current == NULL)
      m_current = m_first;
  }

  /*
  * ���� �� ᯨ᮪?
  */
  int isEmpty() const {
    return m_first == NULL;
  }

  /*
  * ������� ⥪�騩 �������
  */
  int dispose() {
    // �᫨ ⥪�饣� ������� ���, � 㤠���� ��祣� � �����頥� 0
    if (m_current == NULL)
      return 0;

    CElem<type>* for_delete = m_current; // ���������� ������� ��� 㤠�����

    // �ࠢ��쭮� ��४��뢠��� ��뫮�
    if (m_first == m_current) { // �᫨ 㤠�塞 ���� �������
      m_current = m_current->getNext(); // ������ ⥪�騬 ������⮬ ᫥���騩
      m_first = m_current; // � ���� �⠭������ ⠪�� ��
    } else { // �᫨ 㤠�塞 �� ���� �������
      // �� ��� �㦥� ������� ��। ⥪�騬 (���� �������� � ���� ��뫪�)
      // �饬 ��� �।��騩 ������� ��稭�� � ��ࢮ��
      CElem<type>* prev = m_first;

      while (prev->getNext() != m_current)
        prev = prev->getNext();

      // ����� prev - �� ᠬ� �।��騩 �������
      // � ⥯��� �� ������ ��뫠���� �� �� �������, �� ����� ��뫠���
      // 㤠�塞� �������
      prev->setNext(m_current->getNext());

      // ������� �ࠢ��쭮 㪠���� ⥪�騩 ������� � ᯨ᪥
      // �᫨ �� 㤠�﫨 �� ��᫥���� �������
      if (m_current->getNext() != NULL)
        // � ⥪�騬 �⠭�� �������, ����� ᤢ������ �� ���� 㤠�塞���
        m_current = m_current->getNext();
      else
        // � �᫨ 㤠�﫨 ��᫥����, � ⥪�騬 �⠭�� �।��᫥����
        m_current = prev;
    }

    delete(for_delete); // ����⢥��� 㤠����� ������� �� ���. �����

    // �����頥� 1 ��⮬� �� ������ 㤠����� 㤠����
    return 1;
  }

  /*
  * ������� �������
  */
  CElem<type>& getElem() const {
    assert(m_current != NULL);
    return *m_current;
  }

  /*
  * ������� 㪠��⥫� �� ⥪�騩 �������
  */
  CElem<type>* getCurrent() const {
    return m_current;
  }

  /*
  * ������� ���祭�� ⥪�饣� �������
  */
  type& getValue() const {
    assert(m_current != NULL);
    return (*m_current).getValue();
  }

  /*
  * �������� �������
  */
  void setElem(const type& elem) {
    assert(m_current != NULL);
    m_current->setValue(elem);
  }

  /*
  * ��६������� �� ������� ��ࠢ�
  */
  int goNext() {
    if (m_current == NULL) return 0;

    m_current = m_current->getNext();

    if (m_current->getNext() == NULL) return 0;

    return 1;
  }

  int hasNext() {
    return m_current != NULL;
  }

  /*
  * ��६������� �� �������� ������� ᯨ᪠
  */
  int goFirst() {
    m_current = m_first;
    return m_current != NULL;
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
  size_t size() const {
    CElem<type>* tmp = m_first;
    size_t count = 0;

    while (tmp != NULL) {
      count++;
      tmp = tmp->getNext();
    }

    return count;
  }

  /*
  * ��ॣ�㧪� ������ ��ᢠ������
  */
  CList& operator=(const CList& list) {
    m_id = list.getID();

    for (CElem<type>* c = list.m_first; c != NULL; c = c->getNext())
      insert(c->getValue());

    return *this;
  }

  /*
  * ������ �뢮�� � ��⮪
  */
  friend ostream& operator << (ostream& s, const CList& l) {
    for (CElem<type>* c = l.m_first; c != NULL; c = c->getNext())
      cout << c->getValue() << ", ";

    cout << endl;
    return s;
  }
};

template <class type>
int CList<type> :: countreal = 0;
template <class type>
int CList<type> :: countall = 0;

#endif