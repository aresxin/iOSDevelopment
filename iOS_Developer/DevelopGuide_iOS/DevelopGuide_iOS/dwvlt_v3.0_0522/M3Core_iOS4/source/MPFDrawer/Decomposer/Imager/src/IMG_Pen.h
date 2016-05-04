/*!
  @file IMG_Pen.h
  @brief Pen classヘッダファイル

  HBPS Imager内部でPathのStroke描画機能で使用されるIMG_Pen classのヘッダファイルである．<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-08
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Apr,17,2001	Toshio Yamazaki
 */

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_DisplayList.h"
#include "IMG_GraphicsContext.h"
#include "IMG_GeometricShape.h"
#include "IMG_Path.h"
#include "IMG_ClassPointer.h"

#include "IMG_RotatedRect.h"
#include "IMG_QuadRangle.h"
#include "IMG_Circle.h"

#ifndef IMG_PEN_H_INCLUDED
#define IMG_PEN_H_INCLUDED

/* Error Code は #define の羅列 */
#define IMG_PEN_ERRORCODE_NOERROR	0	/*!< IMG_Pen成功エラーコード */
#define IMG_PEN_ERRORCODE_ERROR	       -1	/*!< IMG_Pen失敗エラーコード */

/*! 仮想関数用IMG_Pen構造体前宣言	*/
typedef struct IMG_Pen_L	*IMG_PenPointer;

/*! IMG_Pen構造体

  HBPS Imager内部で，PathのStroke描画時に生成される，ラインセグメント図形・
  ジョイン図形・キャップ図形を実際の描画を行うクラスのI/Fクラスである．<br>
  IMG_Pathクラスが生成される際にカレントのCTMに合わせて生成され，
  描画時にIMG_Strokeクラスから使用され，描画終了後破棄されるクラスである．<br>
  通常生成され描画に使われるのは，IMG_Penクラスを継承した，IMG_PenNonOrthogonal(非直行座標系用),
  IMG_PenOrthogonal(直行座標系用), IMG_PenPathNonOrthogonal(非直行座標系かつパス描画用),
  クラスのいずれかであり，IMG_Penクラスは各々のクラス内から生成され，
  各々のクラスが破棄される時に同時に破棄される．
  したがって，このクラスで提供される機能は以下の通り．
  処理概要は，IMG_PathStrokeを参照のこと.
	-# 生成・破棄時における共通メンバ変数の処理
	-# 共通な座標系演算アルゴリズムの提供

  @warning
	生成・破棄のI/Fは，ややこしいことに，IMG_Pen_Create(),IMG_Pen_Destroy()
	を使わなければならない．<br>
	IMG_Penクラスを使用するだけなら，IMG_Pen_Create()関数にて，実際の必要な
	IMG_Penの継承クラスのオブジェクトが生成され，それを利用するだけだが，
	新しいIMG_Penの継承クラスを作る場合は，生成がややこしいので注意すること．
  <br><br>

  @par 使用方法:
	必要なIMG_Context, IMG_GraphicsContext, IMG_DisplayListを生成する．
	もしくは他のモジュールから有効なオブジェクトとして確保した後，
	以下のシーケンスで生成する．生成した後は，
	IMG_Pen用の関数を利用してラインセグメント図形・ジョイン図形・キャップ図形
	の描画を行うことが可能となる．<br>
	この時生成されるIMG_Penオブジェクトは生成時のCTM，グラフィックス属性に
	合ったIMG_Penオブジェクトが生成されることが保証されている．
  @code
	＊コード例＊
	IMG_Context *c;
	IMG_GraphicsContext *gc;
	IMG_DipslayList *dl;

	＊IMG_Context, IMG_GraphicsContext, IMG_DisplayListの確定＊

	IMG_Pen *pen;

	pen = IMG_Pen_Create( c, dl, gc );
	＊以降，penオブジェクトの使用が可能になる＊
  @endcode
	IMG_Penオブジェクトが生成されたなら，IMG_Penオブジェクト関数を利用して，
	描画を行うことができる．描画時のグラフィック属性はIMG_Penオブジェクトが生成された
	時のグラフィック属性が用いられる．(実際はポインタでハンドリングしているため，
	生成時とグラフィック属性を変更することが可能であるが，推奨はしない)
  @code
	＊コード例＊
	IMG_Point	p1, p2, p3;

	p1.x = 0.0; p1.y = 0.0;
	p2.x = 0.0; p2.y = 10.0;
	p3.x = 10.0; p2.y = 10.0;

	＊(0,0)〜(0,10)にラインセグメント図形を描画する＊
	pen->DrawLine( pen, &p1, &p2 );
	＊(0,10)〜(10,10)にラインセグメント図形を描画する＊
	pen->DrawLine( pen, &p2, &p3 );
	＊p1=(0,0)にキャップ図形を描画する＊
	pen->DrawLine( pen, &p2, &p1 );
	＊p3=(10,10)にキャップ図形を描画する＊
	pen->DrawLine( pen, &p2, &p3 );
	＊p2=(0,10)にジョイン図形を描画する＊
	pen->DrawLine( pen, &p1, &p2, &p3 );
  @endcode
	描画が終了したなら，以下のシーケンスでIMG_Penオブジェクトを削除する．
  @code
	＊コード例＊
	IMG_Pen *pen;

	＊IMG_Penオブジェクトの確定＊

	IMG_Pen_Destroy(pen);
  @endcode
  @note
	IMG_Penでの描画処理は，(1)ユーザー座標系で図形を作る
	(2)デバイス空間での描画用に座標変換を行う，のステップで行われる．<br>
	通常，IMG_Penの描画関数を使用する場合，与えられる座標系はデバイス座標系
	であるため，上記ステップを行う必要から，(1)デバイス座標系をユーザー座標系へ逆変換
	(2)ユーザー座標系で図形を作る(3)デバイス空間での描画用に座標変換を行う，の
	ステップで処理が行われる．<br>
	ここで，座標変換のコストが大きくなることから，座標系にあわせてIMG_Penの継承クラスを作成し，
	省ける座標変換を省くことによって処理速度を稼ぐわけである．
 */
