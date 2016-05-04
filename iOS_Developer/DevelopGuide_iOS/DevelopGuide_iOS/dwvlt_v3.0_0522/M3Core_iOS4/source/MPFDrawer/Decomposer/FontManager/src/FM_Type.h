/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_TypeExt.h -- definition of Font Manager 

	Created:	Jun 28, 2002 By Kunihiko Kobayashi 
	Modified:	
*/

#ifndef _FM_TYPE_H_INCLUDED_
#define _FM_TYPE_H_INCLUDED_

#include <math.h>
#include <string.h>
#include "FM_Type.h"

enum {
    FM_NOERROR		= 0,
    FM_ERROR		= 1
};

#define FM_ERR() { return FM_ERROR; }
#define FM_NOERR() { return FM_NOERROR; }

#define FM_PI 				3.1415926535
#define FM_TRUE				1
#define FM_FALSE			0
#define FM_ITALIC_ANGLE			0.34  /* cos */
#define FM_CHAR_REGISTER_SIZE		500
#define FM_CACHE_SIZE		(800 * 1024)

#define FM_ISZERO(a)       	(((a) == 0.0) ? 1 : 0)
#define FM_ABS(x)          	(((x) < 0) ? -(x) : (x))
#define FM_SGN(a)          	(((a) < 0) ? -1 : 0)
#define FM_ZSGN(a)         	(((a) < 0) ? -1 : (((a) > 0) ? 1 : 0))  
#define FM_MAX(x,y)        	(((x) > (y)) ? (x) : (y))
#define FM_MIN(x,y)        	(((x) < (y)) ? (x) : (y))
#define FM_FLOOR		floor
#define FM_CEIL			ceil
#define FM_LARGE_NUMBER   	(1000 * 1024 * 1024)
#define FM_SMALL_NUMBER		0.0000001
#define FM_MEMSET(a, b, c)	memset(a, b, c)
#define FM_MEMCPY(a, b, c)	memcpy(a, b, c)
#define FM_MEMCMP(a, b, c)	memcmp(a, b, c)
#define FM_FLOATTOFIX16(x)      ((long)(x * 65536))
#define FM_FIX16TOFLOAT(x)      ((float)((double)(x) / (double)(65536)))

/***** COMMON DEFINE ******/

typedef enum 
{
	FM_FONT_DIRECTION_V = 0,
	FM_FONT_DIRECTION_H = 1

} FM_FontDirection;

typedef struct
{
	long	saHeight;
	long	saAscent;
	long	saDescent;
	long	saInternalLeading;
	long	saWidth;
	long	saOverhang;
	long	saClipExtend;

} FM_StringArea;

typedef struct
{
	short	y;
	short	sx;
	short	ex;
} FM_ClipEdge;

typedef struct
{
    double a;
    double b;
    double c;
    double d;
    double tx;          /* This value is ignored               */
    double ty;          /* This value is ignored               */

} FM_FontMatrix;


/***** DrawDataFont() DEFINE ******/

#define FM_DDF_DATA_OFFSET        0

/** Bitmap **/
#define FM_DDFB_OFFSETX_OFFSET          8
#define FM_DDFB_OFFSETY_OFFSET         12
#define FM_DDFB_HEIGHT_OFFSET          16
#define FM_DDFB_WIDTH_OFFSET           18
#define FM_DDFB_WIDTHBYTES_OFFSET      20
#define FM_DDFB_DEPTH_OFFSET           21
#define FM_DDFB_DATA_OFFSET            22

/** Outline **/
#define FM_DDFO_POINTSIZE_OFFSET		8
#define FM_DDFO_POINTNUM_OFFSET        12
#define FM_DDFO_LINENUM_OFFSET         14
#define FM_DDFO_DATA_OFFSET            16

/* (1)Italic Flag  */
typedef enum {
  FM_DDF_ITALIC_OFF   = 0,
  FM_DDF_ITALIC_ON,
} FM_DDF_ITALIC_FLAG;

/* (2)Weight  */

/* (3)Compress format */
typedef enum {
  FM_DDF_COMPRESS_NOCOMP    = 0,
  FM_DDF_COMPRESS_MMR,
  FM_DDF_COMPRESS_DELTALOW,
} FM_DDF_COMPRESS_FORMAT;

/* (4)Gray Flag */
typedef enum {
  FM_DDF_GRAY_OFF  = 0,
  FM_DDF_GRAY_ON
} FM_DDF_GRAY_FLAG;

/* (5)Font Type (format) */
typedef enum {
  FM_DDF_DATA_FIXED_OUTLINE = 0,
  FM_DDF_DATA_FLOAT_OUTLINE,
  FM_DDF_DATA_GRAY_1,
  FM_DDF_DATA_GRAY_2,
  FM_DDF_DATA_GRAY_4,
  FM_DDF_DATA_GRAY_6,
  FM_DDF_DATA_GRAY_8,
  FM_DDF_DATA_RESERVED,
  FM_DDF_DATA_EDGELIST,
  FM_DDF_DATA_CODE
} FM_DDF_DATA_FORMAT;

/*(6) Reserved */

/*(7) DataSize */


/***** DATA TYPE DEFINE ******/

typedef struct {
  short		      start;
  short		      end;
} FM_FontEdge;

typedef struct {
  float               offsety;
  float               offsetx;
  unsigned short      height;
  unsigned short      width;
  unsigned char       pixelBits;
  unsigned short      lineAmount;
  unsigned short      edgeAmount;
  unsigned short      *line;
  void		      *edge;
} FM_EdgelistFont;

typedef struct {
  float               offsety;
  float               offsetx;
  unsigned short      height;
  unsigned short      width;
  unsigned short      widthBytes;
  unsigned char       pixelBits;
  unsigned char       *bitmap;
} FM_BitmapFont;

typedef enum {
  FM_FONT_DATA_TYPE_EDGELIST	= 0,
  FM_FONT_DATA_TYPE_BITMAP 	= 1
} FM_EnumFontDataType;

#endif
