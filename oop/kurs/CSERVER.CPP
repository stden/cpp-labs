// Файл: CServer.cpp
// Реализация класса "сервер"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CServer.H"
#include <iostream.h>
#include <conio.h>
#include <assert.h>

static const int Server_Do_Confirmation = 0;

CServer :: CServer() {
  cout << "Server: created" << endl;
  assert(GetClientByID(1) == NULL);
}

CServer :: ~CServer() {
  UnregisterAll();
  cout << "Server: deleted" << endl;
}

CClient* CServer :: GetClientByID(int _id) {
  for (ClientList.goFirst();ClientList.hasNext();ClientList.goNext())
    if (ClientList.getValue()->getID() == _id)
      return ClientList.getValue();
  return NULL;
}

int CServer :: ClientCount() const {
  return ClientList.size();
}

void CServer :: Register(CClient *client) {
  if (client == NULL) {
    cout << "Server: failed to register client due to wrong address" << endl;
  } else {
    if (GetClientByID(client->getID()) != NULL) {
      cout << "Client #" << client->getID() <<
           " already registered on server" << endl;
    } else {
      int n = ClientCount();
      cout << "Server: register client #" << client->getID() << endl;
      assert(GetClientByID(client->getID()) == NULL);
      ClientList.insert(client);
      assert(GetClientByID(client->getID()) != NULL);
      assert(ClientCount() == n + 1);
      if (client->getServer() == NULL) {
        client->Register(this);
        cout << "Client #" << client->getID()
             << " was registered on server" << endl;
      }
      assert(client->getServer() != NULL);
    }
  }
}


void CServer :: Unregister(int _id) {
  CClient* client = GetClientByID(_id);
  if (client == NULL) {
    cout << "Client #" << _id << " can not unregister from server "
         << " cause it does not registered on it" << endl;
  } else {
    assert(ClientList.getValue()->getID() == _id);
    ClientList.dispose();
    if (client->getServer() != NULL) {
      client->Unregister();
      cout << "Client #" << client->getID() <<
           " was unregistered from server" << endl;
    }
    assert(client->getServer() == NULL);
  }
}

void CServer ::UnregisterAll() {
  if (ClientList.size() == 0) {
    cout << "There are already no registered clients exists" << endl;
  } else {
    while (ClientList.size() > 0) {
      ClientList.goFirst();
      CClient* cl = ClientList.getValue();
      Unregister(cl->getID());
    };
    cout << "Server: unregistered all clients" << endl;
  }
  assert(ClientList.size() == 0);
}


void CServer :: SendMessage(CMessage *msg) {
  assert(msg != NULL);
  assert(msg->getDirection() == Server_to_Client ||
         msg->getDirection() == Client_to_Client);
  if (msg->getDirection() == Server_to_Client)
    assert(msg->getFromID() == 1);

  CClient *client = GetClientByID(msg->getToID());
  if (client != NULL) {
    cout << "Server: sent " << *msg << " to client #" << msg->getToID() << endl;
    client->ReceiveMessage(msg);
  } else {
    cout << "Server could not send messages to client #"
         << msg->getToID() << " cause it not registered on it" << endl;
  }
}


void CServer :: SendMessageToAll(CMessage *msg) {
  assert(msg->getFromID() == 1);
  assert(msg->getDirection() == Server_to_Client);
  if (ClientList.size() != 0) {
    assert(msg->getDirection() == Server_to_Client);
    for (ClientList.goFirst();ClientList.hasNext();ClientList.goNext()) {
      assert(msg->getFromID() == 1);
      msg->setToID(ClientList.getValue()->getID());
      ClientList.getValue()->ReceiveMessage(msg);
    };
    cout << "Server: sent message to all clients " << endl;
  } else {
    cout << "Server: could not send messages to clients "
         << "cause they are not registered on it" << endl;
  }
}

void CServer :: ReceiveMessage(CMessage *msg) {
  assert(msg->getDirection() == Client_to_Server ||
         msg->getDirection() == Client_to_Client);
  if (msg->getDirection() == Client_to_Server)
    assert(msg->getToID() == 1);
  CClient* client = GetClientByID(msg->getFromID());
  if (client != NULL) {
    cout << "Server: recived " << *msg << " from client #" << client->getID()
         << endl << endl;
    if (msg->getDirection() == Client_to_Server &&
        msg->getType() > 0 && Server_Do_Confirmation) {
      CMessage msg1(*msg);
      msg1.setType(CONFIRMATION); //код подтверждения приёма сообщения
      msg1.setDirection(Server_to_Client);
      msg1.setToID(client->getID());
      SendMessage(&msg1);
    }
    if (msg->getDirection() == Client_to_Client) {
      CClient* dst_client = GetClientByID(msg->getToID());
      if (dst_client != NULL) {
        cout << "Server: REDIRECT to Client #" << msg->getToID() << endl;
        SendMessage(msg);
      } else {
        cout << "Server: could not send message to client "
             << msg->getToID() << endl;
      }
    }
  } else {
    cout << "Server: could not recive " << *msg << " from unknown client "
         << endl << endl;
  }
  assert(msg != NULL);
  delete msg;
}

void CServer::Print() const {
  cout << "Server: " << endl
       << "  Number of registered clients = " << ClientList.size() << endl
       << "  List of clients: " << endl;
  if (ClientList.size() == 0) {
    cout << "    List is empty" << endl;
  } else {
    ClientList.goFirst();
    for (int i = 0;i < ClientList.size(); i++, ClientList.goNext())
      cout << "    " << (i + 1) << ") #" << ClientList.getValue()->getID() << endl;
  }
}
