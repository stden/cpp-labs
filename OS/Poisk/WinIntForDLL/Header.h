#include <shlobj.h>
#include <windows.h>
#include <string>
#include "PoiskDLL.h"
#include "resurs.h"
#pragma comment(lib, "PoiskDLL.lib")
#define ID_BUTTONn1 1
#define ID_STATIC1 2
#define ID_BUTTONn3 3
#define ID_LISTBOX1 4
#define ID_CHECKBOX1 5
#define ID_CHECKBOX2 6
#define ID_CHECKBOX3 7
#define ID_CHECKBOX4 8
#define ID_CHECKBOX5 9
#define ID_STATIC2 10
#define ID_EDIT1 11
#define ID_EDIT2 12
#define ID_GROUPBOX1 13
#define ID_GROUPBOX2 14//!!!!!!!!!!!!!!!!!!!!!днаюбхк!!!!!!!!!!!!!!!!!!!!!
#define ID_STATUSBAR1 15
#define ID_SETFONT1 16
#define ID_BUTTONn2 17
#define ID_CHECKBOX6 18
#define ID_STATIC3 19
#define ID_STATIC4 20
#define ID_BUTTONn4 21




class CriticalSection {
 public:
  CriticalSection(CRITICAL_SECTION* S) {
    Section = S;
    EnterCriticalSection(Section);
  }
  ~CriticalSection() {
    LeaveCriticalSection(Section);
  }
  CRITICAL_SECTION* Section;
};