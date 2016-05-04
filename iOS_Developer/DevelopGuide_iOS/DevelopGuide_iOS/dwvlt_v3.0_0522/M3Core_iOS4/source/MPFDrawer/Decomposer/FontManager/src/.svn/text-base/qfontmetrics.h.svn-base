#ifndef QFONTMETRICS_H_
#define QFONTMETRICS_H_

#include "qfont.h"
#include "qrect.h"
#include "qnamespace.h"

#define ASCENT_RATE	(60)	// ピクセルサイズに対するパーセンテージ
#define DESCENT_RATE	(20)	// ピクセルサイズに対するパーセンテージ
#define WIDTH_RATE		(55)	// ピクセルサイズに対するパーセンテージ
#define SPACING_RATE	(100)	// ピクセルサイズに対するパーセンテージ

class QFontMetrics
{
private:
	int m_ascent;
	int m_descent;
	int m_height;
	int m_width;
	int m_leading;
	int m_lineSpacing;
	
	QFontMetrics (){};
	
public:
	QFontMetrics ( const QFont & font );
	QFontMetrics ( const QFontMetrics & fm );
	virtual ~QFontMetrics ();
	
	QFontMetrics & operator= ( const QFontMetrics & fm );
	int ascent () const;
	int descent () const;
	int height () const;
	int leading () const;
	int lineSpacing () const;
	/*
	int minLeftBearing () const
	int minRightBearing () const
	*/
	int maxWidth () const;
	/*
	bool inFont ( QChar ch ) const
	int leftBearing ( QChar ch ) const
	int rightBearing ( QChar ch ) const
	*/
	int width ( const QString & str, int len = -1 ) const;
	/*
	int width ( QChar ch ) const
	*/
	int width ( char c ) const; // (obsolete)
	int charWidth ( const QString & str, int pos ) const;
	QRect boundingRect ( const QString & str, int len = -1 ) const;
	/*
	QRect boundingRect ( QChar ch ) const
	*/
	/* QTextParag不明
	QRect boundingRect ( int x, int y, int w, int h, int flgs, const QString & str, int len = -1, int tabstops = 0, int * tabarray = 0, QTextParag ** intern = 0 ) const
	QSize size ( int flgs, const QString & str, int len = -1, int tabstops = 0, int * tabarray = 0, QTextParag ** intern = 0 ) const
	*/
	/*
	int underlinePos () const;
	int strikeOutPos () const;
	int lineWidth () const;
	*/
};

#endif /*QFONTMETRICS_H_*/
