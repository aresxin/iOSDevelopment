/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_TypesExt.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */



#ifndef _OL_TYPES_EXT_H_INCLUDED_
#define _OL_TYPES_EXT_H_INCLUDED_

#include "OL_Config.h"
#include "OL_Types.h"

#define OL_SHIFT_WEIGHT     4

enum OL_Weight {
  OL_WEIGHT_DONTCARE          = 0x00,
  OL_WEIGHT_THIN              = 0x10,
  OL_WEIGHT_EXTRALIGHT        = 0x20,
  OL_WEIGHT_LIGHT             = 0x30,
  OL_WEIGHT_NORMAL            = 0x40,
  OL_WEIGHT_MEDIUM            = 0x50,
  OL_WEIGHT_DEMIBOLD          = 0x60,
  OL_WEIGHT_BOLD              = 0x70,
  OL_WEIGHT_EXTRABOLD         = 0x80,
  OL_WEIGHT_ULTRABOLD         = 0x90,

  OL_WEIGHT_0                 = 0x00,
  OL_WEIGHT_1                 = 0x10,
  OL_WEIGHT_2                 = 0x20,
  OL_WEIGHT_3                 = 0x30,
  OL_WEIGHT_4                 = 0x40,
  OL_WEIGHT_5                 = 0x50,
  OL_WEIGHT_6                 = 0x60,
  OL_WEIGHT_7                 = 0x70,
  OL_WEIGHT_8                 = 0x80,
  OL_WEIGHT_9                 = 0x90,
  OL_WEIGHT_10                = 0xA0,
  OL_WEIGHT_11                = 0xB0,
  OL_WEIGHT_12                = 0xC0,
  OL_WEIGHT_13                = 0xD0,
  OL_WEIGHT_14                = 0xE0,
  OL_WEIGHT_15                = 0xF0
};

enum OL_DataType {
  OL_DT_VOID          = 0x0,
  OL_DT_REFERENCE     = 0x1,
  OL_DT_RAW           = 0x2
};

/*
 bit 7-5 : segment type
 bit 4-0 : num of points
*/
typedef enum OL_SegmentType_t {
    ST_VOID             = 0x00,
    ST_MOVETO           = 0x11,
    ST_LINETO           = 0x21,
    ST_QSPLINETO        = 0x32,
    ST_CURVETO          = 0x43,
    ST_CLOSEPATH        = 0x50,
    ST_ENDCHAR          = 0x60,
    ST_SPECIAL          = 0xF0,
    ST_TERMINATOR       = 0xFF
} OL_SegmentType;

typedef enum OL_Direction_t {
    OL_DIR_VOID		= 0x0,
    OL_DIR_E		= 0x1,
    OL_DIR_N            = 0x2,
    OL_DIR_W            = 0x3,
    OL_DIR_S            = 0x4,
    OL_DIR_MASK		= 0x7,
    OL_DIR_FULLVERT	= 0x8
} OL_Direction;


typedef enum OL_ComposerControl {
    /*                    0x---3 */
    OL_CC_SCANCTRL_VOID	= 0x0000,
    OL_CC_SCANCTRL_OFF	= 0x0001,
    OL_CC_SCANCTRL_ON	= 0x0002,
    OL_CC_SCANCTRL	= 0x0003,

    /*			  0x---C */
    OL_CC_GRIDFIT_VOID	= 0x0000,
    OL_CC_GRIDFIT_OFF	= 0x0004,
    OL_CC_GRIDFIT_ON	= 0x0008,
    OL_CC_GRIDFIT	= 0x000C,

    /*                    0x--3- */
    OL_CC_FILLRULE_VOID	= 0x0000,
    OL_CC_FILLRULE_NZW	= 0x0010,
    OL_CC_FILLRULE_EO	= 0x0020,
    OL_CC_FILLRULE	= 0x0030,

    /*			  0x--C- */
    OL_CC_PAINT_VOID	= 0x0000,
    OL_CC_PAINT_FILL	= 0x0040,
    OL_CC_PAINT_CONTOUR	= 0x0080,
    OL_CC_PAINT_BOLD	= 0x00C0,
    OL_CC_PAINT		= 0x00C0,

    /*			  0x-F-- */
    OL_CC_GRAYSCALE_VOID= 0x0000,
    OL_CC_GRAYSCALE_1	= 0x0100,
    OL_CC_GRAYSCALE_2	= 0x0200,
    OL_CC_GRAYSCALE_4	= 0x0400,
    OL_CC_GRAYSCALE_8	= 0x0800,
    OL_CC_GRAYSCALE	= 0x0F00,

    /*			  0x7--- */
    OL_CC_VOID		= 0x0000,
    OL_CC_BITMAP	= 0x1000,
    OL_CC_CHARPATH	= 0x2000,
    OL_CC_EDGELIST	= 0x3000,
    OL_CC_IEL		= 0x4000,
    OL_CC_FTSEDGELIST	= 0x5000,	/* added for FontStream by hori */
    OL_CC_CHARPATH_FIXED= 0x6000,	/* added for FontStream by hori */
    OL_CC_OUTPUTFORMAT	= 0x7000,

    /*			0x8--- */
    OL_CC_SUPPRESSHINT	= 0x8000,
    OL_CC_SUPPRESSHINT_OFF= 0x0000,
    OL_CC_SUPPRESSHINT_ON= 0x8000
}OL_ComposerControl;


