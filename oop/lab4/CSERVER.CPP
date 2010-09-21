// Файл: CServer.cpp
// Реализация класса "сервер"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CList.h"
#include "CListN.h"
#include "CServer.H"
#include <iostream.h>
#include <conio.h>
#include <assert.h>

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
  assert( GetClientByID(1) == NULL );
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
  ClientList.goFirst();
  if(ClientList.getCurrent() != NULL)
    do{
      if (ClientList.getValue()->getID() == _id)
        return ClientList.getValue();
    } while(ClientList.goNext());
  return NULL;
}

int CServer :: ClientCount() const {
  return ClientList.size();
}

void CServer :: Register(CClient *client) {
  assert( id > 0 && "Server ID must be > 0");
  if (client == NULL) {
    cout << "Server #"<< id << " Failed to register client due to wrong address" << endl;
  } else {
    if (GetClientByID(client->getID()) != NULL) {
      cout << "Client #" << client->getID()
	   << " already registered on server #"<<id<<endl;
    } else {
      int n = ClientCount();
      cout << "Server #" << id << " register client #" << client->getID() << endl;
      assert( GetClientByID(client->getID()) == NULL );
      ClientList.insert(client);
      assert( GetClientByID(client->getID()) != NULL );
      assert( ClientCount() == n+1 );
      if (client->GetServerByID(id) == NULL) {
        client->Register(this);
      	cout << "Client #" << client->getID() << " was registered on server #"
      	  << id << endl;
      }
      assert( client->GetServerByID(id) != NULL );
    }
  }
}


void CServer :: Unregister(int _id) {
  CClient* client = GetClientByID(_id);
  if (client == NULL) {
    cout << "Client #"<<_id<< " can not unregister from server #" << id
      << " cause it does not registered on it" << endl;
  } else {
    assert(ClientList.getValue()->getID() == _id);
    ClientList.dispose();
    if (client->GetServerByID(id) != NULL) {
      client->Unregister(id);
      cout << "Client #"<< client->getID() <<" was unregistered from server #"<<id<<endl;
    }
    assert( client->GetServerByID(id) == NULL );
  }
}

void CServer ::UnregisterAll() {
  if (ClientList.size() == 0) {
    cout << "There are already no registered clients exists"<<endl;
  } else {
    while(ClientList.size() > 0){
      ClientList.goFirst();
      CClient* cl = ClientList.getValue();
      Unregister(cl->getID());
    };
    cout << "Server #"<<id<<": unregistered all clients"<<endl;
  }
  assert( ClientList.size() == 0 );
}


void CServer :: SendMessage(CMessage *msg) {
  assert( msg != NULL );
  assert( msg->getFromID() == id );
  assert( msg->getDirection() == Server_to_Client );

  CClient *client = GetClientByID(msg->getToID());
  if (client != NULL) {
    assert( msg->getDirection() == Server_to_Client );
    client->ReceiveMessage(msg);
    cout << "Server #" << id << ": sent message to client #"
      << msg->getToID() << endl;
  }
  else {
    cout << "Server #" << id << " could not send messages to client #"
      << msg->getToID() << " cause it not registered on it"<<endl;
  }
}


void CServer :: SendMessageToAll(int _type, double _info) {
  CMessage msg(id,1,_type,_info,Server_to_Client);
  SendMessageToAll(&msg);
  assert( msg.getFromID() == id );
  assert( msg.getType() == _type );
  assert( msg.getInfo() == _info );
}

void CServer :: SendMessageToAll(CMessage *msg) {
  assert( msg->getFromID() == id );
  assert( msg->getDirection() == Server_to_Client );
  if (ClientList.size() != 0) {
    assert( msg->getDirection() == Server_to_Client );
    ClientList.goFirst();
    if(ClientList.getCurrent()!=NULL)
      do{
        assert( msg->getFromID() == id );
        msg->setToID(ClientList.getValue()->getID());
        ClientList.getValue()->ReceiveMessage(msg);
      } while (ClientList.goNext());
    cout << "Server #"<<id<< ": sent message to all clients " << endl;
  } else {
    cout << "Server #" << id
      << " could not send messages to clients cause they are not registered on it"<<endl;
  }
}

void CServer :: SendMessage(int _type, double _info, int _id) {
  CMessage msg(id,_id,_type,_info,Server_to_Client);
  SendMessage(&msg);
}

void CServer :: ReceiveMessage(CMessage *msg) {
  assert( msg->getToID() == id );
  assert( msg->getDirection() == Client_to_Server );
  CClient* client = GetClientByID(msg->getFromID());
  if (client != NULL) {
    cout << "Server #" << id << ": recived message from client #" << client->getID() << endl;
    msg->Print();
    if (msg->getType() > 0 && Server_Do_Confirmation) {
      CMessage msg1(*msg);
      msg1.setType(Confirmation); //код подтверждения приёма сообщения
      msg1.setDirection(Server_to_Client);
      msg1.setToID(client->getID());
      SendMessage(&msg1);
    }
  } else {
    cout << "Server #" << id << ": could not recive message from unknown client"<<endl;
  }
  assert( msg != NULL );
  delete msg;
}

void CServer::Print() const {
  cout << "Server: #" << id << endl
    << "  Current number of servers = " << current << endl
    << "  Number of registered clients = " << ClientList.size() << endl
    << "  List of clients: " << endl;
  if (ClientList.size() == 0) {
    cout << "    List is empty"<<endl;
  } else {
    ClientList.goFirst();
    for (int i = 0;i < ClientList.size(); i++,ClientList.goNext())
      cout << "    " << (i+1) << ") #" << ClientList.getValue()->getID() << endl;
  }
}
