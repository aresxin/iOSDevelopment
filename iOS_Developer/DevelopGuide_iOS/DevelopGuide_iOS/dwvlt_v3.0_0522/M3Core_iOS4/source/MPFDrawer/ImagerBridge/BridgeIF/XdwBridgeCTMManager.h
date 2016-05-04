/**
 * @file  XdwBridgeCTMManager.h
 * @brief CTM管理クラス用ヘッダファイル
 *
 * CTM管理クラスの宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-07-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-07-09	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGECTMMANAGER_H_INCLUDED
#define XDWBRIDGECTMMANAGER_H_INCLUDED

#include "XdwError.h"
#include "XdwMatrix.h"
#include "XdwGraphicsAttribute.h"

/*! CTM Manager
 *
 * CTMや座標系の操作と必要なデータをを提供するクラス．
 * 今のところ，XdwBridgeGraphicStateContents内で使われることを想定している．
 * データと操作を一緒にしたから．
 * 
 * Bridgeの座標は，Window座標系->ViewPort座標系->Device座標系
 * の流れで座標系を通り，最終的にDevice座標系へ変換される．
 * ここで，明示されない限り，Bridge I/FはWindow座標系である．<br>
 * XdwBridgeCTMManagerは，指定されるWindow/ViewPort/Device座標系のつじつまを合わせ，
 * Window座標系からDevice座標系へのマッピングマトリクスであるCTMを算出する
 * 処理を提供する．<br>
 * ここで，Window座標系->ViewPort座標系->Device座標系
 * の座標変換を記述するためにはマトリクスが2つ (->の部分が相当するから) 必要
 * であるが，それらの管理はXdwBridgeGraphicStateManagerにて行うことに注意すること．
 */
class XdwBridgeCTMManager {
private:
    /*
     * GDI系のWindow->ViewPort->Deviceの座標変換を表現する
     * Current Matrixを表現するために必要なデータの羅列．
     * 主に，XdwBridgeGraphicStateContentsでのマトリクスデータの実体の保存と，
     * XdwBridgeCTMManager class のメソッドの引数に用いられる.
     * ここにあるのは，定義するのに適当な場所が無かったから.
     */
    XdwMatrix		ctmF;		/*!< Current Transfer Matrix実体*/
    XdwMatrix		win_matF;	/*!< Window Matrix実体		*/
    XdwMatrix		vp_matF;	/*!< ViewPort Matrix実体	*/
    XdwMatrix		dev_matF;	/*!< Device Matrix実体		*/
    XdwMatrix		dev_invmatF;	/*!< Device Invert Matrix実体	*/
    double		window_widthF;	/*!< Window 幅			*/
    double		window_heightF;	/*!< Window 高さ		*/
    double		viewport_widthF;/*!< View Port 幅		*/
    double		viewport_heightF;/*!< View Port 高さ		*/
    double     viewport_xoriginF; /*! View Port origin X */
    double     viewport_yoriginF; /*! View Port origin Y */
    unsigned long	viewport_xdpiF;	/*!< View Port X軸方向DPI値	*/
    unsigned long	viewport_ydpiF;	/*!< View Port Y軸方向DPI値	*/
    double		device_widthF;	/*!< Device Port 幅		*/
    double		device_heightF;	/*!< Device Port 高さ		*/

    XdwErrorCode CalcTransferMatrix(void);
public:
    XdwBridgeCTMManager();
    ~XdwBridgeCTMManager();

    XdwErrorCode GetCTM( XdwMatrix * );
    XdwErrorCode GetWindowInfo( unsigned long *, unsigned long * );
    XdwErrorCode GetViewPortInfo( unsigned long *, unsigned long *,
				  unsigned long *, unsigned long *);

    XdwErrorCode SetCurrentTransferMatrix( const XdwMatrix &dev_mat,
					   unsigned long width, unsigned long height,
					   unsigned long xdpi, unsigned long ydpi );

    XdwErrorCode SetTransferMatrixMode( XdwTransferMatrixMode );
    XdwErrorCode ScaleViewport( const double&, const double & );
    XdwErrorCode ScaleWindow( const double&, const double & );

    XdwErrorCode OffsetViewport( const double&, const double & );
    XdwErrorCode OffsetWindow( const double&, const double & );

    XdwErrorCode ExtentViewport( const double&, const double & );
    XdwErrorCode ExtentWindow( const double&, const double & );
};

#endif /* XDWBRIDGECTMMANAGER_H_INCLUDED */
