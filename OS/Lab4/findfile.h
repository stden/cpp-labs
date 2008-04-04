#ifndef FINDFILE_H
#define FINDFILE_H

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#ifndef STRICT
    #define STRICT
#endif

#if !defined(_WINDOWS_)
    #include <windows.h>
#endif

#if !defined(_STRING_) && !defined(_STLP_STRING) && !defined(__STD_STRING) && !defined(_CPP_STRING) && !defined(_GLIBCXX_STRING)
    #include <string>
#endif

#if !defined(_IOSTREAM_) && !defined(_STLP_IOSTREAM) && !defined(__STD_IOSTREAM__) && !defined(_CPP_IOSTREAM) && !defined(_GLIBCXX_IOSTREAM)
    #include <iostream>
#endif

#ifndef TOOEM_H
    #include "toOem.h"
#endif

//--------------------------------------------------------------
// FindFN( const WIN32_FIND_DATA * pFindData)
template <typename FindFN>
class CFindFile
{
        HANDLE           hFind;
        WIN32_FIND_DATA  findData;
        FindFN           findFN;

    public:

        CFindFile(FindFN fn, const std::string& mask = "*.*") 
           : hFind(INVALID_HANDLE_VALUE)
           , findData()
           , findFN(fn)
           {
            hFind = FindFirstFile( mask.empty() ? "*.*" : mask.c_str(), &findData );
            if (hFind==INVALID_HANDLE_VALUE) return;
            findFN(&findData);
           }

        ~CFindFile()
           {
            FindClose(hFind);
           }

        bool nextFile()
           {
            if (hFind==INVALID_HANDLE_VALUE) return false;
            if (FindNextFile(hFind, &findData))
               {
                findFN(&findData);
                return true;
               }
            return false;
           }
};
//--------------------------------------------------------------
template <typename FindFN>
void enumFiles(FindFN fn, const std::string& mask = "*.*")
   {
    CFindFile<FindFN> ff(fn, mask);
    while(ff.nextFile()) ;
   }
//--------------------------------------------------------------
inline 
void fileAttrBuildStringHelper(std::string &str, DWORD attr, char chAttr)
   {
    if (attr) str.append(1, chAttr); 
    else      str.append(1, '-');
   }
#define CPFI_BAS(Mask, attrChar) fileAttrBuildStringHelper(res, (attrs & (Mask)), attrChar)

inline
std::string fileAttrBuildString(DWORD attrs)
   {
    std::string res;
    CPFI_BAS(FILE_ATTRIBUTE_ARCHIVE,    'A');
    CPFI_BAS(FILE_ATTRIBUTE_HIDDEN,     'H');
    CPFI_BAS(FILE_ATTRIBUTE_SYSTEM,     'S');
    CPFI_BAS(FILE_ATTRIBUTE_READONLY,   'R');
    CPFI_BAS(FILE_ATTRIBUTE_COMPRESSED, 'C');
    CPFI_BAS(FILE_ATTRIBUTE_ENCRYPTED,  'E');
    CPFI_BAS(FILE_ATTRIBUTE_DIRECTORY,  'D');
    CPFI_BAS(FILE_ATTRIBUTE_TEMPORARY,  'T');
    CPFI_BAS(FILE_ATTRIBUTE_OFFLINE,    'O');
    CPFI_BAS(FILE_ATTRIBUTE_REPARSE_POINT, 'P');
    CPFI_BAS(FILE_ATTRIBUTE_SPARSE_FILE,'F');
    return res;
   }
//--------------------------------------------------------------
inline 
DWORD charToFileAttr(char ch)
   {
    switch(ch)
       {
        case 'A': case 'a': return FILE_ATTRIBUTE_ARCHIVE;
        case 'H': case 'h': return FILE_ATTRIBUTE_HIDDEN;
        case 'S': case 's': return FILE_ATTRIBUTE_SYSTEM;
        case 'R': case 'r': return FILE_ATTRIBUTE_READONLY;
        case 'C': case 'c': return FILE_ATTRIBUTE_COMPRESSED;
        case 'E': case 'e': return FILE_ATTRIBUTE_ENCRYPTED;
        case 'D': case 'd': return FILE_ATTRIBUTE_DIRECTORY;
        case 'T': case 't': return FILE_ATTRIBUTE_TEMPORARY;
        case 'O': case 'o': return FILE_ATTRIBUTE_OFFLINE;
        case 'P': case 'p': return FILE_ATTRIBUTE_REPARSE_POINT;
        case 'F': case 'f': return FILE_ATTRIBUTE_SPARSE_FILE;
        return 0;
       }
   }
