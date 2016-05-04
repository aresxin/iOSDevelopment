// File: STGFILEIO.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_FILEIO_H__
#define __STG_FILEIO_H__

#include "stg.h"

const long READ_CACHE_SIZE = 2048;
const long WRITE_CACHE_SIZE = 2048;
const long MIN_READ_SIZE = READ_CACHE_SIZE/2;
const long MAX_WRITE_SIZE = WRITE_CACHE_SIZE/2;

class ImplStgFileIO
{
public:
	MP_File* m_MPFile;
	HRESULT	m_LastError;
	long	m_SeekPtr;

	ImplStgFileIO( MP_File* mp_file, MP_Integer delete_mp_file );
	~ImplStgFileIO();
	HRESULT	Destroy(void);
	HRESULT ClearErrorFlag(void);
	long	GetSize(void);
	HRESULT SetSize( MP_Integer size );
	long	Seek( long offset, MP_SeekMethod = MP_SEEK_BEGIN );
	char*	ReadCache( long length, HRESULT* phres = NULL );
	TAG_TYPE	ReadTag( HRESULT* phres = NULL );
	long	ReadLength( HRESULT* phres = NULL );
	long	ReadInteger( HRESULT* phres );
	long	Read( char* rtn_data, long size, HRESULT* phres = NULL );
	long	WriteCache( HRESULT* phres = NULL );
	long	WriteTag( TAG_TYPE tag_data );
	long	WriteLength(long length );
	long	WriteInteger(long value );
	long	Write( const void* data, long size, HRESULT* phres = NULL );
	long	Write( ImplStgFileIO* src_file_io, HRESULT* phres = NULL );
	long	Write( ImplStgReadOnlyDataIO* src_file_io, HRESULT* phres = NULL );
	long	WriteToFile( const MP_WPath* path, long size, HRESULT* phres = NULL );
	long	CopyToStgFileIO( ImplStgFileIO* dst_fileio, HRESULT* phres = NULL  );
	long	CopyRangeToStgFileIO( ImplStgFileIO* dst_fileio, long iStartPos, long iLength, HRESULT* phres = NULL  );

	HRESULT SetNoReadCache( MP_Integer bCareful );
		// MP_S_OKを指定すると、ReadCacheを使わない。
		// バイトサーブなどでファイル内容が変わることが正常系としてあり得るときに指定する。

private:
	MP_Integer	m_DeleteMPFileOnDestory;
	char*	m_ReadCache;
	long	m_ReadCachePtr;
	long	m_ReadCacheSize;
	char*	m_WriteCache;
	long	m_WriteCacheSize;

	MP_Integer m_bNoReadCache;
};

class ImplStgReadOnlyFileIO : public ImplStgFileIO
{
public:
	ImplStgReadOnlyFileIO( MP_File* mp_file, long Inital_offset, long size );
	~ImplStgReadOnlyFileIO();
	HRESULT	Destroy(void);
	long	GetSize(void);
	long	Seek( long offset );
	TAG_TYPE	ReadTag( HRESULT* phres = NULL );
	long	ReadLength( HRESULT* phres = NULL );
	long	ReadInteger( HRESULT* phres = NULL );
	long	Read( char* ptr, long size, HRESULT* phres = NULL );
	HRESULT	WriteToFile( const MP_WPath* path, long size, HRESULT* phres = NULL );

private:
	long	m_InitialOffset;
	long	m_Size;
};

class ImplStgReadOnlyDataIO
{
public:
	long	m_InitialOffset;
	ImplStgReadOnlyFileIO*	m_file;
	ImplStgMemIO*	m_mem;

	ImplStgReadOnlyDataIO( const MP_WPath* path );
	ImplStgReadOnlyDataIO( MP_File* mp_file, long Inital_offset, long size );
	ImplStgReadOnlyDataIO( void* data, long size );
	~ImplStgReadOnlyDataIO();
	HRESULT	Destroy(void);
	long	GetSize(void);
	long	Seek( long offset );
	TAG_TYPE	ReadTag( HRESULT* phres = NULL );
	long	ReadLength( HRESULT* phres = NULL );
	long	ReadInteger( HRESULT* phres = NULL );
	long	Read( char* ptr, long size, HRESULT* phres = NULL );
	HRESULT	WriteToFile( const MP_WPath* path, long size, HRESULT* phres = NULL );
};


#endif

//
//CHANGE LOG
//97.10.21 - Nagano - 作成
//97.10.28 - Nagano - ディスクフル・エラー処理を追加
//98.05.28 - Nagano - V3.1 SetSize(),CopyToStgFileIO()を追加
//98.06.09 - Nagano - AR2821: GetFilePath()の削除
//98.06.19 - Nagano - V3.1:MP_Fileのエラーコード関連仕様変更対応
//98.11.13 - Nagano - V4開発(AR2130):ファイルIOにキャッシュを追加
//1999.06.25 - Tashiro - V4開発: BD因数化の実装 ImplStrReadOnlyDataIOの新設
//----V5-----
//2002.04.16 - Tashiro - インクルード構成を変更(コンパイル効率の改善のため)
//2002.04.16 - Tashiro - CopyRangeToStgFileIO()追加(署名ロールバック用)
//---- 6.0開発
//2004.04.06 - Tashiro - V6.0 OM_MODEST_READ導入のためのエラー処理強化
//---- 6.0ENG
//2005.02.10 - Tashiro - AR12011 バイトサーブ等、ReadCacheを使わないモードを追加
