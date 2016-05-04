/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_CommandUtility.h - コマンドクラスのヘルパー関数群のヘッダ
 *
 */

#ifndef INC_IMG_CommandUtility_h
#define INC_IMG_CommandUtility_h

#include "IMG_Context.h"
#include "IMG_Common.h"
#include "IMG_CommandImage.h"
#include "IMG_RopDataConversionLib.h"

/*
 * イメージ描画コマンドをイメージデータ変換ライブラリで扱える構造体に変換する。
 */
extern void IMG_CommandUtil_DiToImage(
	IMG_Context					*context,
	IMG_Command_DrawImage		*di,
	IMG_RopDataConvLib_Image	*image);

/*
 * 色値の同一性判定
 */
static IMG_BOOL IMG_CommandUtil_BgrEqual(
	IMG_ColorData	*color1,
	IMG_ColorData	*color2)
{
	return color1->bgr.blue  == color2->bgr.blue &&
		   color1->bgr.green == color2->bgr.green &&
		   color1->bgr.red   == color2->bgr.red;
}

static IMG_BOOL IMG_CommandUtil_GrayEqual(
	IMG_ColorData	*color1,
	IMG_ColorData	*color2)
{
	return color1->gray == color2->gray;
}

static IMG_BOOL IMG_CommandUtil_ColorEqual(
	IMG_ColorSpace	space1,
	IMG_ColorData	*color1,
	IMG_ColorSpace	space2,
	IMG_ColorData	*color2)
{
	return space1 == space2 &&
		   space1 == IMG_COLOR_SPACE_GRAY ?
		   IMG_CommandUtil_GrayEqual(color1, color2) :
		   IMG_CommandUtil_BgrEqual(color1, color2);
}

/*
 * 色の黒判定
 */
static IMG_BOOL IMG_CommandUtil_IsGrayBlack(
	IMG_ColorData	*color)
{
	return color->gray == 0xff;
}

static IMG_BOOL IMG_CommandUtil_IsBgrBlack(
	IMG_ColorData	*color)
{
	return color->bgr.blue  == 0 &&
		   color->bgr.green == 0 &&
		   color->bgr.red   == 0;
}

static IMG_BOOL IMG_CommandUtil_IsBlack(
	IMG_ColorSpace	space,
	IMG_ColorData	*color)
{
	return space == IMG_COLOR_SPACE_GRAY ?
			IMG_CommandUtil_IsGrayBlack(color) : 
			IMG_CommandUtil_IsBgrBlack(color);
}

/*
 * 色の白判定
 */
static IMG_BOOL IMG_CommandUtil_IsGrayWhite(
	IMG_ColorData	*color)
{
	return color->gray == 0x00;
}

static IMG_BOOL IMG_CommandUtil_IsBgrWhite(
	IMG_ColorData	*color)
{
	return color->bgr.blue  == 0xff &&
		   color->bgr.green == 0xff &&
		   color->bgr.red   == 0xff;
}

static IMG_BOOL IMG_CommandUtil_IsWhite(
	IMG_ColorSpace	space,
	IMG_ColorData	*color)
{
	return space == IMG_COLOR_SPACE_GRAY ?
			IMG_CommandUtil_IsGrayWhite(color) : 
			IMG_CommandUtil_IsBgrWhite(color);
}

/*
 * 黒データの生成
 */
static void IMG_CommandUtil_ConstructGrayBlack(
	IMG_ColorData	*color)
{
	color->gray = 0xFF;
}

static void IMG_CommandUtil_ConstructBgrBlack(
	IMG_ColorData	*color)
{
	color->bgr.blue  = 0x00;
	color->bgr.green = 0x00;
	color->bgr.red   = 0x00;
}

static void IMG_CommandUtil_ConstructBlack(
	IMG_ColorSpace	space,
	IMG_ColorData	*color)
{
	if (space == IMG_COLOR_SPACE_GRAY)
		IMG_CommandUtil_ConstructGrayBlack(color);
	else
		IMG_CommandUtil_ConstructBgrBlack(color);
}

/*
 * 白データの生成
 */
static void IMG_CommandUtil_ConstructGrayWhite(
	IMG_ColorData	*color)
{
	color->gray = 0x00;
}

static void IMG_CommandUtil_ConstructBgrWhite(
	IMG_ColorData	*color)
{
	color->bgr.blue  = 0xff;
	color->bgr.green = 0xff;
	color->bgr.red   = 0xff;
}

static void IMG_CommandUtil_ConstructWhite(
	IMG_ColorSpace	space,
	IMG_ColorData	*color)
{
	if (space == IMG_COLOR_SPACE_GRAY)
		IMG_CommandUtil_ConstructGrayWhite(color);
	else
		IMG_CommandUtil_ConstructBgrWhite(color);
}

/*
 * 色値のコピー
 */
static void IMG_CommandUtil_CopyGrayColor(
	IMG_ColorData	*src,
	IMG_ColorData	*dst)
{
	dst->gray = src->gray;
}

static void IMG_CommandUtil_CopyBgrColor(
	IMG_ColorData	*src,
	IMG_ColorData	*dst)
{
	dst->bgr.blue  = src->bgr.blue;
	dst->bgr.green = src->bgr.green;
	dst->bgr.red   = src->bgr.red;
}

static void IMG_CommandUtil_CopyColor(
	IMG_ColorSpace	space,
	IMG_ColorData	*src,
	IMG_ColorData	*dst)
{
	if (space == IMG_COLOR_SPACE_GRAY)
		IMG_CommandUtil_CopyGrayColor(src, dst);
	else
		IMG_CommandUtil_CopyBgrColor(src, dst);
}

/*
 * 座標点の同一性判定
 */
static IMG_BOOL IMG_CommandUtil_PointEqual(
	IMG_Point	*p1,
	IMG_Point	*p2)
{
	return p1->x == p2->x && p1->y == p2->y;
}

#endif /* INC_IMG_CommandUtility_h */

/*
 * Log
 * 27.Feb.2002 Yozo Kashima 新規作成。
 */

/* end of IMG_CommandUtility.h */
