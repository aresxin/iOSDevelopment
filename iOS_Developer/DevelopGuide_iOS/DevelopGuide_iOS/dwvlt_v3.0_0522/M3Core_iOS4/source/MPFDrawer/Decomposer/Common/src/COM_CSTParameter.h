/*
 * Copyright (C) 2004 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_CSTParameter.h -- CSTパラメータの定義
 *
 * Created : 2004.04.09 Hisashi.Ichioka(FXPS)
 *
 */

#if !defined(COM_CSTPARAMETER_H_INCLUDED)
#define COM_CSTPARAMETER_H_INCLUDED

#include "CST_IF.h"

/*----------------------------------*/
/*	DLUT型の定義					*/
/*----------------------------------*/
typedef struct CST_ParaData3DLUTT {
    unsigned char	prelut[3][256];
    unsigned long	dlut[17][17][17];
} CST_ParaData3DLUT;


/*----------------------------------*/
/*	TRC取得モードの定義				*/
/*----------------------------------*/
typedef enum COM_TRC_ModeT {
	COM_TRC_MODE_COLOR = 0,					/* ColorのTRCを取得 */
	COM_TRC_MODE_GRAY						/* MonochromeのTRCを取得 */
} COM_TRC_Mode;

/*--------------------------------------------------*/
/*	プロコン側から取得するであろうデータ構造の定義	*/
/*	SetDefaultCSTParameterで使用					*/
/*--------------------------------------------------*/
typedef struct {
    unsigned char colorBalanceY[2][33];
    unsigned char colorBalanceM[2][33];
    unsigned char colorBalanceC[2][33];
    unsigned char colorBalanceK[2][33];
} PfRscSysAdcLut;

typedef struct {
    unsigned char colorBalanceY[2][3];
    unsigned char colorBalanceM[2][3];
    unsigned char colorBalanceC[2][3];
    unsigned char colorBalanceK[2][3];
} PfRscSysManualLut;

/*----------------------------------*/
/* TRCパラメータの取得				*/
/*----------------------------------*/
extern	const unsigned char *
SIF_GetTRCParameter( void *sif, int trc_number, COM_TRC_Mode mode );

/*----------------------------------*/
/* DLUTパラメータの取得				*/
/*----------------------------------*/
extern	const CST_ParaData3DLUT *
SIF_GetDLUTParameter( void *sif, int dlut_number );

/*----------------------------------*/
/* CSTパラメータの初期化			*/
/*----------------------------------*/
extern void
SIF_SetDefaultCSTParameter( CST_Parameter *p );

void SIF_GetDefaultRGBcrParaStatus( CST_RGBcrParaStatus * );
void SIF_GetDefaultLCCcrParaStatus( CST_LCCcrParaStatus * );
int SIF_GetDeviceConfigTRC( PfRscSysAdcLut *, PfRscSysManualLut * );

#endif
