/*!
  @file  XdwBridgeSkiaImpl.h
  @brief Bridge Draw関連I/Fクラスヘッダファイル

  各種DecomposerのI/Fを隠蔽し，描画関連のI/F機能を提供する．
 */
#ifndef XDWBRIDGESKIAIMPL_H_INCLUDED
#define XDWBRIDGESKIAIMPL_H_INCLUDED

#include "System/SystemIF/XdwError.h"
#include "System/SystemIF/XdwConfig.h"

/* 他のファイルに定義されているデータ類 */
#include "XdwBridgeCommon.h"
#include "XdwMatrix.h"
#include "XdwGraphicsAttribute.h"
#include "XdwPoint.h"
#include "XdwShape.h"
#include "XdwFont.h"
#include "XdwRaster.h"
#include "XdwPen.h"

#include "DataObject/Include/XdwDataObject.h"

/* インターフェースの定義のためのIncludeファイル */
#include "ImagerBridge/BridgeIF/XdwBridgeDrawIF.h"
#include "ImagerBridge/BridgeIF/XdwBridgeViewerContIF.h"
#include "ImagerBridge/DebugBridge/XdwLogInterface.h"
#include "Viewer/OffScreen/Android/Header/XdwOffScreenDIB.h"

// Jonah add this header XdwBridgeGraphicStateManager
#include "ImagerBridge/BridgeIF/XdwBridgeGraphicStateManager.h"

#include "SkCanvas.h"
#include "SkBitmap.h"

#include "skiabridgeheader.h"

/* ログ出力用インターフェースの宣言 */
class XdwLogInterface;

/* Bridge I/Fにて定義される共通クラスの先行宣言 */
//class XdwBridgeGraphicStateManager;
class XdwBridgeObjectFont;
class XdwBridgeObjectBrush;
class XdwBridgeObjectPen;
class XdwBridgeObjectPattern;
class XdwBridgeObjectPalette;

typedef struct
{
	float a;
	float b;
	float c;
	float d;
	float tx;
	float ty;
} Skia_Matrix;

#ifdef _SKIA_INT_POINT_
typedef SkIPoint Skia_Point;
#else
typedef SkPoint Skia_Point;
#endif

class XdwOffScreen;

/*! 描画関連の各種Decomposer用BridgeI/Fクラス

  Globe Decomposr, HBPS Decomposer等の仕様の違いを吸収し，
  描画に関する共通化されたDecomposer I/Fをクライアントに提供する，Bridgeクラス．
  抽象クラスなので，クライアントは具象クラスを生成して，それを使用する．
  ただし，具象クラスはこのクラスと制御系のBridgeI/Fクラスとの多重継承にしなければならない．<br>
  <br><b>クリッピング</b><br>
  全ての描画は，カレントクリッピング領域において，
  クリッピングされる．<br>
  <br><b>描画色</b><br>
  全ての描画は，Pen色かBrush色により描画される．
  主に，Stroke系はPen色で描画され，Fill系はBrus色で描画される．<br>
  @attention Bridge I/F上における次元は全てユーザー空間であり，
  明示的に指定しない限り，デバイス空間にはならない．
  つまり，全ての色値は色空間とペアで設定され，Bridge内部 (実際はImager)
  でデバイス色空間に変換され，全ての座標値・ベクトルはCTMによりデバイス座標系に
  変換される．したがって，明示的に色空間・座標系をデバイス座標系に設定しない限り，
  クライアントはデバイス空間で値を設定することはできない．
  @attention Bridge classは，ポインタにより渡された，クライアント側で動的確保
  されたメモリ領域を開放することは決してない．Bridge classがFreeするのは，
  Bridge classが動的確保したメモリ領域のみである．
  @attention 基本的に引数として渡したオブジェクトの内部変数は変更されない．
  変更されるI/Fに関は，I/Fにその旨記載する．
 */
class XdwBridgeSkia : public XdwBridgeDrawIF, public XdwBridgeViewerContIF {
public:
	SkCanvas *m_pcanvas;

    Skia_Matrix	m_skia_mat;

	XdwBridgeGraphicStateManager	*gstateF;	/*!< GraphicState管理クラス	*/

	SkPaint m_paint;

	SkPath m_path;

    SkRect m_rect;

	//SkDevice *m_device;

	XdwErrorCode m_retCode;

	Skia_Matrix m_matrix;

	Skia_Point m_skiapoint;

    /*! Logファイルを記述するためのインターフェース */
    XdwLogInterface* fXdwLogInterface;

    XdwTransferMatrixMode m_preMatrixMode;

    XdwTypeUInt32 m_rop2Code;
    XdwTypeUInt32 m_rop3Code;

    SkPaint m_penObject;
    SkPaint m_brushObject;

    int path_state;

    XdwGSDrawMode m_drawmode;
    // Save bounding box
    XdwRectangle m_pageBoundingBox;

    /*
	resolutionX	x方向解像度<br>
	resolutionX	y方向解像度<br>
	width		x方向オフスクリーンサイズ<br>
	weight		y方向オフスクリーンサイズ<br>
	*/

    unsigned short mResoX;
    unsigned short mResoY;
    long mPageWidth;
    long mPageHeight;

    float m_assitScale; /* the value is skbitmap width(height) / real width(height)*/
public:
    /*! コンストラクタ
      コンストラクタでは，動的メモリの確保は行われない．
      ただし，ポインタのNULL初期化は行われる．
     */
    XdwBridgeSkia();
    /*! デストラクタ
      XdwBridgeが動的に確保したメモリ領域のみFreeされる．
      他のクラスにおいて生成したと思われる領域のFreeは行わない．
     */
    virtual ~XdwBridgeSkia();

