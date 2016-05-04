#ifndef QIMAGE_H_
#define QIMAGE_H_

#include "qrect.h"
#include "qsize.h"
#include "qstring.h"
#include "qpaintdevice.h"
#include "qnamespace.h"
#include "qcolor.h"
#include "qpoint.h"

#ifndef QPIXMAP_H_
class QPixmap;
#endif

class QImage
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

	enum Endian
	{
		IgnoreEndian,
		BigEndian,
		LittleEndian
	};

	enum ScaleMode
	{
		ScaleFree,
		ScaleMin,
		ScaleMax
	};


	QImage ();
	QImage ( int w, int h, int depth, int numColors = 0, Endian bitOrder = IgnoreEndian );
	QImage ( const QSize & size, int depth, int numColors = 0, Endian bitOrder = IgnoreEndian );
	QImage ( const QImage & image );
	
	/*
	QImage ( const QString & fileName, const char * format = 0 );
	QImage ( const char * const xpm[] );
	*/

	/* QByteArray未実装
	QImage ( const QByteArray & array )
	{
		return;
	};
	*/

	/*
	QImage ( unsigned char * yourdata, int w, int h, int depth, QRgb * colortable, int numColors, Endian bitOrder )
	{
		return;
	};

	QImage ( unsigned char * yourdata, int w, int h, int depth, int bpl, QRgb * colortable, int numColors, Endian bitOrder )
	{
		return;
	};
	*/

	virtual ~QImage ();

	QImage & operator= ( const QImage & image );
	QImage & operator= ( const QPixmap & pixmap );

	/*
	bool operator== ( const QImage & i ) const;
	bool operator!= ( const QImage & i ) const;
	void detach ();
	QImage copy () const;
	QImage copy ( int x, int y, int w, int h, int conversion_flags = 0 ) const;
	QImage copy ( const QRect & r ) const;
	*/

	bool isNull () const;
	int width () const;
	int height () const;
	QSize size () const;
	QRect rect () const;
	int depth () const;
	
	/*
	int numColors () const;
	void setNumColors ( int numColors );
	Endian bitOrder () const;
	QRgb color ( int i ) const;
	void setColor ( int i, QRgb c );
	bool hasAlphaBuffer () const;
	void setAlphaBuffer ( bool enable );
	bool allGray () const;
	bool isGrayscale () const;
	*/
	
	unsigned char * bits () const;
	unsigned char * scanLine ( int i ) const;

	/*
	unsigned char ** jumpTable () const;
	QRgb * colorTable () const;
	*/

	int numBytes () const;
	int bytesPerLine () const;

	/*
	bool create ( int width, int height, int depth, int numColors = 0, Endian bitOrder = IgnoreEndian );
	bool create ( const QSize &, int depth, int numColors = 0, Endian bitOrder = IgnoreEndian );
	void reset ();
	void fill ( unsigned int pixel );
	void invertPixels ( bool invertAlpha = true );
	QImage convertDepth ( int depth ) const;
	QImage convertDepthWithPalette ( int d, QRgb * palette, int palette_count, int conversion_flags = 0 ) const;
	QImage convertDepth ( int depth, int conversion_flags ) const;
	QImage convertBitOrder ( Endian bitOrder ) const;
	QImage smoothScale ( int w, int h, ScaleMode mode = ScaleFree ) const;
	QImage smoothScale ( const QSize & s, ScaleMode mode = ScaleFree ) const;
	QImage scale ( int w, int h, ScaleMode mode = ScaleFree ) const;
	QImage scale ( const QSize & s, ScaleMode mode = ScaleFree ) const;
	QImage scaleWidth ( int w ) const;
	QImage scaleHeight ( int h ) const;
	*/


	/* QWMatrix未実装
	QImage xForm ( const QWMatrix & matrix ) const;
	*/
	
	/*
	QImage createAlphaMask ( int conversion_flags = 0 ) const;
	QImage createHeuristicMask ( bool clipTight = true ) const;
	QImage mirror () const;
	QImage mirror ( bool horizontal, bool vertical ) const;
	QImage swapRGB () const;
	bool load ( const QString & fileName, const char * format = 0 );
	bool loadFromData ( const unsigned char * buf, unsigned int len, const char * format = 0 );
	*/

	/* QByteArray未実装
	bool loadFromData ( QByteArray buf, const char * format = 0 );
	*/

	/*
	bool save ( const QString & fileName, const char * format, int quality = -1 ) const
	bool valid ( int x, int y ) const
	int pixelIndex ( int x, int y ) const
	QRgb pixel ( int x, int y ) const
	void setPixel ( int x, int y, unsigned int index_or_rgb )
	int dotsPerMeterX () const
	int dotsPerMeterY () const
	void setDotsPerMeterX ( int x )
	void setDotsPerMeterY ( int y )
	QPoint offset () const
	void setOffset ( const QPoint & p )
	*/

	/* QImageTextKeyLang未実装
	QValueList<QImageTextKeyLang> textList () const;
	*/

	/* QStringList未実装
	QStringList textLanguages () const;
	QStringList textKeys () const;
	*/

	/*
	QString text ( const char * key, const char * lang = 0 ) const:
	QString text ( const QImageTextKeyLang & kl ) const:
	void setText ( const char * key, const char * lang, const QString & s ):
	*/

public:

	/* システム設定取得方法不明
	static Endian systemBitOrder ();
	static Endian systemByteOrder ();
	*/

	/*
	static const char * imageFormat ( const QString & fileName );
	*/

	/* ASCII文字列を使用
	static QStrList inputFormats ();
	static QStrList outputFormats ();
	*/

	/* UNICODE文字列を使用 
	static QStringList inputFormatList ();
	static QStringList outputFormatList ();
	*/
	
private:
	Endian m_bitOrder;

	/*
	static Endian m_systemBitOrder;
	static Endian m_systemByteOrder;
	*/
};

#endif /*QIMAGE_H_*/
