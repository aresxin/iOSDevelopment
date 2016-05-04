/* IMG_BitmapRotation.h */

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_Matrix.h"
#include "IMG_Image.h"

#ifndef IMG_MIN
#define IMG_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

/* 列挙宣言 */
typedef enum {
	IMG_8BIT_BOUNDARY,
	IMG_16BIT_BOUNDARY,
	IMG_32BIT_BOUNDARY,
} IMG_Boundary;

typedef enum {
	IMG_IMAGE_PARALLEL,
	IMG_IMAGE_VERTICAL,
} IMG_ImageDirection;

/* 構造体宣言 */
typedef struct IMG_BitmapRotationParam {
	IMG_Context			*pContext;		/* Imagerコンテキスト(ファイル出力のとき使う) */
	IMG_Matrix			*pMatrix;		/* 拡縮の誤差を少なくするため入れた */
	IMG_ColorSpace		inColorSpace;	/* 入力カラースペース */
	IMG_UINT8			inDataDepth;	/* 入力カラー深さ */
	IMG_UINT16			inWidth;		/* 入力幅 */
	IMG_UINT16			inWidthBytes;	/* 入力幅バイト */
	IMG_UINT16			inHeight;		/* 入力高さ */
	IMG_ColorInterleave	inInterleave;	/* 入力色順次(入力が24BPPのときだけ)  */
	IMG_PatternPolarity	inPolarity;		/* 入力極性(入力が1BPPのときだけ) */
	char				*inDataAddress;	/* 入力データ開始アドレス */
	void				*inDatafile;	/* 入力ファイル(16Mを超えるイメージ対応) */
	IMG_ColorSpace		outColorSpace;	/* 出力カラースペース */
	IMG_UINT8			outDataDepth;	/* 出力カラー深さ */
	IMG_Matrix_Angle	outAngle;		/* 出力回転角度 */
	IMG_UINT16			outWidth;		/* 出力幅 */
	IMG_UINT16			outWidthBytes;	/* 出力幅バイト */
	IMG_UINT16			outHeight;		/* 出力高さ */
	IMG_Boundary		outBoundary;	/* 出力のカラーバウンダリ(出力が24BPPのときだけ) */
	char				*outDataAddress;/* 出力データ書き込み開始アドレス(メモリ出力のときだけ) */
	void				*outDatafile;	/* 出力ファイル(ファイル出力のときだけ) */
	char				*pWork;			/* 作業用バッファ開始アドレス(ファイル出力のときだけ) */
	IMG_BOOL			colorFlg;		/* 縮小時の1BPPの時にカラーデーターがあるか？ */
	IMG_SmoothingType	smoothingType;	/* 縮小時のスムージング */
	IMG_UINT16			smoothingQuality;/* 縮小時のスムージング品質 */
	IMG_Palette			*palette;		/* パレット */
} IMG_BitmapRotationParam,IMG_BitmapRotationParamPointer;

typedef struct img_bitmappixel {
	char				*pStartAddress;	/* 開始アドレス(8ビットデータアドレス) */
	IMG_UINT8			startBit;		/* 開始Pixelがアドレスデータ内の８ビットデータ内の何ビット目なのか */
	IMG_FLOAT			pitchX1;		/* DestのX方向1ピクセル移動に対するSourceのX移動値 */
	IMG_FLOAT			pitchY1;		/* DestのX方向1ピクセル移動に対するSourceのY移動値 */
	IMG_FLOAT			pitchX2;		/* DestのY方向1ピクセル移動に対するSourceのX移動値 */
	IMG_FLOAT			pitchY2;		/* DestのY方向1ピクセル移動に対するSourceのY移動値 */
	IMG_INT16			intPitchX1;		/* DestのX方向1ピクセル移動に対するSourceのX移動ベクトル */
	IMG_INT16			intPitchY1;		/* DestのX方向1ピクセル移動に対するSourceのY移動ベクトル */
	IMG_INT16			intPitchX2;		/* DestのY方向1ピクセル移動に対するSourceのX移動ベクトル */
	IMG_INT16			intPitchY2;		/* DestのY方向1ピクセル移動に対するSourceのY移動ベクトル */
	IMG_INT16			lastPitchX;		/* 縮小時の最終端のピクセルの長さ(X方向) */
	IMG_INT16			lastPitchY;		/* 縮小時の最終端のピクセルの長さ(Y方向) */
	IMG_ImageDirection	direction;		/* イメージのねじれ具合 */
#ifndef IMG_IMAGESHRINK
	IMG_UINT16			smoothingX;		/* X方向のスムージング品質(ソースデータの何ピクセルまで保証するか) */
	IMG_UINT16			smoothingY;		/* Y方向のスムージング品質(ソースデータの何ピクセルまで保証するか) */
#endif /* IMG_IMAGESHRINK */
#ifdef IMG_IMAGESHRINK
	IMG_INT16			*xBlockSizeArray;	/* 縮小時のX方向ピクセル数の配列 */
	IMG_INT16			*yBlockSizeArray;	/* 縮小時のY方向ピクセル数の配列 */
#endif /* IMG_IMAGESHRINK */
} IMG_BitmapPixel,IMP_BitmapPixelPointer;

/* プロトタイプ宣言 */
int
IMG_BitmapRotation(IMG_BitmapRotationParam	*pParam);
int
IMG_BitmapRotation16M(IMG_BitmapRotationParam	*pParam);
int
IMG_BitmapColorConvert(IMG_ColorSpace colorSpace,IMG_ColorData *pColor);
int
IMG_PointToWidth(IMG_Point *pPoint1,IMG_Point *pPoint2,IMG_UINT16 *pWidth,IMG_UINT16 *pHeight);
