/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_Composer.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */


/*
 SKDComp.h	07/15/96	M.Chikyu Created.

 Ver0.83	02/27/97 クリップボックスの左端をラスタの座標０とする
 Ver0.84	03/04/97 旧 SPARC Compiler(C++3.0) 対応
 Ver0.85	03/06/97 エッジリスト変更(構造体とグレイスケール対応)
 Ver0.85a	03/07/97 SKD_ScanConvをSKD_ComposerにSKD_ScanConvPSと
						SKD_ScanConvTTをSKD_ComposerIFに変更
 Ver0.86	03/13/97 バウンディングボックスを別設定とし、補正を実行。シリアル番号の領域を追加。
 Ver0.87	03/31/97 曲線の制御点がすべて同じ場合に0で除算することを防ぐ様変更
 Ver0.90	05/15/97 輪郭描画サポート(プロト1)
 Ver0.91	06/10/97 輪郭線描画バグフィックス制御点と端点がほぼ一直線に並ぶ場合の不具合を修正
 Ver0.91a	06/13/97 Processer対応、SKD_ を flib_ に変更
 Ver0.91c	06/18/97 コントロールコード関連を修正
 Ver0.92	06/20/97 DrawPointTT()を修正、Start,EndのOffPointに対応
 Ver0.93	07/22/97 MakeLine()を整数化
 Ver0.94	07/25/97 ベジェの変更、ポインタ渡し
 Ver1.50a	08/05/97 MakeLineの変更（ドロップアウトの簡略化）
 Ver1.50b	08/07/97 MakeLineの変更（垂直線の登録法変更）
 Ver1.60	08/19/97 ドロップアウト処理の変更
 Ver1.61	08/29/97 ドロップアウト処理の変更
 Ver1.62	09/10/97 バウンディングボックス補正
 Ver1.63	10/17/97 バウンディングボックスの左下を原点に変更
 Ver1.64	10/17/97 flib_EdgeRegを削除し、オーバーヘッドを削減
 Ver1.65	10/27/97 MakeLine()を改良
 Ver1.80	10/28/97 2分探索木から挿入ソートに変更
 Ver1.80a	10/28/97 flib_ScanLineSCT::MakeLine()を一部変更
 Ver1.81	10/31/97 メモリを描画方法が異なるオブジェクトで共用化
 Ver1.81a	11/05/97 グレイスケールのバグを修正
 Ver1.81b	02/19/98 RegBuffer()の呼び出し回数を減らす
 Ver1.81c	02/25/98 アドレス計算をテーブル参照に変更
 Ver1.81d	02/26/98 描画コマンドへのパラメータ数を縮小
 Ver1.81e	02/27/98 ハッシュ関数を削除
 Ver1.81f	02/27/98 メモリ確保の上限を設定
 Ver1.81g	03/10/98 グレイスケールにDIANA対応を追加
 Ver1.82	03/12/98 flib_Composerとflib_CompoerIFの構成を変更
 Ver1.82a	03/25/98 マクロ名を一部変更
 Ver1.82b	04/28/98 マクロ変更に伴って一部変更、DrawPoint_TTを変更
 Ver1.82c	05/13/98 DIANA用に出力形式を変更
 Ver1.82d	05/19/98 DrawPointTTを一部修正
 Ver1.82e	06/10/98 ヘッダの変更に伴って一部修正
 Ver1.82f	06/17/98 グレイスケールでスキャンコントロールを有効にする
 Ver1.82g	06/17/98 StartとEndが重なっている場合に対応
 Ver1.82h	06/19/98 グレイスケールに細線抜け防止
 Ver1.82i	06/24/98 細線抜け防止処理にカウンタ設置
 Ver1.82j	07/07/98 スプラインに新ロジック追加
 Ver1.82k	07/08/98 新ロジックをデフォルト、細線抜け判定を追加
 Ver2.00	07/22/98 DIANA対応部分を変更、6ラインでパターン判定、斜め線判定を追加
 Ver2.05a	09/10/98 ボールド・細線表示対応α版
 Ver2.05b 09/25/98 ボールドバグフィックス
 Ver2.06	04/13/99 DIANA対応、前後上下のパターンを判定
 Ver2.06a	05/14/99 DIANA対応、パターン追加
 Ver2.07	06/28/99 m_edgeListSize CMP_UINT16からCMP_UINT32



	Composer Test 5

*/