#define OL_PatternType	OL_ComposerControl

typedef struct OL_BoundingBox_t {
    double      left, lower, right, upper;
} OL_BoundingBox;


typedef struct OL_MetricsInfo_t {
    OL_Direction      dir;
    OL_BoundingBox    bbox;
    double              descender_h, descender_v;
    double              off_x, off_y;
    double              esc_x, esc_y;
} OL_MetricsInfo;



typedef struct OL_PatternInfo_t {
    unsigned long		code;
    unsigned long		id;
    OL_ComposerControl	type;
    OL_MetricsInfo		metrics;
    unsigned short		size_x, size_y;
    unsigned short		data_type;
    unsigned long		data_size;		/* MY 1998.06.02 */
    void			*data;
} OL_PatternInfo;


/*
 *  |  a   b   0 |
 *  |  d   e   0 |
 *  |  g   h   1 |
 */

typedef struct OL_matrix32_t {
    double a, b;
    double d, e;
    double g, h;
} OL_MATRIX32;



/*

 pattern

*/
    
typedef struct OL_EdgeList_GS_t {
    unsigned short	level;
    short		start;
    short		end;
} OL_EdgeList_GS;


typedef struct OL_EdgeList_t {
    short	start, end;
} OL_EdgeList;


typedef struct OL_EdgeListInfo_t {
    unsigned long	code;
    unsigned long	id;
    OL_MetricsInfo	metrics;

    unsigned short	height;
    unsigned short	width;
    unsigned char	pixelBits;

    unsigned short	lineAmount;
    unsigned short	edgeAmount;
    unsigned short	a_lineSize[1];
} OL_EdgeListInfo;


typedef struct OL_BitmapInfo_t {
    unsigned long	code;
    unsigned long	id;
    OL_MetricsInfo	metrics;

    unsigned short	height;
    unsigned short	width;
    unsigned short	widthBytes;
    unsigned char	planes;
    unsigned char	pixelBits;
    unsigned char	a_bitmap[1];
} OL_BitmapInfo;


typedef struct { float x, y; } OL_cp_point;
typedef OL_cp_point OL_CP_Point;

typedef struct OL_CharPathInfo_t {
    unsigned long	code;
    unsigned long	id;
    OL_MetricsInfo	metrics;

    unsigned short	num_of_segment;
    unsigned short	num_of_point;
    unsigned char	*segment_ptr;
    OL_cp_point		*point_ptr;
    unsigned char	segment[1];
} OL_CharPathInfo;


typedef struct OL_Bitmap_t {
    unsigned short	height;		// in pixel
    unsigned short	width;		// in pixel
    unsigned char	byte_width;	// in byte
    unsigned char	depth;
    unsigned char	*data;
} OL_Bitmap;


typedef struct OL_Outline_t {
    unsigned short	nSegment;
    unsigned short	nSegmentPoint;
    unsigned char	*segmentPtr;
    OL_cp_point		*segmentPointPtr;
} OL_Outline;


/* decorator */

#define OL_DEC_PATH_AUTO                      0
#define OL_DEC_PATH_1                         1
#define OL_DEC_PATH_2                         2

#define OL_DEC_TYPE_VOID                      0x00
#define OL_DEC_TYPE_BOLD                      0x01
#define OL_DEC_TYPE_ENCLOSER                  0x02
#define OL_DEC_TYPE_SHADOW                    0x04
#define OL_DEC_TYPE_SENCLOSER                 0x08
#define OL_DEC_TYPE_SLANT                     0x10
#define OL_DEC_TYPE_PSEUDO                    0x80

typedef struct OL_Decoration_Param_t
{
  OL_DEC_TYPE                           type;
  OL_DEC_PATH                           path;
  OL_INT                                angle;
  OL_UINT32                             bold_x;
  OL_UINT32                             bold_y;
  OL_UINT32                             enclose_x;
  OL_UINT32                             enclose_y;
  OL_INT32                              shadow_x;
  OL_INT32                              shadow_y;
  OL_INT32                              slant_x;
  OL_INT32                              slant_y;
} OL_Decoration_Param;  



#endif //_OL_TYPES_EXT_H_INCLUDED_


/*
 * log:
 *
 */
