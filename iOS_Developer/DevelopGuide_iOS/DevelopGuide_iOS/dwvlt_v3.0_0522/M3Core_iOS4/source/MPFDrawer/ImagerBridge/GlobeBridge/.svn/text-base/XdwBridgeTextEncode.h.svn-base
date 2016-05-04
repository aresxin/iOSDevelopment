/*!
  @file  XdwBridgeTextEncode.h
  @brief 文字コードEnCode/DeCodeクラスヘッダファイル

  文字コードをEncodeするためのクラスを記述する．

  @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
  @date 2002-06-21
  @version 0.1

  Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
  Created:	2002-06-21	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGETEXTENCODE_H_INCLUDED
#define XDWBRIDGETEXTENCODE_H_INCLUDED

class XdwBridgeTextEncoder {
 private:
    int ConvSJIStoUTF16( unsigned char*, unsigned short* );
 public:
    XdwBridgeTextEncoder();
    ~XdwBridgeTextEncoder();

    void ConvertSJIStoUTF16( unsigned char *, int, unsigned short* );
};

#endif	/* XDWBRIDGETEXTENCODE_H_INCLUDED */
