// Файл: CSView.h
// Проект класса "сервер-вид"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0


#ifndef CSVIEW_H_
#define CSVIEW_H_

#include "CServer.h"
#include "CoPoint.h"
#include "Scene.h"
#include "Glass.h"

class CServerView : public CScene, public CServer {
public:
  CServerView(const CCountedPoint& leftBottom, const CCountedPoint& rightTop)
      : CScene(leftBottom, rightTop) {}

  CServerView(const CScene& scene) : CScene(scene) { };

  virtual ~CServerView() {};

  void ReciveMessage(CMessage* msg) {
    CServer :: ReceiveMessage(msg);
    if (msg->getType() > 2) {
      CServer :: SendMessage(msg->getType(), msg->getInfo(), msg->getFromID());
    }
  }

  void Print() const {
    cout << (CScene&)*this << endl;
    CServer :: Print();
    cout << "----------------------";
    cout << endl << endl;
  }

  int inv() { return 2 == 2; }

  void MoveGlassCaseToPoint(CCountedPoint P) {

  }

  void MoveCollection(double dx, double dy) {

  }

  void MoveStand(double dx, double dy) {
  }

  CGlassList& GetCollection() {
    return *this;
  }
};

#endif