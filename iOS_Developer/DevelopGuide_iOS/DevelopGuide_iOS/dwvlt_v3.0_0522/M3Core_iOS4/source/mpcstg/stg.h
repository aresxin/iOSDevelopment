// File: STG.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_STG_H__
#define __STG_STG_H__

#include "mpc_api.h"
#include "mpcwcstr.h"

//const int MPMSTG_VERSION = 7;
//const int MPMSTG_NEW_VERSION = 8;
        // 1: 06/12    --- 06/22
        // 2: 06/28    --- end of proto2
		// 3: 01/12/96 --- (proto3 develop)
		// 4: 08/08/96 --- change PD format (add MH, & change compress rule)
		// 5: 01/27/97 --- StgVersion5 == Docuworks V2.0 
		// 6: 30/09/97 --- StgVersion6 == Docuworks V3.0
		// 7: 19/05/99 --- StgVersion7 == Docuworks V4.0
		// 8: 01/04/2002 --- StgVersion8 == Docuworks V5.0 (Signatured Docs, 128-Crypted Docs)
		// 10: 29/11/2007 --- StgVersion10 == DocuWorks 7.0
const int MPMSTG_VERSION_V4 = 7;
const int MPMSTG_VERSION_V5 = 8;
const int MPMSTG_VERSION_V6 = 9;                                                                        
const int MPMSTG_VERSION_V7 = 10;


typedef  unsigned long TAG_TYPE;
#define TAG_SIZE    1

#define INVALID_TAG ((TAG_TYPE)(0))

#define ASN1_APPLMSK (TAG_TYPE)0x1F
#define ASN1_INT     (TAG_TYPE)0x02
#define ASN1_OCTSTR  (TAG_TYPE)0x04

#define MPTG_   0x60
#define PRTG_   0xC0
#define CSTG_   0x80

#define TAG_MASK (TAG_TYPE)0x1F

#define TAG_METAPAPER (TAG_TYPE)(MPTG_|0)
#define TAG_UPDATEBODY (TAG_TYPE)(MPTG_|1)
#define TAG_PDBODY	(TAG_TYPE)(MPTG_|1)
#define TAG_STORAGE (TAG_TYPE)(MPTG_|2)
#define TAG_BULKDATA (TAG_TYPE)(MPTG_|4)
#define TAG_TREEBODY (TAG_TYPE)(MPTG_|2)
#define TAG_COMPRESSED_TREEBODY	(TAG_TYPE)(MPTG_|3)
#define TAG_TRAILER	(TAG_TYPE)(MPTG_|5)
//v4 secu
#define TAG_ENCRYPTED_TREEBODY	(TAG_TYPE)(MPTG_|6)
#define TAG_ENCRYPTED_BULKDATA (TAG_TYPE)(MPTG_|7)
// VLTforWeb ByteServe
//#ifdef DWBYTESERVE
#define TAG_METAPAPER_BYTESERVE (TAG_TYPE)(MPTG_|1)
	//TAG_METAPAPERと異なり、かつ１バイトにエンコードされる値にする
//#endif
// V5
#define TAG_TRAILER_V5	(TAG_TYPE)(MPTG_|8)

//// Tag for Header
#define TAG_VERSION (TAG_TYPE)(CSTG_|2)
#define TAG_ROOTASSORT  (TAG_TYPE)(CSTG_|0)
#define TAG_CRLFCHECKDATA  (TAG_TYPE)(CSTG_|3)
#define TAG_LOCALPROF   (TAG_TYPE)(CSTG_|1)

//// Tag for Storage block in tree body
#define TAG_LEVEL   (TAG_TYPE)(CSTG_|0)
#define ASSORTMENT_POSITION 2
#define TAG_ASSORTMENT  (TAG_TYPE)(MPTG_|ASSORTMENT_POSITION)
#define TAG_PAGEPDBODY  (TAG_TYPE)(CSTG_|16)
#define TAG_BULKBODY    (TAG_TYPE)(CSTG_|17)

//// Tag for Local Profile
#define TAG_LP_VER (TAG_TYPE)(CSTG_|1)		// LocalProfile - Storage Version
#define TAG_LP_NPD (TAG_TYPE)(CSTG_|2)		// LocalProfile - Number of PD
#define TAG_LP_PDC (TAG_TYPE)(CSTG_|3)
#define TAG_LP_BAS (TAG_TYPE)(CSTG_|4)		// LocalProfile - Bulkdata each Array size
#define TAG_LP_BDS (TAG_TYPE)(CSTG_|5)		// LocalProfile - Bulkdata size
#define TAG_LP_TBS (TAG_TYPE)(CSTG_|6)		// LocalProfile - TreeBody size
#define TAG_LP_NBD (TAG_TYPE)(CSTG_|7)		// LocalProfile - Nubmer of BulkData

