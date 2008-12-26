#include "PoiskDLL.h"

ListF*  ListF::del( ListF*  delt, ListF* fest)
{
  ListF *temp = fest;
  if ( temp == delt)
  {
    temp = delt->next;
    delete(delt);
    return temp;
  }
  else
  {
    while ( temp->next != delt)
    {
      temp = temp->next;
    }
    temp->next = delt->next;
    delete(delt);
    return fest;
  }
}

ListF*  ListF::add(WIN32_FIND_DATA *WFD, HANDLE *HD, LPCSTR *PathP, ListF *fest)
{
  ListF *temp = new ListF();
  temp->next	= fest;
  temp->HD	= *HD;
  strcpy(temp->PathP, *PathP);
  temp->WFD	= *WFD;
  return temp;
}

void ListF::WrCons(ListF *lf)
{
  ListF *temp;
  temp = lf;
  while(temp)
  {
    std::cout<<"\n Path -> "<<temp->PathP;
    std::cout<<"\t   "<<temp->WFD.cFileName;
    temp = temp->next;
  };
}
