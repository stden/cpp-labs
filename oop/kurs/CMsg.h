//���� : CMessage.h
//������ ������ "���������"
//����� : ������ �.�.
//���� : 1.06.2010 �������� : 1.0

#ifndef CMSG_H
#define CMSG_H

#include "CPoint.h"



class CInfo {
     public :
     	int command; /*2 - ��������� � �����
                       3 - ������������������ ����������� �� dx,dy 
                       4 - ����������� ������ � ������� �� dy */
	double dx;
	double dy;
	CPoint p;
        /* ����������� */
	CInfo (int _command = 1, double _dx = 0, double _dy = 0, const CPoint& _p = CPoint()) :
        command(_command), dx(_dx), dy(_dy), p(_p) {}
         
       void Print () {
                cout << "(dx = " << dx << ", dy = " << dy << ", Point = " << p << ")" <<endl;
        }


};

class CMessage {
private:
	unsigned int FromID;
	unsigned int ToID;
	CInfo Info;
        int Type;/*    ��� ���������:
                                      0 - ������������� ������
                                      1 - ����� � ����������
                                      > 1 - ������ ��������  */


        unsigned int direction; /*    ����������� ��������:
                                      0 - ������->������
                                      1 - ������->������  */


        static unsigned int debug;
        static unsigned int total;
        const unsigned int id;
        static unsigned int current;
public:
	CMessage(unsigned int _FromID = 0, unsigned int _ToID = 0, int _Type = 0, const CInfo& _Info = 0, unsigned int _dir = 0);
        CMessage(const CMessage& msg);
	~CMessage();
        unsigned int GetFromID() const { return FromID; }
        unsigned int GetToID() const { return ToID; }
        unsigned int GetType() const { return Type; }
        const CInfo& GetInfo() const { return Info; }
        unsigned int GetDirection() const { return direction; }
        void SetFromID(unsigned int _FromID);
        void SetToID(unsigned int _ToID);
        void SetType(unsigned int _Type);
        void SetInfo(const CInfo& _Info);
        void SetDirection(unsigned int _dir);
        const char* InterpritateType (unsigned int type);

        void Print () const;

        static void  SetDebug (unsigned int d) { debug = d; }
        unsigned int GetID () { return id; }
        static  unsigned int GetCurrent () { return current; }
        static  unsigned int GetTotal () { return total; }
        static unsigned int Get_debug() { return debug; }

};


#endif