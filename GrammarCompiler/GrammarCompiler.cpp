#include "stdafx.h"

#include "Scanner.h"
#include "NamesTable.h"
#include "Lexer.h"
#include "Parser.h"
#include <iostream>

#include "compiler.h"

using namespace scan;
using namespace lex;
using namespace parser;

int main(int argc, char** argv) {
  for ( int i = 0; i < argc; ++i ) cout << argv[i] << ' ';

  if ( !argv[1] ) {
    cout << "\nUsage:\nGrammarCompiler.exe <input file>";
    cin.get();
    return 0;
  }

  Parser p(argv[1]);

  try {
    p.ParseFile();
    (new grm_compiler::GrammarCompiler(argv[1]))->Check("check.txt");
  } catch( ParserException& e ) {
    cout << "\nError: " << e.what() << endl;
    cout << "==========================================================\n";
    return 0;
  }

  States* s = p.GetStatesVector();
  Transfers* t = p.GetTransfersTable();
  Terminals* ts = p.GetTerminalsString();
  cout << "\nTerminals used:\n";

  for ( size_t i = 0; i < ts->size(); ++i) cout << ts->at(i);

  cout << "\n\nStates:\n";

  for ( size_t i = 0; i < s->size(); ++i) cout << s->at(i) << ' ';

  cout << "\n\nTransfers:\n";

  for ( size_t i = 0; i < t->size(); ++i) {
    cout << t->at(i).terminals.c_str() << ' ';

    for ( size_t j = 0; j < t->at(i).states.size(); ++j )
      cout << t->at(i).states[j] << ' ';

    cout << endl;
  }

  cout << "\nAliases:\n";

  for ( size_t i = 0; i < p.atable->ItemsCount(); ++i)
    cout << p.atable->GetAlias(i).Name << ' ' << p.atable->GetAlias(i).IsTerminal << ' ' << p.atable->GetAlias(i).Value << endl;

  cout << "==========================================================\n";

  return 0;
}