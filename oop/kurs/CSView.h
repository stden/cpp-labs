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
  void inv() {
    CScene :: inv();
    CServer :: inv();
  }

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

  void MoveGlassCaseToPoint(CCountedPoint P) {
    CGlassCase :: MoveToPoint(P);
    inv();
  }

  void MoveCollection(double dX, double dY) {
    CGlassList :: MovedXdY(dX, dY);
    inv();
  }

  void MoveCollectionToPoint(CCountedPoint P) {
    CGlassCase :: MoveToPoint(P);
    inv();
  }

  void GlassCaseMovedXdY(double dX, double dY) {
    CGlassCase :: MovedXdY(dX, dY);
    inv();
  }

  CGlassList& GetCollection() {
    return *this;
  }
};

#endif