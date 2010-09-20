//Файл : CServer.h
//Проект класса "сервер"
//Автор : Монько А.О.
//Дата : 1.06.2010 Редакция : 1.0

#ifndef _CSERVER_H_
#define _CSERVER_H_

#include "CMSG.H"

#include "CCLIENT.H"
#include <iostream.h>

class CClient;

class CServer
{
private:
  static unsigned int debug;
  static unsigned int total;
  const unsigned int id;
  static unsigned int current;

 CircleList<CClient*> ClientList;

public:
    CServer();
    virtual ~CServer();


    CClient* GetClientByID(unsigned int _id);
    unsigned int Client_Count() const;
    void Register(CClient *client);
    void Unregister(unsigned int _id);
    void UnregisterAll();
    void SendMessage(CMessage *msg, unsigned int _id);
    void SendMessage(unsigned int _type, const CInfo& _info, unsigned int _id);
    void SendMessageToAll(CMessage *msg);
    void SendMessageToAll(unsigned int _type, const CInfo& _info);
    virtual void ReceiveMessage(CMessage *msg);
    virtual void Print() const;

    static void  SetDebug (unsigned int d) { debug = d; }
    unsigned int GetID () { return id; }
    static  unsigned int GetCurrent () { return current; }
    static  unsigned int GetTotal () { return total; }
    static unsigned int Get_debug() { return debug; }

};


#endif