/*
 * Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
 *
 * CST_IF.h	CST関連ヘッダファイル
 * Fuji Xerox Co., Ltd. DPC CS&S STD T11G 山崎寿夫
 *
 * Created:	Apr,2,2001	Toshio Yamazaki
 * 21 June, 2004 H.Ichioka CST構造体の導入
 *
 * <<参考>>
 * Limoges Win95 Driver cil_cmn.h
 *	ACCT周りのデータ構造は上記コードより移植
 */

#ifndef CST_IF_H_INCLUDED
#define CST_IF_H_INCLUDED

/*#include "IMG_Context.h"*/

/* 強制的にプロダクト用パラメータを有効にするスイッチ	*/
/* つまり，ドライバからのパラメータ指定を無視する	*/
/*#define CST_FORCESET_PARAMETER*/

/* プロダクト用パラメータを指定する			*/
/* 今の所指定できるのは，				*/
/* ・Lmoges or IMARI					*/
/* ・Bk TRC ON or OFF					*/
/* ここから						*/
/* 手抜きしてるからどちらかは必ず有効にしておくこと！！	*/
#define CST_BWOUTPUT_BKTRC_ON		/* 白黒出力の時にBkにTRCをかける		*/
/*#define CST_BWOUTPUT_BKTRC_OFF*/	/* 白黒出力の時にBkにTRCをかけけない		*/
/* ここまで						*/

typedef long	CST_Fixed32;		/* 符号付固定小数点型(整数部16bit/小数部16bit)	*/
typedef short	CST_Fixed16;		/* 符号付固定小数点型(整数部8bit/小数部8bit)	*/
typedef unsigned long	CST_UFixed32;	/* 符号無し固定小数点型(整数部16bit/小数部16bit)*/
typedef unsigned short	CST_UFixed16;	/* 符号無し固定小数点型(整数部8bit/小数部8bit)	*/

#define CST_TRUE	1
#define CST_FALSE	0


typedef struct {
    /* 3x3+c 変換用 Matrix */
    CST_Fixed32	a, b, c, c1,
		d, e, f, c2,
		g, h, i, c3;
} CST_Matrix3x4;

typedef struct {
    /* 3x1+c 変換用 Matrix */
    CST_Fixed32	a, b, c, c1;
} CST_Matrix3x1;

/*
 * CST_RGBcrParaStatusに設定される値の定義
 * ACCTにも使う
 */
#define CST_RGB_WPOINT_DEFAULT	0
#define CST_RGB_WPOINT_5000K	5000
#define CST_RGB_WPOINT_6500K	6500
#define CST_RGB_WPOINT_9300K	9300

#define CST_RGB_GAMMA_DEFAULT	0
#define CST_RGB_GAMMA_10	10
#define CST_RGB_GAMMA_14	14
#define CST_RGB_GAMMA_18	18
#define CST_RGB_GAMMA_22	22
#define CST_RGB_GAMMA_26	26

typedef struct {
    /* RGB色補正用のパラメータ */
    long	temperature;
    long	gamma;
} CST_RGBcrParaStatus;

/*
 * ACCT用の構造体
 * ただの3次元の線形変換に，
 * こんなに構造体定義しなきゃなんないなんて…
 * あほらし
 */
/* XYZ 色値（浮動小数点）*/
typedef struct {
    float	X;
    float	Y;
    float	Z;
} CST_ACCT_XYZ;

/* xy色値（浮動小数点）*/
typedef struct ACCT_xy {
    float	x;
    float	y;
} CST_ACCT_xy;

// L*a*b*色値（浮動小数点）
typedef struct {
    float	L;
    float	a;
    float	b;
} CST_ACCT_Lab;

/*　RGB 色値 */
typedef struct {
    CST_Fixed32		r;
    CST_Fixed32		g;
    CST_Fixed32		b;
} CST_ACCT_RGB32;

/* 色変換計算方法とパラメータの
 * 種類を表すフラグ型 */
