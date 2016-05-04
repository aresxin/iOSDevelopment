/**
 * @file    converter.h
 * @brief   Converterクラスの宣言
 * @author  Tomoki Kitahashi (STDG-SWPD-5G)
 * @date    2006-08-28
 *
 * $Id: converter.h,v 1.4 2009/12/22 08:11:31 chikyu Exp $
 *
 * Copyright (C) 2006 Fuji Xerox Co., Ltd.
 */
#ifndef _CONVERTER_H
#define _CONVERTER_H

/**
 * Unicode <-> MultiByte 変換クラス.
 */
class Converter
{
public:
	static int MultiByteToUTF16(int codepage, const char* iStr, int iLength,
			unsigned short* oStr, int oLength);
	static int UTF16ToMultiByte(int codepage, const unsigned short* iStr, int iLength,
			char* oStr, int oLength);
	static int UTF8ToUTF16(const char* iStr, int iLength,
						   unsigned short* oStr, int oLength);
	static int UTF16ToUTF8(const unsigned short* iStr, int iLength,
						   char* oStr, int oLength);

	// EUC対応(09/03/12) M.Chikyu
	// UTF-8から指定のエンコードに変換
	static int UTF8ToMultiByte(int codepage,
							    const char* iStr,
							    int iLength,
							    char* oStr,
							    int oLength);
	// EUC対応(09/03/12) M.Chikyu
	// UTF-8からOSネイティブのエンコードに変換
	static int UTF8ToNativeCode(const char* iStr,
								 int iLength,
								 char *oStr,
								 int oLength);
	
private:
	Converter();
	~Converter();

	// EUC対応(09/03/12) M.Chikyu
	// コードページ格納変数
	static int m_nativeCodepage;

public:	
	enum CODEPAGE_ENUM {
		CONV_CP932_JAPANESE = 932,
		CONV_CP936_CHINESE_SIMPLIF = 936,
		CONV_CP949_KOREAN = 949,
		CONV_CP950_CHINESE_TRAD = 950,
		CONV_CP1252_ANSI = 1252,
		CONV_CP1250_EASTEUROPE = 1250,
		CONV_CP1251_RUSSIAN =  1251,
		CONV_CP1253_GREEK = 1253,
		CONV_CP1254_TURKISH = 1254,
		CONV_CP1255_HEBREW = 1255,
		CONV_CP1256_ARABIC = 1256,
		CONV_CP1257_BALTIC = 1257,
		CONV_CP1258_VIETNAMESE = 1258,
		CONV_CP874_THAI = 874,
		CONV_CP42_SYMBOL = 42,
		CONV_UTF8 = 65001,
		// EUC対応(09/03/12)
		// M.Chikyu
		CONV_EUCJP = 20932,
		CONV_DEFAULT_CODEPAGE = 0
	};
};

// Linux対応　(09/03/12) M.Chikyu
// コードページを判定できない場合のデフォルトコードページ
#define _UNKNOWNCODEPAGE_ Converter::CONV_UTF8

#endif 
