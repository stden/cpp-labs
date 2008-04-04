#ifndef TOOEM_H
#define TOOEM_H

#pragma comment( lib, "user32" )

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

#include <malloc.h>

inline std::string toOem(const std::string &ansiStr)
{
    char *buf = (char*)_alloca(ansiStr.size()+1);
    CharToOem( ansiStr.c_str(), buf);
    return std::string(buf);
}

#endif /* TOOEM_H */