#ifndef _OL_COMPOSER_H_INCLUDED_

#define	_OL_COMPOSER_H_INCLUDED_

#include "OL_ComposerTypes.h"
#include "OL_Context.h"

/* DIANAの波形引寄せ対応チェック */
#define CMP_DIANA
/* 6ライン参照版 */
#define CMP_DIANA_NEW
/* グレイの細線抜け防止ルーチン */
#define CMP_DIANA_2
/* グレイの細線抜け防止ルーチン */
#define CMP_DIANA_3
/* グレイの細線抜け防止ルーチンのカウンタ */
/*#define CMP_COVERAGE */
/* 反転出力用マクロ */
/* #define CMP_REVERSE */
/* スプライン旧ロジックマクロ */
/*#define CMP_OLDSP */


#define CMP_NODEDEPTH		15

/* メモリを開放しない縦方向のピクセルサイズの上限です */
#define CMP_LIMIT_SIZE		140

/* スプラインの新ロジックで用いる閾値です */
#ifndef CMP_OLDSP
#define CMP_SP_DIFF		1.0
#endif //CMP_OLDSP



/* -------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------*/

/*
 CMP_EdgeNode
 エッジ格納Tree基本ノードオブジェクト
*/
typedef struct CMP_EdgeNode_t {
	CMP_PIXELUNIT	point;			/* 座標値 */
	CMP_INT16	type;			/* ワインディングの方向 下から上が+、逆が- */
	CMP_INT16	type2;			/* ワインディングの方向 左から右が+、逆が- */
	CMP_UINT16	count;			/* 登録ノード数 */
	struct CMP_EdgeNode_t	*offset;	/* 自分より小さいノードへのポインタ */
} CMP_EdgeNode;


/* -------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------*/


typedef struct CMP_Context_t {

    OL_Context		*context;
    CMP_EdgeNode	*g_bufferPtr;		/* エッジリスト配列の先頭ポインタを格納 */
    CMP_INT32		g_bufferSize;		/* エッジリスト配列のサイズ */
    CMP_EdgeNode	**g_hashTblPtr;		/* ハッシュテーブル（エッジリストへのオフセット） */
    CMP_INT32		g_hashTblSize;		/* ハッシュテーブルのサイズ */
    CMP_INT32		g_cntBuffer;		/* Bufferのノード数を格納 */
    CMP_PIXELUNIT	g_maxUpper;		/* エッジの最大値（上） */
    CMP_PIXELUNIT	g_maxRight;		/* エッジの最大値（右） */
    
} CMP_Context;


/* -------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------*/
 
/*
 CMP_ScanLine
 ライン生成オブジェクト
*/

enum {
    CMP_SCANLINE = 0,
    CMP_SCANLINESCT = 1,
    CMP_SCANLINECON = 2,
    CMP_SCANLINEBLD = 3,
    CMP_SCANLINELGT = 4
  };


typedef struct CMP_ScanLine_t {
    CMP_Context		*context;

    CMP_Point		m_pD0;
    CMP_Point		m_pD1;
    CMP_Point		m_pD2;
    CMP_Point		m_pD3;
    CMP_Point		m_fnEnd;

    CMP_PIXELUNIT	m_curLine;
    CMP_PIXELUNIT	m_curCol;
    CMP_Point		m_ptStart;
    CMP_Point		m_ptCur;

    CMP_INT16		m_magWinding;

    CMP_UINT32		type;

    CMP_VOID		*child;

/*  from Globe4 
    CMP_VOID		(*SetStatus)(struct CMP_ScanLine_t *handle, CMP_PIXELUNIT contWidth);
*/
    CMP_VOID		(*SetStatus)(struct CMP_ScanLine_t *handle, CMP_DecorationParam *decParam);
    
    /* change VOID to UINT32 */
    CMP_UINT32		(*MakeLine)(struct CMP_ScanLine_t *handle, CMP_Point *ptNext);
    CMP_UINT32		(*MoveTo)(struct CMP_ScanLine_t *handle, CMP_Point *ptStart);
    CMP_UINT32		(*LineTo)(struct CMP_ScanLine_t *handle, CMP_Point *ptNext);
    CMP_UINT32		(*QSplineTo)(struct CMP_ScanLine_t *handle, CMP_Point *ptCtl, CMP_Point *ptEnd);
    CMP_UINT32		(*BezierTo)(struct CMP_ScanLine_t *handle, CMP_Point *ptCtl1, CMP_Point *ptCtl2, CMP_Point *ptEnd);
    CMP_UINT32		(*Close)(struct CMP_ScanLine_t *handle);

} CMP_ScanLine;