typedef struct IMG_Pen_L {

    IMG_Context		*context;		/*!< 管理用クラス	*/
    IMG_DisplayList	*display_list;		/*!< 描画先クラス	*/
    IMG_GraphicsContext	*graphics_context;	/*!< グラフィック属性クラス*/
    /*! ROP2 Stroke 描画用 Path Object			*/
    IMG_Path		*path;

    /* width は，Pen class生成時に設定される線幅	*/
    /* ただし，FastOrthogonal でのみ使用できる		*/
    IMG_FLOAT		width;	/*!< Pen幅	*/

    /* 2001/9/18 Path仕様変更				*/
    /* PathBufferには座標変換済みの座標値を格納される	*/
    /* それの対応のための逆行列				*/
    IMG_Matrix33	inv_ctm;	/*!< CTMの逆行列 */

    /* 90度単位で回転されたときに，			*/
    /* strokeの描画位置を補正するための変数		*/
    IMG_REAL32		stroke_correct_x;	/*!< 回転時X座標補正値	*/
    IMG_REAL32		stroke_correct_y;	/*!< 回転時Y座標補正値	*?

    /* 生成する描画図形．いちいちmallocするのは嫌だから	*/
    /* Penでハンドリングして，Create時に生成する	*/
    IMG_GeometricShape	*rotrect;	/*!< 描画図形(傾いた矩形)	*/
    IMG_GeometricShape	*quadrangle;	/*!< 描画図形(凸四角形)		*/
    IMG_GeometricShape	*circle;	/*!< 描画図形(円)		*/
	IMG_TagFilterPtr	tagFilter;

    /* vertual function の定義					*/
    /*! ジョイン図形を描画する仮想関数				*/
    int (*Draw_JoinPoint)( IMG_PenPointer, IMG_Point *, IMG_Point *, IMG_Point * );
    /*! キャップ図形を描画する仮想関数				*/
    int (*Draw_CapPoint)( IMG_PenPointer, IMG_Point *, IMG_Point * );
    /*! ラインセグメント図形を描画する仮想関数			*/
    int (*Draw_Line)( IMG_PenPointer, IMG_Point *, IMG_Point * );
    /*! パスの方向と直行するStroke線幅演算のための仮想関数	*/
    int (*Calc_VectorLength)( IMG_PenPointer, IMG_Point *, IMG_Point *, IMG_FLOAT * );

} IMG_Pen;

IMG_Pen *IMG_Pen_Init( IMG_Context *, IMG_DisplayList *,
		       IMG_GraphicsContext * );
IMG_Pen *IMG_Pen_Create( IMG_Context *, IMG_DisplayList *, IMG_TagFilterPtr ,
			 IMG_GraphicsContext * );
int IMG_Pen_Destroy( IMG_Pen * );

/*
 * Pen 共通の関数
 */
IMG_FLOAT IMG_Pen_CalcAngle( IMG_FLOAT, IMG_FLOAT );
void IMG_Pen_CalcOrthogonalVector(IMG_Point *, IMG_Point *, IMG_Point * );
IMG_Point IMG_Pen_CalcRelativeSidePoint(IMG_Point *, IMG_Point *,
					IMG_Point *, IMG_Point *);
int IMG_Pen_CalcMiterJoinPoint(IMG_Point *, IMG_Point *, IMG_Point *,
			       IMG_FLOAT,
			       IMG_Point *, IMG_Point *, IMG_Point *);
int IMG_Pen_CalcBevelJoinPoint(IMG_Point *, IMG_Point *, IMG_Point *,
			       IMG_FLOAT,
			       IMG_Point *, IMG_Point * );
int IMG_Pen_CalcRoundJoinAngle(IMG_Point *, IMG_Point *, IMG_Point *,
			       IMG_FLOAT,
			       IMG_Point *, IMG_Point *,
			       IMG_FLOAT *, IMG_FLOAT * );
int IMG_Pen_CalcTopPoint(IMG_Point *, IMG_Point *,
			 IMG_FLOAT,
			 IMG_Point * );
void IMG_Pen_CorrectStroke( IMG_Pen *, IMG_Point *, IMG_Point * );
/*! 回転時座標補正用マクロ */
#define IMG_PEN_CORRECTSTROKE(p,s,d)	(d)->x =  (s)->x + (p)->stroke_correct_x;	\
					(d)->y =  (s)->y + (p)->stroke_correct_y

/*
 * Pen 共通のマクロ&定数
 */
#define IMG_PEN_PI		3.1415926535898		/*!< パイ			*/
#define IMG_PEN_PERMITTED_ERROR		IMG_FLOATING_ERROR		/*!< 許容誤差値			*/
#define IMG_PEN_FABS(a)			(((a)<0)?-(a):(a))	/*!< abs演算マクロ	*/

#define IMG_PEN_1PIXELLINE_LIMIT	(1.5)	/*!< 1 pixel 線描画になるデバイス線幅のスレッショルド値*/
#define IMG_PEN_DONWDRAW_JOIN_LIMIT	(2.0)	/*!< ジョイン図形を描画しないデバイス線幅のスレッショルド値*/
#define IMG_PEN_DONWDRAW_CAP_LIMIT	(2.0)	/*!< キャップ図形を描画しないデバイス線幅のスレッショルド値*/

#endif /* IMG_PEN_H_INCLUDED */
