/*!
  @file  XdwBridgeColorManager.h
  @brief XdwBridgeColorManager クラスヘッダファイル

  XdwBridgeColorManagerクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-24
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Toshio Yamazaki<br>
  Modifyed:	2002-07-11	Toshio Yamazaki	XdwBridgeGraphicStateColorから変更<br>
 */
#ifndef XDWBRIDGECOLORMANAGER_H_INCLUDED
#define XDWBRIDGECOLORMANAGER_H_INCLUDED

#include "XdwError.h"
#include "XdwColor.h"
#include "XdwBridgeCommon.h"

/*! Bridge内部Color属性管理クラス

  Graphic State内のColor属性の管理を行う抽象クラス．<br>
  XdwBridgeGraphicState classは，Decomposer専用のこのクラスを継承したクラスを生成し，
  全てのColor属性の管理を行う．色変換が必要なDecomposerの場合は，ここで色変換も行う．<br>
  将来，色補正が必要になった場合，このクラスが担当する予定．
 */
class XdwBridgeColorManager {
private:
public:
    XdwBridgeColorManager();		//!< コンストラクタ
    virtual ~XdwBridgeColorManager();	//!< デストラクタ

    /*! 初期化
      XdwBridgeColorManager classとその派生classにおいて，
      動的に生成されるオブジェクトが存在する場合，ここで初期化される．<br>
      メンバ変数の場合はたいていコンストラクタの方で初期化する予定．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
    */
    virtual XdwErrorCode Initialize( void ) = 0;

    /*! 色設定処理
      出力先のDecomposerにForeground色値を設定する
      @param colorspace 色空間
      @param color 整数化された色値
      @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode SetFGColor( const XdwColorSpaceID &colorspace,
				     const XdwTypeUInt32 &color) = 0;

    /*! 色設定処理
      出力先のDecomposerにBackground色値を設定する
      @param colorspace 色空間
      @param color 整数化された色値
      @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    virtual XdwErrorCode SetBGColor( const XdwColorSpaceID &colorspace,
				     const XdwTypeUInt32 &color) = 0;


    /*! 汎用色空間変換処理
      実際の色変換を行う．
      入力・取得される色値は整数化された ( 0x00〜0xff ) 色値である．<br>
      virtualぢゃ無いのは汎用だから．もし，派生クラスで特化した色変換処理が
      ほしい場合は，別に作る予定．
      @param src_colorspace 色空間
      @param src_color 整数化された色値
      @param dst_colorspace 色空間
      @param dst_color 整数化された色値
      @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode Translate( const XdwColorSpaceID *src_colorspace,
			    const XdwTypeUInt32 *src_color,
			    XdwColorSpaceID *dst_colorspace,
			    XdwTypeUInt32 *dst_color);

    /*! 色空間のサポート判定
      Decomposerで色空間がサポートされているか否かを判定する．
      @param colorspace 色空間
      @retval true サポートされている
      @retval false サポートされていない
     */
    virtual bool IsSupportedColorSpace( const XdwColorSpaceID &colorspace ) = 0;
};

class imgImager;	//!< imgImagerクラスの先行宣言

class XdwBridgeColorManagerForGlobe : public XdwBridgeColorManager {
private:
    imgImager		*imagerF;		//!< 出力先
public:
    XdwBridgeColorManagerForGlobe( imgImager *);	//!< コンストラクタ
    ~XdwBridgeColorManagerForGlobe();		//!< デストラクタ

    XdwErrorCode Initialize( void );
    XdwErrorCode SetFGColor( const XdwColorSpaceID &,
			     const XdwTypeUInt32 &);
    XdwErrorCode SetBGColor( const XdwColorSpaceID &,
			     const XdwTypeUInt32 &);


    bool IsSupportedColorSpace( const XdwColorSpaceID & );
};

#endif /* XDWBRIDGECOLORMANAGER_H_INCLUDED */