/* public */

/* コンストラクタ */
CMP_ScanLine 	*CMP_ScanLine_New(CMP_Context *context, CMP_UINT32 type);

CMP_VOID 	CMP_ScanLine_Delete(CMP_ScanLine *handle);

/* パラメータ設定 */
/*  from Globe4 
CMP_VOID	CMP_ScanLine_SetStatus(CMP_ScanLine *handle, CMP_PIXELUNIT contWidth); 
*/
CMP_VOID	CMP_ScanLine_SetStatus(CMP_ScanLine *handle, CMP_DecorationParam *decParam);  /* virtual */
	
/* change VOID to UINT32 */
CMP_UINT32	CMP_ScanLine_MoveTo(CMP_ScanLine *handle, CMP_Point *ptStart); /* virtual */
CMP_UINT32	CMP_ScanLine_LineTo(CMP_ScanLine *handle, CMP_Point *ptNext); /* virtual */
CMP_UINT32	CMP_ScanLine_QSplineTo(CMP_ScanLine *handle, CMP_Point *ptCtl, CMP_Point *ptEnd); /* virtual */
CMP_UINT32	CMP_ScanLine_BezierTo(CMP_ScanLine *handle, CMP_Point *ptCtl1, CMP_Point *ptCtl2, CMP_Point *ptEnd); /* virtual */
CMP_UINT32	CMP_ScanLine_Close(CMP_ScanLine *handle); /* virtual */

/* 終点座標取得関数 */
CMP_Point	EndPoint(CMP_ScanLine *handle);


/* private/protected */

/* 内部利用関数 */
CMP_VOID	CMP_ScanLine_SwapPt(CMP_ScanLine *handle, CMP_Point* a, CMP_Point* b);

CMP_VOID	CMP_ScanLine_RotatePt(CMP_ScanLine *handle, CMP_Point *a);

/* オブジェクト登録関数 */
/* change VOID to UINT32 */
CMP_UINT32	CMP_ScanLine_MakeLine(CMP_ScanLine *handle, CMP_Point *ptNext); /* virtual */
#ifdef CMP_OLDSP
CMP_UINT32	CMP_ScanLine_MakeQSpline(CMP_ScanLine *handle);
#endif //CMP_OLDSP
CMP_UINT32	CMP_ScanLine_MakeBezier(CMP_ScanLine *handle);

/* バッファに登録 */
/* change VOID to UINT32 */
CMP_UINT32	CMP_ScanLine_RegBuffer(CMP_ScanLine *handle, CMP_PIXELUNIT line, CMP_PIXELUNIT point, CMP_INT16 posType);
CMP_UINT32	CMP_ScanLine_GetBuffer(CMP_ScanLine *handle);




/*
 CMP_ScanLineSCT
 ライン生成オブジェクト(スキャンコントロール)
*/
typedef struct CMP_ScanLineSCT_t {
    CMP_ScanLine *super;
} CMP_ScanLineSCT;

/* public */
/*  コンストラクタ */
CMP_ScanLineSCT *CMP_ScanLineSCT_New(CMP_ScanLine *super, CMP_UINT32 type);

CMP_VOID 	CMP_ScanLineSCT_Delete(CMP_ScanLineSCT *self);

/* protected */
/* オブジェクト登録関数 */
/* change VOID to UINT32 */
CMP_UINT32	CMP_ScanLineSCT_MakeLine(CMP_ScanLine *super, CMP_Point *ptNext); /* vertual */
CMP_UINT32	CMP_ScanLineSCT_RegBuffer1(CMP_ScanLineSCT *handle, CMP_PIXELUNIT line, CMP_PIXELUNIT point, CMP_INT16 posType);
CMP_UINT32	CMP_ScanLineSCT_RegBuffer2(CMP_ScanLineSCT *handle, CMP_PIXELUNIT line, CMP_PIXELUNIT point, CMP_INT16 posType2);
CMP_UINT32	CMP_ScanLineSCT_RegBuffer3(CMP_ScanLineSCT *handle, CMP_PIXELUNIT line, CMP_PIXELUNIT point, CMP_INT16 posType, CMP_INT16 posType2);





