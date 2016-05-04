/** 
 * @file  XdwOffScreenWriterDIB.h
 * @brief XdwOffScreenWriterDIBクラスの定義
 *
 * @author DPC DS&S STD T31G Yozo Kashima <Yozo.Kashima@fujiexreox.co.jp>
 * @date 2002-10-22
 * @version 1.0
 * $Id: XdwOffScreenWriterALLA.h,v 1.4 2009/12/22 08:11:39 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_OFF_SCREEN_WRITER_ALLA_H_
#define _XDW_OFF_SCREEN_WRITER_ALLA_H_

/* 列挙型のためのIncludeファイル */
#include "XdwError.h"

/* スーパークラス*/
#include "XdwOffScreenWriter.h"

/**
 * @brief XdwOffScreenDIBをALLA形式でファイルに書き込むためのクラス
 *
 * XdwOffScreenDIBのALLAフォーマットでファイルに書き込む機能を本クラスに切り出した。
 */
class XdwOffScreenWriterALLA : public XdwOffScreenWriter
{
public:
    
    /********************************************/
    /* メソッド */
  
    /**
     * @brief コンストラクタ
     *
     * @param offscreen 書き込み対象のオフスクリーン
     */
    XdwOffScreenWriterALLA();
  
    /**
     * @brief デストラクタ
     */
    virtual ~XdwOffScreenWriterALLA();
    
    /**
     * @brief オフスクリーンをファイルに書き込む
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode WriteTo(TCHAR* file_name);
private:
	typedef XdwOffScreenWriter Super;
};

#endif