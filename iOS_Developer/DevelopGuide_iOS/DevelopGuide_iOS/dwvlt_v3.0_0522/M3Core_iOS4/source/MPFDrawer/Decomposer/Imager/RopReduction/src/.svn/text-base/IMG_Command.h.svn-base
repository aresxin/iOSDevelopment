/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Command.h - コマンドクラスの定義
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_Command_h
#define INC_IMG_Command_h

#include "IMG_Builtin.h"
#include "IMG_Context.h"
#include "IMG_ClassPointer.h"

/*
 * コマンド種別の定義
 */
typedef enum {
	IMG_COMMAND_NOKIND				= 0x00,		/* NULL */
	IMG_COMMAND_SETROP				= 0x01,		/* ROP設定命令 */
	IMG_COMMAND_ATTRIBUTE_BRUSH		= 0x02,		/* 描画色設定 */
	IMG_COMMAND_ATTRIBUTE_SHAPE		= 0x04,		/* 形状属性設定命令 */
	IMG_COMMAND_CLIP				= 0x08,		/* クリップ命令 */
	IMG_COMMAND_DRAWING_GRAPHICS	= 0x10,		/* グラフィックス描画命令 */
	IMG_COMMAND_DRAWING_IMAGE		= 0x20,		/* イメージ描画命令 */
	IMG_COMMAND_PATH				= 0x40,		/* パス構築命令 */
	IMG_COMMAND_ALL					= 0xFF,		/* すべてのコマンドを示す */
	IMG_COMMAND_ATTRIBUTE			= IMG_COMMAND_ATTRIBUTE_BRUSH | IMG_COMMAND_ATTRIBUTE_SHAPE,
	IMG_COMMAND_DRAWING				= IMG_COMMAND_DRAWING_GRAPHICS | IMG_COMMAND_DRAWING_IMAGE,
} IMG_CommandKind;

/*
 * 蓄積のためのコマンドコード
 */
typedef enum img_commandcode {

    /* 描画属性指定コマンド（整数型パラメータ）*/
    IMG_CMD_INT_RC = 0x4142,	/* クリップ領域の指定 */
    IMG_CMD_INT_CC = 0x4143,	/* カレントパスをクリップ領域に指定 */
    IMG_CMD_INT_LW = 0x4144,    /* 線幅の指定 */
    IMG_CMD_INT_LC = 0x4145,    /* ラインキャップの指定    */
    IMG_CMD_INT_LJ = 0x4146,    /* ラインジョインの指定    */
    IMG_CMD_INT_ML = 0x4147,    /* マイターリミットの指定 */
    IMG_CMD_INT_AS = 0x4149,    /* ストロークの調整 */
    IMG_CMD_INT_FM = 0x414A,    /* 塗りつぶし規則の指定 */
    IMG_CMD_INT_SM = 0x414B,    /* 描画方式の指定 */
    IMG_CMD_INT_RM = 0x414C,    /* 論理演算モードの指定 */
    IMG_CMD_INT_SC = 0x414D,    /* ソリッドカラー指定 */
    IMG_CMD_INT_PH = 0x414E,    /* パターンの指定(ハッチタイプ) */
    IMG_CMD_INT_PM = 0x414F,    /* パターンの指定(マスクタイプ) */
    IMG_CMD_INT_PC = 0x4150,    /* パターンの指定(フルカラータイプ) */
    IMG_CMD_INT_BC = 0x4151,    /* バックグラウンド描画色の指定 */
    IMG_CMD_INT_IC = 0x4152,    /* クリップ領域の初期化 */
    IMG_CMD_INT_SG = 0x4646,    /* 補正描画方式の指定 */

    /* 描画属性指定コマンド（実数型パラメータ）*/
    IMG_CMD_REAL_SA = 0x4161,	/* 座標系の指定  */
    IMG_CMD_REAL_LT = 0x4168,	/* 線の形状の指定 */

    /* パスコマンド（整数型パラメータ）*/
    IMG_CMD_INT_IP = 0x4241,	/* カレントパスの初期化 */
    IMG_CMD_INT_CP = 0x4243,	/* 始点と終点を結ぶ */
    IMG_CMD_INT_SR = 0x4244,	/* パスの描画 */

    /* パスコマンド（実数型パラメータ）*/
    IMG_CMD_REAL_MP = 0x4262,	/* カレントポイントの移動 */
    IMG_CMD_REAL_AL = 0x4270,	/* 線分パスの追加 */
    IMG_CMD_REAL_AR = 0x4276,	/* 長方形パスの追加 */

    /* 描画コマンド（相対＆可変長整数型パラメータ）*/
    IMG_CMD_INT_QS = 0x432C,	/* スキャンラインの描画 */
 
    /* 描画コマンド（整数型パラメータ）*/
    IMG_CMD_INT_SL = 0x4341,	/* 線分の描画 */
    IMG_CMD_INT_DR = 0x4347,	/* 長方形の描画 */
    IMG_CMD_INT_RS = 0x434F,	/* 長方形集合の描画(HB拡張命令) */

    /* 描画コマンド（実数型パラメータ） */
    IMG_CMD_REAL_DM = 0x4370,	/* イメージマスクの描画 */
    IMG_CMD_REAL_DI = 0x4371,	/* イメージの描画(単一指定) */
	IMG_CMD_REAL_DC = 0x4362,	/* 円弧描画 */
	IMG_CMD_REAL_DE = 0x4363,	/* 楕円弧描画 */
	IMG_CMD_REAL_DB = 0x4366,	/* Bezier描画 */
	IMG_CMD_REAL_RR = 0x4368,	/* 角丸矩形描画 */

    /* フォントコマンド（実数型パラメータ）*/
    IMG_CMD_REAL_DF = 0x4469,	/* ダウンロードした文字データの描画 Ａ */

    /* ジョブ制御コマンド（整数型パラメータ）*/
    IMG_CMD_INT_JS = 0x4541,	/* ジョブの開始 */
    IMG_CMD_INT_JE = 0x4542,	/* ジョブの終了 */
    IMG_CMD_INT_PE = 0x4544,	/* ページの終了 */

    /* ジョブ制御コマンド（実数型パラメータ）*/
    IMG_CMD_REAL_PN = 0x4563,	/* ページの開始 */

    /* デバイス管理コマンド（整数パラメータ）*/
    IMG_CMD_INT_SP = 0x4642,	/* ページ出力 */

    /* デバイス管理コマンド（実数パラメータ）*/
    IMG_CMD_REAL_PR = 0x4661,	/* ダウンロードデータの解像度指定 */

} IMG_CommandCode;