/*
 CMP_ScanLineCON
 ライン生成オブジェクト(輪郭線描画)
*/
typedef struct CMP_ScanLineCON_t {
    /* 輪郭線の半分の太さ */
    CMP_Point		m_ptStart2;
    CMP_Point		m_ptCur2;
/* from Globe4
    CMP_POINTUNIT	m_adjPoint;
    CMP_POINTUNIT	m_halfWidth;
*/
    CMP_POINTUNIT	m_adjPoint_x;
    CMP_POINTUNIT	m_adjPoint_y;
    CMP_POINTUNIT	m_halfWidth_x;
    CMP_POINTUNIT	m_halfWidth_y;
    
    CMP_INT16		m_magFrame;
    CMP_INT16		m_magContour;
    
    CMP_ScanLine	*super;

} CMP_ScanLineCON;


/* public */
/* コンストラクタ */
CMP_ScanLineCON* CMP_ScanLineCON_New(CMP_ScanLine *super, CMP_UINT32 type);

CMP_VOID	CMP_ScanLineCON_Delete(CMP_ScanLineCON *handle);

/* パラメータ設定 */
/* from Globe4 
CMP_VOID	CMP_ScanLineCON_SetStatus(CMP_ScanLine *super, CMP_PIXELUNIT contWidth);
*/
CMP_VOID	CMP_ScanLineCON_SetStatus(CMP_ScanLine *super, CMP_DecorationParam *decParam); /* virtual */

/* 座標リスト生成関数 */
/* change VOID to UINT32 */
CMP_UINT32	CMP_ScanLineCON_MoveTo(CMP_ScanLine *super, CMP_Point *ptStart); /* virtual */
CMP_UINT32	CMP_ScanLineCON_LineTo(CMP_ScanLine *super, CMP_Point *ptNext); /* virtual */
CMP_UINT32	CMP_ScanLineCON_QSplineTo(CMP_ScanLine *super, CMP_Point *ptCtl, CMP_Point *ptNext); /* virtual */
CMP_UINT32	CMP_ScanLineCON_BezierTo(CMP_ScanLine *super, CMP_Point *ptCtl1, CMP_Point *ptCtl2, CMP_Point *ptNext); /* virtual */
CMP_UINT32	CMP_ScanLineCON_Close(CMP_ScanLine *super); /* virtual */

/* protected */
/* オブジェクト登録関数 */
/* change VOID to UINT32 */
CMP_UINT32	CMP_ScanLineCON_MakeCircle(CMP_ScanLineCON *handle, CMP_Point *ptEnd, CMP_Point *ptCenter);
CMP_Point	CMP_ScanLineCON_GetEndPoint(CMP_ScanLineCON *handle, CMP_Point ptCtl1, CMP_Point ptCtl2);
CMP_Point	CMP_ScanLineCON_GetBendPoint(CMP_ScanLineCON *handle, CMP_Point ptCtl1, CMP_Point ptCtl2, CMP_Point ptCtl3);



/*
 CMP_ScanLineBLD
 ライン生成オブジェクト(ボールド描画)
*/
/* from Globe4 
CMP_VOID CMP_ScanLineBLD_SetStatus(CMP_ScanLine *super, CMP_PIXELUNIT contWidth);
*/
CMP_VOID CMP_ScanLineBLD_SetStatus(CMP_ScanLine *super, CMP_DecorationParam *decParam); /* virtual */



/*
 CMP_ScanLineLGT
 ライン生成オブジェクト(ボールド描画)
*/
/*  from Globe4 
CMP_VOID CMP_ScanLineLGT_SetStatus(CMP_ScanLine *super, CMP_PIXELUNIT contWidth); 
*/
CMP_VOID CMP_ScanLineLGT_SetStatus(CMP_ScanLine *super, CMP_DecorationParam *decParam); /* virtual */



/* -------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------*/


/*
 CMP_EdgeBuffer
 エッジ格納Tree基本ノードオブジェクト
*/
#define CMP_NOT_USE	(-1)

