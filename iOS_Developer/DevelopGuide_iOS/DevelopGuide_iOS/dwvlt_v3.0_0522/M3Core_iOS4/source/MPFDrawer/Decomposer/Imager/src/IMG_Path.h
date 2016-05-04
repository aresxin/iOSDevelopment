/*!
  @file IMG_Path.h
  @brief Path classヘッダファイル

  HBPS Imager内部でPathの機能を提供するIMG_Path classのヘッダファイルである．<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-04
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Edited:	Apr, 4,2001	Kenichi Ishida
  Modified:	Apr,18,2001	Toshio Yamazaki
 */

#ifndef IMGPATH_H_INCLUDED
#define IMGPATH_H_INCLUDED

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_GeometricShape.h"
#include "IMG_PathBuffer.h"
#include "IMG_ClassPointer.h"

/* Error Code は #define の羅列 */
#define IMG_PATH_ERRORCODE_NOERROR	0	/*!< IMG_Path成功エラーコード	*/
#define IMG_PATH_ERRORCODE_ERROR	-1	/*!< IMG_Path失敗エラーコード	*/

/*! パス構築状態
  IMG_Pathでパスを構築する際の状態を示す状態変数．
  IMG_Pathはパスを構築する際に，この状態変数に従った，
  ステートマシーンを構成することによりパスの構築を行う．
 */
enum IMG_PATH_CONSTRUCT_STATE {
    IMG_PATH_CONSTRUCT_STATE_CONSTRUCTING,	/*!< サブパス構築中		*/
    IMG_PATH_CONSTRUCT_STATE_NULL,		/*!< パスが存在しない，空の状態	*/
    IMG_PATH_CONSTRUCT_STATE_STARTCONSTRUCT	/*!< サブパス構築開始．カレントポインタが設定されている状態*/
};

/*! IMG_Path構造体

  HBPS Imager内部でPathの機能を提供する．<br>
  生成されたIMG_Path classは，内部にIMG_PathBufferを生成するので，
  一般的なPathの機能を提供することが出来る．<br>
  Pathのストローク描画時には，IMG_GraphicsContextを参照して，
  適切なIMG_Pen classを生成してIMG_DisplayListに対して描画を行う．
  また，Pathのフィル描画時も同様に，適切なIMG_Fill classを生成して
  IMG_Contextに対して描画を行う．<br>
  これらの操作は全て隠蔽されているので，クライアントは適切なI/Fをcallするだけで，
  必要な機能を実行することが出来る．ただし，
  Cで記述されているため，以下のシーケンスによって生成しなければならない．
  <br>
  <br>
  @code
	IMG_Context *c;
	IMG_GraphicsContext *gc;

	IMG_Path *path;

	path = IMG_Path_Create( c, gc );
  @endcode
  <br>
  <br>
  また，IMG_Path classをdeleteする場合も，以下のシーケンスによって削除しなければならない．
  <br>
  <br>
  @code
	IMG_Context *c;
	IMG_GraphicsContext *gc;

	IMG_Path *path;

	path = IMG_Path_Create( c, gc );

	＊＊Pathの操作処理＊＊

	IMG_Path_Destroy(path);
  @endcode

  @par 使用方法:
	-# 必要なIMG_Context, IMG_GraphicsContextを生成する．
	もしくは他のモジュールから有効なオブジェクトとして確保した後，
	以下のシーケンスで生成する．生成した後は，
	IMG_Path用の関数を利用してパスの操作を行うことが可能となる．
  @code
	＊コード例＊
	IMG_Context *c;
	IMG_GraphicsContext *gc;

	＊IMG_Context, IMG_GraphicsContextの確定＊

	IMG_Path *path;

	path = IMG_Path_Create( c, gc );
	＊以降，pathオブジェクトの使用が可能になる＊
  @endcode
	-# パスを構築する．パスの構築は，IMG_Path_MoveTo(), IMG_Path_LineTo(),
	IMG_Path_BezierTo(), IMG_Path_Close(), IMG_Path_Open()
	の各関数を使用する．これらの関数は生成されたIMG_Pathオブジェクトを
	引数に渡すことにより，IMG_Pathオブジェクトにパスを構築する．
	この時のパスの構築は，Adobe PostScript Level2または，Windows GDIの仕様に準じる．<br>
	不正な構築によるエラーや，その他のエラーが発生した場合は，
	関数内での適切な処理を保証する．
  @code
	＊コード例＊
	IMG_Point p;
	IMG_Path *path;

	＊IMG_Pathオブジェクトの確定＊

	＊以下のようにパスを構築する＊
	＊(0,0)へmoveto＊
	p.x = 0; p.y = 0;
	IMG_PathMoveTo( path, &p, IMG_TRUE );

	＊(10,10)へlineto＊
	p.x = 10.0; p.y = 10.0;
	IMG_PathLineTo( path, &p, IMG_TRUE );
  @endcode
	-# パスを描画する．パスの描画は，IMG_Path_Fill(), IMG_Path_Fill_NOTRANSFORM(),
	IMG_Path_Stroke()の各関数を使用する．
	これらの関数はパスが構築されたIMG_Pathオブジェクトを
	引数に渡すことにより，引数のIMG_DisplayListにパスを描画する．
	この時のパスの描画は，Adobe PostScript Level2または，Windows GDIの仕様に準じ，
	IMG_GraphicsCotext内のグラフィックス属性に従って描画される．
  @code
	＊コード例＊
	IMG_Context *c;
	IMG_Path *path;
	IMG_GraphicsContext *gc;
	IMG_DisplayList *dl;

	＊IMG_Context, IMG_GraphicsContext, IMG_DisplayListの確定＊
	＊IMG_Pathオブジェクトの確定＊

	＊IMG_Pathに構築されたPathをFill描画する＊
	path = IMG_Path_Fill( path, c, dl, gc );
  @endcode
	-# パスを破棄する．不必要になったパスは，
	以下のシーケンスによって削除する．
  @code
	＊コード例＊
	IMG_Path *path;

	＊IMG_Pathオブジェクトの確定＊

	IMG_Path_Destroy(path);
  @endcode


  @par	内部に保存されるパスの座標系について:
	IMG_Pathは，内部に保存されるパスを，使用状況によって，
	CTMにより座標変換を行うか，座標変換を行わないかを
	切り替えたい場合がある．<br>
	そこで，IMG_Pathのほぼ全てのメソッドには，
	引数に切り替えフラグが付いており，
	IMG_Pathを使用する場合，そのフラグを，使用者側が適切に
	設定しなければならない．

  @warning
	IMG_Pathを生成するには，IMG_Context, IMG_GraphicsContext
	が生成されていなければならない．<br>
	IMG_Path内のパスを描画するには，IMG_Context, IMG_GraphicsContext
	IMG_DisplayListが生成されていなければならない．
 */
