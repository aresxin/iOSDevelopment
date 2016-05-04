/**
 * @file  XdwGraphicFormatEMFEMRModifyWorldTransFormRecord.h
 * @brief XdwGraphicFormat::EMF::EMR::ModifyWorldTransFormRecordクラスの定義
 *
 * @author TDG Yasuhiro.Ito@fujixerox.co.jp
 * @date 2004-01-28
 * @version 1.0
 * $Id
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef _XDW_GRAPHICFORMAT_EMF_EMR_MODIFY_WORLD_TRANSFORM_RECORD_H_
#define _XDW_GRAPHICFORMAT_EMF_EMR_MODIFY_WORLD_TRANSFORM_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatEMFEMR.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatEMFEMRSetWorldTransFormRecord.h"


/**
 * @brief META_SETWORLDTRANSFORMレコードを規定するクラス
 *
 */
class XdwGraphicFormat::EMF::EMR::ModifyWorldTransFormRecord : public XdwGraphicFormat::EMF::EMR::SetWorldTransFormRecord
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    ModifyWorldTransFormRecord();

    /**
     * @brief デストラクタ
     */
    virtual ~ModifyWorldTransFormRecord();
    
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
	
	/*Mode*/
	long fMode;
};

#endif
