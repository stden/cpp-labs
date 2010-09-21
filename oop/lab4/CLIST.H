// Файл: CList.h
// Реализация шаблона класса "Кольцевой однонаправленный список"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 21.02.2010, Редакция: 1.0

#ifndef CLIST_H             
#define CLIST_H

#include "CListD.h"
#include <stdlib.h>

template<class ValueType>
CircleList<ValueType>::CircleList() : _length(0), header(0), last(0), cur(0) {
  if (debug) cout << "CircleList is created, length = "<<_length<<endl;
}                       

template<class ValueType>
CircleList<ValueType>::~CircleList () {
  /*  while (_length > 0) {
  CLNode <ValueType>* thead = header;
  header = header->GetNext();
  last->SetNext(header);
  --_length;
  delete thead;
  }*/

  if (debug) cout << "CircleList is deleted, length = "<<_length<<endl;
}

template <class ValueType>
int CircleList<ValueType> :: GetSize () const {
  return _length;
}

template <class ValueType>
CLNode<ValueType>* CircleList<ValueType> :: GetFirst() {
  if (_length) {
    cur = header;
    return cur;
  }

  else return 0;
}

template <class ValueType>
CLNode<ValueType>* CircleList<ValueType> :: GetLast() {
  if (_length) {
    cur = last;
    return cur;
  }

  else return 0;
}

template <class ValueType>
CLNode<ValueType>* CircleList<ValueType> :: GetCur() const {
  if (_length && cur) return cur;
  else return 0;
}

template <class ValueType>
CLNode<ValueType>* CircleList<ValueType> :: GetElemByNum(int N) const {
  if (_length <= 0) return NULL;
  if (_length == 1) return header;

  if (_length > 1) {
    if (N < 0) return NULL;
    if (N >= _length) return NULL;
    //         GetFirst();
    CLNode<ValueType>* tmp = header;
    for (int i = 0; i < _length; i++) {
      if (i == N) return tmp;
      tmp = tmp->GetNext();

    }

  }

  return NULL;

}

template <class ValueType>
CLNode<ValueType>* CircleList<ValueType> :: SetCur (const ValueType& val) {
  cur->SetValue(val);
  return cur;
}

template <class ValueType>
CLNode<ValueType>* CircleList<ValueType> :: NextCur () {
  cur = cur->GetNext();
  return cur;
}

template<class ValueType>
void CircleList<ValueType>::RemoveCur() {

  if(_length == 0) {
    cout<<"Empty list, nothing to delete"<<endl;
    return;
  }

  if(_length == 1){
    cur = header;
    delete cur;
    header = last = cur = 0;
    --_length;
    return;
  }

  if(_length > 1){
    if (cur == header) {
      CLNode<ValueType>* tcur = header;
      header = header->GetNext();
      last->SetNext(header);
      delete tcur;
      cur = header;
      --_length;
      return;
    }
    int i = 0;
    CLNode<ValueType>* tcur = header;
    while (i < _length+1 ) {
      if (tcur->GetNext() == cur) {
        tcur->SetNext(cur->GetNext());
        if (cur == last) last = tcur;
        --_length;
        delete cur;
        return;
      }
      tcur = tcur->GetNext();
    }
  }
}

template<class ValueType>
void CircleList<ValueType>::ExcludeCur() {

  if(_length == 0) {
    cout<<"Empty list, nothing to delete"<<endl;
    return;
  }

  if(_length == 1){
    cur = header;
    // delete cur;
    header = last = cur = 0;
    --_length;
    return;
  }

  if(_length > 1){


    if (cur == header) {
      CLNode<ValueType>* tcur = header;
      header = header->GetNext();
      last->SetNext(header);
      delete tcur;
      cur = header;
      --_length;
      return;
    }

    int i = 0;
    CLNode<ValueType>* tcur = header;
    while (i < _length+1 ) {
      if (tcur->GetNext() == cur) {
        tcur->SetNext(cur->GetNext());
        if (cur == last) last = tcur;
        --_length;
        //       delete cur;
        return;
      }
      tcur = tcur->GetNext();
    }
  }
}

template<class ValueType>
void CircleList<ValueType>::ExcludeByNum(int n) {
  if(_length == 0) {
    cout<<"Empty list, nothing to delete"<<endl;
    return;
  }
  if(_length == 1){
    cur = header;
    // delete cur;
    header = last = cur = 0;
    --_length;
    return;
  }

  if(_length > 1 && n < _length && n > 0){
    if (cur == header) {
      CLNode<ValueType>* tcur = header;
      header = header->GetNext();
      last->SetNext(header);
      delete tcur;
      cur = header;
      --_length;
      return;
    }

    int i = 0;
    CLNode<ValueType>* tcur = header;
    while (i < _length+1 ) {
      if (i == n) {
        tcur->SetNext(cur->GetNext());
        if (cur == last) last = tcur;
        --_length;
        //       delete cur;
        return;
      }
      tcur = tcur->GetNext();
    }
  }
}

template<class ValueType>
CLNode<ValueType>* CircleList<ValueType>:: Append (CLNode<ValueType>* node) {
  if(_length == 0) { // Empty list
    header = last = node;
    last->SetNext(header);
    ++_length;
  } else { // List is filled somehow
    last->SetNext(node);
    last = node;
    node->SetNext(header);
    ++_length;
  }
  return node;
}

template<class ValueType>
CLNode<ValueType>* CircleList<ValueType>:: Prepend (CLNode<ValueType>* node)
{
  if(_length == 0) { // Empty list
    header = last = node;
    last->SetNext(header);
    ++_length;
  } else { // List is filled somehow
    node->SetNext(header->GetNext());
    header->SetNext(node);
    ++_length;
  }
  return node;
}

template<class ValueType>
void CircleList<ValueType>:: Print () const {

  if(_length == 0){
    cout<<endl<<"The List is empty"<<endl;
    return;
  }

  short i = 0;
  CLNode <ValueType> * temp = header;

  while (i < _length && temp) {
    cout << "Element "<<i<<": "<<temp.getValue<<endl;
    i++;
    temp = temp->GetNext();
  }

  cout <<endl<<endl;


}



#endif