typedef enum {
    CST_ACCT_NoParam			= -1,	/* パラメータが設定されていない	*/
    CST_ACCT_Matrix			= 0,	/* 3x3matrix			*/
    CST_ACCT_DlutTetraHydra17Grids	= 1,	/* DLUT（17grids,テトラヒドラ補間）*/
} CST_ACCT_ConvType;

/* 白かぶり除去処理のための補間演算のパラメータを格納する構造体
 * 補間演算を行う領域は点(65535,65535,65535)に接する大きさ4096の立方体である。*/
typedef struct {
    CST_ACCT_RGB32	a;	/* 点(61439,61439,61439)の出力値 */
    CST_ACCT_RGB32	b;	/* 点(61439,61439,65535)の出力値 */
    CST_ACCT_RGB32	c;	/* 点(61439,65535,61439)の出力値 */
    CST_ACCT_RGB32	d;	/* 点(61439,65535,65535)の出力値 */
    CST_ACCT_RGB32	e;	/* 点(65535,61439,61439)の出力値 */
    CST_ACCT_RGB32	f;	/* 点(65535,61439,65535)の出力値 */
    CST_ACCT_RGB32	g;	/* 点(65535,65535,61439)の出力値 */
    CST_ACCT_RGB32	h;	/* 点(65535,65535,65535)の出力値 */
} CST_ACCT_WhiteNeighbor;

/* RGB色補正用のデータ */
typedef struct {
    /* RGB色補正用の LUT + 3x3+C Matrix		*/
    /* preは，256byteずつ各コンポーネントのLUT	*/
    /* となる.つまり				*/
    /* pre[0..255] Blue用LUT			*/
    /* pre[256..511] Green用LUT			*/
    /* pre[512..767] RED用LUT となる		*/
    unsigned short	pre[256*3];
    CST_Matrix3x4	mat;

    /* ACCTの処理用のデータ			*/
    CST_ACCT_ConvType		type;
    CST_ACCT_WhiteNeighbor	wadj;
    CST_Fixed32			isWhiteAdjust;
} CST_RGBcrParaData;

//#define kACCT_N_TRC		256		/* TRCのステップ数 */
#define CST_kACCT_N_TRC		256		/* TRCのステップ数 */

typedef struct {
    char		*profname;		/* Profile Name 実体へのポインタ	*/
    unsigned short	inLut[3][CST_kACCT_N_TRC];/* ICC Profile 入力TRC			*/
    CST_Fixed32		matrix[3][3];		/*行列演算に使う3x3matrix,符号付固定小数点型(整数16/小数16)	*/
    unsigned short	dlut[17*17*17*4];	/* ICC Profile 変換用 D LUT実体		*/

    /* ACCTの処理用のデータ			*/
    CST_ACCT_ConvType		type;
    CST_ACCT_WhiteNeighbor	wadj;
    CST_Fixed32			isWhiteAdjust;
} CST_ICCProfileData;

typedef struct {
    /* LCC色補正用のパラメータ */
    signed char		lightness;
    signed char		contrast;
    signed char		chroma;
    signed char		dummy;
} CST_LCCcrParaStatus;

typedef struct {
    /* LCC色補正用の 3x3 Matrix	*/
    CST_Matrix3x4	mat;
    /* Gray用のパラメータ		*/
    CST_Fixed32		a;	/* 乗算係数 */
    CST_Fixed32		b;	/* 加算定数 */
} CST_LCCcrParaData;
/*
 * CST_Parameter で使用されるパラメータのサイズ
 */
#define CST_PARA_TRCCOLORBALANCE_SIZE	(4*4)
#define CST_PARA_TRC_SIZE		(256*5)
#define CST_PARA_COLORTRC_SIZE		(256*4)
#define CST_PARA_GRAYTRC_SIZE		(256)

/*
 * CSTパッケージは 以下のstructをパラメータとみなして，
 * 色変換処理を実行する．パラメータの正当性の検証は行わない．
 */
