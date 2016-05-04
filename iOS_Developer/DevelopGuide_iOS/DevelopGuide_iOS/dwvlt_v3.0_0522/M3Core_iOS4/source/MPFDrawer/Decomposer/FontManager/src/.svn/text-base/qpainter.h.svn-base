#ifndef QPAINTER_H_
#define QPAINTER_H_

#include "qpixmap.h"
#include "qpainter.h"
#include "qfont.h"
#include "qfontmetrics.h"

typedef unsigned int QTextParag;

/* QTラッパーでの代替フォント描画の塗りつぶし指定 */
#define FONT_BOX_FILL false

class QPainter
{
private:
	QFont		m_font;
	QPixmap *	m_pPixmap;
	
public:

	enum CoordinateMode
	{
		CoordDevice,
		CoordPainter
	};

	enum TextDirection
	{
		Auto,
		RTL,
		LTR
	};

	QPainter ();
	QPainter ( const QPaintDevice * pd, bool unclipped = false );
	/*
	QPainter ( const QPaintDevice * pd, const QWidget * copyAttributes, bool unclipped = false )
	*/

	virtual ~QPainter ();

	bool begin ( const QPaintDevice * pd, bool unclipped = false );
	/*
	bool begin ( const QPaintDevice * pd, const QWidget * copyAttributes, bool unclipped = false )
	*/
	bool end ();
	/*
	QPaintDevice * device () const
	QGfx * internalGfx ()
	bool isActive () const
	void flush ( const QRegion & region, CoordinateMode cm = CoordDevice )
	void flush ()
	void save ()
	void restore ()
	QFontMetrics fontMetrics () const
	QFontInfo fontInfo () const
	*/

	const QFont & font () const;
	void setFont ( const QFont & font );

	/*
	const QPen & pen () const
	void setPen ( const QPen & pen )
	void setPen ( PenStyle style )
	void setPen ( const QColor & color )
	const QBrush & brush () const
	void setBrush ( const QBrush & brush )
	void setBrush ( BrushStyle style )
	void setBrush ( const QColor & color )
	QPoint pos () const
	const QColor & backgroundColor () const
	void setBackgroundColor ( const QColor & c )
	BGMode backgroundMode () const
	void setBackgroundMode ( BGMode m )
	RasterOp rasterOp () const
	void setRasterOp ( RasterOp r )
	const QPoint & brushOrigin () const
	void setBrushOrigin ( int x, int y )
	void setBrushOrigin ( const QPoint & p )
	bool hasViewXForm () const
	bool hasWorldXForm () const
	void setViewXForm ( bool enable )
	QRect window () const
	void setWindow ( const QRect & r )
	void setWindow ( int x, int y, int w, int h )
	QRect viewport () const
	void setViewport ( const QRect & r )
	void setViewport ( int x, int y, int w, int h )
	void setWorldXForm ( bool enable )
	const QWMatrix & worldMatrix () const
	void setWorldMatrix ( const QWMatrix & m, bool combine = false )
	void saveWorldMatrix ()  (obsolete)
	void restoreWorldMatrix ()  (obsolete)
	void scale ( double sx, double sy )
	void shear ( double sh, double sv )
	void rotate ( double a )
	void translate ( double dx, double dy )
	void resetXForm ()
	QPoint xForm ( const QPoint & pv ) const
	QRect xForm ( const QRect & rv ) const
	QPointArray xForm ( const QPointArray & av ) const
	QPointArray xForm ( const QPointArray & av, int index, int npoints ) const
	QPoint xFormDev ( const QPoint & pd ) const
	QRect xFormDev ( const QRect & rd ) const
	QPointArray xFormDev ( const QPointArray & ad ) const
	QPointArray xFormDev ( const QPointArray & ad, int index, int npoints ) const
	void setClipping ( bool enable )
	bool hasClipping () const
	QRegion clipRegion ( CoordinateMode m = CoordDevice ) const
	*/

	void setClipRect ( const QRect & r, CoordinateMode m = CoordDevice );
	void setClipRect ( int x, int y, int w, int h, CoordinateMode m = CoordDevice );

