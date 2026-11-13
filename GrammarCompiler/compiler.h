#pragma once

#include "parser.h"
#include <algorithm>
#include <fstream>

using namespace parser;

namespace grm_compiler {
class GrammarCompiler {
 public:
  GrammarCompiler(const char* fileName) : parser(fileName), file(fileName) {}
  void AttachFile(const char* fileName) {
    parser.AttachFile(fileName);
    file = fileName;
  }
  //void Compile();
  void Check(const char* fileName);
 private:
  Parser parser;
  const char* file;
};

/*void GrammarCompiler::Compile()
{
  ofstream err( "errors.txt" );
  try {
  parser.ParseFile();
  States *s = parser.GetStatesVector();
  Transfers *t = parser.GetTransfersTable();
  Terminals *ts = parser.GetTerminalsString();

  }
  catch( ParserException& e ) { err<<*e.what()<<endl; }
}*/

void GrammarCompiler::Check(const char* fileName) {
  ifstream f(fileName);
  parser.ParseFile();
  Terminals* t = parser.GetTerminalsString();
  States* s = parser.GetStatesVector();
  Transfers* ts = parser.GetTransfersTable();
  State state;

  if ( s->size() > 0 ) state = s->at(0);

  char c;
  cout << '\n';

  if ( !f.is_open() ) return;

  while ( !f.eof() ) {
    f >> c;

    for ( unsigned int i = 0; i < ts->size(); ++i )
      if ( ts->at(i).terminals.find(c) != string::npos ) {
        unsigned int j = 0;

        while ( s->at(j) != state ) ++j;

        state = ts->at(i).states.at(j);
        cout << state << ' ';
        break;
      }

    if ( t->find(c) == string::npos ) cout << "? ";
  }

  cout << '\n';
}

}