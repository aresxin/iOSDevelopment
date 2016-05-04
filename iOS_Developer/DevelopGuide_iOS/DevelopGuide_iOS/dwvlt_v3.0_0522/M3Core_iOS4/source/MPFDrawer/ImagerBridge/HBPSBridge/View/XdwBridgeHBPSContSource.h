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

#if !defined(CXX_DECOMPOSER)
extern "C" {
#include "HB_Decomposer.h"
}
#else
#include "HB_Decomposer.h"
#endif

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

	return XDW_ERRORCODE_SUCCESS;
};

/*!	制御系ブリッジのインスタンスを初期化する
*/
XdwErrorCode XdwBridgeHBPS::InitializeContIF( void )
{
    return XDW_ERRORCODE_SUCCESS;
};
XdwErrorCode XdwBridgeHBPS::InitializeContIF( unsigned short resolutionX, unsigned short resolutionY, long width, long height )
{
	resoX = resolutionX;
	resoY = resolutionY;
	pageWidth = width;
	pageHeight = height;

/*	const unsigned long dlSize1 = 0x3FFFFF; 4MBytes(〜V8) */
	const unsigned long dlSize1 = 0x200000; /* 2MBytes(V8から変更) */
/*	const unsigned long dlSize2 = 0x000000; 0Bytes(メモリ確保しない) */
	const unsigned long dlSize2 = 0x004000; /* 16Kbytes(V16〜)		*/
	const unsigned long rbSize  = 0x020000; /* 128KBytes */

	/* HostBasedImagerの生成 */

	HB_JobParam		jobParam;

	jobParam.size = sizeof(HB_JobParam);/* 構造体のサイズ */
	jobParam.dlSize1	= dlSize1;			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ1 */
	jobParam.dlSize2	= dlSize2;			/* 中間コードの蓄積、及びワーク用に使用するメモリのサイズ2 */
	jobParam.rbSize		= rbSize;			/* レンダリング用バッファのサイズ */
	jobParam.outputResolutionX	= resoX;	/* X方向の出力解像度 */
	jobParam.outputResolutionY	= resoY;	/* Y方向の出力解像度 */
	jobParam.inputResolutionX	= resoX;	/* X方向の入力解像度 */
	jobParam.inputResolutionY	= resoY;	/* Y方向の入力解像度 */
	jobParam.imageResolutionX	= resoX;	/* X方向のイメージ蓄積解像度 */
	jobParam.imageResolutionY	= resoY;	/* Y方向のイメージ蓄積解像度 */
	jobParam.maxPageSizeX		= pageWidth;/* X方向の最大ページサイズ */
	jobParam.maxPageSizeY		= pageHeight;/* Y方向の最大ページサイズ */
#if 0 /* HB-V19 */
	jobParam.directoryPath		= ".\\";	/* テンポラリファイルを作成するディレクトリのフルパス名 */
#else
	memcpy(jobParam.directoryPath, ".\\", 3);
#endif
	jobParam.plex				= HB_PLEX_NULL;	/* 両面印刷指定(HB_PLEX_XXXX参照) */

#if 0 /* HB-V19 */
	imagerF = HB_Initialize( &jobParam, 0, 0, 0 );
#else
	imagerF = HB_Initialize( &jobParam, 0, 0, 0, 0, 0 );
#endif

    if ( imagerF == (void*)XdwNull ) {
		return XDW_ERRORCODE_INVALID_PARAMETER;
    };

	/* ジョブの開始

		パターンモード:	 HB_PATTERN_IGNORE_CTM = 0
						HB_PATTERN_APPLY_CTM = 1
						HB_PATTERN_ROTATION_ONLY = 2 */
	if ( HB_StartJob( imagerF, 2 ) != 0 ) {
		return XDW_ERRORCODE_ERROR;
	};
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
	if ( HB_SetPatternResolution( imagerF, resoX ) != 0 ) {
		return XDW_ERRORCODE_ERROR;
	};
	if ( HB_SetRasterSmoothingMode( imagerF, 1, 0 ) != 0) {
		return XDW_ERRORCODE_ERROR;
	};

    // MRC対応
    // 現在のBridgeではHB_DrawImageMask()が呼ばれるのは
    // MRC画像処理だけなので, Mask描画は常に補間ONにする
    if (HB_SetMaskSmoothingMode(imagerF, 1, 0 ) != 0) {
        return XDW_ERRORCODE_ERROR;
    }

    /* 必要なオブジェクトを生成し初期化する		*/
	if( NewObject() != XDW_ERRORCODE_SUCCESS){
		return XDW_ERRORCODE_ERROR;
	};
    return XDW_ERRORCODE_SUCCESS;
};

