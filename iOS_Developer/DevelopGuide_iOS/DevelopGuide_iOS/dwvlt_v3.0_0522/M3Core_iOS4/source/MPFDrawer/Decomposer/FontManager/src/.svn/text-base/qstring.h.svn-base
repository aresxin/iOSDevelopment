#ifndef QSTRING_H_
#define QSTRING_H_

#include <string>
#include "qnamespace.h"

class QString
{
private:
	std::string m_str;
	
public:
	
	enum SectionFlags
	{
		SectionDefault				= 0x00,
		SectionSkipEmpty			= 0x01,
		SectionIncludeLeadingSep	= 0x02,
		SectionIncludeTrailingSep	= 0x04,
		SectionCaseInsensitiveSeps	= 0x08
	};

	QString ();
	QString ( const QString & s );
	QString ( const char * str );

	/* QChar未実装	
	QString ( QChar ch );
	*/

	/* QByteArray、QChar未実装
	QString ( const QByteArray & ba );
	QString ( const QChar * unicode, unsigned int length );
	*/
	
	virtual ~QString ();

	QString & operator= ( const QString & s );	
	QString & operator= ( const char * str );

	/* QCString未実装
	QString & operator= ( const QCString & cs );
	*/
	
	/* QChar未実装	
	QString & operator= ( QChar c );
	*/
	
	QString & operator= ( char c );
	bool isNull () const;
	bool isEmpty () const;
	unsigned int length () const;
	
	/*
	void truncate ( unsigned int newLen );
	*/
	
	/* QChar未実装	
	QString & fill ( QChar c, int len = -1 );
	*/
	
	/*
	QString copy () const; // (obsolete)
	QString arg ( long a, int fieldwidth = 0, int base = 10 ) const;
	QString arg ( unsigned long a, int fieldwidth = 0, int base = 10 ) const;
	QString arg ( int a, int fieldwidth = 0, int base = 10 ) const;
	QString arg ( unsigned int a, int fieldwidth = 0, int base = 10 ) const;
	QString arg ( short a, int fieldwidth = 0, int base = 10 ) const;
	QString arg ( unsigned short a, int fieldwidth = 0, int base = 10 ) const;
	QString arg ( char a, int fieldwidth = 0 ) const;

	/* QChar未実装	
	QString arg ( QChar a, int fieldwidth = 0 ) const;
	*/
	
	/*
	QString arg ( const QString & a, int fieldwidth = 0 ) const;
	QString arg ( double a, int fieldwidth = 0, char fmt = 'g', int prec = -1 ) const;
	QString & sprintf ( const char * cformat, ... );
	*/
	
	/* QChar未実装	
	int find ( QChar c, int index = 0, bool cs = TRUE ) const;
	*/
	
	/*
	int find ( char c, int index = 0, bool cs = true ) const;
	*/
	
	/* csは未対応 */
	int find ( const QString & str, int index = 0, bool cs = true ) const;
	
	/* QRegExp未実装
	int find ( const QRegExp & rx, int index = 0 ) const;
	*/
	
	int find ( const char * str, int index = 0 ) const;
	
	/* QChar未実装
	int findRev ( QChar c, int index = -1, bool cs = true ) const;
	*/
	
	/*
	int findRev ( char c, int index = -1, bool cs = true ) const;
	int findRev ( const QString & str, int index = -1, bool cs = true ) const;
	*/
	
	/* QRegExp未実装
	int findRev ( const QRegExp & rx, int index = -1 ) const;
	*/
	
	/*
	int findRev ( const char * str, int index = -1 ) const;
	*/
	
	/* QChar未実装
	int contains ( QChar c, bool cs = true ) const;
	*/
	
	/*
	int contains ( char c, bool cs = true ) const;
	int contains ( const char * str, bool cs = true ) const;
	int contains ( const QString & str, bool cs = true ) const;
	*/
	
	/* QRegExp未実装
	int contains ( const QRegExp & rx ) const;
	*/
	
	/* QChar未実装	
	QString section ( QChar sep, int start, int end = 0xffffffff, int flags = SectionDefault ) const;
	*/
	
	/*
	QString section ( char sep, int start, int end = 0xffffffff, int flags = SectionDefault ) const;
	QString section ( const char * sep, int start, int end = 0xffffffff, int flags = SectionDefault ) const;
	QString section ( const QString & sep, int start, int end = 0xffffffff, int flags = SectionDefault ) const;
	*/
	
	/* QRegExp未実装
	QString section ( const QRegExp & reg, int start, int end = 0xffffffff, int flags = SectionDefault ) const;
	*/
	
	/*
	QString left ( unsigned int len ) const;
	QString right ( unsigned int len ) const;
	QString mid ( unsigned int index, unsigned int len = 0xffffffff ) const;
	*/
	