	/*!< 初期化メソッド */
    XdwErrorCode Initialize(XdwLogInterface *);

    /***************************************************/
    /*! @name 初期化I/F
     * 描画関連の初期化を行うI/Fである．
     */
    /***************************************************/
    /*@{*/
    /*!初期化メソッド
      プライベートメンバ変数を初期化し，プライベートメンバ変数を設定する．
      クライアントは必ずこのメソッドを呼ばなければならない．<br>
      また，動的確保されるメモリ領域は，このメソッドが呼ばれることにより，
      初めて確保されるので，クライアントはこのメソッドを呼ぶことにより，
      XdwBridgeクラス生成時のエラーを判定する．<br>
      必要であれば，Bridge以下のクラス (Imagerモジュール等) に対して，
      初期化を実行する．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
      @attention 渡されるポインタが何であるかは具象クラスに依存する．
      @attention 初期化されたパラメータ値はXdwBridgeDrawIF::InitializeDrawParameter()と等しくなる．
     */
    XdwErrorCode InitializeDrawIF( void );

    /*! パラメータの初期化
      パラメータの初期化を行う．XdwBridgeDrawIF::InitializeDrawIF()が呼ばれた際にも，
      内部から呼ばれる．
      <center>
      <br>初期化されるパラメータの値<br><br>
      <table>
          <tr><td><center>パラメータ名</center></td><td><center>値</center></td><td><center>注釈</center></td></tr>
          <tr><td>色空間</td><td>XDW_COLORSPACEID_RGB</td><td>デフォルトはRGB</td></tr>
          <tr><td>Foreground色値</td><td>黒 (0x00000000)</td><td>暫定</td></tr>
          <tr><td>Background色値</td><td>白 (0xFFFFFFFF)</td><td>暫定</td></tr>
          <tr><td>背景描画モード</td><td>XDW_GSTATEBGM_OPAQUE</td><td>暫定</td></tr>
          <tr><td>Pen色</td><td>Solid Color and Foreground色値</td><td>暫定</td></tr>
          <tr><td>Brush色</td><td>Solid Color and Background色値</td><td>暫定</td></tr>
          <tr><td>Current Transfer Matrix </td><td>システム依存</td><td>ただし，拡縮無しでデバイス空間と一致する</td></tr>
          <tr><td>線幅</td><td>1.0</td><td>ユーザー空間における線幅</td></tr>
          <tr><td>Pen Type</td><td>XDW_PENSTYLE_SOLID (実線)</td><td>暫定</td></tr>
          <tr><td>Join Type</td><td>XDW_JOINTYPE_MITER</td><td>暫定</td></tr>
          <tr><td>Cap Type</td><td>XDW_JOINTYPE_BUTT</td><td>暫定</td></tr>
          <tr><td>Cliping領域</td><td>デバイス上ページのBounding Box</td><td>暫定</td></tr>
          <tr><td>Cliping Logic</td><td>XDW_GSTATECL_AND</td><td>暫定</td></tr>
          <tr><td>ROP Mode and Code</td><td>Mode 2, COPY</td><td>暫定</td></tr>
          <tr><td>Fill Rule</td><td>Even-Odd</td><td>暫定</td></tr>
          <tr><td>Fill Mode</td><td>Fill</td><td>暫定</td></tr>
      </table>
      </center>
      <br>
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
     */
    XdwErrorCode InitializeDrawParameter( void );
    /*@}*/

    /***************************************************/
    /*! @name 描画オブジェクト系I/F
     * 描画オブジェクト(フォント、ペン、ブラシ)の設定をI/Fである。
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief 描画オブジェクト(フォント、ペン、ブラシ)を選択する
     *
     * 描画オブジェクトのカレントの描画属性として選択する
     * @param handle 選択される描画オブジェクトのハンドル
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode SelectObject( const unsigned long& handle );

    /**
     * @brief 描画オブジェクト(フォント、ペン、ブラシ、パレット)を削除する
     *
     * 指定された描画オブジェクトを完全に破棄する
     * @param handle 削除する描画オブジェクトのハンドル
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode DeleteObject( const unsigned long& handle );

    /*@}*/

    /***************************************************/
    /*! @name Font系I/F
     * Fontの制御を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief フォントを作成する
     *
     * 以後のフォント描画は，作成されたフォントのハンドルを
     * XdwBridgeDrawIF::SelectObject()メソッドで選択しなければ、有効ではない。<br>
     * 指定されたフォントが存在しない場合，似たフォントへの置換が実施されるが，
     * 置換されるフォントが何になるかは実装依存であり，
     * クライアントから制御することはできない．
     * @param font 作成するフォントの属性
     * @param handle 作成されたフォントのハンドル
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode CreateFont( const XdwFontInfo &font ,
                                     unsigned long& handle );

    /**
     * @brief Font Alignの設定
     *
     * カレントFontAlignを指定する．
     * 以後のText(フォント)描画は，指定されたAlignによって描画矩形内で整列する．
     * @param align カレントTextAlignを指定する
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode SetFontAlign( XdwTextAlign align );

    /**
     * @brief Font Extraの設定
     *
     * 現在選択されているフォントに対して文字間隔を設定する。<br>
     * 1行のテキストを描画する場合、各文字に対して、文字間隔が追加される
     * @param extra 各文字に追加するスペースの大きさ
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode SetFontExtra( const long& extra );

    /**
     * @brief 文字列中の区切り文字に対するスペースの大きさの設定
     *
     * @param extra 出力される行に追加する合計スペース量
     * @param count 行に含まれる区切り文字数
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode SetFontJustification( const long& extra,
                                               const long& count );

    /*@}*/

