/*!
  @file  XdwBridgeViewerContIF.h
  @brief Bridge Viewer制御関連I/Fクラスヘッダファイル

  各種DecomposerのI/Fを隠蔽し，Viewer制御関連のI/F機能を提供する．

  @author Kenichi Ishida (Fuji Xelox Co., Ltd. DPC DS&S STD) <Kenichi.Ishida@fujixerox.co.jp>
  @date 2002-07-19
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Kenichi Ishida<br>
  Created:	2002-07-19	Kenichi Ishida<br>
 */
#ifndef XDWBRIDGEVIEWERCONT_H_INCLUDED
#define XDWBRIDGEVIEWERCONT_H_INCLUDED

#include "System/SystemIF/XdwError.h"

/* 他のファイルに定義されているデータ類 */
#include "XdwBridgeCommon.h"

#include "DataObject/Include/XdwDataObject.h"
class XdwOffScreen;

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
class XdwBridgeViewerContIF {
public:
    /*! コンストラクタ
      コンストラクタでは，動的メモリの確保は行われない．
      ただし，ポインタのNULL初期化は行われる．
    */
    XdwBridgeViewerContIF() {};
    /*! デストラクタ
      XdwBridgeが動的に確保したメモリ領域のみFreeされる．
      他のクラスにおいて生成したと思われる領域のFreeは行わない．
    */
    virtual ~XdwBridgeViewerContIF() {};

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
    virtual XdwErrorCode InitializeContIF( void ) = 0;
	virtual XdwErrorCode InitializeContIF( unsigned short resolutionX, unsigned short resolutionY, long width, long weight ) = 0;

    /*! BoundingBoxのセット
      DocuWorksの表示領域の中でImagerが描画可能な領域をセットする
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    virtual XdwErrorCode SetBoundingBox( const XdwRectangle &rect ) = 0;


    /*! オフスクリーンのセット
      オフスクリーンをセット後HBPSイメージャのStartPageを呼ぶ
      @param off_screen オフスクリーンを規定するインターフェース
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
/*	AR1170 (オフスクリーン切替時のImager終了処理は呼び出し側で行う)
	virtual XdwErrorCode SetOffScreen( XdwOffScreen* off_screen, bool change_flag ) = 0; */
    virtual XdwErrorCode SetOffScreen( XdwOffScreen* off_screen) = 0;

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

    /*! ジョブのターミネート
      ジョブを終了する．ジョブの終了時には呼ばなければならない．
      Bridge以下のコンポーネントは，EndJob()が呼ばれることによって，
      ジョブの終了処理を行う．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @attention Viewerへの対応は未検討．
    */
    virtual XdwErrorCode Terminate( void ) = 0;

    /*! ページの開始
      ページの描画を開始する．ページの描画の開始時には呼ばなければならない．
      @retval XDW_ERRORCODE_SUCCESS 正常終了
      @retval XDW_ERRORCODE_INSUFFICINET_MEMORY メモリ確保が不可能
      @attention Viewerへの対応は未検討．
      @attention 初期化パラメータは暫定的にXdwBridgePrintContIF::StartJob()と等しい．
    */
    virtual XdwErrorCode StartPage( int reso_x, int reso_y, long x, long y, unsigned char *pageBuffer, long lineSize, void *DC ) = 0;

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

#endif /* XDWBRIDGEVIEWERCONT_H_INCLUDED */
