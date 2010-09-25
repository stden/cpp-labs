// Файл: CMessage.h
// Проект класса "сообщение"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#ifndef CMSG_H
#define CMSG_H

// направление передачи: сервер->клиент, клиент->сервер,
// клиент->клиент через сервер
enum Direction { Server_to_Client, Client_to_Server,
  Client_to_Client };

// тип сообщения: остальные коды - запрос действия (ACTION)
const int CONFIRMATION = 0; // подтверждение приема
const int REPORT = 1; // отчет о выполнении команды

// Объявление класса Сообщение
class CMessage {
private:
  const int id; // id сообщения
  int FromID; // id от кого сообщение
  int ToID; // id кому сообщение
  double Info; // Информационное поле сообщения
  int Type; // тип сообщения (CONFIRMATION, REPORT, ACTION)
  Direction direction; // направление передачи
  static int debug;
  static int total;
  static int current;
public:
  CMessage(int _FromID, int _ToID, int _Type, double _Info, Direction _dir);
  CMessage(const CMessage& msg);
  ~CMessage();

  const char* InterpritateType(int type) const;
  void Print(char *prompt="") const;

  int getID() const { return id; }
  int getFromID() const { return FromID; }
  int getToID() const { return ToID; }
  int getType() const { return Type; }
  double getInfo() const { return Info; }
  Direction getDirection() const { return direction; }

  void setFromID(int _FromID) { FromID = _FromID; };
  void setToID(int _ToID) { ToID = _ToID; };
  void setType(int _Type) { Type = _Type; };
  void setInfo(double _Info) { Info = _Info; };
  void setDirection(Direction _dir){ direction = _dir; }

  static void setDebug(int d) { debug = d; }

  static int getCurrent(){ return current; }
  static int getTotal(){ return total; }
  static int getDebug(){ return debug; }
};

#endif