typedef struct img_path {
    /*
     * Imagerパッケージ内のクラスとして必要なメンバ
     */
    IMG_Context		*context;		/*!< 管理用クラス		*/
    IMG_GraphicsContext	*graphics_context;	/*!< グラフィック属性クラス	*/
    /*
     * Pathに必要なメンバ
     */
    IMG_PathBuffer	*path_buffer;		/*!< パス実体			*/
    int			path_state;		/*!< パス構築状態		*/
    IMG_Point		current_point;		/*!< カレントポイント		*/
    IMG_Point		current_point_notransform;/*!< 座標変換されていない，カレントポイント	*/
    IMG_Point		start_point;		/*!< パスの開始点		*/
    IMG_Point		start_point_notransform;/*!< 座標変換されていない，パスの開始点	*/
} IMG_Path;

/*! Stroke Adjust機能を有効にする	*/
#define IMG_ENABLE_STROKEADJUST
#ifdef	IMG_ENABLE_STROKEADJUST
void IMG_Path_StrokeAdjust(IMG_Point *, int );
#endif	/* IMG_ENABLE_STROKEADJUST */

IMG_Path* IMG_Path_Create( IMG_Context*, IMG_GraphicsContext* );
int IMG_Path_Destroy( IMG_Path* );

int IMG_Path_MoveTo( IMG_Path*, IMG_Point*, int, IMG_BOOL );
int IMG_Path_LineTo( IMG_Path*, IMG_Point*, int, IMG_BOOL  );
int IMG_Path_BezierTo( IMG_Path*, IMG_Point*, int, IMG_BOOL );
int IMG_Path_Close( IMG_Path* );
int IMG_Path_Open( IMG_Path* );
int IMG_Path_Clear( IMG_Path* );
int IMG_Path_GetCurrentPoint( IMG_Path*, IMG_Point*, IMG_BOOL );

int IMG_Path_Fill(
    IMG_Path		*,
    IMG_Context		*,
    IMG_DisplayList	*,		/* DisplayListオブジェクト */
	IMG_TagFilterPtr	tagFilter,
    IMG_GraphicsContext *);		/* 描画属性 */

int IMG_Path_Fill_NOTRANSFORM(
    IMG_Path		*,
    IMG_Context		*,
    IMG_DisplayList	*,		/* DisplayListオブジェクト */
	IMG_TagFilterPtr	tagFilter,
    IMG_GraphicsContext *);		/* 描画属性 */

int IMG_Path_Stroke(
    IMG_Path		*,
    IMG_Context		*,
    IMG_DisplayList	*,		/* DisplayListオブジェクト */
	IMG_TagFilterPtr	tagFilter,
    IMG_GraphicsContext	*);		/* 描画属性 */

#endif	/* IMGPATH_H_INCLUDED */
