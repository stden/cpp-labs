// Файл: CServer.h
//Проект класса "сервер"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#ifndef _CSERVER_H_
#define _CSERVER_H_

#include "CMSG.H"

#include "CCLIENT.H"
#include <iostream.h>

class CClient;

class CServer
{
private:
  static int debug;
  static int total;
  const int id;
  static int current;

 CircleList<CClient*> ClientList;

public:
    CServer();
    virtual ~CServer();


    CClient* GetClientByID(int _id);
    int Client_Count() const;
    void Register(CClient *client);
    void Unregister(int _id);
    void UnregisterAll();
    void SendMessage(CMessage *msg, int _id);
    void SendMessage(int _type, const CInfo& _info, int _id);
    void SendMessageToAll(CMessage *msg);
    void SendMessageToAll(int _type, const CInfo& _info);
    virtual void ReceiveMessage(CMessage *msg);
    virtual void Print() const;

    static void  setDebug(int d) { debug = d; }
    int getID() { return id; }
    static  int getCurrent() { return current; }
    static  int getTotal() { return total; }
    static int getDebug() { return debug; }

};


#endif