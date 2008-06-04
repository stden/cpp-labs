#include <iostream>
using namespace std;
////////////////////
template <class Type>
struct link
{
 Type data;
 link* next;
 link* prev;
};
/////////////////////
template <class Type>
class linklist
{
 private:
	 link<Type>* first;
 public:
	 linklist();
	 ~linklist();
	 void addData(Type);
	 void deleteData(Type);
	 void display();
};
/////////////////////////////////////
template <class Type>

linklist<Type>::linklist()
{ 
 first = NULL;
}
////////////////////////////////////////
template <class Type>

linklist<Type>::~linklist()
{
 link<Type>* temp, *currentPtr = first;
 if(first)
 {
  while(currentPtr)
  {
   temp = currentPtr;
   currentPtr = currentPtr->next;
   delete(temp);
  }
 }
}
/////////////////////////////////////
template <class Type>

void linklist<Type>::addData(Type d)
{
 if(!first)
	{
	 first = new link<Type>;
	 first->data = d;
	 first->next = NULL;
	 first->prev = NULL;
	}
 else
 {
  link<Type>* newlink = new link<Type>, *temp = first;
  newlink->data = d;

  while(temp->next)
	   temp = temp->next;
  
  temp->next = newlink;
  newlink->prev = temp;
  newlink->next = NULL;
 }
}
///////////////////////////////////////
template <class Type>

void linklist<Type>::display()
{
 link<Type>* current = first;
 while(current)
 {
  cout<<current->data<<endl;
  current = current->next;
 }
}
////////////////////////////////////
template <class Type>

void linklist<Type>::deleteData(Type d)
{
 bool f = true;
 if(!first)
	cout<<"\n Error: LINK's EMPTY!!!"<<endl;
 else
 {
  link<Type>* current = first, *temp = current;
  while(current)
	{
     (f) ? (temp = current->next) : (f = true); 

	 if(current->data == d)
		{
		 if(current == first)
		 {
		  link<Type>* fPtr = first;
		  first = first->next;
		  first->prev = NULL;
		  delete(fPtr);
		 }
		 else
		 {
		  if(current->next == NULL)
			 (current->prev)->next = NULL;
		  else
		  {
		   (current->next)->prev = current->prev;	
		   (current->prev)->next = current->next;
		  }
		  temp = current->next;
		  delete(current);
		  f = false;
		 }
		}
	 current = temp;
	}
  }
}
/////////////////////////////////////////
//////*************************//////////
/////////////////////////////////////////
int main()
{
 linklist<double> ld;
 
 cout<<"\n ***TYPE double***\n";

 ld.addData(12.989);
 ld.addData(13.008);
 ld.addData(14.089);
 ld.addData(15.067);
 ld.addData(16.077);
 ld.addData(17.087);
 
 ld.display();

 ld.deleteData(14.089);
 ld.deleteData(16.077);
 ld.deleteData(17.087);
 ld.deleteData(12.989);

 cout<<"\n Delete: 14.089, 16.077, 17.087, 12.989:\n";
 ld.display();

 cout<<"\n ***TYPE char***\n";

 linklist<char> lch;

 lch.addData('L');
 lch.addData('A');
 lch.addData('L');
 lch.addData('L');
 lch.addData('L');
 lch.addData('F');
 lch.addData('L');
 lch.addData('L');
 lch.addData('L');
 lch.addData('O');
 lch.addData('O');
 lch.addData('L');
 lch.addData('A');
 lch.addData('W');
 lch.addData('L');
 lch.addData('L');
 lch.addData('L');
 lch.addData('A');
 lch.addData('W');
 
 lch.display();

 lch.deleteData('F');
 lch.deleteData('O');
 lch.deleteData('L');
 lch.deleteData('W');
 
 cout<<"\n Delete: F, O, L, W:\n";
 lch.display();

 return 0;
}
