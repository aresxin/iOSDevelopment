/*!
  @file  XdwBridgeFontManager.h
  @brief Font管理関連クラスヘッダファイル

  Fontを管理するためのI/Fクラスおよび，各Decomposer用の
  継承クラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-06-12
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-06-12	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEFONTMANAGER_H_INCLUDED
#define XDWBRIDGEFONTMANAGER_H_INCLUDED

#include "XdwError.h"
#include "XdwGraphicsAttribute.h"
#include "XdwFont.h"

class XdwBridgeGraphicStateManager;	/*!< クラスの先行宣言 */

/*! Bridge内部Font管理I/F

  Font管理を行うクラスの抽象(I/F)クラス．<br>
  XdwBridgeGlobe classは，Decomposer専用のこのクラスを継承したクラスを生成し，
  全てのグラフィックス描画を行う．
 */
class XdwBridgeFontManager {
protected:
    XdwBridgeGraphicStateManager	*gs_managerF;		/*!< GraphicState実体クラス	*/

public:
    XdwBridgeFontManager(XdwBridgeGraphicStateManager*);	/*!< コンストラクタ	*/
    virtual ~XdwBridgeFontManager();				/*!< デストラクタ	*/

    /*! カレントフォントのDeviceFontへのMapping
      カレントフォントをDeviceFontへMappingする．
      以後のフォント描画は，指定されたカレントフォントにて描画される<br>
      指定されたフォントが存在しない場合，似たフォントへの置換が実施されるが，
      置換されるフォントが何になるかは実装依存であり，
      クライアントから制御することはできない．<br>
      引数のXdwFontInfo内のDeviceFont情報が書き換えられる.
      @param font カレントフォントを指定する
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
    */
    virtual XdwErrorCode MappingFont( XdwFontInfo &font ) = 0;
    /*! カレントフォントの設定
      カレントフォントを指定する．
      以後のフォント描画は，指定されたカレントフォントにて描画される<br>
      XdwFontInfo内のDeviceFont情報に正しい情報が設定されていなければならない．
      @param font カレントフォントを指定する
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
    */
    virtual XdwErrorCode SetCurrentFont( const XdwFontInfo &font ) = 0;
};

class imgImager;		/*!< imgImagerクラスの先行宣言 */
class imgMatrix32;		/* 先行宣言 */
class XdwBridgeFontTableMapper;	/* 先行宣言 */

class XdwBridgeFontManagerForGlobe : public XdwBridgeFontManager {
private:
    imgImager			*imagerF;	/*!< 出力先					*/
    XdwBridgeFontTableMapper	*mapperF;	/*!< WindowsFontをGlobeへマッピングするテーブル	*/

public:
    XdwBridgeFontManagerForGlobe(imgImager*, XdwBridgeGraphicStateManager*);	/*!< コンストラクタ	*/
    ~XdwBridgeFontManagerForGlobe();				/*!< デストラクタ			*/

    XdwErrorCode Initialize( void );
    XdwErrorCode SetEscOriParameter( XdwFontInfo *font_info );
    XdwErrorCode GenerateFontMatrix( const XdwFontInfo &, imgMatrix32 *, double *, double * );
    XdwErrorCode MappingFont( XdwFontInfo &);
    XdwErrorCode SetCurrentFont( const XdwFontInfo & );
    XdwErrorCode SetEscOriParameter( const XdwFontInfo *, XdwMatrix *, XdwPoint * );
};

#endif /* XDWBRIDGEFONTMANAGER_H_INCLUDED */
