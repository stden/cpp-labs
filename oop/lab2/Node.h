//File cNode.h
//declaration cNode class
//Author: Volinko Evgeniy
//Date: 15.02.2010 version: 1.0

#ifndef CNODE_H
#define CNODE_H

//#include "cNode.cpp"
template <class type>
class cNode
{
private:
	type Value;
	cNode *Next;
public:
	cNode(void);
	~cNode();
	cNode<type> *GetNext(void);
	void SetNext(cNode *b);
	type GetValue(void);
	void SetValue (type a);
};

#endif