// File: CUTIL.H
// Auther: Maezawa Hiroaki
// Copyright(C) 1995,1996 by Fuji Xerox Co,. Ltd. All right reserved.

//

typedef  unsigned long TAG_TYPE;

#define MPTG_   0x60
#define PRTG_   0xC0
#define CSTG_   0x80

#define TAG_MASK (TAG_TYPE)0x1F

/************************************************************
                   CUtil Declaration
*************************************************************/
////////////////////////////////////////////////////////////
//  class CUtil: おもに、ASN1対応のエンコード/デコードのサービス関数
class CUtil {
public:
    // 属性tagをEncodeするのに必要なバイト数
    static long TagSize(unsigned long tag);

    // lengthをEncodeするのに必要なバイト数
    static long LengthSize(long length);

    // valueをint4でEncodeした時に必要なバイト数
    static long IntegerSize(long value);

    // memPtrからタグをデコードして返す。return値は使ったバイト数
    //static long SDecodeTag(char* memptr, unsigned long& tag);
    static long SDecodeTag(char* memptr, unsigned long& tag, long& isPrivate);

    // memPtrからInt4数値をデコードして返す。return値は使ったバイト数
    static long SDecodeInteger(char* memptr, long& value);

    // memPtrからLengthをデコードして返す。return値は使ったバイト数
    static long SDecodeLength(char* memptr, long& length);

    // tagをエンコードしmemPtrに書き込む。使ったバイト数を返す
    static long SEncodeTag(char* memptr, unsigned long tag);
    static long SEncodeTag(char* memptr, unsigned long tag, long isPrivate);

    // lengthをエンコードしmemPtrに書き込む。使ったバイト数を返す
    static long SEncodeLength(char* memptr, long length);

    // intValueをエンコードしmemPtrに書き込む。使ったバイト数を返す
    static long SEncodeInteger(char* memptr, long value);

};


//
//CHANGE LOG
//95.5.9 - Maezawa - 作成
//96.2.1 - Ichiriki - P2用実装を、P3用に変更
//96.6.10 - Ichiriki - Integ用変更
