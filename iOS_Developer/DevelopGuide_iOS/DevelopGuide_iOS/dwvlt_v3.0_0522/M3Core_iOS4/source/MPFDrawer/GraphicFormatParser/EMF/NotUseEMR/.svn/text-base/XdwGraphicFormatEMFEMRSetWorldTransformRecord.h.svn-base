/**
 * @file  XdwGraphicFormatEMFEMRSetWorldTransFormRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::SetWorldTransFormRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_SET_WORLD_TRANSFORM_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_SET_WORLD_TRANSFORM_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"
#include "XdwDocuWorksBinaryInterface.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwDataObjectBinary.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRRecord.h"
/* 集約*/
#include "XdwGraphicFormatGDIXForm.h"
/**
 * @brief META_SETWORLDTRANSFORMレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::SetWorldTransFormRecord : public XdwGraphicFormat::EMF::EMR::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    SetWorldTransFormRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~SetWorldTransFormRecord();
    
    /**
     * @brief META_SETWORLDTRANSFORMレコードをパースする
     *
     * WorldTrans座標系をセット
	 *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:


    /**
     * @brief レコードの属性を読み込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Read();
	
	/*集約*/
	XdwGraphicFormat::GDI::XForm fXform;
};

#endif
