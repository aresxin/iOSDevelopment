/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_ComposerTypes.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */


/* OL_ComposerTypes.h

   1998.04.09 M.Chikyu created.
*/

/* PROCESSERとリンク */
#define _LINK_PROCESSER_

#ifdef _OL_COMPOSER_H_INCLUDED_

#ifdef _LINK_PROCESSER_

/*
 プロセッサヘッダファイルがある場合

*/

#include "OL_Config.h"
#include "OL_Types.h"
#include "OL_TypesExt.h"
#include "OL_Common.h"
#include "OL_Path.h"
#include "OL_Error.h"

#ifdef OL_COVERAGE
#define CMP_COVERAGE
#endif //OL_COVERAGE

/* form Globe4 */
#define CMP_MEMCPY      OL_MEMCPY
#define CMP_MEMSET      OL_MEMSET

/* 変数型 */
#define	CMP_INT8	OL_INT8		
#define CMP_INT16	OL_INT16		
#define CMP_INT32	OL_INT32
#define CMP_UINT8	OL_UINT8	
#define CMP_UINT16	OL_UINT16	
#define CMP_UINT32	OL_UINT32	

#define	CMP_BYTE	OL_BYTE
#define	CMP_CHAR	OL_CHAR
#define	CMP_SHORT	OL_SHORT
#define	CMP_USHORT	OL_USHORT
#define	CMP_INT		OL_INT
#define	CMP_UINT	OL_UINT
#define	CMP_LONG	OL_LONG
#define	CMP_ULONG	OL_ULONG

#define CMP_VOID	OL_VOID		
#define CMP_REAL	OL_REAL32

#define	CMP_STATUS	OL_STATUS
#define	CMP_BOOL	OL_BOOL

#define	CMP_PIXELUNIT	OL_PIXELUNIT
#define	CMP_POINTUNIT	OL_POINTUNIT
#define CMP_BITMAPUNIT	OL_BITMAPUNIT


/* 構造体 */
#define	CMP_Direction		OL_Direction
#define	CMP_MetricsInfo		OL_MetricsInfo
#define	CMP_BoundingBox		OL_BoundingBox
#define	CMP_EdgeList_GS		OL_EdgeList_GS
#define	CMP_EdgeList		OL_EdgeList
#define	CMP_EdgeListInfo	OL_EdgeListInfo
#define	CMP_BitmapInfo		OL_BitmapInfo

/* 定数（真偽） */
#define CMP_TRUE		OL_TRUE
#define CMP_FALSE		OL_FALSE
#define CMP_NULL		OL_NULL

/* 定数（コントロール） */
#define	CMP_TT_OFF		OL_TT_OFFPOINT
#define	CMP_TT_ON		OL_TT_ONPOINT
#define	CMP_TT_START_OFF	OL_TT_STARTPOINT_OFF
#define	CMP_TT_START_ON		OL_TT_STARTPOINT_ON
#define	CMP_TT_START		OL_TT_STARTPOINT
#define CMP_TT_END_OFF		OL_TT_ENDPOINT_OFF
#define CMP_TT_END_ON		OL_TT_ENDPOINT_ON
#define	CMP_TT_END		OL_TT_ENDPOINT

#define	CMP_PS_VOID		ST_VOID
#define	CMP_PS_MOVETO		ST_MOVETO
#define	CMP_PS_LINETO		ST_LINETO
#define	CMP_PS_QSPLINETO	ST_QSPLINETO
#define CMP_PS_CURVETO		ST_CURVETO
#define	CMP_PS_CLOSEPATH	ST_CLOSEPATH
#define	CMP_PS_ENDCHAR		ST_ENDCHAR
#define	CMP_PS_SPECIAL		ST_SPECIAL
#define	CMP_PS_TERMINATOR	ST_TERMINATOR

	/*				0x---3 */
#define	CMP_CC_SCANCTRL_VOID	OL_CC_SCANCTRL_VOID
#define	CMP_CC_SCANCTRL_OFF	OL_CC_SCANCTRL_OFF
#define	CMP_CC_SCANCTRL_ON	OL_CC_SCANCTRL_ON
#define	CMP_CC_SCANCTRL		OL_CC_SCANCTRL

	/*				0x---C */
#define CMP_CC_GRIDFIT_VOID	OL_CC_GRIDFIT_VOID
#define CMP_CC_GRIDFIT_OFF	OL_CC_GRIDFIT_OFF
#define CMP_CC_GRIDFIT_ON	OL_CC_GRIDFIT_ON
#define CMP_CC_GRIDFIT		OL_CC_GRIDFIT

	/*				0x--3- */
#define	CMP_CC_FILLRULE_VOID	OL_CC_FILLRULE_VOID
#define	CMP_CC_FILLRULE_NZW	OL_CC_FILLRULE_NZW
#define	CMP_CC_FILLRULE_EO	OL_CC_FILLRULE_EO
#define	CMP_CC_FILLRULE		OL_CC_FILLRULE

	/*				0x--C- */
