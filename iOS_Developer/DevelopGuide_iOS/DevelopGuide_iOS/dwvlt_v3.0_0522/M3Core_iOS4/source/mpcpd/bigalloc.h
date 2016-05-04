
// File: BigAlloc.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.


/*
*	PD作業領域など、メモリ不足チェックを実装する、大量メモリの獲得に利用する
*		通常は、new オーバライドでまとめてメモリ不足処理（再試行＆終了）を行う
*/
BINDFUNC_(void*, MPBigAlloc)(unsigned int nSize);
BINDFUNC_(void, MPBigFree)(void* p);

//CHANGE LOG
//96.9.2 - Ichiriki - 作成
