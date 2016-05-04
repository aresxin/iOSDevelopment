// File: STGMEMIO.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_MEMIO_H__
#define __STG_MEMIO_H__

#include "stg.h"

class ImplStgMemIO {

public:
	char*	m_Data;
	long	m_Size;
	long	m_CurrentOffset;
	long	m_AllocaSize;
	long	m_InitialAllocaSize;
	MP_Integer	m_DeleteDataOnDestory;

	ImplStgMemIO( char* data, long size, MP_Integer delete_dat );
	~ImplStgMemIO();
	HRESULT	Destroy(void);
	HRESULT Clear(void);
	long	GetCurrentOffset(void);
    long	GetSize(void);
    long	Seek( long seek_pos, MP_SeekMethod = MP_SEEK_BEGIN );
	TAG_TYPE	ReadTag( long* rtn_read_size = NULL );
	TAG_TYPE	ReadTag( MP_Integer* is_private, long* rtn_read_size );
	long	ReadLength( long* rtn_read_size = NULL );
	long	ReadInteger( long* rtn_read_size = NULL );
	long	Read( void *buffer, long size, HRESULT* phres = NULL );
	long	WriteTag( TAG_TYPE tag );
	long	WriteTag( TAG_TYPE tag, MP_Integer is_private );
	long	WriteLength( long length );
	long	WriteInteger( long integer );
	long	Write( const void* buffer, long size, HRESULT* phres = NULL );
	long	WriteToFile( const MP_WPath* path, long size, HRESULT* phres = NULL );
	HRESULT	EnlargeSize( long size );
};

#endif

//
//CHANGE LOG
//97.10.21 - Nagano - 作成
//----V5-----
//2002.04.16 - Tashiro - インクルード構成を変更(コンパイル効率の改善のため)
//2002.04.16 - Tashiro - Seekにモード追加
//---- 6.0開発
//2004.04.06 - Tashiro - V6.0 OM_MODEST_READ導入のためのエラー処理強化
