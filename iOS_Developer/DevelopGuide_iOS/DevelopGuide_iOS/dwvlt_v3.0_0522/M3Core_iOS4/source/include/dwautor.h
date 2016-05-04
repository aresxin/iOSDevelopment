// File: DWAUTOR.H
// Auther: Kiyoshi Tashiro
// Copyright(C) 1999 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef DWAUTOR_H
#define DWAUTOR_H

#include "mpc_api.h"
//#include "windows.h"

MPC_EXTERN_GUID(IID_AUTOROTATE, 0x1324);

mpinterface DWAutoRotate : public MPCInterface
{
//自動正立機能
STDMETHOD(MPCEstimateDirectionInit)(void) PURE;
STDMETHOD(MPCEstimateDirection)(MPCObject *basicpage, MPC_AdvCancelInfo *info = NULL) PURE;
STDMETHOD(MPCEstimateDirectionFinish)(void) PURE;

};

#define DWAUTOR_ERR_NOIMAGE     -1 /* イメージPDが無い */
#define DWAUTOR_ERR_BADIMAGE    -2 /* 画像の形式が対象外 */
#define DWAUTOR_ERR_FXTR_INIT   -3 /* 文字認識モジュールの初期化に失敗 */
#define DWAUTOR_ERR_NOINIT      -4 /* 文字認識モジュールが初期化されていない */
#define DWAUTOR_ERR_MEMORY      -5 /* メモリ関係のエラー */
#define DWAUTOR_ERR_BAD_DEPTH   -6 /* BMPファイルが白黒でない */
#define DWAUTOR_ERR_CANCELED    -7 /* キャンセルされた */
#define DWAUTOR_ERR_POOR_CHAR -100 /* 認識できる文字が十分に無かった */
                                   /* 文字が少ない、画質が悪いなど */

#endif //DWAUTOR_H

//CHANGE LOG
//99.6.28 - Tashiro - V4自動正立機能のインタフェースを SPIBindMPCLT に編入
//99.6.29 - Ichiriki - 田代,中澤 とモジュール構成を協議しMPCLT から分離
