#ifndef QSIZE_H_
#define QSIZE_H_

#include "qnamespace.h"

class QSize
{
private:
	int m_width, m_height;
	
public:
	QSize ()
	{
		m_width = m_height = 0;
		
		return;
	};
	
	QSize ( int w, int h )
	{
		m_width	= w;
		m_height= h;
		
		return;
	};
	
	bool isNull () const
	{
		if ((m_width == 0) && (m_height == 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	
	bool isEmpty () const
	{
		if ((m_width <= 0) && (m_height <= 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	
	bool isValid () const
	{
		if ((m_width >= 0) && (m_height >= 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	int width () const
	{
		return m_width;
	};
	
	int height () const
	{
		return m_height;
	};
	
	void setWidth ( int w )
	{
		m_width = w;

		return;
	};
	
	void setHeight ( int h )
	{
		m_height = h;

		return;
	};

	/*	
	void transpose ()
	QSize expandedTo ( const QSize & otherSize ) const
	QSize boundedTo ( const QSize & otherSize ) const
	QCOORD & rwidth ()
	QCOORD & rheight ()
	QSize & operator+= ( const QSize & s )
	QSize & operator-= ( const QSize & s )
	QSize & operator*= ( int c )
	QSize & operator*= ( double c )
	QSize & operator/= ( int c )
	QSize & operator/= ( double c )
	*/
	
	bool operator== (const QSize & s )
	{
		if ((m_width == s.width()) && (m_height == s.height()))
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	
	bool operator!= ( const QSize & s )
	{
		return !(*this == s);
	};
	
	/*
	const QSize operator+ ( const QSize & s1, const QSize & s2 )
	const QSize operator- ( const QSize & s1, const QSize & s2 )
	const QSize operator* ( const QSize & s, int c )
	const QSize operator* ( int c, const QSize & s )
	const QSize operator* ( const QSize & s, double c )
	const QSize operator* ( double c, const QSize & s )
	const QSize operator/ ( const QSize & s, int c )
	const QSize operator/ ( const QSize & s, double c )
	*/

	/*
	QDataStream & operator<< ( QDataStream & s, const QSize & sz )
	QDataStream & operator>> ( QDataStream & s, QSize & sz )
	*/
};

#endif /*QSIZE_H_*/
