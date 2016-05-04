#ifndef QPOINT_H_
#define QPOINT_H_

#include <cmath>
#include "qnamespace.h"

class QPoint
{
private:
	int m_x, m_y;

public:
	QPoint ()
	{
		m_x = m_y = 0;
		
		return;
	};

	QPoint ( int xpos, int ypos )
	{
		m_x = xpos;
		m_y = ypos;

		return;
	};

	bool isNull () const
	{
		if ((m_x == 0) && (m_y == 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	int x () const
	{
		return m_x;
	};

	int y () const
	{
		return m_y;
	};

	void setX ( int x )
	{
		m_x = x;
		return;
	};

	void setY ( int y )
	{
		m_y = y;
		return;
	};

	int manhattanLength () const
	{
		return (int)( std::sqrt( (double)(m_x*m_x + m_y*m_y) ));
	};

	/*
	QCOORD & rx ()
	{
	};

	QCOORD & ry ()
	{
	};
	*/

	QPoint & operator+= ( const QPoint & p )
	{
		m_x += p.x();
		m_y += p.y();
		
		return *this;
	};

	QPoint & operator-= ( const QPoint & p )
	{
		m_x -= p.x();
		m_y -= p.y();
		
		return *this;
	};

	QPoint & operator*= ( int c )
	{
		m_x *= c;
		m_y *= c;
		
		return *this;
	};

	QPoint & operator*= ( double c )
	{
		m_x = (int)(m_x * c);
		m_y = (int)(m_y * c);
		
		return *this;
	};

	QPoint & operator/= ( int c )
	{
		if (c != 0)
		{
			m_x /= c;
			m_y /= c;
		}
		
		return *this;
	};

	QPoint & operator/= ( double c )
	{
		if (c != 0.0)
		{
			m_x /= (int)(m_x / c);
			m_y /= (int)(m_y / c);
		}

		return *this;
	};

	bool operator== ( const QPoint & p)
	{
		if ((m_x == p.x()) && (m_y == p.y()))
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool operator!= ( const QPoint & p)
	{
		return !(*this == p);
	};

	const QPoint operator+ ( const QPoint & p )
	{
		return QPoint(m_x + p.x(), m_y + p.y());
	};

	const QPoint operator- ( const QPoint & p )
	{
		return QPoint(m_x - p.x(), m_y - p.y());
	};

	const QPoint operator* ( int c )
	{
		return QPoint(m_x * c, m_y * c);
	};

	const QPoint operator* ( double c )
	{
		return QPoint((int)(m_x * c), (int)(m_y * c));
	};

	const QPoint operator/ ( int c )
	{
		QPoint ret = *this;
		
		if (c != 0)
		{
			ret /= c;
		}
		
		return ret;
	};

	const QPoint operator/ ( double c )
	{
		QPoint ret = *this;
		
		if (c != 0.0)
		{
			ret /= c;
		}
		
		return ret;
	};

	/*
	QDataStream & operator<< ( QDataStream & s, const QPoint & p )
	{
	};

	QDataStream & operator>> ( QDataStream & s, QPoint & p )
	{
	};
	*/
};

#endif /*QPOINT_H_*/
