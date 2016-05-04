/**
 * @file  XdwGraphicFormatRasterThumbnail.h
 * @brief XdwGraphicFormat::Raster::Thumbnailクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-28
 * @version 1.0
 * $Id: XdwGraphicFormatRasterThumbnail.h,v 1.4 2009/12/22 08:11:41 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHIC_FORMAT_RASTER_THUMBNAIL_H_
#define _XDW_GRAPHIC_FORMAT_RASTER_THUMBNAIL_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatRaster.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatRasterDIB.h"

/**
 * @brief DocuWorksファイルのサムネイル用DIBデータを読み込むクラス
 *
 */
class XdwGraphicFormat::Raster::Thumbnail : public XdwGraphicFormat::Raster::DIB
{
public:

    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    Thumbnail();

    /**
     * @brief デストラクタ
     */
    virtual ~Thumbnail();

protected:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief PD情報を取得する
     *
     * @return XdwDocuWorks::ContentManager::PDInfoインターフェース参照
     */
    virtual XdwDocuWorks::ContentManager::PDInfo* GetPD();
    
    
};

#endif
