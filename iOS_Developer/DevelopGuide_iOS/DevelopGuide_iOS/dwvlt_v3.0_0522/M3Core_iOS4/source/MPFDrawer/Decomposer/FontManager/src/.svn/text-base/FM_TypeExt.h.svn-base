/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_Type.h -- definition of Font Manager 

	Created:	Jun 28, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef _FM_TYPEEXT_H_INCLUDED_
#define _FM_TYPEEXT_H_INCLUDED_

#include <stdio.h>


/* PageInfo */
typedef struct {
    void			*DC;
    long			height;
    long			width;
    long			widthBytes;
    unsigned char*		buffer;
} FM_PageInfo;

/* Encoding */
typedef enum {
    FM_ENCODE_ANSI		= 1,
    FM_ENCODE_UNICODE		= 2,
    FM_ENCODE_SJIS		= 3,
    FM_ENCODE_SYMBOL		= 4,
	FM_ENCODE_HANGEUL	= 5,
	FM_ENCODE_JOHAB		= 6,
	FM_ENCODE_GB2312		= 7,
	FM_ENCODE_CHINESEBIG5= 8
} FM_Encoding;

/* LogFont */
typedef struct {
    int 			lfHeight;
    int 			lfWidth;
    int 			lfEscapement;
    int 			lfOrientation;
    int 			lfWeight;
    unsigned char 		lfItalic;
    unsigned char 		lfUnderline;
    unsigned char 		lfStrikeOut;
    unsigned char 		lfCharSet;
    unsigned char 		lfOutPrecision;
    unsigned char 		lfClipPrecision;
    unsigned char 		lfQuality;
    unsigned char 		lfPitchAndFamily;
    unsigned char 		lfFaceNameSize;
    unsigned char		lfFaceName[64];
    FM_Encoding 		lfFaceNameEncoding;
    unsigned char		lfEmulation;
    unsigned char		lfPhysicalCharSet;
} FM_LogFont;

/* Matrix */
typedef struct {
    double			a;   /* | a     b | */
    double			b;   /* |         | */
    double			c;   /* | c     d | */
    double			d;   /* |         | */
    double			tx;  /* | tx   ty | */
    double			ty;  /* |         | */
} FM_Matrix;

/* Point */
typedef struct {
    double			x;
    double			y;
} FM_Point;

/* Rect */
typedef struct {
    double			lx;
    double			ly;
    double			ux;
    double			uy;
} FM_Rect;

/* PitchMode */
typedef enum {
    FM_PITCH_MODE_ABS = 1,
    FM_PITCH_MODE_REL = 2,
    FM_PITCH_MODE_ADD = 3
} FM_PitchMode;

/* TextAlign */
typedef enum {
    /* 2bit */
    FM_TEXT_ALIGN_V_NOT		= 0x00,
    FM_TEXT_ALIGN_V_TOP		= 0x01,
    FM_TEXT_ALIGN_V_BASELINE    = 0x02,
    FM_TEXT_ALIGN_V_BOTTOM      = 0x03,
    FM_TEXT_ALIGN_V_MASK        = 0x03,
    /* 2bit */
    FM_TEXT_ALIGN_H_NOT         = 0x00,
    FM_TEXT_ALIGN_H_LEFT        = 0x04,
    FM_TEXT_ALIGN_H_CENTER      = 0x08,
    FM_TEXT_ALIGN_H_RIGHT       = 0x0c,
    FM_TEXT_ALIGN_H_MASK        = 0x0c,
    /* 2bit */
    FM_TEXT_ALIGN_CP_NOT        = 0x00,
    FM_TEXT_ALIGN_CP_NOUPDATE   = 0x10,
    FM_TEXT_ALIGN_CP_UPDATE     = 0x20,
    FM_TEXT_ALIGN_CP_MASK       = 0x30 
} FM_TextAlign;

/* RectOption */
typedef enum {
    FM_RECT_OPTION_NO_USE	= 0x00,
    FM_RECT_OPTION_CLIP		= 0x01,
    FM_RECT_OPTION_OPAQUE	= 0x02
} FM_RectOption;

/* ColorMode */
typedef enum {
    FM_COLOR_MODE_TRANSPARENT	= 1,
    FM_COLOR_MODE_OPAQUE	= 2
} FM_ColorMode;

/* String */
typedef struct {
    FM_PitchMode	 	pitchMode;
    long 			pitchLength;
    float*			pitchData;
    long 			codeSize;
    unsigned char* 		codePtr;
    FM_Encoding	 		codeEncoding;
    FM_TextAlign		textAlign;
    FM_ColorMode		bkColorMode;
    unsigned char		bkColor[3];
} FM_CodeString;

typedef struct {
    unsigned long		cacheKey;
    unsigned char		*dataPtr;
} FM_DataCharacter;

/* Attribute */
typedef struct {
    unsigned long 		tag;
    unsigned long 		color;
    void*         		pattern;
    unsigned long 		ROP;
} FM_Attribute;

/* FontInfo */
typedef struct FM_CharInfo_t {
  struct FM_CharInfo_t *next;
  long charSet;
  long charCode;
  long point[8];
} FM_CharInfo;
  
/* Emulation */
typedef enum {
    FM_EMULATION_NO_USE		= 0x00,
    FM_EMULATION_BOLD		= 0x01,
    FM_EMULATION_SPECIAL	= 0x02,
	FM_EMULATION_BOLD_DESIGN= 0xc0
} FM_Emulation;

#endif
