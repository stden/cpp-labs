#pragma once

#include <vector>
#include <string>
#include "Lexer.h"
#include "NamesTable.h"

using namespace std;
using namespace lex;
using namespace names_table;

namespace parser {

    class ParserException : public std::exception
    {
        public:
            ParserException( const char* msg ) : message( msg ) {}
            ParserException( const std::string& msg ) : message( msg ) {}

            virtual const char* what() const throw() { return message.c_str(); }
            virtual ~ParserException() throw() {}

        private:
			ParserException();
            const std::string message;
    };


	typedef string Terminals;
	typedef string State;
	typedef vector<State> States;
	typedef	vector<Alias> Aliases;
	class Transfer {
	public:
		Terminals	terminals;
		States		states;
		Transfer() {}
		Transfer( Terminals terminals, States states ) { this->states=states; this->terminals=terminals; }
	};
	typedef vector<Transfer> Transfers;

	class Parser
	{
	public:
		Parser( const char *fileName ) {
			lexer = new Lexer( fileName );
			atable = new AliasesTable;
			terminals = new Terminals;
		}
		void		ParseFile();
		void		AttachFile(const char *fileName) { lexer->AttachFile(fileName); }
		string*		GetTerminalsString() const	{ return terminals; }
		States*		GetStatesVector() const		{ return states; }
		Transfers*	GetTransfersTable() const	{ return transfers; }

		AliasesTable	*atable;

	private:
		void		AddAlias( AliasesTable*, const Alias& );
		bool		ProcessNewBlock();
		Aliases*	ProcessAliases();
		States*		ProcessStates();
		Transfers*	ProcessTransfers();
		Alias*		ProcessAlias();
		Transfer*	ProcessTransfer();
		Terminals*	ProcessTerminalList();

		Lexer			*lexer;
		States			*states;
		Terminals		*terminals;
		Transfers		*transfers;

		Lexeme	*w;
	};

	void Parser::ParseFile()
	{
		try	{
			while ( ProcessNewBlock() );
		}
		catch( LexerException& e ) {
			throw ParserException( e.what() );
		}
	}

	bool Parser::ProcessNewBlock()
	{
		w = lexer->GetLexeme();
		if ( !w ) return 0;
		if ( *w->pValue != "<" ) throw ParserException( "'<' expected" );
		w = lexer->GetLexeme();
		if ( !w ) throw ParserException( "unexpected end of file" );

		if ( w->type != ID ) throw ParserException( "block specifier expected after '<'" );
		else if ( *w->pValue == "aliases" ) {
			Aliases *aliases = ProcessAliases();
			for ( unsigned int i=0; i<aliases->size(); ++i )
				AddAlias( atable, aliases->at(i) );
		}
		else if ( *w->pValue == "states" )		states = ProcessStates();
		else if ( *w->pValue == "transfers" )	transfers = ProcessTransfers();

		else { string e("invalid block specifier '"); e=e+w->pValue->c_str()+"'"; throw ParserException(e); }
		return true;
	}

	Alias* Parser::ProcessAlias()
	{
		Alias *a = new Alias;
		w = lexer->GetLexeme();
		if ( !w ) throw ParserException( "unexpected end of file" );
		if ( w->type != ID ) throw ParserException( "identifier missed after <" );
		else a->Name = *w->pValue;
		string *t = ProcessTerminalList();
		if ( !t ) {
			//alias of non-terminal
			if ( w->type != ID ) throw ParserException( "identifier or terminals missed in alias definition" ); 
			a->Value = *w->pValue;
			a->IsTerminal = false;
			w = lexer->GetLexeme();
			if ( *w->pValue != ">" ) throw ParserException( "'>' missed after alias value" );
		} else {
			a->Value = *t;
			a->IsTerminal = true;
		}
		return a;
	}

	Aliases* Parser::ProcessAliases()
	{
		w = lexer->GetLexeme();
		if ( !w ) throw ParserException( "unexpected end of file" );
		Aliases *av = new Aliases;

		while ( *w->pValue != ">" ) {
			if ( *w->pValue == "<" ) av->push_back( *ProcessAlias() );
			else throw ParserException( "alias' definition expected" );
			w = lexer->GetLexeme();
			if ( !w ) throw ParserException( "unexpected end of file" );
		}
		return av;
	}

