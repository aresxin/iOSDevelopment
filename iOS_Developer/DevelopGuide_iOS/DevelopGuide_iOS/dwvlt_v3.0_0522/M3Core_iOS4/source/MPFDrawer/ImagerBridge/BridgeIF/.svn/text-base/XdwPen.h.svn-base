/**
 * @file  XdwPen.h
 * @brief Pen属性関連クラス用ヘッダファイル
 *
 * Pen (旧Stroke or Line) 属性に関する型の宣言やグローバルな関数を提供する．<br>
 * Pen属性はsave/restore対象である．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-10
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-10	Toshio Yamazaki<br>
 */
#ifndef XDWPEN_H_INCLUDED
#define XDWPEN_H_INCLUDED

/*!Pen Attributeクラス

  Pen属性を提供する．
 */
class XdwPenAttribute {
public:
    /*! 線形状の指定
      線分形状，実線か破線か，また，破線だったらどんな破線かを指定する
    */
    enum PenStyle {
	XDW_PENSTYLE_SOLID = 0,	/*!< 実線		*/
	XDW_PENSTYLE_DASH,	/*!< 破線 -------	*/
	XDW_PENSTYLE_DOT,	/*!< 点線 .......	*/
	XDW_PENSTYLE_DASHDOT,	/*!< 一点鎖線 _._._._	*/
	XDW_PENSTYLE_DASHDOTDOT,/*!< 二点鎖線 _.._.._	*/
	XDW_PENSTYLE_NULL,	/*!< 不可視線		*/
	XDW_PENSTYLE_INSIDEFRAME,/*!< 境界内保証実線	*/
	XDW_PENSTYLE_USERSTYLE,	/*!< 任意形状破線	*/
	XDW_PENSTYLE_ALTERNATE	/*!< 1pixel毎点線	*/
    };
    /*! Capy Typeの指定
      線分の端点形状を指定する
    */
    enum CapType {
        /*! 円形状 */
        XDW_CAPTYPE_ROUND = 0x0000,
        /*! 矩形形状 */
        XDW_CAPTYPE_SQUARE = 0x0100,
        /*! 何もしない */
	XDW_CAPTYPE_BUTT = 0x0200,
        /*! デフォルト */
        XDW_CAPTYPE_DEFAULT = XDW_CAPTYPE_ROUND
    };
    /*! Join Typeの指定
      線分の接続点形状を指定する
    */
    enum JoinType {
        /*! 円接続 */
        XDW_JOINTYPE_ROUND = 0x0000,
        /*! べベル接続 */
        XDW_JOINTYPE_BEVEL = 0x1000,
        /*! マイター接続 */
        XDW_JOINTYPE_MITER = 0x2000,
        /*! デフォルト */
        XDW_JOINTYPE_DEFAULT = XDW_JOINTYPE_ROUND
    };
    XdwPenAttribute::PenStyle	PenStyleF;	/*!< 線形状		*/
    XdwPenAttribute::CapType	CapTypeF;	/*!< Cap形状		*/
    XdwPenAttribute::JoinType	JoinTypeF;	/*!< Join形状		*/
    double			WidthF;		/*!< 線幅		*/
    long		DashCountF;	/*!< 任意形状破線データ個数	*/
    double*		DashDataF;	/*!< 任意形状破線データ		*/

    // AR849対応.
    /*! このインスタンス生成のもとになった構造体の明示
      がLOGPENかEXTLOGPENかを示す
    */
    enum SourceStructure {
	/*! LOGPEN構造体 */
	XDW_SOURCE_STRUCTURE_LOGPEN,
	/*! EXTLOGPEN構造体 */
	XDW_SOURCE_STRUCTURE_EXTLOGPEN
    };
    XdwPenAttribute::SourceStructure SourceStructureF;	/*!< インスタンス生成のもとになった構造体の種類 */
};

#endif /* XDWPEN_H_INCLUDED */