//// Tag for Bulkdata Reference --> Compress0719
// Postion
#define TAG_BR_POS (TAG_TYPE)(CSTG_|1)
// Length
#define TAG_BR_LEN (TAG_TYPE)(CSTG_|2)
//// Compress Method (optional)
//#define TAG_BR_COMPMETHOD (TAG_TYPE)(CSTG_|3)
//// Original Data length before compressing (optional)
//#define TAG_BR_ORIGLEN (TAG_TYPE)(CSTG_|4)
//#define COMP_OKD 1 //Compress Method
//#define MINLEN_COMPRESS 327680 // Minumun length to compress 
// <-- Compress0719

//V4
//compressed-len optional
#define TAG_BR_COMPRESSEDLEN (TAG_TYPE)(CSTG_|3)
//encrypted-len optional
#define TAG_BR_ENCRYPTEDLEN (TAG_TYPE)(CSTG_|5)
//hash optional
#define TAG_BR_HASH (TAG_TYPE)(CSTG_|4)
//init-vector optional
#define TAG_BR_INITVECTOR (TAG_TYPE)(CSTG_|6)

//// Tag for Bulkdata
#define TAG_BD_CHECKSUM (TAG_TYPE)(CSTG_|1)
#define TAG_BD_DATA (TAG_TYPE)(CSTG_|2)

//// Tag for Trailer
#define TAG_TL_NBD  (TAG_TYPE)(CSTG_|0)
#define TAG_TL_BDO  (TAG_TYPE)(CSTG_|1)
#define TAG_TL_DEL  (TAG_TYPE)(CSTG_|2)
#define TAG_TL_OTS  (TAG_TYPE)(CSTG_|3)
#define TAG_TL_TBS  (TAG_TYPE)(CSTG_|4)
#define TAG_TL_TCS  (TAG_TYPE)(CSTG_|5)
#define TAG_TL_TSZ  (TAG_TYPE)(CSTG_|6)
//v4
#define TAG_TL_LOCALDATA  (TAG_TYPE)(CSTG_|7)
#define TAG_TL_SECURITYID  (TAG_TYPE)(CSTG_|8)
#define TAG_TL_SECURITYINFO  (TAG_TYPE)(CSTG_|9)
#define TAG_TL_TREEENCRYPTEDLEN  (TAG_TYPE)(CSTG_|10)
#define TAG_TL_TREEHASH  (TAG_TYPE)(CSTG_|11)
#define TAG_TL_MAC  (TAG_TYPE)(CSTG_|12)
#define TAG_TL_REUSABLE_BD_INFO  (TAG_TYPE)(CSTG_|13)
//V5
#define TAG_TL_SIGNATURE_NUM (TAG_TYPE)(CSTG_|14)
#define TAG_TL_SIGNATURE_DATA (TAG_TYPE)(CSTG_|15)
#define TAG_TL_SIGNATURE_LAST_POS (TAG_TYPE)(CSTG_|16)
//V6
#define TAG_TL_WATERMARK (TAG_TYPE)(CSTG_|17)

#define TAG_CONTEXT_SPECIFIC	0
#define TAG_PRIVATE 1

typedef long MP_Boolean;	// 0=FALSE,   not 0 = TRUE
typedef long OBJECT_TYPE;	// MPMOBJCT.TXTで記載された値
typedef unsigned long ATTR_ID;
typedef long BDID;
typedef long TRID;
//暗号化関係の64bitデータ
typedef unsigned __int64 UINT64;

const long	INVALID_SEEK_POINTER = -1;
const long	END_SEEK_POINTER = -2;
const long	INVALID_OBJECT_TYPE = -1;
const ATTR_ID	INVALID_AID = 0;
const BDID	INVALID_BDID = -1;
const TRID	INVALID_TRID = -1;
const unsigned long	INVALID_CHECKSUM = 0;
const long ATT_SIZE_TO_TEMP = 1024*1024*10;
const long COMPRESSED_ATT_SIZE_TO_TEMP = 1024*1024*2;
const long INITIAL_TEMP_BDID = -2;

//v4
const long CRLF_ORG = 0x010D0A01;
const long CRLF_0A_0D0A = 0x010D0D0A;
const long CRLF_0D0A_0A = 0x010A0100;
const long TRAILER_MAC_LEN = 24; //0531までは32
const long TREE_HASH_LEN = 8;
const long BD_HASH_LEN = 8;
const long UINT64_LEN = 8;
const long CRYPT_UNIT = 8;

