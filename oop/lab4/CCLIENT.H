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

class CServer;

class CClient {
private:
  static int debug;
  static int total;
  const int id;
  static int current;

  //список серверов на которых зарегестрирован клиент
  CList<CServer*> ServerList;

public:
  CClient();
  ~CClient();

  CServer* GetServerByID(int _id);     //получить сервер по ID
  int ServerCount() const;     //кол-во зарегестрированных серверов
  void Register(CServer *server); // Зарегестрироваться на сервере
  void Unregister(int _id); // Сняться с регистрации
  void UnregisterAll(); //Сняться с регистрации со всех серверов
  void SendMessage(CMessage *msg); // отправить сообщение серверу
  void SendMessage(int _type, double _info, int _id); // отправить сообщение серверу
  void ReceiveMessage(CMessage *msg); // Получить сообщение
  void Action(int _type, const float _info);
  void Print() const;

  static void setDebug( int _debug ){ debug = _debug; }
  int getID(){ return id; }
  static int getCurrent(){ return current; }
  static int getTotal(){ return total; }
  static int getDebug(){ return debug; }
};

#endif