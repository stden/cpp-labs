#include "PoiskDLL.h"

ListL*  Poisk::PoiskDubl( bool inVlosP, bool inTabulP, bool inIFIP, LPCSTR inParametrP, ListP*  inListPP,
                          DWORD   inFileP, DWORD   inDerekP) {
  inVlos =  inVlosP;
  inTabul = inTabulP;
  inIFI = inIFIP;
  inParametr =  inParametrP;
  inListP = inListPP;
  inFile = inFileP;
  inDerek = inDerekP;

  return PoiskDubl();
}

ListL* Poisk::PoiskDubl(void) {
  PP();

  if (!inListP)
    return NULL;

  if(!inTabul)
    if(!inParametr)
      inParametr = "*.*";

  // ≈сли параметр не равен нулю и нет точки то ничего не найдет!!!!!!!!
  OneL();
  ListCleen();
}


void Poisk::OneL(void) {
  if (inTabul) {
    ListP* LP = inListP;

    while( LP ) {
      TreeBP( LP->PathP );
      LP = LP->next;
    }
  } else {
    ListP* LP = inListP;

    while( LP ) {
      TreeB( LP->PathP );
      LP = LP->next;
    }
  }
}


void Poisk::ListCleen(void) {
  if (!inListF)
    return;

  ListF* temp1 = inListF->next;
  ListF* temp2;
  LPCSTR LP;
  bool flagC = true, flagM = true, flagS = true, flagB = true;
  ListF* temp3 = NULL;
  char tem1[MAX_PATH];
  char tem2[MAX_PATH];

  while( temp1 ) {

    if (inListF->WFD.nFileSizeLow == temp1->WFD.nFileSizeLow ) {
      flagC = true;
      flagM = true;
      flagS = true;
      flagB = true;

      strcpy(tem1, inListF->PathP);
      strcat(tem1, "\\");
      strcat(tem1, inListF->WFD.cFileName);
      strcpy(tem2, temp1->PathP);
      strcat(tem2, "\\");
      strcat(tem2, temp1->WFD.cFileName);

      if (CRC32)
        if (pathCRC(tem1) == pathCRC(tem2))
          flagC = true;
        else
          flagC = false;


      if (BITscan)
        if (pathBIT(tem1, tem2))
          flagB = true;
        else
          flagB = false;

      if (MD5) {
        char out1[64 + 9];
        char out2[64 + 9];
        pathMD5(tem1, out1);
        pathMD5(tem2, out2);

        if (!strcmp(out1, out2))
          flagM = true;
        else
          flagM = false;
      }

      if (SHA256) {
        char out1[64 + 9];
        char out2[64 + 9];
        pathSHA256(tem1, out1);
        pathSHA256(tem2, out2);

        if (!strcmp(out1, out2))
          flagS = true;
        else
          flagS = false;

      }

      if(flagC && flagM && flagS && flagB) {
        temp2 = temp1->next;
        LP = temp1->PathP;
        temp3 = ListF::add(&temp1->WFD, &temp1->HD, &LP, temp3);
        inListF->del(temp1, inListF);
        temp1 = temp2;
      } else
        temp1 = temp1->next;

    } else
      temp1 = temp1->next;
  }

  if (temp3) {
    LP = inListF->PathP;
    temp3 = ListF::add(&inListF->WFD, &inListF->HD, &LP, temp3);
    inListL = ListL::add(temp3, inListL);
  }

  inListF = ListF::del(inListF, inListF);

  if (inListF)
    ListCleen();
}


void Poisk::PP(void) {
  if(!inListP)
    return;

  // ќчистка непраельно веденных
  ListP* LP = inListP;
  ListP* LP2;
  bool  tempB = true; // лишн€€
  int sizPath;

  while( LP ) {
    sizPath = strlen(LP->PathP);

    if ( sizPath >= 2 ) {
      if ( LP->PathP[sizPath - 1] == '\\') {
        if (!SetCurrentDirectory(LP->PathP)) {
          LP2 = LP->next;
          inListP = LP->del(LP, inListP);   // delite
          LP = LP2;
          tempB = false;
        }
      } else {
        strcat(LP->PathP, "\\");

        if (!SetCurrentDirectory(LP->PathP)) {

          LP2 = LP->next;
          inListP = LP->del(LP, inListP);   // delite
          LP = LP2;
          tempB = false;
        }
      }
    } else {
      LP2 = LP->next;
      inListP = LP->del(LP, inListP);   // delite
      LP = LP2;
      tempB = false;
    }

    if (!LP)
      break;

    if(tempB)
      LP = LP->next;
    else
      tempB = true;
  }

  // ќчистка дубликатов
  if(!inListP)
    return;

  if(!inVlos) { //≈сли не искать во вложенных !!!!!
    ListP* temp1 = inListP;
    ListP* temp2 = inListP->next;
    ListP* temp22;

    while( temp1 ) {
      temp2 = temp1->next;

      while( temp2 ) {
        if ( !strcmp(temp1->PathP, temp2->PathP) ) {
          temp22 = temp2->next;
          inListP = temp1->del(temp2, inListP);
          temp2 = temp22;
        } else
          temp2 = temp2->next;
      }

      temp1 = temp1->next;
    }
  } else { // ¬ принцепи похож на "если не искать во вложенных" разница только в паре строчек можно сократить
    ListP* temp1 = inListP;
    ListP* temp2 = inListP->next;
    ListP* temp22;
    tempB = true;

    while( temp1 ) {
      temp2 = temp1->next;

      while( temp2 ) {
        if ( !strncmp (temp1->PathP, temp2->PathP, strlen(temp2->PathP)) || !strncmp(temp2->PathP, temp1->PathP, strlen(temp1->PathP))  ) {
          if ( !strncmp (temp2->PathP, temp1->PathP, strlen(temp1->PathP )) ) {
            temp22 = temp2->next;
            inListP = temp1->del(temp2, inListP);
            temp2 = temp22;
            continue;
          }

          temp22 = temp1->next;
          inListP = temp2->del(temp1, inListP);
          temp1 = temp22;
          tempB = false;
          break;
        } else
          temp2 = temp2->next;
      }

      if (tempB)
        temp1 = temp1->next;
      else
        tempB = true;
    }
  }


}


