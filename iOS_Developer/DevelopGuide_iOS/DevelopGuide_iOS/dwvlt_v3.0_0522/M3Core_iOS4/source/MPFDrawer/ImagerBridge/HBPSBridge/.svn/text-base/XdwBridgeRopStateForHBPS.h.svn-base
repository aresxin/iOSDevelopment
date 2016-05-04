/*!
  @file  XdwBridgeRopStateForHBPS.h
  @brief XdwBridgeRopStateForHBPS クラスヘッダファイル

  XdwBridgeRopStateForHBPSクラスを記述する．

  @author Yozo Kashima (Fuji Xelox Co., Ltd. DPC DS&S STD) <Yozo.Kashima@fujixerox.co.jp>
  @date 2003-01-10
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC RDC4 T22G Yozo Kashima<br>
  Created:	2003-01-10	Yozo Kashima<br>
 */
#ifndef XDWBRIDGEROPSTATE_H_INCLUDED
#define XDWBRIDGEROPSTATE_H_INCLUDED

#include "XdwError.h"
#include "XdwBridgeCommon.h"
#include "XdwGraphicsAttribute.h"

/*! HostBasedImagerに出力するROPコードを管理する

  HostBasedImagerに出力するROPコードを管理する．<br>
  本クラスは，HostBasedImager専用の具象クラスである．
 */
class XdwBridgeRopStateForHBPS {
public:
    XdwBridgeRopStateForHBPS(void *imager);		//!< コンストラクタ
    virtual ~XdwBridgeRopStateForHBPS();	//!< デストラクタ

    XdwErrorCode SetRop2(XdwTypeUInt32 rop2Code);
    XdwErrorCode SetRop3(XdwTypeUInt32 rop3Code, bool hasImage);
    XdwErrorCode UpdateRop2();
private:
	void *imagerF;
    bool isRop2CurrentF;
    XdwTypeUInt32 rop2CodeF;
    XdwTypeUInt32 rop3CodeF;
};


#endif /* XDWBRIDGEROPSTATE_H_INCLUDED */
