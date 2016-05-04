// File: readOnlyDataImpl.h
// Auther: Kiyoshi Tashiro
// Copyright(C) 2000 by Fuji Xerox Co,. Ltd. All right reserved.

// CReadOnlyDataFile と CReadOnlyDataMem を定義する。
// これらは CReadOnlyData の派生クラス
// CReadOnlyData は ACCESがファイルまたはメモリ上のデータを読むためのクラス


#ifndef _READONLYDATAIMPL_H_
#define _READONLYDATAIMPL_H_

#include "mpc_api.h"
#include "readonlydata.h"

class CReadOnlyDataFile : public CReadOnlyData
{
public:
	CReadOnlyDataFile( MP_File* pMpFile );
	~CReadOnlyDataFile();
    long Seek(const long seek_pos);
    long Read(void * buff, const long size);
private:
	MP_File* m_pMpFile;
};


class CReadOnlyDataMem : public CReadOnlyData
{
private:
	//07.09.13 - M.Chikyu UNICODE対応
	// 代入演算子は使用しない
	const CReadOnlyDataMem& operator=(const CReadOnlyDataMem&) {return *this;};

public:
	CReadOnlyDataMem( const MP_Integer iSize, const MP_Octet* pOctet );
	~CReadOnlyDataMem();
    long Seek(const long seek_pos);
    long Read(void * buff, const long size);
private:
	const MP_Octet* m_pOctet;
	const MP_Integer m_iSize;
	MP_Integer m_iPos; // シーク位置
};


#endif // #ifndef _READONLYDATAIMPL_H_

//
//CHANGE LOG
//2000.9.29 - Tashiro - 作成
