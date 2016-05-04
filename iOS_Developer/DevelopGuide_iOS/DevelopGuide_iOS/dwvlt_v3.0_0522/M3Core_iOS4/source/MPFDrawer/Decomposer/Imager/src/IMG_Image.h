/* IMG_Image.h */
#ifndef INC_IMG_Image_h
#define INC_IMG_Image_h

#include "IMG_BitmapShape.h"
#include "IMG_ClassPointer.h"

/* 宣言 */
/* パラメータ */
/* 最大横幅を何PIXELにするか */
/* 1200DPI,A3長辺を想定 */
#define IMG_IMAGE_MAX_PIXEL		(IMG_UINT16)(1024*16)

/* 列挙型宣言 */
typedef enum IMG_PaletteType {
	IMG_PALETTE_NULL,	/* パレットは無効 */
	IMG_PALETTE_COLOR,	/* カラー(BGR)パレット */
	IMG_PALETTE_GRAY,	/* グレー(GRAY)パレット */
} IMG_PaletteType;

/* 縮小方法の定義	*/
typedef enum IMG_SmoothingType {
	IMG_SMOOTHING_NONE,
	IMG_SMOOTHING_LOW,
	IMG_SMOOTHING_HIGH
} IMG_SmoothingType;

/* 拡大方法の定義	*/
typedef enum IMG_MagnifyType {
	IMG_MAGNIFY_DONTCARE,		/* 拡大しない，後段任せ	*/
	IMG_MAGNIFY_RIE				/* RIEで拡大，補間あり	*/
} IMG_MagnifyType;


/* 構造体宣言 */

typedef struct IMG_Palette {
	IMG_PaletteType	paletteType;
	IMG_UINT16		entries;/* 1〜256個 */
	IMG_UINT32		dataSize;
	char			*dataAddress;
	IMG_BOOL		dataMallocFlg;
} IMG_Palette,*IMG_PalettePointer;

typedef struct IMG_Image {
	int				(*destroy)(IMG_BitmapShape *object);
	int				(*draw)(IMG_BitmapShapePointer object,
							IMG_DisplayList *displayList,
							IMG_TagFilterPtr tagFilter,
							IMG_Matrix *matrix);
	IMG_UINT8		bitmapType;		/* character,image,imagemaskのどれなのか */
	/* ここまでは共通 */
	IMG_Context			context;		/* Image共通context */
	IMG_Point			paintingPoint;	/* 表示座標 */
	IMG_Matrix			matrix;			/* 変換マトリクス */
#if defined(HB_USE_FIXEDPOINT)
	/* 固定小数点 精度不足に起因する障害の回避 */
	IMG_FLOAT			fltMatrix[6];
#endif
	IMG_Palette			palette;		/* パレット */
	/*IMG_Mask			mask;*/
	IMG_UINT16			width;			/* source幅 */
	IMG_UINT16			widthBytes;		/* source幅バイト */
	IMG_UINT16			height;			/* source高さバイト */
	IMG_UINT16			dWidth;			/* destination幅 */
	IMG_UINT16			dHeight;		/* destination高さ */
	IMG_Matrix_Angle	angle;			/* 回転角度 */
	IMG_ColorSpace		colorSpace;		/* カラースペース*/
	IMG_UINT8			interleave;		/* 色順次 */
	IMG_UINT8			dataDepth;		/* データ深さ */
	IMG_UINT32			dataSize;		/* データサイズ */
	char				*dataAddress;	/* データアドレス */
	IMG_BOOL			dataMallocFlg;	/* データのメモリを解放するかどうかのフラグ */
	IMG_BOOL			smallGrayFlg;	/* グレイデータでイメージが小さいかどうかのフラグ */
	IMG_BOOL			colorFlg;		/* 縮小時の1BPPの時にカラーデーターがあるか？ */
	IMG_BOOL			smallImageDrawFlg;/* HalfScanLineにかからないイメージを描画するかどうかのフラグ */
	IMG_BOOL			adjustX;		/* 回転時のX方向の補正を行うかどうかを示すフラグ */
	IMG_BOOL			adjustY;		/* 回転時のX方向の補正を行うかどうかを示すフラグ */
	IMG_SmoothingType	smoothingType;	/* 縮小時のスムージング */
	IMG_UINT16			smoothingQuality;/* 縮小時のスムージング品質 */
	IMG_MagnifyType		magnifyType;	/* 拡大時の方法 */
	IMG_UINT16			magnifyQuality;	/* 拡大時のスムージング品質 */
	IMG_FLOAT			imageScaleX;	/* イメージのスケーリングＸ方向 */
	IMG_FLOAT			imageScaleY;	/* イメージのスケーリングＹ方向 */
	void				*filePointer;	/* 16M over対応のためのファイルポインタ */
} IMG_Image,*IMG_ImagePointer;