#define	CMP_CC_PAINT_VOID	OL_CC_PAINT_VOID
#define	CMP_CC_PAINT_FILL	OL_CC_PAINT_FILL
#define	CMP_CC_PAINT_CONTOUR	OL_CC_PAINT_CONTOUR
#define CMP_CC_PAINT_BOLD	OL_CC_PAINT_BOLD
#define	CMP_CC_PAINT		OL_CC_PAINT

	/*				0x-F-- */
#define	CMP_CC_GRAYSCALE_VOID	OL_CC_GRAYSCALE_VOID
#define	CMP_CC_GRAYSCALE_1	OL_CC_GRAYSCALE_1
#define	CMP_CC_GRAYSCALE_2	OL_CC_GRAYSCALE_2
#define	CMP_CC_GRAYSCALE_4	OL_CC_GRAYSCALE_4
#define	CMP_CC_GRAYSCALE_8	OL_CC_GRAYSCALE_8
#define	CMP_CC_GRAYSCALE	OL_CC_GRAYSCALE

	/*				0x7--- */
#define	CMP_CC_VOID		OL_CC_VOID
#define	CMP_CC_BITMAP		OL_CC_BITMAP
#define	CMP_CC_CHARPATH		OL_CC_CHARPATH
#define	CMP_CC_EDGELIST		OL_CC_EDGELIST
#define	CMP_CC_IEL		OL_CC_IEL
#define	CMP_CC_FTSEDGELIST	OL_CC_FTSEDGELIST		/* add for FontStream by hori */
#define	CMP_CC_OUTPUTFORMAT	OL_CC_OUTPUTFORMAT

/* from Globe4 */
#define CMP_DEC_PATH_AUTO               OL_DEC_PATH_AUTO
#define CMP_DEC_PATH_1                  OL_DEC_PATH_1
#define CMP_DEC_PATH_2                  OL_DEC_PATH_2

#define CMP_DEC_TYPE_VOID               OL_DEC_TYPE_VOID
#define CMP_DEC_TYPE_BOLD               OL_DEC_TYPE_BOLD
#define CMP_DEC_TYPE_ENCLOSER           OL_DEC_TYPE_ENCLOSER
#define CMP_DEC_TYPE_SHADOW             OL_DEC_TYPE_SHADOW
#define CMP_DEC_TYPE_SENCLOSER          OL_DEC_TYPE_SENCLOSER
#define CMP_DEC_TYPE_SLANT              OL_DEC_TYPE_SLANT

#define CMP_DecorationParam             OL_Decoration_Param



#else //_LINK_PROCESSER_

/*
 プロセッサヘッダファイルが無い場合
*/

/* from Globe4 */
#define CMP_MEMCPY                      memcpy
#define CMP_MEMSET                      memset

/* 変数型 */
#define	CMP_INT8		signed char		
#define CMP_INT16		signed short		
#define CMP_INT32		signed long
#define CMP_UINT8		unsigned char	
#define CMP_UINT16		unsigned short	
#define CMP_UINT32		unsigned long	

#define CMP_BYTE		unsigned char
#define CMP_CHAR		signed char
#define CMP_SHORT		signed short
#define CMP_USHORT		unsigned short
#define CMP_INT			signed int
#define CMP_UINT		unsigned int
#define CMP_LONG		signed long
#define CMP_ULONG		unsigned long

#define CMP_VOID		void		
#define CMP_REAL		double

#define CMP_STATUS		int
#define CMP_BOOL		int

#define	CMP_PIXELUNIT		CMP_INT16
#define	CMP_POINTUNIT		CMP_REAL
#define	CMP_BITMAPUNIT		CMP_UINT16	/* ビットマップのバウンダリサイズ */

/* 定数（真偽） */
#define CMP_TRUE		1
#define CMP_FALSE		0
#define CMP_NULL		0

/* 定数（コントロール） */
#define	CMP_TT_OFF		(0x00)
#define	CMP_TT_ON		(0x01)
#define	CMP_TT_START_OFF	(0x10)
#define	CMP_TT_START_ON		(0x10 | 0x01)
#define	CMP_TT_START		(0x10)
#define CMP_TT_END_OFF		(0x20)
#define CMP_TT_END_ON		(0x20 | 0x01)
#define	CMP_TT_END		(0x20)

enum CMP_SegmentType {
	CMP_PS_VOID		= 0x00,
	CMP_PS_MOVETO		= 0x11,
	CMP_PS_LINETO		= 0x21,
	CMP_PS_QSPLINETO	= 0x32,
	CMP_PS_CURVETO		= 0x43,
	CMP_PS_CLOSEPATH	= 0x50,
	CMP_PS_ENDCHAR		= 0x60,
	CMP_PS_SPECIAL		= 0xF0,
	CMP_PS_TERMINATOR	= 0xFF
};

enum CMP_ComposerControl {
	/*				0x---3 */
	CMP_CC_SCANCTRL_VOID	= 0x0000,
	CMP_CC_SCANCTRL_OFF	= 0x0001,
	CMP_CC_SCANCTRL_ON	= 0x0002,
	CMP_CC_SCANCTRL		= 0x0003,

