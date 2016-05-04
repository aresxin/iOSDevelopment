/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	RND_DLDefine.h -- definition of DL structur in DL renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef RND_DLDEFINE_H_INCLUDED
#define RND_DLDEFINE_H_INCLUDED

#include "COM_ObjectTag.h"


/* DL Color Type */
#define	RND_DLCTYPE_CONSTANT 		0x00000000
#define	RND_DLCTYPE_POINTER 		0x00000080

/* DL Object Type */
#define RND_DLTAG_GRAPHICS              COM_OBJECTTAG_GRAPHICS          
#define RND_DLTAG_FONT                  COM_OBJECTTAG_FONT
#define RND_DLTAG_IMAGE                 COM_OBJECTTAG_IMAGE
#define RND_DLTAG_BACKGROUND            COM_OBJECTTAG_BACKGROUND

/* DL Shape Type */
#define	RND_DLSHAPE_RECTANGLE 		0x00000000
#define	RND_DLSHAPE_LINE 		0x00000010
#define	RND_DLSHAPE_TRAPEZOID1 		0x00000020
#define	RND_DLSHAPE_TRAPEZOID2 		0x00000030
#define	RND_DLSHAPE_IEL  		0x00000040

/* DL IMG Type */
#define	RND_DLPOINTER_PATTERN 		0x00
#define	RND_DLPOINTER_IMAGE 		0x01

/* GET DL INFO */
#if (COM_OBJECTTAG_BITS == 2)
#define RND_GET_DLTAG(H)      		(H->info & 0x00000003)
#define RND_SET_DLTAG(H, t)             (H->info = (H->info & 0xfffffffc) | (t & 0x00000003))
#elif (COM_OBJECTTAG_BITS == 4)
#define RND_GET_DLTAG(H)      		(H->info & 0x0000000f)
#define RND_SET_DLTAG(H, t)             (H->info = (H->info & 0xfffffff0) | (t & 0x0000000f))
#endif

#define RND_GET_DLCOLOR(H)       	(H->info & 0x0000000c)
#define RND_GET_DLCTYPE(H)       	(H->info & 0x00000080)
#define RND_GET_DLSHAPE(H)       	(H->info & 0x00000070)
#define RND_GET_DLID(H)          	(H->info & 0xffffff00)
#define RND_GET_DLINFO(H)          	(H->info & 0x000000ff)
#define RND_GET_DLIMAGE(H)          	((*((char *)(H->color.ptr))))

/* SCANLINE INFO */
#define RND_DLLINEINFO_ROP               0x10
#define RND_DLLINEINFO_PATTERN           0x20

typedef struct RND_DLHeader
{
    struct RND_DLHeader *next;
    union {
	unsigned long 	value;
	unsigned char	comp[4];
	void		*ptr;
    }color;
    unsigned long 	info;
    unsigned short 	size;
    unsigned short 	height;

}RND_DLHeader;


typedef struct
{
    unsigned short 	sx;
    unsigned short 	ex;

}RND_DLRectangle;


typedef struct
{
    long 		x;
    long 		slant;

}RND_DLLine;

typedef struct
{
    long 		lx;
    long 		ux;
    long 		lslant;
    long 		uslant;

}RND_DLTrapezoid;

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

}RND_DLPattern;
    

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
    RND_DLPattern 	*pattern;
    unsigned char 	*buffer;
    long 		offset;
    unsigned char 	*pallet;
    unsigned char 	*extend;

}RND_DLImage;


typedef struct RND_DLImageExtend
{
    struct RND_DLImageExtend 	*next;
    RND_DLImage			*image;
    unsigned char		*buffer;
    unsigned char		*pallet;
    long			baseline;
    double			xtimes;
    double			ytimes;
    long			py;
    long			psx;
    long			pex;
    char			init;
    char			tag;
    char			order;

} RND_DLImageExtend;


typedef struct
{
    unsigned char       *rflag;
    RND_DLHeader        **dltable;
    void                *dlimage;

} RND_DLData;




#endif
