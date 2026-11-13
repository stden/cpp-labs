#pragma once

#include "Scanner.h"
#include <stdexcept>

using namespace scan;

namespace lex {

class LexerException : public std::exception {
 public:
  LexerException( const char* msg ) : message( msg ) {}
  LexerException( const std::string& msg ) : message( msg ) {}

  virtual const char* what() const throw() {
    return message.c_str();
  }
  virtual ~LexerException() throw() {}

 private:
  LexerException& operator=( const LexerException& ) {}
  LexerException();
  const std::string message;
};

enum Types { CHAR, CHAR_CONST, ID };
struct Lexeme {
  string*  pValue;
  Types type;
  Lexeme();
  Lexeme( string* val, const Types t ) : pValue(val), type(t) {}
};

class Lexer {
 public:
  Lexer( Scanner* sc ) : scanner(sc) {}
  Lexer( const char* fileName ) {
    scanner = new Scanner(fileName);
  }
  void  AttachFile( const char* fileName )  {
    scanner->AttachFile(fileName);
  }
  Lexeme* GetLexeme() const;

 private:
  Lexer();
  bool  IsValidChar( const char ) const;
  bool  IsValidCharConst( const char* ) const;
  bool  IsValidIdentifier( const char* ) const;
  bool  IsLetter( const char ) const;
  bool  IsDigit( const char ) const;

  Scanner*     scanner;
};

inline bool Lexer::IsLetter( const char c ) const {
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
}

inline bool Lexer::IsDigit( const char c ) const {
  return c >= '0' && c <= '9';
}

inline bool Lexer::IsValidIdentifier( const char* id ) const {
  // all id's are valid in this language
  do if ( !IsLetter(*id) && !IsDigit(*id) ) return false;

  while ( *++id );

  return true;
}

inline bool Lexer::IsValidChar( const char c ) const {
  if ( !(c == '<' || c == '>' || c == '-' || c == ',' || c == ';') ) return false;

  return true;
}

inline bool Lexer::IsValidCharConst( const char* t ) const {
  if ( (*t == '\'' || *t == '"') && *t != *(t + 2) ) return false;

  return true;
}

Lexeme* Lexer::GetLexeme() const {
  string* s = new string;

  try {
    s = scanner->GetLexeme();
  } catch( ScannerException& e ) {
    throw LexerException( e.what() );
  }

  if ( s == 0 ) return 0;

  /*if ( !IsValidIdentifier(s->c_str()) ) {
    if ( !IsValidChar(*s->c_str()) ) {
      if ( !IsValidCharConst(s->c_str()) )
        throw LexerException(string("   ")+*s);   // impossible to get here
      else return new Lexeme(s,CHAR_CONST);
      //throw LexerException("unknown character");
    }
    else return new Lexeme(s,CHAR);
    //throw LexerException(string("invalid identifier '")+*s+"'");
  }
  return new Lexeme(s,ID);*/
  if ( IsValidIdentifier(s->c_str()) ) return new Lexeme(s, ID);

  if ( IsValidChar(*s->c_str()) ) return new Lexeme(s, CHAR);

  if ( IsValidCharConst(s->c_str()) ) return new Lexeme(s, CHAR_CONST);

  return 0; // impossible due to scanner
}

}