enum{
    CMP_EDGEBUFFER 		= 0,
    CMP_EDGEBUFFERNZW 		= 1,
    CMP_EDGEBUFFERNZWSCT 	= 2,
    CMP_EDGEBUFFEREVOD 		= 3,
    CMP_EDGEBUFFEREVODSCT 	= 4,
    CMP_EDGEBUFFERLGT 		= 5
  };
    

typedef struct CMP_EdgeBuffer_t {
    CMP_Context		*context;

    CMP_EdgeNode	*m_tmpBufPtr;		/* g_bufferPtr */
    CMP_INT32		m_tmpBufSize;		/* g_bufferSize */

    CMP_INT16		m_paintState;
    CMP_INT16		m_paintFlag;
    CMP_INT16		m_paintFlag2;

    CMP_STATUS		status;

    CMP_UINT16		*m_edgeListHead;	/* エッジリストの先頭各ラインのサイズを格納 */
    CMP_EdgeList	*m_edgeList;		/* エッジリストの先頭ポインタを格納 */
    CMP_INT32		m_edgeListSize;		/* エッジリストのサイズ(BYTE単位） */
    CMP_UINT16		m_edgeAmount;		/* エッジの総数 */

    CMP_UINT32		type;

    CMP_VOID		(*RegList)(struct CMP_EdgeBuffer_t *handle, CMP_EdgeList** pList, CMP_UINT16 *cnt, CMP_EdgeNode *pNode);

} CMP_EdgeBuffer;

/* コンストラクタ */
CMP_EdgeBuffer 	*CMP_EdgeBuffer_New(CMP_Context *context, CMP_UINT32 type);

/* デストラクタ */
CMP_VOID 	CMP_EdgeBuffer_Delete(CMP_EdgeBuffer *handle);

/* ペイントロジックを設定する */
CMP_UINT32	CMP_EdgeBuffer_SetStatus(CMP_EdgeBuffer *handle);

/* 1ライン分のエッジリストを作成(配列にソートして登録) */
CMP_INT 	CMP_EdgeBuffer_MakeList(CMP_EdgeBuffer *handle);

CMP_VOID 	CMP_EdgeBuffer_BufferSort(CMP_EdgeBuffer *handle);

/* リスト構造に登録 */
CMP_VOID	CMP_EdgeBuffer_RegList(CMP_EdgeBuffer *handle, CMP_EdgeList** plist, CMP_UINT16 *cnt, CMP_EdgeNode *pNode);


/* -------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------*/


/*
 CMP_Composer
 エッジリスト生成オブジェクト
*/
typedef struct CMP_Composer_t {
    CMP_Context		context;

    /* エッジ抽出用オブジェクト */
    CMP_ScanLine	*m_genLine;
    CMP_ScanLine	*m_genLineNSC;
    CMP_ScanLine	*m_genLineSCT;
    CMP_ScanLine	*m_genLineCON;
    CMP_ScanLine	*m_genLineBLD;
    CMP_ScanLine	*m_genLineLGT;

    CMP_INT		m_ctlVal;			/* コントロールコード */
    CMP_INT		m_lineMag;			/* グレイスケール用拡大率 */
    CMP_INT		m_sftNum;			/* グレイスケール用シフト数 */
    CMP_INT		m_mskNum;			/* グレイスケール用ビットマスク */

/* from Globe4
    CMP_PIXELUNIT	m_contWidth;			
*/
    CMP_PIXELUNIT       m_contWidth_x;          	/* 輪郭線表示時の幅 */
    CMP_PIXELUNIT       m_contWidth_y;          	/* 輪郭線表示時の幅 */
    CMP_DecorationParam m_decParam;

    CMP_EdgeBuffer	*m_edgeBuffer;			/* エッジリスト格納 */
    CMP_EdgeBuffer	*m_edgeBufferNZW;		/* エッジリスト格納 */
    CMP_EdgeBuffer	*m_edgeBufferNZWSCT;		/* エッジリスト格納 */
    CMP_EdgeBuffer	*m_edgeBufferEVOD;		/* エッジリスト格納 */
    CMP_EdgeBuffer	*m_edgeBufferEVODSCT;		/* エッジリスト格納 */
    CMP_EdgeBuffer	*m_edgeBufferLGT;		/* エッジリスト格納 */
    CMP_VOID		*m_bufferPtr;			/* エッジリスト配列の先頭ポインタを格納 */
    CMP_INT32		m_bufferSize;			/* エッジリスト配列のサイズ */
    CMP_VOID		*m_hashTblPtr;			/* ハッシュテーブルの先頭ポインタを格納 */
    CMP_INT32		m_hashTblSize;			/* ハッシュテーブルのサイズ */

    /* 描画エリア設定用メンバ */
    CMP_BoundingBox	m_bbox;
    CMP_BoundingBox	m_cbox;
    CMP_POINTUNIT	m_offset_x;
    CMP_POINTUNIT	m_offset_y;
    CMP_UINT16		m_flgClose;			/* クローズフラグ */

    /* エッジリスト用メンバ */
    CMP_EdgeListInfo	m_edgeListInfo;
    CMP_VOID		*m_edgeList;
    CMP_UINT32		m_edgeListSize;
    CMP_UINT16		*m_lineSize;
    CMP_UINT16		m_lineSizeSize;

    /* ビットマップ用メンバ */
    CMP_BitmapInfo	m_bitmapInfo;
    CMP_VOID		*m_bitmap;
    CMP_INT32		m_bitmapSize;

    /* グレイスケール用メンバ */
    CMP_UINT16		*m_lineSizeGS;
    CMP_INT32		m_lineSizeGSSize;
    CMP_EdgeList_GS	*m_edgeListGS;
    CMP_INT32		m_edgeListGSSize;
    CMP_UINT16		m_edgeAmountGS;
#ifdef CMP_DIANA
    CMP_UINT8		*m_buffer[6];
#endif //CMP_DIANA

    CMP_STATUS status;

} CMP_Composer;