	/*
	void setClipRegion ( const QRegion & rgn, CoordinateMode m = CoordDevice )
	void drawPoint ( int x, int y )
	void drawPoint ( const QPoint & p )
	void drawPoints ( const QPointArray & a, int index = 0, int npoints = -1 )
	void moveTo ( int x, int y )
	void moveTo ( const QPoint & p )
	void lineTo ( int x, int y )
	void lineTo ( const QPoint & p )
	void drawLine ( int x1, int y1, int x2, int y2 )
	void drawLine ( const QPoint & p1, const QPoint & p2 )
	void drawRect ( int x, int y, int w, int h )
	void drawRect ( const QRect & r )
	void drawWinFocusRect ( int x, int y, int w, int h )
	void drawWinFocusRect ( int x, int y, int w, int h, const QColor & bgColor )
	void drawWinFocusRect ( const QRect & r )
	void drawWinFocusRect ( const QRect & r, const QColor & bgColor )
	void drawRoundRect ( int x, int y, int w, int h, int xRnd = 25, int yRnd = 25 )
	void drawRoundRect ( const QRect & r, int xRnd = 25, int yRnd = 25 )
	void drawEllipse ( int x, int y, int w, int h )
	void drawEllipse ( const QRect & r )
	void drawArc ( int x, int y, int w, int h, int a, int alen )
	void drawArc ( const QRect & r, int a, int alen )
	void drawPie ( int x, int y, int w, int h, int a, int alen )
	void drawPie ( const QRect & r, int a, int alen )
	void drawChord ( int x, int y, int w, int h, int a, int alen )
	void drawChord ( const QRect & r, int a, int alen )
	void drawLineSegments ( const QPointArray & a, int index = 0, int nlines = -1 )
	void drawPolyline ( const QPointArray & a, int index = 0, int npoints = -1 )
	void drawPolygon ( const QPointArray & a, bool winding = false, int index = 0, int npoints = -1 )
	void drawConvexPolygon ( const QPointArray & pa, int index = 0, int npoints = -1 )
	void drawCubicBezier ( const QPointArray & a, int index = 0 )
	void drawPixmap ( int x, int y, const QPixmap & pixmap, int sx = 0, int sy = 0, int sw = -1, int sh = -1 )
	void drawPixmap ( const QPoint & p, const QPixmap & pm, const QRect & sr )
	void drawPixmap ( const QPoint & p, const QPixmap & pm )
	void drawPixmap ( const QRect & r, const QPixmap & pm )
	void drawImage ( int x, int y, const QImage & image, int sx = 0, int sy = 0, int sw = -1, int sh = -1, int conversionFlags = 0 )
	void drawImage ( const QPoint &, const QImage &, const QRect & sr, int conversionFlags = 0 )
	void drawImage ( const QPoint & p, const QImage & i, int conversion_flags = 0 )
	void drawImage ( const QRect & r, const QImage & i )
	void drawTiledPixmap ( int x, int y, int w, int h, const QPixmap & pixmap, int sx = 0, int sy = 0 )
	void drawTiledPixmap ( const QRect & r, const QPixmap & pm, const QPoint & sp )
	void drawTiledPixmap ( const QRect & r, const QPixmap & pm )
	void drawPicture ( const QPicture & pic )  (obsolete)
	void drawPicture ( int x, int y, const QPicture & pic )
	void drawPicture ( const QPoint & p, const QPicture & pic )
	void fillRect ( int x, int y, int w, int h, const QBrush & brush )
	void fillRect ( const QRect & r, const QBrush & brush )
	void eraseRect ( int x, int y, int w, int h )
	void eraseRect ( const QRect & r )
	*/

	/*
	void drawText ( int x, int y, const QString & str, int len = -1, TextDirection dir = Auto )
	void drawText ( const QPoint &, const QString & str, int len = -1, TextDirection dir = Auto )
	void drawText ( int x, int y, const QString & str, int pos, int len, TextDirection dir = Auto )
	void drawText ( const QPoint & p, const QString & str, int pos, int len, TextDirection dir = Auto )
	*/

	void drawText ( int x, int y, int w, int h, int flags, const QString & str, int len = -1, QRect * br = 0, QTextParag ** internal = 0 );
	void drawText ( const QRect & r, int flags, const QString & str, int len = -1, QRect * br = 0, QTextParag ** internal = 0 );
	QRect boundingRect ( int x, int y, int w, int h, int flags, const QString & str, int len = -1, QTextParag ** internal = 0 );
	QRect boundingRect ( const QRect & r, int flags, const QString & str, int len = -1, QTextParag ** internal = 0 );

	/*
	int tabStops () const
	void setTabStops ( int ts )
	int * tabArray () const
	void setTabArray ( int * ta )
	HDC handle () const
	*/

//public:	
	/*
	static void redirect ( QPaintDevice * pdev, QPaintDevice * replacement )
	static void initialize ()
	static void cleanup ()
	*/
};

#endif /*QPAINTER_H_*/