	/*				0x---C */
	CMP_CC_GRIDFIT_VOID	= 0x0000,
	CMP_CC_GRIDFIT_OFF	= 0x0004,
	CMP_CC_GRIDFIT_ON	= 0x0008,
	CMP_CC_GRIDFIT		= 0x000C,

	/*				0x--3- */
	CMP_CC_FILLRULE_VOID	= 0x0000,
	CMP_CC_FILLRULE_NZW	= 0x0010,
	CMP_CC_FILLRULE_EO	= 0x0020,
	CMP_CC_FILLRULE		= 0x0030,

	/*				0x--C- */
	CMP_CC_PAINT_VOID	= 0x0000,
	CMP_CC_PAINT_FILL	= 0x0040,
	CMP_CC_PAINT_CONTOUR	= 0x0080,
	CMP_CC_PAINT_BOLD	= 0x00C0,
	CMP_CC_PAINT		= 0x00C0,

	/*				0x-F-- */
	CMP_CC_GRAYSCALE_VOID	= 0x0000,
	CMP_CC_GRAYSCALE_1	= 0x0100,
	CMP_CC_GRAYSCALE_2	= 0x0200,
	CMP_CC_GRAYSCALE_4	= 0x0400,
	CMP_CC_GRAYSCALE_8	= 0x0800,
	CMP_CC_GRAYSCALE	= 0x0F00,

	/*				0x7--- */
	CMP_CC_VOID		= 0x0000,
	CMP_CC_BITMAP		= 0x1000,
	CMP_CC_CHARPATH		= 0x2000,
	CMP_CC_EDGELIST		= 0x3000,
	CMP_CC_IEL		= 0x4000,
	CMP_CC_FTSEDGELIST	= 0x5000,	/* add for FontStream by hori */
	CMP_CC_OUTPUTFORMAT	= 0x7000,
};

enum CMP_Direction {
	CMP_DIR_VOID		= 0,
	CMP_DIR_E		= 1,
	CMP_DIR_N,
	CMP_DIR_W,
	CMP_DIR_S
};


/* 構造体 */
typedef struct CMP_BoundingBox {
	double	left, lower, right, upper;
} CMP_BoundingBox;

typedef struct CMP_MetricsInfo {
    CMP_Direction	dir;
    CMP_BoundingBox	bbox;
    double			descender_h, descender_v;
    double			off_x, off_y;
    double			esc_x, esc_y;

    CMP_MetricsInfo() {
	dir = CMP_DIR_VOID;
	off_x = off_y = 0.0;
	esc_x = esc_y = 0.0;
    };

    ~CMP_MetricsInfo() {};
} CMP_MetricsInfo;

typedef struct CMP_EdgeList_GS {
	unsigned short	level;
	short			start;
	short			end;
} CMP_EdgeList_GS;

typedef struct CMP_EdgeList {
	short			start, end;
} CMP_EdgeList;

typedef struct CMP_EdgeListInfo {
	unsigned long	code;
	unsigned long	id;
	CMP_MetricsInfo	metrics;

	unsigned short	height;
	unsigned short	width;
	unsigned char	pixelBits;

	unsigned short	lineAmount;
	unsigned short	edgeAmount;
	unsigned short	a_lineSize[1];
} CMP_EdgeListInfo;

typedef struct CMP_BitmapInfo {
	unsigned long	code;
	unsigned long	id;
	CMP_MetricsInfo	metrics;

	unsigned short	height;
	unsigned short	width;
	unsigned short	widthBytes;
	unsigned char	planes;
	unsigned char	pixelBits;
	unsigned char	a_bitmap[1];
} CMP_BitmapInfo;

/* from Globe4 */

#define CMP_DEC_PATH_AUTO               0
#define CMP_DEC_PATH_1                  1
#define CMP_DEC_PATH_2                  2

#define CMP_DEC_TYPE_VOID               0x00
#define CMP_DEC_TYPE_BOLD               0x01
#define CMP_DEC_TYPE_ENCLOSER           0x02
#define CMP_DEC_TYPE_SHADOW             0x04
#define CMP_DEC_TYPE_SENCLOSER          0x08
#define CMP_DEC_TYPE_SLANT              0x10

typedef struct CMP_DecorationParam_t
{
  CMP_DEC_TYPE                          type;
  CMP_DEC_PATH                          path;
  CMP_INT                               angle;
  CMP_UINT32                            bold_x;
  CMP_UINT32                            bold_y;
  CMP_UINT32                            enclose_x;
  CMP_UINT32                            enclose_y;
  CMP_INT32                             shadow_x;
  CMP_INT32                             shadow_y;
  CMP_INT32                             slant_x;
  CMP_INT32                             slant_y;
} CMP_DecorationParam;  


#endif //_LINK_PROCESSER_


#define	CMP_TT_POINTFLAG	(0x0f)
#define	CMP_TT_BOUNDFLAG	(0xf0)

typedef struct CMP_Point {
    CMP_POINTUNIT	x;
    CMP_POINTUNIT	y;
} CMP_Point;

typedef struct CMP_Pixel {
	CMP_PIXELUNIT	x;
	CMP_PIXELUNIT	y;
} CMP_Pixel;

#endif //_OL_COMPOSER_H_INCLUDED_

