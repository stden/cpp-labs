// Файл: CMessage.h
// Проект класса "сообщение"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#ifndef CMSG_H
#define CMSG_H

// направление передачи: 0 - сервер->клиент, 1 - клиент->сервер
enum Direction { Server_to_Client, Client_to_Server };
// тип сообщения: 0 - подтверждение приема
//   1 - отчет о выполнении >= 2 - запрос действия
const int Confirmation = 0;
const int Report = 1;

class CMessage {
private:
  int FromID;
  int ToID;
  double Info;
  int Type; // тип сообщения
  Direction direction; // направление передачи
  static int debug;
  static int total;
  const int id;
  static int current;
public:
  CMessage(int _FromID, int _ToID, int _Type, double _Info, Direction _dir);
  CMessage(const CMessage& msg);
  ~CMessage();
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
  const char* InterpritateType(int type) const;
  void Print(char *prompt="") const;
  static void setDebug(int d) { debug = d; }
  int getID() { return id; }
  static int getCurrent(){ return current; }
  static int getTotal(){ return total; }
  static int get_debug(){ return debug; }
};

#endif