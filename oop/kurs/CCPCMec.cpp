// Файл: СCPСMec.cpp
// Реализация класса "клиент - закрытый поршневой механизм"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CCPCMec.h"


CClientClosedPistonMechanism :: CClientClosedPistonMechanism(const CClosedPistonMechanism & mec)
 : CClosedPistonMechanism(mec), CClient() {

}

CClientClosedPistonMechanism :: CClientClosedPistonMechanism()
 : CClosedPistonMechanism(), CClient() {

}

CClientClosedPistonMechanism :: CClientClosedPistonMechanism(double x1, double y1, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth, double y2, double pistonheight, double stocklength,double cover_height,double hole_width)
 : CClosedPistonMechanism(x1, y1, leftwidth, leftheight, bottomwidth, bottomheight, rightwidth, y2, pistonheight, stocklength, cover_height, hole_width), CClient() {

}

CClientClosedPistonMechanism :: CClientClosedPistonMechanism(CPoint P1, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth, double y2, double pistonheight, double stocklength,double cover_height,double hole_width)
 : CClosedPistonMechanism(P1, leftwidth, leftheight, bottomwidth, bottomheight, rightwidth, y2, pistonheight, stocklength, cover_height, hole_width), CClient() {

}

CClientClosedPistonMechanism :: ~CClientClosedPistonMechanism() {

}

void CClientClosedPistonMechanism :: Move(double dx, double dy){
  CServer* srv = CClient :: GetServerList().GetFirst()->GetValue();
  CClient :: SendMessage(3,CInfo(3,dx,dy),srv->getID());
}

void CClientClosedPistonMechanism :: SetP1(CPoint P0){
  CServer* srv = CClient :: GetServerList().GetFirst()->GetValue();
  CClient :: SendMessage(2,CInfo(2,0,0,P0),srv->getID());
}

int CClientClosedPistonMechanism :: MovePiston(double dy){
  CServer* srv = CClient :: GetServerList().GetFirst()->GetValue();
  CClient :: SendMessage(4,CInfo(4,0,dy),srv->getID());
  return 0;
}

void CClientClosedPistonMechanism :: Action(int _type, const CInfo& info){



 switch (info.command)
  {
    case 2:
      cout << "Client is handling action with code = "<<info.command<<"(Setting P1)"<<endl
      << "And parametrs = ";info.Print(); cout <<endl;
      CClosedPistonMechanism :: SetP1(info.p);

    break;

    case 3:
     cout << "Client is handling action with code = "<<info.command<<"(Moving by dx, dy)"<<endl
      << "And parametrs = ";info.Print(); cout <<endl;
      CClosedPistonMechanism :: Move(info.dx,info.dy);
    break;

    case 4:
     cout << "Client is handling action with code = "<<info.command<<"(Moving Piston by dy)"<<endl
      << "And parametrs = ";info.Print(); cout <<endl;
      CClosedPistonMechanism :: MovePiston(info.dy);
    break;

    default:
      cout << "Client could not handle action with code = "<<info.command<<endl
      << "case of unknown code "<< endl<<endl;
    break;
  }
}

void CClientClosedPistonMechanism :: Print() const {
  CClosedPistonMechanism :: Print();
  CClient :: Print();
  cout << "--------------------"<<endl<<endl;
}

int CClientClosedPistonMechanism :: getID() {
        return CClient :: getID();
}

