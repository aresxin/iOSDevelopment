/*
 * Copyright (C) 2003 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_DeviceColorSpace.h -- デバイス色空間の定義
 * (元RND_DeviceColorSpace.h)
 *
 * Created : 2003.07.16 Masao.Morita(DPSC SWD PFCoreG)
 *
 */

#if !defined(COM_DEVICECOLORSPACE_H_INCLUDED)
#define COM_DEVICECOLORSPACE_H_INCLUDED

/*----------------------------------*/
/*	基本色空間の定義				*/
/*----------------------------------*/
typedef enum COM_DCS_BaseTypeT
{
	COM_DCS_BASETYPE_GRAYW0	= 0,		/* 白が0で表現されるグレースケール	*/
	COM_DCS_BASETYPE_GRAYB0,			/* 黒が0で表現されるグレースケール	*/
	COM_DCS_BASETYPE_RGB,				/* 入力されたRGBをそのまま			*/
	COM_DCS_BASETYPE_sRGB,				/* RGB-RGB変換ありの色空間			*/
	COM_DCS_BASETYPE_CMYK,				/* CMYK色空間						*/
	COM_DCS_BASETYPE_CMY,				/* CMY色空間						*/
	COM_DCS_BASETYPE_RGBrevCMY			/* RGB補色のCMY色空間				*/
} COM_DCS_BaseType;

/*----------------------------------*/
/*	パディング形式の定義			*/
/*----------------------------------*/
typedef enum COM_DCS_OptionT
{
	COM_DCS_PADDING_NONE	= 0,		/* パディングなし					*/
	COM_DCS_PADDING_FIRST,				/* パディングはバイト列の先頭		*/
	COM_DCS_PADDING_LAST				/* パディングはバイト列の最後		*/
} COM_DCS_Option;

/*----------------------------------*/
/*	色の並びの定義					*/
/*----------------------------------*/
typedef enum COM_DCS_ComponentOrderT
{
	COM_DCS_ORDER_NONE	= 0,			/* 無指定(Gray時)					*/
	COM_DCS_ORDER_RGB	= 0,			/* RGBの順序						*/
	COM_DCS_ORDER_BGR,					/* BGRの順序(Windowsの形式)			*/
	COM_DCS_ORDER_CMYK	= 0,			/* CMYKの順序						*/
	COM_DCS_ORDER_YMCK,					/* YMCKの順序						*/
	COM_DCS_ORDER_KYMC,					/* KYMCの順序						*/
	COM_DCS_ORDER_CMY	= 0,			/* CMYの順序						*/
	COM_DCS_ORDER_YMC					/* YMCの順序						*/
} COM_DCS_ComponentOrder;

/*----------------------------------*/
/*	デバイス色空間の定義			*/
/*----------------------------------*/
typedef struct COM_DeviceColorSpaceT
{
	COM_DCS_BaseType		base;		/* 基本色空間名						*/
	int						bytes;		/* 一画素分のバイト数				*/
	COM_DCS_Option			option;		/* パディング形式					*/
	COM_DCS_ComponentOrder	order;		/* 色の並び							*/
} COM_DeviceColorSpace;


#endif
