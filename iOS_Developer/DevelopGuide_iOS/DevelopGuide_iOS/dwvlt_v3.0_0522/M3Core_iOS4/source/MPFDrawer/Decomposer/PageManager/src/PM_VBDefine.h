/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	PM_VBDefine.h -- definition of VB structur in VB renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef VB_DLDEFINE_H_INCLUDED
#define VB_DLDEFINE_H_INCLUDED

/* setting output bytes per pixel 3 or 4*/
//#ifdef LINUX
#if 0
#define PM_VB_OUTPUT_BYTES		4
#else /* LINUX */
#define PM_VB_OUTPUT_BYTES		3
#endif /* LINUX */

#define PM_VB_IMG_MEM_LIMIT		(256 * 1024 * 1024)
#define PM_VB_IMG_FILE_LIMIT		(256 * 1024 * 1024)
#define PM_VB_IMG_RENDER_SIZE		(512 * 1024)

typedef union
{
    unsigned long 	value;
    unsigned char	comp[4];
    void 	  	*ptr;

} PM_VBGenerator_Pixel;

typedef struct
{
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

}PM_VBPattern;
    
typedef struct
{
    unsigned char 	itype;
    unsigned char 	info;
    unsigned char 	rop;
    short 		offsetx;
    short 		offsety;
    unsigned short 	dw;
    unsigned short 	dh;
    unsigned short 	sw;
    unsigned short 	sh;
    PM_VBPattern 	*pattern;
    unsigned char 	*buffer;
    long 		offset;
    unsigned char 	*pallet;
    unsigned char	*render_buffer;
    unsigned char	*render_pallet;
    long		render_sy;
    long		render_ey;
    double		render_ratex;
    double		render_ratey;

}PM_VBImage;

typedef struct
{
    unsigned long	tag;
    unsigned char	ropMode;
    unsigned char	ropCode;
    PM_VBImage		*image;
    PM_VBPattern	*pattern;
    PM_VBGenerator_Pixel color;

} PM_VBMode;

typedef struct {
    short		component,
			next_pixel;
    unsigned long	pixel_num;

    void		**buffer;
} PM_VBPixelBufferInfo;

#endif
