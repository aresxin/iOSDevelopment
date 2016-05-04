#ifndef QCOLOR_H_
#define QCOLOR_H_

typedef unsigned int QRgb;

class QColor
{
private:

	Qt::GlobalColor m_globalColor;
	
public:

	enum Spec
	{
		Rgb,
		Hsv
	};

	QColor ()
	{
		m_globalColor = Qt::color0;
		
		return;
	};

	/*
	QColor ( int r, int g, int b )
	{
		return;
	};

	QColor ( int x, int y, int z, Spec colorSpec )
	{
		return;
	};

	QColor ( QRgb rgb, unsigned int pixel = 0xffffffff )
	{
		return;
	};

	QColor ( const QString & name )
	{
		return;
	};

	QColor ( const char * name )
	{
		return;
	};
	*/

	QColor ( const QColor & c )
	{
		*this = c;

		return;
	};
	
	QColor ( Qt::GlobalColor color )
	{
		m_globalColor = color;
		
		return;
	};
	
	QColor & operator= ( Qt::GlobalColor color )
	{
		m_globalColor = color;
		
		return *this;
	};
	
	QColor & operator= ( const QColor & color )
	{
		m_globalColor = color.globalColor();
		
		return *this;
	};

	bool isValid () const
	{
		return true;
	};
	
	/*
	QString name () const
	{
		QString result;
		
		return result;
	};

	void setNamedColor ( const QString & name )
	{
		return;
	};

	void rgb ( int * r, int * g, int * b ) const
	{
		return;
	};

	QRgb rgb () const
	{
		return 0;
	};

	void setRgb ( int r, int g, int b )
	{
		return;
	};

	void setRgb ( QRgb rgb )
	{
		return;
	};

	int red () const
	{
		return 0;
	};

	int green () const
	{
		return 0;
	};

	int blue () const
	{
		return 0;
	};

	void hsv ( int * h, int * s, int * v ) const
	{
		return;
	};

	void getHsv ( int & h, int & s, int & v ) const // (obsolete)
	{
		return;
	};

	void setHsv ( int h, int s, int v )
	{
		return;
	};

	QColor light ( int factor = 150 ) const
	{
		return *this;
	};

	QColor dark ( int factor = 200 ) const
	{
		return *this;
	};
	*/
	
	Qt::GlobalColor globalColor() const
	{
		return m_globalColor;
	};
	
	bool operator== ( const QColor & c ) const
	{
		if (m_globalColor == c.globalColor())
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	/*
	bool operator!= ( const QColor & c ) const
	{
		return false;
	};

	unsigned int alloc ()
	{
		return 0;
	};

	unsigned int pixel () const
	{
		return 0;
	};
	*/
	
	/*
public:
	static int maxColors ()
	{
		return 0;
	};

	static int numBitPlanes ()
	{
		return 0;
	};

	static int enterAllocContext ()
	{
		return 0;
	};

	static void leaveAllocContext ()
	{
		return;
	};

	static int currentAllocContext ()
	{
		return 0;
	};

	static void destroyAllocContext ( int context )
	{
		return;
	};

	static void initialize ()
	{
		return;
	};

	static void cleanup ()
	{
		return;
	};
	*/
};

#endif /*QCOLOR_H_*/