    /***************************************************/
    /*! @name Pattern 設定系I/F
     * Pattern設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief パターン(ペン,ブラシ)のオフセットの設定
     *
     * @param offset オフセット
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetPatternOffset( const XdwPoint &offset );

    /*@}*/

    /***************************************************/
    /*! @name Pen属性系I/F
     * Pen属性の設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief ペンを作成する
     *
     * 以後のStroke描画は，作成されたペンのハンドルを
     * XdwBridgeDrawIF::SelectObject()メソッドで選択しなければ、有効ではない。<br>
     * Strokeによって描画されるPen (線) の属性を全て設定する．
     * @param para Pen属製
     * @param pattern Stroke時の描画パターン
     * @param image image属性<br>
     *              ラスタパターンのペンで場合は、無視される
     * @param imagedata imageデータ<br>
     *                  ラスタパターンのペンでない場合は、無視される
     * @param offset imageデータまでのオフセット<br>
     * @param size imageデータのサイズ<br>
     * @param handle 作成されたペンのハンドル
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @attention imagedataが示すImageの実体は変更されないが，
     *            XdwDataObject::Binaryの内部状態は変更される
     */
    XdwErrorCode CreatePen( const XdwPenAttribute &para ,
                                    const XdwPatternAttribute &pattern,
                                    const XdwRasterImageAttribute &image,
                                    XdwDataObject::Binary *imagedata,
                                    const long& offset,
                                    const long& size,
                                    unsigned long& handle );

    /**
     * @brief マイター制限値の設定
     *
     * @param limit マイター制限値
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode SetMiterLimit( double limit );

    /*@}*/

    /***************************************************/
    /*! @name Brush属性系I/F
     * Brush属性の設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief ブラシの作成
     *
     * 以後のFill描画は，作成されたブラシのハンドルを
     * XdwBridgeDrawIF::SelectObject()メソッドで選択しなければ、有効ではない。<br>
     * Fillによって描画されるBrush (塗りつぶし) の属性を全て設定する．
     * @param pattern Fill時の描画パターン
     * @param image image属性<br>
     *              ラスターパターンのブラシ以外は無視される
     * @param imagedata imageデータ<br>
     *                  ラスターパターンのブラシ以外は無視される
     * @param offset imageデータまでのオフセット<br>
     * @param size imageデータのサイズ<br>
     * @param handle 作成されたブラシのハンドル
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @attention imagedataが示すImageの実体は変更されないが，
     *            XdwDataObject::Binaryの内部状態は変更される
     */
    XdwErrorCode CreateBrush( const XdwPatternAttribute &pattern,
                                      const XdwRasterImageAttribute &image,
                                      XdwDataObject::Binary *imagedata,
                                      const long& offset,
                                      const long& size,
                                      unsigned long& handle );

    /*@}*/

    /***************************************************/
    /*! @name 色属性系I/F
     * 色関連属性の設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief Foreground整数色値の設定
     *
     * Foregroundに描画されるオブジェクトの色値(フォント,マスクパターン)を指定する．
     * @param colorspace 色空間
     * @param color 整数化された色値<br>
     *              色空間がXDW_COLORSPACEID_RGBの場合には、0x00RRGGBBである
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetFGColor( const XdwTypeUInt32 &color,
                                     XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );
    /**
     * @brief Background整数色値の設定
     *
     * Backgroundに描画されるオブジェクトの色値を指定する．
     * @param colorspace 色空間
     * @param color 整数化された色値<br>
     *              色空間がXDW_COLORSPACEID_RGBの場合には、0x00RRGGBBである
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetBGColor( const XdwTypeUInt32 &color,
                                     XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );

    /*@}*/

    /***************************************************/
    /*! @name Palette 設定系I/F
     * Palette設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief Paletteの作成
     *
     * 以後の描画は、作成したパレットのハンドルを
     * XdwBridgeDrawIF::SelectPalette()メソッドで選択しなければ、有効ではない。<br>
     * @param palette パレット
     * @param handle ハンドル
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode CreatePalette( const XdwColorPalette &palette,
                                        unsigned long& handle );

    /**
     * @brief パレットを選択する
     *
     * パレットをカレントのパレットとして選択する
     * @param handle 選択されるパレットのハンドル
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode SelectPalette( const unsigned long &handle );

    /**
     * @brief Paletteのエントリへの色値設定
     *
     * カレントパレットの指定されたエントリへ色値を設定する．
     * カレントパレットの色空間に合う色値を設定しなければならない．
     * @param handle パレットオブジェクトハンドル
     * @param position パレットエントリ位置
     * @param color 色値の配列
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetPaletteEntries( const unsigned long& handle,
                                            const long &position,
                                            const XdwUInt32Vector &color );

    /**
     * @brief Paletteサイズの変更
     *
     * カレントパレットサイズを変更する．サイズが小さくなる場合は，
     * 後ろから (エントリの大きいほうから) 削除される．
     * サイズが大きくなる場合は，後ろ (エントリの大きい側へ) へ追加される．
     * 追加されたパレットの色値は，色空間において一番暗くて彩度が低い色値
     * (例えば黒)になることが期待されるが，基本的に不定．
     * @param handle 変更するパレットのハンドル
     * @param entries 変更後のエントリー数
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode ResizePalette( const unsigned long& handle,
                                        const long &entries );

    /**
     * @brief カレントパレットの更新
     *
     * 現在選択されているパレットをシステムのパレットとして、更新する<br>
     * システムがTrueColorの場合は、無視される
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode RealizePalette( void );

    /*@}*/

