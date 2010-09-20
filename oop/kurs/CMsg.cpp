//Файл : CMsg.h
//Реализация класса "сообщение"
//Автор : Монько А.О.
//Дата : 1.06.2010 Редакция : 1.0



#include "CMsg.h"
#include <iostream.h>


unsigned int CMessage :: current = 0;
unsigned int CMessage :: total = 0;
unsigned int CMessage :: debug = 0;


CMessage :: CMessage(unsigned int _FromID, unsigned int _ToID, int _Type, const CInfo& _Info, unsigned int _dir) :
FromID(_FromID), ToID(_ToID), Type(_Type), Info(_Info), id(++total) {

++current;

 if (debug) {
         cout << InterpritateType(Type)<< " Message with id = " << id << " created"<<endl;
         if (direction == 0) cout << "From server with id = " <<FromID<<"to client with id = "<<ToID<<endl;
         else cout << "From client with id = " <<FromID<<"to server with id = "<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


 }

}

CMessage :: CMessage(const CMessage &msg)
	  :id(++total), FromID(msg.GetFromID()), ToID(msg.GetToID()), Type(msg.GetType()), Info(msg.GetInfo()),
          direction(msg.GetDirection()) {

  ++current;


  if (debug) {
         cout << InterpritateType(Type)<< " Message with id = " << id << " copied"<<endl;
         if (direction == 0) cout << "From server with id = " <<FromID<<"to client with id = "<<ToID<<endl;
         else cout << "From client with id = " <<FromID<<"to server with id = "<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


 }
}

CMessage :: ~CMessage() {
--current;

 if (debug) {
         cout << InterpritateType(Type)<< " Message with id = " << id << " deleted"<<endl;
         if (direction == 0) cout << "From server with id = " <<FromID<<"to client with id = "<<ToID<<endl;
         else cout << "From client with id = " <<FromID<<" to server with id = "<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


 }


}

void CMessage :: SetFromID(unsigned int _FromID){
	FromID = _FromID;
}

void CMessage :: SetToID(unsigned int _ToID){
	ToID = _ToID;
}

void CMessage :: SetInfo(const CInfo& _Info){
	Info = _Info;
}

void CMessage :: SetType(unsigned int _Type){
	Type = _Type;
}

void CMessage :: SetDirection(unsigned int _dir){
	direction = _dir;
}

const char* CMessage :: InterpritateType (unsigned int type){
	switch(type){
		case 0 :{
			return "Confirm";
		}break;
		case 1 :{
			return "Report";
		}break;

		default:{
			return "Action";
		}
	}
}

void CMessage :: Print () const{
         cout <<endl<< InterpritateType (Type)<<" message ";
         if (direction == 0) cout << "from server with id = " <<FromID<<" to client with id = "<<ToID<<endl;
         else cout << "from client with id = " <<FromID<<" to server with id = "<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


}



