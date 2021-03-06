// ����: CClient.h
// �஥�� ����� "������"
// ����: ���뭪� �. ��. ��. 7304
// ���: 20.09.2010 ������� : 1.0

#ifndef _CCLIENT_H
#define _CCLIENT_H

#include "CoList.h"
#include "CServer.h"
#include "CMsg.h"
#include <iostream.h>

// ����� ��ࢥ� �ᯮ���� ����� ������, � ����� ������ ����� ��ࢥ�
// ����砥���, ��ࢥ� ������ ���� ��।��� ࠭�� ������, �� � � �� ᠬ��
// �६� ������ ������ ���� ࠭�� ��ࢥ�, ��� ��室� �� �⮩ ���樨
// �ᯮ��㥬 �।���⥫쭮� ������� �����
class CServer;

// ����� "������"
class CClient {
 private:
  static int total;
  const int id;

  // �ࢥ� �� ���஬ ��ॣ����஢�� ������ ��� NULL
  CServer* server;

 public:
  CClient();
  ~CClient();

  CServer* getServer();     // ������� �ࢥ�
  void Register(CServer* server); // ��ॣ����஢����� �� �ࢥ�
  void Unregister(); // ������� � ॣ����樨 �� �ࢥ�
  void SendMessage(CMessage* msg); // ��ࠢ��� ᮮ�饭�� �ࢥ��
  void SendMessage(int _type, double _info, int _id); // ��ࠢ��� ᮮ�饭�� �ࢥ��
  void ReceiveMessage(CMessage* msg); // ������� ᮮ�饭��
  void Action(int _type, const float _info);

  int getID() const {
    return id;
  }
  static int getTotal() {
    return total;
  }

  // ������ �뢮�� � ��⮪
  friend ostream& operator << (ostream& s, const CClient& c) {
    s << "Client #" << c.id << "  total = " << c.total <<
      ((c.server == NULL) ?
       " - Not registered on server" : " - Registered on server")
      << endl << endl;
    return s;
  }
};

#endif