    /***************************************************/
    /*! @name 座標系I/F
     * 座標形の設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief カレント座標変換Matrixの設定
     *
     * BridgeI/Fの座標系 (ユーザー座標系) からデバイスの座標系へ
     * 変換するMatrixを設定する．
     * @param matrix 変換マトリクス
     * @param width 設定された座標系の幅
     * @param height 設定された座標系の高さ
     * @param xdpi 設定された座標系のx方向DPI値
     * @param ydpi 設定された座標系のy方向DPI値
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetCurrentTransferMatrix( const XdwMatrix &matrix,
						   unsigned long width,
						   unsigned long height,
						   unsigned long xdpi,
						   unsigned long ydpi );

    /**
     * @brief CTMを設定する
     *
     * @param mode XdwTransferMatrixModeを参照
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetTransferMatrixMode( XdwTransferMatrixMode mode );

    /**
     * @brief Viewportの表示範囲の拡縮指定
     *
     * Viewportの座標系の表示範囲を拡大or縮小する．
     * CTMは，引数の拡縮小率を乗算したMatrixとなる．
     * @param xscale x軸方向の拡縮値 (%指定ぢゃない)
     * @param yscale y軸方向の拡縮値 (%指定ぢゃない)
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode ScaleViewport( const double &xscale,
                                        const double &yscale );

    /**
     * @brief Viewportの座標系の平行移動指定
     *
     * Viewportの座標系を，平行移動する．<br>
     * CTMは，引数の平行移動成分を加えたMatrixとなる．<br>
     * (指定値はユーザー座標系値なので，実際はデバイス座標系に変換された値になる)
     * @param x x軸方向の平行移動量
     * @param y y軸方向の平行移動量
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode OffsetViewport( const double &x,
                                         const double &y );

    /**
     * @brief Viewportの座標系の表示範囲指定
     *
     * Viewportの座標系を，表示範囲を指定する<br>
     * XdwBridgeDrawIF::SetTransferMatrixMode()で
     * XDW_TRANSFER_MATRIX_ISOTROPIC or XDW_TRANSFER_MATRIX_ANISOTROPICを指定していない場合は無視される<br>
     * 軸方向も指定される?
     * @param width x軸方向の表示範囲
     * @param height y軸方向の表示範囲
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode ExtentViewport( const double &width,
                                         const double &height );

    /**
     * @brief Windowの表示範囲の拡縮指定
     *
     * Windowの座標系の表示範囲を拡大or縮小する．
     * CTMは，引数の拡縮小率を乗算したMatrixとなる．
     * @param xscale x軸方向の拡縮値 (%指定ぢゃない)
     * @param yscale y軸方向の拡縮値 (%指定ぢゃない)
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode ScaleWindow( const double &xscale,
                                      const double &yscale );

    /**
     * @brief Windowの座標系の平行移動指定
     *
     * Windowの座標系を，平行移動する．<br>
     * CTMは，引数の平行移動成分を加えたMatrixとなる．<br>
     * (指定値はユーザー座標系値なので，実際はデバイス座標系に変換された値になる)
     * @param x x軸方向の平行移動量
     * @param y y軸方向の平行移動量
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode OffsetWindow( const double &x,
                                       const double &y );

    /**
     * @brief Windowの座標系の表示範囲指定
     *
     * Windowの座標系を，表示範囲を指定する<br>
     * XdwBridgeDrawIF::SetTransferMatrixMode()で
     * XDW_TRANSFER_MATRIX_ISOTROPIC or XDW_TRANSFER_MATRIX_ANISOTROPICを指定していない場合は無視される<br>
     * 軸方向も指定される?
     * @param width x軸方向の表示範囲
     * @param height y軸方向の表示範囲
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode ExtentWindow( const double &width,
                                       const double &height );

    /*@}*/

    /***************************************************/
    /*! @name 描画属性系I/F
     * 描画属性の設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief 塗りつぶしルールの設定
     *
     * 閉図形がどのように塗りつぶされるか指定する．
     * @param rule 塗りつぶしルール
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetFillRule( XdwGSFillRule rule );

    /**
     * @brief ラスター描画の拡縮方法の設定
     *
     * 解像度が大きい場合には、無視される
     * @param mode 拡縮方法
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetRasterSmoothingMode( XdwRasterSmoothingMode mode );

    /**
     * @brief 背景描画の設定
     *
     * 背景が適用される描画の場合，どのように背景が描画されるか指定する．
     * @param mode 背景モード
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetBackGroundMode( XdwGSBackGroundMode mode );

    /**
     * @brief 巻き方向の設定
     *
     * 円弧系の図形において，その図形の巻き方向を指定する．
     * @param mode 巻き方向
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetWiseMode( XdwArcWiseMode mode );

    /**
     * @brief Raster Operation Codeの設定
     *
     * Raster Operation Code (ROP) を設定する．
     * 以下の描画は，ROPコードが適用された描画となる．<br>
     * ROP Mode 3〜4は，Raster Image描画が必須となるため，
     * Raster Image属性側に付加され，このI/Fで有効なのは，
     * ROP Mode 2のみである．
     * @param ropmode Raster Operation Mode
     * @param ropcode Raster Operation Code (MSDNの定義と同じ)
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetRopMode( XdwGSRopMode ropmode,
                                     XdwTypeUInt32 ropcode );

    /**
     * @brief 属性の保存
     *
     * カレント属性を“全て”スタック上へ積む．
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode Save( void );

    /**
     * @brief 属性の復帰
     *
     * スタック上に積まれているカレント属性を設定し，
     * スタックの一番上の属性を破棄する．
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode Restore( void );

    /*@}*/

