// ����: CServer.h
// �஥�� ����� "�ࢥ�"
// ����: ���뭪� �. ��. ��. 7304
// ���: 20.09.2010 �������: 1.0

#ifndef _CSERVER_H_
#define _CSERVER_H_

#include "CMSG.H"

#include "CCLIENT.H"
#include <iostream.h>

// ����� ��ࢥ� �ᯮ���� ����� ������, � ����� ������ ����� ��ࢥ�
// ����砥���, ��ࢥ� ������ ���� ��।��� ࠭�� ������, �� � � �� ᠬ��
// �६� ������ ������ ���� ࠭�� ��ࢥ�, ��� ��室� �� �⮩ ���樨
// �ᯮ��㥬 �।���⥫쭮� ������� �����
class CClient;

// ���ᠭ�� ����� ��ࢥ�
class CServer {
 private:
  CList<CClient*> ClientList;

 public:
  CServer();
  ~CServer();

  CClient* GetClientByID(int _id);
  int ClientCount() const;
  void Register(CClient* client);
  void Unregister(int _id);
  void UnregisterAll();
  void SendMessage(CMessage* msg);
  void SendMessage(int _type, const CInfo& _info, int _id) {
    SendMessage(&CMessage(1, _id, _type, _info, Server_to_Client));
  }

  void SendMessageToAll(CMessage* msg);
  void ReceiveMessage(CMessage* msg);
  void Print() const;

  void SendMessageToAll(int _type, const CInfo& _info) {
    CMessage msg(1, 1, _type, _info, Server_to_Client);
    SendMessageToAll(&msg);
    assert(msg.getFromID() == 1);
    assert(msg.getType() == _type);
  }

};

#endif