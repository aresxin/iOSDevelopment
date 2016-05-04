#ifndef QFONT_H_
#define QFONT_H_

#include "qstring.h"
#include "qnamespace.h"

class QFont
{
public:

	enum StyleHint
	{
		Helvetica,
		SansSerif	= Helvetica,
		Times,
		Serif		= Times,
		Courier,
		TypeWriter	= Courier,
		OldEnglish,
		Decorative	= OldEnglish,
		System,
		AnyStyle
	};
	
	enum StyleStrategy
	{
		PreferDefault	= 0x0001,
		PreferBitmap	= 0x0002,
		PreferDevice	= 0x0004,
		PreferOutline	= 0x0008,
		ForceOutline	= 0x0010,
		PreferMatch		= 0x0020,
		PreferQuality	= 0x0040,
		PreferAntialias	= 0x0080,
		NoAntialias		= 0x0100
	};
	
	enum Weight
	{
		Light	= 25,
		Normal	= 50,
		DemiBold= 63,
		Bold	= 75,
		Black	= 87
	};

	enum Script
	{
		Latin,
		Greek,
		Cyrillic,
		Armenian,
		Georgian,
		Runic,
		Ogham,
		SpacingModifiers,
		CombiningMarks,
		Hebrew,
		Arabic,
		Syriac,
		Thaana,
		Devanagari,
		Bengali,
		Gurmukhi,
		Gujarati,
		Oriya,
		Tamil,
		Telugu,
		Kannada,
		Malayalam,
		Sinhala,
		Thai,
		Lao,
		Tibetan,
		Myanmar,
		Khmer,
		Han,
		Hiragana,
		Katakana,
		Hangul,
		Bopomofo,
		Yi,
		Ethiopic,
		Cherokee,
		CanadianAboriginal,
		Mongolian,
		CurrencySymbols,
		LetterlikeSymbols,
		NumberForms,
		MathematicalOperators,
		TechnicalSymbols,
		GeometricSymbols,
		MiscellaneousSymbols,
		EnclosedAndSquare,
		Braille,
		Unicode,
		NScripts,
		UnknownScript = NScripts,
		NoScript,
		HanX11,
		LatinBasic = Latin,
		LatinExtendedA_2 = HanX11 + 1,
		LatinExtendedA_3,
		LatinExtendedA_4,
		LatinExtendedA_14,
		LatinExtendedA_15,
		LastPrivateScript
	};

private:

	QString	m_family;
	QString	m_rawName;

	bool	m_isFixedPitch;
	bool	m_isUnderLine;
	bool	m_isItalic;
	bool	m_isBold;
	bool	m_isStrikeOut;
	bool	m_isRawMode;
	int		m_weight;
	int		m_pixelSize;
	int		m_pointSize;
	
	StyleHint		m_hint;
	StyleStrategy	m_strategy;
	
public:
	
	QFont ()
	{
		m_family	= "default";
		m_rawName	= "default";
		
		m_isFixedPitch	= true;
		m_isUnderLine	= false;
		m_isItalic		= false;
		m_isBold		= false;
		m_isStrikeOut	= false;
		m_weight		= Normal;
		m_pixelSize		= 0;
		m_pointSize		= 12;
		
		m_hint		= System;
		m_strategy	= PreferDefault;
		
		return;
	};
	
	QFont ( const QString & family, int pointSize = 12, int weight = Normal, bool italic = false )
	{
		m_family	= family;
		m_rawName	= family;
		
		m_isFixedPitch	= true;
		m_isUnderLine	= false;
		m_isItalic		= italic;
		m_isBold		= false;
		m_isStrikeOut	= false;
		m_weight		= weight;
		m_pixelSize		= 0;
		m_pointSize		= pointSize;
		
		m_hint		= System;
		m_strategy	= PreferDefault;
		
		return;
	};
	
	QFont ( const QFont & font )
	{
		*this = font;

		return;
	};
	
	virtual ~QFont ()
	{
		return;
	};
	
	QString family () const
	{
		return m_family;
	};

	void setFamily ( const QString & family )
	{
		m_family = family;
		
		return;
	};
	
	int pointSize () const
	{
		return m_pointSize;
	};
	
	float pointSizeFloat () const
	{
		return (float)m_pointSize;
	};
	
	void setPointSize ( int pointSize )
	{
		m_pointSize = pointSize;
		
		return;
	};
	
	void setPointSizeFloat ( float pointSize )
	{
		m_pointSize = (int)pointSize;
		
		return;
	};
	
	int pixelSize () const
	{
		return m_pixelSize;
	};
	
