// ����: CClient.h
// �஥�� ����� "������"
// ����: ���뭪� �. ��. ��. 7304
// ���: 20.09.2010 ������� : 1.0

#ifndef _CCLIENT_H
#define _CCLIENT_H

#include <iostream.h>
#include "CoList.h"
#include "CServer.h"
#include "CMsg.h"
#include "id_obj.h"

// ����� ��ࢥ� �ᯮ���� ����� ������, � ����� ������ ����� ��ࢥ�
// ����砥���, ��ࢥ� ������ ���� ��।��� ࠭�� ������, �� � � �� ᠬ��
// �६� ������ ������ ���� ࠭�� ��ࢥ�, ��� ��室� �� �⮩ ���樨
// �ᯮ��㥬 �।���⥫쭮� ������� �����
class CServer;

// ����� "������"
class CClient {
 private:
  // �ࢥ� �� ���஬ ��ॣ����஢�� ������ ��� NULL
  CServer* server;

  // �����䨪���
  const int m_id;

  // ��饥 ������⢮ ᮧ������ �����-���� ��������஢
  static int total;

 public:
  CClient(int id);
  ~CClient();

  int getID() const {
    return m_id;
  };

  CServer* getServer();     // ������� �ࢥ�
  void Register(CServer* server); // ��ॣ����஢����� �� �ࢥ�
  void Unregister(); // ������� � ॣ����樨 �� �ࢥ�
  void SendMessage(CMessage* msg); // ��ࠢ��� ᮮ�饭�� �ࢥ��
  void SendMessage(int _type, const CInfo& _info, int _id); // ��ࠢ��� ᮮ�饭�� �ࢥ��
  void ReceiveMessage(CMessage* msg); // ������� ᮮ�饭��
  virtual void Action(int _type, const CInfo& _info);

  // ������ �뢮�� � ��⮪
  friend ostream& operator << (ostream& s, const CClient& c) {
    s << "Client #" << c.getID() << "  " <<
      ((c.server == NULL) ?
       " - Not registered on server" : " - Registered on server")
      << endl << endl;
    return s;
  }

  static int getTotal() {
    return total;
  }
};

#endif