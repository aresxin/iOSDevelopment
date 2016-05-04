/**
 * @file  XdwGraphicsAttribute.h
 * @brief グラフィックス属性関連クラス用ヘッダファイル
 *
 * グラフィックス属性に関する型の宣言やグローバルな関数を提供する．
 * save/restore対象となるグラフィックス属性は基本的にここで定義する．<br>
 * 多分，内部で使うGraphics Stateもここで定義される．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-04	Toshio Yamazaki<br>
 */
#ifndef XDWGRAPHICSATTRIBUTE_H_INCLUDED
#define XDWGRAPHICSATTRIBUTE_H_INCLUDED

/***************************************************/
/*! @name 描画属性定数
 * Bridge全般で用いられる
 */
/***************************************************/
/*@{*/

/*!描画モード
  閉図形がどのように描画されるか指定する．
*/
enum XdwGSDrawMode {
    XDW_GSTATEDM_FILL,		/*!< 塗りつぶしのみ		*/
    XDW_GSTATEDM_STROKE,	/*!< 線描画のみ			*/
    XDW_GSTATEDM_STROKEANDFILL	/*!< 塗りつぶしして線描画	*/
};

/*!塗りつぶしルール
  閉図形がどのように塗りつぶされるか指定する．
*/
enum XdwGSFillRule {
    XDW_GSTATEFR_EO = 1,	/*!< Even-Odd ルール		*/
    XDW_GSTATEFR_NZ,		/*!< Non-Zero ルール		*/
    XDW_GSTATEFR_NE		/*!< Non-Exterior ルール	*/
};

/*!背景描画モード
  背景が適用される描画の場合，どのように背景が描画されるか指定する．
*/
enum XdwGSBackGroundMode {
    XDW_GSTATEBGM_OPAQUE = 2,	  /*!< 背景色が適用される		*/
    XDW_GSTATEBGM_TRANSPARENT = 1 /*!< すでに描画されている背景が残る	*/
};

/*!Raster Operation Mode
  Raster Operation の種別を指定する．
*/
enum XdwGSRopMode {
    XDW_GSTATEROPMODE_2,	/*!< Raster Operation Mode 2	*/
    XDW_GSTATEROPMODE_3,	/*!< Raster Operation Mode 3	*/
    XDW_GSTATEROPMODE_4		/*!< Raster Operation Mode 4	*/
};
/*!Clipping 論理演算モード
  クリッピング領域を指定する際の，論理演算方式の指定．
*/
enum XdwGSClipLogic {
    XDW_GSTATECL_AND = 1,	/*!< カレントクリッピング領域とのAND	*/
    XDW_GSTATECL_COPY = 5,	/*!< カレントクリッピング領域を破棄し，指定されたクリップ領域となる．	*/
    XDW_GSTATECL_DIFF = 4,	/*!< カレントクリッピング領域との差分領域	*/
    XDW_GSTATECL_OR = 2,	/*!< カレントクリッピング領域とのOR	*/
    XDW_GSTATECL_XOR = 3	/*!< カレントクリッピング領域とのXOR	*/
};

/**
 *! ラスター描画の拡縮方法
 */
enum XdwRasterSmoothingMode{
    /*! 残す点の色 AND 除く点の色 */
    XDW_RASTER_SMOOTHING_AND = 1,
    /*! 残す点の色 OR 除く点の色 */
    XDW_RASTER_SMOOTHING_OR,
    /*! 除く点を無視 */
    XDW_RASTER_SMOOTHING_IGONRED,
    /*! 平均色 */
    XDW_RASTER_SMOOTHING_AVERAGE
};

/**
 *! 座標変換モード
 * 内部的にCTMを自動的に設定する
 */
enum XdwTransferMatrixMode{
    /**
     *! 各論理単位を1[pixel]に変換する
     * x軸は右方向,y軸は下方向
     */
    XDW_TRANSFER_MATRIX_TEXT = 1,
    
    /**
     *! 各論理単位を0.1[mm]に変換する
     * x軸は右方向,y軸は上方向
     */
    XDW_TRANSFER_MATRIX_LOMETRIC,

    /**
     *! 各論理単位を0.01[mm]に変換する
     * x軸は右方向,y軸は上方向
     */
    XDW_TRANSFER_MATRIX_HIMETRIC,

    /**
     *! 各論理単位を0.01[inch]に変換する
     * x軸は右方向,y軸は上方向
     */
    XDW_TRANSFER_MATRIX_LOENGLISH,

    /**
     *! 各論理単位を0.001[inch]に変換する
     * x軸は右方向,y軸は上方向
     */
    XDW_TRANSFER_MATRIX_HIENGLISH,

    /**
     *! 各論理単位を1/1440[inch]に変換する
     * x軸は右方向,y軸は上方向
     */
    XDW_TRANSFER_MATRIX_TWIPS,
    
    /**
     *! x軸方向とy軸方向の1単位を等しい値に変換する
     * x軸,y軸の方向は別途指定される
     */
    XDW_TRANSFER_MATRIX_ISOTROPIC,

    /**
     *! x軸方向とy軸方向の単位を任意の尺度に設定する
     * x軸,y軸の方向は別途指定される
     */
    XDW_TRANSFER_MATRIX_ANISOTROPIC
};

/*@}*/

#endif /* XDWGRAPHICSATTRIBUTE_H_INCLUDED */
