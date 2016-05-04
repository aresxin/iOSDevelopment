/**
 * @file  XdwBridgeObjectManager.h
 * @brief GDI Object管理クラス用ヘッダファイル
 *
 * GDIのObject管理クラスの宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-07-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-07-04	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEOBJECTMANAGER_H_INCLUDED
#define XDWBRIDGEOBJECTMANAGER_H_INCLUDED

#include "XdwError.h"

/*前宣言*/
class XdwBridgeObject;
class XdwPatternAttribute;
class XdwFontInfo;
class XdwColorPalette;
class XdwPenAttribute;

class XdwBridgeObjectBrush;
class XdwBridgeObjectFont;
class XdwBridgeObjectPalette;
class XdwBridgeObjectPen;

#include "XdwStl.h"
#include <vector>
class XdwBridgeCurrentObject {
public:
    XdwBridgeObject	*FontObjF;	/*!< Currentチェック用	*/
    XdwBridgeObject	*BrushObjF;	/*!< Currentチェック用	*/
    XdwBridgeObject	*PaletteObjF;	/*!< Currentチェック用	*/
    XdwBridgeObject	*PenObjF;	/*!< Currentチェック用	*/

    XdwBridgeCurrentObject();
    ~XdwBridgeCurrentObject();
};
typedef XdwStlVector(XdwBridgeCurrentObject)	XdwBridgeCurrentObjectVector;	/*!< Save/Resore用Vector */

/*! 生成されるObjectの最大数 */
#define XDWBIRDIGEOBJECT_MAXNUMBER	(2147483646L)	/*((2^31)-1)*/

/*!Object Managerクラス

  XdwBridgeObjectクラスを継承した各具象クラスを管理する．
 */
class XdwBridgeObjectManager {
    /* Save, Restoreだけ，XdwBridgeGraphicStateManager
       からアクセスさせたいからfriend*/
    friend class XdwBridgeGraphicStateManager;
private:
    XdwBridgeObject	*topF;		/*!< Object Listの基点		*/
    XdwBridgeObject	*currentF;	/*!< Object List操作用ポインタ	*/
    unsigned long	baseIDF;	/*!< ID生成用パラメータ		*/
    unsigned long	stackcounterF;	/*!< Stack UnderFlow確認用	*/

    XdwBridgeCurrentObjectVector	*current_object_listF;	/*!< Current Object	*/
    XdwBridgeCurrentObjectVector::iterator	current_objF;	/*!< Current Object	*/

    XdwErrorCode	GenerateSystemObject(void);

    XdwErrorCode	Save(void);
    XdwErrorCode	Restore(void);
public:
    XdwBridgeObjectManager();
    ~XdwBridgeObjectManager();

    XdwErrorCode	Initialize(void);
    XdwBridgeObject *	SelectObject( unsigned long ID );
    XdwErrorCode	DeleteObject( unsigned long ID );
    XdwErrorCode	DeleteAllObject( void );

    XdwBridgeObjectBrush *	CreateBrushObject( const XdwPatternAttribute &, unsigned long * );
    XdwBridgeObjectFont *	CreateFontObject( const XdwFontInfo &, unsigned long * );
    XdwBridgeObjectPalette *	CreatePaletteObject( const XdwColorPalette &, unsigned long * );
    XdwBridgeObjectPen *	CreatePenObject( const XdwPenAttribute &, const XdwPatternAttribute &, unsigned long * );

    XdwBridgeObjectBrush *	GetCurrentBrushObject(void);
    XdwBridgeObjectFont *	GetCurrentFontObject(void);
    XdwBridgeObjectPalette *	GetCurrentPaletteObject(void);
    XdwBridgeObjectPen *	GetCurrentPenObject(void);
};

/*! System Objectの番号
  以下の番号を持つオブジェクトは，
  XdwBridgeObjectManager生成時に生成され，
  Deleteされることはない.<br>
  SystemObjectは最上位Bitが立っていることに注意
*/
enum XdwBridgeObject_SystemObjNo {
    XDWBRIDGEOBJECT_SYSTEMOBJNO_WHITE_BRUSH		= 0x80000000,	/*!< Solid白色Brush	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_LTGRAY_BRUSH		= 0x80000001,	/*!< Solid薄灰色Brush	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_GRAY_BRUSH		= 0x80000002,	/*!< Solid灰色Brush	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_DKGRAY_BRUSH		= 0x80000003,	/*!< Solid濃灰色Brush	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_BLACK_BRUSH		= 0x80000004,	/*!< Solid黒色Brush	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_NULL_BRUSH		= 0x80000005,	/*!< Null Brush		*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_HOLLOW_BRUSH		= 0x80000005,	/*!< Null Brush		*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_WHITE_PEN		= 0x80000006,	/*!< Solid白色Pen	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_BLACK_PEN		= 0x80000007,	/*!< Solid黒色Pen	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_NULL_PEN		= 0x80000008,	/*!< Null Pen		*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_OEM_FIXED_FONT		= 0x8000000a,	/*!< 固定幅OEM Font	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_ANSI_FIXED_FONT		= 0x8000000b,	/*!< 固定幅Ansi Font	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_ANSI_VAR_FONT		= 0x8000000c,	/*!< 可変幅Ansi Font	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_SYSTEM_FONT		= 0x8000000d,	/*!< System Font	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_DEVICE_DEFAULT_FONT	= 0x8000000e,	/*!< Default Font	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_DEFAULT_PALETTE		= 0x8000000f,	/*!< Default Palette	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_SYSTEM_FIXED_FONT	= 0x80000010,	/*!< System 固定幅Font	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_DEFAULT_GUI_FONT	= 0x80000011,	/*!< Default GUI Font	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_DC_BRUSH		= 0x80000012,	/*!< DC Brushって何？	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_DC_PEN			= 0x80000013,	/*!< DC Penって何？	*/
    XDWBRIDGEOBJECT_SYSTEMOBJNO_STOCK_LAST		= 0x80000013	/*!< 全部の個数		*/
};

#endif /* XDWBRIDGEOBJECTMANAGER_H_INCLUDED */
