// ����: ELEMENT.H
// ����� ������� ᯨ᪠
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, ।���� 1.0.

#ifndef _ELEMENT
#define _ELEMENT

#include <iostream.h>


template<class elemType>
class CElem {
  //���祭�� ������� ᯨ᪠
  elemType  m_value;

  //�����⥫� �� ᫥���騩 �������
  CElem<elemType>* m_next;

  //������⢮ ��������஢ ����� ������� ᯨ᪠
  static int countreal;

  //��饥 ������⢮ ᮧ������ �����-���� ��������஢
  static int countall;

  //�����䨪���
  int m_id;

 public:
  /*
  * ���������
  */
  CElem(const elemType& elem) : m_value(elem), m_id(countall++) {
    countreal++;
    m_next = NULL;
    // cout << "  Element num = " << countreal << " created" << endl;
  }


  /*
  * ��������� ����஢����
  */
  CElem(const CElem& elem) : m_value(elem.m_value), m_id(countall++) {
    countreal++;
    m_next = NULL;
    // cout << "  Element num = " << countreal << " copyed" << endl;
  }

  /*
  * ������� ���祭��
  */
  elemType& getValue() {
    return m_value;
  }

  /*
  * �������� ���祭��
  */
  void setValue(const elemType& elem) {
    m_value = elem;
  }

  /*
  * ������� 㪠��⥫� �� ᫥���騩 �������
  */
  CElem<elemType>* getNext() const {
    return m_next;
  }

  /*
  * ������� ����騩 �������
  */
  void setNext(CElem* elem) {
    m_next = elem;
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