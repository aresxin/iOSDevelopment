/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_cml_prd_Llib.h	TRC補正モジュールヘッダファイル
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Modified:	Jul,1,2001	Toshio Yamazaki
 *
 * IMARI PRDモジュールの以下のファイルをHostBased用に移植しました．
 * 主に，NameにCST_COML_を付加する修正を行っています．
 */
/********************************************************************************
*	名称：	cml_prd_Llib.h
*	内容：	PRDRV Function Heder	
*
*	作成：	'00.04.26
*	作成者：奥津優
*	修正:
*
********************************************************************************/

/* 共通定数定義 */
#define	CST_COML_PRD_DATA_COUNT256	256
#define CST_COML_PRD_NOERROR	0
#define CST_COML_PRD_ERROR	-1

/* RCT関連定義 */
#define	CST_COML_LOW_STEP	2	/* 低濃度ステップ幅	*/
#define	CST_COML_MID_STEP	3	/* 中濃度ステップ幅	*/
#define	CST_COML_HIGH_STEP	4	/* 高濃度ステップ幅	*/
#define	CST_COML_K_1		10	/* 係数1		*/
#define	CST_COML_K_2		0	/* 係数2		*/
#define	CST_COML_K_3		10	/* 係数3		*/

/* XJCL関連定義 */
#define IOTC_TRCM_TONER_SAVE 0.70F	/* トナーセーブ値	*/
#define IOTC_TRCM_PALE_BLACK 0.35F	/* 薄墨印刷の値		*/
#define IOTC_TRCM_X0	   0		/* 低濃度		*/
#define IOTC_TRCM_X1	  85		/* 中濃度		*/
#define	IOTC_TRCM_X2	 170		/* 高濃度1		*/
#define IOTC_TRCM_X3	 255		/* 高濃度2		*/
#define	IOTC_TRCM_STEP0	   4		/* 低濃度ステップ巾	*/
#define	IOTC_TRCM_STEP1	   4		/* 中濃度ステップ巾	*/
#define	IOTC_TRCM_STEP2	   4		/* 高濃度1ステップ巾	*/
#define	IOTC_TRCM_STEP3	   2		/* 高濃度2ステップ巾	*/

/* 関数プロトタイプ宣言 */
extern char CST_COML_Prd_CB_mklutKYMCG( char *, char *, char*, char*, unsigned char * );
extern char CST_COML_Prd_Calib_mklutKYMCG( char *, char *, char*, char*, unsigned char * );
extern char CST_COML_Prd_Adc_Auto_mklutKYMCG( unsigned char *, unsigned char *, 
				     unsigned char *, unsigned char *, unsigned char * );
extern char CST_COML_Prd_TrcPale_mklut( unsigned char *, unsigned char *, float ,int );
extern char CST_COML_Prd_LutLut( unsigned char *, unsigned char *, unsigned char * ,int );
extern float CST_COML_Prd_PaleRate_calc( unsigned char, unsigned char );