    /***************************************************/
    /*! @name Clip系I/F
     * Clipの設定を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief 矩形クリッピング領域の指定
     *
     * 矩形のクリッピング領域を指定する．指定された後のクリッピング領域は，
     * カレントクリッピング領域との間にmodeで指定された論理演算を行った後の領域となる．
     * @param rect 矩形
     * @param mode 論理演算モード
	 * @param device_unit 矩形座標値指定がデバイス座標系かどうか (true: デバイス座標系, false: ユーザー座標系)
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
	XdwErrorCode SetRectangleToClip(const XdwRectangleVector& rect, XdwGSClipLogic mode, bool device_unit = false);

    /**
     * @brief カレントパスをクリッピング領域へ設定する．
     *
     * カレントパスをクリッピング領域へ設定する．指定された後のクリッピング領域は，
     * カレントクリッピング領域との間にmodeで指定された論理演算を行った後の領域となる．
     * @param mode 論理演算モード
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetPathToClip( XdwGSClipLogic mode );

    /**
     * @brief カレントクリップ領域を平行移動する．
     *
     * カレントクリップ領域平行移動する．指定されるオフセット値はユーザー座標系である．
     * @param offset 移動量
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode OffsetClip( const XdwPoint &offset );

    /*@}*/

    /***************************************************/
    /*! @name Path構築系I/F
     * Pathの設定，構築を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief カレントポイントを設定する
     *
     * カレントポイントを設定し，新たなサブパスの構築を開始する．
     * 構築中であったパスは開いたサブパスとなって，カレントパスに残る．<br>
     * 動作は，PostScriptのmovetoと同一．
     * @param p カレントポイント
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode SetCurrentPoint( const XdwPoint &p );

    /**
     * @brief カレントパスを閉じる
     *
     * カレントパスを閉じてパス構築を終了する．<br>
     * 動作は，PostScriptのclosepathと同一．
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode ClosePath( void );

    /**
     * @brief カレントパスの設定を開始する
     *
     * 以降、Graphics描画系のメソッドおよびFont描画系のメソッドが
     * カレントパスに登録される<br>
     * 本メソッドを発行された場合に、カレントパスはいったん初期化される
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode BeginPath( void );

    /**
     * @brief カレントパスの設定を終了する
     *
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode EndPath( void );

    /*@}*/

    /***************************************************/
    /*! @name Graphics描画系I/F
     * Graphicstの描画を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief 線分集合の描画
     *
     * 線分の集合を，カレントの描画属性にしたがってStrok描画を行う．<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * パス構築のために使用される
     * @param p 座標値Vector<br>
     *          頂点の集合の意
     * @param update 現在位置の参照/更新の有無
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawLineSet( const XdwPointVector &p,
                                      bool update );

    /**
     * @brief 多角形の描画
     *
     * 多角形を，カレントの描画属性にしたがってStrok And Fill描画を行う．<br>
     * 自動的に閉じる<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * パス構築のために使用される
     * @param p 座標値Vector<br>
     *          頂点の集合の意
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawPolygon( const XdwPointVector &p );

    /**
     * @brief Bezer線分集合の描画
     *
     * Bezier線分の集合を，カレントの描画属性にしたがってStrok描画を行う．<br>
     * 現在位置を更新しない場合は、
     * Bezierデータの最初の座標点(1番目の)を始点として，2,3番目を制御点，
     * 4番目を終点として，最初のBezier線分を取得する．<br>
     * 以降のBezier線分は直前のBezier線分の終点を始点とし，続く2つの制御点，
     * 1つの終点を取得してBezier線分とする．<br>
     * つまり，最初のBezier線分のみ4点必要であり，
     * 以降のBezier線分は3点必要である．<br>
     * したがって，座標値数は，Bezier線分数×3＋1で
     * なければならない．<br>
     * 現在位置を更新する場合は、
     * Bezierデータの現在位置を始点として，1,2番目を制御点，
     * 3番目を終点として，最初のBezier線分を取得する．<br>
     * 以降のBezier線分は直前のBezier線分の終点を始点とし，続く2つの制御点，
     * 1つの終点を取得してBezier線分とする．<br>
     * したがって，座標値数は，Bezier線分数×3でなければならない．<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * パス構築のために使用される
     * @param p 座標値のVector．頂点の集合の意
     * @param update 現在位置の参照/更新の有無
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawBezierSet( const XdwPointVector &p,
                                        bool update );

    /**
     * @brief 楕円図形の描画
     *
     * 楕円図形を，カレントの描画属性にしたがってStrok描画またはStrok And Fill描画を行う．<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * パス構築のために使用される
     * @param shape 描画する楕円図形
     * @param mode 描画方法
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawEllipse( const XdwEllipse& shape,
                                      XdwGSDrawMode mode );

    /**
     * @brief 矩形の描画
     *
     * 矩形を，カレントの描画属性にしたがってStrok And Fill描画を行う．<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * パス構築のために使用される
     * @param shape 描画する矩形集合のVector
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawRectangle( const XdwRectangle &shape );

    /**
     * @brief 矩形集合の描画
     *
     * 矩形集合を，カレントの描画属性にしたがってFill描画する．<br>
     * @param ropMode ROPモード，3〜4のみ
	 * @param nrect 全矩形数
	 * @param nbocks ブロック数
	 * @param startY 最初の矩形の左上点のY座標
	 * @param lines ライン数
	 * @param colums 列数
	 * @param height 矩形群の高さ
	 * @param x num個の描画開始点のX座標
	 * @param width num個の矩形の幅
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawPolyPolyPatBlt( XdwGSRopMode ropMode, XdwTypeUInt32 ropCode,
											 short nrect, short blocks, short startY,
											XdwShortVector	&lines,	XdwShortVector	&colums,
											XdwShortVector	&height, XdwShortVector	&x,	XdwShortVector &width );

    /**
     * @brief 円弧の描画
     *
     * 円弧図形を，カレントの描画属性にしたがってStrok描画を行う．<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * パス構築のために使用される
     * @param shape 描画する円弧
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawArc( const XdwArc& shape );

    /**
     * @brief 角丸矩形の描画
     *
     * 角丸矩形を，カレントの描画属性にしたがってStrok And Fill描画を行う．<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * パス構築のために使用される
     * @param shape 描画する角丸矩形
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawRoundRect( const XdwRoundRect& shape );

    /**
     * @brief カレントパスの描画
     *
     * カレントパスを，カレントの描画属性にしたがって指定された描画方法で描画する．<br>
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawPath( XdwGSDrawMode mode );

    /**
     * @brief Pixel単位での描画
     *
     * 指定された座標値を指定された色で、描画する
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     */
    XdwErrorCode DrawPixel( const XdwPoint& point,
                                    const XdwTypeUInt32 &color,
                                    XdwColorSpaceID colorspace = XDW_COLORSPACEID_RGB );

