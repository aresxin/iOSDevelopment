// File: MPFMT.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

//
#include "mpc_api.h"

#define MAX_INT_LEN 5

class MP_Format {
public:
    // memPtrからInt4数値をデコードしてvalueに返す。return値は使ったバイト数
    static long Decode(MP_Octet* memptr, long& value);

    // memPtrデコードして返す。lengthに値のバイト長、valOffsetにmemptr中での
    // 値の開始バイト位置を返す。return値は使ったバイト数
    static long Decode(MP_Octet* memptr, long& length, MP_Octet*& valptr);

    // valueをエンコードしmemPtrに書き込む。使ったバイト数を返す
    static long Encode(MP_Octet* memptr, long length, const MP_Octet* valptr);

    // int4値をエンコードしmemPtrに書き込む。使ったバイト数を返す
    static long Encode(MP_Octet* memptr, long value);
};

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
