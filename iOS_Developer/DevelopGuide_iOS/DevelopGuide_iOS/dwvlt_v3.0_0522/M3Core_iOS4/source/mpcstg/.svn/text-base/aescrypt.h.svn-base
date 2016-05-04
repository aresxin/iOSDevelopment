// File: aescrypt.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 2002 Fuji Xerox Co., Ltd. All right reserved.

#ifndef _AES_CRYPT_H_
#define _AES_CRYPT_H_

// AES(Rijndael)の暗号/復号関数(DESの関数と同じように使えるラッパー)

// 暗号/復号化の指定
const unsigned int AES_ENCRYPT = 0;
const unsigned int AES_DECRYPT = 1;

// 鍵のビット数
const unsigned int AES_KEY_128 = 128;
const unsigned int AES_KEY_192 = 192;
const unsigned int AES_KEY_256 = 256;

// 扱うデータのサイズは16バイトバウンダリにしなければならない
const unsigned int AES_DATA_BOUNDARY = 16;

bool aes_ecb_crypt(const char* key, const char* buf, unsigned int len, unsigned int mode, unsigned int keyLen = AES_KEY_128);
bool aes_cbc_crypt(const char* key, const char* buf, unsigned int len, unsigned int mode, const char* ivec = 0, unsigned int keyLen = AES_KEY_128);

/*
○aes_ecb_crypt
・説明：	AES(Rijndael)-ECBによる暗号/復号化を行う。入出力ともに同じメモリ上のデータを扱う。
・引数：	key		暗号/復号化に使用する鍵へのポインタ。keyLenで指定するビット数の領域に格納しておかなければならない。
			buf		処理したいデータへのポインタ。16バイトバウンダリになっていなければならない。
					この領域のデータが直接暗号/復号化される。
			len		pDataで確保している領域のバイト数。16の倍数でなければならない。
			mode	暗号化のときはAES_ENCRYPTを、復号化のときはAES_DECRYPTを指定する。
			keyLen	鍵のサイズをAES_KEY_128/192/256で指定する。
・返り値：	成功した場合はtrue。パラメータが不正だった場合はfalse。

○aes_cbc_crypt
・説明：	AES(Rijndael)-CBCによる暗号/復号化を行う。入出力ともに同じメモリ上のデータを扱う。
・引数：	key		暗号/復号化に使用する鍵へのポインタ。keyLenで指定するビット数の領域に格納しておかなければならない。
			buf		処理したいデータへのポインタ。16バイトバウンダリになっていなければならない。
					この領域のデータが直接暗号/復号化される。
			len		pDataで確保している領域のバイト数。16の倍数でなければならない。
			mode	暗号化のときはAES_ENCRYPTを、復号化のときはAES_DECRYPTを指定する。
			ivec	初期ベクトルへのポインタ。16バイトの領域を確保しておかなければならない。
					ポインタがNULLだった場合は、全て0のデータを初期ベクトルとして扱う。
			keyLen	鍵のサイズをAES_KEY_128/192/256で指定する。
・返り値：	成功した場合はtrue。パラメータが不正だった場合はfalse。
*/

#endif // _AES_CRYPT_H_

// CHANGES LOG
// 2002.05.14 - Nakazawa - 新規作成
