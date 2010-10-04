// Файл: CClient.h
// Проект класса "клиент"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция : 1.0

#ifndef _CCLIENT_H
#define _CCLIENT_H

#include <iostream.h>
#include "CoList.h"
#include "CServer.h"
#include "CMsg.h"
#include "id_obj.h"

// Класс Сервер использует класс Клиент, а класс Клиент класс Сервер
// Получается, Сервер должен быть определён раньше Клиента, но в то же самое
// время Клиент должен быть раньше Сервера, для выхода из этой ситуации
// используем предварительное объявление класса
class CServer;

// Класс "Клиент"
class CClient {
private:
  // сервер на котором зарегестрирован клиент или NULL
  CServer* server;

  // Идентификатор
  const int m_id;

  // Общее количество созданных когда-либо экземпляров
  static int total;

public:
  CClient(int id);
  ~CClient();

  int getID() const { return m_id; };

  CServer* getServer();     // Получить сервер
  void Register(CServer *server); // Зарегестрироваться на сервере
  void Unregister(); // Сняться с регистрации на сервере
  void SendMessage(CMessage *msg); // Отправить сообщение серверу
  void SendMessage(int _type, const CInfo& _info, int _id); // Отправить сообщение серверу
  void ReceiveMessage(CMessage *msg); // Получить сообщение
  virtual void Action(int _type, const CInfo& _info);

  // Оператор вывода в поток
  friend ostream& operator << (ostream& s, const CClient& c) {
    s << "Client #" << c.getID() << "  " <<
    ((c.server == NULL) ?
     " - Not registered on server" : " - Registered on server")
    << endl << endl;
    return s;
  }

  static int getTotal() { return total; }
};

#endif