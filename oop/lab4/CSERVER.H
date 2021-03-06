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
  void SendMessage(int _type, double _info, int _id);
  void SendMessageToAll(CMessage* msg);
  void SendMessageToAll(int _type, double _info);
  void ReceiveMessage(CMessage* msg);
  void Print() const;
};

#endif