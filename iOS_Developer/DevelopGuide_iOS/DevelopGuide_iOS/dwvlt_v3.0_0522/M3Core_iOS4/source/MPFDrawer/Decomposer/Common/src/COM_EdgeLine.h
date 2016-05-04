/*
 * Copyright (C) 2001 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_EdgeLine.h -- EdgeLine型の定義
 * (元RND_EdgeLine.h)
 *
 * Created : 2003.07.16 Masao.Morita(DPS SWD PFCoreG)
 *
 */

#if !defined(COM_EDGELINE_H_INCLUDED)
#define COM_EDGELINE_H_INCLUDED

typedef struct COM_EdgeT * COM_EdgePtr;


/*----------------------------------*/
/*	COM_EdgeLineModeeの定義			*/
/*----------------------------------*/
typedef enum COM_EdgeLineModeT
{
	COM_EDGELINE_EDGEONLY =	0,			/* Edgeだけで構成される			*/
	COM_EDGELINE_PIXELONLY,				/* 画素列だけで構成される		*/
	COM_EDGELINE_COMPOSITE				/* Edgeと画素列により構成される	*/
} COM_EdgeLineMode;

/*----------------------------------*/
/*	EdgeLineの定義					*/
/*----------------------------------*/
typedef struct COM_EdgeLineT
{
	COM_EdgePtr			edge;
	unsigned char		*pixel;
	int					edgecount;
	COM_EdgeLineMode	mode;
} COM_EdgeLine;

#endif

