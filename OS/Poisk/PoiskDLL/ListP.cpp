#include "PoiskDLL.h"


ListP*  ListP::add(LPCSTR *PatH, ListP *fest)
{
	    ListP *temp = new ListP();
		temp->next	= fest;
		strcpy(temp->PathP, *PatH);
		return temp;
}

ListP*  ListP::del( ListP*  delt, ListP* fest)
{
	    ListP *temp = fest;

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

void ListP::WrCons(ListP *lp)
{
	ListP *temp;
	temp = lp;
	while(temp)
	{
		std::cout<<"\n Path -> "<<temp->PathP;
		temp = temp->next;
	};
}



