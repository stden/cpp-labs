// Файл: CSView.cpp
// Реализация класса "сервер-вид"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CSView.h"

CServerView :: CServerView(CPoint _P1,double _P1P2,CPoint _P3)
	: CView(_P1,_P1P2,_P3){

}

CServerView :: CServerView(const CView& view)
	: CView(view){


}

CServerView :: ~CServerView() {

}

void CServerView :: ReciveMessage(CMessage* msg){
  CServer :: ReceiveMessage(msg);
	if(msg->GetType() > 2){
            CServer :: SendMessage(msg->GetType(),msg->GetInfo(),msg->GetFromID());
        }
}

void CServerView :: Print() const {
        CView :: Print();
        CServer :: Print();
        cout << "----------------------";
        cout << endl<< endl;
}
