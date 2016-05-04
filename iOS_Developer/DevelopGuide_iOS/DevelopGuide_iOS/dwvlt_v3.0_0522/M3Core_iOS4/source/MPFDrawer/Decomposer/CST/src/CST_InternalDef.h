/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_InternalDef.h	CST関連ヘッダファイル(CSTモジュール内部で使用する定義)
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Created:	Jun,19,2001	Toshio Yamazaki
 *
 * <<参考>>
 * Limoges Win95 Driver cil_cmn.h
 *	ACCT周りのデータ構造は上記コードより移植
 */

#ifndef CST_INTERNALDEF_H_INCLUDED
#define CST_INTERNALDEF_H_INCLUDED

#include <stdio.h>	/* NULLの定義用 */
#include "CST_IF.h"

/*----------------------------------*/
/* CST型の定義						*/
/*----------------------------------*/
/* trcはcst_parameterに、DLUTはCST直下につくなど、CST_Parameterを内部構造体として */
/* 使用していた名残で整合性のない状況になっているが、互換を重んじてそのままとする */

typedef struct CST_workT {
	/* CSTコンポーネントは，Heap Memoryを使用しない．				*/
	/* 以下の領域を用いる．							*/
	unsigned char	work[1024*4];
} CST_work;

typedef struct CST_objT {
	void *DLUT[3];			/* Graphic/Text/Photoに使用するDLUT	 */

	void *sif_mi;
	void *sif;

	void *self;
} CST_obj;

typedef struct CSTT
{
	/* 以下，属性部分をクライアントは指定する． */
	unsigned long	status;		/* 色パス全体の指定			*/

	/* 色補正パス指定．font/graphics/imageの3つ分				*/
	unsigned long	crstatus[3];

	/* 色補正パラメータ属性指定．font/graphics/imageの3つ分			*/
	CST_RGBcrParaStatus	rgbstatus[3];	/* RGB色補正属性指定			*/
	CST_LCCcrParaStatus	lccstatus[3];	/* LCC色補正属性指定			*/

	/* 色変換パスの指定								*/
	unsigned short	in_space;	/* 入力色空間．予約パラメータ		*/
	unsigned short	out_space;	/* 出力色空間．予約パラメータ		*/

	/* 色変換パス指定．font/graphics/imageの3つ分				*/
	unsigned long	cststatus[3];

	/* TRC補正パラメータ属性							*/
	/* TRC総量制限パラ．4コンポーネント×font/graphics/image．			*/
	unsigned char	trclimit[4*3];
	/* TRC部分補正パラ．4コンポーネント×部分領域数4×font/graphics/image．	*/
	signed char		trcpara[CST_PARA_TRCCOLORBALANCE_SIZE*3];

	/* 以下，パラ実体に，CSTコンポーネントは実パラを生成する			*/
	/* 特に断らなければ，font/graphics/imageの3つ分必ず存在する．		*/

	CST_RGBcrParaData	rgbparadata[3];	/* RGB色補正パラ実体			*/
	CST_LCCcrParaData	lccparadata[3];	/* LCC色補正パラ実体			*/

	CST_Matrix3x1	bwmat[3];	/* B/W変換パラ実体			*/

	/* ICC Profileのパラ計算用にmalloc使うから追加				*/
	void		*context;
	/* ICC Profile変換用パラメータの実体．					*/
	char		iccpara_textgraphics_profname[512];	/* ICC Profileのファイルネーム,絶対Path	*/
	char		iccpara_image_profname[512];		/* ICC Profileのファイルネーム,絶対Path	*/
	CST_ICCProfileData	*iccpara_textgraphics;	/* ICCパラ実体 Text Graphics用	*/
	CST_ICCProfileData	*iccpara_image;		/* ICCパラ実体 Image用		*/

	/* 色変換パラメータの実体							*/
	/* TRC 実体									*/
	/* 1D-LUT = 256 byte×5コンポーネント×font/graphics/imageで，3840 byte	*/
	unsigned char	trc[CST_PARA_TRC_SIZE*3];

	/* 3D-LUT 実体は無し．static constでハードコーディングされたデータを，	*/
	/* cststatusで指定されたd-lut番号で参照して色変換を行う．			*/

/* ここはトリッキー。オブジェクト化前のSIFはCST_Parameter分しかメモリを確保してくれないので、 */
/* オブジェクトはCST_Parameterよりも小さいサイズにしておく。workを使う場合はobjをバックアップ */
/* してから使うようにする																	  */

	union {
		CST_work	work;
		CST_obj		obj;
	};
} CST;

/* その他のマクロ				*/
/* 型変換マクロ					*/
#define CST_PROC_InttoFix16(i)	((i) << 8)	/*整数→16bit固定小数点変換*/
#define CST_PROC_InttoFix32(i)	((i) << 16)	/*整数→32bit固定小数点変換*/
#define CST_PROC_Fix16toInt(x)	((x) >> 8)	/*16bit固定小数点→整数変換*/
#define CST_PROC_Fix32toInt(x)	((x) >> 16)	/*32bit固定小数点→整数変換*/

#define CST_PROC_FloattoFix16(x)	((CST_Fixed16)((float)(x) * 256.0f))	/*浮動小数点→16bit固定小数点変換*/
#define CST_PROC_FloattoFix32(x)	((CST_Fixed32)((float)(x) * 65536.0f))	/*浮動小数点→326bit固定小数点変換*/
#define CST_PROC_Fix16toFloat(x)	((float)(x) / 256.0f)			/*16bit固定小数点→浮動小数点変換*/
#define CST_PROC_Fix32toFloat(x)	((float)(x) / 65536.0f)			/*32bit固定小数点→浮動小数点変換*/

#define CST_PROC_Fix16toFix32(x)	((x) << 8)				/*16bit固定小数点→32bit固定小数点変換*/
#define CST_PROC_Fix32toFix16(x)	((x) >> 8)				/*32bit固定小数点→16bit固定小数点変換*/

/* vをa以上b以下の値にクリッピングする		*/
#define CST_PROC_MINMAX(v,a,b)	( ( (v) <= (a) ) ? (a) : ( ( (v) >= (b) ) ? (b) : (v) ) )

/* 共通関数 */
float CST_Proc_Det33( float mat[3][3] );
float CST_Proc_Yoinshi33( float mat[3][3], short j, short k );
short CST_Proc_Inv33( float out[3][3], float in[3][3] );
void CST_Proc_MulMat33( float out[3][3], const float in1[3][3], float in2[3][3] );
void CST_Proc_MulCoeMat33( float coe[3], float mat[3][3] );
#endif /* CST_INTERNALDEF_H_INCLUDED */
