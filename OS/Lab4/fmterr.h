#ifndef FMTERR_H
#define FMTERR_H

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

//--------------------------------------------------------------
inline
std::string formatMessage(unsigned errorCode) {
  char* pbuf = 0;
  DWORD dwChars = ::FormatMessage(
                    FORMAT_MESSAGE_FROM_SYSTEM
                    | FORMAT_MESSAGE_ALLOCATE_BUFFER
                    , 0, errorCode
                    , MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)
                    , (LPTSTR)&pbuf, 1024, NULL
                  );
  std::string res(pbuf, std::string::size_type(dwChars));
  LocalFree((HLOCAL)pbuf);
  return res;
}
//--------------------------------------------------------------
inline
std::string formatMessage() {
  return formatMessage(GetLastError());
}
//--------------------------------------------------------------

#endif /* FMTERR_H */

