// Файл: CClient.h
// Реализация класса "клиент"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CClient.H"
#include <iostream.h>
#include <conio.h>
#include <assert.h>
#include "debug.h"

int CClient :: total = 0;

CClient :: CClient(int id) : m_id(id) {
  total++;
  cout << "Client #" << getID() << " is created" <<
       " total = " << getTotal() << endl;
}

CClient :: ~CClient() {
  total--;
  Unregister();
  cout << "Client #" << getID() << " is deleted" <<
       " total = " << getTotal() << endl;
}

CServer* CClient :: getServer() {
  return server;
}

void CClient :: Register(CServer *server) {
  if (server == NULL)  {
    cout << "Client #" << getID() << endl
         << "Failed to register on server due to wrong address" << endl;
  } else  {
    if (getServer() != NULL) {
      cout << "Client #" << getID() << " already registered on server" << endl;
    } else {
      this->server = server;
      if (server->GetClientByID(getID()) == NULL) {
        server->Register(this);
        cout << "Client #" << getID() << " was registered on server" << endl;
      }
    }
  }
}

void CClient::Unregister() {
  if (getServer() == NULL) {
    cout << "Client #" << getID() << " can not unregister from server"
         << "cause it does not registered on it" << endl;
  } else {
    server = NULL;
    if (server->GetClientByID(getID()) != NULL) {
      server->Unregister(getID());
      cout << "Client #" << getID() << " was unregistered from server" << endl;
    }
  }
}

// Собственно отправка сообщения клиенту
// Все остальные варианты SendMessage только подготоваливают
// сообщения разных видов и вызывают данный метод
void CClient::SendMessage(CMessage *msg) {
  assert(msg->getFromID() == getID());
  assert(msg->getDirection() == Client_to_Server ||
         msg->getDirection() == Client_to_Client);
  if (server != NULL) {
    if (msg->getDirection() == Client_to_Server)
      cout << "Client #" << getID() << " sent " << *msg << " to server "
           << endl;
    else
      cout << "Client #" << getID() << " sent " << *msg << " to client #" <<
           msg->getToID() << endl;
    server->ReceiveMessage(msg);
  } else {
    cout << "Client #" << getID() << " could not send messages to server "
         << " cause it not registered on it" << endl;
  }
}

void CClient::SendMessage(int _type, const CInfo&  _info, int _id) {
  CMessage msg(getID(), _id, _type, _info, Client_to_Server);
  assert(msg.getFromID() == getID());
  assert(msg.getToID() == _id);
  assert(msg.getType() == _type);
  assert(msg.getDirection() == Client_to_Server);
  SendMessage(&msg);
}

void CClient::ReceiveMessage(CMessage *msg) {
  // Проверяем кооректность пришедшего сообщения
  assert(msg->getDirection() == Server_to_Client ||
         msg->getDirection() == Client_to_Client);
  assert(msg->getToID() == getID());

  if (server != NULL)  {
    if (msg->getDirection() == Server_to_Client)
      cout << endl << "Client #" << getID() << " recived " << *msg << " from server"
           << endl << endl;
    else
      cout << endl << "Client #" << getID() << " recived " << *msg << " from client #"
           << msg->getFromID() << endl << endl;
    if (msg->getType() > 1)  {
      // отправка подтверждения о приёме сообщения
      CMessage m1(*msg);
      m1.setToID(1);
      m1.setFromID(getID());
      m1.setType(CONFIRMATION); //код подтверждения приёма сообщения
      m1.setDirection(Client_to_Server);
      SendMessage(&m1);
      Action(msg->getType(), msg->getInfo());
      //отправка подтверждения о выполнении действия
      SendMessage(&CMessage(getID(), 1, REPORT, msg->getInfo(), Client_to_Server));
    }
  } else
    cout << "Client #" << getID() << " could not recive message from unknown server"
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

