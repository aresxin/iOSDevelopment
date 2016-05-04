/*
	Copyright (C) Fuji Xerox Co;Ltd. 2001. All rights reserved.
 
	rnd_internaldef.h -- definition of Renderer

	Created:	Feb 23, 2001 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef RND_INTERNALDEF_H_INCLUDED
#define RND_INTERNALDEF_H_INCLUDED

#include			<stdio.h>
#include			<math.h>
#include			<string.h>

#include			"MI_MemoryInterface.h"
#include			"COM_ObjectTag.h"
#include			"COM_DeviceColorSpace.h"
#include			"COM_Edge.h"
#include			"COM_EdgeLine.h"
#include			"COM_OutputLocation.h"
#include			"COM_ES_Spec.h"
#include			"COM_ES_DistributorIF.h"

extern void RND_WriteLog(void *MI, const char *fmt, ...);

typedef long    		RND_Error;

#define RND_TRUE		1
#define RND_FALSE		0
#define RND_NOERROR             0
#define RND_ERROR       	1
#define RND_NOERR()             { return RND_NOERROR; }
#define RND_ERR(MI)		{ printf("ERR:%s,%d\n",__FILE__,__LINE__); MI_WriteLog(MI, "ERR:%s,%d\n",__FILE__,__LINE__); return RND_ERROR; }
/*
#define RND_ERR(MI)		{ return RND_ERROR; }
*/

#define RND_MARGIN_WIDTH    	1.0  /* inch */
#define RND_MARGIN_HEIGHT   	1.0  /* inch */

#define RND_DL_IMG_SPLIT_HEIGHT	16
#define RND_DL_IMG_SPLIT_LIMIT	3 /* AR1552 */

#define RND_Y(y)		((long)(y))
#define RND_SX1(sx)		((long)((float)(sx)))
#define RND_EX1(ex)		((long)((float)(ex)))
#define RND_SX2(sx)		((long)((float)(sx) + 0.5))
#define RND_EX2(ex)		((long)((float)(ex) + 0.5) - 1)
#define RND_CHECKEDGE(sx,ex)	{ if( ex < sx ) PM_NOERR(); }                                    

#define RND_FLOATTOFIX16(x)	((long)(x * 65536))
#define RND_FIX16TOFLOAT(x)	((float)((double)(x) / (double)(65536)))
#define RND_FSX1(sx)		((long)((sx >> 16) & 0xffff))
#define RND_FEX1(ex)		((long)((ex >> 16) & 0xffff))
#define RND_FSX2(sx)		(RND_SX2(RND_FIX16TOFLOAT(sx)))
#define RND_FEX2(ex)		(RND_EX2(RND_FIX16TOFLOAT(ex)))

#define RND_ISZERO(a)       	(((a) == 0.0) ? 1 : 0)
#define RND_ABS(x)          	(((x) < 0) ? -(x) : (x))
#define RND_SGN(a)          	(((a) < 0) ? -1 : 0)
#define RND_ZSGN(a)         	(((a) < 0) ? -1 : (((a) > 0) ? 1 : 0))  
#define RND_MAX(x,y)        	(((x) > (y)) ? (x) : (y))
#define RND_MIN(x,y)        	(((x) < (y)) ? (x) : (y))
#define RND_FABS(x)        	fabs(x)
#define RND_FLOOR(x)		floor(x)
#define RND_CEIL(x)		ceil(x)
#define RND_MEMSET(a, b, c)	memset(a, b, c)
#define RND_MEMCPY(a, b, c)	memcpy(a, b, c)

#define RND_TAG_FONT		COM_OBJECTTAG_FONT
#define RND_TAG_GRAPHICS	COM_OBJECTTAG_GRAPHICS
#define RND_TAG_IMAGE		COM_OBJECTTAG_IMAGE
#define RND_TAG_BACKGROUND	COM_OBJECTTAG_BACKGROUND
#define RND_TAG(T)		(T & 0x00000003)

#define RND_EDGE_TYPE_CONSTANT	0x00000000
#define RND_EDGE_TYPE_POINTER	0x00000080
#define RND_EDGE_TYPE(T)	(T & 0x00000080)

#define RND_EDGE_INFO_DIFFIMAGE 0x00000000
#define RND_EDGE_INFO_SAMEIMAGE 0x00000040
#define RND_EDGE_INFO(T)        (T & 0x00000040)


typedef enum RND_RendererType
{
    RND_PAGERENDERER_DLRENDERER = 0
    
} RND_RendererType;

/*
typedef struct
{
    long		format; 
    long		compress;
    long 		guarantee;
    long		filter;
    long		colorspace;
    long		bytes;
    long		order;
    long		option;
    long		tag;
      
} RND_OutputParameter;
*/

typedef struct RND_EdgeListCell
{
    struct RND_EdgeListCell 	*next;
    unsigned short 		sx;
    unsigned short 		ex;

} RND_EdgeListCell;


typedef struct
{
    long                width;
    long                height;
    unsigned long       rop;
    unsigned long       prerop;
	unsigned long		pat0;
	unsigned long		prepat0;
    unsigned long       color;
    unsigned long       type;
    unsigned long       fallback;
    void                *prefile;
    void                *pretagfile;
    void                *outfile;
    void                *outtagfile;
    void                *data;

} RND_PageInfo;

#endif
