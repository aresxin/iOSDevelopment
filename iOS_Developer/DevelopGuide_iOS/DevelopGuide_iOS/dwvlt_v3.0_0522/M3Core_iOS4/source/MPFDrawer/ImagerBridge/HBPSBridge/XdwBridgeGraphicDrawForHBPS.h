/*!
  @file  XdwBridgeGraphicDraw.h
  @brief Graphics描画関連クラスヘッダファイル

  グラフィックスを描画するためのI/Fクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-06-05
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-06-05	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEGRAPHICDRAW_H_INCLUDED
#define XDWBRIDGEGRAPHICDRAW_H_INCLUDED

#include "XdwError.h"
#include "XdwGraphicsAttribute.h"
#include "XdwShape.h"
#include "XdwColor.h"

class XdwBridgeGraphicStateManager;
class XdwBridgeColorManager;
#include "XdwBridgePatternDrawForHBPS.h"

/*! Bridge内部Graphic描画I/F

  Graphic描画を行うクラスの抽象(I/F)クラス．<br>
  XdwBridgeHBPS classは，Decomposer専用のこのクラスを継承したクラスを生成し，
  全てのグラフィックス描画を行う．
 */
class XdwBridgeGraphicDraw {
protected:
    XdwBridgeGraphicStateManager	*gs_managerF;		/*!< GraphicState実体クラス	*/
    XdwBridgeColorManager		*color_managerF;	/*!< Color Manager		*/

public:
    /*! コンストラクタ */
    XdwBridgeGraphicDraw(XdwBridgeGraphicStateManager*, XdwBridgeColorManager *);
    /*! デストラクタ */
    virtual ~XdwBridgeGraphicDraw();

    /*! 図形の描画 (Fill or Stroke or FillAndStroke )
      設定された図形形状を，カレントの描画属性に従って描画する．
      @param mode 描画モード (Fill or FillAndStroke or Stroke)
      @retval XDW_ERRORCODE_SUCCESS 正常終了
    */
    virtual XdwErrorCode Draw( const XdwGSDrawMode &mode ) = 0;

    /*! 図形の描画 (Fill)
     * 設定された図形形状を，指定された色情報に従って描画する．
     * @param colorspace	色空間
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode Fill( ) = 0;

    /*! 図形の描画 (Stroke)
     * 設定された図形形状を，指定された色情報に従って描画する．
     * @param colorspace	色空間
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode Stroke( ) = 0;

    /*! Clip領域の描画 (Fillのみ)
     * 設定された図形形状を，カレントの描画属性に従ってClip領域として描画する．
     * @param mode	論理演算モード
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode DrawClip( const XdwGSClipLogic &mode ) = 0;
};

/*! HostBased用Bridge内部Graphic描画共通クラス

  HostBased用のGraphic描画を行うクラス中の，共通の処理を提供するクラス．
 */
class XdwBridgeGDCommonForHBPS {
    void *imagerF;		/*!< 出力先		*/
public:
    XdwBridgeGDCommonForHBPS( void * );	/*!< コンストラクタ	*/
    ~XdwBridgeGDCommonForHBPS();		/*!< デストラクタ	*/

    int ConvertXdwGSClipLogic2rndcliplogic( const XdwGSClipLogic &mode );
};

/*! Bridge内部Rectangle描画I/F

  Bridge内部用のRectangle描画を行うクラスの抽象(I/F)クラス．<br>
  XdwBridgeHBPS classは，Decomposer専用のこのクラスを継承したクラスを生成し，
  全てのグラフィックス描画を行う．
 */
class XdwBridgeGDRectangle : public XdwBridgeGraphicDraw {
protected:
    XdwRectangle	shapeF;			/*!< 描画される矩形	*/
public:
    /*! コンストラクタ	*/
    XdwBridgeGDRectangle(XdwBridgeGraphicStateManager*, XdwBridgeColorManager *);
    /*! デストラクタ	*/
    virtual ~XdwBridgeGDRectangle();
    virtual XdwErrorCode Draw( const XdwGSDrawMode &mode ) = 0;
    virtual XdwErrorCode Fill( ) = 0;
    virtual XdwErrorCode Stroke( ) = 0;
    virtual XdwErrorCode DrawClip( const XdwGSClipLogic &mode ) = 0;
    /*! 矩形の設定
     * 以降の処理対象となる矩形を設定する．
     * @param rect 矩形
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode Set( const XdwRectangle &rect );
    /*! Clip領域の描画 (Fillのみ)
     * 設定された複数の矩形形状を，カレントの描画属性に従って1つのClip領域として描画する．
     *
     * @param rect 矩形のVector
     * @param mode 論理演算モード
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode DrawClip( const XdwRectangleVector &rect, XdwGSClipLogic mode ) = 0;
};

class XdwBridgeGDRectangleForHBPS : public XdwBridgeGDRectangle {
private:
	/*!< 出力先	*/
    void *imagerF;
	XdwBridgePatternDrawForHBPS		*pattern_drawF;

	XdwErrorCode SetDrawMode( XdwGSDrawMode );
	int ConvertDrawMode( const XdwGSDrawMode &);

public:
    /*! コンストラクタ */
    XdwBridgeGDRectangleForHBPS( void *, XdwBridgeGraphicStateManager*, XdwBridgeColorManager *);

    /*! デストラクタ	*/
    ~XdwBridgeGDRectangleForHBPS();

	XdwErrorCode Initialize(XdwBridgePatternDrawForHBPS *);

    XdwErrorCode Draw( const XdwGSDrawMode &mode );
    XdwErrorCode Fill( );
    XdwErrorCode Stroke( );
    XdwErrorCode DrawClip( const XdwGSClipLogic &mode );
    XdwErrorCode DrawClip( const XdwRectangleVector &rect, XdwGSClipLogic mode );
};

#endif /* XDWBRIDGEGRAPHICDRAW_H_INCLUDED */
