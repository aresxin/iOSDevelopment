/*!
  @file IMG_PathStroke.h
  @brief PathStroke classヘッダファイル

  HBPS Imager内部でPathのStroke描画機能を提供するIMG_PathStroke classのヘッダファイルである．<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-04
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Apr,13,2001	Toshio Yamazaki
 */

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_DisplayList.h"
#include "IMG_GraphicsContext.h"
#include "IMG_Path.h"
#include "IMG_PathBuffer.h"
#include "IMG_Pen.h"

#ifndef IMG_PATHSTROKE_H_INCLUDED
#define IMG_PATHSTROKE_H_INCLUDED

/* Error Code は #define の羅列 */
#define IMG_PATHSTROKE_ERRORCODE_NOERROR	0	/*!< IMG_PathStroke成功エラーコード */
#define IMG_PATHSTROKE_ERRORCODE_ERROR	       -1	/*!< IMG_PathStroke失敗エラーコード */

/*! 破線補正タイプの定義
  破線のセグメント長を線幅で補正する場合の，
  補正アルゴリズムを指定する．
  破線描画時にはこの指定に従った補正で，
  破線のセグメント長が線幅に依存して補正される．
*/
typedef enum {
    IMG_PATHDASH_WINCORRECT,	/*!< Windowsライクな補正	*/
    IMG_PATHDASH_NORMAL		/*!< デフォルトの補正		*/
} IMG_PathDash_CorrectType;

typedef struct IMG_PathStroke_L	*IMG_PathStrokePointer;
/*! IMG_PathStroke構造体

  HBPS Imager内部で，PathのStroke描画機能を提供するクラスのI/Fクラスである．<br>
  IMG_Pathクラスにてストローク描画が発生した場合に，IMG_Pathクラス内において生成され，
  使用後破棄されるクラスであり，現時点では例外は無い．<br>
  通常生成されるのは，IMG_Strokeクラスを継承した，IMG_PathNormalStrokeクラスか，
  IMG_PathDashedStrokeクラスであり，IMG_PathStrokeクラスは各々のクラス内から生成され，
  各々のクラスが破棄されるときに，同時に破棄される．<br>
  したがって，このクラスで提供される機能は，
	-# 生成・破棄時における共通メンバ変数の処理
	-# 共通なストロークアルゴリズムの提供
  である．

  @par 処理概略:
	IMG_PathStroke内のStroke描画処理の概略を以下に示す．
	-# 共通のストロークアルゴリズムを提供する，
	IMG_PathStroke_Stroke()にてIMG_PathBuffer内に蓄えられたパスを操作し，
	パスを，ラインセグメント図形・ジョイン図形・キャップ図形に分解する．
	-# 分解された図形は，
	(*Draw_JoinPoint)(), (*Draw_CapPoint)(), (*Draw_Line)()
	の各 (関数へのポインタで表現されている) 仮想関数により描画する．
	-# IMG_PathStrokeを継承したIMG_PathNormalStroke, IMG_PathDashedStroke
	の各クラスは，それらの仮想関数をフックし，各々に特有な処理を施して，
	ラインセグメント図形・ジョイン図形・キャップ図形の実際の描画を行う
	IMG_Penクラスの該当描画メソッドに対して描画を依頼する
  @warning
	IMG_PathStrokeは，IMG_PathNormalStrokeかIMG_PathDashedStroke
	から生成されなければならない．なぜなら，そのままでは実際の描画を行う
	関数が仮想関数に設定されないからである．<br>
	IMG_PathStrokeを生成するには，IMG_Context, IMG_GraphicsContext,
	が生成されていなければならない．
 */
typedef struct IMG_PathStroke_L {

    IMG_Context		*context;		/*!< 管理用クラス	*/
    IMG_DisplayList	*display_list;		/*!< 描画先クラス	*/
    IMG_GraphicsContext	*graphics_context;	/*!< グラフィック属性クラス*/
    IMG_Path		*path;			/*!< 描画対象Pathクラス	*/
    IMG_Pen		*pen;			/*!< Pen描画クラス	*/

    /* vertual function の定義	*/
    /*! ジョイン図形を描画するIMG_Penクラスのメソッドへの仮想関数	*/
    int (*Draw_JoinPoint)( IMG_PathStrokePointer, IMG_Point *, IMG_Point *, IMG_Point * );
    /*! キャップ図形を描画するIMG_Penクラスのメソッドへの仮想関数	*/
    int (*Draw_CapPoint)( IMG_PathStrokePointer, IMG_Point *, IMG_Point * );
    /*! ラインセグメント図形を描画するIMG_Penクラスのメソッドへの仮想関数	*/
    int (*Draw_Line)( IMG_PathStrokePointer, IMG_Point *, IMG_Point * );

	/* AR1505 */
	int (*Reset)( IMG_PathStrokePointer );

    /*破線描画用変数

      破線描画時に必要な形状データを，IMG_GraphicsContext内からコピーして
      保持しておくための変数である
     */
    IMG_LineStyle		style;		/*!< 線形状			*/
    IMG_PathDash_CorrectType	correct_type;	/*!< 破線補正タイプ		*/
    unsigned long		count;		/*!< 破線要素数			*/
    IMG_FLOAT			*data;		/*!< 破線の各要素の長さの配列	*/

    /*描画用変数

      破線の描画に際して，前もって計算しておいたり，
      ラインセグメント図形・ジョイン図形・キャップ図形間にまたがって
      影響を与える変数は，処理の親にあたるIMG_PathStrokeクラスで保持する
      必要がある．
     */
    IMG_FLOAT		corrected_length;	/*!< 不明				*/
    IMG_FLOAT		drawn_length;		/*!< 破線描画時に描画完了した破線要素長	*/
    IMG_FLOAT		drawn_ratio;		/*!< 破線描画時の破線描画長補正用	*/
    unsigned long	drawn_count;		/*!< 描画した破線セグメントの数		*/
    unsigned long	total_drawn_count;	/*!< 描画した破線セグメントの総数	*/

    unsigned long	prev_dash_draw_count;	/*!< 不明				*/
    IMG_FLOAT		dash_draw_offset;	/*!< 破線描画セグメント長へのオフセット	*/

	long			dash_offset_flag;	/* test !!!! */

} IMG_PathStroke;

IMG_PathStroke *IMG_PathStroke_Init( IMG_Context *, IMG_DisplayList *,
				     IMG_GraphicsContext *, IMG_Path *, IMG_Pen * );
IMG_PathStroke *IMG_PathStroke_Create( IMG_Context *, IMG_DisplayList *,
				       IMG_GraphicsContext *, IMG_Path *, IMG_Pen * );
int IMG_PathStroke_Destroy( IMG_PathStroke * );
int IMG_PathStroke_Stroke( IMG_PathStroke *, IMG_PathBuffer * );

#endif /* IMG_PATHSTROKE_H_INCLUDED */
