/*
 * Copyright (C) 2003 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_ES_DistributorIF.h -- ES_Distributorの外部I/F定義
 *
 * Created : 2003.07.16 Masao.Morita(DPSC SWD PFCoreG)
 *
 */

#if !defined(COM_ES_DISTRIBUTORIF_H_INCLUDED)
#define COM_ES_DISTRIBUTORIF_H_INCLUDED

#include "COM_DeviceColorSpace.h"
#include "COM_Edge.h"
#include "COM_EdgeLine.h"
#include "COM_OutputLocation.h"

/*----------------------------------*/
/* EdgeSinkSetTarget型の定義		*/
/*----------------------------------*/
typedef enum ES_DistributorTargetT
{
	ES_DISTRIBUTOR_FINALOUT =	0,	/* 最終出力処理の実行	*/
	ES_DISTRIBUTOR_FALLBACK			/* FallBack処理の実行	*/

} ES_DistributorTarget;


/*----------------------------------*/
/*	外部インタフェース定義			*/
/* for Renderer						*/
/*----------------------------------*/
extern int
ES_Distributor_DrawStartPage(
	void *,						/* ES_Distributorインスタンス		*/
	ES_DistributorTarget,		/* target							*/
	unsigned char *,			/* workbuf							*/
	long,						/* workbuf size						*/
	long,						/* width							*/
	long,						/* height							*/
	COM_DeviceColorSpace *,		/* Renderer出力の仕様				*/
	COM_OutputLocation *,		/* prerendered						*/
	COM_OutputLocation *,		/* output							*/
	void * );					/* reserved							*/

extern int
ES_Distributor_DrawEndPage(
	void * );					/* ES_Distributorインスタンス		*/

extern COM_EdgeLine *
ES_Distributor_GetBuffer(
	void * );					/* ES_Distributorインスタンス		*/

extern int
ES_Distributor_PutLine(
	void * );					/* ES_Distributorインスタンス		*/


#endif
