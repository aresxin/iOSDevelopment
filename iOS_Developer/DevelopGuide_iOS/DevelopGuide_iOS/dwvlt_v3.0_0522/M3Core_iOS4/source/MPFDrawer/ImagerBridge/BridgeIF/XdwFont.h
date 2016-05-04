/**
 * @file  XdwFont.h
 * @brief Font処理関連クラス用ヘッダファイル
 *
 * Font処理に関する型の宣言やグローバルな関数，ライブラリへのI/Fを提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-03
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-03	Toshio Yamazaki<br>
 */
#ifndef XDWFONT_H_INCLUDED
#define XDWFONT_H_INCLUDED

#include "XdwShape.h"

/*! Font Name指定の最大サイズ	*/
#define XDW_FONT_FACESIZE	64

/*! Fontのデフォルトサイズ		*/
/* とりあえず10pt. 確か，		*/
/* (PT x DPI)/72.0で求められたはず…	*/
#define XDW_FONT_DEFAULT_SIZE	((10.0*300.0)/72.0)

/*! String Modeを指定するID

  文字列のEncodeがUNICODEかMulti ByteCharactor String (MBCS) か
  を指定する．UNICODEはEMREXTTEXTOUTWで，MBCSはEMREXTTEXTOUTAで
  使用される．<br>
  Bridgeで使用されるStringのEncodeは，UNICODEが指定された場合，
  UNICODEで，MBCSが指定された場合，EncodeIDで指定されたEncodingで
  Encodeされる
 */
enum XdwFontStringModeID {
    XDW_BRIDGE_SMID_UNICODE,	/*!< UNICODE でEncodeされる			*/
    XDW_BRIDGE_SMID_MBCS	/*!< XdwFontEncodeIDの指定でEncodeされる	*/
};

/*! Encodeを指定するID

  文字列のEncodeを指定する場合のID．
*/
enum XdwFontEncodeID {
    /* Windowsそのまま */
    XDW_BRIDGEEID_ANSI		= 0,	/*!< ANSI Code	*/
    XDW_BRIDGEEID_DEFAULT	= 1,	/*!< Default	*/
    XDW_BRIDGEEID_SYMBOL	= 2,	/*!< Symbol Code	*/
    XDW_BRIDGEEID_SHIFTJIS	= 128,	/*!< Shift-JIS Code	*/
    XDW_BRIDGEEID_HANGEUL	= 129,	/*!< <-参照	*/
    XDW_BRIDGEEID_HANGUL	= 129,	/*!< <-参照	*/
    XDW_BRIDGEEID_GB2312	= 134,	/*!< <-参照	*/
    XDW_BRIDGEEID_CHINESEBIG5	= 136,	/*!< <-参照	*/
    XDW_BRIDGEEID_OEM		= 255,	/*!< <-参照	*/
    XDW_BRIDGEEID_JOHAB		= 130,	/*!< <-参照	*/
    XDW_BRIDGEEID_HEBREW	= 177,	/*!< <-参照	*/
    XDW_BRIDGEEID_ARABIC	= 178,	/*!< <-参照	*/
    XDW_BRIDGEEID_GREEK		= 161,	/*!< <-参照	*/
    XDW_BRIDGEEID_TURKISH	= 162,	/*!< <-参照	*/
    XDW_BRIDGEEID_VIETNAMESE	= 163,	/*!< <-参照	*/
    XDW_BRIDGEEID_THAI		= 222,	/*!< <-参照	*/
    XDW_BRIDGEEID_EASTEUROPE	= 238,	/*!< <-参照	*/
    XDW_BRIDGEEID_RUSSIAN	= 204,	/*!< <-参照	*/
    XDW_BRIDGEEID_MAC		= 77,	/*!< <-参照	*/
    XDW_BRIDGEEID_BALTIC	= 186,	/*!< <-参照	*/
    /* 追加 */
    XDW_BRIDGEEID_UNICODE	/*!< 16bit UNICode	*/
};

