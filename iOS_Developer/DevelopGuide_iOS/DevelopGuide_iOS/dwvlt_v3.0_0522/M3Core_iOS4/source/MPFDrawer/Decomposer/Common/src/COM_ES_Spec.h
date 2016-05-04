/*
 * Copyright (C) 2001 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_ES_Spec.h -- ES_Spec型の定義
 * (元のRND_EdgeSinkSpec.h)
 *
 * Created : 2003.07.17 Masao.Morita(DPSC SWD PFCoreG)
 *
 */

#if !defined(COM_ES_SPEC_H_INCLUDED)
#define COM_ES_SPEC_H_INCLUDED

#include "COM_DeviceColorSpace.h"


#define ES_FILTERMAX	16		/* HB_Decomposer.hと合わせる事	*/

/*----------------------------------*/
/*	出力フォーマットの指定			*/
/*----------------------------------*/
typedef enum ES_FormatterTypeT
{
	/* 0x0000 - 0x0006 : assigned to Base Service						*/
	/* 0x0000 : 中間コードフォールバック用								*/
	ES_FORMATTER_ALLA = 0x0000,				/* ALLA(点順次)形式での出力	*/

	/* 0x0007 - 0x1FFF : assigned to FXPS Product						*/
	ES_FORMATTER_PCL6	 = 0x0007,			/* FXPS:Reserve				*/
	ES_FORMATTER_AKAISHI = 0x0008,			/* FXPS:Gokuu				*/
	ES_FORMATTER_Legion	 = 0x0009,			/* FXPS:Legion				*/

	/* 0x2000 - 0x3FFF : assigned to FX Product							*/
	ES_FORMATTER_ARTEX_Image = 0x2000,		/* FX  :ART-EX Image Mode	*/

	/* 0x4000 - 0x5FFF : reserved										*/

	/* 0x6000 - 0x7FFF : assigned to Experimental work					*/
	/* 0x8000以降は16ビットコンパイラでエラーになるので未使用(AR1572)	*/
	ES_FORMATTER_ALLA_SEPARATION = 0x6000,	/* ALLA(面順次)形式での出力	*/
	ES_FORMATTER_PDF,						/* PDF形式での出力			*/
	ES_FORMATTER_PLW,						/* PLW形式での出力			*/
	ES_FORMATTER_TIFF,						/* TIFF形式での出力			*/
	ES_FORMATTER_D_RASTER,					/* D-Raster形式での出力		*/
	ES_FORMATTER_BMP,						/* BMP形式での出力			*/
	ES_FORMATTER_DOUT,						/* ES-DirectOutput形式での出力	*/
	ES_FORMATTER_MRC						/* MRC形式での出力			*/

} ES_FormatterType;

/*----------------------------------*/
/*	フィルタ処理の指定				*/
/*----------------------------------*/
/* FilterはCodecの前に適用される	*/
/*----------------------------------*/
typedef enum ES_FilterTypeT
{
	ES_FILTER_NONE = 0,				/* フィルタなし				*/
	ES_FILTER_MERGEEDGE,			/* エッジの結合				*/
	ES_FILTER_EXPANDEDGE_CONTONE,	/* エッジの画素展開(点順)	*/
	ES_FILTER_EXPANDEDGE_SEPARATION,/* エッジの画素展開(線順)	*/
	ES_FILTER_CONTONE2SEPARATION,	/* ラスタ点順->線順変換		*/
	ES_FILTER_SEPARATION2CONTONE,	/* ラスタ線順->点順変換		*/
	ES_FILTER_ED,					/* 誤差拡散					*/
	ES_FILTER_UCRBG,				/* RGBTag->CMYK				*/
	ES_FILTER_HALFTONE,				/* 減色						*/
	ES_FILTER_TRAPPING				/* トラッピング				*/
} ES_FilterType;

/*----------------------------------*/
/*	圧縮形式の指定					*/
/*----------------------------------*/
typedef enum ES_CodecTypeT
{
	ES_CODEC_NONE = 0,				/* 圧縮なし					*/
	ES_CODEC_ALLA,					/* ALLA圧縮					*/
	ES_CODEC_SQUARE21,				/* Square21圧縮				*/
	ES_CODEC_JPEG,					/* JPEG圧縮					*/
	ES_CODEC_DELTAROW				/* DeltaRow圧縮				*/
} ES_CodecType;


/*----------------------------------*/
/*	EdgeSinkの仕様定義				*/
/*----------------------------------*/
typedef struct ES_SpecT
{
	ES_FormatterType	formatter;	/* 出力フォーマットの指定		*/
	long				fmtArg;		/* フォーマット初期化引数		*/
	
	ES_FilterType		filter[ES_FILTERMAX];/* フィルタ処理の指定	*/
	long				fltArg[ES_FILTERMAX];/* フィルタの初期化引数*/

	ES_CodecType		codec;		/* 圧縮形式の指定				*/
	long				cdcArg;		/* 圧縮の初期化引数				*/

	/* 白黒ページの設定		*/
	int						bwDepth;
	int						bwTag;
	COM_DeviceColorSpace	bwDCS;
	
	/* カラーページの設定	*/
	int						clDepth;
	int						clTag;
	COM_DeviceColorSpace	clDCS;

	void					*extraParam; /* 出力形式依存パラメータ */
	long					formatMode;  /* Formatterの形式(Job/Page単位) */

} ES_Spec;


#endif

