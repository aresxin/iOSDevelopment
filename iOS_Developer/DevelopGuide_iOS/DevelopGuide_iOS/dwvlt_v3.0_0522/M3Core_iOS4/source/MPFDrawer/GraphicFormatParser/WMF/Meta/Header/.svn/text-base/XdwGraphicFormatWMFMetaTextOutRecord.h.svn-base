/**
 * @file  XdwGraphicFormatWMFMetaTextOutRecord.h
 * @brief XdwGraphicFormat::WMF::Meta::TextOutRecordクラスの定義
 *
 * @author Yasuhiro.Ito@fujixerox.co.jp
 * @date 2005-01-19
 * @version 1.0
 * $Id: XdwGraphicFormatWMFMetaTextOutRecord.h,v 1.4 2009/12/22 08:10:47 chikyu Exp $
 *
 * Copyright (C) 2005 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_GRAPHICFORMAT_WMF_META_TEXT_OUT_RECORD_H_
#define _XDW_GRAPHICFORMAT_WMF_META_TEXT_OUT_RECORD_H_

/* パッケージを記述するためのIncludeファイル */
#include "XdwGraphicFormatWMFMeta.h"

/* 親クラスのIncludeファイル */
#include "XdwGraphicFormatWMFMetaRecord.h"

/* 集約するクラスのIncludeファイル */
#include "XdwGraphicFormatGDIPoint.h"
#include "XdwFont.h"
/**
 * @brief META_TEXTOUTを規定するクラス
 * <br> AR11957 対応 TEXTOUTはかなり古いレコードで特殊な形式をしているので、GDIパッケージは使わないで
 * このクラスだけで処理を完結させる<br>Bridgeには通常のI/Fを用いる。
 *
 */
class XdwGraphicFormat::WMF::Meta::TextOutRecord : public XdwGraphicFormat::WMF::Meta::Record
{
public:
    
    /********************************************/
    /* メソッド */

    /**
     * @brief デフォルトコンストラクタ
     */
    TextOutRecord();
    
    /**
     * @brief デストラクタ
     */
    virtual ~TextOutRecord();
    
    /**
     * @brief META_EXTTEXTOUTをパースする
     *
     * 拡張テキスト描画命令をパースして、Imagerに渡す
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Parse();
    
protected:
    /*! 座標を管理するクラス */
    XdwGraphicFormat::GDI::Point fPoint;
    /*! テキスト情報を受け渡すためのクラス */
    XdwCodeText fText;
    	
    /********************************************/
    /* メソッド */
    
    /**
     * @brief インスタンスを初期化する
     *
     * 集約や属性の初期化
     *
     * @return XdwErrorCode参照
     */
    virtual XdwErrorCode Initialize();
private:
	/**
	* @brief 文字列を読み込む
    *
	* @param count 文字列の長さ
	*
	* @return XdwErrorCode参照
	*/
	XdwErrorCode ReadString(long);
};

#endif
