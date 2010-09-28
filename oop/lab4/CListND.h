//Файл: CListND.h
//Проект шаблона класса "Узел кольцевого однонаправленного списка"
//Автор: Волынко Е. ст. гр. 7304
//Дата: 21.02.2010, Редакция: 1.0


#ifndef CLISTND_H
#define CLISTND_H

template <class ValueType>

class CLNode {
protected:
  CLNode* _next;  // связь к последующему узлу
  ValueType _value;
  static int debug;
public:
  CLNode(const ValueType& value);
  CLNode();
// ~CLNode (void);
  CLNode* GetNext(void) const;
  void SetNext(CLNode* n);
  ValueType& GetValue();
  void SetValue(ValueType);
// CLNode* Insert(CLNode*);  // вставить узел после текущего
};

template <class ValueType>
int CLNode<ValueType> :: debug = 0;

#endif