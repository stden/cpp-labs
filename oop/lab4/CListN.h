//Файл: CListN.h
//Реализация шаблона класса "Узел кольцевого однонаправленного списка"
//Автор: Волынко Е. ст. гр. 7304
//Дата: 21.02.2010, Редакция: 1.0

#ifndef CLISTN_H
#define CLISTN_H

#include "CListND.h"
#include "iostream.h"

template <class ValueType>
CLNode<ValueType>::CLNode(const ValueType& value) : _next(this), _value(value) {
  if (debug) cout << "CLNode is created, value = " << _value << endl;
}

template <class ValueType>
CLNode<ValueType>::CLNode() : _next(NULL), _value(0) {
  if (debug) cout << "CLNode is created, value = " << _value << endl;
}

/*template <class ValueType>
CLNode<ValueType>::~CLNode () {
if (debug) cout << "CLNode is deleted, value = "<<_value<<endl;
} */

template <class ValueType>
CLNode<ValueType>* CLNode<ValueType>::GetNext() const {
  return _next;
}

template <class ValueType>
void CLNode<ValueType>::SetValue(ValueType val) {
  _value = val;
}

template <class ValueType>
ValueType& CLNode<ValueType>::GetValue() {
  return _value;
}

template< class ValueType >
void CLNode<ValueType> :: SetNext(CLNode<ValueType>* n) {
  _next = n;
}

#endif
