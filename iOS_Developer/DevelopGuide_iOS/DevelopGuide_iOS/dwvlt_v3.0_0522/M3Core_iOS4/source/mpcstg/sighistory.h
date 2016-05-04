// File: SigHistory.h
// Auther: Kiyoshi Tashiro
// Copyright(C) 2004 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_SIGHISTORY_H__
#define __STG_SIGHISTORY_H__

#include "mpc_api.h"

class ImplSignatureHistory : public MPCSignatureHistory
{
public:

	// MPCSignatureHisotry
	STDMETHOD(GetSignatureVersionSelf)(char* pszText = NULL);
	STDMETHOD(HasEditSave)();
	STDMETHOD(HasNextSignature)();
	STDMETHOD(GetSignatureVersionNext)(char* pszText = NULL);
	STDMETHOD(Destroy)();

	HRESULT SetThisSigVersion( MP_Integer iVerLen, char* pVerText );
	HRESULT SetNextSigVersion( MP_Integer iVerLen, char* pVerText );
	HRESULT SetHasNextSig( MP_Integer iHasNextSig );
	HRESULT SetHasNextEdit( MP_Integer iHasNextEdit );


private:
	friend class ImplSession;

	ImplSignatureHistory( HRESULT* phres );
	~ImplSignatureHistory();

	MP_Integer m_iThisVerTextLen;
	char* m_pszThisVerText;
	MP_Integer m_iNextVerTextLen;
	char* m_pszNextVerText;
	MP_Integer m_iHasNextSig;
	MP_Integer m_iHasNextEdit;
};


#endif //__STG_SIGHISTORY_H__

//
//CHANGE LOG
// 2004.7.27 - Tashiro - 作成