/*! BoundingBoxのセット
*/
XdwErrorCode XdwBridgeHBPS::SetBoundingBox( const XdwRectangle &rect )
{
	XdwErrorCode ret_code = XDW_ERRORCODE_SUCCESS;

	/* 入力されたBoundingBoxを保存する */
	pageBoundingBox = rect;

	/* 初期化後にBoundingBoxがセットされる */
    return InitClip();
};

/*! オフスクリーンクラスにイメージャーをセットしてスタートページをコールしてもらう
*/

/*	AR1170 (オフスクリーン切替時のImager終了処理は呼び出し側で行う)
XdwErrorCode XdwBridgeHBPS::SetOffScreen( XdwOffScreen* off_screen, bool change_flag ) */
XdwErrorCode XdwBridgeHBPS::SetOffScreen(XdwOffScreen* off_screen)
{
    /* オフスクリーンの切り替えかのチェック */
/*	if(change_flag == true){
		if ( HB_ShowPage( imagerF ) != 0 ) {
			return XDW_ERRORCODE_ERROR;
		};
		if ( HB_EndPage( imagerF ) != 0 ) {
			return XDW_ERRORCODE_ERROR;
		};
	};
*/
    /* Decomposerにオフスクリーンをセット */
	if( off_screen->SetToDecomposer( imagerF ) != 0 ){
		return XDW_ERRORCODE_ERROR;
	};

    return XDW_ERRORCODE_SUCCESS;
};

/*! ジョブの開始
*/
XdwErrorCode XdwBridgeHBPS::StartJob( void )
{
	/* 現在ImagerのStartJobはInitializeContIFから直接呼ばれる */
    return XDW_ERRORCODE_NOT_IMPLEMENTED;
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
    // 明示的にTerminate()を呼ばれた後に,
    // デストラクタからTerminate()が呼ばれた際に
    // imagerFがNULLのままShowPage()が呼ばれないように
    // するためのチェック
    if (imagerF == (void*) 0) {
        return XDW_ERRORCODE_SUCCESS;
    }

	if ( ShowPage() != XDW_ERRORCODE_SUCCESS ) {
		return XDW_ERRORCODE_ERROR;
	};
	if ( EndPage() != XDW_ERRORCODE_SUCCESS ) {
		return XDW_ERRORCODE_ERROR;
	};
	if(imagerF != (void *)XdwNull){
		if ( HB_EndJob( imagerF ) != 0 ) {
			return XDW_ERRORCODE_ERROR;
		};
		if ( HB_Finalize( imagerF ) != 0 ) {
			return XDW_ERRORCODE_ERROR;
		};
		imagerF = (void *)XdwNull;
	};
    return XDW_ERRORCODE_SUCCESS;
};

/*!	StartPage
*/
XdwErrorCode XdwBridgeHBPS::StartPage(  int reso_x, int reso_y, long x, long y, unsigned char *pageBuffer, long lineSize, void *DC)
{
	/* 現在	ImagerのStartPageはOffScreenから直接呼ばれる */
    return XDW_ERRORCODE_NOT_IMPLEMENTED;
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