/* public */

/* コンストラクタ */
CMP_Composer* 	CMP_Composer_New(OL_Context *context);
/* デストラクタ */
CMP_VOID	CMP_Composer_Delete(CMP_Composer *handle);

/* 環境設定 */
/* from Globe4 
CMP_INT 	CMP_Composer_SetStatus(CMP_Composer *handle, CMP_INT ctlVal, CMP_PIXELUNIT contWidth);
*/
CMP_INT 	CMP_Composer_SetStatus(CMP_Composer *handle, CMP_INT ctlVal, CMP_DecorationParam *decParam);


/* protected */

/* 描画領域を設定する */
/* virtual */
CMP_INT 	CMP_Composer_SetActiveArea(CMP_Composer *handle, CMP_BoundingBox *bbox, CMP_BoundingBox *cbox);



/* エッジリスト生成 */
	
/* エッジリストを生成する。 */
CMP_INT 	CMP_Composer_MakeList(CMP_Composer *handle);
	
/* エッジリストからグレイスケールエッジリストを生成 */
/* change VOID to UINT32 */
CMP_UINT32 	CMP_Composer_StoreEdgeListGS(CMP_Composer *handle);

#ifdef CMP_DIANA
/* グレイスケール DIANA対応 */
CMP_UINT32 	CMP_Composer_StoreEdgeListGS_D(CMP_Composer *handle);
#endif //CMP_DIANA



/* ビットマップ生成 */

/* エッジリストからラスターを生成 */
CMP_VOID 	CMP_Composer_StoreRaster(CMP_Composer *handle);
	
/* エッジリストからラスターを生成(グレイスケール対応) */
CMP_VOID 	CMP_Composer_StoreRasterGS(CMP_Composer *handle);

#ifdef CMP_DIANA
/* グレイスケール DIANA対応 */
CMP_UINT32 	CMP_Composer_StoreRasterGS_D(CMP_Composer *handle);
CMP_UINT32 	CMP_Composer_MakeGrayLine_D(CMP_Composer *handle, CMP_UINT8 *buffer, 
					    CMP_EdgeList* edgeList, CMP_UINT16* edgeCnt, CMP_PIXELUNIT line);
#endif //CMP_DIANA

/* グレイスケール用関数 */
CMP_UINT32	CMP_Composer_MakeGrayLine(CMP_Composer *handle, CMP_UINT8 *buffer, CMP_EdgeList *edgeList, CMP_UINT16 edgeCnt);
CMP_UINT16	CMP_Composer_MakeGrayEdgeList(CMP_Composer *handle, CMP_UINT8 *buffer, CMP_EdgeList_GS *edgeList);

/* メモリサイズ確認関数 */
CMP_UINT32 	CMP_Composer_MemCheck(CMP_Composer *handle, CMP_INT32 NewSize, CMP_INT32 *CurSize, CMP_VOID **CurPointer);


