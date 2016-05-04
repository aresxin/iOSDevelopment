/*
 * The QPixmap class is an off-screen, pixel-based paint device. 
 * Inherits QPaintDevice and Qt.
 * Inherited by QBitmap and QCanvasPixmap.
 */

#ifndef QPIXMAP_H_
#define QPIXMAP_H_

#include "qrect.h"
#include "qsize.h"
#include "qstring.h"
#include "qpaintdevice.h"
#include "qnamespace.h"
#include "qcolor.h"
#include "qpoint.h"

#ifndef QIMAGE_H_
class QImage;
#endif

class QPixmap : public QPaintDevice
{
protected:

	unsigned char *m_buffer;
	
	int m_bufSize;
	int m_lineSize;
	
	int m_height;
	int m_width;
	
	int m_depth;
	
	void initialize ( int w, int h, bool clear, int depth);
	void copy ( int w, int h, const void *buffer, int depth);

public:
	/*
	 This enum type defines the color modes that exist for converting QImage objects to QPixmap.
	 The current values are:

    * QPixmap::Auto - Select Color or Mono on a case-by-case basis.
    * QPixmap::Color - Always create colored pixmaps.
    * QPixmap::Mono - Always create bitmaps.
    */ 
	enum ColorMode
	{
		Auto,
		Color,
		Mono
	};

	/*
	 QPixmap has the choice of optimizing for speed or memory in a few places; the best choice varies from pixmap to pixmap but can generally be derived heuristically.
	 This enum type defines a number of optimization modes that you can set for any pixmap to tweak the speed/memory tradeoffs:

    * QPixmap::DefaultOptim - Whatever QPixmap::defaultOptimization() returns. A pixmap with this optimization will have whatever the current default optimization is. If the default optimization is changed using setDefaultOptimization, then this will not effect any pixmaps that have already been created.
    * QPixmap::NoOptim - No optimization (currently the same as MemoryOptim).
    * QPixmap::MemoryOptim - Optimize for minimal memory use.
    * QPixmap::NormalOptim - Optimize for typical usage. Often uses more memory than MemoryOptim, and is often faster.
    * QPixmap::BestOptim - Optimize for pixmaps that are drawn very often and where performance is critical. Generally uses more memory than NormalOptim and may provide a little better speed. 

	 We recommend using DefaultOptim. 
	 */
	enum Optimization
	{
		DefaultOptim,
		NoOptim,
		MemoryOptim = NoOptim,
		NormalOptim,
		BestOptim
	};

	/*
	 Constructs a null pixmap.
	 See also isNull().
	 */ 
	QPixmap ();

	/*
	 Constructs a pixmap from the QImage image.
	 See also convertFromImage().
	 */ 
	QPixmap ( const QImage & image );

	/*
	 Constructs a pixmap with w width, h height and depth bits per pixel.
	 The pixmap is optimized in accordance with the optimization value.
	 The contents of the pixmap is uninitialized.
	 The depth can be either 1 (monochrome) or the depth of the current video mode.
	 If depth is negative, then the hardware depth of the current video mode will be used.
	 If either w or h is zero, a null pixmap is constructed.
	 See also isNull() and QPixmap::Optimization. 
	 */
	QPixmap ( int w, int h, int depth = -1, Optimization optimization = DefaultOptim );

	/*
	 This is an overloaded member function, provided for convenience.
	 It behaves essentially like the above function.
	 Constructs a pixmap of size size, depth bits per pixel, optimized in accordance with the optimization value. 
	 */
	QPixmap ( const QSize & size, int depth = -1, Optimization optimization = DefaultOptim );

	/*
	 Constructs a pixmap that is a copy of pixmap. 
	 */
	QPixmap ( const QPixmap & pixmap );

	/* 未実装
	QPixmap ( const QString & fileName, const char * format = 0, ColorMode mode = Auto );
	QPixmap ( const QString & fileName, const char * format, int conversion_flags );
	QPixmap ( const char * xpm[] );
	*/

	/* QByteArray未実装
	QPixmap ( const QByteArray & img_data );
	*/


	/*
	 Destroys the pixmap. 
	 */ 
	virtual ~QPixmap ();


	/*
	 Assigns the pixmap pixmap to this pixmap and returns a reference to this pixmap.
	 */ 
	QPixmap & operator= ( const QPixmap & pixmap );

	/*
	 This is an overloaded member function, provided for convenience.
	 It behaves essentially like the above function.
	 Converts the image image to a pixmap that is assigned to this pixmap.
	 Returns a reference to the pixmap.
	 See also convertFromImage(). 
	 */ 
	QPixmap & operator= ( const QImage & image );


	/*
	 Returns TRUE if this is a null pixmap; otherwise returns FALSE.
	 A null pixmap has zero width, zero height and no contents.
	 You cannot draw in a null pixmap or bitBlt() anything to it.
	 Resizing an existing pixmap to (0, 0) makes a pixmap into a null pixmap.
	 See also resize(). 
	 */ 
	bool isNull () const;

	/*
	 Returns the width of the pixmap.
	 See also height(), size() and rect(). 
	 */ 
	int width () const;

