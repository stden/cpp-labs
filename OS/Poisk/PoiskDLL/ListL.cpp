//            ListL.cpp

#include "PoiskDLL.h"

ListL* ListL::add(ListF*  lf, ListL*  fest) {
  ListL* temp  = new ListL();
  temp->next   = fest;
  temp->spisok = lf;
  return temp;
}

void   ListL::WrCons(ListL* ll) {
  ListL* temp;
  temp = ll;

  while(temp) {
    std::cout << "\n\n******************************\n\n";
    ListF::WrCons(temp->spisok);
    temp = temp->next;
  };
}