typedef signed char IMG_SINT8;

/*
 * IMG_Commandクラスの定義
 */
typedef struct img_command {
	IMG_UINT32			size;			/* コマンドが占有するバイト数 */
	IMG_Context			*context;		/* 実行環境コンテキスト */
	IMG_UINT16			code;			/* コマンドコード */
	IMG_UINT8			kind;			/* コマンド種別 */
	IMG_SINT8			refCounter;		/* リファレンスカウンタ */
	/* メモリ削減のためenumの使用をやめる */
	/*
    IMG_CommandCode		code;
	IMG_CommandKind		kind;
	int					refCounter;
	*/

	/* Public操作 */

	/*
	 * 2つのコマンドが同一かどうかを調べる。
	 */
	int (*isEqualTo)(
		IMG_CommandPtr	self,			/* this pointer */
		IMG_CommandPtr	target,			/* target object */
		IMG_BOOL		*result);		/* 同一かどうか? */

	/*
	 * pageに対してコマンドを実行する。
	 */
	int (*execute)(
		IMG_CommandPtr		self,		/* this pointer */
		IMG_CommandFilterPtr filter,	/* filter object */
		IMG_BOOL			release);	/* 実行後リソースを解放すべきか? */

	/* Private操作 */

	/* 
	 * オブジェクトを削除する。
	 * クライアントは本操作を呼んではならない。
	 * 代わりにIMG_Command_Releaseを使うこと。
	 */
	int (*destroy)(
		struct img_command	*self);		/* this pointer */

} IMG_Command;

/*
 * IMG_Commandクラスのサービス関数
 */
extern IMG_BOOL IMG_Command_IsValid(
	IMG_CommandPtr	self);

extern int IMG_Command_Release(
	IMG_CommandPtr	self);

extern int IMG_Command_Refer(
	IMG_CommandPtr	*lhs,		/* left hand side */
	IMG_CommandPtr	rhs);		/* right hand side */

extern int IMG_Command_MakeReference(
	IMG_CommandPtr	*lhs,		/* left hand side */
	IMG_CommandPtr	rhs);		/* right hand side */

/*
 * 以下はインライン関数
 */

