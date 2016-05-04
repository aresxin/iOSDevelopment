/**
 * @file  XdwBridgeRasterDecodeStrategyALLAv2.h
 * @brief XdwBridgeRasterDecoStALLAv2クラスの定義
 * @author OPBG-SD5G-54T Tomoki Kitahashi
 * @date 2004-07-14
 *
 * Copyright (C) 2004 Fuji Xerox Co., Ltd.
 */
#ifndef XDWBRIDGERASTERDECODESTRATEGYALLAV2_H_INCLUDED
#define XDWBRIDGERASTERDECODESTRATEGYALLAV2_H_INCLUDED

#include "XdwBridgeRasterDecodeStrategy.h"

namespace alla_v2
{
    class Dec;
}

/**
 * ALLAv2 Decode Class.
 *
 * ALLAv2をラスタにデコードするクラス.
 * ALLAv2デコード機能を提供する．
 */
class XdwBridgeDecoStALLAv2 : public XdwBridgeDecodeStrategy
{
public:
    XdwBridgeDecoStALLAv2();
    ~XdwBridgeDecoStALLAv2();

    XdwErrorCode Set(const XdwRasterImageAttribute& img_attr,
            XdwDataObject::Binary* img_data, long img_offset, long img_size);
    XdwErrorCode GetHeader(XdwRasterImageAttribute* img_header);
    XdwErrorCode ReadRaster(unsigned char* buffer);
    XdwErrorCode Finish(void);
    bool IsPaletteIndexOut(void);
    bool IsBottomUp(void);

private:
    alla_v2::Dec* allaF;           ///< liballa decoder object
    long read_data_numF;        ///< Data Objectから読み込んだデータ数
    long scanline_sizeF;        ///< デコードされたImageのスキャンラインサイズ[byte]
    unsigned char* out_bufferF; ///< Image出力バッファのアドレス

    static int CallBackIn(void* ptr, const int size, void* userdata);
    static int CallBackOut(void* ptr, const int size, void* userdata);
    XdwErrorCode GetStatus();
};

#endif /* XDWBRIDGERASTERDECODESTRATEGYALLAV2_H_INCLUDED */
