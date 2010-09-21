// Файл: CClient.h
// Реализация класса "клиент"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CClient.H"
#include "CList.h"
#include "CListN.h"
#include <iostream.h>
#include <conio.h>

int CClient :: current = 0;
int CClient :: total = 0;
int CClient :: debug = 0;

CClient :: CClient() : id(++total) {
  ++current;
  if (debug) {
    cout << "Client #" << id << " is created" <<endl
      << "total = " << total << ", current = " << current<<endl;
  }
}

CClient :: ~CClient() {
  UnregisterAll();
  --current;
  if (debug) {
    cout << "Client #" << id << " is deleted" <<endl
      << "total = " << total << ", current = " << current<<endl;
  }
}

CServer* CClient :: GetServerByID(int _id) {
  ServerList.goFirst();
  for (int i = 0; i < ServerList.size(); i++,ServerList.goNext())
    if (ServerList.getElem().getValue()->getID() == _id)
      return  ServerList.getElem().getValue();
  return 0;
}

int CClient :: ServerCount() const {
  return ServerList.size();
}

void CClient :: Register(CServer *server) {
  if (server == NULL)  {
    cout << "Client #"<<id<<endl
      <<"Failed to register on server due to wrong address"<<endl;
  } else  {
    if (GetServerByID(server->getID()) != NULL) {
      cout << "Client #" << id 
        <<" already registered on server #" << server->getID() << endl;
    } else {
      ServerList.insert(server);
      if (server->GetClientByID(id) == NULL) {
        server->Register(this);
        cout << "Client #" << id << " was registered on server #"
          << server->getID()<<endl;
      }
    }
  }
}

void CClient::Unregister(int _id) {
  CServer *server = GetServerByID(_id);
  if (server == NULL) {
    cout << "Client #" << id << " can not unregister from server #"
      << server->getID() << endl
      <<"cause it does not registered on it"<<endl;
  } else {
    ServerList.dispose();
    if (server->GetClientByID(id) != NULL) {
      server->Unregister(id);
      cout << "Client #" << id<<" was unregistered from server #" << server->getID()<<endl;
    }
  }
}

void CClient::UnregisterAll() {

  if (ServerList.size() == 0) {
    cout << "There are already no registered servers exists"<<endl;
  }
  else {
    ServerList.goFirst();
    if(ServerList.getCurrent()!=NULL)
      do{
	Unregister(ServerList.getElem().getValue()->getID());
      } while(ServerList.goNext());
    cout << "Client #"<<id<<" was unregistered from all servers"<<endl;
  }
}


void CClient::SendMessage(CMessage *msg, int _id) {
  CServer *server = GetServerByID(_id);
  if (server != NULL) {
    msg->setFromID(id);
    msg->setToID(_id);
    msg->setDirection(Client_to_Server);
    server->ReceiveMessage(msg);
    cout << "Client #"<<id<< " sent message to server #"<<_id<<endl;
  } else {
    cout << "Client #" << id<< "could not send messages to server #"<<_id<<endl
      <<"cause it not registered on it"<<endl;
    // delete msg;
  }
}

void CClient::SendMessage(int _type, double _info, int _id) {
  CServer *server = GetServerByID(_id);
  CMessage *msg = new CMessage(id,_id,_type,_info,Client_to_Server);
  if (server != NULL) {
    msg->setFromID(id);
    msg->setToID(_id);
    msg->setType(_type);
    msg->setInfo(_info);
    msg->setDirection(Client_to_Server);
    server->ReceiveMessage(msg);
    cout << "Client #"<<id<< " sent message to server #"<<_id<<endl;
  }
  else {
    cout << "Client #" << id<< "could not send messages to server #"<<_id
      << " cause it not registered on it" << endl;
  }
  delete msg;
}

void CClient::ReceiveMessage(CMessage *msg) {
  CServer *server = GetServerByID(msg->getFromID());
  if (server != NULL)  {
    cout << endl << "Client #" << id << " recived message from server #" 
      << server->getID() << endl;
    msg->Print();

    if (msg->getType() > 1)  {
      // отправка подтверждения о приёме сообщения
      CMessage *msg1 = new CMessage(*msg);
      msg1->setType(Confirmation); //код подтверждения приёма сообщения
      msg1->setDirection(Client_to_Server);
      SendMessage(msg1, server->getID());
      Action (msg->getType(), msg->getInfo());
      //отправка подтверждения о выполнении действия
      SendMessage( new CMessage(msg->getToID(),msg->getFromID(),
        Report,msg->getInfo(),Client_to_Server),
        server->getID());
    }
  } else
    cout << "Client #" << id << " could not recive message from unknown server"<<endl;
  //delete msg;
}

void CClient::Action(int _code, const float _info) {
  switch (_code) {
    case 2:
      cout << "Client is handling action with code = "<<_code<<endl
        << "And parametrs = "<< _info<<endl<<endl;
      break;
    case 3:
      cout << "Client is handling action with code = "<<_code<<endl
        << "And parametrs = "<< _info<< endl<<endl;
      break;
    default:
      cout << "Client could not handle action with code = "<<_code<<endl
        << "case of unknown code "<< endl<<endl;
      break;
  }
}

void CClient :: Print() const {
  cout << "Client #" << id << endl
    << "  Current number of clients = "<<current<<endl
    << "  Number of registered servers = "<<ServerList.size() <<endl
    << "  List of servers: "<<endl;
  if (ServerList.size() == 0) {
    cout << "List is empty"<<endl;
  }
  else  {
    ServerList.goFirst();
    for (int i = 0;i < ServerList.size(); i++,ServerList.goNext()) {
      cout << "  #"<< (i+1) <<" Server,#"
	<< ServerList.getElem().getValue()->getID() << endl;
    }
  }
  cout << endl;
}