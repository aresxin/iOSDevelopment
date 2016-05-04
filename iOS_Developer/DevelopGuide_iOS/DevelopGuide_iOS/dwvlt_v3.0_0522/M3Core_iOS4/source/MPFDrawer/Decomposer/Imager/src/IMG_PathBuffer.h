/*!
  @file IMG_PathBuffer.h
  @brief PathBuffer classヘッダファイル

  HBPS Imager内部でPathを格納するを提供するIMG_PathBuffer classのヘッダファイルである．<br>

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPSC SD推) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2003-07-07
  @version 0.1

  Copyright (C) Fuji Xerox Co.,Ltd. 2001. All rights reserved.
  Created:	Apr,9,2001	Toshio Yamazaki
 */

#include "IMG_Common.h"
#include "IMG_Context.h"
#include "IMG_BezierData.h"

#ifndef IMG_PATHBUFFER_H_INCLUDED
#define IMG_PATHBUFFER_H_INCLUDED

/* DEBUG用DUMP関数			*/
/* 以下のdefineを有効にするとOK		*/
/* #define IMG_DEBUG_PATHBUFFER		*/

/*! パス図形ヘッダ
  IMG_PathBuffer内に蓄えられる点列のタイプと，
  頂点数を格納する構造体.<br>
  頂点のデータは，IMG_Common.hの
  IMG_Pointを使用する．
 */
typedef struct {
    unsigned short	type;	/*!< パス図形のタイプ		*/
    unsigned short	number;	/*!< パス図形内頂点の個数	*/
} IMG_PathElementHeader;

/*! パス図形タイプ定義
  IMG_PathElementHeader::typeに入れる定数
 */
typedef enum {
    IMG_PATHELEMENT_TYPE_MOVETO,	/*!< movetoパス図形			*/
    IMG_PATHELEMENT_TYPE_LINETO,	/*!< linetoパス図形			*/
    IMG_PATHELEMENT_TYPE_OPEN,		/*!< 直前のサブパスはopenパスである	*/
    IMG_PATHELEMENT_TYPE_CLOSE		/*!< 直前のサブパスはcloseパスである	*/
} IMG_PathElementType;

/*! IMG_PathBufferRep内バッファのサイズ
  実サイズ [byte] で指定する
*/
#define IMG_PATHBUFFER_SIZE	(1024*4)

/*! パスデータ実体格納構造体

  IMG_PathBufferからfriendアクセスされて，
  格納データの実体を保存するクラスである．<br>
  IMG_PATHBUFFER_SIZE [byte]分の領域を自分自身に持ち，
  自分自身を端方向リストで繋ぐことにより，可変長のFIFOバッファとして振舞う．<br>
  また，IMG_PathBufferRepのメソッドは，IMG_PathBufferがフレンドなので，
  static 関数として IMG_PathBuffer.cに直接記述されている．

  @warning
  現実装では，4byte単位の書き込みのみを保証する．<br>
  IMG_PathBufferクラスからの操作のみを保証する．
 */
typedef struct IMG_PathBufferRep_L{
    /*
     * IMG_PathBufferRepに必要なメンバ
     */
    struct IMG_PathBufferRep_L	*next;	/*!< 単方向List構造のためのポインタ	*/
    int			buffer_size;	/*!< bufferの最大サイズIMG_PATHBUFFER_SIZEと等しい	*/
    int			used_bytenum;	/*!< 使用されている buffer の総バイト数	*/
    int			readed_bytenum;	/*!< peekメソッドで読み込んだ総バイト数	*/
    
    double		tmp_buffer[IMG_PATHBUFFER_SIZE/sizeof(double)];
    /*!< data object が実際に格納されるバッファ．
      double なのは,VX-Works上でアライメントのバグがでるから	*/

    /* method 内で使用されるポインタ				*/
    unsigned char	*buffer;		/*!< tmp_bufferへのポインタ			*/
    unsigned char	*current_write_pos;	/*!< tmp_buffer上で現在書き込んでいる位置[byte]	*/

    IMG_Context		*context;	/*!< HBPSにてメモリ管理をしてくれるクラス */
} IMG_PathBufferRep;

/*
 * IMG_PathBufferRepのマクロで実装されるメソッド
 * 引数は IMG_PathBufferRepへのポインタ
 */
