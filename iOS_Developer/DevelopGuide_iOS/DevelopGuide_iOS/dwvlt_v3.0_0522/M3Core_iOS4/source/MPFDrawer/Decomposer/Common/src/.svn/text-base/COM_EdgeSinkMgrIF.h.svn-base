/*
 * Copyright (C) 2003 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_EdgeSinkMgrIF.h -- EdgeSinkMgrの外部I/F定義
 *
 * Created : 2003.09.22 Masao.Morita(DPSC/SDM/PFCoreG)
 *
 */

#if !defined(COM_EDGESINKMGRIF_H_INCLUDED)
#define COM_EDGESINKMGRIF_H_INCLUDED

#include "COM_DeviceColorSpace.h"
#include "COM_ES_Spec.h"


/*----------------------------------*/
/*	外部インタフェース定義			*/
/*----------------------------------*/
/* for SIF							*/
/*----------------------------------*/
extern void *
ES_EdgeSinkMgr_Initialize(
	int	maxwidth,						/* 出力用紙の最大幅(ピクセル数)	*/
	int	maxheight,						/* 出力用紙の最大長(ピクセル数)	*/
	int	maxcomponent,					/* 最大の色数(CMYKの場合4)		*/
	int	resoX,							/* 主走査方向の解像度			*/
	int	resoY,							/* 副走査方向の解像度			*/
	ES_Spec					*fo,		/* 最終出力のEdgeSink仕様		*/
	ES_Spec					*fb,		/* FallbackのEdgeSink仕様		*/
	void					*splParam,	/* HB_SpoolParam				*/
	void					*mmgr );	/* メモリインタフェース			*/

extern void *
ES_EdgeSinkMgr_GetDistributor(
	void *esmgr );

extern int
ES_EdgeSinkMgr_Terminate(
	void *esmgr );

#endif
