// File: MP_CHILD.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*	MP_CHILD.H	: MPCObjectの従属オブジェクト管理
*
*	MP/Content/ContDoc コア実装者に提供するコア内部ユーティリティ。
*
*	子を持つMPCObjectインタフェースのためのデフォルト実装で利用義務はない。
*
*	仕様：	しばらくは、子を持つＭＰ,付箋,CDocのコア実装者以外には公開しない

"従属オブジェクト管理"オブジェクト

ドキュメントデータモデル層のMetaPaper、basic-page、 付箋オブジェクトに共通の従属オブジェクト管理処理を集約したオブジェクト。MP_Childrenインタフェースを提供する。

*/

#ifndef MP_CHILD_H
#define MP_CHILD_H

#include "mpc_spi.h"

// mpc_spi.hに定義移動


#endif //MP_CHILD_H

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//97.3.19 - Nagano - AR466 GetMaxNumberOfPreLoadChidren() GetNthPreLoadChild()の追加
//97.10.21 - Ichiriki - mpc_spi.hに定義移動