/*! IMG_PathBufferRepの最大サイズを取得する			*/
#define IMG_PATHBUFFERREP_GETMAXSIZE(r)		IMG_PATHBUFFER_SIZE
/*! IMG_PathBufferRepの開き領域サイズを取得する			*/
#define IMG_PATHBUFFERREP_GETSPACESIZE(r)	(IMG_PATHBUFFER_SIZE-(r->used_bytenum))
/*! これから描きこむIMG_PathBufferRep::tmp_buffer[]の書き込み位置へのポインタを取得する	*/
#define IMG_PATHBUFFERREP_GETCURRENTWRITEPOS(r)	(r->current_write_pos)

/*!パスデータ格納クラス

  パス図形データを受け取ってIMG_PathBufferRepに格納するクラス．<br>
  パスを操作するクラス，例えばIMG_Path，は，このクラスをラッパーにして，
  パス図形を格納する可変長のデータ領域を操作する．
  つまり，クライアントにおいては，IMG_PathBufferRepを意識することなく，
  IMG_PathBufferオブジェクトを操作することにより，パスの格納機能を利用することが出来る．
 */
typedef struct {
    /* IMG_PathBufferに必要なメンバ	*/
    IMG_PathBufferRep	*top;		/*!< 先頭のIMG_PathBufferRep．線形リストになってるから． */
    IMG_PathBufferRep	*write_current;	/*!< 現在書き込み中の IMG_PathBufferRep		*/
    /* Peekメソッド用のメンバ		*/
    IMG_PathBufferRep	*read_current;	/*!< 現在読み込み中の IMG_PathBufferRep		*/

    unsigned char	*writing_header_pos; /*!< 可変長図形構築用変数			*/

    IMG_Context		*context;	/*!< HBPSにてメモリ管理をしてくれるクラス	*/
} IMG_PathBuffer;

/*
 * Path Bufferパッケージ Public I/F
 */
IMG_PathBuffer * IMG_PathBuffer_Create( IMG_Context * );
int IMG_PathBuffer_Destroy( IMG_PathBuffer * );
void IMG_PathBuffer_Clear( IMG_PathBuffer * );
/*
 * Path Bufferパッケージ Path構築用 I/F
 */
int IMG_PathBuffer_AppendMoveTo( IMG_PathBuffer *, IMG_Point *, int );
int IMG_PathBuffer_AppendLineTo( IMG_PathBuffer *, IMG_Point *, int );
int IMG_PathBuffer_AppendBezierTo( IMG_PathBuffer *, IMG_BezierData *, int );
int IMG_PathBuffer_AppendClose( IMG_PathBuffer * );
int IMG_PathBuffer_AppendOpen( IMG_PathBuffer * );
/*
 * Path Bufferパッケージ データ読み出し用 I/F
 */
void IMG_PathBuffer_PeekStart( IMG_PathBuffer * );
IMG_PathElementHeader * IMG_PathBuffer_Peek( IMG_PathBuffer *, IMG_Point ** );
/*
 * Path Bufferパッケージ 可変長Pathデータ構築用 I/F
 */
int IMG_PathBuffer_StartMoveTo( IMG_PathBuffer *, IMG_Point * );
int IMG_PathBuffer_StartLineTo( IMG_PathBuffer *, IMG_Point * );
int IMG_PathBuffer_AppendPoint( IMG_PathBuffer *, IMG_Point * );
/*
 * Path Bufferパッケージ座標変換用 I/F
 */
int IMG_PathBuffer_Transform( IMG_PathBuffer *, IMG_Matrix * );
int IMG_PathBuffer_Transform_NoPt( IMG_PathBuffer *, IMG_Matrix * );

/* Error Code は #define の羅列 */
#define IMG_PATHBUFFER_ERRORCODE_NOERROR	0	/*!< IMG_PathBuffer成功エラーコード */
#define IMG_PATHBUFFER_ERRORCODE_ERROR	       -1	/*!< IMG_PathBuffer失敗エラーコード */

#ifdef IMG_DEBUG_PATHBUFFER
#include <stdio.h>

void IMG_PathBuffer_Print_Point( FILE *, IMG_Point *, int num );
void IMG_PathBuffer_Print_PathElementHeader( FILE *, IMG_PathElementHeader * );
void IMG_PathBufferRep_Print( FILE *, IMG_PathBufferRep * );
void IMG_PathBuffer_Print( FILE *, IMG_PathBuffer * );

void IMG_PathBuffer_Dump( IMG_Context *, IMG_PathBuffer * );

#endif /* IMG_DEBUG_PATHBUFFER */

#endif /* IMG_PATHBUFFER_H_INCLUDED */
