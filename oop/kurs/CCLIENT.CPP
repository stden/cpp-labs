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

  if (debug)
  {
    cout << "Client with id = " << id << " is created" <<endl
   << "total = " << total << ", current = " << current<<endl;
  }
}

CClient :: ~CClient()
{

  UnregisterAll();
  --current;

  if (debug)
  {
    cout << "Client with id = " << id << " is deleted" <<endl
   << "total = " << total << ", current = " << current<<endl;
  }
}


CServer* CClient :: GetServerByID(int _id)
{
   ServerList.GetFirst();
   for (int i = 0; i < ServerList.GetSize(); i++,ServerList.NextCur()) {
        if (ServerList.GetElemByNum(i)->GetValue()->getID() == _id)
        return  ServerList.GetCur()->GetValue();
   }

  return 0;
}


int CClient :: ServerCount() const {
  return ServerList.GetSize();
}


void CClient :: Register(CServer *server) {
  if (server == NULL)  {
      cout << "Client with id = "<<id<<endl
      <<"Failed to register on server due to wrong address"<<endl;
  }

  else  {
    if (GetServerByID(server->getID()) != NULL) {
         cout << "Client with id = "<<id<<endl
      <<"Already registered on server with id = "<<server->getID()<<endl;
    }

    else {

      ServerList.Append(new CLNode<CServer*>(server));

      if (server->GetClientByID(id) == NULL) {
  server->Register(this);
  cout << "Client with id = " << id << " was registered on server with id = "
       << server->getID()<<endl;
      }
    }
  }
}


void CClient::Unregister(int _id)
{
  CServer *server = GetServerByID(_id);
  if (server == NULL) {
    cout << "Client with id = "<<id << " can not unregister from server with id = "<<server->getID()<<endl
    <<"cause it does not registered on it"<<endl;
  }
  else {

   ServerList.ExcludeCur();
    if (server->GetClientByID(id) != NULL) {
      server->Unregister(id);
      cout << "Client with id = "<<id<<" was unregistered from server with id = "<<server->getID()<<endl;
    }
  }
}


void CClient::UnregisterAll() {

  if (ServerList.GetSize() == 0) {
    cout << "There are already no registered servers exists"<<endl;
  }
  else {

    int tlen = ServerList.GetSize();
    for (int i = 0; i < tlen;i++) {
            Unregister(ServerList.GetElemByNum(i)->GetValue()->getID());
    }
    cout << "Client with id = "<<id<<" was unregistered from all servers"<<endl;
  }
}


void CClient::SendMessage(CMessage *msg, int _id)
{
  CServer *server = GetServerByID(_id);
  if (server != NULL) {
    msg->setFromID(id);
    msg->setToID(_id);
    msg->setDirection(Client_to_Server);
    server->ReceiveMessage(msg);
  //  cout << "Client with id = "<<id<< " sent message to server with id = "<<_id<<endl;
  }
  else {
    cout << "Client with id = " << id<< "could not send messages to server with id = "<<_id<<endl
    <<"cause it not registered on it"<<endl;
    getch();
   // delete msg;
  }
}

void CClient::SendMessage(int _type, const CInfo& _info, int _id)
{
  CServer *server = GetServerByID(_id);
  CMessage *msg = new CMessage;
  if (server != NULL) {
    msg->setFromID(id);
    msg->setToID(_id);
    msg->setType(_type);
    msg->setInfo(_info);
    msg->setDirection(Client_to_Server);
    server->ReceiveMessage(msg);
   // cout << "Client with id = "<<id<< " sent message to server with id = "<<_id<<endl;
  }
  else {
    cout << "Client with id = " << id<< "could not send messages to server with id = "<<_id<<endl
    <<"cause it not registered on it"<<endl;
    getch();

  }
  delete msg;
}


void CClient::ReceiveMessage(CMessage *msg)
{
 CServer *server = GetServerByID(msg->GetFromID());
 if (server != NULL)  {
   cout <<endl<< "Client with id = "<<id<< " recived message"<<endl
   <<"from server with id = "<<server->getID()<<endl;
   msg->Print();
   getch();

   if (msg->GetType() > 1)  {
     /*CMessage *msg1 = new CMessage(*msg);
     msg1->setType(0); //код подтверждения приёма сообщения
     msg1->setDirection(Client_to_Server);
     SendMessage(msg1, server->getID()); //отправка подтверждения о приёме
           //сообщения */
     Action (msg->GetType(), msg->GetInfo());
     //отправка подтверждения о выполнении действия
     CMessage *msg2 = new CMessage();
     msg2->setType(1);
     msg2->setDirection(Client_to_Server);
     SendMessage(msg2, server->getID());
     //delete msg2;
   }
 }
 else {
   cout << "Client with id = " <<id<< "could not recive message from unknown server"<<endl;
 }
 //delete msg;
}

void CClient::Action(int _code, const CInfo& _info)
{

  switch (_code)
  {
    case 2:
      cout << "Client is handling action with code = "<<_code<<endl
      << "And parametrs = ";_info.Print(); cout <<endl;

    break;

    case 3:
     cout << "Client is handling action with code = "<<_code<<endl
      << "And parametrs = ";_info.Print(); cout <<endl;
    break;

    default:
      cout << "Client could not handle action with code = "<<_code<<endl
      << "case of unknown code "<< endl<<endl;
    break;
  }
}


void CClient :: Print() const {
  cout << "Client : "<<endl
       << "ID = "<<id<<endl
       << "Current number of clients = "<<current<<endl
       << "Number of registered servers = "<<ServerList.GetSize() <<endl
       << "List of servers : "<<endl;

  if (ServerList.GetSize() == 0) {
    cout << "List is empty"<<endl;
  }

  else  {
    ServerList.GetFirst();
    for (int i = 0;i < ServerList.GetSize(); i++,ServerList.NextCur()) {
        cout << "#"<< i+1<<" Server, ID = "<<ServerList.GetCur()->GetValue()->getID()<<endl;
    }
  }
}





