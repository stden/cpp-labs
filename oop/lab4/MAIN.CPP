// Файл: Main.cpp
// Основная программа
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CMsg.h"
#include "CServer.h"
#include "CClient.h"
#include "CList.h"
#include <iostream.h>
#include <conio.h>
#include <values.h>

// Input value from "cin" with error checking
template <class T>
T input(char *prompt, T min, T max){
  T value;
  do{
    cout << prompt << " " << min << ".." << max << ": ";
    while(!(cin >> value) && !cin.eof()) {
      cerr << "Error: invalid input, try again: "<<endl;
      cin.clear();
      cin.ignore(cin.rdbuf()->in_avail());
    }
    if(value < min)
      cerr << "Error: Required value >= " << min <<endl;
    if(value > max)
      cerr << "Error: Required value <= " << max <<endl;
  } while(value < min || value > max);
  return value;
}

int inputClientID(char *prompt){
  if(CClient::getCurrent() < 1){
    cout << "Register at least one client at first" << endl;
    return 0;
  };
  return input(prompt,1,CClient::getTotal());
}

int inputMessageCode(){
  return input("Enter code of message, u want to send",2,99);
}

float inputInfoField(){
  return input("Enter info field",MINFLOAT,MAXFLOAT);
}

int main() {
  clrscr();
  cout << endl << endl << "-----------------------------------------------"<<endl;
  cout << "Programm is modeling of Client->Server->Client message exchange"<<endl
    << "with confirmation of Server->Client interaction."<<endl
    << "Programmed by: Evgeny Volinko"<<endl
    << "--------------------------------"<<endl;

  int menu;
  CServer server;
  CircleList<CClient*> clients;

  do{
    cout << endl
      << "Main Menu" << endl 
      << "  1. Create Client"<<endl
      << "  2. Registrate on server"<<endl
      << "  3. Registrate all clients on server"<<endl
      << "  4. Unregistrate client from server"<<endl
      << "  5. Unregistrate all clients from server"<<endl
      << "  6. Send message Client -> Server"<<endl
      << "  7. Send message Server -> Client"<<endl
      << "  8. Send message Server -> all Clients"<<endl
      << "  9. Print clients info"<<endl
      << "  10. Print all clients info"<<endl
      << "  11. Exit"<<endl << endl;

    menu = input("Your choice",1,11);
    cout << endl;
    switch (menu) {
      case 1:
  cout << "== 1. Create Client ==" << endl;
  CClient* cl = new CClient;
  if (cl) {
    clients.Append(new CLNode<CClient*>(cl));
    cout << "New client added #" << cl->getID() << endl;
  } else
    cout << "Error while create client!" << endl;
  break;
      case 2:
  cout << "== 2. Registrate on server ==" << endl;
  int id = inputClientID("Enter id of client to register");
  for (int i = 0;i < clients.GetSize();i++) {
    if (clients.GetElemByNum(i)->GetValue()->getID() == id) {
      server.Register(clients.GetElemByNum(i)->GetValue());
      break;
    }
  }
  break;
      case 3: {
  cout << "== 3. Registrate all clients on server ==" << endl;
  for (int i = 0;i < clients.GetSize();i++)
    server.Register(clients.GetElemByNum(i)->GetValue());
  break;
      };
      case 4: {
  cout << "== 4. Unregistrate client from server ==" << endl;
  int tid = inputClientID("Enter id of client, u want to unregister");
  for (int i = 0;i < clients.GetSize();i++) {
    if (clients.GetElemByNum(i)->GetValue()->getID() == tid) {
      server.Unregister(tid);
      break;
    }
  }
  break;
      };
      case 5:
  cout << "== 5. Unregistrate all clients from server ==" << endl;
  server.UnregisterAll();
  break;
      case 6: {
  cout << "== 6. Send message Client -> Server ==" << endl;
  int tid = inputClientID("Enter id of client");
        if(tid==0) break;
  int tcode = inputMessageCode();
  float tinfo = inputInfoField();
  for (int i = 0;i < clients.GetSize();i++) {
    if (clients.GetElemByNum(i)->GetValue()->getID() == tid) {
      clients.GetElemByNum(i)->GetValue()->
        SendMessage(tcode,tinfo,server.getID());
      break;
    }
  }
  break;
      }
      case 7: {
  cout << "== 7. Send message Server -> Client ==" << endl;
  int tid = inputClientID("Enter id of client");
  if(tid==0) break;
  int tcode = inputMessageCode();
  float tinfo = inputInfoField();
  server.SendMessage(
    new CMessage(server.getID(),tid,tcode,tinfo,Server_to_Client),tid);
  break;
      }
      case 8:
  cout << "== 8. Send message Server -> all Clients ==" << endl;
  server.SendMessageToAll( inputMessageCode(), inputInfoField() );
  break;
      case 9: {
  cout << "== 9. Print clients info ==" << endl;
  int tid = inputClientID("Enter id of client, which info u want to look");
  for (int i = 0;i < clients.GetSize();i++) {
    if (clients.GetElemByNum(i)->GetValue()->getID() == tid) {
      clients.GetElemByNum(i)->GetValue()->Print();
      break;
    }
  }
  break;
      }
      case 10: {
  cout << "== 10. Print all clients info ==" << endl;
  for (int i = 0;i < clients.GetSize();i++) {
    clients.GetElemByNum(i)->GetValue()->Print();
    cout << "-- Press any key to continue or ESC to exit -- "<<endl;
    if (getch() == 27) break; // Waiting for some action
  }
  break;
       }
      default:
  return 0;
   }
  } while(menu!=11);
  return 0;
}





