// $Archive: /DocuWorks/60/Source/include/cstocp.h $
//
// Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:29 $
// $Revision: 1.4 $

#ifndef _CSTOCP_H
#define _CSTOCP_H

// 説明		キャラクタセットからコードページに変換する
// 引数		charSet キャラクタセット
// 戻り値	コードページ
// 備考		VLTなどで複数includeされてもリンクエラーとならないように
//			inlineとする

inline unsigned int DWCharSetToCodePage(unsigned int charSet)
{
	unsigned int codePage = CP_ACP;

	switch (charSet)
	{
	case SHIFTJIS_CHARSET:
		codePage = 932;
		break;
	case GB2312_CHARSET:
		codePage = 936;
		break;
	case HANGEUL_CHARSET:
		codePage = 949;
		break;
	case CHINESEBIG5_CHARSET:
		codePage = 950;
		break;
	case ANSI_CHARSET:
		codePage = 1252;
		break;
	case EASTEUROPE_CHARSET:
		codePage = 1250;
		break;
	case RUSSIAN_CHARSET:
		codePage = 1251;
		break;
	case GREEK_CHARSET:
		codePage = 1253;
		break;
	case TURKISH_CHARSET:
		codePage = 1254;
		break;
	case HEBREW_CHARSET:
		codePage = 1255;
		break;
	case ARABIC_CHARSET:
		codePage = 1256;
		break;
	case BALTIC_CHARSET:
		codePage = 1257;
		break;
	case VIETNAMESE_CHARSET:
		codePage = 1258;
		break;
	case THAI_CHARSET:
		codePage = 874;
		break;
	case SYMBOL_CHARSET:
		codePage = CP_SYMBOL;
		break;
	}

	return codePage;
}

#endif

// $History: cstocp.h $
// 
// *****************  Version 1  *****************
// User: Komoda       Date: 04/03/29   Time: 16:30
// Created in $/DocuWorks/60/Source/include
// V6.0新規作成
