// File: ATTRUTY.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.


#ifndef ATTRUTY_H
#define ATTRUTY_H

#include "mpc_spi.h"

class MPCAValue : public MP_AValue
{
public:
inline	MPCAValue() {
	m_allocbuf = NULL; adata = NULL; atype = 0; asize = 0; };

inline	~MPCAValue() {
	if (m_allocbuf) { delete [] (MP_Octet*)m_allocbuf; } };

inline	void Clear() {
	Free(); adata = NULL; atype = 0; asize = 0; };

inline	HRESULT Fetch(IStgObject* stgobj, const MP_AName* aname) {
		if ( !stgobj ) return MP_E_INVALIDARG;
		Free();
		stgobj->GetAttribute(aname, this);
		if ( asize <= 0 ) return MP_E_INVALIDARG;
		Alloc(asize);
		return stgobj->GetAttribute(aname, this);
	};

inline	HRESULT Store(IStgObject* stgobj, const MP_AName* aname) {
		if ( !stgobj ) return MP_E_INVALIDARG;
		return stgobj->SetAttribute(aname, this);
	};

inline	HRESULT Fetch(MPCObject* mpcobj, const MP_AName* aname) {
		if ( !mpcobj ) return MP_E_INVALIDARG;
		Free();
		mpcobj->GetAttribute(aname, this);
		if ( asize <= 0 ) return MP_E_INVALIDARG;
		Alloc(asize);
		return mpcobj->GetAttribute(aname, this);
	};

inline	HRESULT Store(MPCObject* mpcobj, const MP_AName* aname) {
		if ( !mpcobj ) return MP_E_INVALIDARG;
		return mpcobj->SetAttribute(aname, this);
	};

inline MP_Integer DataAsInt() { return (adata&&(atype==MP_A_INT)) ? *(MP_Integer*)adata : 0; };
inline MP_Pos DataAsPos() { return (adata&&(atype==MP_A_POS)) ? *(MP_Pos*)adata : MP_NULL_POS; };
inline MP_Dim DataAsDim() { return (adata&&(atype==MP_A_DIM)) ? *(MP_Dim*)adata : MP_NULL_DIM; };

inline	HRESULT operator= (MP_Integer idata) {
		HRESULT	hres;
		if ( (hres = Alloc(sizeof(MP_Integer))) == MP_NOERROR )
			*(MP_Integer*)adata = idata;
		atype = MP_A_INT;
		return hres;
	};

inline	HRESULT operator= (MP_Pos pos) {
		HRESULT	hres;
		if ( (hres = Alloc(sizeof(MP_Pos))) == MP_NOERROR )
			*(MP_Pos*)adata = pos;
		atype = MP_A_POS;
		return hres;
	};

inline	HRESULT operator= (MP_Dim dim) {
		HRESULT	hres;
		if ( (hres = Alloc(sizeof(MP_Dim))) == MP_NOERROR )
			*(MP_Dim*)adata = dim;
		atype = MP_A_DIM;
		return hres;
	};

inline	MP_Integer operator== (MP_Integer idata) {
		if ( (asize == sizeof(MP_Integer)) && (atype == MP_A_INT) && adata )
			if ( *(MP_Integer*)adata == idata )	return TRUE;
		return FALSE;
	};

protected:

inline	HRESULT Alloc(long size) {
		Free();
		asize = size;
		m_allocbuf = new MP_Octet[asize];
		if ( !m_allocbuf )	return MP_E_OUTOFMEMORY;
		adata = m_allocbuf;	
		return MP_NOERROR;
	};

inline	void Free() {
		if ( m_allocbuf ) delete [] (MP_Octet*)m_allocbuf;
		asize = 0;
		m_allocbuf = NULL;
		adata = NULL;
	};

	void* m_allocbuf;	//外部から非alloc領域を直接adataに代入される事を想定したFailSafe
};


/*
* MID配列の属性操作ユーティリティクラス
*/

class MPCAValMIDArray : public MPCAValue
{
public:
	MPCAValMIDArray() : MPCAValue() { } ;

	/*
	*	Encode : midarray に格納された MP_Integer配列をシリアライズして this の属性に格納する
	*/
	HRESULT	Encode(IMediaIDManager* midmgr, MP_PtrArray* midarray) {
		HRESULT hres;
		Free();
		midmgr->EncodeRefMID(this, midarray);
		if ( asize <= 0 ) return MP_E_INVALIDARG;
		if ( (hres = Alloc(asize)) != MP_NOERROR ) return hres;
		return midmgr->EncodeRefMID(this, midarray);
	};		

	/*
	*	Decode : this の属性に格納されたMP_Integer配列を、midarrayに展開する
	*/
	HRESULT	Decode(IMediaIDManager* midmgr, MP_PtrArray* midarray) {
		return midmgr->DecodeRefMID(this, midarray);
	};		
};

#endif //ATTRUTY_H

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.25 - Ichiriki - Size取得後にatypeクリアしないよう修正
//96.10.21 - Ichiriki - stg_spi.h -> mpc_spi.h, MPCAValMIDArrayマージ
