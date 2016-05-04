// File: OKD_PUB.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef _MP_OKD_PUB_
#define _MP_OKD_PUB_

/*
*     MetaPaper MP_OKD API
*/

class MP_OKDEncPrivateOrg;
class MP_OKDEncPrivateNew;

class MP_OKDEncodePublic
{
  public:
    MP_OKDEncodePublic();
    ~MP_OKDEncodePublic();
    long Initialize();
    long Encode(long orgBytes, const void* orgMem, void* packedMem);
        // RETURN : packedBytes    

  private:
    MP_OKDEncPrivateOrg *m_ppr_org;
    MP_OKDEncPrivateNew *m_ppr_new;
};

class MP_OKDDecPrivate;
class MP_OKDDecodePublic
{
  public:
    MP_OKDDecodePublic();
    ~MP_OKDDecodePublic();
    long Initialize();
    long Decode(long packedBytes, const void* packedMem, long orgBytes, void* orgMem);
        //RETURN : orgBytes
  private:
    MP_OKDDecPrivate*  m_ppr;
};

#endif // _MP_OKD_PUB_

//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.8.8 - Ichiriki - PDフォーマット変更 ： 圧縮制御インタフェースの開示
//97.3.18 - R.Matsumura - AR544 データが小さいとき、かつ、インスタンス作成・圧縮・インスタンス削除を繰り返す
//				ようなときに、遅くなるのを解消.sourceのsizeをみて、使う圧縮ルーチンをかえる.