// V5 128bit暗号対応
const long TRAILER_MAC_LEN_128 = 32;
const long TRAILER_MAC_LEN_MAX = TRAILER_MAC_LEN_128;	// AES256bitまでは32バイトで大丈夫
const long CRYPT_UNIT_AES128 = 16;
const long CRYPT_IVEC_MAX_SIZE = 16;

// V5.0.2 AR6978
const int MAX_PATH_SAVE = 255;
	// mpcstgでファイル保存するときの最大パス長。5.0.1までも255でハードコードされていた。
	// AR6978でファイルを開くときの最大パス長は、_MAX_PATH-1(259)まで許す仕様に変更した。

class ImplSession;
class ImplStgTree;
class ImplStgWriteData;
class ImplStgObj;
class ImplStgAttManager;
class ImplStgAtt;
class ImplStgTempBDMgr;
class ImplStgFileIO;
class ImplStgReadOnlyFileIO;
class ImplStgMemIO;
class ImplStgReadOnlyDataIO;


// in stgtree.cpp
ImplStgTree* CreateScratchStgTree( ImplSession* session, ImplStgObj* root_stgobj, MPCObject* mpcobj, HRESULT* phres );

// in mpfile.cpp
MP_File* MP_File_Open(const MP_WPath* fileName, MP_OpenMode omMode, HRESULT* phres, MP_Integer deleteFileOnClose );
MP_File* MP_File_Open_No_Share(const MP_WPath* fileName, MP_OpenMode omMode, HRESULT* phres, MP_Integer deleteFileOnClose );
MP_File* MP_File_Create(const MP_WPath* fileName, HRESULT* phres, MP_Integer deleteFileOnClose, MP_Integer overwrite );
MP_File* MP_File_Create_Hidden(const MP_WPath* fileName, HRESULT* phres, MP_Integer deleteFileOnClose, MP_Integer overwrite );
HRESULT	MP_File_Remove(const MP_WPath* fileName);
HRESULT	MP_File_Rename(const MP_WPath* oldName, const MP_WPath* newName);
HRESULT	MP_File_Copy(const MP_WPath* oldName, const MP_WPath* newName, MP_Integer fFailIfExists);
HRESULT	MP_File_SetAttributes(const MP_WPath* fileName, MP_OpenMode attribute);
HRESULT	MP_File_SetHidden( const MP_WPath* fileName );
HRESULT	MP_File_UnsetHidden( const MP_WPath* fileName );

MP_File* MP_File_Open_From_Handle( const MP_WPath* fileName, void* hFile, MP_OpenMode omMode, HRESULT* phres, MP_Integer deleteFileOnClose );

//HRESULT MPGetLastError();

// in stgfileio.cpp
ImplStgFileIO* CreateStgFileIO( MP_File* mp_file, MP_Integer delete_mp_file, HRESULT* phres );
ImplStgFileIO* CreateStgFileIO( const MP_WPath* path, MP_OpenMode open_mode, MP_Integer delete_mp_file, MP_Integer delete_file, HRESULT* phres );
ImplStgFileIO* CreateStgFileIONoShare( const MP_WPath* path, MP_OpenMode open_mode, MP_Integer delete_mp_file, MP_Integer delete_file, HRESULT* phres );
ImplStgReadOnlyFileIO* CreateStgReadOnlyFileIO( MP_File* mp_file, long offset, long size );

// in stgmemio.cpp
ImplStgMemIO* CreateStgMemIO( char* data, long alloca_size, MP_Integer delete_data, HRESULT* phres );

// in DataCheck.cpp
unsigned long GetDataCheckKey( void* data, long size, HRESULT* phres );
unsigned long GetDataCheckKey( ImplStgReadOnlyDataIO* file, HRESULT* phres );
unsigned long GetDataCheckKeyF( const MP_WPath* path, HRESULT* phres );
unsigned long GetDataCheckKeyF( ImplStgReadOnlyDataIO* file, HRESULT* phres );
//unsigned long ReadCheckSumInFile( ImplStgReadOnlyDataIO* file );
HRESULT DataCheck( void* data, long size, unsigned long data_check_key );
HRESULT DataCheck( ImplStgReadOnlyDataIO* file );
HRESULT CheckCRLF( long dummy );
HRESULT IsSameDataBD( ImplStgReadOnlyDataIO* bd_io, void* data, long len, void* comp_data, long comp_len );
HRESULT IsSameDataBD( ImplStgReadOnlyDataIO* ref_io, ImplStgReadOnlyDataIO* new_io, MP_Integer has_tag );

// in BDFile_Util.cpp
unsigned long BDF_ReadCheckSum( ImplStgReadOnlyDataIO* bdfile, HRESULT *phres );
long BDF_GetDataSize( ImplStgReadOnlyDataIO* bdfile, HRESULT *phres );
long BDF_ReadData( ImplStgReadOnlyDataIO* bdfile, char* dst, HRESULT *phres );
HRESULT BDF_SeekToData( ImplStgReadOnlyDataIO* bdfile );


