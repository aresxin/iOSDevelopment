/*
 * Copyright (C) 2001 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_Edge.h -- Edge型の定義
 * (元RND_Edge.h)
 *
 * Created : 2003.07.15 Masao.Morita(DPSC SWD PFCoreG)
 *
 */

#if !defined(COM_EDGE_H_INCLUDED)
#define COM_EDGE_H_INCLUDED

#include "COM_ObjectTag.h"


/*----------------------------------*/
/*	ユーティリティ					*/
/*----------------------------------*/
#define COM_EDGE_COLORFIELD		0x00000080
#define COM_EDGE_SAMEUPPER		0x00000040
#if (COM_OBJECTTAG_BITS == 2)
#define COM_EDGE_TAGAREA		0x00000003
#elif (COM_OBJECTTAG_BITS == 4)
#define COM_EDGE_TAGAREA		0x0000000f
#endif

#define COM_EDGE_EDGETYPE(t)	(COM_EDGE_TAGAREA & (t))
#define COM_EDGE_PIXELTYPE(t)	(COM_EDGE_COLORFIELD | (COM_EDGE_TAGAREA & (t)))

#define	COM_EDGE_ISEDGE(t)		!(t & COM_EDGE_COLORFIELD)
#define COM_EDGE_ISPIXEL(t)		(t & COM_EDGE_COLORFIELD)
#define COM_EDGE_GETTAG(t)		(t & COM_EDGE_TAGAREA)

#define COM_EDGE_ISSAMEUPPER(t)	(t & COM_EDGE_SAMEUPPER)


/*----------------------------------*/
/*	Edge型の定義					*/
/*----------------------------------*/
typedef struct COM_EdgeT
{
	unsigned long		type;			/* データ形式とタグ値		*/
	short				sx;				/* 開始x座標				*/
	short				ex;				/* 終了x座標				*/
	union {
		unsigned char	comp[4];		/* このエッジの色(要素毎)	*/
		unsigned long	pixel;			/* このエッジの色(画素)		*/
		unsigned char	*ptr;			/* このエッジの画素列		*/
	} color;
} COM_Edge;

#endif
