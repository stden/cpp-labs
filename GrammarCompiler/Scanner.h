#pragma once

#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

namespace scan {

    class ScannerException : public std::exception
    {
        public:
            ScannerException( const char* msg ) : message( msg ) {}
            ScannerException( const std::string& msg ) : message( msg ) {}

            virtual const char* what() const throw() { return message.c_str(); }
            virtual ~ScannerException() throw() {}

        private:
			ScannerException();
            const std::string message;
    };

	class Scanner
	{
	public:
		Scanner( const char* fileName )				{ f.open( fileName ); }
		void	AttachFile( const char* fileName )	{ f.close(); f.open( fileName ); }
		void	Reset()								{ f.seekg(0, ios::beg); }
		string*	GetLexeme();
		virtual ~Scanner()							{ f.close(); }

	protected:
		string*		ReadWord();
		string*		ReadStrConst( const char commas );
		void		SkipComments();

	private:
		Scanner();
		bool		IsLetter( const char ) const;
		bool		IsDigit( const char ) const;
		bool		IsDelimeter( const char ) const;
		ifstream	f;
		char		c;
	};


	inline bool Scanner::IsLetter( const char c ) const
	{
		return c>='a' && c<='z' || c>='A' && c<='Z' || c=='_';
	}

	inline bool Scanner::IsDigit( const char c ) const
	{
		return c>='0' && c<='9';
	}

	inline bool Scanner::IsDelimeter( const char c ) const
	{
		return c==' ' || c=='\t' || c=='\n' || c=='\r';

	}

	string* Scanner::ReadStrConst( const char commas )
	{
		string *s = new string;
		*s=commas;
		try	{
			while ( (c=f.get()) && c!=commas ) {
				if ( c=='/' && f.peek()==commas ) c=f.get();
				if ( c=='\n' ) throw ScannerException("new line in constant");
				(*s)+=c;
			}
			(*s)+=commas;
		}
		catch ( ios_base::failure& e ) { throw ScannerException(e.what()); }
		return s;
	}

	string* Scanner::ReadWord()
	{
		string *s = new string;
		try	{
			while ( (c=f.get()) && (IsLetter(c) || IsDigit(c)) ) {
				(*s)+=c;
			}
			f.putback(c);
		}
		catch ( ios_base::failure& e ) { throw ScannerException(e.what()); }
		return s;
	}

	inline void Scanner::SkipComments()
	{
		while ( c=='/' && f.peek()=='/' ) {
			f.ignore(256, '\n');
			f>>c;
		}
	}

	string* Scanner::GetLexeme()
	{
		if ( !f.is_open() ) throw ScannerException( "source file was not opened" );
		string *s = new string;
		try	{
			do c=f.get(); while ( IsDelimeter(c) );
			SkipComments();
			if ( f.eof() ) return 0;
			if ( IsLetter(c) || IsDigit(c) ) { *s = c; *s += *ReadWord(); }
			else if ( c=='\'' || c=='"' ) s = ReadStrConst(c);
			else *s=c;
		}
		catch ( ios_base::failure& e ) { throw ScannerException(e.what()); }

		return s;
	}
}