typedef struct IMG_ImageParam {
	IMG_Point			point;					/* イメージ開始座標 */
	IMG_Matrix			matrix;					/* イメージ用変換マトリクス */
#if defined(HB_USE_FIXEDPOINT)
	/* 固定小数点 精度不足に起因する障害の回避 */
	IMG_FLOAT			fltMatrix[6];
#endif
	IMG_UINT16			width;					/* イメージデータの幅 */
	IMG_UINT16			widthBytes;				/* イメージデータの幅バイト数 */
	IMG_UINT16			height;					/* イメージデータの高さ */
	IMG_ColorSpace		imageColorSpace;		/* イメージデータのカラースペース */	
	IMG_ColorInterleave	imageColorInterleave;	/* イメージデータの色順 */
	IMG_UINT8			imageDataDepth;			/* イメージデータの深さ */
	IMG_UINT32			imageDataSize;			/* イメージデータのバイト数 */
	IMG_PatternPolarity	maskPolarity;			/* マスクデータの極性 */
	IMG_UINT32			maskDataSize;			/* マスクデータのバイト数 */
	IMG_UINT16			paletteEntries;			/* パレットデータのエントリ数 */
	IMG_UINT32			paletteDataSize;		/* 全パレットデータのバイト数 */
	IMG_BOOL			dataMallocFlg;			/* 入力データをIMG_FREEする必要があるかどうか IMG_TRUEなら必要あり */
	IMG_BOOL			paletteMallocFlg;		/* パレットデータをIMG_FREEする必要があるかどうか IMG_TRUEなら必要あり */
	IMG_BOOL			smallImageDrawFlg;		/* 1ピクセル以下の幅又は高さのイメージを描画するかどうかのフラグ */
	IMG_BOOL			smoothReduceFlg;		/* 縮小時IMG_TRUEなら補完する，IMG_FALSEなら補完しない */
	IMG_BOOL			smoothMagnifyFlg;		/* 拡大時IMG_TRUEなら補間する，IMG_FALSEなら補完しない */
	IMG_BOOL			smoothBinaryFlg;		/* IMG_TRUEならバイナリ高速補完する，IMG_FALSEなら補完しない */
	IMG_UINT32			smoothQualityReduce;	/* 縮小イメージ品質指定 */
	IMG_UINT32			smoothQualityMagnify;	/* 拡大イメージ品質指定	*/
	IMG_FLOAT			imageScaleX;			/* 中間コードイメージ解像度比率X */
	IMG_FLOAT			imageScaleY;			/* 中間コードイメージ解像度比率Y */
} IMG_ImageParam,*IMG_ImageParamPointer;	

/* プロトタイプ宣言 */
IMG_BitmapShapePointer
	IMG_ImageCreate(IMG_Context *context,IMG_ImageParam	*imageParam,
					char *maskAddress,char *paletteAddress,char *imageAddress,char *pFileName);

#endif /* INC_IMG_Image_h */
