//Файл : CClient.h
//Проект класса "клиент"
//Автор : Монько А.О
//Дата : 1.06.2010 Редакция : 1.0

#ifndef _CCLIENT_H
#define _CCLIENT_H

#include "CList.h"
#include "CServer.h"
#include "CMsg.h"
#include <iostream.h>

class CServer;

class CClient
{
private:
  static unsigned int debug;
  static unsigned int total;
  const unsigned int id;
  static unsigned int current;

  //список серверов на которых зарегестрирован клиент
  CircleList<CServer*> ServerList;

   virtual void Action(unsigned int _type, const CInfo& _info);

  public:
    CClient();
    virtual ~CClient();


    CServer* GetServerByID(unsigned int _id);     //получить сервер по ID
    CircleList<CServer*> GetServerList() const { return ServerList; }

    unsigned int ServerCount() const;     //кол-во зарегестрированных серверов
    void Register(CServer *server); // Зарегестрироваться на сервере
    void Unregister(unsigned int _id); // Сняться с регистрации
    void UnregisterAll(); //Сняться с регистрации со всех серверов
    void SendMessage(CMessage *msg, unsigned int _id); // отправить сообщение серверу
    void SendMessage(unsigned int _type, const CInfo& _info, unsigned int _id); // отправить сообщение серверу
    void ReceiveMessage(CMessage *msg); // Получить сообщение

    virtual void Print() const;

        static void  SetDebug (unsigned int d) { debug = d; }
        virtual unsigned int GetID () { return id; }
        static  unsigned int GetCurrent () { return current; }
        static  unsigned int GetTotal () { return total; }
        static unsigned int Get_debug() { return debug; }


};



#endif