/*! Font情報

  Fontの情報を指定する．
  以下の文字描画は，これで指定されたFontで描画される．<br>
  LOGFONTAと同じメンバは同じ意味を持つ．
*/
class XdwFontInfo {
public:
    /*! Font Weight 値

      XdwsBridge::FontInfo等で指定されるFont Weight値．
      Font Weight値は0〜1000の値で指定されるが，
      幾つかの値は，例えば400はノーマル，700はボールドの等のように，
      特定の意味を持つ．<br>
      Windowsそのままなのは気のせい．
    */
    enum FontWeight {
	XDW_BRIDGEFW_DONTCARE	= 0,	/*!< 気にしない	*/
	XDW_BRIDGEFW_THIN	= 100,	/*!< <-参照	*/
	XDW_BRIDGEFW_EXTRALIGHT	= 200,	/*!< <-参照	*/
	XDW_BRIDGEFW_LIGHT	= 300,	/*!< <-参照	*/
	XDW_BRIDGEFW_NORMAL	= 400,	/*!< ノーマル	*/
	XDW_BRIDGEFW_MEDIUM	= 500,	/*!< <-参照	*/
	XDW_BRIDGEFW_SEMIBOLD	= 600,	/*!< <-参照	*/
	XDW_BRIDGEFW_BOLD	= 700,	/*!< ボールド	*/
	XDW_BRIDGEFW_EXTRABOLD	= 800,	/*!< <-参照	*/
	XDW_BRIDGEFW_HEAVY	= 900	/*!< <-参照	*/
    };

    /*! Out Precision値

      文字出力精度の指定
    */
    enum OutPrecison {
	XDW_BRIDGE_FONT_OUT_DEFAULT_PRECIS		= 0,	/*!< デフォルト	*/
	XDW_BRIDGE_FONT_OUT_STRING_PRECIS		= 1,	/*!< 文字列	*/
	XDW_BRIDGE_FONT_OUT_CHARACTER_PRECIS		= 2,	/*!< 文字	*/
	XDW_BRIDGE_FONT_OUT_STROKE_PRECIS		= 3,	/*!< ストローク	*/
	XDW_BRIDGE_FONT_OUT_TT_PRECIS			= 4,	/*!< TrueType	*/
	XDW_BRIDGE_FONT_OUT_DEVICE_PRECIS		= 5,	/*!< デバイス	*/
	XDW_BRIDGE_FONT_OUT_RASTER_PRECIS		= 6,	/*!< ラスタ	*/
	XDW_BRIDGE_FONT_OUT_TT_ONLY_PRECIS		= 7,	/*!< TrueTypeのみ	*/
	XDW_BRIDGE_FONT_OUT_OUTLINE_PRECIS		= 8,	/*!< Out Line	*/
	XDW_BRIDGE_FONT_OUT_SCREEN_OUTLINE_PRECIS	= 9	/*!< Screen Out Line	*/
    };

    /*! Clip Precision値

      文字クリッピング精度の指定
    */
    enum ClipPrecision {
	/* 下位4bit	*/
	XDW_BRIDGE_FONT_CLIP_DEFAULT_PRECIS	= 0,		/*!< デフォルト	*/
	XDW_BRIDGE_FONT_CLIP_CHARACTER_PRECIS	= 1,		/*!< 文字	*/
	XDW_BRIDGE_FONT_CLIP_STROKE_PRECIS	= 2,		/*!< ストローク	*/
	XDW_BRIDGE_FONT_CLIP_MASK		= 0xf,		/*!< Mask用	*/
	/* 上位4bit	*/
	XDW_BRIDGE_FONT_CLIP_LH_ANGLES		= (1<<4),	/*!< LH ANGLES	*/
	XDW_BRIDGE_FONT_CLIP_TT_ALWAYS		= (2<<4),	/*!< TT ALWAYS	*/
	XDW_BRIDGE_FONT_CLIP_EMBEDDED		= (8<<4)	/*!< EMBEDDED	*/
    };

    /*! 品質指定値

      文字出力品質の指定…多分
    */
    enum Quality {
	XDW_BRIDGE_FONT_DEFAULT_QUALITY		= 0,		/*!< デフォルト	*/
	XDW_BRIDGE_FONT_DRAFT_QUALITY		= 1,		/*!< ドラフト	*/
	XDW_BRIDGE_FONT_PROOF_QUALITY		= 2,		/*!< プルーフ	*/
	XDW_BRIDGE_FONT_NONANTIALIASED_QUALITY	= 3,		/*!< ？		*/
	XDW_BRIDGE_FONT_ANTIALIASED_QUALITY	= 4		/*!< ？		*/
    };