typedef struct {
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

    /* CSTコンポーネントは，Heap Memoryを使用しない．				*/
    /* 以下の領域を用いる．							*/
    unsigned char	work[1024*4];

} CST_Parameter;

/*
 * CST_PixelBufferInfo の指定例
 */
/*
 * all case.
 *
 *	  +----+----+----+-----+----+
 *buffer->|buf0|buf1|buf2| ... |bufn| n == component -1
 *	  +----+----+----+-----+----+
 *
 * case 1
 *	   +--------buf0
 *	   |  +-----buf1
 *	   |  |  +--buf2
 *	   |  !  !
 *	  +--+--+--+--+--+--+---+--+--+--+--+
 *	  |R0|G0|B0|P0|R1|G1|...|Rn|Gn|Bn|Pn| n == pixel_num -1
 *	  +--+--+--+--+--+--+---+--+--+--+--+
 *	  |	   |  |
 *	  +-----------+<- next_pixel
 *	  |	   |
 *	  +--------+---<- component
 *
 * case 2
 *
 *	  +--+--+--+--+--+--+---+--+
 * buf0 ->|R0|R1|R2|R3|R4|R5|...|Rn| n == pixel_num -1
 *	  +--+--+--+--+--+--+---+--+
 *	  |  |
 *	  +--+--+--+--+--+--+---+--+
 * buf1 ->|G0|G1|G2|G3|G4|G5|...|Gn| n == pixel_num -1
 *	  +--+--+--+--+--+--+---+--+
 *	  |  |
 *	  +--+--+--+--+--+--+---+--+
 * buf2 ->|B0|B1|B2|B3|B4|B5|...|Bn| n == pixel_num -1
 *	  +--+--+--+--+--+--+---+--+
 *	  |  |
 *	  +--+<- next_pixel
 */

/*
 * Buffer上にある画素値の記述用struct
 */
typedef struct {
    short		component,
			next_pixel;
    unsigned long	pixel_num;

    void	**buffer;
} CST_PixelBufferInfo;

/* Error Code は #define の羅列 */
#define CST_ERRORCODE_NOERROR	0
#define CST_ERRORCODE_ERROR	-1

/* 色空間の指定が必要な場合に用いる定数 */
enum CST_ColorSpaceName {
    CST_COLORSPACENAME_DONTCARE = 0,
    CST_COLORSPACENAME_sRGB,
    CST_COLORSPACENAME_sGray,
    CST_COLORSPACENAME_DevCMYK,
    CST_COLORSPACENAME_DevBlack,
    CST_COLORSPACENAME_DevWhite
};

/*
 * Tagのデータが固まったけど，
 * 修正面倒なので名前は同一．
 * 値をCommon/COM_ObjectTag.hと同一に変更
 */
typedef unsigned long CST_TagName;

/* #define CST_TAGNAME_DONTCARE	0x00000003 */
#define CST_TAGNAME_FONT	0x00000001
#define CST_TAGNAME_GRAPHICS	0x00000000
#define CST_TAGNAME_IMAGE	0x00000002

/*
 * CST_ParameterのBitFieldをアクセスするためのマクロ
 * および，各種の定数
 * 引数は unsigned long を前提においてあるので，注意
 */
/* CST_Parameter.status に対する定数		*/
#define CST_PARAMETER_STATUS_CR_CHANGED		(0x00000001)
#define CST_PARAMETER_STATUS_CST_CHANGED	(0x00000002)
#define CST_PARAMETER_STATUS_DONTEXEC_CST	(0x00000004)
/* CST_Parameter.status に対するマクロ		*/
#define CST_PARAMETER_IS_CR_CHANGED(x)		((x)&(CST_PARAMETER_STATUS_CR_CHANGED))
#define CST_PARAMETER_IS_CST_CHANGED(x)		((x)&(CST_PARAMETER_STATUS_CST_CHANGED))
#define CST_PARAMETER_IS_DONTEXEC_CST(x)	((x)&(CST_PARAMETER_STATUS_DONTEXEC_CST))

