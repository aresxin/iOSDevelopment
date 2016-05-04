#ifndef MPCWCSTR_H
#define MPCWCSTR_H

#if defined _PF_WIN32_ || defined _PF_WINCE_

#include <string>
#include <sstream>

typedef std::basic_string<MP_Text> mpcwcstring;
typedef std::basic_stringstream<MP_Text> mpcwcstringstream;

#else

class mpcwcstring
{
public:
	mpcwcstring();
	~mpcwcstring();
	mpcwcstring(const MP_Text*);

	mpcwcstring& operator=(const mpcwcstring&);
	mpcwcstring& operator=(const MP_Text*);
	mpcwcstring& operator+=(const MP_Text*);
	operator const MP_Text*() const;
	bool operator==(const MP_Text*);

	void clear();
	const MP_Text* c_str() const;
	bool empty() const;
	size_t length() const;
	mpcwcstring& append(const MP_Text*);
	mpcwcstring& replace(size_t pos1, size_t n1, size_t n2, MP_Text c);

private:
	void set(const MP_Text*);
	void free();

	MP_Text* data_;
	size_t length_;
};

class mpcwcstringstream
{
public:
	mpcwcstringstream();
	~mpcwcstringstream();
};

#endif

#endif