    /*! ピッチ&ファミリー指定値

      文字のピッチとファミリーの指定
    */
    enum PitchAndFamily {
	/* 下位 4bit, Pitch 指定 */
	XDW_BRIDGE_FONT_PITCHANDFAMILY_DEFAULT_PITCH	= 0,	/*!< デフォルト	*/
	XDW_BRIDGE_FONT_PITCHANDFAMILY_FIXED_PITCH	= 1,	/*!< 固定	*/
	XDW_BRIDGE_FONT_PITCHANDFAMILY_VARIABLE_PITCH	= 2,	/*!< 可変	*/
	XDW_BRIDGE_FONT_PITCHANDFAMILY_MONO_FONT	= 8,	/*!< MONO	*/
	/* 上位 4bit, Font Families 指定 */
	XDW_BRIDGE_FONT_PITCHANDFAMILY_FF_DONTCARE	= (0<<4),	/*!< Don't care or don't know. */
	XDW_BRIDGE_FONT_PITCHANDFAMILY_FF_ROMAN		= (1<<4),	/*!< Variable stroke width, serifed. */
									/* Times Roman, Century Schoolbook, etc. */
	XDW_BRIDGE_FONT_PITCHANDFAMILY_FF_SWISS		= (2<<4),	/*!< Variable stroke width, sans-serifed. */
									/* Helvetica, Swiss, etc. */
	XDW_BRIDGE_FONT_PITCHANDFAMILY_FF_MODERN	= (3<<4),	/*!< Constant stroke width, serifed or sans-serifed. */
									/* Pica, Elite, Courier, etc. */
	XDW_BRIDGE_FONT_PITCHANDFAMILY_FF_SCRIPT	= (4<<4),	/*!< Cursive, etc. */
	XDW_BRIDGE_FONT_PITCHANDFAMILY_FF_DECORATIVE	= (5<<4)	/*!< Old English, etc. */
    };

    long		HeightF;	/*!< Fontの高さ			*/
    long		WidthF;		/*!< Fontの平均幅		*/
    long		EscapementF;	/*!< Fontの角度 (NT以降)	*/
    long		OrientationF;	/*!< Fontの角度			*/
    long		FontWeightF;	/*!< Font Weight		*/
    bool		IsProportionalF;/*!< Proportional Font指定	*/
    bool		IsItalicF;	/*!< Italic Font指定		*/
    bool		IsUnderLineF;	/*!< 下線指定			*/
    bool		IsStrikeOutF;	/*!< ストライクアウト指定	*/

    char		OutPrecisionF;	/*!< 出力精度指定		*/
    char		ClipPrecisionF;	/*!< クリップ精度指定		*/
    char		QualityF;	/*!< 出力品質指定		*/
    char		PitchAndFamilyF;/*!< Pitch and Famly指定	*/

    XdwFontEncodeID	TextCharSetF;			/*!< キャラクターセット指定	*/
    XdwFontStringModeID	FaceNameStringModeF;		/*!< MBCS or UNICODE		*/
    unsigned char	FaceNameF[XDW_FONT_FACESIZE];	/*!< Font TypeFace指定		*/

    /* 以下，Imager (Decomposer) 依存なデータ	*/
    /* ここにあった方が都合がいい．小さいしね．	*/
    unsigned short	devfontIDF;			/*!< Globe Font ID	*/

/* staticでconstのXdwFontInfoあるから
   コンストラクタとかは作っちゃ駄目
    XdwFontInfo();
    ~XdwFontInfo();
*/
    bool IsKanji(void) const;
    bool IsTategaki(void) const;
    bool IsProportional(void) const;
};

/*! Text情報

  Text情報用のclassの共通処理をまとめる親クラス．
  各Text関連のクラスは，これをpublic継承する．<br>
  ついでに，Text描画時の属性を指定する．何故なら，
  描画位置とAlignの指定でピッチが変更されるから．
  @attention Text描画属性も追加された，要検討．
*/
class XdwText {
public:
    /***************************************************/
    /*! @name Pitch属性
     * FontのPitch属性を指定する．
     */
    /***************************************************/
    /*@{*/
    /*! Text描画時のピッチデータの指定方法

      指定されたピッチがどういう情報か指定する．<br>
      GlobeのFont機能仕様書を参照．
     */
    enum PitchMode {
	XDW_BRIDGEPIM_NOT_USED,		/*!< Pitch情報を使わない			*/
	XDW_BRIDGEPIM_DEFAULT,		/*!< システムのデフォルト			*/
	XDW_BRIDGEPIM_ALL_FIXED,	/*!< 全ての固定値				*/
	XDW_BRIDGEPIM_ALL_ADDITON,	/*!< フォント幅への加算値			*/
	XDW_BRIDGEPIM_EACH_DIFFERENCE,	/*!< 描画開始位置からの差分値			*/
	XDW_BRIDGEPIM_EACH_SPECIFY,	/*!< 各々の文字に対しての指定値			*/
	XDW_BRIDGEPIM_EACH_ADDITON	/*!< 各々の文字のフォント幅に対する加算値	*/
    };
    XdwText::PitchMode	PitchModeF;	/*!< Pitchモードの指定			*/
    unsigned long	PitchLengthF;	/*!< Pitchデータの長さ			*/
    double *		PitchDataF;	/*!< Pitchデータ配列へのポインタ	*/
    /*@}*/

