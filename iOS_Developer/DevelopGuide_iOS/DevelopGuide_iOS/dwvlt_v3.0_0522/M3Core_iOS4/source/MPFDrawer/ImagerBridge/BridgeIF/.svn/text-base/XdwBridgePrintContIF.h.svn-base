/*!
  @file  XdwBridgePrintContIF.h
  @brief Bridge プリント制御関連I/Fクラスヘッダファイル

  各種DecomposerのI/Fを隠蔽し，Controler制御関連のI/F機能を提供する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-04-24
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-04-24	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEPRINTCONT_H_INCLUDED
#define XDWBRIDGEPRINTCONT_H_INCLUDED

#include "XdwError.h"

/* 他のファイルに定義されているデータ類 */
#include "XdwBridgeCommon.h"

#include "XdwDataObject.h"

/*! 各種Decomposer用のBridgeクラス

  Globe Decomposr, HBPS Decomposer等の仕様の違いを吸収し，
  Print関連の制御に関する共通化されたDecomposer I/Fをクライアントに提供する，Bridgeクラス．
  抽象クラスなので，クライアントは具象クラスを生成して，それを使用する．
  ただし，具象クラスはこのクラスと描画系のBridgeI/Fクラスとの多重継承にしなければならない．<br>
  @attention Bridge classは，ポインタにより渡された，クライアント側で動的確保
  されたメモリ領域を開放することは決してない．Bridge classがFreeするのは，
  Bridge classが動的確保したメモリ領域のみである．
  @attention 基本的に引数として渡したオブジェクトの内部変数は変更されない．
  変更されるI/Fに関は，I/Fにその旨記載する．
 */
class XdwBridgePrintContIF {
public:
    /*! コンストラクタ
      コンストラクタでは，動的メモリの確保は行われない．
      ただし，ポインタのNULL初期化は行われる．
    */
    XdwBridgePrintContIF() {};
    /*! デストラクタ
      XdwBridgeが動的に確保したメモリ領域のみFreeされる．
      他のクラスにおいて生成したと思われる領域のFreeは行わない．
    */
    virtual ~XdwBridgePrintContIF() {};

    /***************************************************/
    /*! @name 公開属性定数
     * Bridge特有のenum定数．後でグローバルにするかも．
     */
    /***************************************************/
    /*@{*/
    /*! ページモード
      ページ描画時のモードを指定する．<br>
      @attention CONTONEは多値，BINARYは2値描画が期待されるが，
      あくまでも“高画質”と“高速”の区別であり，
      描画される時のbit depthはシステム依存である．
    */
    enum PageMode {
	XDW_BRIDGEPM_CONTONE_COLOR,	//!< 高画質カラーページ描画
	XDW_BRIDGEPM_CONTONE_GRAY,	//!< 高画質白黒ページ描画
	XDW_BRIDGEPM_CONTONE_AUTO,	//!< 自動認識しての高画質描画
	XDW_BRIDGEPM_BINARY_COLOR,	//!< 高速カラーページ描画
	XDW_BRIDGEPM_BINARY_GRAY,	//!< 高速白黒ページ描画
	XDW_BRIDGEPM_BINARY_AUTO	//!< 自動認識しての高速描画
    };
    /*@}*/

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
      初期化を実行する．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
      @attention 渡されるポインタが何であるかは具象クラスに依存する．
      @attention 初期化されたパラメータ値はXdwBridgePrintContIF::StartJob()と同じになる．
    */
    virtual XdwErrorCode InitializeContIF( void ) = 0;

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
    virtual XdwErrorCode StartJob( void ) = 0;

    /*! ジョブの終了
      ジョブを終了する．ジョブの終了時には呼ばなければならない．
      Bridge以下のコンポーネントは，EndJob()が呼ばれることによって，
      ジョブの終了処理を行う．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    virtual XdwErrorCode EndJob( void ) = 0;

    /*! ページの開始
      ページの描画を開始する．ページの描画の開始時には呼ばなければならない．
      @param pm ページの描画モードを指定する
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
      @attention 初期化パラメータは暫定的にXdwBridgePrintContIF::StartJob()と等しい．
    */
    virtual XdwErrorCode StartPage( const XdwBridgePrintContIF::PageMode &pm ) = 0;

    /*! ページの描画
      ページを描画する．XdwBridgePrintContIF::StartPage()以降の描画を，
      全て，なんらかの出力デバイスへ出力する．<br>
      Viewer時には，StartPage()以降の描画が，都度，描画されるため，
      意味を持たない．
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    virtual XdwErrorCode ShowPage( void ) = 0;

    /*! ページの終了
      ページを終了する．ページの終了時には呼ばなければならない．
      Bridge以下のコンポーネントは，EndPage()が呼ばれることによって，
      ページの終了処理を行う．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
    */
    virtual XdwErrorCode EndPage( void ) = 0;
    /*@}*/

};

#endif /* XDWBRIDGEPRINTCONT_H_INCLUDED */
