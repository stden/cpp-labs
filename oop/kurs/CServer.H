// Файл: CServer.h
// Проект класса "сервер"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#ifndef _CSERVER_H_
#define _CSERVER_H_

#include "CMSG.H"

#include "CCLIENT.H"
#include <iostream.h>

// Класс Сервер использует класс Клиент, а класс Клиент класс Сервер
// Получается, Сервер должен быть определён раньше Клиента, но в то же самое
// время Клиент должен быть раньше Сервера, для выхода из этой ситуации
// используем предварительное объявление класса
class CClient;

// Описание класса Сервер
class CServer {
private:
  CList<CClient*> ClientList;

public:
  CServer();
  ~CServer();

  CClient* GetClientByID(int _id);
  int ClientCount() const;
  void Register(CClient *client);
  void Unregister(int _id);
  void UnregisterAll();
  void SendMessage(CMessage *msg);
  void SendMessage(int _type, const CInfo& _info, int _id) {
    SendMessage(&CMessage(1, _id, _type, _info, Server_to_Client));
  }

  void SendMessageToAll(CMessage *msg);
  void ReceiveMessage(CMessage *msg);
  void Print() const;

  void SendMessageToAll(int _type, const CInfo& _info) {
    CMessage msg(1, 1, _type, _info, Server_to_Client);
    SendMessageToAll(&msg);
    assert(msg.getFromID() == 1);
    assert(msg.getType() == _type);
  }

};

#endif