    /***************************************************/
    /*! @name 描画属性
     * Fontに付随する，Font以外の描画属性を指定する．
     */
    /***************************************************/
    /*@{*/
    bool		IsClippingF;	/*!< クリッピング指定		*/
    XdwRectangle	ClipAreaF;	/*!< クリッピング領域		*/
    bool		IsBackFillF;	/*!< 背景塗りつぶし		*/
    XdwRectangle	BackFillAreaF;	/*!< 背景領域			*/
    /*@}*/
};

/*! Text Align情報

  TextをどのようにAlign (整列)させるか指定する．MSDNのSetTextAlignを参照．<br>
  <center>
  <br>JOBで初期化されるパラメータの値<br><br>
  <table>
  <tr><td><center>ビット位置</center></td><td><center>指定属性</center></td></tr>
  <tr><td>0</td><td>カレント描画位置の更新/非更新</td></tr>
  <tr><td>1〜2</td><td>水平位置Aling指定</td></tr>
  <tr><td>3〜4</td><td>垂直位置Aling指定</td></tr>
  <tr><td>8</td><td>アラビア文字の時の指定(サポート予定無し)</td></tr>
  </table>
  </center>
  <br>
  @attention 縦書きの場合は，BaseLineが垂直方向になるので，値が変わる
*/
enum XdwTextAlign {
    XDW_BRIDGETAM_NOUPDATECP	= 0x000, /*!< カレント描画位置の非更新	*/
    XDW_BRIDGETAM_UPDATECP	= 0x001, /*!< カレント描画位置の更新	*/
    XDW_BRIDGETAM_LEFT		= 0x000, /*!< 左揃え			*/
    XDW_BRIDGETAM_RIGHT		= 0x002, /*!< 右揃え			*/
    XDW_BRIDGETAM_CENTER	= 0x006, /*!< 中心揃え			*/
    XDW_BRIDGETAM_TOP		= 0x000, /*!< 上端揃え			*/
    XDW_BRIDGETAM_BOTTOM	= 0x008, /*!< 下端揃え			*/
    XDW_BRIDGETAM_BASELINE	= 0x018, /*!< BaseLine揃え		*/
    XDW_BRIDGETAM_RTLREADING	= 0x100, /*!< アラビア文字用(未サポート)*/

    XDW_BRIDGETAM_V_TOP		= 0x000, /*!< 縦書き用上端揃え		*/
    XDW_BRIDGETAM_V_BOTTOM	= 0x002, /*!< 縦書き用下端揃え		*/
    XDW_BRIDGETAM_V_CENTER	= 0x006, /*!< 縦書き用中心揃え		*/
    XDW_BRIDGETAM_V_RIGHT	= 0x000, /*!< 縦書き用右揃え		*/
    XDW_BRIDGETAM_V_LEFT	= 0x008, /*!< 縦書き用左揃え		*/
    XDW_BRIDGETAM_V_BASELINE	= 0x018, /*!< 縦書きBaseLine揃え	*/

    XDW_BRIDGETAM_MASK		= 0x1FF  /*!< マスク用			*/
};

/*! Code Text情報

  Codeで表現されるTextの情報を指定する．
  主に文字描画時の文字列指定に使われる．
*/
class XdwCodeText : public XdwText {
public:
    XdwFontStringModeID	TextStringModeF;/*!< MBCS or UNICODE				*/
    unsigned long	TextLengthF;	/*!< Code記述されたTextデータの長さ(byte)	*/
    unsigned char *	TextDataF;	/*!< Code記述されたTextデータへのポインタ	*/
};

/*! Data Text情報

  Dataで表現されるTextの情報を指定する．
  主に文字描画時の文字列指定に使われる．<br>
  Dataとしては，Bitmap・Outlineを想定．
  もしたかしたら，TrueType Formatも含まれるかも．<br>
  今のところ未定．
*/
class XdwDataText : public XdwText {
public:
    unsigned long	TextLengthF;	/*!< Data記述されたTextデータ数(文字数)		*/
    unsigned char **	TextDataF;	/*!< Data記述されたTextデータへのポインタへのポインタ	*/
};

/*! @name Font用マクロ
 * Font 関連で使うマクロ……結構適当
 */
/*@{*/
/*! SJIS 1BYTE目を判定するマクロ*/
#define XDWBRIDGEFONT_IS_SJIS1BYTE(c) (((c) >= 0x80) && !(((c)>=0xa0) && ((c)<=0xdf)))
/*@}*/

#endif /* XDWFONT_H_INCLUDED */
