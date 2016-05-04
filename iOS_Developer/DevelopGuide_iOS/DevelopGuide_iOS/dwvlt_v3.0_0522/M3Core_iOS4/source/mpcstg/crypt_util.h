// File: crypt_util.h
// Auther: Kiyoshi Tashiro
// Copyright(C) 1999 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_CRYPT_UTIL_H__
#define __STG_CRYPT_UTIL_H__

#include "stg.h"

#ifndef SFXVW
UINT64 GenerateRandomValue( unsigned int* pOld_seed );
UINT64 Encrypt64( const UINT64 data, const UINT64 key );
UINT64 Decrypt64( const UINT64 data, const UINT64 key );
UINT64 DecryptSessionKey( const UINT64 data, const UINT64 nonce, long int iSecurityID );
UINT64 Pad64( const long data );
HRESULT EncryptDesCbc( MP_Octet* data, UINT64 key, long size, UINT64 initvec );
HRESULT EncryptDesCbc( ImplStgReadOnlyDataIO* file, UINT64 key, UINT64 initvec, MP_Octet* out );
HRESULT DecryptDesCbc( MP_Octet* data, UINT64 key, long size, UINT64 initvec );
HRESULT DecryptDesCbc( ImplStgReadOnlyDataIO* file, UINT64 key, UINT64 initvec, MP_Octet* out );
HRESULT GetTrailerMAC( const MP_Octet* data, const long size, const UINT64 key, MP_Octet* mac );
HRESULT IsSameData( const MP_Octet* data1, const MP_Octet* data2, const long size );
HRESULT IsSameData( ImplStgReadOnlyDataIO* io1, ImplStgReadOnlyDataIO* io2 );
HRESULT GetTreeHash( const MP_Octet* data, const long size, MP_Octet* hash );
HRESULT GetBDHash( const MP_Octet* data, const long size, MP_Octet* hash );
HRESULT GetBDHash( ImplStgReadOnlyDataIO* file, MP_Octet* hash );

// V5 128bit暗号対応
HRESULT EncryptAesCbc( MP_Octet* data, const char* key, long size, const char* initvec, unsigned int keyLen = 128 );
HRESULT EncryptAesCbc( ImplStgReadOnlyDataIO* file, const char* key, const char* initvec, MP_Octet* out, unsigned int keyLen = 128 );
HRESULT DecryptAesCbc( MP_Octet* data, const char* key, long size, const char* initvec, unsigned int keyLen = 128 );
HRESULT DecryptAesCbc( ImplStgReadOnlyDataIO* file, const char* key, const char* initvec, MP_Octet* out, unsigned int keyLen = 128 );
HRESULT GetTrailerMAC_AES( const MP_Octet* data, const long size, const char* key, MP_Octet* mac, unsigned int keyLen = 128 );

// V5 複数の暗復号アルゴリズムに対応するように関数を追加
HRESULT EncryptDataEx( MP_Octet* data, const MPCCryptKey* key, long size, UINT64 initvec );
HRESULT EncryptDataEx( ImplStgReadOnlyDataIO* file, const MPCCryptKey* key, UINT64 initvec, MP_Octet* out );
HRESULT DecryptDataEx( MP_Octet* data, const MPCCryptKey* key, long size, UINT64 initvec );
HRESULT DecryptDataEx( ImplStgReadOnlyDataIO* file, const MPCCryptKey* key, UINT64 initvec, MP_Octet* out );
HRESULT GetTrailerMACEx( const MP_Octet* data, const long size, const MPCCryptKey* key, MP_Octet* mac );
HRESULT CheckSecuredDataKeyAndSetMPCCryptKey(const MP_Octet* psDataKey, MPCCryptKey* key);
long GetPaddedSize( const MPCCryptKey* key, long size );
long GetTrailerMACLen(const MPCCryptKey* key);

#endif //SFXVW

#endif // __STG_CRYPT_UTIL_H__

//
//CHANGE LOG
//99.06.01 - Tashiro - V4開発: 作成
//99.06.27 - Tashiro - V4開発: BD因数化の実装
//---- 990701ビルド
//99.07.01 - Tashiro - V4開発: 不要コード削除
//99.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//----V5-----
//2002.04.16 - Tashiro - インクルード構成を変更(コンパイル効率の改善のため)
//2002.05.14 - Nakazawa - 128bit暗号対応
//----- x64対応
//2005.10.17 - Kudo - x64対応：2.0の宣言追加
//----- マルチスレッド対応
//2006.05.26 - Kudo - マルチスレッド対応：乱数生成関数のシードを引数で与えるように変更
//---- 6.2 ----
//2006.06.12 - Kudo - の排他処理追加
//2006.07.20 - Tashiro - セキュリティモジュール追加対応
//---- 7.0 ----
//2007.12.10 - Kitahashi - 2.1対応