	States* Parser::ProcessStates()
	{
		w = lexer->GetLexeme();
		if ( !w ) throw ParserException( "unexpected end of file" );
		if ( *w->pValue == ">" ) return 0;
		States *s = new States;

		while ( *w->pValue != ">" ) {
			if ( w->type != ID ) 
				throw ParserException( string("invalid symbol '")+*w->pValue+"' in states declaration, identifier expected" );
			s->push_back( *w->pValue );
			w = lexer->GetLexeme();
			if ( !w ) throw ParserException( "unexpected end of file" );
			if ( *w->pValue == "," ) {
				w = lexer->GetLexeme();
				if ( !w ) throw ParserException( "unexpected end of file" );
				if ( w->type != ID ) throw ParserException( "missing state identifier after ','" );
			}
		}
		return s;
	}
	Transfer* Parser::ProcessTransfer()
	{
		Transfer *t = new Transfer;
		Terminals *trms = new Terminals;

		trms = ProcessTerminalList();
		if ( trms && *trms!="" ) t->terminals = *trms;
		else if ( w->type == ID )
		{
			// get terminals from alias
			int i = atable->FindAliasByName( w->pValue->c_str() );
			if ( i==-1 ) throw ParserException( string("undeclared alias '")+*w->pValue+"'" );
			Alias a = atable->GetAlias(i);
			if ( a.IsTerminal == false ) throw ParserException( string("alias '")+*w->pValue+"' of non-terminal is at terminals list" );
			t->terminals = a.Value;

			w = lexer->GetLexeme();
			if ( !w ) throw ParserException( "unexpected end of file" );
			if ( *w->pValue != ";" ) throw ParserException( "missing ';' after terminals" );
		}
		else throw ParserException( "alias or terminals missed after '<'" );


		States *s = ProcessStates();
		if ( !s ) throw ParserException( "missing states list" );
		if ( s->size() != states->size() ) throw ParserException( "not all transfer states have been defined" );
		t->states = *s;
		for ( unsigned int i=0; i<t->states.size(); ++i )
			if ( find(states->begin(), states->end(), t->states[i])==states->end() )
				throw ParserException( string("undeclared state '")+t->states[i]+"'" );

		return t;
	}
	Transfers* Parser::ProcessTransfers()
	{
		w = lexer->GetLexeme();
		if ( !w ) throw ParserException( "unexpected end of file" );
		Transfers *t = new Transfers;

		while ( *w->pValue != ">" )
		{
			if ( *w->pValue == "<" )
			{
				t->push_back( *ProcessTransfer() );
				*terminals += t->at(t->size()-1).terminals.c_str();
				for ( unsigned int i=0; i<terminals->size(); ++i )
				{
					unsigned int j=terminals->find(terminals->at(i));
					if ( j != terminals->rfind(terminals->at(i)) )
						throw ParserException( string("duplicate terminal '")+terminals->at(j)+"'"+"found in transfers" );
				}
			}
			else throw ParserException( "transfer's definition expected" );
			w = lexer->GetLexeme();
			if ( !w ) throw ParserException( "unexpected end of file" );
		}
		return t;
	}


	enum TListFSMState { START, TRMNL, TRMNL2, OK, ERROR };
	Terminals* Parser::ProcessTerminalList()
	{
		w = lexer->GetLexeme();
		if ( !w ) throw ParserException( "unexpected end of file" );
		if ( w->type != CHAR_CONST ) return 0;
		
		TListFSMState state = START;
		Terminals *s = new Terminals;
		char c=0;

		if ( w->type==CHAR_CONST ) c = w->pValue->at(1);
		while ( state != OK )
		{
			// кусок ламерства:
			switch ( state )
			{
			case START:
				if ( w->type==CHAR_CONST ) {
					state=TRMNL;
					if ( s->find(c) == string::npos ) (*s)+=c;
				}
				else return s;//throw ParserException( "terminal expected" );
				break;
			case TRMNL:
				if ( w->type==CHAR_CONST ) throw ParserException( "'-' or ',' missed between terminals" );
				else if ( w->pValue->at(0)=='-' ) state=TRMNL2;
				else if ( w->pValue->at(0)=='>' || w->type==ID ) state=OK;
				else if ( w->pValue->at(0)==',' ) state=START;
				else return s;//throw ParserException( "wrong character after terminal" );
				break;
			case TRMNL2:
				if ( w->type==CHAR_CONST ) {
					state=TRMNL;
					if ( c <= s->at( s->length()-1 ) ) throw ParserException( "invalid terminal range" );
				    for ( char x = s->at(s->length()-1) + 1; x <= c; ++x )
						if ( s->find(x)==string::npos ) s->operator +=(x);
				}
				else throw ParserException( "terminal missed after '-'" );
				break;
			}
			if ( state==OK ) break;
			// конец куска ламерства

			w = lexer->GetLexeme(); 
			if ( !w ) throw ParserException( "unexpected end of file" );
			if ( w->type==CHAR_CONST ) c = w->pValue->at(1);
		}

		//cout<<s->c_str()<<endl<<w->pValue->c_str()<<endl;
		return s;
	}

	void Parser::AddAlias( AliasesTable *at, const Alias& a )
	{
		// check whether alias is valid
		if ( a.IsTerminal )
		{
			for ( unsigned int i=0; i<at->ItemsCount(); ++i )
				for ( unsigned int j=0; j<at->GetAlias(i).Value.size(); ++j )
				if ( a.Value.find(at->GetAlias(i).Value[j]) != string::npos )
					throw ParserException( string("one or more terminals of the alias '")+a.Name+"' have already been specified in other alias" );
			for ( unsigned int j=0; j<a.Value.length(); ++j )
				if ( a.Value.find(a.Value[j]) != a.Value.rfind(a.Value[j]) )
					throw ParserException( string("duplicate terminals in alias '")+a.Name+"'" );
		}
		at->AddAlias( a );
	}

}