/* CST_Parameter.crstatusに対する定数		*/
#define CST_PARAMETER_CRSTATUS_EXEC_CR		(0x00000001)	/* 0 bit	*/
#define CST_PARAMETER_CRSTATUS_EXEC_SIMPLE_BK	(0x00000002)	/* 1 bit	*/
#define CST_PARAMETER_CRSTATUS_EXEC_100PER_BK	(0x00000004)	/* 2 bit	*/
#define CST_PARAMETER_CRSTATUS_EXEC_RGB_CR	(0x00000018)	/* 4〜3 bit	*/
#define CST_PARAMETER_CRSTATUS_EXEC_LCC_CR	(0x00000380)	/* 9〜7 bit	*/
#define CST_PARAMETER_CRSTATUS_DONTEXEC_COLORBALANCE_CR	(0x00000400)	/* 10 bit	*/
#define CST_PARAMETER_CRSTATUS_DONTEXEC_TRC_CR	(0x00000800)	/* 11 bit	*/
#define CST_PARAMETER_CRSTATUS_DONTEXEC_LUT_CR	(0x00001000)	/* 12 bit	*/

/* CST_Parameter.crstatusに対するマクロ		*/
#define CST_PARAMETER_IS_EXEC_CR(x)		((x)&(CST_PARAMETER_CRSTATUS_EXEC_CR))
#define CST_PARAMETER_IS_EXEC_SIMPLE_BK(x)	((x)&(CST_PARAMETER_CRSTATUS_EXEC_SIMPLE_BK))
#define CST_PARAMETER_IS_EXEC_100PER_BK(x)	((x)&(CST_PARAMETER_CRSTATUS_EXEC_100PER_BK))
#define CST_PARAMETER_IS_EXEC_RGB_CR(x)		((x)&(CST_PARAMETER_CRSTATUS_EXEC_RGB_CR))
#define CST_PARAMETER_IS_EXEC_LCC_CR(x)		((x)&(CST_PARAMETER_CRSTATUS_EXEC_LCC_CR))
#define CST_PARAMETER_IS_DONTEXEC_COLORBALANCE_CR(x)		((x)&(CST_PARAMETER_CRSTATUS_DONTEXEC_COLORBALANCE_CR))
#define CST_PARAMETER_IS_DONTEXEC_TRC_CR(x)		((x)&(CST_PARAMETER_CRSTATUS_DONTEXEC_TRC_CR))
#define CST_PARAMETER_IS_DONTEXEC_LUT_CR(x)		((x)&(CST_PARAMETER_CRSTATUS_DONTEXEC_LUT_CR))

#define CST_PARAMETER_IS_EXEC_RGBCR_TEM(x)	((x)&(0x00000008))
#define CST_PARAMETER_IS_EXEC_RGBCR_GAM(x)	((x)&(0x00000010))
#define CST_PARAMETER_IS_EXEC_RGBCR_ICC1(x)	((x)&(0x00000020))
#define CST_PARAMETER_IS_EXEC_RGBCR_ICC2(x)	((x)&(0x00000040))
#define CST_PARAMETER_RESET_EXEC_RGBCR_ICC1(x)	(x= ((x)&(~(0x00000020))))
#define CST_PARAMETER_RESET_EXEC_RGBCR_ICC2(x)	(x= ((x)&(~(0x00000040))))
#define CST_PARAMETER_SET_EXEC_RGBCR_ICC1(x)	(x= ((x)|(0x00000020)))
#define CST_PARAMETER_SET_EXEC_RGBCR_ICC2(x)	(x= ((x)|(0x00000040)))

#define CST_PARAMETER_IS_EXEC_LCCCR_CONT(x)	((x)&(0x00000080))
#define CST_PARAMETER_IS_EXEC_LCCCR_CHRO(x)	((x)&(0x00000100))
#define CST_PARAMETER_IS_EXEC_LCCCR_LIGH(x)	((x)&(0x00000200))

