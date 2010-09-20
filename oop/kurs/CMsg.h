// Файл: CMessage.h
//Проект класса "сообщение"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#ifndef CMSG_H
#define CMSG_H

#include "CPoint.h"



class CInfo {
     public :
     	int command; /*2 - Помещение в точку
                       3 - Плоскопараллельное перемещение на dx,dy 
                       4 - Перемещение поршня в стакане на dy */
	double dx;
	double dy;
	CPoint p;
        /* Конструктор */
	CInfo (int _command = 1, double _dx = 0, double _dy = 0, const CPoint& _p = CPoint()) :
        command(_command), dx(_dx), dy(_dy), p(_p) {}
         
       void Print () {
                cout << "(dx = " << dx << ", dy = " << dy << ", Point = " << p << ")" <<endl;
        }


};

class CMessage {
private:
	int FromID;
	int ToID;
	CInfo Info;
        int Type;/*    тип сообщения:
                                      0 - подтверждение приема
                                      1 - отчет о выполнение
                                      > 1 - запрос действия  */


        int direction; /*    направление передачи:
                                      0 - сервер->клиент
                                      1 - клиент->сервер  */


        static int debug;
        static int total;
        const int id;
        static int current;
public:
	CMessage(int _FromID = 0, int _ToID = 0, int _Type = 0, const CInfo& _Info = 0, int _dir = 0);
        CMessage(const CMessage& msg);
	~CMessage();
        int GetFromID() const { return FromID; }
        int GetToID() const { return ToID; }
        int GetType() const { return Type; }
        const CInfo& GetInfo() const { return Info; }
        int GetDirection() const { return direction; }
        void SetFromID(int _FromID);
        void SetToID(int _ToID);
        void SetType(int _Type);
        void SetInfo(const CInfo& _Info);
        void SetDirection(int _dir);
        const char* InterpritateType (int type);

        void Print () const;

        static void  setDebug(int d) { debug = d; }
        int getID() { return id; }
        static  int getCurrent() { return current; }
        static  int getTotal() { return total; }
        static int getDebug() { return debug; }

};


#endif