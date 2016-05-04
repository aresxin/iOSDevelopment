/*
      Copyright (C) Fuji Xerox Co; Ltd. 2001. All rights reserved.

      PM_DeviceFigure.h -- definition of Page Manager 

      Created:        Feb 23, 2001 By Kunihiko Kobayashi
      Modified:


*/

#ifndef PM_DEVICEFIGURE_H_INCLUDED
#define PM_DEVICEFIGURE_H_INCLUDED

#include <stdio.h>

#if !defined(HB_USE_FIXEDPOINT)
/* 浮動小数点使用(デフォルト)	*/
typedef float			PM_DFREAL32;  /* 32ビット浮動小数点型 */
typedef double			PM_DFREAL64;  /* 64ビット浮動小数点型 */

#else
/* 固定小数点使用	*/
#include "COM_HB_Fixed.h"
typedef HB_Fixed32		PM_DFREAL32; /* 32ビット実数型		*/
typedef HB_Fixed64		PM_DFREAL64; /* 64ビット実数型		*/

#endif	/* HB_USE_FIXEDPOINT	*/



typedef struct 
{
    long			ly;	
    long			uy;	
    PM_DFREAL64			lx;	
    PM_DFREAL64			rx;	
    PM_DFREAL64			lslant;
    PM_DFREAL64			rslant;
} PM_Trapezoid;

typedef struct 
{ 
    PM_DFREAL64			sx;	
    PM_DFREAL64			sy;
    PM_DFREAL64			ex;	
    PM_DFREAL64			ey;
} PM_Line;

typedef struct 
{ 
    long			ly;	
    long			uy;	
    PM_DFREAL64			lx;	
    PM_DFREAL64			ux;	
} PM_Rectangle;

typedef struct 
{ 
    long			ly;	
    long			uy;	
    long			lx;	
    long			ux;	
} PM_FRectangle;

typedef struct 
{ 
    long 			offsetx;
    long 			offsety;
    long 			sh;
    long 			sw;
    long 			dh;
    long 			dw;
    char			polarity;
    unsigned char 		*bitmap;
} PM_Bitmap;

typedef struct 
{ 
    long 			offsetx;
    long 			offsety;
    long 			height;
    long 			width;
    char			polarity;
    unsigned char 		*bitmap;
} PM_BitmapFont;

typedef struct {
    unsigned short      	level;
    short               	start;
    short               	end;
} PM_FontEdgeGS;
  
typedef struct {
    short       		start;
    short       		end;
} PM_FontEdge;
  
typedef struct {
    long 			offsetx;
    long 			offsety;
    long      			height;
    long			width;
    unsigned char       	pixelBits;
    unsigned short      	lineAmount;
    unsigned short      	edgeAmount;
    unsigned short      	*line;
    void			*edge;
} PM_EdgeFont;

typedef struct 
{ 
    long			y;	
    PM_DFREAL64			sx;
    PM_DFREAL64			ex;
} PM_Edge;

typedef struct 
{ 
    long			x;	
    PM_DFREAL64			sy;
    PM_DFREAL64			ey;
} PM_VEdge;

typedef struct 
{ 
    short			y;	
    short			sx;
    short			ex;
} PM_FEdge;

typedef struct 
{ 
    short			x;	
    short			sy;
    short			ey;
} PM_FVEdge;

typedef struct 
{
    long			offsetx;
    long			offsety;
    long			dw;
    long			dh;
    long			sw;
    long			sh;
    long			type;
    long			info;
    long			mode;
    char			*buffer;
    FILE			*file;
} PM_Image;

typedef struct 
{
    long			offsetx;
    long			offsety;
    long			dw;
    long			dh;
    long			sw;
    long			sh;
    long			mode;
    char			*buffer;
    FILE			*file;
} PM_GrayMask;

typedef struct 
{
    long			offsetx;
    long			offsety;
    long			width;
    long			height;
    long			type;
    unsigned long		fgcolor;
    unsigned long		bgcolor;
    char			*data;
    long			id;
} PM_Pattern;
    
#endif

