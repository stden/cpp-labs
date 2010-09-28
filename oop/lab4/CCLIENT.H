// Файл: CClient.h
// Проект класса "клиент"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция : 1.0

#ifndef _CCLIENT_H
#define _CCLIENT_H

#include "CoList.h"
#include "CServer.h"
#include "CMsg.h"
#include <iostream.h>

// Класс Сервер использует класс Клиент, а класс Клиент класс Сервер
// Получается, Сервер должен быть определён раньше Клиента, но в то же самое
// время Клиент должен быть раньше Сервера, для выхода из этой ситуации
// используем предварительное объявление класса
class CServer;

class CClient {
private:
  static int total;
  const int id;

  //список серверов на которых зарегестрирован клиент
  CServer* server;

public:
  CClient();
  ~CClient();

  CServer* getServer();     // Получить сервер
  void Register(CServer *server); // Зарегестрироваться на сервере
  void Unregister(); // Сняться с регистрации на сервере
  void SendMessage(CMessage *msg); // Отправить сообщение серверу
  void SendMessage(int _type, double _info, int _id); // Отправить сообщение серверу
  void ReceiveMessage(CMessage *msg); // Получить сообщение
  void Action(int _type, const float _info);
  void Print() const;

  int getID() const { return id; }
  static int getTotal() { return total; }
};

#endif