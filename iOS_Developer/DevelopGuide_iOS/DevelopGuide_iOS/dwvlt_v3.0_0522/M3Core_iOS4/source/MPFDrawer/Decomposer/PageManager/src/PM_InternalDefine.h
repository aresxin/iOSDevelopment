/*
      Copyright (C) Fuji Xerox Co; Ltd. 2001. All rights reserved.

      PM_InternalDefine.h -- definition of Page Manager 

      Created:        Feb 23, 2001 By Kunihiko Kobayashi
      Modified:


*/

#ifndef PM_INTERNALDEF_H_INCLUDED
#define PM_INTERNALDEF_H_INCLUDED

#include			<stdio.h>
#include			<math.h>
#include			<string.h>
#include			"MI_MemoryInterface.h"	
#include 			"RND_Renderer.h"
#include 			"COM_DeviceColorSpace.h"


#if !defined(HB_USE_FIXEDPOINT)
/* 浮動小数点使用(デフォルト)	*/
#include <float.h>
typedef float			PM_FLOAT;  /* 32ビット浮動小数点型 */
typedef double			PM_DOUBLE; /* 64ビット浮動小数点型 */
typedef float			PM_REAL32; /* 32ビット実数型		*/
typedef double			PM_REAL64; /* 64ビット実数型		*/
#else
/* 固定小数点使用	*/
#include "COM_HB_Fixed.h"
typedef float			PM_FLOAT;  /* 32ビット浮動小数点型 */
typedef double			PM_DOUBLE; /* 64ビット浮動小数点型 */
typedef HB_Fixed32		PM_REAL32; /* 32ビット実数型		*/
typedef HB_Fixed64		PM_REAL64; /* 64ビット実数型		*/
#endif	/* HB_USE_FIXEDPOINT	*/



extern void PM_WriteLog(void *MI, const char *fmt, ...);


typedef long			PM_Error;

#define PM_TRUE			1
#define PM_FALSE		0
#define PM_NOERROR		0
#define PM_ERROR		1
#define PM_NOERR()		{ return PM_NOERROR; }
#define PM_ERR(MI)		{ printf("ERR:%s,%d\n",__FILE__,__LINE__); MI_WriteLog(MI, "ERR:%s,%d\n",__FILE__,__LINE__); return PM_ERROR; }
/*
#define PM_ERR(MI)		{ return PM_ERROR; }
*/

#define PM_MARGIN_WIDTH    	1.0  /* inch */
#define PM_MARGIN_HEIGHT   	1.0  /* inch */

#define PM_Y(y)			((long)(y))
#define PM_SX1(sx)		((long)floor((PM_REAL32)(sx)))
#define PM_EX1(ex)		((long)floor((PM_REAL32)(ex)))
#define PM_SX2(sx)		((long)floor((PM_REAL32)(sx)+0.5))
#define PM_EX2(ex)		((long)floor((PM_REAL32)(ex)+0.5)-1)
#define PM_CHECKEDGE(sx,ex)	{ if( ex < sx ) PM_NOERR(); }                                    
#define PM_FLOATTOFIX16(x)	((long)(x * 65536))
#define PM_FIX16TOFLOAT(x)	((float)((double)(x) / (double)(65536)))

#define PM_ISZERO(a)       	(((a) == 0.0) ? 1 : 0)
#define PM_ABS(x)          	(((x) < 0) ? -(x) : (x))
#define PM_SGN(a)          	(((a) < 0) ? -1 : 0)
#define PM_ZSGN(a)         	(((a) < 0) ? -1 : (((a) > 0) ? 1 : 0))  
#define PM_MAX(x,y)        	(((x) > (y)) ? (x) : (y))
#define PM_MIN(x,y)        	(((x) < (y)) ? (x) : (y))
#define PM_FLOOR		floor
#define PM_CEIL			ceil
#define PM_LARGENUMBER   	(1000 * 1024 * 1024)
#define PM_MEMSET(a, b, c)	memset(a, b, c)
#define PM_MEMCPY(a, b, c)	memcpy(a, b, c)
#define PM_MEMCMP(a, b, c)	memcmp(a, b, c)

/* PageGenerator Type */
typedef enum PM_GeneratorType
{
    PM_PAGEGENERATOR_DLGENERATOR = 0,
    PM_PAGEGENERATOR_VBGENERATOR = 1
    
} PM_GeneratorType;

#define PM_EL_MEM_BLOCK_SIZE   	(128 * 1024)
#define PM_DL_MEM_BLOCK_SIZE   	(16 * 1024)
#define PM_DL_MEM_CELL_SIZE   	(16 * 1024)

/* EdgeList MemoryBlock Definition */
typedef struct PM_EdgeListCell 
{
    struct PM_EdgeListCell 	*next;
    short 			sx;
    short 			ex;

} PM_EdgeListCell;

/* DisplayList MemoryBlock Definition */
typedef struct PM_DisplayListCell
{
    struct PM_DisplayListCell	*next;
    struct PM_DisplayListCell	*prev;
    int                         data[4];
    unsigned char               buf[PM_DL_MEM_CELL_SIZE - 24];

} PM_DisplayListCell;

/* PageData Definition */
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
    unsigned long		fallback;
    void                *prefile;
    void                *pretagfile;
    void                *outfile;
    void                *outtagfile;
    void                *data;

} PM_PageInfo;



#endif