	void setPixelSize ( int pixelSize )
	{
		m_pixelSize = pixelSize;
		
		return;
	};
	
	void setPixelSizeFloat ( float pixelSize ) // (obsolete)
	{
		m_pixelSize = (int)pixelSize;
		
		return;
	};
	
	int weight () const
	{
		return m_weight;
	};
	
	void setWeight ( int weight )
	{
		m_weight = weight;
		
		return;
	};
	
	bool bold () const
	{
		return m_isBold;
	};
	
	void setBold ( bool enable )
	{
		m_isBold = enable;
		
		return;
	};
	
	bool italic () const
	{
		return m_isItalic;
	};
	
	void setItalic ( bool enable )
	{
		m_isItalic = enable;
		
		return;
	};
	
	bool underline () const
	{
		return m_isUnderLine;
	};
	
	void setUnderline ( bool enable )
	{
		m_isUnderLine = enable;
		
		return;
	};
	
	bool strikeOut () const
	{
		return m_isStrikeOut;
	};
	
	void setStrikeOut ( bool enable )
	{
		m_isStrikeOut = enable;
		
		return;
	};
	
	bool fixedPitch () const
	{
		return m_isFixedPitch;
	};
	
	void setFixedPitch ( bool enable )
	{
		m_isFixedPitch = enable;
		
		return;
	};
	
	StyleHint styleHint () const
	{
		return m_hint;
	};
	
	StyleStrategy styleStrategy () const
	{
		return m_strategy;
	};
	
	void setStyleHint ( StyleHint hint, StyleStrategy strategy = PreferDefault )
	{
		m_hint		= hint;
		m_strategy	= strategy;
		
		return;
	};
	
	void setStyleStrategy ( StyleStrategy s )
	{
		m_strategy	= s;
		
		return;
	};
	
	bool rawMode () const
	{
		return m_isRawMode;
	};
	
	void setRawMode ( bool enable )
	{
		m_isRawMode = enable;
		
		return;
	};
	
	bool exactMatch () const
	{
		return false;
	};
	
	QFont & operator= ( const QFont & font )
	{
		m_family	= font.family();
		m_rawName	= font.rawName();

		m_isFixedPitch	= font.fixedPitch();
		m_isUnderLine	= font.underline();
		m_isItalic		= font.italic();
		m_isBold		= font.bold();
		m_isStrikeOut	= font.strikeOut();
		m_isRawMode		= font.rawMode();
		m_weight		= font.weight();
		m_pixelSize		= font.pixelSize();
		m_pointSize		= font.pointSize();
	
		m_hint		= font.styleHint();
		m_strategy	= font.styleStrategy();
		
		return *this;
	};
	
	/*
	bool operator== ( const QFont & f ) const
	{
		return false;
	};
	
	bool operator!= ( const QFont & f ) const
	{
		return false;
	};
	
	bool isCopyOf ( const QFont & f ) const
	{
		return false;
	};
	*/
	
	/*
	HFONT handle () const
	{
	};
	*/
	
	void setRawName ( const QString & name )
	{
		m_rawName = name;

		return;
	};
	
	QString rawName () const
	{
		return m_rawName;
	};
	/*
	QString key () const
	{
		QString str;

		return str;
	};
	
	QString toString () const
	{
		QString str;

		return str;
	};
	
	bool fromString ( const QString & descrip )
	{
		return false;
	};
	
	void qwsRenderToDisk ( bool all = true )
	{
		return;
	};
	
	QString defaultFamily () const
	{
		QString str;

		return str;
	};
	
	QString lastResortFamily () const
	{
		QString str;

		return str;
	};
	
	QString lastResortFont () const
	{
		QString str;

		return str;
	};

	QString substitute ( const QString & familyName )
	{
		QString str;

		return str;
	};
	*/
	/*
	QStringList substitutes ( const QString & familyName )
	{
		QString str;

		return str;
	};
	
	QStringList substitutions ()
	{
		QString str;

		return str;
	};
	*/

	/*
	void insertSubstitution ( const QString & familyName, const QString & substituteName )
	{
		return;
	};

	void insertSubstitutions ( const QString & familyName, const QStringList & substituteNames )
	{
		return;
	};

	void removeSubstitution ( const QString & familyName )
	{
		return;
	};
	*/
	
	/*
	QFont defaultFont () // (obsolete)
	{
		return *this;
	};
	
	void setDefaultFont ( const QFont & f ) // (obsolete)
	{
		return;
	};
	*/
};

#endif /*QFONT_H_*/
