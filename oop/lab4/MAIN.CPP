// Файл: Main.cpp
// Основная программа
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция: 1.0

#include "CMsg.h"
#include "CServer.h"
#include "CClient.h"
#include "CoList.h"
#include <iostream.h>
#include <conio.h>
#include <values.h>
#include <assert.h>

// Input value from "cin" with error checking
template <class T>
T input(char *prompt, T min, T max) {
  T value;
  do {
    cout << prompt << " " << min << ".." << max << ": ";
    while (!(cin >> value)/* && !cin.eof()*/) {
      cerr << "Error: invalid input " << value << ", try again: ";
      cin.clear();
      cin.ignore(cin.rdbuf()->in_avail());
    }
    if (value < min)
      cerr << "Error: Required value >= " << min << endl;
    if (value > max)
      cerr << "Error: Required value <= " << max << endl;
  } while (value < min || value > max);
  return value;
}

int inputClientID(char *prompt) {
  if (CClient::getTotal() < 1) {
    cout << "Register at least one client at first" << endl;
    return 0;
  };
  return input(prompt, 1, CClient::getTotal());
}

int inputMessageCode() {
  return input("Enter code of message, u want to send", 2, 99);
}

float inputInfoField() {
  return input("Enter info field", MINFLOAT, MAXFLOAT);
}

CList<CClient*> clients;

CClient* clientByID(int id) {
  for (clients.goFirst();clients.hasNext();clients.goNext())
    if (clients.getValue()->getID() == id)
      return clients.getValue();
  return NULL;
}

int main() {
  // Test list
  CList<int> l; assert(l.size() == 0); assert(!l.goFirst());
  l.insert(1); assert(l.size() == 1); // [1]
  l.insert(2); assert(l.size() == 2); // [1 2]
  l.insert(3); assert(l.size() == 3); // [1 2 3]
  l.insert(4); assert(l.size() == 4); // [1 2 3 4]
  l.goFirst(); assert(l.getValue() == 1); // [(1) 2 3 4]
  l.dispose(); assert(l.getValue() == 2 && l.size() == 3); // [(2) 3 4]
  l.goFirst(); assert(l.getValue() == 2 && l.size() == 3); // [(2) 3 4]
  l.goNext();  assert(l.getValue() == 3 && l.size() == 3); // [2 (3) 4]
  l.dispose(); assert(l.getValue() == 4 && l.size() == 2); // [2 (4)]
  l.dispose(); assert(l.getValue() == 2 && l.size() == 1); // [(2)]
  l.dispose(); assert(l.size() == 0); // []
  l.insertBegin(239); assert(l.getValue() == 239 && l.size() == 1); // [239]

  clrscr();
  cout << endl << endl << "----------------------------------------------------" << endl;
  cout << "Programm is modeling of Client->Server->Client message exchange" << endl
       << "with confirmation of Server->Client interaction." << endl
       << "Programmed by: Evgeny Volinko" << endl
       << "----------------------------------------------------" << endl;

  int menu;
  CServer server;
  assert(server.ClientCount() == 0);
  do {
    cout << endl
         << "Main Menu" << endl
         << "  1. Create Client" << endl
         << "  2. Registrate on server" << endl
         << "  3. Registrate all clients on server" << endl
         << "  4. Unregistrate client from server" << endl
         << "  5. Unregistrate all clients from server" << endl
         << "  6. Send message Client -> Server" << endl
         << "  7. Send message Server -> Client" << endl
         << "  8. Send message Client -> Server -> Client" << endl
         << "  9. Print clients info" << endl
         << "  10. Print all clients info" << endl
         << "  11. Exit" << endl << endl;

    menu = input("Your choice", 1, 11);
    cout << endl;
    switch (menu) {
      case 1: {
        cout << "== 1. Create Client ==" << endl;
        CClient* cl = new CClient;
        assert(cl != NULL);
        int n = clients.size();
        assert(clientByID(cl->getID()) == NULL);
        clients.insert(cl);
        assert(clientByID(cl->getID()) != NULL);
        assert(clients.size() == n + 1);
        cout << "New client added #" << cl->getID() << endl;
        assert(server.GetClientByID(cl->getID()) == NULL);
        break;
      };
      case 2: {
        cout << "== 2. Registrate on server ==" << endl;
        int id = inputClientID("Enter id of client to register");
        CClient* cl = clientByID(id);
        if (cl == NULL) {
          cout << "Client #" << id << " not exists!" << endl;
          break;
        }
        server.Register(cl);
        assert(server.GetClientByID(id) == cl);
        assert(cl->getServer() != NULL);
        break;
      };
      case 3: {
        cout << "== 3. Registrate all clients on server ==" << endl;
        for (clients.goFirst();clients.hasNext();clients.goNext()) {
          server.Register(clients.getValue());
          assert(server.GetClientByID(clients.getValue()->getID()) ==
                 clients.getValue());
        };
        assert(clients.size() == server.ClientCount());
        break;
      };
      case 4: {
        cout << "== 4. Unregistrate client from server ==" << endl;
        int id = inputClientID("Enter id of client to unregister");
        server.Unregister(id);
        assert(server.GetClientByID(id) == NULL);
        break;
      };
      case 5:
        cout << "== 5. Unregistrate all clients from server ==" << endl;
        server.UnregisterAll();
        break;
      case 6: {
        cout << "== 6. Send message Client -> Server ==" << endl;
        int id = inputClientID("Enter id of client");
        if (id == 0) break;
        int tcode = inputMessageCode();
        float tinfo = inputInfoField();
        cout << endl;
        CClient* cl = clientByID(id);
        if (cl != NULL)
          cl->SendMessage(tcode, tinfo, 1);
        else
          cout << "Client #" << id << " not exists!" << endl;
        break;
      }
      case 7: {
        cout << "== 7. Send message Server -> Client ==" << endl;
        int id = inputClientID("Enter id of client");
        if (id == 0) break;
        int tcode = inputMessageCode();
        float tinfo = inputInfoField();
        cout << endl;
        server.SendMessage(&CMessage(1, id, tcode, tinfo, Server_to_Client));
        break;
      }
      case 8: {
        cout << "===  8. Send message Client -> Server -> Client ===" << endl;
        int src_id = inputClientID("Enter id of source client");
        int dst_id = inputClientID("Enter id of destination client");
        if (src_id == 0 || dst_id == 0) break;
        int tcode = inputMessageCode();
        float tinfo = inputInfoField();
        cout << endl;
        CClient* src = clientByID(src_id);
        if (src != NULL)
          src->SendMessage(&CMessage(src_id, dst_id, tcode, tinfo, Client_to_Client));
        else
          cout << "Client #" << src_id << " not exists!" << endl;
        break;
      }
      case 9: {
        cout << "== 9. Print client info ==" << endl;
        int id = inputClientID("Enter id of client, which info u want to look");
        cout << endl;
        CClient* cl = clientByID(id);
        if (cl != NULL)
          cout << *cl << endl;
        else
          cout << "Client #" << id << " not exists!" << endl;
        break;
      }
      case 10: {
        cout << "== 10. Print all clients info ==" << endl;
        for (clients.goFirst();clients.hasNext();clients.goNext()) {
          cout << *clients.getValue() << endl;
          cout << "-- Press any key to continue or ESC to exit -- " << endl;
          if (getch() == 27) break; // Waiting for some action
        };
        server.Print();
        break;
      }
      default:
        return 0;
    }
  } while (menu != 11);
  return 0;
}