#define CST_PARAMETER_SET_EXEC_CR(a)		(a = ((a)|(CST_PARAMETER_CRSTATUS_EXEC_CR)))
#define CST_PARAMETER_RESET_EXEC_CR(a)		(a = ((a)&(~CST_PARAMETER_CRSTATUS_EXEC_CR)))
#define CST_PARAMETER_SET_EXEC_RGB_CR(a)	(a = ((a)|(CST_PARAMETER_CRSTATUS_EXEC_RGB_CR)))
#define CST_PARAMETER_RESET_EXEC_RGB_CR(a)	(a = ((a)&(~CST_PARAMETER_CRSTATUS_EXEC_RGB_CR)))
#define CST_PARAMETER_SET_EXEC_LCC_CR(a)	(a = ((a)|(CST_PARAMETER_CRSTATUS_EXEC_LCC_CR)))
#define CST_PARAMETER_RESET_EXEC_LCC_CR(a)	(a = ((a)&(~CST_PARAMETER_CRSTATUS_EXEC_LCC_CR)))

#define CST_PARAMETER_SET_EXEC_SIMPLE_BK(a)	(a = ((a)|(CST_PARAMETER_CRSTATUS_EXEC_SIMPLE_BK)))
#define CST_PARAMETER_RESET_EXEC_SIMPLE_BK(a)	(a = ((a)&(~CST_PARAMETER_CRSTATUS_EXEC_SIMPLE_BK)))
#define CST_PARAMETER_SET_EXEC_100PER_BK(a)	(a = ((a)|(CST_PARAMETER_CRSTATUS_EXEC_100PER_BK)))
#define CST_PARAMETER_RESET_EXEC_100PER_BK(a)	(a = ((a)&(~CST_PARAMETER_CRSTATUS_EXEC_100PER_BK)))

/* CST_Parameter.cststatusに対するマクロ	*/
#define CST_PARAMETER_GET_DLUT_NUMBER(x)	((x)&(0x000000FF))
#define CST_PARAMETER_GET_TRC_NUMBER(x)		(((x)&(0x0000FF00))>>8)
#define CST_PARAMETER_SET_DLUT_NUMBER(a,b)	(a = (((a)&(~0x000000FF))|(b)))
#define CST_PARAMETER_SET_TRC_NUMBER(a,b)	(a = (((a)&(~0x0000FF00))|(b<<8)))


/*----------------------------------*/
/*	外部インタフェース定義			*/
/* for Renderer						*/
/*----------------------------------*/

/*
 * CSTパッケージ Public I/F
 */
extern int CST_Init( CST_Parameter * );
extern int CST_MakeParameter( void *cst );
extern int CST_SetColorParameter( void *cst, CST_Parameter *);

extern int CST_StartJob( void *cst );
extern int CST_EndJob( void *cst );
extern int CST_StartPage( void *cst );
extern int CST_EndPage( void );

extern int CST_TransValueWithTag( void *cst, unsigned char *, CST_TagName );
extern int CST_TransBufferWithTag( void *cst, CST_PixelBufferInfo *,
			    CST_PixelBufferInfo *,CST_TagName );

/*
 * CSTオブジェクト化追加I/F
 */

void *CST_Initialize( CST_Parameter *, void *sif_mi, void *sif );
int CST_SetColorParamter( void *cst, CST_Parameter * );
int CST_Finalize( void *cst );

/*
 * デバッグ用関数
 */
#ifdef CST_DEBUG
void print_CST_TRC256x1( unsigned char * );
void print_CST_TRC256x3( unsigned char * );
void print_CST_TRC256x4( unsigned char * );
void print_CST_TRC256x5( unsigned char * );
void print_CST_Matrix3x4( CST_Matrix3x4 * );
void print_CST_RGBcrParaStatus( CST_RGBcrParaStatus * );
void print_CST_RGBcrParaData( CST_RGBcrParaData * );
void print_CST_LCCcrParaStatus( CST_LCCcrParaStatus * );
void print_CST_Parameter( CST_Parameter * );
#endif	/* CST_DEBUG */

#endif	/* CST_IF_H_INCLUDED */