/*
 * コマンド種別を設定する。
 */
static void IMG_Command_SetKind(
	IMG_CommandPtr	self,
	IMG_CommandKind	kind)
{
	self->kind = kind;
}

/*
 * コマンド種別を取得する
 */
static IMG_CommandKind IMG_Command_GetKind(
	IMG_CommandPtr	self)
{
	return (IMG_CommandKind)self->kind;
}

/*
 * コマンドコードを取得する。
 */
static IMG_CommandCode IMG_Command_GetCode(
	IMG_CommandPtr	self)
{
	return (IMG_CommandCode)self->code;
}

/*
 * コマンドサイズ(バイト数)を取得する。
 */
static IMG_UINT32 IMG_Command_GetSize(
	IMG_CommandPtr	self)
{
	return self->size;
}

/*
 * コマンドがブラシ設定コマンドかどうか調べる。
 */
static IMG_BOOL IMG_Command_IsBrush(
	IMG_CommandPtr	self)
{
	return self->kind == IMG_COMMAND_ATTRIBUTE_BRUSH;
}

/*
 * コマンドが属性設定コマンドかどうか調べる。
 */
static IMG_BOOL IMG_Command_IsAttribute(
	IMG_CommandPtr	self)
{
	return (self->kind & IMG_COMMAND_ATTRIBUTE) != 0;
}

/*
 * コマンドが図形描画コマンドかどうか調べる。
 */
static IMG_BOOL IMG_Command_IsGraphicsDrawing(
	IMG_CommandPtr	self)
{
	return self->kind == IMG_COMMAND_DRAWING_GRAPHICS;
}

/*
 * コマンドがイメージ描画コマンドかどうか調べる。
 */
static IMG_BOOL IMG_Command_IsImageDrawing(
	IMG_CommandPtr	self)
{
	return self->kind == IMG_COMMAND_DRAWING_IMAGE;
}

/*
 * コマンドが描画コマンドかどうか調べる。
 */
static IMG_BOOL IMG_Command_IsDrawing(
	IMG_CommandPtr	self)
{
	return IMG_Command_IsGraphicsDrawing(self) ||
		   IMG_Command_IsImageDrawing(self);
}

/*
 * コマンドがクリップ設定コマンドかどうか調べる。
 */
static IMG_BOOL IMG_Command_IsClip(
	IMG_CommandPtr	self)
{
	return self->kind == IMG_COMMAND_CLIP;
}

/*
 * コマンドがパス構築コマンドかどうか調べる。
 */
static IMG_BOOL IMG_Command_IsPath(
	IMG_CommandPtr	self)
{
	return self->kind == IMG_COMMAND_PATH;
}

/*
 * コマンドが実際に図形を描画するコマンドであるかどうか調べる。
 * 実際に描画するとは、そのコマンドが実行されるタイミングで
 * ページに画像が描画されるという意味である。
 * 例1) パス構築コマンドは、それ自体では描画はしないため、結果はFALSE。
 * 例2) パス描画コマンドは、構築されたパスを描画するという意味で、結果はTRUE。
 */
static IMG_BOOL IMG_Command_IsRealDrawing(
	IMG_CommandPtr	self)
{
	return self->code == IMG_CMD_INT_SR  ||	/* パスの描画 */
		   self->code == IMG_CMD_INT_QS  ||	/* スキャンラインの描画 */
		   self->code == IMG_CMD_INT_SL  ||	/* 線分の描画 */
		   self->code == IMG_CMD_INT_DR  ||	/* 長方形の描画 */
		   self->code == IMG_CMD_INT_RS  ||	/* 長方形セットの描画 */
		   self->code == IMG_CMD_REAL_DM ||	/* イメージマスクの描画 */
		   self->code == IMG_CMD_REAL_DI ||	/* イメージの描画(単一指定) */
		   self->code == IMG_CMD_REAL_DC ||	/* 円弧描画 */
		   self->code == IMG_CMD_REAL_DE ||	/* 楕円弧描画 */
		   self->code == IMG_CMD_REAL_DB ||	/* Bezier描画 */
		   self->code == IMG_CMD_REAL_RR;	/* 角丸矩形描画 */
}

/*
 * Protected操作
 */
extern int IMG_Command_Construct(
	IMG_CommandPtr	self,		/* this pointer */
	IMG_Context		*context,
	IMG_UINT32		size,
    IMG_CommandCode	code,
	IMG_CommandKind	kind);