    /*@}*/

    /***************************************************/
    /*! @name RasterImage描画系I/F
     * RasterImageの描画を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief ラスターの描画
     *
     * これから描画するラスターの属性とラスタデータを指定しイメージを描画する．<br>
     * パターン描画のみの場合はimagedataがNULLになる。<br>
     * image描画のみの場合はmask, maskdataがNULLに，
     * mask描画のみの場合はimage, imagedataがNULLになる．<br>
     * もちろん，mask付きimage描画の場合は，
     * 両方に有効なポインタを指定しなければならない．<br>
     * 内部動作としては，XdwDataObjectを介して，Imageを読み込み描画を行う．<br>
     * クライアントは，XdwDataObjectに適切なデータを設定する必要があるが，
     * Imageの分割描画およびCall Back描画等のDecomposerに依存する処理は，
     * Bridge内部で行われる．<br>
     * @param image 描画するイメージの属性
     * @param imagedata 描画するイメージ
     * @param image_offset imageデータまでのオフセット<br>
     * @param image_size imageデータのサイズ<br>
     * @param mask 描画するMask属性
     * @param maskdata 描画するMask
     * @param mask_offset imageデータまでのオフセット<br>
     * @param mask_size imageデータのサイズ<br>
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @attention imagedata, maskedataが示すImageやMaskデータの実体は変更されないが，
     *            XdwDataObject::Binaryの内部状態は変更される<br>
     *            更に、imagedata, maskdataは同一のインスタンスを指す事も考えられ、
     *            データ取得時には注意が必要<br>
     *            データ取得時に先頭位置から、必ずSeekするようにすれば、回避できる。<br>
     *
        <CENTER>
        <BR>XdwDataObject::Binaryに格納されているラスターデータ<BR><BR>
        <TABLE border=1>
  	    <TR>
    		<TD>XdwRasterFormatID</TD>
    		<TD>XdwRasterCodecID</TD>
		    <TD>解説</TD>
	    </TR>
  	    <TR>
    		<TD>XDW_RASTERFORMATID_JPEG</TD>
		    <TD>XDW_RASTERCODECID_INVALID</TD>
    		<TD>Jpegフォーマットのバイナリデータ</TD>
	    </TR>
  	    <TR>
    		<TD>XDW_RASTERFORMATID_MH<BR>XDW_RASTERFORMATID_MMR</TD>
		    <TD>XDW_RASTERCODECID_INVALID</TD>
    		<TD>MH/MMR圧縮されたイメージデータ</TD>
	    </TR>
  	    <TR>
    		<TD>XDW_RASTERFORMATID_OKD</TD>
		    <TD>XDW_RASTERCODECID_DIB_RAW</TD>
    		<TD>DIBフォーマットのイメージデータが数ライン単位でOKD圧縮されている<BR>詳しくはDocuWorksファイルフォーマット仕様書参照</TD>
	    </TR>
  	    <TR>
    		<TD>XDW_RASTERFORMATID_ALLA</TD>
		    <TD>XDW_RASTERCODECID_DIB_RAW</TD>
    		<TD>DIBフォーマットのイメージデータが1ライン単位でALLA圧縮されている<BR>詳しくはDocuWorksファイルフォーマット仕様書参照</TD>
	    </TR>
  	    <TR>
    		<TD>XDW_RASTERFORMATID_WMF_RASTER<BR>XDW_RASTERFORMATID_EMF_RASTER<BR>XDW_RASTERFORMATID_OKD_OLD</TD>
		    <TD>XDW_RASTERCODECID_DIB_RAW<BR>XDW_RASTERCODECID_DIB_RLE_8<BR>XDW_RASTERCODECID_DIB_RLE_4<BR>XDW_RASTERCODECID_DIB_BIT_FILDES<BR>XDW_RASTERCODECID_DIB_JPEG<BR>XDW_RASTERCODECID_DIB_PNG</TD>
    		<TD>DIBフォーマットのイメージデータ</TD>
	    </TR>
  	    <TR>
    		<TD>XDW_RASTERFORMATID_WMF_RASTER<BR>XDW_RASTERFORMATID_EMF_RASTER</TD>
		    <TD>XDW_RASTERCODECID_XDW_JPEG</TD>
    		<TD>Jpegフォーマットのバイナリデータ</TD>
	    </TR>
        </TABLE>
        </CENTER>
     */
    XdwErrorCode DrawImage( const XdwRasterImageAttribute &image,
                                    XdwDataObject::Binary *imagedata,
                                    const long& image_offset,
                                    const long& image_size,
                                    const XdwRasterImageAttribute &mask,
                                    XdwDataObject::Binary *maskdata,
                                    const long& mask_offset,
                                    const long& mask_size );