	/* QChar未実装	
	QString leftJustify ( unsigned int width, QChar fill = ' ', bool truncate = false ) const;
	QString rightJustify ( unsigned int width, QChar fill = ' ', bool truncate = false ) const;
	*/
	
	/*
	QString lower () const;
	QString upper () const;
	QString stripWhiteSpace () const;
	QString simplifyWhiteSpace () const;
	QString & insert ( unsigned int index, const QString & s );
	*/
	
	/* QChar未実装	
	QString & insert ( unsigned int index, const QChar * s, unsigned int len );
	QString & insert ( unsigned int index, QChar c );
	*/
	
	/*
	QString & insert ( unsigned int index, char c );
	QString & append ( char ch );
	*/
	
	/* QChar未実装	
	QString & append ( QChar ch );
	*/
	
	/*
	QString & append ( const QString & str );
	QString & prepend ( char ch );
	*/
	
	/* QChar未実装	
	QString & prepend ( QChar ch );
	*/
	
	/*
	QString & prepend ( const QString & s );
	QString & remove ( unsigned int index, unsigned int len );
	QString & replace ( unsigned int index, unsigned int len, const QString & s );
	*/

	/* QChar未実装	
	QString & replace ( unsigned int index, unsigned int len, const QChar * s, unsigned int slen );
	*/
	
	/* QRegExp未実装
	QString & replace ( const QRegExp & rx, const QString & str );
	*/
	
	/*
	short toShort ( bool * ok = 0, int base = 10 ) const;
	unsigned short toUshort ( bool * ok = 0, int base = 10 ) const;
	int toInt ( bool * ok = 0, int base = 10 ) const;
	unsigned int toUint ( bool * ok = 0, int base = 10 ) const;
	long toLong ( bool * ok = 0, int base = 10 ) const;
	unsigned long toULong ( bool * ok = 0, int base = 10 ) const;
	float toFloat ( bool * ok = 0 ) const;
	double toDouble ( bool * ok = 0 ) const;
	QString & setNum ( short n, int base = 10 );
	QString & setNum ( unsigned short n, int base = 10 );
	QString & setNum ( int n, int base = 10 );
	QString & setNum ( unsigned int n, int base = 10 );
	QString & setNum ( long n, int base = 10 );
	QString & setNum ( unsigned long n, int base = 10 );
	QString & setNum ( float n, char f = 'g', int prec = 6 );
	QString & setNum ( double n, char f = 'g', int prec = 6 );
	*/
	
	/* QChar未実装	
	void setExpand ( unsigned int index, QChar c ); // (obsolete)
	*/
	
	/*
	QString & operator+= ( const QString & str );
	*/
	
	/* QChar未実装	
	QString & operator+= ( QChar c );
	*/
	
	/*
	QString & operator+= ( char c );
	*/

	/* QChar未実装	
	QChar at ( unsigned int i ) const;
	QChar operator[] ( int i ) const;
	QCharRef at ( unsigned int i );
	QCharRef operator[] ( int i );
	QChar constref ( unsigned int i ) const;
	QChar & ref ( unsigned int i );
	const QChar * unicode () const;
	*/
	
	const char * ascii () const; // (obsolete)
	const char * latin1 () const;

	/* QCString未実装
	QCString utf8 () const;
	QCString local8Bit () const;
	bool operator! () const;
	*/
	
	operator const char * () const;

	/* QChar未実装	
	QString & setUnicode ( const QChar * unicode, unsigned int len );
	*/
	
	/* 今回は処理場変換が必要ないので文字数分だけ"X"を書き込むこととする。*/
	QString & setUnicodeCodes ( const unsigned short * unicode_as_ushorts, unsigned int len );
	QString & setLatin1 ( const char * str, int len = -1 );
	
	/*
	int compare ( const QString & s ) const;
	int localeAwareCompare ( const QString & s ) const;
	void compose ();
	*/

	/*	
	const char * data () const; // (obsolete)
	*/
	
	/*
	bool startsWith ( const QString & s ) const;
	bool endsWith ( const QString & s ) const;
	void setLength ( unsigned int newLen );
	*/
	
public:

	/*
	static QString number ( long n, int base = 10 );
	static QString number ( unsigned long n, int base = 10 );
	static QString number ( int n, int base = 10 );
	static QString number ( unsigned int n, int base = 10 );
	static QString number ( double n, char f = 'g', int prec = 6 );
	*/

	static QString fromLatin1 ( const char * chars, int len = -1 );
	static QString fromUtf8 ( const char * utf8, int len = -1 );
	static QString fromLocal8Bit ( const char * local8Bit, int len = -1 );

	/*
	static int compare ( const QString & s1, const QString & s2 );
	static int localeAwareCompare ( const QString & s1, const QString & s2 );
	*/
};

#endif /*QSTRING_H_*/
