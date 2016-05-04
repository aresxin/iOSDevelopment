/*!
  @file  XDWTestPrintController.h
  @brief TEST用PrintControllerクラスヘッダファイル

  n-up/小冊子の機能を提供する

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-05-17
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC CS&S STD Toshio Yamazaki<br>
  Created:	2002-05-17	Toshio Yamazaki<br>
 */
#ifndef XDWTESTPRINTCONTROLLER_H_INCLUDED
#define XDWTESTPRINTCONTROLLER_H_INCLUDED

#include "XdwError.h"
#include "XdwBridge.h"

class sifDevice_Info;

class XdwTestPrintController {
 private:
    sifDevice_Info		*di_f;
    XdwBridgePrintContIF	*printerif_f;
 public:
    XdwTestPrintController() {};
    ~XdwTestPrintController() {};

    XdwErrorCode Initialize( sifDevice_Info *, XdwBridgePrintContIF * );
    XdwErrorCode StartJob( void );
    XdwErrorCode EndJob( void );
    XdwErrorCode StartPage( const XdwBridgePrintContIF::PageMode & );
    XdwErrorCode ShowPage( void );
    XdwErrorCode EndPage( void );
};

#endif /* XDWTESTPRINTCONTROLLER_H_INCLUDED */
