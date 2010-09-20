// Файл: CServer.cpp
// Реализация класса "сервер"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CList.h"
#include "CListN.h"
#include "CServer.H"
#include <iostream.h>
#include <conio.h>

static const int Server_Do_Confirmation = 0;

int CServer :: current = 0;
int CServer :: total = 0;
int CServer :: debug = 0;

CServer :: CServer() : id(++total) {
  ++current;
  if (debug) {
    cout <<"Server #"<<id<<" created"<<endl;
    cout << "Total number of servers = " << total << endl
      << "Current number of servers = " << current << endl;
  }
}

CServer :: ~CServer() {
  UnregisterAll();
  --current;
  if (debug) {
    cout <<"Server #"<<id<<" deleted"<<endl;
    cout << "Total number of servers = "<<total<<endl
      <<"Current number of servers = "<<current<<endl;
  }
}


CClient* CServer :: GetClientByID(int _id) {
  ClientList.GetFirst();
  for (int i = 0; i < ClientList.GetSize();i++,ClientList.NextCur()) {
    if (ClientList.GetCur()->GetValue()->getID() == _id)
      return ClientList.GetCur()->GetValue();
  }

  return 0;
}

int CServer :: Client_Count() const {
  return ClientList.GetSize();
}


void CServer :: Register(CClient *client)
{
  if (client == NULL) {
    cout << "Server #"<<id<<endl
      <<"Failed to register client due to wrong address"<<endl;
  }
  else   {
    if (GetClientByID(client->getID()) != NULL) {
      cout << "Client #" << client->getID() 
        << " already registered on server #"<<id<<endl;
    }
    else {

      ClientList.Append(new CLNode<CClient*>(client));
      if (client->GetServerByID(id) == NULL)
      {
        client->Register(this);
  cout << "Client #" << client->getID() << " was registered on server #"
    << id<<endl;
      }
    }
  }
}


void CServer :: Unregister(int _id) {
  CClient* client = GetClientByID(_id);
  if (client == NULL) {
    cout << "Client #"<<_id<< " can not unregister from server #"<<id<<endl
      <<"cause it does not registered on it"<<endl;
  }
  else {
    ClientList.ExcludeCur();
    if (client->GetServerByID(id) != NULL) {
      client->Unregister(id);
      cout << "Client #"<< client->getID() <<" was unregistered from server #"<<id<<endl;
    }
  }
}

void CServer ::UnregisterAll() {

  if (ClientList.GetSize() == 0) {
    cout << "There are already no registered clients exists"<<endl;
  } else {
    ClientList.GetFirst();
    int tlen = ClientList.GetSize();
    for (int i = 0; i < tlen;i++) 
      Unregister(ClientList.GetFirst()->GetValue()->getID());
    cout << "Server #"<<id<<": unregistered all clients"<<endl;
  }
}


void CServer :: SendMessage(CMessage *msg, int _id)
{
  CClient *client = GetClientByID(_id);
  if (client != NULL) {
    msg->setFromID(id);
    msg->setToID(_id);
    msg->setDirection(Server_to_Client);
    client->ReceiveMessage(msg);
    cout << "Server #" << id << ": sent message to client #"<<_id<<endl;
  }
  else {
    cout << "Server #" << id << " could not send messages to client #"<<_id<<endl
      <<"cause it not registered on it"<<endl;
    //   delete msg;
  }
}


void CServer :: SendMessageToAll(int _type, double _info) {
  CMessage* msg = new CMessage(id,1,_type,_info,Server_to_Client);
  if (ClientList.GetSize() != 0) {
    msg->setDirection(Server_to_Client);
    int tlen = ClientList.GetSize();
    for (int i = 0; i < tlen; i ++) {
      msg->setFromID(id);
      msg->setToID(ClientList.GetElemByNum(i)->GetValue()->getID());
      ClientList.GetElemByNum(i)->GetValue()->ReceiveMessage(msg);
    }
    cout << "Server #"<<id<< ": sent message to all clients " << endl;
  }
  else {
    cout << "Server #" << id 
      << " could not send messages to clients cause they are not registered on it"<<endl;
  }
  // delete msg;
}

void CServer :: SendMessageToAll(CMessage *msg) {
  SendMessageToAll(msg->getType(),msg->getInfo());
}

void CServer :: SendMessage(int _type, double _info, int _id) {
  CClient *client = GetClientByID(_id);
  if (client != NULL) {
    CMessage *msg = new CMessage(id,_id,_type,_info,Server_to_Client);
    msg->setFromID(id);
    msg->setToID(_id);
    msg->setType(_type);
    msg->setInfo(_info);
    msg->setDirection(Server_to_Client);
    client->ReceiveMessage(msg);
    cout << "Server #" << id << ": sent message to client #" << _id << endl;
    delete msg;
  } else {
    cout << "Server #" << id << ": could not send messages to client #"
      << _id << "cause it not registered on it"<<endl;
  }
}

void CServer :: ReceiveMessage(CMessage *msg) {
  CClient* client = GetClientByID(msg->getFromID());
  if (client != NULL) {
    cout << "Server #" << id << ": recived message from client #" << client->getID() << endl;
    msg->Print();
    if (msg->getType() > 0 && Server_Do_Confirmation) {
      CMessage *msg1 = new CMessage(*msg);
      msg1->setType(Confirmation); //код подтверждения приёма сообщения
      msg1->setDirection(Server_to_Client);
      SendMessage(msg1, client->getID());
      delete msg1;
    }
  } else {
    cout << "Server #" << id << ": could not recive message from unknown client"<<endl;
  }
  // delete msg;
}

void CServer::Print() const {
  cout << "Server: "<< endl
    << "  ID = " << id << endl
    << "  Current number of servers = " << current << endl
    << "  Number of registered clients = " << ClientList.GetSize() << endl
    << "  List of clients : " << endl;
  if (ClientList.GetSize() == 0) {
    cout << "List is empty"<<endl;
  } else  {
    ClientList.GetFirst();
    for (int i = 0;i < ClientList.GetSize(); i++,ClientList.NextCur()) 
      cout << "#" << (i+1) << " Server, ID = " << ClientList.GetCur()->GetValue()->getID() << endl;
  }
}
