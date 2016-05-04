/**
 * @file  XdwBridgeObject.h
 * @brief Object関連クラス用ヘッダファイル
 *
 * GDIのObjectに対応するクラスの宣言やグローバルな関数を提供する．
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-07-04
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-07-04	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGEOBJECT_H_INCLUDED
#define XDWBRIDGEOBJECT_H_INCLUDED

#include "XdwError.h"

/*!Objectタイプ

  GDIのオブジェクトタイプを指定する．
 */
enum XdwBridgeObjectType {
    XDW_BRDIGEOBJECTTYPE_BASE,		/*!< 基底Object		*/
    XDW_BRDIGEOBJECTTYPE_FONT,		/*!< Font Object	*/
    XDW_BRDIGEOBJECTTYPE_PEN,		/*!< Pen Object		*/
    XDW_BRDIGEOBJECTTYPE_BRUSH,		/*!< Brush Object	*/
    XDW_BRDIGEOBJECTTYPE_PALETTE,	/*!< Palette Object	*/
    XDW_BRDIGEOBJECTTYPE_REGION		/*!< Region Object	*/
};

/*!Objectクラス

  List構造をもつGDIのオブジェクトをシミュレートする．
  実際は，XdwBridgeObjectクラスを継承した各具象クラスが
  XdwBridgeObjectManagerクラスにより操作される．<br>
  XdwBridgeObject::IDFはListに繋がっているオブジェクト中で一意でなければならないが，
  IDFの生成はXdwBridgeObjectManagerクラスにしておく．<br>
  また，IDFの値はList中で以下の条件が成立することを保証する<br>
  prevF->IDF < this->IDF < nextF->IDF
 */
class XdwBridgeObject {
    friend class XdwBridgeObjectManager;
private:
    XdwBridgeObject	*prevF;	/*!< 前方向のオブジェクト,IDは小さいか等しい	*/
    XdwBridgeObject	*nextF;	/*!< 後方向のオブジェクト,IDは小さいか等しい	*/
    unsigned long	refcountF;	/*!< Current Object参照カウンタ		*/
protected:
    unsigned long	IDF;	/*!< ID, List内オブジェクト間で一意		*/
    XdwBridgeObjectType	typeF;		/*!< Objectのタイプ			*/
    void		Purge(void);
public:
    XdwBridgeObject();
    XdwBridgeObject(unsigned long ID);
    virtual ~XdwBridgeObject();

    void		IncCurrentRef(void);
    void		DecCurrentRef(void);

    void		SetID( unsigned long ID );
    unsigned long	GetID(void);
    XdwBridgeObjectType	GetType(void);
    XdwErrorCode	Insert( XdwBridgeObject *obj );
    XdwBridgeObject *	Delete( unsigned long ID );
    XdwBridgeObject *	Search( unsigned long ID );
};

#endif /* XDWBRIDGEOBJECT_H_INCLUDED */
