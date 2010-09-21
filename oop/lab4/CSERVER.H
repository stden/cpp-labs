// Файл: CServer.h
// Проект класса "сервер"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#ifndef _CSERVER_H_
#define _CSERVER_H_

#include "CMSG.H"

#include "CCLIENT.H"
#include <iostream.h>

class CClient;

class CServer {
private:
  static int debug;
  static int total;
  const int id;
  static int current;

  CList<CClient*> ClientList;

public:
  CServer();
  ~CServer();

  CClient* GetClientByID(int _id);
  int ClientCount() const;
  void Register(CClient *client);
  void Unregister(int _id);
  void UnregisterAll();
  void SendMessage(CMessage *msg, int _id);
  void SendMessage(int _type, double _info, int _id);
  void SendMessageToAll(CMessage *msg);
  void SendMessageToAll(int _type, double _info);
  void ReceiveMessage(CMessage *msg);
  void Print() const;

  static void setDebug(int d) { debug = d; }
  int getID() { return id; }
  static int getCurrent(){ return current; }
  static int getTotal(){ return total; }
  static int getDebug(){ return debug; }
};

#endif