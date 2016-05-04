/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	PM_DLDefine.h -- definition of DL structur in DL renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef PM_DLDEFINE_H_INCLUDED
#define PM_DLDEFINE_H_INCLUDED

#include "COM_ObjectTag.h"


/* DL Color Type */
#define	PM_DLCTYPE_CONSTANT 		0x00000000
#define	PM_DLCTYPE_POINTER 		0x00000080

/* DL Object Type */
#define	PM_DLTAG_GRAPHICS 		COM_OBJECTTAG_GRAPHICS          
#define	PM_DLTAG_FONT 			COM_OBJECTTAG_FONT
#define	PM_DLTAG_IMAGE 			COM_OBJECTTAG_IMAGE
#define	PM_DLTAG_BACKGROUND 		COM_OBJECTTAG_BACKGROUND

/* DL Shape Type */
#define	PM_DLSHAPE_RECTANGLE 		0x00000000
#define	PM_DLSHAPE_LINE 		0x00000010
#define	PM_DLSHAPE_TRAPEZOID1 		0x00000020
#define	PM_DLSHAPE_TRAPEZOID2 		0x00000030
#define	PM_DLSHAPE_IEL  		0x00000040

/* DL IMG Type */
#define	PM_DLPOINTER_PATTERN 		0x00
#define	PM_DLPOINTER_IMAGE 		0x01

/* GET DL INFO */
#if (COM_OBJECTTAG_BITS == 2)
#define PM_GET_DLTAG(H)                (H->info & 0x00000003)
#elif (COM_OBJECTTAG_BITS == 4)
#define PM_GET_DLTAG(H)                (H->info & 0x0000000f)
#endif

#define PM_GET_DLCOLOR(H)       	(H->info & 0x0000000c)
#define PM_GET_DLCTYPE(H)       	(H->info & 0x00000080)
#define PM_GET_DLSHAPE(H)       	(H->info & 0x00000070)
#define PM_GET_DLID(H)          	(H->info & 0xffffff00)
#define PM_GET_DLINFO(H)          	(H->info & 0x000000ff)
#define PM_GET_DLIMAGE(H)          	((*((char *)(H->color.ptr))))

/* SCANLINE INFO */
#define PM_DLLINEINFO_ROP		0x10
#define PM_DLLINEINFO_PATTERN		0x20

/* DL GENARATING INFO */
#define PM_DL_GEN_RECT_THVAL   		4
#define PM_DL_GEN_TRAP_THVAL   		4
#define PM_DL_GEN_LINE_THVAL   		4
#define PM_DL_GEN_MEM_ALIGN		4
#define PM_DL_IMG_MEM_LIMIT		(16 * 1024)
#define PM_DL_IMG_FILE_LIMIT		(256 * 1024 * 1024)
#define PM_DL_IMG_SPLIT_HEIGHT  	16  
#define PM_DL_IMG_SPLIT_LIMIT   	3	/* AR1552 */
#define PM_DL_IMG_CACHE_SIZE		10

typedef struct PM_DLHeader
{
    struct PM_DLHeader *next;
    union {
	unsigned long 	value;
	unsigned char	comp[4];
	void		*ptr;
    }color;
    unsigned long 	info;
    unsigned short 	size;
    unsigned short 	height;

}PM_DLHeader;


typedef struct
{
    unsigned short 	sx;
    unsigned short 	ex;

}PM_DLRectangle;


typedef struct
{
    long 		x;
    long 		slant;

}PM_DLLine;

typedef struct
{
    long 		lx;
    long 		ux;
    long 		lslant;
    long 		uslant;

}PM_DLTrapezoid;

typedef struct
{
    unsigned char 	type;
    unsigned char 	ptype;
    unsigned char 	info;
    unsigned char 	rop;
    short 		offsetx;
    short 		offsety;
    unsigned short 	width;
    unsigned short 	height;
    union {
	unsigned long 	value;
	unsigned char	comp[4];
    }fgcolor;
    union {
	unsigned long 	value;
	unsigned char	comp[4];
    }bgcolor;
    unsigned char 	*buffer;

}PM_DLPattern;
    

typedef struct
{
    unsigned char 	type;
    unsigned char 	itype;
    unsigned char 	info;
    unsigned char 	rop;
    short 		offsetx;
    short 		offsety;
    unsigned short 	dw;
    unsigned short 	dh;
    unsigned short 	sw;
    unsigned short 	sh;
    PM_DLPattern 	*pattern;
    unsigned char 	*buffer;
    long 		offset;
    unsigned char 	*pallet;
    unsigned char 	*extend;

}PM_DLImage;


typedef struct
{
    unsigned char       *rflag;
    PM_DLHeader        **dltable;
    void                *dlimage;

} PM_DLData;



#endif