    /**
     * @brief ラスターの分割描画
     *
     * これから描画するラスターの属性とラスタデータを指定する．<br>
     * パターン描画のみの場合はimagedataがNULLになる。<br>
     * image描画のみの場合はmask, maskdataがNULLに，
     * mask描画のみの場合はimage, imagedataがNULLになる．<br>
     * もちろん，mask付きimage描画の場合は，
     * 両方に有効なポインタを指定しなければならない．<br>
     * 内部動作としては，XdwDataObjectを介して，Imageを読み込み描画を行う．<br>
     * クライアントは，XdwDataObjectに適切なデータを設定する必要があるが，
     * Imageの分割描画およびCall Back描画等のDecomposerに依存する処理は，
     * Bridge内部で行われる．<br>
     * @param image 描画するイメージの属性
     * @param imagedata 描画するイメージ
     * @param image_offset imageデータまでのオフセット<br>
     * @param image_size imageデータのサイズ<br>
     * @param mask 描画するMask属性
     * @param maskdata 描画するMask
     * @param mask_offset imageデータまでのオフセット<br>
     * @param mask_size imageデータのサイズ<br>
     * @param nlines　	DrawDividedImage一回あたりの描画ライン数<br>
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     * @attention imagedata, maskedataが示すImageやMaskデータの実体は変更されないが，
     *            XdwDataObject::Binaryの内部状態は変更される<br>
     *            更に、imagedata, maskdataは同一のインスタンスを指す事も考えられ、
     *            データ取得時には注意が必要<br>
     *            データ取得時に先頭位置から、必ずSeekするようにすれば、回避できる。<br>
     *
     */
    XdwErrorCode StartDrawDividedImage( const XdwRasterImageAttribute &image,
                                    XdwDataObject::Binary *imagedata,
                                    const long& image_offset,
                                    const long& image_size,
                                    const XdwRasterImageAttribute &mask,
                                    XdwDataObject::Binary *maskdata,
                                    const long& mask_offset,
                                    const long& mask_size,
									long nlines );

    /*! MaskとRaster Imageの分割描画
     *
     * StartDrawDividedImageでセットされたイメージとパラメータに従って分割出力する
     *
     * @retval XDW_ERRORCODE_SUCCESS	正常終了
     * @retval XDW_ERRORCODE_CONTINUE	引き続き処理が可能
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     */
    XdwErrorCode DrawDividedImage( void );
    /*! MaskとRaster Imageの分割描画終了
     *
     * StartDrawDividedImage->DrawDividedImageの順で処理される一連のイメージ描画処理を終了する。
     * 処理を中断する場合でも必ず呼ばれなければならない。
     *
     * @retval XDW_ERRORCODE_SUCCESS	正常終了
     * @retval XDW_ERRORCODE_ERROR		なんらかのエラー
     */
    XdwErrorCode EndDrawDividedImage( void );

    /*@}*/

    /***************************************************/
    /*! @name Font描画系I/F
     * Fontの描画を行うI/Fである．
     */
    /***************************************************/
    /*@{*/

    /**
     * @brief Textの描画
     *
     * 指定された位置に，指定されたカレントフォントで，Code指定のTextを描画する．<br>
     * 本メソッドがXdwBridgeDrawIF::BeginPath()メソッドとXdwBridgeDrawIF::EndPath()メソッドの間に存在する場合には
     * テキストのアウトラインがパス構築のために使用される
     * @param p 描画位置座標値
     * @param text 描画するText
     * @retval XDW_ERRORCODE_SUCCESS 正常終了
     * @retval XDW_ERRORCODE_INVALID_PARAMETER 不正なパラメータ
     */
    XdwErrorCode DrawFont( const XdwPoint &p,
                                   const XdwCodeText &text );

    /*@}*/


    /*!
    @file  XdwBridgeViewerContIF.h
    @brief Bridge Viewer制御関連I/Fクラスヘッダファイル

    各種DecomposerのI/Fを隠蔽し，Viewer制御関連のI/F機能を提供する．
    */
        /***************************************************/
    /*! @name 制御系I/F
     * JobやPageの制御を行うI/Fである．Viewerとの共通化
     * を行うつもりだが，未だ未定．
     */
    /***************************************************/
    /*@{*/
    /*!初期化メソッド
      プライベートメンバ変数を初期化し，プライベートメンバ変数を設定する．
      クライアントは必ずこのメソッドを呼ばなければならない．<br>
      また，動的確保されるメモリ領域は，このメソッドが呼ばれることにより，
      初めて確保されるので，クライアントはこのメソッドを呼ぶことにより，
      XdwBridgePrintContIFクラス生成時のエラーを判定する．<br>
      必要であれば，Bridge以下のクラス (Imagerモジュール等) に対して，
      初期化を実行する．<br>

		resolutionX	x方向解像度<br>
		resolutionX	y方向解像度<br>
		width		x方向オフスクリーンサイズ<br>
		weight		y方向オフスクリーンサイズ<br>

      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
      @attention 渡されるポインタが何であるかは具象クラスに依存する．
      @attention 初期化されたパラメータ値はXdwBridgePrintContIF::StartJob()と同じになる．
    */
    XdwErrorCode InitializeContIF( void );
	XdwErrorCode InitializeContIF( unsigned short resolutionX, unsigned short resolutionY, long width, long weight );

    /*! BoundingBoxのセット
      DocuWorksの表示領域の中でImagerが描画可能な領域をセットする
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    XdwErrorCode SetBoundingBox( const XdwRectangle &rect );


    /*! オフスクリーンのセット
      オフスクリーンをセット後HBPSイメージャのStartPageを呼ぶ
      @param off_screen オフスクリーンを規定するインターフェース
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
/*	AR1170 (オフスクリーン切替時のImager終了処理は呼び出し側で行う)
	XdwErrorCode SetOffScreen( XdwOffScreen* off_screen, bool change_flag ); */
    XdwErrorCode SetOffScreen( XdwOffScreen* off_screen);

