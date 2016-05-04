/*!
  @file  XdwBridgeFontTableForGlobe.h
  @brief Font管理テーブルヘッダファイル

  Fontの置換に用いるFont名のテーブル構造体の定義を記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-06-12
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-06-12	Toshio Yamazaki<br>
 */
#include "XdwError.h"
#include "XdwFont.h"

#include "XdwBridgeConfigForGlobe.h"

#ifndef XDWBRIDGEFONTTABLEFORGLOBE_H_INCLUDED
#define XDWBRIDGEFONTTABLEFORGLOBE_H_INCLUDED

/*! Font Table

  Globe Imagerを使うときの，Windowsフォント名と，
  IDのペアでFontテーブル管理するための構造体．<br>
  Windows側のフォント名とGlobe側フォントIDの対応をとるためのテーブル．<br>
  fontnameFはunsigned charの配列だけど，一応0x00でターミネイトされている
  必要があることにしておく．
*/
typedef struct {
    unsigned short IDF;					/*!< フォントID		*/
    unsigned char fontnameF[XDW_FONT_FACESIZE];		/*!< フォント名		*/
} XdwBridgeFontTableForWindows;

/*! Font Table

  Globe Imagerを使うときの，Globeのフォント名と，
  IDのペアでFontテーブル管理するための構造体．<br>
  Globe側フォント属性とIDとの対応をとるためのテーブル．<br>
  fontnameFはunsigned charの配列だけど，一応0x00でターミネイトされている<br>
  必要があることにしておく．
*/
typedef struct {
    unsigned short	IDF;				/*!< フォントID		*/
    unsigned short	PitchAndFamilyF;		/*!< PitchとFamily属性	*/
/*    int			italic;			イタリックフラグ	*/
/*    int			bold;			Boldフラグ		*/
    unsigned char	fontnameF[XDW_FONT_FACESIZE];	/*!< フォント名		*/
} XdwBridgeFontTableForGlobe;

/*! Font Table種別
 * Font Tableの種別を指定する
 */
enum XdwBridgeFontTableMode {
    XDW_BRIDGE_FTFG_TABLE_WIN,	/*!< Windows Font置換テーブル指定	*/
    XDW_BRIDGE_FTFG_TABLE_GLOBE	/*!< Globe Fontスコアリングテーブル指定	*/
};

/*! Font Table操作
  XdwBridgeFontTableGlobe, XdwBridgeFontTableGlobe
  を操作するためのクラス．
  主にIteratorとして動作し，メインの操作は
  二分探索による文字列検索とFont Mappingのための処理．
*/
class XdwBridgeFontTableMapper {
private:
    const XdwBridgeFontTableForGlobe	*globe_tableF;	/*!< スコアリング用Globe Font Table */
    const int				globe_tablesizeF;/*!< スコアリング用Globe Font Table のサイズ*/
    const XdwBridgeFontTableForWindows	*win_tableF;	/*!< 置換用Windows Font Table */
    const int				win_tablesizeF;	/*!< 置換用Windows Font Table サイズ*/

    int ScoreCharSet( const XdwFontInfo &, int *, int );
    int ScoreFontNameAndFamily( const XdwFontInfo &, int *, int );
    int ScoreItalicAndBold( const XdwFontInfo &, int *, int );
    int CompareUnicodeString( const unsigned char *, const unsigned char * );

public:
    XdwBridgeFontTableMapper();				/*!< コンストラクタ		*/
    XdwBridgeFontTableMapper( const XdwBridgeFontTableForGlobe *, int,
			      const XdwBridgeFontTableForWindows *, int );	/*!< コンストラクタ	*/
    ~XdwBridgeFontTableMapper();				/*!< デストラクタ		*/

    XdwErrorCode MappingFont( const XdwFontInfo &, unsigned short * );
    unsigned short SearchFontName( XdwBridgeFontTableMode,
				   const unsigned char * );

    int GetTableSize(XdwBridgeFontTableMode);	/*!< Talbeサイズの取得		*/
    unsigned short GetFontID(XdwBridgeFontTableMode,
			     int);				/*!< Font IDの取得		*/
};

/*! @name IMARI Font用定義
 * IMARI Fontを使用するときに有効になる定数．
 * どこかで XDWBRIDGEGLOBE_USEFONT_IMARI が有効になっている時，
 * Font ROMがIMARIのものとして各定数を設定する
 */
/*@{*/
#ifdef XDWBRIDGEGLOBE_USEFONT_IMARI
/*! Windows Font Table 個数
 * Windows Font Nameの置換時に使うフォントテーブルの個数．
 * 実際に使うときは配列だから0基数であることに注意
 */
#define XDWBRIDGEFONTTABLEWINDOWS_SIZE	29
extern const XdwBridgeFontTableForWindows XDWBRIDGEFONTTABLEWINDOWS01[];	/* 前宣言 */
/*! Globe Font Table 個数
 * Globe Font のスコアリング時に使うフォントテーブルの個数．
 * 実際に使うときは配列だから0基数であることに注意
 */
#define XDWBRIDGEFONTTABLEGLOBE_SIZE	17
extern const XdwBridgeFontTableForGlobe XDWBRIDGEFONTTABLEGLOBE01[];		/* 前宣言 */
#endif	/* XDWBRIDGEGLOBE_USEFONT_IMARI */
/*@}*/

/*! @name LIMOGES Font用定義
 * LIMOGES Fontを使用するときに有効になる定数．
 * どこかで XDWBRIDGEGLOBE_USEFONT_LIMOGES が有効になっている時，
 * Font ROMがLIMOGESのものとして各定数を設定する
 */
/*@{*/
#ifdef XDWBRIDGEGLOBE_USEFONT_LIMOGES
/*! Windows Font Table 個数
 * Windows Font Nameの置換時に使うフォントテーブルの個数．
 * 実際に使うときは配列だから0基数であることに注意
 */
#define XDWBRIDGEFONTTABLEWINDOWS_SIZE	38
extern const XdwBridgeFontTableForWindows XDWBRIDGEFONTTABLEWINDOWS01[];	/* 前宣言 */
/*! Globe Font Table 個数
 * Globe Font のスコアリング時に使うフォントテーブルの個数．
 * 実際に使うときは配列だから0基数であることに注意
 */
#define XDWBRIDGEFONTTABLEGLOBE_SIZE	17
extern const XdwBridgeFontTableForGlobe XDWBRIDGEFONTTABLEGLOBE01[];		/* 前宣言 */
#endif	/* XDWBRIDGEGLOBE_USEFONT_LIMOGES */
/*@}*/

#endif /* XDWBRIDGEFONTTABLEFORGLOBE_H_INCLUDED */
