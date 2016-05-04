/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Job.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_Job_h
#define INC_IMG_Job_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"

typedef enum img_patternmode {
	IMG_PATTERN_IGNORE_CTM,
	IMG_PATTERN_APPLY_CTM,
	IMG_PATTERN_ROTATION_ONLY,
} IMG_PatternMode;

typedef struct img_job
{
	void					*memTop;
	IMG_Context				context;			/* コンテキスト */
	struct img_displaylist	*displayList;		/* DisplayListオブジェクト */
	struct img_commandprocessor	*processor;		/* カレントのページオブジェクト */
	IMG_UINT16				outputResolutionX;	/* X方向の出力解像度 */
	IMG_UINT16				outputResolutionY;	/* Y方向の出力解像度 */
	IMG_UINT16				inputResolutionX;	/* X方向の入力解像度 */
	IMG_UINT16				inputResolutionY;	/* Y方向の入力解像度 */
	IMG_UINT16				imageResolutionY;	/* Y方向のイメージ蓄積解像度 */
	IMG_UINT16				imageResolutionX;	/* X方向のイメージ蓄積解像度 */
	IMG_UINT16				maxPageSizeX;		/* X方向の最大ページサイズ(出力解像度でのピクセル値) */
	IMG_UINT16				maxPageSizeY;		/* Y方向の最大ページサイズ(出力解像度でのピクセル値) */
	IMG_UINT16				patternResolution;	/* パターンのオリジナル解像度 */
	IMG_PatternMode			patternMode;		/* パターン生成モード */
	IMG_BOOL				imageSmoothingReduce;		/* イメージ縮小時の補間処理を行うかどうか */
	IMG_UINT32				imageQualityReduce;			/* イメージ縮小時の品質 */
	IMG_BOOL				imageSmoothingMagnify;		/* イメージ拡大時の補間処理を行うかどうか */
	IMG_UINT32				imageQualityMagnify;		/* イメージ拡大時の品質 */
	IMG_BOOL				maskSmoothingReduce;		/* イメージマスク縮小時の補間処理を行うかどうか */
	IMG_UINT32				maskQualityReduce;			/* イメージマスク縮小時の品質 */
	IMG_BOOL				maskSmoothingMagnify;		/* イメージマスク拡大時の補間処理を行うかどうか */
	IMG_UINT32				maskQualityMagnify;		/* イメージマスク拡大時の品質 */
	IMG_UINT32				pageNumber;			/* 現在処理中のページ番号 */
	IMG_INT32				currentSaveLevel;	/* 現在のSaveレベル */
} IMG_Job;

#endif /* INC_IMG_Job_h */

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 * 18,Apr.2001 Yozo Kashima forward declarationを削除。
 * 08.Mar.2001 Yozo Kashima currentPatternIDメンバを削除(IMG_Pageに移した)。
 * 10.Mar.2001 Yozo Kashima ropReplacementメンバを追加。
 * 26.Jul.2001 Yozo Kashima ropReplacementメンバを削除。processorメンバを追加。
 * 20.Aug.2001 Yozo Kashima pageNumberメンバを追加(ログ書き込み用)。
 * 11.Dec.2002 Yozo Kashima イメージの独立解像度指定のための変更。
 *							resolution{X,Y}をoutputResolution{X,Y}に変更。
 *							inputResolution{X,Y},imageResolution{X,Y}を追加。
 *							maxPage{X,Y}をmaxPageSize{X,Y}にImager内で名称を統一。
 * 19.Dec.2002 Yozo Kashima imageSmoothingとimageQualityメンバを追加。
 * 28.May.2003 Yozo Kashima currentSaveLevelを追加(AR#845)。
 * 10.Aug.2004 Yozo Kashima Maskの補間方法に関するメンバ変数を追加(DW-V6.0 MRC対応)。
 */

/* end of IMG_Job.h */
