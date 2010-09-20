//����: CListND.h
//������ ������� ������ "���� ���������� ����������������� ������"
//�����: ������� �. ��. ��. 7304
//����: 21.02.2010, ��������: 1.0


#ifndef CLISTND_H
#define CLISTND_H

template <class ValueType>

class CLNode {
protected:
  CLNode* _next;	// ����� � ������������ ����
  ValueType _value;
  static int debug;
public:
  CLNode (const ValueType& value);
  CLNode ();
 // ~CLNode (void);
  CLNode* GetNext(void) const;
  void SetNext(CLNode* n);
  ValueType& GetValue();
  void SetValue (ValueType);
 // CLNode* Insert(CLNode*);  // �������� ���� ����� ��������
};

template <class ValueType>
int CLNode<ValueType> :: debug = 0;

#endif