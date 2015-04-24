//File Node.h
//declaration cNode class
//Author: Volinko Evgeniy
//Date: 15.02.2010 version: 1.0

#ifndef CNODE_H
#define CNODE_H

template <class type>
class CNode {
 private:
  type Value;
  cNode* Next;
 public:
  CNode(void);
  ~CNode();
  CNode<type>* GetNext(void);
  void SetNext(CNode* b);
  type GetValue(void);
  void SetValue(type a);
};

#endif