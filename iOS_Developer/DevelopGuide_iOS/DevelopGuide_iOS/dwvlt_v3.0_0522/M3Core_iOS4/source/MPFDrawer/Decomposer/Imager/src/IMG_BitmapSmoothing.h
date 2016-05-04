/* IMG_BitmapSmoothign.h */

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_Matrix.h"

#include "IMG_ScaleRIEMEP.h"
#include "IMG_RIELCCA.h"

/* 構造体宣言 */
typedef struct {
	IMG_UINT16			planes;			/* プレーン数			*/
	IMG_INT16			x_offset;		/* X方向の移動成分		*/
	IMG_INT16			y_offset;		/* Y方向の移動成分		*/
	IMG_UINT16			dWidth;		    /* 入力幅(回転を考慮しない本来の幅	*/
	IMG_UINT16			inWidth;		/* 入力幅(90度回転の場合は入力高さ	*/
	IMG_UINT16			inHeight;		/* 入力高さ(90度回転の場合は入力幅	*/

    unsigned char		*in_buffer;

    LCCA               lcca;
    RingBuffer         rBuf;
    detectAngle        dAngle;
    enlargeBlock       eBlock;
} IMG_RieObject;

typedef struct {
	IMG_Context			*pContext;		/* Imagerコンテキスト(ファイル出力のとき使う) */
	IMG_ColorSpace		inColorSpace;	/* 入力カラースペース */
	IMG_UINT16			inWidth;		/* 入力幅 */
	IMG_UINT16			inWidthBytes;	/* 入力幅バイト */
	IMG_UINT16			inHeight;		/* 入力高さ */
	char				*inDataAddress;	/* 入力データ開始アドレス */
	void				*inDatafile;	/* 入力ファイル(16Mを超えるイメージ対応) */
	IMG_Matrix_Angle	outAngle;		/* 出力回転角度 */
	IMG_UINT16			outWidth;		/* 出力幅 */
	IMG_UINT16			outWidthBytes;	/* 出力幅バイト */
	IMG_UINT16			outHeight;		/* 出力高さ */
	char				*outDataAddress;/* 出力データ書き込み開始アドレス(メモリ出力のときだけ) */
	void				*outDatafile;	/* 出力ファイル(ファイル出力のときだけ) */
	char				*pWork;			/* 作業用バッファ開始アドレス(ファイル出力のときだけ) */

    IMG_RieObject       rieObject;
} IMG_BitmapSmoothingParam, IMG_BitmapSmoothingParamPointer;

/* プロトタイプ宣言 */
int IMG_BitmapSmoothing     (IMG_BitmapSmoothingParam *pParam);
int IMG_InitBitmapSmoothing (IMG_BitmapSmoothingParam *pParam);


