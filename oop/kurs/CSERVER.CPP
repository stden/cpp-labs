//Файл : CServer.cpp
//Реализация класса "сервер"
//Автор : Волынко Е. ст. гр. 7304
//Дата : 1.06.2010 Редакция : 1.0


#include "CList.h"
#include "CListN.h"
#include "CServer.H"
#include <iostream.h>
#include <conio.h>


unsigned int CServer :: current = 0;
unsigned int CServer :: total = 0;
unsigned int CServer :: debug = 0;

CServer :: CServer() : id(++total) {

  ++current;
  if (debug) {
        cout <<"Server with id = "<<id<<" created"<<endl;
        cout << "Total number of servers = "<<total<<endl
        <<"Current number of servers = "<<current<<endl;
  }
}

CServer :: ~CServer() {

  UnregisterAll();
  --current;
  if (debug) {
        cout <<"Server with id = "<<id<<" deleted"<<endl;
        cout << "Total number of servers = "<<total<<endl
        <<"Current number of servers = "<<current<<endl;
  }
}


CClient* CServer :: GetClientByID(unsigned int _id) {
  ClientList.GetFirst();
  for (int i = 0; i < ClientList.GetSize();i++,ClientList.NextCur()) {
         if (ClientList.GetCur()->GetValue()->GetID() == _id)
         return ClientList.GetCur()->GetValue();
  }

  return 0;
}

unsigned int CServer :: Client_Count() const {
  return ClientList.GetSize();
}


void CServer :: Register(CClient *client)
{
  if (client == NULL) {
    cout << "Server with id = "<<id<<endl
      <<"Failed to register client due to wrong address"<<endl;
  }
  else   {
    if (GetClientByID(client->GetID()) != NULL) {
       cout << "Client with id = "<<client->GetID()<<endl
      <<"Already registered on server with id = "<<id<<endl;
    }
    else {

      ClientList.Append(new CLNode<CClient*>(client));
      if (client->GetServerByID(id) == NULL)
      {
  client->Register(this);
  cout << "Client with id = " << client->GetID() << " was registered on server with id = "
       << id<<endl;
      }
    }
  }
}


void CServer :: Unregister(unsigned int _id) {
  CClient* client = GetClientByID(_id);
  if (client == NULL) {
    cout << "Client with id = "<<client->GetID()<< " can not unregister from server with id = "<<id<<endl
    <<"cause it does not registered on it"<<endl;
  }
  else {
      ClientList.ExcludeCur();
    if (client->GetServerByID(id) != NULL) {
      client->Unregister(id);
      cout << "Client with id = "<<client->GetID()<<" was unregistered from server with id = "<<id<<endl;
    }
  }
}

void CServer ::UnregisterAll() {

  if (ClientList.GetSize() == 0) {
    cout << "There are already no registered clients exists"<<endl;
  }

  else {
    ClientList.GetFirst();
    int tlen = ClientList.GetSize();
    for (int i = 0; i < tlen;i++) {
//            ClientList.GetFirst();
           /* ClientList.ExcludeCur();*/Unregister(ClientList.GetFirst()->GetValue()->GetID());
    }
    cout << "Server with id = "<<id<<" unregistered all clients"<<endl;
  }
}


void CServer :: SendMessage(CMessage *msg, unsigned int _id)
{
  CClient *client = GetClientByID(_id);
  if (client != NULL) {
    msg->SetFromID(id);
    msg->SetToID(_id);
    msg->SetDirection(0);
    client->ReceiveMessage(msg);
  //  cout << "Server with id = "<<id<< " sent message to client with id = "<<_id<<endl;
  }
  else {
     cout << "Server with id = " << id<< " could not send messages to client with id = "<<_id<<endl
    <<"cause it not registered on it"<<endl;
    getch();
 //   delete msg;
  }
}


void CServer :: SendMessageToAll(unsigned int _type, const CInfo& _info)
{
  CMessage* msg = new CMessage(id,1,_type,_info,0);
  if (ClientList.GetSize() != 0) {

    msg->SetDirection(0);

    int tlen = ClientList.GetSize();
    for (int i = 0; i < tlen; i ++) {
        msg->SetFromID(id);
        msg->SetToID(ClientList.GetElemByNum(i)->GetValue()->GetID());
        ClientList.GetElemByNum(i)->GetValue()->ReceiveMessage(msg);
    }

  //  cout << "Server with id = "<<id<< " sent message to all clients "<<endl;
  }
  else {
     cout << "Server with id = " << id<< "could not send messages to clients"<<endl
    <<"cause they are not registered on it"<<endl;
    getch();
  }
 // delete msg;
}

void CServer :: SendMessageToAll(CMessage *msg)
{
  SendMessageToAll(msg->GetType(),msg->GetInfo());
}

void CServer :: SendMessage(unsigned int _type, const CInfo& _info, unsigned int _id)
{
  CClient *client = GetClientByID(_id);
  CMessage *msg = new CMessage;
  if (client != NULL) {
    msg->SetFromID(id);
    msg->SetToID(_id);
    msg->SetType(_type);
    msg->SetInfo(_info);
    msg->SetDirection(0);
    client->ReceiveMessage(msg);
   // cout << "Server with id = "<<id<< " sent message to client with id = "<<_id<<endl;
  }
  else {
     cout << "Server with id = " << id<< "could not send messages to client with id = "<<_id<<endl
    <<"cause it not registered on it"<<endl;
    getch();

  }
  delete msg;

}


void CServer :: ReceiveMessage(CMessage *msg) {
  CClient* client = GetClientByID(msg->GetFromID());
  if (client != NULL)
  {
    cout << "Server with id = "<<id<< " recived message"<<endl
    <<"from client with id = "<<client->GetID()<<endl;
   msg->Print();
   getch();


    if (msg->GetType() > 0 && msg->GetType() < 2)
    {
     CMessage *msg1 = new CMessage(*msg);
     msg1->SetType(0); //код подтверждения приёма сообщения
     msg1->SetDirection(0);
     SendMessage(msg1, client->GetID());
     delete msg1;

    }

    if (msg->GetType() >= 2)
    {
     CMessage *msg1 = new CMessage(*msg);
     msg1->SetType(msg->GetType()); //код подтверждения приёма сообщения
     msg1->SetInfo(msg->GetInfo());
     msg1->SetDirection(0);
     SendMessage(msg1, client->GetID());
     delete msg1;

    }
  }
  else
  {
    cout << "Server with id = " <<id<< "could not recive message from unknown client"<<endl;
  }
 // delete msg;
}


void CServer::Print() const{
  cout << "Server : "<<endl
       << "ID = "<<id<<endl
       << "Current number of servers = "<<current<<endl
       << "Number of registered clients = "<<ClientList.GetSize() <<endl
       << "List of clients : "<<endl;

  if (ClientList.GetSize() == 0) {
    cout << "List is empty"<<endl;
  }

  else  {
    ClientList.GetFirst();
    for (int i = 0;i < ClientList.GetSize(); i++,ClientList.NextCur()) {
        cout << "#"<< i+1<<" Server, ID = "<<ClientList.GetCur()->GetValue()->GetID()<<endl;
    }
  }
}

