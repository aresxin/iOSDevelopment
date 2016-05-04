// File: mpc_cryp.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

#ifndef _MPC_CRYP_H_
#define _MPC_CRYP_H_

// DWコアとセキュリティモジュールで用いるDESやSHA1のヘッダをまとめたものである。
// コア共通ディレクトリに置いて、必要なモジュールがインクルードする。
// 同時に mpc_cryp.cpp もコピーしてプロジェクトに追加すること。
// (暗号復号I/Fを DLLExport すると、そこが攻撃の対象になり得るので、各モジュールで個別に実装する)

///////////////////////////// for DES ////////////////////////////////
#define DES_DIRMASK	001
#define DES_ENCRYPT	(0 * DES_DIRMASK)	// 暗号化するとき
#define DES_DECRYPT	(1 * DES_DIRMASK)	// 復号化するとき

// エラーコード
#define DESERR_NONE	0
#define DESERR_NOHWDEVICE 1
#define DESERR_HWERROR	2
#define DESERR_BADPARAM	3

int ecb_crypt(char* key, char* buf, unsigned len, unsigned mode);
int cbc_crypt(char* key, char* buf, unsigned len, unsigned mode, char* ivec);
void des_setparity(char* key);

/*
DES_CRYPT(3)           C LIBRARY FUNCTIONS           DES_CRYPT(3)

名前
     ecb_crypt, cbc_crypt, des_setparity - DES 暗号化／複号関数


書式
     #include <des_crypt.h>

     int ecb_crypt(key, buff, len, mode)
          char *key;
          char *buff;
          int len;
          unsigned mode;

     int cbc_crypt(key, buff, len, mode, vec)
          char *key;
          char *buff;
          int len;
          unsigned mode;
          char *vec;

     int des_setparity(key)
          char *key;


説明
     これらの関数は  Data Encryption Standard  による暗号化／複号
     ルーチンです。

     ecb_crypt は  Electric Code Book  方式による暗号化／複号を行
     います。 これは、 平文   buff の内容を  8 バイトずつのブロッ
     ク単位で、暗号鍵  key をつかって変換します。個々のブロックは
     独立に暗号化されますので、 平文の一部が分っている場合には、
     暗号鍵の割出しが比較的やりやすいという欠点があります。

     cbc_crypt は  Cipher Block Chaining 方式による暗号化／複号を
     行います。  CBC では、平文  buff の内容を  8 バイトずつ、鍵
     key を使って暗号化する点は  ECB と同じですが、暗号化前にひと
     つ前のブロックの変換結果と  XOR (排他的論理和)をとる点が異な
     ります。最初のブロックはパラメータ  vec の内容とXORされます。
     この方法では、平文の一部が分っていても、鍵の割出しは困難です。

     des_setparity は、鍵  key の各バイトの最上位ビットにパリティ
     をセットします。  key は、実際の暗号化の際には、各バイトの上
     位7ビットしかつかわれません。もしも、鍵として  ASCII コード
     を使うと、 最下位の1ビットが無駄になることになりますが、実際
     には最上位ビットにパリティをセットすることにより、最下位ビッ
     トの情報は最上位ビットに保存されますので、問題はありません。

     パラメータ  key には、暗号鍵を  8 バイトの配列として渡します。
     パラメータ   buff は、暗号化されるべき平文で、そのサイズはパ
     ラメータ  len が示しています。このサイズは  8 の倍数でなくて
     はいけません。  8 の倍数でない場合は、最後の半端な部分は変換
     されません。

     パラメータ  mode は、 変換操作が暗号化なのか複号なのかを示し
     ます。 定数  DES_ENCRYPT (ヘッダ  des_crypt.h で定義されてい
     る) であれば暗号化を、 DES_DECRYPT であれば複号を意味します。

     cbc_crypt におけるパラメータ  vec は、 8バイトの初期  XOR パ
     ターンを指定します。関数から戻ってきたとき、ここには最後のブ
     ロックの変換結果が格納されるので、一連の連続したデータを暗号
     化／複号するさいには、 同じ配列 vec を次の呼び出しで渡すだけ
     ですみます。


参考文献
     土居範久、「米国のデータ暗号化規格  DES」、 bit  1981年2月号、
     共立出版


取扱
     作者は本プログラムの著作権を放棄します。配布、変更、変更した
     ものの配布等、自由に行なってかまいません。

     ただし、変更したバージョンを公開する場合は、誰がいつ、どのよ
     うな変更を行なったかがわかるようにしておくのが好ましいでしょ
     う。

     本プログラムは無保証で提供されます。作者は本プログラムの実行
     結果に対する責任を一切負いません。本プログラムの使用、変更等
     は、各自の責任で行なってください。


作者の連絡先
     E-Mail
          kmori@lsi-j.co.jp

     日経MIX
          kmori

     アスキーネット
          pcs29537

     住所
          〒151 東京都渋谷区千駄ケ谷1-8-14
          エル・エス・アイ  ジャパン(株)
          森  公一郎

     FAX  (03)3478-0576


Version 1.00        Last change: 18 June 1993
*/
///////////////////////////// for DES (end) //////////////////////////


///////////////////////////// for SHA1 ///////////////////////////////
// data にハッシュ値を計算したいデータ、len にそのサイズを指定する。
// digest に計算されたハッシュ値が格納される(160bits/20bytes)。
#define SHA1HANDSOFF
void SHA1Calc(char* data, int len, char digest[20]);
///////////////////////////// for SHA1 (end) /////////////////////////


#endif // _MPC_CRYP_H_

// CHANGE LOG
// 1999.05.18 - Nakazawa - 新規作成