extern int IMG_Command_Destruct(
	IMG_CommandPtr	self);		/* this pointer */

extern int IMG_Command_Reconstruct(
	IMG_CommandPtr	self);		/* this pointer */

extern int IMG_Command_IsEqualTo(
	IMG_CommandPtr	self,		/* this pointer */
	IMG_CommandPtr	target,
	IMG_BOOL		*isEqual);

extern int IMG_Command_CloneData(
	IMG_CommandPtr	self,		/* this pointer */
	void			**dest,
	void			*src,
	IMG_UINT32		size);

extern int IMG_Command_GetData(
	IMG_CommandPtr	self,		/* this pointer */
	void			**src,		/* source address */
	void			**dest,
	IMG_UINT32		size,
	IMG_BOOL		release);

extern int IMG_Command_UngetData(
	IMG_CommandPtr	self,		/* this pointer */
	void			**src,
	void			*dest,
	IMG_BOOL		release);

/*
 * マクロ定義
 *
 * キャストが煩雑なので導入。
 */
#define IMG_COMMAND_SET_INSTANCE(concrete, super, type)	type *concrete = (type *)super

#define IMG_COMMAND_GET_DATA(self, src, dest, size, release) \
	IMG_Command_GetData(self, (void**)(src), (void**)(dest), size, release)

#define IMG_COMMAND_UNGET_DATA(self, src, dest, release) \
	IMG_Command_UngetData(self, (void **)src, (void *)dest, release)

#define IMG_COMMAND_CLONE_DATA(self, copy, src, size) \
	IMG_Command_CloneData(self, (void **)copy, (void *)src, size)


#endif /* INC_IMG_Command_h */

/*
 * Old Log(IMG_CommandUnit.h)
 * 14.May.2001 Yozo Kashima  Created
 * 21.May.2001 Yozo Kashima IMG_CommandUnit_Destroyを追加。
 * 24.Jul.2001 Yozo Kashima IMG_CommandKindを追加。
 * 27.Jul.2001 Yozo Kashima	IMG_CommandUnit_SetRectangleを追加。
 */

/*
 * Log
 * 21.Aug.2001 Yozo Kashima IMG_Command_DrawScanlineを追加。
 *							clone操作を削除。
 * 22.Aug.2001 Yozo Kashima IMG_Command_DrawImageを追加。
 * 14.Sep.2001 Yozo Kashima 障害#97(fh8007g0-07)の対応。
 *							パス関連のクラスを追加。
 * 27.Sep.2001 Yozo Kashima 障害#88(pb0008g0-09)の対応。
 *							IMG_COMMAND_PATHを命令種別に追加。
 *							IMG_Command_ClipPathクラスを追加。
 * 02.Oct.2001 Yozo Kashima IMG_Command_LineToを削除、IMG_Command_AddRectanglePathを追加。
 * 08.Oct.2001 Yozo Kashima Win2000(Xor-Mask-Xorの置換)対応
 *							IMG_Command_SetMaskPatternを追加。
 * 15.Oct.2001 Yozo Kashima Win2000(Nopの置換)対応
 *							ストローク関連の属性設定命令クラスを追加。
 * 26.Oct.2001 Yozo Kashima 障害#143対応(ROP2-11が置換されない。w2k:dw4008g0-08,pb0008g0-09,pb0009i0-11)
 *							IMG_Command_SetHatchPattern, IMG_Command_SetMatrixクラスを追加。
 * 30.Oct.2001 Yozo Kashima ROP3-136(DSa)がクリップとして使用されるケースに対応。
 *							(qx4001t0-01,qx4003t0-03,qx4004t1-04,qx4013l0-13)
 *							IMG_Command_DrawImageMaskクラスを追加。
 * 01.Nov.2001 Yozo Kashima 障害#163 (fl0004t0-04.prn), #167 (fl0009g0-10.prn) #169 (lt0008g1-09.prn)に対応。
 *							IMG_COMMAND_SET_KINDを追加。
 * 04.Mar.2002 Yozo Kashima サブクラスを別ファイルに移す。
 * 06.Sep.2002 Yozo Kashima IMG_Command_IsRealDrawingを追加(障害#11:vi0009i0.prn)。
 * 23.Dec.2003 Yozo Kashima AR#1439(Imagerでのタグ拡張のため実行対象をpageでなくfilterに変更)。
 */

/* end of IMG_Command.h */
