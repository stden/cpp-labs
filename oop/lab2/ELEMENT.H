// ����: ELEMENT.H
// ����� ������� ������
// �����: ������� �. ��. ��. 7304
// ����: 16.05.10, �������� 1.0.

#ifndef _ELEMENT
#define _ELEMENT

#include <iostream.h>


template<class elemType>
class CElem {
  //�������� �������� ������
  elemType  m_value;

  //��������� �� ��������� �������
  CElem<elemType>* m_next;

  //���������� ����������� ������ ������� ������
  static int countreal;

  //����� ���������� ��������� �����-���� �����������
  static int countall;

  //�������������
  int m_id;

 public:
  /*
  * ����������
  */
  CElem(const elemType& elem) : m_value(elem), m_id(countall++) {
    countreal++;
    m_next = NULL;
    // cout << "  Element num = " << countreal << " created" << endl;
  }


  /*
  * ���������� �����������
  */
  CElem(const CElem& elem) : m_value(elem.m_value), m_id(countall++) {
    countreal++;
    m_next = NULL;
    // cout << "  Element num = " << countreal << " copyed" << endl;
  }

  /*
  * �������� ��������
  */
  elemType& getValue() {
    return m_value;
  }

  /*
  * �������� ��������
  */
  void setValue(const elemType& elem) {
    m_value = elem;
  }

  /*
  * �������� ��������� �� ��������� �������
  */
  CElem<elemType>* getNext() const {
    return m_next;
  }

  /*
  * ������� ��������� �������
  */
  void setNext(CElem* elem) {
    m_next = elem;
  }

  /*
  * �������� ���������� ����������� ������
  */
  static int getCount() {
    return countall;
  }

  /*
  * ����������
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