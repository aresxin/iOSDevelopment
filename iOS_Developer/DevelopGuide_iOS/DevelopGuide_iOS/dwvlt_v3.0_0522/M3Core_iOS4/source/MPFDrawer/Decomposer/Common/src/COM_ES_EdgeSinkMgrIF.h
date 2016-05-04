/*
 * Copyright (C) 2003 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_ES_EdgeSinkMgrIF.h -- EdgeSinkMgrの外部I/F
 *
 * Created : 2003.09.22 Masao.Morita(DPSC/SDM/PFCoreG)
 *
 */

#if !defined(COM_ES_EDGESINKMGRIF_H_INCLUDED)
#define COM_ES_EDGESINKMGRIF_H_INCLUDED

#include "COM_ES_Spec.h"


/*----------------------------------*/
/*----------------------------------*/
typedef int (*ES_TrueSpoolWrite)(int, void *, long, long *);


/*----------------------------------*/
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
	ES_TrueSpoolWrite		splfunc,	/* 最終書き出し関数Ptr			*/
	void					*mmgr );	/* メモリインタフェース			*/

extern	void *
ES_EdgeSinkMgr_GetDistributor( void *esmgr );

extern	int
ES_EdgeSinkMgr_Terminate( void *esmgr );


/*----------------------------------*/
/*----------------------------------*/
extern int
ES_EdgeSinkMgr_StartJob(
	void *,						/* ES_EdgeSinkMgrインスタンス		*/
	void *,						/* Jobスコープ出力先情報			*/
	void * );					/* 制御情報							*/

extern int
ES_EdgeSinkMgr_EndJob(
	void *,						/* ES_EdgeSinkMgrインスタンス		*/
	void * );					/* 制御情報							*/

extern int
ES_EdgeSinkMgr_CtrlStartPage(
	void *,						/* ES_EdgeSinkMgrインスタンス		*/
	int  isPageBw,				/* 出力ページがBW:1,Color:0			*/
	void * );					/* 制御情報							*/

extern int
ES_EdgeSinkMgr_CtrlEndPage(
	void *,						/* ES_EdgeSinkMgrインスタンス		*/
	void * );					/* 制御情報							*/


#endif
