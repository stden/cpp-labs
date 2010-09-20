// ����: CMsg.h
// ���������� ������ "���������"
// �����: ������� �. ��. ��. 7304
// ����: 20.09.2010 ��������: 1.0



#include "CMsg.h"
#include <iostream.h>


int CMessage :: current = 0;
int CMessage :: total = 0;
int CMessage :: debug = 0;


CMessage :: CMessage(int _FromID, int _ToID, int _Type, const CInfo& _Info, int _dir) :
FromID(_FromID), ToID(_ToID), Type(_Type), Info(_Info), id(++total) {

++current;

 if (debug) {
         cout << InterpritateType(Type)<< " Message #" << id << " created"<<endl;
         if (direction == Server_to_Client) cout << "From server #" <<FromID<<"to client #"<<ToID<<endl;
         else cout << "From client #" <<FromID<<"to server #"<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


 }

}

CMessage :: CMessage(const CMessage &msg)
	  :id(++total), FromID(msg.GetFromID()), ToID(msg.GetToID()), Type(msg.GetType()), Info(msg.GetInfo()),
          direction(msg.GetDirection()) {

  ++current;


  if (debug) {
         cout << InterpritateType(Type)<< " Message #" << id << " copied"<<endl;
         if (direction == Server_to_Client) cout << "From server #" <<FromID<<"to client #"<<ToID<<endl;
         else cout << "From client #" <<FromID<<"to server #"<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


 }
}

CMessage :: ~CMessage() {
--current;

 if (debug) {
         cout << InterpritateType(Type)<< " Message #" << id << " deleted"<<endl;
         if (direction == Server_to_Client) cout << "From server #" <<FromID<<"to client #"<<ToID<<endl;
         else cout << "From client #" <<FromID<<" to server #"<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


 }


}

void CMessage :: SetFromID(int _FromID){
	FromID = _FromID;
}

void CMessage :: SetToID(int _ToID){
	ToID = _ToID;
}

void CMessage :: SetInfo(const CInfo& _Info){
	Info = _Info;
}

void CMessage :: SetType(int _Type){
	Type = _Type;
}

void CMessage :: SetDirection(int _dir){
	direction = _dir;
}

const char* CMessage :: InterpritateType (int type){
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
         if (direction == Server_to_Client) cout << "from server #" <<FromID<<" to client #"<<ToID<<endl;
         else cout << "from client #" <<FromID<<" to server #"<<ToID<<endl;
         cout << "Info = ";Info.Print(); cout<<endl;


}