#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#ifdef _DEBUG
#ifdef VERBOSE_ASSERT
#include "assert.h"
#define DEBUG_ASSERT(x) assert(x)
#else
#define DEBUG_ASSERT(x) ;
#endif
#else
#define DEBUG_ASSERT(x) ;
#endif

// V5以降：データの暗号/復号化用の鍵情報を保持する構造体
const MP_Integer MPC_CRYPT_MAX_KEY_BYTES = 32;	// 最大256bitまではバッファを確保
struct MPCCryptKey {
	char key[MPC_CRYPT_MAX_KEY_BYTES];	// 鍵のデータ
	unsigned int keyLen;				// 鍵の長さ(ビット数)
	long cryptType;						// 暗復号の種類
	long dataBoundary;					// 暗復号するデータのバウンダリ(バイト数)
	// 以下はユーティリティ用
	MPCCryptKey();
	~MPCCryptKey();
	bool IsValid();		// 鍵データが0でないかどうか調べる
	bool operator==(const MPCCryptKey& target);					// 比較用
	bool operator!=(const MPCCryptKey& target);					// 比較用
	const MPCCryptKey& operator=(const MPCCryptKey& target);	// 代入用
	void Init();		// 0にする
};

// Windows APIレベルのエラーをログ書き出しするための構造体
// 将来的にコアの上にこの情報を出すときには、外部向けのヘッダに移動する
typedef struct {
	int iStructSize;
	long int iAPIErrorCode;
	mpcwcstring filepath;
	mpcwcstring errorAPI;
} MP_ErrorInfo;

#endif // __STG_STG_H__

//
//CHANGE LOG
//97.10.21 - Nagano - 作成
//97.10.30 - Nagano - BDのチェックサム導入準備による変更
//97.11.06 - Nagano - Checksum導入による変更
//97.11.13 - Nagano - ATT_SIZE_TO_TEMPをグローバル変数に変更
//98.06.12 - Nagano - MP_File_Createの変更
//1999.05.19 - Tashiro - V4.0: MPMSTG_VERSIONを7に変更、CheckCRLF宣言追加
//---お試し版990531リリース
//1999.05.31 - Tashiro - V4 TAG_ENCRYPTED_TREEBODY追加、暗号関連関数の修正
//1999.06.01 - Tashiro - 暗号化関係の関数の宣言をcrypt_util.hに移動
//1999.06.09 - Tashiro - バルク関連タグ追加、ハッシュ長など修正
//1999.06.09 - Tashiro - V4開発: BD(保護なし)のチェックサム関連関数追加
//1999.06.27 - Tashiro - V4開発: BD因数化の実装
//1999.07.06 - Tashiro - V4開発: CreateStgFileIONoShare追加 (一時ファイル用)
//---- V4.1
//2000.05.30 - Tashiro - バイトサーブ用コード(DWBYTESERVE)の挿入
//---- V5
//2002.02.23 - Tashiro - セキュリティ関連のID定義をmpc_secu.hに移動
//2002.04.16 - Tashiro - インクルード構成を変更(コンパイル効率の改善のため)
//2002.04.19 - Tashiro - 署名文書用トレーラタグの追加
//2002.05.14 - Nakazawa - 128bit暗号対応
//2002.05.18 - Tashiro - ファイルバージョン(V4/V5)の定義変更
//2002.07.30 - Tashiro - AR8160 V5フォーマット保存時はトレーラのタグも変更する
//2002.11.12 - Tashiro - 5.0.2 AR6978対応 開くときはパス長を259バイトまで許すように修正
//---- 6.0開発
//2004.04.06 - Tashiro - V6.0 V6フォーマット定義追加
//2004.05.12 - Tashiro - V6.0 TMBトレーラ属性対応
//2004.06.29 - Tashiro - AR9358切り分け用に署名のバージョンをトレーラに追加
//2004.07.16 - Tashiro - AR9358/10026 ツリー内の署名バージョン読み込み実装
//2004.07.26 - Tashiro - AR9951 ファイルに隠し属性を付ける/はずす関数を追加
//2004.07.29 - Tashiro - AR9358/10026 ツリー内の署名バージョンをキャンセル
//2004.08.23 - Tashiro - AR9951 ファイル生成時から隠し属性を付ける関数を追加
//---- 6.2
//2006.07.20 - Tashiro - DE向けファイルオープン機能追加
//---- 7.0
//2007.11.29 - Komoda  - V7.0 MPMSTG_VERSION_V7を追加
