/*!
  @file  XdwBridgeHBPSContSource.cpp
  @brief BridgeHBPS クラス実装ファイル

  XdwBridgeを継承したXdwBridgeHBPS classは，
  HostBased DecomposerのImagerを隠蔽してクライアントに対して，
  共通のBridge I/Fを提供する．<br>
  このファイルでは，主に，初期化，制御関連I/F，XdwBridgeViewerContIF　I/F，の実体を記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-04-08
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-08	Toshio Yamazaki<br>
  Modify:	2002-09-30	Kenichi Ishida 各メソッドの実装<br>
 */

#include <string.h>

extern "C" {
#include "HB_Decomposer.h"

#ifdef BRIDGE_HBPS_PRINT
#include "CST_IF.h"
#endif

}

#include "XdwBridgeHBPSHeader.h"
#include "XdwLogInterface.h"
#include "XdwDataObjectBinary.h"
#include "XdwOffScreen.h"
#include "XdwBridgeGraphicStateManager.h"
#include "XdwBridgeHBPSHeader.h"
#include "XdwBridgeHBPSInternal.h"
#include "XdwBridgeGraphicDrawForHBPS.h"
#include "XdwBridgeGraphicStateBrushForHBPS.h"
#include "XdwBridgeGraphicStatePenForHBPS.h"
#include "XdwBridgeColorManagerForHBPS.h"
#include "XdwBridgeRasterManagerForHBPS.h"
#include "XdwBridgeRasterOutputAdapterForHBPS.h"
#include "XdwBridgePatternDrawForHBPS.h"
#include "XdwBridgeRopStateForHBPS.h"

/*!コンストラクタ
	コンストラクタでは，動的メモリの確保は行われない．
	ただし，ポインタのNULL初期化は行われる．
 */
XdwBridgeHBPS::XdwBridgeHBPS()
{
    /* 関連の初期化 */
    fXdwLogInterface = XdwNull;
    /* 属性の初期化 */
    fHandleCount = 0;

	imagerF = (void*)XdwNull;
	gd_rectangleF = (XdwBridgeGDRectangleForHBPS*)XdwNull;
	gd_commonF = (XdwBridgeGDCommonForHBPS*)XdwNull;
	penF = (XdwBridgeGraphicStatePen*)XdwNull;
	brushF = (XdwBridgeGraphicStateBrush*)XdwNull;
	colorF = (XdwBridgeColorManager*)XdwNull;
	gstateF = (XdwBridgeGraphicStateManager*)XdwNull;
	raster_managerF = (XdwBridgeRasterManagerForHBPS*)XdwNull;
	raster_outputF = (XdwBridgeRasterOutputAdapterForHBPS*)XdwNull;
	pattern_drawF = (XdwBridgePatternDrawForHBPS*)XdwNull;
	rop_stateF = (XdwBridgeRopStateForHBPS*)XdwNull;

	/* パス構築状態初期化　*/
	path_state = FALSE;
};

/*!デストラクタ
	XdwBridgeが動的に確保したメモリ領域のみFreeされる．
	他のクラスにおいて生成したと思われる領域のFreeは行わない．
 */
XdwBridgeHBPS::~XdwBridgeHBPS()
{
	/* 途中で処理が中断した場合にもブリッジで確保した
	   メモリを解放できるようにする */
	Terminate( );

	XdwDelete( gd_rectangleF );
	XdwDelete( penF );
	XdwDelete( brushF );
	XdwDelete( colorF );
	XdwDelete( gstateF );
	XdwDelete( gd_commonF );
	XdwDelete( raster_managerF );
	XdwDelete( raster_outputF );
	XdwDelete( pattern_drawF );
	XdwDelete( rop_stateF );
};

/*!
 * @brief ブリッジのインスタンスを初期化する
  @retval XDW_ERRORCODE_NOERROR 正常終了
*/
XdwErrorCode XdwBridgeHBPS::Initialize(XdwLogInterface* log_file)
{
    /* パラメータのチェック */
    if(log_file == XdwNull){
        return XDW_ERRORCODE_INVALID_PARAMETER;
    };
    fXdwLogInterface = log_file;

    /* 属性の初期化 */
    fHandleCount = 0;


	/* HBPSPRINTの初期化デフォルトパラメータ設定 */
	
	CSTParam = NULL;
	jobParam = NULL;
	outParam = NULL;
	pageParam = NULL;

	if(CreateDefaultParameter() != XDW_ERRORCODE_SUCCESS){
		return XDW_ERRORCODE_ERROR;
	}

	return XDW_ERRORCODE_SUCCESS;
};