/* from CMP_ComposerIF */

/* 閉曲線を閉じる */
CMP_INT 	CMP_Composer_Close(CMP_Composer *handle);

/* 閉曲線の始点に移動する */
CMP_INT 	CMP_Composer_Move(CMP_Composer *handle, CMP_Point ptFirst);

/* ラインのエッジをTree構造に登録 */
CMP_INT 	CMP_Composer_DrawLine(CMP_Composer *handle, CMP_Point ptNext);

/* 2次BスプラインのエッジをTree構造に登録 */
CMP_INT 	CMP_Composer_DrawQSpline(CMP_Composer *handle, CMP_Point ptCtl, CMP_Point ptNext);

/* 3次ベジェのエッジをTree構造に登録 */
CMP_INT 	CMP_Composer_DrawBezier(CMP_Composer *handle, CMP_Point ptCtl1, CMP_Point ptCtl2, CMP_Point ptNext);

/* エッジリスト抽出インターフェイス */

/* 渡されたバッファにエッジリストをコピーする */
CMP_EdgeListInfo CMP_Composer_GetEdgeList(CMP_Composer *handle, CMP_VOID *edgeList);

/* エッジリストのサイズを得る */
CMP_INT32 	CMP_Composer_GetEdgeListSize(CMP_Composer *handle);


/* ビットマップ抽出インターフェイス */

/* 渡されたバッファにビットマップを作成する */
CMP_BitmapInfo CMP_Composer_GetBitmap(CMP_Composer *handle, CMP_VOID *bitmap);

/* ビットマップのサイズを得る */
CMP_INT32 	CMP_Composer_GetBitmapSize(CMP_Composer *handle);


/* -------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------------*/



/*
 CMP_ComposerIF
 エッジリスト生成オブジェクト 
*/
typedef struct CMP_ComposerIF{
    OL_Context *context;
    CMP_Composer *composer;
} CMP_ComposerIF;


/* public */

/* コンストラクタ */
CMP_ComposerIF 	*CMP_ComposerIF_New(OL_Context *context);

/* デストラクタ */
CMP_VOID	CMP_ComposerIF_Delete(CMP_ComposerIF *handle);

/* 環境設定 */
/* from Globe4 
CMP_INT 	CMP_ComposerIF_SetStatus(CMP_ComposerIF *handle, CMP_INT ctlVal, CMP_PIXELUNIT contWidth);
*/
CMP_INT 	CMP_ComposerIF_SetStatus(CMP_ComposerIF *handle, CMP_INT ctlVal, CMP_DecorationParam *decParam);

/* 描画領域設定インターフェイス */
CMP_INT 	CMP_ComposerIF_SetActiveArea(CMP_ComposerIF *handle, CMP_BoundingBox *bbox, CMP_BoundingBox *cbox);


/* 描画インターフェイス */

/* point を置く(for PostScript type interpriter) */
CMP_INT 	CMP_ComposerIF_DrawPointPS(CMP_ComposerIF *handle, CMP_UINT8 *pathList, CMP_Point *ptList, 
					   CMP_BoundingBox *bbox, CMP_BoundingBox *cbox);

/* point を置く(for TrueType type interpriter) */
CMP_INT 	CMP_ComposerIF_DrawPointTT(CMP_ComposerIF *handle, CMP_UINT8 *attrib, CMP_Point *ptList, 
					   CMP_BoundingBox *bbox, CMP_BoundingBox *cbox);


/* エッジリスト抽出インターフェイス */

/* 渡されたバッファにエッジリストをコピーする */
CMP_EdgeListInfo CMP_ComposerIF_GetEdgeList(CMP_ComposerIF *handle, CMP_VOID *edgeList);

/* エッジリストのサイズを得る */
CMP_INT32 	CMP_ComposerIF_GetEdgeListSize(CMP_ComposerIF *handle);


/* ビットマップ抽出インターフェイス */

/* 渡されたバッファにビットマップを作成する */
CMP_BitmapInfo CMP_ComposerIF_GetBitmap(CMP_ComposerIF *handle, CMP_VOID *bitmap);

/* ビットマップのサイズを得る */
CMP_INT32 	CMP_ComposerIF_GetBitmapSize(CMP_ComposerIF *handle);


#endif //_OL_COMPOSER_H_INCLUDED_