void Poisk::TreeB(LPCSTR  LP) {

  HANDLE han = NULL;
  WIN32_FIND_DATA WFD;

  char PolPath[MAX_PATH];
  strcpy(PolPath, LP);
  strcat(PolPath, "*.*");

  if(inVlos) {
    han = FindFirstFile(PolPath, &WFD);

    do {
      if (!strcmp(WFD.cFileName, ".") || !strcmp(WFD.cFileName, ".."))
        continue;

      if (WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && Poisk::AtribBool(&WFD.dwFileAttributes, &inDerek)) {
        char next[MAX_PATH];
        strcpy(next, LP);
        strcat(next, "\\");
        strcat(next, WFD.cFileName);
        strcat(next, "\\");
        TreeB (next);
      }
    } while (FindNextFile(han, &WFD));

    FindClose (han);
  }

  strcpy(PolPath, LP);
  strcat(PolPath, inParametr);


  if ((han = FindFirstFile(PolPath, &WFD)) == INVALID_HANDLE_VALUE)
    return;

  do
    if (!(WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && Poisk::AtribBool(&WFD.dwFileAttributes, &inFile))
      inListF = ListF::add(&WFD, &han, &LP, inListF);

  while (FindNextFile(han, &WFD));

  FindClose (han);
}


bool Poisk::AtribBool(DWORD* WFD, DWORD* par) {
  if (*par == NULL)
    return true;

  if (inIFI) { // если параметор галок »
    if (*WFD&*par == *par )
      return true;
    else
      return false;
  } else { // или  !!!!!!!!!!!!!!!!!// проверить не накас€чил ли € с двойныи » *&*&(
    if(*WFD&*par & (1 << FILE_ATTRIBUTE_ARCHIVE)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_COMPRESSED)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_ENCRYPTED)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_HIDDEN)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_NORMAL)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_OFFLINE)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_READONLY)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_REPARSE_POINT)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_SPARSE_FILE)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_SYSTEM)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_TEMPORARY)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)) return true;

    if(*WFD&*par & (1 << FILE_ATTRIBUTE_VIRTUAL)) return true;
  }

  return false;
}

void Poisk::TreeBP(LPCSTR  LP) {
  char PolPath[MAX_PATH];

  HANDLE han = NULL;
  WIN32_FIND_DATA WFD;
  bool strTemp = false;

  strcpy(PolPath, LP);
  strcat(PolPath, "*.*");

  han = FindFirstFile(PolPath, &WFD);

  do {
    if (!strcmp(WFD.cFileName, ".") || !strcmp(WFD.cFileName, ".."))
      continue;

    if ( WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && inVlos && Poisk::AtribBool(&WFD.dwFileAttributes, &inDerek)) {
      char next[MAX_PATH];
      strcpy(next, LP);
      strcat(next, "\\");
      strcat(next, WFD.cFileName);
      strcat(next, "\\");
      TreeBP(next);
    }

    strTemp = false;

    if (inParametr) {
      if (strstr(WFD.cFileName, inParametr))
        strTemp = true;
    } else
      strTemp = true;

    if ( !(WFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && strTemp && Poisk::AtribBool(&WFD.dwFileAttributes, &inFile))
      inListF = ListF::add(&WFD, &han, &LP, inListF);

  } while (FindNextFile(han, &WFD));

  FindClose (han);
}

Poisk::Poisk(): inVlos(true),   // искать во вложеных
  inTabul(true),   // имеет ли значение табул€ци€ параметра
  inParametr(NULL),  // параметр поиска
  inListP(NULL),   // список папок дл€ поиска
  inListF(NULL),   // список фаелов после поиска
  inListL(NULL),   // список списков
  inFile (NULL),   // параметры поиска фаила
  inDerek(NULL),   // параметры поиска деректории
  inIFI(true),     // и переметры или или если true то »
  CRC32(false),    // —равнение по CRC
  MD5(false),      // —равнение по MD5
  SHA256(false),   // —равнение по SHA-256
  BITscan(false) {
}
