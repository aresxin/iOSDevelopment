// File: STGTEMPFILE.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_TEMPFILE_H__
#define __STG_TEMPFILE_H__

#include "okd_pub.h"
#include "stg.h"


class ImplStgFileBDData {

public:
	long	m_BDID;
	long	m_offset;
	long	m_size;
	long	m_space;
	long	m_refnum;
	unsigned long	m_compressed_checksum;

	ImplStgFileBDData(void);
	~ImplStgFileBDData();
};

class ImplStgMemBDData {

public:
	long	m_BDID;
	long	m_size;
	void*	m_data;
	unsigned long	m_native_checksum;
	long	m_compressed_size;
	void*	m_compressed_data;
	unsigned long	m_compressed_checksum;
	long	m_refnum;

	ImplStgMemBDData(void);
	~ImplStgMemBDData();
};

class ImplStgTempBDMgr {

public:
	HRESULT MoveToFile( ImplStgMemBDData* mem_bd_data );
	size_t CalcMemoryLimit();
	long m_MemBDSize;
	ImplSession*	m_Session;
	ImplStgFileIO*	m_TempFile;
	MP_PtrArray*	m_FileBDTable;
	MP_PtrArray*	m_MemBDTable;
	long			m_NewBDID;		// 新規発行BDID
    MP_OKDEncodePublic*	m_OKDEncode;
    MP_OKDDecodePublic*	m_OKDDecode;
	MP_PtrArray*	m_ReusableFileBDTable;
	MP_PtrArray*	m_ReusableMemBDTable;
	
	ImplStgTempBDMgr( ImplSession* session );
	~ImplStgTempBDMgr();
	HRESULT Destroy(void);
	HRESULT CreateTempFile(void);
	BDID GetNewBDID(void);
	ImplStgReadOnlyDataIO* GetBDStgDataIO( BDID bdid );
	HRESULT SetAttribute( const MP_AName* aname, ATTR_ID aid, const MP_AValue* avalue, ImplStgAtt* rtn_att, MP_Integer do_compress, MP_Integer do_encrypt, MP_Integer reusable );
	HRESULT SetAttributeF( const MP_AName* aname, ATTR_ID aid, MP_AType atype, const MP_WPath* path, ImplStgAtt* rtn_att, MP_Integer reusable );
	BDID SetBD( ImplStgReadOnlyDataIO* bd_file, ImplStgAtt* ret_att, MP_Integer reusable, HRESULT* phres );
	HRESULT SetCopyBD( BDID bdid );
	HRESULT DeleteBD( BDID bdid );
	ImplStgFileBDData* GetFreeBDData( long bd_size );

	BDID SearchSameBD( void* data, long len, MP_Integer do_compress, HRESULT* phres );
	BDID SearchSameBD( ImplStgReadOnlyDataIO* bd_io, HRESULT* phres );
	BDID SearchSameBDF( const MP_WPath* path, HRESULT* phres );
	HRESULT IsReusableBD( BDID bdid );
	unsigned long GetBDCheckSum( BDID bdid, HRESULT *phres );
#ifndef SFXVW
	long HoldCompressedData( BDID bdid, HRESULT* phres );
	HRESULT ReleaseCompressedData( BDID bdid );
#endif

private:
	ImplStgMemBDData* GetLargestMemBD();
	HRESULT SetAttributeToFile( const MP_AName* aname, ATTR_ID aid, const MP_AValue* avalue, ImplStgAtt* rtn_att, MP_Integer do_compress, MP_Integer do_encrypt, MP_Integer reusable );
	HRESULT SetAttributeToMem( const MP_AName* aname, ATTR_ID aid, const MP_AValue* avalue, ImplStgAtt* rtn_att, MP_Integer do_compress, MP_Integer do_encrypt , MP_Integer reusable);
	HRESULT SetSameAttribute( const BDID same_bd, const MP_AName* aname, ATTR_ID aid, const MP_AValue* avalue, long compressed_size, ImplStgAtt* rtn_att );
	HRESULT SetAttributeFToFile( const MP_AName* aname, ATTR_ID aid, MP_AType atype, const MP_WPath* path, ImplStgAtt* rtn_att, MP_Integer reusable );
	HRESULT SetAttributeFToMem( const MP_AName* aname, ATTR_ID aid, MP_AType atype, const MP_WPath* path, ImplStgAtt* rtn_att, MP_Integer reusable);
	HRESULT SetSameAttributeF( const BDID same_bd, const MP_AName* aname, ATTR_ID aid, const MP_AType atype, const MP_WPath* path, long compressed_size, ImplStgAtt* rtn_att );
	HRESULT IntoFile( const long size );
	HRESULT IntoFileF( const MP_WPath* path );
	BDID SetBDToFile( ImplStgReadOnlyDataIO* bd_file, ImplStgAtt* ret_att, MP_Integer reusable, HRESULT* phres );
	BDID SetBDToMem( ImplStgReadOnlyDataIO* bd_file, ImplStgAtt* ret_att, MP_Integer reusable, HRESULT* phres );
	BDID SearchSameBDAux( void* data, long len, MP_Integer do_compress, long *ret_compressed_size, HRESULT* phres );
	BDID SearchSameBDAux( ImplStgReadOnlyDataIO* bd_io, MP_Integer has_tag, long *ret_compressed_size,  HRESULT* phres );
	BDID SearchSameBDFAux( const MP_WPath* path, long *ret_compressed_size, HRESULT* phres );
	long GetFileSize( const MP_WPath* path, HRESULT *phres = NULL );
	HRESULT AddToReusableBDList( BDID bdid );
};

#endif //#ifndef __STG_TEMPFILE_H__

//
//CHANGE LOG
//97.10.21 - Nagano - 作成
//97.10.28 - Nagano - ディスクフル・エラー処理を追加
//97.11.13 - Nagano - 一時ファイルのガベージコレクション導入
//---- お試し版990531リリース
//1999.06.09 - Tashiro - V4開発: メモリからのSetBD追加
//1999.06.25 - Tashiro - V4開発: BD因数化の実装
//---- 990726インテグ
//1999.07.30 - Tashiro - V4開発: ピークメモリ消費量抑止を実装
//---- 990830インテグ
//1999.09.06 - Tashiro - V4 AR4745 自己解凍文書用ビューワサイズ削減
// ----6.0.5----
//2005.11.08 - Kudo - 64bit対応