    /*! ジョブの開始
      ジョブを開始する．ジョブの開始時には呼ばなければならない．
      Bridge以下のコンポーネントは，XdwBridgePrintContIF::StartJob()が呼ばれることによって，
      各種の設定を行う．
      <center>
      <br>JOBで初期化されるパラメータの値<br><br>
      <table>
          <tr><td><center>パラメータ名</center></td><td><center>値</center></td><td><center>注釈</center></td></tr>
          <tr><td>色空間</td><td>XDW_COLORSPACEID_RGB</td><td>デフォルトはRGB</td></tr>
          <tr><td>Foreground色値</td><td>黒 (0x00000000)</td><td>暫定</td></tr>
          <tr><td>Background色値</td><td>白 (0xFFFFFFFF)</td><td>暫定</td></tr>
          <tr><td>背景描画モード</td><td>XDW_GSTATEBGM_OPAQUE</td><td>暫定</td></tr>
          <tr><td>Pen色</td><td>Solid Color and Foreground色値</td><td>暫定</td></tr>
          <tr><td>Brush色</td><td>Solid Color and Background色値</td><td>暫定</td></tr>
          <tr><td>Current Transfer Matrix </td><td>システム依存</td><td>ただし，拡縮無しでデバイス空間と一致する</td></tr>
          <tr><td>線幅</td><td>1.0</td><td>ユーザー空間における線幅</td></tr>
          <tr><td>Pen Type</td><td>XDW_PENSTYLE_SOLID (実線)</td><td>暫定</td></tr>
          <tr><td>Join Type</td><td>XDW_JOINTYPE_MITER</td><td>暫定</td></tr>
          <tr><td>Cap Type</td><td>XDW_JOINTYPE_BUTT</td><td>暫定</td></tr>
          <tr><td>Cliping領域</td><td>デバイス上ページのBounding Box</td><td>暫定</td></tr>
          <tr><td>Cliping Logic</td><td>XDW_GSTATECL_AND</td><td>暫定</td></tr>
          <tr><td>ROP Mode and Code</td><td>Mode 2, COPY</td><td>暫定</td></tr>
          <tr><td>Fill Rule</td><td>Even-Odd</td><td>暫定</td></tr>
          <tr><td>Fill Mode</td><td>Fill</td><td>暫定</td></tr>
      </table>
      </center>
      <br>
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
    */
    XdwErrorCode StartJob( void );

    /*! ジョブの終了
      ジョブを終了する．ジョブの終了時には呼ばなければならない．
      Bridge以下のコンポーネントは，EndJob()が呼ばれることによって，
      ジョブの終了処理を行う．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    XdwErrorCode EndJob( void );

    /*! ジョブのターミネート
      ジョブを終了する．ジョブの終了時には呼ばなければならない．
      Bridge以下のコンポーネントは，EndJob()が呼ばれることによって，
      ジョブの終了処理を行う．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    XdwErrorCode Terminate( void );

    /*! ページの開始
      ページの描画を開始する．ページの描画の開始時には呼ばなければならない．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
      @attention 初期化パラメータは暫定的にXdwBridgePrintContIF::StartJob()と等しい．
    */
    XdwErrorCode StartPage( int reso_x, int reso_y, long x, long y, unsigned char *pageBuffer, long lineSize, void *DC );

    /*! ページの描画
      ページを描画する．XdwBridgePrintContIF::StartPage()以降の描画を，
      全て，なんらかの出力デバイスへ出力する．<br>
      Viewer時には，StartPage()以降の描画が，都度，描画されるため，
      意味を持たない．
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    XdwErrorCode ShowPage( void );

    /*! ページの終了
      ページを終了する．ページの終了時には呼ばなければならない．
      Bridge以下のコンポーネントは，EndPage()が呼ばれることによって，
      ページの終了処理を行う．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
    */
    XdwErrorCode EndPage( void );
    /*@}*/

private:

    void InitSkiaMatrix();

    XdwErrorCode SelectBrushObject( XdwBridgeObjectBrush* );

    XdwErrorCode SetCTMtoSkia(void);

    XdwErrorCode SkiaDrawPolygon( const XdwPointVector &p );

    void SetSkiaMatrix(Skia_Matrix skiamatrix);

    void setARGBforSkPain(unsigned char data[3],SkPaint &temp_paint);

    void TransferPoint(const XdwPoint &p);

    void TransferPoint(const XdwPoint &p,Skia_Point &temp_point);

    void TransferPoint(XDW_REAL64 xF,XDW_REAL64 yF,Skia_Point &temp_point);

    // ROP code settings
    XdwErrorCode SetRop2(XdwTypeUInt32);
    XdwErrorCode SetRop3(XdwTypeUInt32);

    // GDI object select
    XdwErrorCode SelectPenObject(XdwBridgeObjectPen *obj);

    void SkiaDrawRect(XdwPoint LeftTopF,XdwPoint RightBottomF);

    XdwErrorCode SkiaMovePoint(const XdwPoint &p);

    void SkiaAddLinePath(const XdwPoint &p);

    XdwErrorCode SkiaClosePath();

    XdwErrorCode SkiaDrawPath();

    XdwErrorCode SkiaAddBezierPath(unsigned short nBezier, float * dataF);

    XdwErrorCode SkiaPathReset();

    XdwErrorCode SetDrawMode( XdwGSDrawMode mode );

};

#endif /* XDWBRIDGESKIAIMPL_H_INCLUDED */
