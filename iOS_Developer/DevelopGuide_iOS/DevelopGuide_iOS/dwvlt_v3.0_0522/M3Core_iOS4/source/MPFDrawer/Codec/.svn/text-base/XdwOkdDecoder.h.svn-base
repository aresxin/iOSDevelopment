/** 
 * @file  XdwOkdDecoder.h
 * @brief XdwOkdDecoderクラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-4-1
 * @version 1.0
 * $Id: XdwOkdDecoder.h,v 1.4 2009/12/22 08:11:00 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OKD_DECODER_H_
#define _XDW_OKD_DECODER_H_

/* 依存するパッケージのIncludeファイル */
#include "XdwDataObject.h"

/* 列挙型の定義のためのIncludeファイル */
#include "XdwError.h"

/* 親クラスのIncludeファイル */
#include "XdwOkdCommon.h"

/**
 * @brief OKD圧縮されたバイナリーデータを一気に伸張するクラス
 *
 * 指定されたXdwDataObject::Common中の圧縮データをXdwDataObject::Common中に伸張する
 */
class XdwOkdDecoder : public XdwOkdCommon
{
public:
    /********************************************/
    /* メソッド */
  
    /**
     * @brief デフォルトコンストラクタ
     */
    XdwOkdDecoder();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOkdDecoder();
    
    /**
     * @brief OKD圧縮されたバイナリデータを展開する
     *
     * @param src OKD圧縮されたバイナリデータが格納されている
     *            XdwDataObject::Commonインターフェース
     * @param src_offset OKD圧縮されたバイナリデータの先頭位置の
     *                   データ先頭位置からのオフセット
     * @param src_size OKD圧縮されたバイナリデータのサイズ
     * @param dst OKD展開後のバイナリデータを格納するための
     *            XdwDataObject::Commonインターフェース
     * @param dst_offset OKD展開後のバイナリデータの先頭位置への
     *                   データ先頭位置からオフセット
     * @param dst_size OKD展開後のバイナリデータのサイズ
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Decode(XdwDataObject::Common* src,
                                long src_offset,
                                long src_size,
                                XdwDataObject::Common* dst,
                                long dst_offset,
                                long dst_size);

};

#endif
