/*
 * Copyright (C) 2003 by Fuji Xerox Co.,Ltd. All rights reserved.
 *
 * COM_ES_CodecParameter.h -- 圧縮パラメータの定義
 *
 * Created : 2003.11.06 Masao.Morita(DPSC SWD PFCoreG)
 *
 */

#if !defined(COM_CODECPARAMETER_H_INCLUDED)
#define COM_CODECPARAMETER_H_INCLUDED

#define COM_CODEC_MAXSTEP		8

/*----------------------------------*/
/*	圧縮パラメータ型の定義			*/
/*----------------------------------*/
typedef struct COM_CodecParamSetT {
	int		sq21Resolution;		/* SQ21圧縮パラメータ	*/
	int		zPos;				/* Z予測器位置			*/
	int		edgePredStat;		/* 予測器の設定(Edge部)	*/
	int		pixPredStat;		/* 予測期の設定(Pixel部)*/
	int		rd21SelMode;		/* RD21画素選択モード	*/
	int		rd21BlockSize;		/* RD21ブロックサイズ	*/

} COM_CodecParamSet;

typedef struct COM_CodecParamT
{
	float					lineRatio;		/* ライン圧縮率	白黒	*/
	float					pageRatio;		/* ページ圧縮率	白黒	*/
	int						items;			/* 有効なパラメータ数	*/
	COM_CodecParamSet		parameter[COM_CODEC_MAXSTEP];	/* 有効なパラメータ列	*/
} COM_CodecParam;


/*----------------------------------*/
/* 圧縮パラメータの取得				*/
/*----------------------------------*/
extern	COM_CodecParam *
SIF_GetCodecParameter( void *userdata, int codecid, int isPageBw, int paramkey );


#endif
