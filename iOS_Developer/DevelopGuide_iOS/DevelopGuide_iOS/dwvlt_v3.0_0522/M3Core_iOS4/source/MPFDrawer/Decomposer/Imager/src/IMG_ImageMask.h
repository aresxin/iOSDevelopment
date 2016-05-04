/* IMG_ImageMask.h */
#ifndef INC_IMG_ImageMask_h
#define INC_IMG_ImageMask_h

#include "IMG_BitmapShape.h"
#include "IMG_ClassPointer.h"

/* 構造体宣言 */
typedef struct IMG_ImageMask {
	int				(*destroy)(IMG_BitmapShape *object);
	int				(*draw)(IMG_BitmapShapePointer object,
							IMG_DisplayList *displayList,
							IMG_TagFilterPtr tagFilter,
							IMG_Matrix *matrix);
	IMG_UINT8		bitmapType;		/* character,image,imagemaskのどれなのか */
	/* ここまでは共通 */
	IMG_Context			context;		/* Image共通context */
	IMG_Point			paintingPoint;	/* 表示座標 */
	IMG_Matrix			matrix;			/* イメージ用変換マトリクス */
#if defined(HB_USE_FIXEDPOINT)
	/* 固定小数点 精度不足に起因する障害の回避 */
	IMG_FLOAT			fltMatrix[6];
#endif
	IMG_Mask			mask;			/* マスクデータ */
	IMG_UINT16			dwidth;			/* 出力する幅 */
	IMG_UINT16			dheight;		/* 出力する高さ */
	IMG_Matrix_Angle	angle;			/* 角度 */
	IMG_BOOL			smallImageDrawFlg;/* HalfScanLineにかからないイメージを描画するかどうかのフラグ */
	IMG_BOOL			smoothBinaryFlg;/* IMG_TRUEならバイナリ高速補完する，IMG_FALSEなら補完しない */
	IMG_BOOL				smoothReduceFlg;		/* 縮小時IMG_TRUEなら補完する，IMG_FALSEなら補完しない */
	IMG_BOOL				smoothMagnifyFlg;		/* 拡大時IMG_TRUEなら補間する，IMG_FALSEなら補完しない */
	IMG_UINT32				smoothQualityReduce;	/* 縮小イメージ品質指定 */
	IMG_UINT32				smoothQualityMagnify;	/* 拡大イメージ品質指定	*/
	IMG_BOOL			adjustX;		/* 回転時のX方向の補正を行うかどうかを示すフラグ */
	IMG_BOOL			adjustY;		/* 回転時のX方向の補正を行うかどうかを示すフラグ */
} IMG_ImageMask,*IMG_ImageMaskPointer;

typedef struct IMG_ImageMaskParam {
	IMG_Point				point;			/* マスクイメージ表示座標 */
	IMG_Matrix				matrix;			/* マスクイメージ用マトリクス */
#if defined(HB_USE_FIXEDPOINT)
	/* 固定小数点 精度不足に起因する障害の回避 */
	IMG_FLOAT			fltMatrix[6];
#endif
	IMG_UINT16				width;			/* マスクイメージ幅 */
	IMG_UINT16				height;			/* マスクイメージ高さ */
	IMG_UINT32				maskDataSize;	/* マスクイメージバイトサイズ */
	IMG_PatternPolarity		maskPolarity;	/* マスクの極性 */
	IMG_BOOL				smallImageDrawFlg;/* 1ピクセル以下の幅又は高さのイメージマスクを描画するかどうかのフラグ */
	IMG_BOOL				smoothBinaryFlg;/* IMG_TRUEならバイナリ高速補完する，IMG_FALSEなら補完しない */
	IMG_BOOL				dataMallocFlg;
	IMG_BOOL				smoothReduceFlg;		/* 縮小時IMG_TRUEなら補完する，IMG_FALSEなら補完しない */
	IMG_BOOL				smoothMagnifyFlg;		/* 拡大時IMG_TRUEなら補間する，IMG_FALSEなら補完しない */
	IMG_UINT32				smoothQualityReduce;	/* 縮小イメージ品質指定 */
	IMG_UINT32				smoothQualityMagnify;	/* 拡大イメージ品質指定	*/
} IMG_ImageMaskParam,*IMG_ImageMaskParamPointer;	

/* 関数プロトタイプ宣言 */
IMG_BitmapShapePointer
	IMG_ImageMaskCreate(IMG_Context *context,IMG_ImageMaskParam	*imageMaskParam,
					char *maskAddress);
#endif /* INC_IMG_ImageMask_h */
