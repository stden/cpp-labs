//����: CListD.h
//������ ������� ������ "��������� ���������������� ������"
//�����: ������ �.�.
//����: 21.02.2010, ��������: 1.0

#ifndef CLISTD_H
#define CLISTD_H

#include "CListND.h"


template<class ValueType>
 class CircleList {
		 private:
		      	CLNode<ValueType> *header;
		      	CLNode<ValueType> *cur;
		      	CLNode<ValueType> *last;
		        int _length;
                        static unsigned int debug;
		 public :
		      	CircleList (void);  // Constructor creates NULL list
		      	~CircleList (void); // Destructor deletes all elements
                        CLNode<ValueType>* GetFirst(); // Setting header as current element
                        CLNode<ValueType>* GetLast(); // Setting last as current element
                        CLNode<ValueType>* GetCur() const; // Getting current element
                        CLNode<ValueType>* GetElemByNum(int) const; // Getting current element
                        CLNode<ValueType>* SetCur(const ValueType&);
                        CLNode<ValueType>* NextCur(); // Setting next element to current as current
                        CLNode<ValueType>* Append (CLNode<ValueType>*); // Inserting node at the end of the list
		      	CLNode<ValueType>* Prepend (CLNode<ValueType>*); // Inserting node after header
		      	void RemoveCur (void);
                        int GetSize () const; // Getting length of the list
                        void Print () const;
};

template<class ValueType>
unsigned int CircleList<ValueType> :: debug = 0;

#endif
