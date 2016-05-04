// File: STGATTMGR.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_ATTMGR_H__
#define __STG_ATTMGR_H__

#include "stg.h"

const long	INTO_BD_SIZE = 1024;	// INTO_BD_SIZE以上の属性はBDとして保存

class ImplStgAttManager {

public:
	ImplStgObj*		m_StgObj;
	MP_PtrArray*	m_NewAtt;	// 保存時より新しくセットされた属性の配列.ImplStgAttを格納.	
	char*			m_DelAtt;	// レコード内属性の削除フラグ.配列の並びはTRIDが示すレコード内の属性の並びに対応.
	long			m_TreeAttNum;
	long			m_OldNewAttNum;
	unsigned int	m_old_seed;

	ImplStgAttManager( ImplStgObj* stgobj );
	~ImplStgAttManager();
	HRESULT Destroy(void);
	HRESULT InitDelAtt( long tree_att_num = -1 );
	HRESULT GetCopy( ImplStgAttManager* att_mgn );
	HRESULT GetAttribute( const MP_AName* aname, MP_AValue* rtn_avalue, MP_Integer nth_element, MP_Integer do_decompress, MP_Integer do_dectype, ATTR_ID aid = INVALID_AID );
	HRESULT GetAttributeF( const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element );
	long GetAttributeSize( ATTR_ID aid );
	STDMETHODIMP SetAttribute( const MP_AName* aname, const MP_AValue* avalue, MP_Integer nth_element, MP_Integer do_assign, MP_Integer do_compress, MP_Integer do_encrypt, MP_Integer reusable, ATTR_ID aid = INVALID_AID  );
	STDMETHODIMP SetAttributeF( const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element, MP_Integer do_assign, MP_Integer reusable );
	ATTR_ID SetAid( const MP_AName* aname, MP_AType atype, MP_Integer nth_element, MP_Integer do_assign, HRESULT *phres );
	HRESULT SetNewAtt( ImplStgAtt* new_att );
	HRESULT SetAvalue( const MP_AName* aname, ATTR_ID aid, const MP_AValue* avalue, ImplStgAtt* rtn_att, MP_Integer do_compress, MP_Integer do_encrypt, MP_Integer reusable );
	MP_Integer AskAvalueToTempBDMgr( long avalue_size, MP_Integer do_compress );
	STDMETHODIMP DelAttribute( const MP_AName* aname, MP_Integer nth_element, MP_Integer do_assign, ATTR_ID aid = INVALID_AID );
	ATTR_ID EnumAID( ATTR_ID aid );
	HRESULT SeparateFromFile( MP_Integer remove_file_flag, MP_Integer do_decrypt );
	HRESULT CompleteSeparateFromFile(void);
	HRESULT UndoSeparateFromFile(void);
#ifndef SFXVW
	HRESULT GetNewBDArray( ImplStgWriteData* write_data );
	long EncodeAttribute( ImplStgWriteData* write_data, ImplStgMemIO* encode_att, HRESULT* phres );
#endif //SFXVW
	
	// in attrid.cpp
	ATTR_ID ANameToAid( const MP_AName* aname, MP_Integer* p_atype, MP_Integer nth_element, long do_assign, MP_Integer* rtn_nth = NULL );
	HRESULT AidToAName( ATTR_ID aid, MP_AName* aname, MP_Integer namesize, MP_Integer* rtn_nth_element = NULL );
	HRESULT DeleteUserDefinedAName( const MP_AName* aname, MP_Integer nth_element );
	HRESULT NextExtendAName( MP_AName* aname, MP_Integer namesize, MP_Integer* rtn_nth_element, long is1st);
	STDMETHODIMP EnumAttribute( MP_AName* aname, MP_Integer namesize );

	//v4
#ifndef SFXVW
	HRESULT CheckBD( MPC_AdvCancelInfo* info );
#endif //SFXVW
};

class ImplStgAtt {

public:
	ATTR_ID	m_AID;
	MP_AName*	m_AName;
	MP_AType	m_AType;
    void*	m_AData;
    long	m_Size;			// 属性値のバイト数.圧縮状態の場合は,解凍後に必要なバイト数
    long	m_Compress;		// 0:圧縮なし. 正数:圧縮属性,値は圧縮後バイト数. -1:呼び出し側で「圧縮しない」指定された属性.
	BDID	m_BDID;			// -1(INVALID_BDID):ID未発行,m_dataに格納されている.
	unsigned long	m_CheckSum;

	//v4
	long m_EncryptedSize;	//暗号化後のバイト数
	MP_Octet* m_Hash;	//暗号化前のハッシュ値
	UINT64	m_InitVector;	//暗号化時の初期ベクトル

	ImplStgAtt(void);
	~ImplStgAtt();
	HRESULT Destroy(void);
	HRESULT SetAName( const char* src_name );
	HRESULT SetAData( const void* src_data, unsigned long size );
};

#endif

//
//CHANGE LOG
//97.10.21 - Nagano - 作成
//97.10.28 - Nagano - ディスクフル・エラー処理を追加
//97.10.30 - Nagano - SetAttribute(F)の失敗で以前にセットされた属性を削除するバグを修正
//97.11.06 - Nagano - Checksum導入による変更
//97.12.19 - Nagano - AR2026:SeparateFromFile()にremove_file_flagを追加
//---- お試し版990531リリース
//1999.06.09 - Tashiro - V4開発: BDの暗号化/復号の実装
//1999.06.09 - Tashiro - V4開発: BD(保護あり/なし)のデータチェック機能実装
//1999.06.10 - Tashiro - V4開発: データチェックのコールバック実装
//1999.06.25 - Tashiro - V4開発: BD因数化の実装
//1999.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//1999.09.06 - Tashiro - V4 AR4745 自己解凍文書用ビューワサイズ削減 追加
//----V5-----
//2002.04.16 - Tashiro - インクルード構成を変更(コンパイル効率の改善のため)
//----- マルチスレッド対応
//2006.05.26 - Kudo - マルチスレッド対応：乱数のseedをメンバとして保持
