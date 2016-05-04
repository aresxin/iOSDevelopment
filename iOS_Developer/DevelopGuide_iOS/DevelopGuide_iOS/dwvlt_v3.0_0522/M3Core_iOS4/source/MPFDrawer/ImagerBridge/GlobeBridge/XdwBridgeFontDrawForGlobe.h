/*!
  @file  XdwBridgeFontDraw.h
  @brief Font描画関連クラスヘッダファイル

  Fontを描画るためのI/Fクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-06-20
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-06-20	Toshio Yamazaki<br>
 */
#include "XdwError.h"
#include "XdwFont.h"
#include "XdwPoint.h"
#include "XdwMatrix.h"

#ifndef XDWBRIDGEFONTDRAW_H_INCLUDED
#define XDWBRIDGEFONTDRAW_H_INCLUDED

/* クラスの先行宣言*/
class XdwBridgeGraphicStateManager;
class XdwBridgeColorManager;

/*! Bridge内部Font描画I/F

  Font描画を行うクラスの抽象(I/F)クラス．<br>
  XdwBridgeGlobe classは，Decomposer専用のこのクラスを継承したクラスを生成し，
  全てのグラフィックス描画を行う．
 */
class XdwBridgeFontDraw {
protected:
    XdwBridgeGraphicStateManager	*gs_managerF;	/*!< GraphicState実体クラス	*/
    XdwBridgeColorManager		*color_managerF;/*!< Color Manager		*/
public:
    /*! コンストラクタ	*/
    XdwBridgeFontDraw(XdwBridgeGraphicStateManager*,
		      XdwBridgeColorManager *);
    virtual ~XdwBridgeFontDraw();			/*!< デストラクタ	*/

    /*! Textの描画
      指定された位置に，指定されたカレントフォントで，Code指定のTextを描画する．
      @param p 描画位置座標値
      @param text 描画するText
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
    */
    virtual XdwErrorCode DrawFont( const XdwPoint &p, const XdwCodeText &text ) = 0;

    /*! Textの描画
      指定された位置に，指定されたカレントフォントで，Data指定のTextを描画する．
      @param p 描画位置座標値
      @param text 描画するText
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
    */
    virtual XdwErrorCode DrawFont( const XdwPoint &p, const XdwDataText &text ) = 0;
};

/* 必要なクラスの先行宣言	*/
class imgImager;
struct _img_string;
class XdwBridgeGDRectangleForGlobe;
class XdwBridgeFontManagerForGlobe;

class XdwBridgeFontDrawForGlobe : public XdwBridgeFontDraw {
private:
    imgImager				*imagerF;	/*!< 出力先		*/
    XdwBridgeGDRectangleForGlobe	*gd_rectangleF;	/*!< 矩形描画先		*/
    XdwBridgeFontManagerForGlobe	*font_managerF;	/*!< Font管理		*/

    _img_string				*work_stringF;	/*!< 作業用		*/
    unsigned char			work_charF[2];	/*!< 作業用		*/
    unsigned char*			work_charptrF;	/*!< 作業用		*/
    double				work_pitchF;	/*!< 作業用		*/

    XdwErrorCode ReSetFontInfo( XdwFontInfo *, unsigned short, XdwPoint * );
    XdwErrorCode ClipFontArea( const XdwCodeText & );
    XdwErrorCode FillFontBGArea( const XdwCodeText & );
    XdwErrorCode GetTextSetHeightInfo( XdwFontInfo *, double *, double *, XdwFontStringModeID );
    double CalcTotalPitchLength( double *, unsigned long );
    XdwErrorCode SetFontAlign( XdwFontInfo *, XdwTextAlign *,
			       double *, double *, const XdwCodeText &, double *, unsigned long );
    XdwErrorCode GeneratePitchArray( XdwFontInfo *, const XdwCodeText &, unsigned long *, double ** );
public:
    XdwBridgeFontDrawForGlobe( imgImager *,
			       XdwBridgeGraphicStateManager*,
			       XdwBridgeColorManager *,
			       XdwBridgeGDRectangleForGlobe *,
			       XdwBridgeFontManagerForGlobe *);
    ~XdwBridgeFontDrawForGlobe();			/*!< デストラクタ	*/

    XdwErrorCode Initialize( void );

    XdwErrorCode DrawFont( const XdwPoint &, const XdwCodeText & );
    XdwErrorCode DrawFont( const XdwPoint &, const XdwDataText & );
};
#endif /* XDWBRIDGEFONTDRAW_H_INCLUDED */
