#ifndef _ANNOTATION_PARAMETER_H
#define _ANNOTATION_PARAMETER_H

#include <signal.h>
#include "w2mpf_def.h"
#include "win2mpf.h"

template <typename T> class MyArray
{
public:
	MyArray() : m_array(0), m_size(0) {}
	~MyArray() { delete[] m_array; }
	MyArray(const MyArray<T>& right) : m_array(0), m_size(0) {
		set(right.m_array, right.m_size);
	}
	bool allocate(size_t n) {
		delete[] m_array;
		m_size = n;
		m_array = new T[n];
		return true;
	}
	bool set(const T src[], size_t num) {
		delete[] m_array;
		m_size = num;
		m_array = new T[num];
		for (size_t i = 0; i < num; ++i) {
			m_array[i] = src[i];
		}
		return true;
	}
	T& operator[](int index) const {
		return m_array[index];
	}
	size_t size() const { return m_size; }
	T* data() const { return m_array; }
private:
	T* m_array;
	size_t m_size;
};

class UTF16Text
{
public:
	UTF16Text() : m_text(0), m_length(0) {}
	~UTF16Text() { delete[] m_text; }
	UTF16Text(const wchar_t* text) : m_text(0) { copy(text); }
	UTF16Text(const unsigned short* text) : m_text(0) { copy(text); }
	UTF16Text(const UTF16Text& utf16t) : m_text(0) { copy((const unsigned short*)utf16t); }
	UTF16Text& operator =(const UTF16Text& text) { copy(text); return *this; }
	void operator =(const wchar_t* text) { copy(text); }
//	void operator =(const unsigned short* text) { copy(text); }
	operator const unsigned short*() const { return m_text; }
	void* data() const { return m_text; }
	int GetLength() const { return m_length; }
private:
	void copy(const unsigned short* t) {
		delete[] m_text;
		int l = 0;
		while (t[l] != 0) { ++l; }
		m_length = l;
		m_text = new unsigned short[l + 1];
		while (l >= 0) { m_text[l] = t[l]; --l; }
	}
	void copy(const wchar_t* t) {
		delete[] m_text;
		int l = 0;
		while (t[l] != 0) { ++l; }
		m_length = l;
		m_text = new unsigned short[l + 1];
		while (l >= 0) { m_text[l] = t[l]; --l; }
	}
	unsigned short* m_text;
	int m_length;
};

/////////////////////////////////////////////////////////////////////

struct AnnotationParameter
{
	int tag;

	enum {
		TAG_UNKNOWN,
		TAG_TEXT,
		TAG_FREEHAND,
		TAG_NOTEPAD,
		TAG_LINE,
		TAG_RECTANGLE,
		TAG_ELLIPSE,
		TAG_POLYGON,
	};

	enum {
		LINE_BORDER_SOLID = 0,
		LINE_BORDER_DOT = 1,
		LINE_BORDER_DASH = 2,
		LINE_BORDER_DASHDOT = 3,
		LINE_BORDER_DOUBLE = 4,
	};
	enum {
		LINE_ARROW_NONE = 0,
		LINE_ARROW_START = 1,
		LINE_ARROW_END = 2,
		LINE_ARROW_BOTH = 3,
	};
	enum {
		LINE_ARROW_STYLE_OPEN = 0,
		LINE_ARROW_STYLE_OPEN2 = 1,
		LINE_ARROW_STYLE_CLOSED = 2,
	};

	enum {
		TEXT_WRAP_STYLE_NOWRAP = 0,
		TEXT_WRAP_STYLE_WRAP = 1,
		TEXT_WRAP_STYLE_WRAP_RESIZE = 2,
	};
	enum {
		TEXT_FONT_PITCH_DEFAULT = 0,
		TEXT_FONT_PITCH_FIXED = 0x40,
		TEXT_FONT_PITCH_VARIABLE = 0x80,
	};
	enum {
		TEXT_FONT_FAMILY_DONTCARE = 0,
		TEXT_FONT_FAMILY_ROMAN = 1,
		TEXT_FONT_FAMILY_SWISS = 2,
		TEXT_FONT_FAMILY_MODERN = 3,
		TEXT_FONT_FAMILY_SCRIPT = 4,
		TEXT_FONT_FAMILY_DECORATIVE = 5,
	};
	enum {
		TEXT_FONT_SYTLE_NORMAL = 0,
		TEXT_FONT_STYLE_ITALIC = 0x01,
		TEXT_FONT_STYLE_BOLD = 0x02,
		TEXT_FONT_STYLE_UNDERLINE = 0x04,
		TEXT_FONT_STYLE_STRIKEOUT = 0x08,
	};
	enum {
		TEXT_FONT_CHARSET_ANSI = 0,
		TEXT_FONT_CHARSET_SHIFTJIS = 128,
		TEXT_FONT_CHARSET_HANGUL = 129,
		TEXT_FONT_CHARSET_GB2312 = 134,
		TEXT_FONT_CHARSET_BIG5 = 136,
		TEXT_FONT_CHARSET_THAI = 222,
	};
};

struct TextAnnotationParameter : public AnnotationParameter
{
	POINT position;
	int width;
	int height;

	struct Font {
		UTF16Text name;
		int pitchAndFamily;
		int charSet;
		int style;
		float size;
		float angle;
		COLORREF color;
		bool vertical;
	} font;

	struct Fill {
		bool has;
		COLORREF color;
	} fill;

	struct Spacing {
		float line;
		float character;
	} spacing;

	struct Margin {
		float left;
		float top;
		float right;
		float bottom;
	} margin;

	RECT textbox;

	int wrapStyle;
	UTF16Text text;
};

struct FreehandAnnotationParameter : public AnnotationParameter
{
	POINT position;
	int width;
	int height;

	struct Border {
		int width;
		COLORREF color;
		bool transparent;
	} border;

	MyArray<POINT> points;
};

struct NotepadAnnotationParameter : public AnnotationParameter
{
	POINT position;
	int width;
	int height;
	
	RECT rect;

	COLORREF color;
	bool autoResize;
};

struct LineAnnotationParameter : public AnnotationParameter
{
	POINT position;
	int width;
	int height;

	struct Border {
		int style;
		int width;
		COLORREF color;
		bool transparent;
	} border;

	struct Arrow {
		int type;
		int style;
	} arrow;

	POINT startPoint;
	POINT endPoint;
};

struct RectangleAnnotationParameter : public AnnotationParameter
{
	POINT position;
	int width;
	int height;

	RECT rect;

	struct Border {
		bool has;
		int width;
		COLORREF color;
	} border;

	struct Fill {
		bool has;
		COLORREF color;
		bool transparent;
	} fill;
};

struct EllipseAnnotationParameter : public AnnotationParameter
{
	POINT position;
	int width;
	int height;
	
	RECT rect;

	struct Border {
		bool has;
		int width;
		COLORREF color;
	} border;

	struct Fill {
		bool has;
		COLORREF color;
		bool transparent;
	} fill;
};

struct PolygonAnnotationParameter : public AnnotationParameter
{
	POINT position;
	int width;
	int height;

	struct Border {
		bool has;
		int width;
		COLORREF color;
	} border;

	struct Fill {
		bool has;
		COLORREF color;
		bool transparent;
	} fill;

	MyArray<POINT> points;
};

struct TextNotepadAnnotationParameter : public AnnotationParameter
{
	NotepadAnnotationParameter notepadparam;
	TextAnnotationParameter textparam;

	enum { TAG_TEXTNOTEPAD = TAG_POLYGON + 1 };
};

#endif
