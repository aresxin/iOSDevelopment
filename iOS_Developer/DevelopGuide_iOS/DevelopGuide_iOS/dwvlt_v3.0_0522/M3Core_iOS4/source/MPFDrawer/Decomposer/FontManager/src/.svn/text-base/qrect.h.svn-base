#ifndef QRECT_H_
#define QRECT_H_

#include "qpoint.h"
#include "qsize.h"
#include "qnamespace.h"

class QRect
{
private:
	QCOORD m_top, m_bottom, m_left, m_right;
	
public:
	QRect ();
	QRect ( const QPoint & topLeft, const QPoint & bottomRight );
	QRect ( const QPoint & topLeft, const QSize & size );
	QRect ( int left, int top, int width, int height );
	QRect ( const QRect & r );
	QRect & operator= ( const QRect & r );
	bool isEmpty () const;
	bool isNull () const;
	bool isValid () const;
	
	/*
	QRect normalize () const;
	*/

	int left () const;
	int top () const;
	int right () const;
	int bottom () const;
  	QCOORD & rLeft ();
	QCOORD & rTop ();
	QCOORD & rRight ();
	QCOORD & rBottom ();
	int x () const;
	int y () const;
	void setLeft ( int pos );
	void setTop ( int pos );
	void setRight ( int pos );
	void setBottom ( int pos );
	void setX ( int x );
	void setY ( int y );
	QPoint topLeft () const;
	QPoint bottomRight () const;
	QPoint topRight () const;
	QPoint bottomLeft () const;
	QPoint center () const;
	void rect ( int * x, int * y, int * w, int * h ) const;
	void coords ( int * xp1, int * yp1, int * xp2, int * yp2 ) const;
	void moveTopLeft ( const QPoint & p );
	void moveBottomRight ( const QPoint & p );
	void moveTopRight ( const QPoint & p );
	void moveBottomLeft ( const QPoint & p );
	void moveCenter ( const QPoint & p );
	void moveBy ( int dx, int dy );
	void setRect ( int x, int y, int w, int h );
	void setCoords ( int xp1, int yp1, int xp2, int yp2 );
	void addCoords ( int xp1, int yp1, int xp2, int yp2 );
	QSize size () const;
	int width () const;
	int height () const;
	void setWidth ( int w );
	void setHeight ( int h );
	void setSize ( const QSize & s );

	/*
	QRect operator| ( const QRect & r ) const;
	QRect operator& ( const QRect & r ) const;
	QRect & operator|= ( const QRect & r );
	QRect & operator&= ( const QRect & r );
	bool contains ( const QPoint & p, bool proper = FALSE ) const;
	bool contains ( int x, int y, bool proper = FALSE ) const;
	bool contains ( const QRect & r, bool proper = FALSE ) const;
	QRect unite ( const QRect & r ) const;
	QRect intersect ( const QRect & r ) const;
	bool intersects ( const QRect & r ) const;
	*/
};

#endif /*QRECT_H_*/
