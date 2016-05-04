/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: SIF_Interface.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_SIF_Interface_h
#define INC_SIF_Interface_h

#include "HB_Decomposer.h"
#include "COM_Windows.h"
#include "COM_DeviceColorSpace.h"

/*
 * 初期化と終了
 */
void* SIF_Initialize(
	void	*sifmi,			/* SIF用メモリインタフェースハンドル	*/
	void	*jobParam,		/* HB_JobParam					*/
	void	*spoolParam,	/* HB_SpoolParam				*/
	void	*outputParam,	/* 出力仕様						*/
	void	*cstParam,		/* CST_Parameter				*/
	void	*debugInfo,		/* HB_DebugInfo					*/
	void	*extraParam );	/* ユーザ拡張データ				*/

void* SIF_GetEdgeSinkHandle(
	void *sif );			/* SIFのハンドル				*/

void* SIF_GetCSTParameter(
	void *sif );			/* SIFのハンドル				*/


int SIF_SetImagerHandle(
	void	*sifmi,			/* SIF用メモリインタフェースハンドル	*/
    void	*imager );		/* Imagerのハンドル	*/


int SIF_Finalize(
	void *sif);				/* SIFのハンドル */


int SIF_GetMemSize(
	void	*jobParam );


/*
 * ジョブ制御
 */
int SIF_StartJob(
	void *sif,			/* SIFのハンドル */
	WORD patternMode);		/* パターンデータの変換パラメータ */

int SIF_EndJob(
	void *sif);			/* SIFのハンドル */

int SIF_StartPage(
	void *sif,			/* SIFのハンドル */
	void *pageParam,	/* ページパラメータ HB_PageParam参照 */
	void *splParam,		/* HB_SpoolParam */
	void *extraParam);	/* 適用先固有のパラメータ HB_ViewBufferParam等 */

int SIF_EndPage(
	void *sif,			/* SIFのハンドル */
	void *extraParam);	/* 適用先固有のパラメータ */

/*
 * デバイス管理
 */
int SIF_ShowPage(
	void *sif);			/* SIFのハンドル */

/*
 * 描画属性設定
 */
int SIF_SetAxis(
	void *sif,				/* Decomposerのハンドル */
	float a, float b,		/* 変換行列のa,b成分 */
	float c, float d,		/* 変換行列のc,d成分 */
	float tx, float ty);	/* 変換行列のtx,ty成分 */

/* 2004.4.8 FXPS Color / Monoページ切り替え対応 */
int	SIF_SetColorParameter(
	void* imager,			/* Decomposerのハンドル */
	void* colorParameter);	/* 色変換パラメータ */

/*
 * Job制御情報設定
 */
int SIF_SendJobHeader(
	void *sif,				/* SIFのハンドル */
	void *jobHeader);		/* ESS ジョブヘッダ情報。ESS_Parameter_JOBHEADER参照 */

int SIF_SendJobTrailer(
	void *sif,				/* SIFのハンドル */
	void *jobTrailer);		/* ESS ジョブトレイラ-情報 ESS_Parameter_JOBTRAILER参照 */

#endif /* INC_SIF_Interface_h */

/*
 * Log
 * 14.Jul.2003 Yozo Kashima Created
 * 23.Sep.2003 Yozo Kashima SIF_StartPageにextraParam引数を追加。
 */

/* end of SIF_Interface.h */
