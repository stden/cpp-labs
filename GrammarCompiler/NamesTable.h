#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

namespace names_table {

class AliasesTableException : public std::exception {
 public:
  AliasesTableException( const char* msg ) : message( msg ) {}
  AliasesTableException( const std::string& msg ) : message( msg ) {}

  virtual const char* what() const throw() {
    return message.c_str();
  }
  virtual ~AliasesTableException() throw() {}

 private:
  AliasesTableException& operator=( const AliasesTableException& ) {}
  AliasesTableException();
  const std::string message;
};

class Alias {
 public:
  string Name;
  bool   IsTerminal;
  string Value;

  Alias() {}
  Alias( const string name, const bool isTerminal, const string value ) :
    Name(name), IsTerminal(isTerminal), Value(value) {}
  virtual ~Alias() {}
};

class AliasesTable {
 public:
  AliasesTable() {};
  void  AddAlias( const Alias& );
  Alias GetAlias( const size_t i ) const  {
    return Alias(aliases[i]);
  }
  size_t  ItemsCount() const            {
    return aliases.size();
  }
  int   FindAliasByName( const char* ) const;
  int   FindAliasByChar( const char ) const;

 private:
  vector<Alias> aliases;
};

void AliasesTable::AddAlias( const Alias& alias ) {
  for ( unsigned int i = 0; i < aliases.size(); ++i )
    if ( aliases[i].Name == alias.Name ) throw AliasesTableException( "alias already defined" );

  aliases.push_back( alias );
}

int AliasesTable::FindAliasByChar( const char ) const {
  for ( unsigned int i = 0; i < aliases.size(); ++i )
    for ( unsigned int j = 0; j < aliases.size(); ++j )
      if ( aliases[i].Value.find(aliases[i].Value[j]) != string::npos )
        return i;

  return -1;
}

int AliasesTable::FindAliasByName( const char* name ) const {
  for ( unsigned int i = 0; i < aliases.size(); ++i )
    if ( aliases[i].Name == name ) return i;

  return -1;
}
}