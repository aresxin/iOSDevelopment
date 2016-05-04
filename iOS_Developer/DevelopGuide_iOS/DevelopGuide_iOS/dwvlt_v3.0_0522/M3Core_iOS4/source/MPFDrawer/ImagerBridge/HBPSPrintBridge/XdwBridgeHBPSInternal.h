/*!
  @file  XdwBridgeHBPSInternal.h
  @brief XdwBridgeHBPS内部用ヘッダファイル

  XdwBridgeHBPS class内部で使われる，マクロやクラスの定義を記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-09
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-05-09	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEHBPSINTERNAL_H_INCLUDED
#define XDWBRIDGEHBPSINTERNAL_H_INCLUDED

const double PI = 3.1415926535;

/*
 * matrix =	|   a   b   0 |
 *		|   c   d   0 |
 *		|  tx  ty   1 |
 */
typedef struct
{
	float a;
	float b;
	float c;
	float d;
	float tx;
	float ty;
} HBPS_Matrix;

typedef struct
{
	signed int	ly;		/* 矩形の原点から最近点のY座標値 */
	signed int	uy;		/* 矩形の原点から最遠点のY座標値 */
	float		lx;		/* 矩形の原点から最近点のX座標値 */
	float		ux;		/* 矩形の原点から最遠点のX座標値 */
} HBPS_RectangleData;

/*----------------------------------*/
/*	出力仕様パラメータ				*/
/*----------------------------------*/
typedef struct
{
	long	format;
	long	compress;
	long	guarantee;
	long	filter;
	long	colorspace;
	long	bytes;
	long	order;
	long	option;
	long	tag;
} HBPS_OutParam;

#endif /* XDWBRIDGEHBPSINTERNAL_H_INCLUDED */
