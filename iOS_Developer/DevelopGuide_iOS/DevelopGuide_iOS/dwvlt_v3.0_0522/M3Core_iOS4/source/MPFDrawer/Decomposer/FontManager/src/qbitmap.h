#ifndef QBITMAP_H_
#define QBITMAP_H_

#include "qpixmap.h"
#include "qimage.h"

class QBitmap : public QPixmap
{
public:

	QBitmap ()
	{
		initialize(0, 0, false, 1);

		return;
	};

	QBitmap ( int w, int h, bool clear = true, QPixmap::Optimization optimization = QPixmap::DefaultOptim )
	{
		initialize(w, h, clear, 1);
				
		return;
	};

	QBitmap ( const QSize & size, bool clear = true, QPixmap::Optimization optimization = QPixmap::DefaultOptim )
	{
		initialize(size.width(), size.height(), clear, 1);
				
		return;
	};

	QBitmap ( int w, int h, const unsigned char * bits, bool isXbitmap = false )
	{
		copy(w, h, bits, 1);
		
		return;
	};

	QBitmap ( const QSize & size, const unsigned char * bits, bool isXbitmap = false )
	{
		copy(size.width(), size.height(), bits, 1);
		
		return;
	};

	QBitmap ( const QBitmap & bitmap )
	{
		*this = bitmap;
		
		return;
	};

	/*
	QBitmap ( const QString & fileName, const char * format = 0 )
	{
		return;
	};
	*/

	QBitmap & operator= ( const QBitmap & bitmap )
	{
		copy(bitmap.width(), bitmap.height(), bitmap.bits(), 1);
			
		return *this;
	};

	QBitmap & operator= ( const QPixmap & pixmap )
	{
		return *this;
	};

	QBitmap & operator= ( const QImage & image )
	{
		if (image.depth() == 1)
		{
			copy(image.width(), image.height(), image.bits(), 1);
		}
			
		return *this;
	};
	
	virtual ~QBitmap ()
	{
		return;
	};

	/* QWMatrix未実装
	QBitmap xForm ( const QWMatrix & matrix ) const
	{
		return *this;
	};
	*/

	bool isQBitmap () const
	{
		return true;
	};
};

#endif /*QBITMAP_H_*/
