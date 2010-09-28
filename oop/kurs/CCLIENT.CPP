// Файл: CClient.h
// Реализация класса "клиент"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CClient.H"
#include "CList.h"
#include "CListN.h"
#include <iostream.h>
#include <conio.h>
#include <assert.h>

int CClient :: total = 0;

CClient :: CClient() : id(++total) {
  cout << "Client #" << id << " is created" <<
       " total = " << total << endl;
}

CClient :: ~CClient() {
  Unregister();
  cout << "Client #" << id << " is deleted" <<
       " total = " << total << endl;
}

CServer* CClient :: getServer() {
  return server;
}

void CClient :: Register(CServer *server) {
  if (server == NULL)  {
    cout << "Client #" << id << endl
         << "Failed to register on server due to wrong address" << endl;
  } else  {
    if (getServer() != NULL) {
      cout << "Client #" << id << " already registered on server" << endl;
    } else {
      this->server = server;
      if (server->GetClientByID(id) == NULL) {
        server->Register(this);
        cout << "Client #" << id << " was registered on server" << endl;
      }
    }
  }
}

void CClient::Unregister() {
  if (getServer() == NULL) {
    cout << "Client #" << id << " can not unregister from server"
         << "cause it does not registered on it" << endl;
  } else {
    server = NULL;
    if (server->GetClientByID(id) != NULL) {
      server->Unregister(id);
      cout << "Client #" << id << " was unregistered from server" << endl;
    }
  }
}

// Собственно отправка сообщения клиенту
// Все остальные варианты SendMessage только подготоваливают
// сообщения разных видов и вызывают данный метод
void CClient::SendMessage(CMessage *msg) {
  assert(msg->getFromID() == id);
  assert(msg->getDirection() == Client_to_Server ||
         msg->getDirection() == Client_to_Client);
  if (server != NULL) {
    if (msg->getDirection() == Client_to_Server)
      cout << "Client #" << id << " sent " << *msg << " to server "
           << endl;
    else
      cout << "Client #" << id << " sent " << *msg << " to client #" <<
           msg->getToID() << endl;
    server->ReceiveMessage(msg);
  } else {
    cout << "Client #" << id << " could not send messages to server "
         << " cause it not registered on it" << endl;
  }
}

void CClient::SendMessage(int _type, const CInfo&  _info, int _id) {
  CMessage msg(id, _id, _type, _info, Client_to_Server);
  assert(msg.getFromID() == id);
  assert(msg.getToID() == _id);
  assert(msg.getType() == _type);
  assert(msg.getDirection() == Client_to_Server);
  SendMessage(&msg);
}

void CClient::ReceiveMessage(CMessage *msg) {
  // Проверяем кооректность пришедшего сообщения
  assert(msg->getDirection() == Server_to_Client ||
         msg->getDirection() == Client_to_Client);
  assert(msg->getToID() == id);

  if (server != NULL)  {
    if (msg->getDirection() == Server_to_Client)
      cout << endl << "Client #" << id << " recived " << *msg << " from server"
           << endl << endl;
    else
      cout << endl << "Client #" << id << " recived " << *msg << " from client #"
           << msg->getFromID() << endl << endl;
    if (msg->getType() > 1)  {
      // отправка подтверждения о приёме сообщения
      CMessage m1(*msg);
      m1.setToID(1);
      m1.setFromID(id);
      m1.setType(CONFIRMATION); //код подтверждения приёма сообщения
      m1.setDirection(Client_to_Server);
      SendMessage(&m1);
      Action(msg->getType(), msg->getInfo());
      //отправка подтверждения о выполнении действия
      SendMessage(&CMessage(id, 1, REPORT, msg->getInfo(), Client_to_Server));
    }
  } else
    cout << "Client #" << id << " could not recive message from unknown server"
         << endl << endl;
}

void CClient::Action(int _code, const CInfo& _info) {
  switch (_code) {
    case 2:
      cout << "Client is handling action with code = " << _code
           << " Info = " << _info << endl << endl;
      break;
    case 3:
      cout << "Client is handling action with code = " << _code
           << " Info = " << _info << endl << endl;
      break;
    default:
      cout << "Client could not handle action with code = " << _code
           << " case of unknown code " << endl << endl;
      break;
  }
}