	/*
	 Returns the height of the pixmap.
	 See also width(), size() and rect(). 
	 */ 
	int height () const;

	/*
	 Returns the size of the pixmap.
	 See also width(), height() and rect(). 
	 */ 
	QSize size () const;

	/*
	 Returns the enclosing rectangle (0,0,width(),height()) of the pixmap.
	 See also width(), height() and size(). 
	 */ 
	QRect rect () const;

	/*
	 Returns the depth of the image.
	 The pixmap depth is also called bits per pixel (bpp) or bit planes of a pixmap. A null pixmap has depth 0.
	 See also defaultDepth(), isNull() and QImage::convertDepth(). 
	 */ 
	int depth () const;

	/*
	 Fills the pixmap with the color fillColor.
	 */ 
	virtual void fill ( const QColor & fillColor = Qt::white );

	/* QWidget未実装
	void fill ( const QWidget * widget, int xofs, int yofs );
	void fill ( const QWidget * widget, const QPoint & ofs );
	*/


	/*
	 Resizes the pixmap to w width and h height.
	 If either w or h is 0, the pixmap becomes a null pixmap.
	 If both w and h are greater than 0, a valid pixmap is created.
	 New pixels will be uninitialized (random) if the pixmap is expanded. 
	 */ 
	void resize ( int w, int h );

	/*
	 This is an overloaded member function, provided for convenience.
	 It behaves essentially like the above function.
	 Resizes the pixmap to size size. 
	 */ 
	void resize ( const QSize & size );

	/* QBitmapは継承クラス
	const QBitmap * mask () const;
	void setMask ( const QBitmap & newmask );
	bool selfMask () const;
	QBitmap createHeuristicMask ( bool clipTight = TRUE ) const;
	*/

	/* QWMatrix未実装
	QPixmap xForm ( const QWMatrix & matrix ) const;
	*/
	
	/*
	 */
	QImage convertToImage () const;

	/* 未実装
	bool convertFromImage ( const QImage & image, ColorMode mode = Auto );
	bool convertFromImage ( const QImage & img, int conversion_flags );
	bool load ( const QString & fileName, const char * format = 0, ColorMode mode = Auto );
	bool load ( const QString & fileName, const char * format, int conversion_flags );
	bool loadFromData ( const unsigned char * buf, unsigned int len, const char * format = 0, ColorMode mode = Auto );
	bool loadFromData ( const unsigned char * buf, unsigned int len, const char * format, int conversion_flags );
	/*

	/* QByteArray未実装
	bool loadFromData ( const QByteArray & buf, const char * format = 0, int conversion_flags = 0 );
	*/

	/* 未実装
	bool save ( const QString & fileName, const char * format, int quality = -1 ) const;
	int serialNumber () const;
	*/

	/*
	 Returns the optimization setting for this pixmap.
	 The default optimization setting is QPixmap::NormalOptim.
	 You may change this settings in two ways:

    * Call setDefaultOptimization() to set the default optimization for all new pixmaps.
    * Call setOptimization() to set a the optimization for individual pixmaps. 

	 See also setOptimization(), setDefaultOptimization() and defaultOptimization(). 
	 */
	Optimization optimization () const;

	/*
	 Sets pixmap drawing optimization for this pixmap.
	 The optimization setting affects pixmap operations, in particular drawing of transparent pixmaps (bitBlt() a pixmap with a mask set) and pixmap transformations (the xForm() function).
	 Pixmap optimization involves keeping intermediate results in a cache buffer and use the data in the cache to speed up bitBlt() and xForm().
	 The cost is more memory consumption, up to twice as much as an unoptimized pixmap.
	 Use the setDefaultOptimization() to change the default optimization for all new pixmaps.
	 See also optimization(), setDefaultOptimization() and defaultOptimization().
 	 */
	void setOptimization ( Optimization optimization );

	/*
	void detach ();
	*/

	/*
	 Returns TRUE if this is a QBitmap; otherwise returns FALSE. 
	 */
	virtual bool isQBitmap () const;

	//
	// 以下はbeat用に拡張
	//

	// ビットマップバッファの先頭アドレス
	unsigned char * bits () const;
	
	// バッファサイズ(バイト)を返す
	int numBytes () const;
	
	// 1ラインあたりのバイト数を返す
	int bytesPerLine () const;
	
	// 指定したサイズの四角形を描画する
	void drawRect ( QRect & rect, bool fill = false );

public:	

	/* Static関数未実装
	static int defaultDepth ();
	static QPixmap grabWindow ( WId window, int x = 0, int y = 0, int w = -1, int h = -1 );
	static QPixmap grabWidget ( QWidget * widget, int x = 0, int y = 0, int w = -1, int h = -1 );
	static QWMatrix trueMatrix ( const QWMatrix & matrix, int w, int h );
	static const char * imageFormat ( const QString & fileName );
	static Optimization defaultOptimization ();
	static void setDefaultOptimization ( Optimization optimization );
	*/

protected:

	/*
	 */
	QPixmap ( int w, int h, const unsigned char * bits, bool isXbitmap );

	/*
	 */
	virtual int metric ( int m ) const;
};

#endif /*QPIXMAP_H_*/