//--------------------------------------------------------------
inline
std::string fileAttrGetCaptionString()
   {
      return fileAttrBuildString(0xFFFFFFFF);
   }
//--------------------------------------------------------------
inline 
std::string fileTimeStrTime(const FILETIME &ft)
   {
    SYSTEMTIME st;
    if (!FileTimeToSystemTime(&ft, &st))
       {
        return std::string("<INVAL>");
       }

    char buf[256];
    wsprintf(buf, "%02d:%02d:%02d", 
                  (unsigned)st.wHour, 
                  (unsigned)st.wMinute, 
                  (unsigned)st.wSecond
            );
    return std::string(buf);
   }
//--------------------------------------------------------------
inline 
std::string fileTimeStrDate(const FILETIME &ft)
   {
    SYSTEMTIME st;
    if (!FileTimeToSystemTime(&ft, &st))
       {
        return std::string("<INVAL>");
       }

    char buf[256];
    wsprintf(buf, "%02d/%02d/%04d", 
                  (unsigned)st.wDay, 
                  (unsigned)st.wMonth, 
                  (unsigned)st.wYear
            );
    return std::string(buf);
   }
//--------------------------------------------------------------
inline 
std::string fileTimeStrDateTime(const FILETIME &ft)
   {
    return fileTimeStrDate(ft) + std::string(" ") + fileTimeStrTime(ft);
   }
//--------------------------------------------------------------
inline 
std::string fileSizeStr(DWORD hi, DWORD lo)
   {
    char buf[64];
    __int64 size = __int64(hi)<<32 | __int64(lo);
    if (size<1024)
       {
        wsprintf(buf, "%d", (DWORD)size);
       }
    else
       {
        size>>=10; // convert to kilobytes
        if (size<1024)
           {
            wsprintf(buf, "%d Kb", (DWORD)size);
           }
        else
           {
            size>>=10; // convert to megabytes
            wsprintf(buf, "%d Mb", (DWORD)size);
           }
       }
    return std::string(buf);
   }
//--------------------------------------------------------------
inline
std::string fileInfoGetCaptionString()
   {
    return fileAttrGetCaptionString() + std::string("  Creation time      ")
                                      + std::string("  Modification time  ")
                                      + std::string("  Last access time   ")
                                      + std::string("  Name  /  Size");
   }
//--------------------------------------------------------------
inline 
std::string fileInfoMakeStr( DWORD attrs, 
                        const FILETIME &ftCreationTime,
                        const FILETIME &ftModificationTime,
                        const FILETIME &ftLastAccessTime,
                        const std::string &name,
                        DWORD sizeHi, DWORD sizeLo
                      )
   {
    return fileAttrBuildString(attrs)              + std::string("  ")
         + fileTimeStrDateTime(ftCreationTime)     + std::string("  ")
         + fileTimeStrDateTime(ftModificationTime) + std::string("  ")
         + fileTimeStrDateTime(ftLastAccessTime)   + std::string("  ")
         + name + std::string("  ")
         + fileSizeStr(sizeHi, sizeLo);
   }
//--------------------------------------------------------------
template<typename Stream>
class CPrintFileInfo
{
        Stream &stream;

    public:

        CPrintFileInfo(Stream &s) : stream(s) {}
        CPrintFileInfo(const CPrintFileInfo & cpfi) : stream(cpfi.stream) {}
        void operator()(const WIN32_FIND_DATA * pFindData)
           {
            std::string name = pFindData->cFileName;
            if (name=="." || name=="..") 
               return; // skip curent and parent dirs
            stream<<toOem(
                          fileInfoMakeStr( pFindData->dwFileAttributes, 
                                           pFindData->ftCreationTime,
                                           pFindData->ftLastWriteTime,
                                           pFindData->ftLastAccessTime,
                                           name, 
                                           pFindData->nFileSizeHigh, 
                                           pFindData->nFileSizeLow
                                         )
                         )<<"\n";
           }
};

typedef CPrintFileInfo<std::ostream> COstreamPrintFileInfo;


#endif /* FINDFILE_H */

