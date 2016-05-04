/** 
 * @file  XdwDataObjectBaseBuffer.h
 * @brief XdwDataObject::Buffer抽象クラスの定義
 *
 * @author DPC DS&S STD T31G Tomohiro Yamada <Tomohiro.Yamada@fujiexreox.co.jp>
 * @date 2002-3-27
 * @version 1.0
 * $Id: XdwDataObjectBaseBuffer.h,v 1.4 2009/12/22 08:11:38 chikyu Exp $
 *
 * Copyright (C) 2002 Fuji Xerox Co., Ltd.
 */

#ifndef _XDW_DATA_OBJECT_BASE_BUFFER_H_
#define _XDW_DATA_OBJECT_BASE_BUFFER_H_

/* パッケージを記述するためのIncludeファイル */
#include "DataObject/Base/Include/XdwDataObjectBase.h"

/* 親クラスを定義したIncludeファイル */
#include "DataObject/Base/Include/XdwDataObjectBaseInterface.h"

/**
 * @brief バッファを用いてバイナリデータにアクセスする抽象クラス
 *
 * バッファを扱うための属性や、DataObjectの型を識別するための関数などを提供する
 */
class XdwDataObject::Base::Buffer : public XdwDataObject::Base::Interface
{
public:

    /********************************************/
    /* メソッド */
    
	/**
	* @brief コンストラクタ
	*/
	Buffer();
    /**
     * @brief デストラクタ
     */
    virtual ~Buffer();
    
    /**
     * @brief 複製可能かの確認
     *
     * @retval true 可能
     * @retval false 不可能
     */
    virtual bool IsClonable();
    
protected:

    /********************************************/
    /* 属性 */

    /*!  バッファを指すポインタ */
    unsigned char* fBuffer;
    /*!  データのバッファ上での現在位置のポインタ */
    unsigned char* fCurrentBufferPointer;
    /*!  データのバッファ先頭からのオフセット */
    long fCurrentBufferOffset;
    /*!  バッファのサイズ */
    long fBufferSize;
    /**
     * @brief 初期化フラグ
     *
     * Initialize()メソッドでこのフラグはたつ<br>
     * このフラグがたっていないと、他のメソッドは使えない<br>
     * ただし、Lock()メソッドは除く
     */
    bool fInitializeFlag;
    
};

#endif
