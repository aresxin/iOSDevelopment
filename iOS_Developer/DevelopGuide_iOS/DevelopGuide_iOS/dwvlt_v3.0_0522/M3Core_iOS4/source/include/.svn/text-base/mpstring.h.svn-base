// File: mpstring.h
// Auther: Toshiyuki Komoda
// Copyright (c) 2007 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Archive: /DocuWorks/70/Source/include/mpstring.h $ 
// $Date: 2009/12/22 08:11:29 $ 
// $Revision: 1.5 $ 

#ifndef _MP_STRING_
#define _MP_STRING_

#if defined _PF_WIN32_ || defined _PF_WINCE_

#if defined(MP_STRING_EXPORT_DECLARE)
#define MP_STRING_EXPORT _declspec(dllexport)
#else
#define MP_STRING_EXPORT _declspec(dllimport)
#endif

#else

#define MP_STRING_EXPORT

#endif


/*!
@brief WideChar文字列オブジェクト
*/
class MP_STRING_EXPORT MP_String
{
public:
	MP_String();
	~MP_String();
	operator const MP_Text*() const;
	HRESULT SetText(const MP_Text* text, MP_Integer length = -1);
	HRESULT Convert(int codepage, const char* mbtext, MP_Integer bytes = -1);
	MP_Integer GetLength() const;
	bool IsEmpty() const;
private:
	MP_String(const MP_String&);
	MP_String& operator=(const MP_String&);
	MP_Text operator[](int i) const;
private:
	MP_Text* m_data;
	MP_Integer m_length;
};


/*!
@brief MultiByte文字列オブジェクト
*/
class MP_STRING_EXPORT MP_MBString
{
public:
	MP_MBString();
	~MP_MBString();
	operator const char*() const;
	HRESULT SetText(const char* text, MP_Integer bytes = -1);
	HRESULT Convert(int codepage, const MP_Text* wctext, MP_Integer length = -1);
	MP_Integer GetLength() const;
	bool IsEmpty() const;
	bool IsValid() const;
private:
	MP_MBString(const MP_MBString&);
	MP_MBString& operator=(const MP_MBString&);
	char operator[](int i) const;
private:
	char* m_data;
	MP_Integer m_length;
};

/*!
@brief Unicode文字列がMultiByteに変換可能かどうか調べる
@param[in] codepage MultiByteコードのコードページ (CP_ACPなど)
@param[in] text ワイドキャラクタ文字列
@param[in] length 文字列の長さ(文字数) 省略時は-1
@retval true MultiByteに変換しても文字化けしない
@retval false MultiByteに変換すると文字化けが発生
@note lengthに負数を指定するとnull terminate文字列として扱う
*/
extern "C" MP_STRING_EXPORT
bool STDCALL MPCIsMBStringConvertable(int codepage, const MP_Text* wctext, MP_Integer length = -1);

#endif