/*! 内部オブジェクト生成メソッド
 * XdwBridgeHBPSの内部オブジェクトを生成し，
 * 初期化する
 */
XdwErrorCode XdwBridgeHBPS::NewObject( void )
{
    XdwErrorCode	ret_code = XDW_ERRORCODE_SUCCESS;

    /* グラフィック属性関連クラスの生成		*/
    if ( (gstateF = XdwNew( XdwBridgeGraphicStateManager ) ) == (XdwBridgeGraphicStateManager*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
    };
    if ( (penF = XdwNew( XdwBridgeGraphicStatePenForHBPS(imagerF) )) == (XdwBridgeGraphicStatePenForHBPS*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
    };
    if ( (brushF = XdwNew( XdwBridgeGraphicStateBrushForHBPS(imagerF) )) == (XdwBridgeGraphicStateBrushForHBPS*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
    };
	if ( (colorF = XdwNew( XdwBridgeColorManagerForHBPS(gstateF, imagerF) )) == (XdwBridgeColorManagerForHBPS*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
	};

    /* グラフィック描画関連クラスの生成		*/
    if ( (gd_commonF = XdwNew( XdwBridgeGDCommonForHBPS(imagerF) )) == (XdwBridgeGDCommonForHBPS*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
	};
    if ( (gd_rectangleF = XdwNew( XdwBridgeGDRectangleForHBPS(imagerF, gstateF, colorF) )) == (XdwBridgeGDRectangleForHBPS*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
    };

	/* Raster関連クラスの生成			*/
	if ( (raster_managerF = XdwNew( XdwBridgeRasterManagerForHBPS(imagerF) )) == (XdwBridgeRasterManagerForHBPS*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
	};
	if ( (raster_outputF = XdwNew( XdwBridgeRasterOutputAdapterForHBPS(imagerF, gstateF) )) == (XdwBridgeRasterOutputAdapterForHBPS*)XdwNull ) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
	};

	if ( (pattern_drawF = XdwNew(XdwBridgePatternDrawForHBPS(imagerF)) ) == (XdwBridgePatternDrawForHBPS*)XdwNull) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
	}
	if ( (rop_stateF = XdwNew (XdwBridgeRopStateForHBPS(imagerF)) ) == XdwNull) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
	}

    /* 生成したクラスの初期化			*/
	if ( ret_code == XDW_ERRORCODE_SUCCESS ) ret_code = gstateF->Initialize();
	if ( ret_code == XDW_ERRORCODE_SUCCESS ) ret_code = raster_managerF->Initialize();
	if ( ret_code == XDW_ERRORCODE_SUCCESS ) ret_code = penF->Initialize();
	if ( ret_code == XDW_ERRORCODE_SUCCESS ) ret_code = brushF->Initialize();
	if ( ret_code == XDW_ERRORCODE_SUCCESS ) ret_code = colorF->Initialize();

	if ( ret_code == XDW_ERRORCODE_SUCCESS ) ret_code = pattern_drawF->Initialize(gstateF,colorF,raster_managerF,raster_outputF);
	if ( ret_code == XDW_ERRORCODE_SUCCESS ) ret_code = gd_rectangleF->Initialize(pattern_drawF);

    return ret_code;
};



/*! 描画関連の初期化を行うI/F
 */
XdwErrorCode XdwBridgeHBPS::InitializeDrawIF( void )
{
    /* 初期化のチェック */
    if(fXdwLogInterface == XdwNull){
        return XDW_ERRORCODE_NOT_INITIALIZED;
    };
	/* ダウンロードデータの解像度指定 */
	if ( HB_SetPatternResolution( imagerF, patternResolution ) != 0 ) {
		return XDW_ERRORCODE_ERROR;
	};
	if ( HB_SetRasterSmoothingMode( imagerF, 1, 0 ) != 0) {
		return XDW_ERRORCODE_ERROR;
	};
    /* 必要なオブジェクトを生成し初期化する		*/
	if( NewObject() != XDW_ERRORCODE_SUCCESS){
		return XDW_ERRORCODE_ERROR;
	};
    return XDW_ERRORCODE_SUCCESS;
};



/*!	制御系ブリッジのインスタンスを初期化する
*/
XdwErrorCode XdwBridgeHBPS::InitializeContIF( void )
{
	/* HostBasedImagerの生成 */
	imagerF = HB_Initialize( jobParam, jobSplParam, outParam, CSTParam, 0, jobExtraParam );

	if ( imagerF == (void*)XdwNull ) {
	    return XDW_ERRORCODE_INVALID_PARAMETER;
	};

	return XDW_ERRORCODE_SUCCESS;
}

/*! ジョブの開始
*/
XdwErrorCode XdwBridgeHBPS::StartJob( void )
{
  /* ジョブの開始
     
     パターンモード:	 i
     HB_PATTERN_IGNORE_CTM = 0
     HB_PATTERN_APPLY_CTM = 1
     HB_PATTERN_ROTATION_ONLY = 2 */

    if ( HB_StartJob( imagerF, 2 ) != 0 ) {
	return XDW_ERRORCODE_ERROR;
    };
    return XDW_ERRORCODE_SUCCESS;
};

/*!	ジョブの終了
*/
XdwErrorCode XdwBridgeHBPS::EndJob( void )
{
	if ( HB_EndJob( imagerF ) != 0 ) {
		return XDW_ERRORCODE_ERROR;
	};
    return XDW_ERRORCODE_SUCCESS;
};

/*!	Imagerの終了
*/
XdwErrorCode XdwBridgeHBPS::Terminate( void )
{
	if(imagerF != (void *)XdwNull){
		if ( HB_Finalize( imagerF ) != 0 ) {
			return XDW_ERRORCODE_ERROR;
		};
		imagerF = (void *)XdwNull;
	};

	DeleteDefaultParameter();

    return XDW_ERRORCODE_SUCCESS;
};

/* Error発生時のTerminate処理 AR1563 */
XdwErrorCode XdwBridgeHBPS::ErrorTerminate( void )
{
	if(imagerF != (void *)XdwNull){
		if ( HB_ErrorFinalize( imagerF ) != 0 ) {
			return XDW_ERRORCODE_ERROR;
		};
		imagerF = (void *)XdwNull;
	};

	DeleteDefaultParameter();

    return XDW_ERRORCODE_SUCCESS;
};


/*!	StartPage
*/
XdwErrorCode XdwBridgeHBPS::StartPage(  const XdwBridgePrintContIF::PageMode &pm )
{
	int ret_code;

	ret_code = HB_StartPage(imagerF, pageParam, pageSplParam, pageExtraParam);
    
	if ( ret_code != 0 ) {
	    return XDW_ERRORCODE_ERROR;
	};

	ret_code = HB_SetColorParameter(imagerF, CSTParam);

	if ( ret_code != 0 ) {
	    return XDW_ERRORCODE_ERROR;
	}
	
	ret_code = HB_AdjustStroke(imagerF, true );

	if ( ret_code != 0 ) {
	    return XDW_ERRORCODE_ERROR;
	}

	return XDW_ERRORCODE_SUCCESS;
};

/*! ページの描画
  ページを描画する．XdwBridgePrintContIF::StartPage()以降の描画を，
  全て，出力デバイスへ出力する．<br>
  Viewer時には，ROP置換コマンドの蓄積中に終了した場合の処理を行う<br>
*/
XdwErrorCode XdwBridgeHBPS::ShowPage( void )
{
	if ( HB_ShowPage( imagerF ) != 0 ) {
		return XDW_ERRORCODE_ERROR;
	};
	return XDW_ERRORCODE_SUCCESS;
};

/*! ページの終了処理を行う．
*/
XdwErrorCode XdwBridgeHBPS::EndPage( void )
{
	if ( HB_EndPage( imagerF, 0 ) != 0 ) {
		return XDW_ERRORCODE_ERROR;
	};
	return XDW_ERRORCODE_SUCCESS;
};

/*! デフォルトとの差分を設定する関数
　　型の定義は出力形式で異なる
*/
XdwErrorCode XdwBridgeHBPS::SetJobInfo( void* jobinfo )
{
	HB_JobParam *jobParamP = (HB_JobParam *)jobParam;
	HB_OutputParam *outParamP = (HB_OutputParam *)outParam;
	HB_SpoolParam *jobSplParamP = (HB_SpoolParam *)jobSplParam;
	BridgeHBPSPrintJobInfo *p = (BridgeHBPSPrintJobInfo *)jobinfo;
	
	if( jobinfo == XdwNull ){
		return XDW_ERRORCODE_ERROR;
	}
	
/* 
XDW2MRC依存
*/

	outParamP->format				= p->out_format;
	outParamP->formatMode			= p->out_formatMode;
	jobParamP->dlSize1				= p->job_dlSize1;
	jobParamP->dlSize2				= p->job_dlSize2;
	jobParamP->rbSize				= p->job_rbSize;
	jobParamP->outputResolutionX	= p->job_outputResolutionX;
	jobParamP->outputResolutionY	= p->job_outputResolutionY;
	jobParamP->inputResolutionX		= p->job_outputResolutionX;
	jobParamP->inputResolutionY		= p->job_outputResolutionY;
	jobParamP->imageResolutionX		= p->job_imageResolutionX;
	jobParamP->imageResolutionY		= p->job_imageResolutionY;
	memcpy(jobParamP->directoryPath, p->job_directoryPath, 260);
	memcpy(jobSplParamP->localFileName, p->spl_localFileName, 260);
	jobSplParamP->localFileNoTruncate = p->spl_localFileNoTruncate;
	jobSplParamP->localFileOffset = p->spl_localFileOffset;
	jobSplParamP->localFileOrigin = p->spl_localFileOrigin;

	patternResolution				= p->patternResolution;

	jobExtraParam					= p->extraParam;
	
	return XDW_ERRORCODE_SUCCESS;
}

/*! デフォルトとの差分を設定する関数
　　型の定義は出力形式で異なる
*/
XdwErrorCode XdwBridgeHBPS::SetPageInfo( void* pageinfo )
{
	HB_PageParam *pageParamP = (HB_PageParam *)pageParam;
	HB_SpoolParam *pageSplParamP = (HB_SpoolParam *)pageSplParam;
	BridgeHBPSPrintPageInfo *p = (BridgeHBPSPrintPageInfo *)pageinfo;
	
	if( pageinfo == XdwNull ){
		return XDW_ERRORCODE_ERROR;
	}

/* 
XDW2MRC依存
*/
	
	pageParamP->colorMode = p->page_colorMode;
	pageParamP->x = p->page_pageWidth;
	pageParamP->y = p->page_pageHeight;
	memcpy(pageSplParamP->localFileName, p->spl_localFileName, 260);
	pageSplParamP->localFileNoTruncate = p->spl_localFileNoTruncate;
	pageSplParamP->localFileOffset = p->spl_localFileOffset;
	pageSplParamP->localFileOrigin = p->spl_localFileOrigin;

  
	pageBoundingBox.LeftTopF.xF = 0; 
	pageBoundingBox.LeftTopF.yF = 0;  
	pageBoundingBox.RightBottomF.xF = p->page_pageWidth;
	pageBoundingBox.RightBottomF.yF = p->page_pageHeight;

	pageExtraParam = p->extraParam;
	
    return XDW_ERRORCODE_SUCCESS;
}

XdwErrorCode  XdwBridgeHBPS::CreateDefaultParameter()
{
	CST_Parameter *CSTParamP;
	HB_JobParam *jobParamP;
	HB_SpoolParam *jobSplParamP, *pageSplParamP;
	HB_OutputParam *outParamP;
	HB_PageParam *pageParamP;

	const unsigned long dlSize1 = 0x800000; /* 8MBytes */
	const unsigned long dlSize2 = 0x400000; /* 4Mbytes	*/
	const unsigned long rbSize  = 0x400000; /* 4Mbytes */
	const long resoX = 600;
	const long resoY = 600;
	const long pageMaxWidth = 10000;
	const long pageMaxHeight = 10000;

	CSTParamP = (CST_Parameter *)malloc(sizeof(CST_Parameter));
	jobParamP = (HB_JobParam *)malloc(sizeof(HB_JobParam));
	jobSplParamP = (HB_SpoolParam *)malloc(sizeof(HB_SpoolParam));
	pageSplParamP = (HB_SpoolParam *)malloc(sizeof(HB_SpoolParam));
	outParamP = (HB_OutputParam *)malloc(sizeof(HB_OutputParam));
	pageParamP = (HB_PageParam *)malloc(sizeof(HB_PageParam));

	CSTParam = (void *)CSTParamP;
	jobParam = (void *)jobParamP;
	jobSplParam = (void *)jobSplParamP;
	pageSplParam = (void *)pageSplParamP;
	outParam = (void *)outParamP;
	pageParam = (void *)pageParamP;


	if(CSTParam == NULL || jobParam == NULL || jobSplParam == NULL || pageSplParam == NULL ||
		outParam == NULL || pageParam == NULL){
    return XDW_ERRORCODE_ERROR;
	}

	/* CST */
	memset( CSTParam, 0, sizeof(CST_Parameter));

	/* jobParam設定 */
	jobParamP->size = sizeof(HB_JobParam);/* 構造体のサイズ */
	jobParamP->dlSize1	= dlSize1;			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ1 */
	jobParamP->dlSize2	= dlSize2;			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ2 */
	jobParamP->rbSize		= rbSize;			/* レンダリング用バッファのサイズ */
	jobParamP->outputResolutionX	= resoX;	/* X方向の出力解像度 */
	jobParamP->outputResolutionY	= resoY;	/* Y方向の出力解像度 */
	jobParamP->inputResolutionX	= jobParamP->outputResolutionX;	/* X方向の入力解像度 */
	jobParamP->inputResolutionY	= jobParamP->outputResolutionY;	/* Y方向の入力解像度 */
	jobParamP->imageResolutionX	= jobParamP->outputResolutionY;	/* X方向のイメージ蓄積解像度 */
	jobParamP->imageResolutionY	= jobParamP->outputResolutionY;	/* Y方向のイメージ蓄積解像度 */
	jobParamP->maxPageSizeX		= pageMaxWidth;/* X方向の最大ページサイズ */
	jobParamP->maxPageSizeY		= pageMaxHeight;/* Y方向の最大ページサイズ */
	memcpy(jobParamP->directoryPath,".\\",3);	/* テンポラリファイルを作成するディレクトリのフルパス名 */
	jobParamP->plex				= HB_PLEX_NULL;	/* 両面印刷指定(HB_PLEX_XXXX参照) */

	/* SpoolParam設定 */
	memset(jobSplParamP, 0, sizeof(HB_SpoolParam));
	jobSplParamP->size = sizeof(HB_SpoolParam);
	memcpy(jobSplParamP->localFileName, "hb_output", 10);

	memset(pageSplParamP, 0, sizeof(HB_SpoolParam));
	pageSplParamP->size = sizeof(HB_SpoolParam);

	/* OutParam設定 */
	memset(outParamP, 0, sizeof(HB_OutputParam));
	outParamP->size = sizeof(HB_OutputParam);
	outParamP->colorMode = 2;   /* always Color */
	outParamP->rndBwColor = 0;   /* GrayW0 */
	outParamP->rndBwBytes = 1;   /* 1    */
	outParamP->rndBwOption = 0;   /* none  */
	outParamP->rndBwOrder = 0;  /* none */
	outParamP->rndClColor = 2;   /* DevRGB */
	outParamP->rndClBytes = 4;   /* 4    */
	outParamP->rndClOption = 2;   /* last */
	outParamP->rndClOrder = 1;   /* BGR  */
	outParamP->esBwDepth = 8;   /* bit / comp */
	outParamP->esBwColor = 0;   /* GrayW0 */
	outParamP->esBwBytes = 1;   /* 1    */
	outParamP->esBwOption = 0;   /* none  */
	outParamP->esBwOrder = 0;  /* none */
	outParamP->esClDepth = 8;   /* bit / comp */
	outParamP->esClColor = 2;   /* DevRGB */
	outParamP->esClBytes = 4;   /* 4    */
	outParamP->esClOption = 2;   /* last */
	outParamP->esClOrder = 1;   /* BGR  */
	outParamP->format = 0;		/* ALLA */
	outParamP->fmtArg = 0;   /* none */
#if 0 /* filter is all ZERO */
	outParamP->filter[0] = 0;   /* none */
	outParamP->filter[1] = 0;   /* none */
	outParamP->filter[2] = 0;   /* none */
	outParamP->filter[3] = 0;   /* none */
	outParamP->fltArg[0] = 0;   /* none */
	outParamP->fltArg[1] = 0;   /* none */
	outParamP->fltArg[2] = 0;   /* none */
	outParamP->fltArg[3] = 0;   /* none */
#endif
	outParamP->compress = 0;   /* none */
	outParamP->compArg = 0;   /* none */
	outParamP->formatMode = 0; /* JOB MODE */

	/* Page設定 */
	pageParamP->size		= sizeof(HB_PageParam);
	pageParamP->colorMode = 2;	/* Color */
	pageParamP->x			= 4000;
	pageParamP->y			= 7000;
	pageParamP->rotation	= 1;	/* rotaionなし	*/
	pageParamP->fWindowX    = pageParamP->x;
	pageParamP->fWindowY    = pageParamP->y;


    return XDW_ERRORCODE_SUCCESS;

}

XdwErrorCode  XdwBridgeHBPS::DeleteDefaultParameter()
{

	if(CSTParam != NULL) {
		free(CSTParam);
		CSTParam = NULL;
	}
	if(jobParam != NULL) {
		free(jobParam);
		jobParam = NULL;
	}
	if(jobSplParam != NULL) {
		free(jobSplParam);
		jobSplParam = NULL;
	}
	if(pageSplParam != NULL) {
		free(pageSplParam);
		pageSplParam = NULL;
	}
	if(outParam != NULL) {
		free(outParam);
		outParam = NULL;
	}
	if(pageParam != NULL) {
		free(pageParam);
		pageParam = NULL;
	}

    return XDW_ERRORCODE_SUCCESS;
}





