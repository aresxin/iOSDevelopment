// File: SESSION.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_SESSION_H__
#define __STG_SESSION_H__

#include "mpc_spi.h"
#include "stg.h"

class CMediaLoader;
class ImplSessionForDLL;
class ImplSPISession;
class ImplFormatAttribute;
class ImplMediaIDManager;
class ImplSPI_MP_File;
class ImplSessionForDLL;
class ImplFormatAttribute;
class ImplCompressedMPAttribute;
class ImplSpecialAttribute;
class ImplBigAlloc;
class ImplMPCSFXOperations;
class ImplSignatureHistory;

mpinterface MP_PtrArray;
mpinterface MP_Children;
mpinterface MPCTextAttributeHelper;

MP_PtrArray* ImplPtrArray_Create(MPCSession* session, HRESULT* phres) ;
MP_Children* ImplMPChildren_Create(MPCSession* session, MPCObject* mpcobj, IStgObject* stgobj, MP_Integer part_objtype, IStgObject* midkeeper, HRESULT* phres, MP_Integer is_cdoc_root) ;

MPCObject* LoaderCreateMPCObject(MPCSession* session, MP_RefObjectType clsid, HRESULT* phres);
CMediaLoader* CreateMediaLoader(HRESULT* phres);
void MediaLoader_Destroy(CMediaLoader* ldr);

class ImplSession : public MPCSession
{

public:
	CMediaLoader* m_MediaLoader;
	void*	m_hInstance;
	ImplSPISession* m_spisession;
	ImplSessionForDLL* m_spi4dll;
	ImplFormatAttribute* m_iformat_attr;
	ImplMediaIDManager* m_midmgr;
	MPCInterface* m_bindpd3;	
	MPCInterface* m_bindcanvas;	
	//v4 security
	MPCInterface* m_SecuSPI_Pswd;
	MPCInterface* m_SecuSPI_DDSA;
	MPCInterface* m_SecuSelector;
	//
	MPCInterface* m_autorotate;
	// V4.1 プロセスモデル用
	MPCInterface* m_pmodel;
	// V5
	MPCInterface* m_signature; // 電子署名
	MPCInterface* m_SecuSPI_Pswd128;
	MPCInterface* m_SecuSPI_Pkst;
	MPCInterface* m_SecuSPI_SDES;
	MP_Integer m_SaveSignatureMode; //保存時にツリーに渡すためのモード
	// V6
	MPCInterface* m_bindts;	// テキスト検索
	MPCInterface* m_pOpenSecuSPIs[MP_S_OPEN_SECURITY_NUM];
	// V7
	MPCTextAttributeHelper* m_textAttributeHelper; // テキスト属性アクセス

	ImplSPI_MP_File* m_spimpfile;	
	MPCInterface* m_bindmpclt;
	ImplCompressedMPAttribute*	m_icompressedattr;
	ImplSpecialAttribute* m_ispecialattr;
	ImplBigAlloc*	m_bigalloc;
	ImplMPCSFXOperations*	m_mpcsfxope;
	ImplStgTempBDMgr*	m_TempFile;
	ImplStgTree*	m_TreeForScratch;
	MP_PtrArray*	m_TreeArray;	// 生成ツリーを保存

	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres=NULL) ;
	STDMETHOD(Destroy)() ;
	STDMETHOD_(MPCObject*, CreateScratchMPCObject)(const MP_ObjectType clsid, HRESULT* phres) ;
	STDMETHOD_(MPCObject*, OpenFile)(const MP_Path* path, HRESULT* phres, MP_AccessMode access=MP_UPDATE ) ;
	STDMETHOD(CloseFile)(MPCObject* obj,MP_Integer commit=TRUE) ;
	STDMETHOD(Save)(MPCObject* obj) ;
	STDMETHOD(SaveAs)(MPCObject* obj, const MP_Path* path) ;
	STDMETHOD(DELETED_Reload)(MPCObject* obj, const MP_Path* path=NULL);
	STDMETHOD(IsDirty)(MPCObject* obj);
	STDMETHOD(ForceReleaseResource)();
	STDMETHOD_(MPCObject*, CreateFileMPCObject)(MP_File* mpfile, MP_Integer delete_mpfile, HRESULT* phres=NULL);
	STDMETHOD(SaveToPath)(MPCObject* obj, const MP_Path* path, MP_Integer withobj, MP_Integer overwrite);
	STDMETHOD(SaveToFileObject)(MPCObject* obj, const MP_File* mpfile, MP_Integer withobj);

	// V5
	STDMETHOD(SaveWithSignature)(MPCObject* pRootObj, MPCObject* pSignatureObj, const MP_Path* path, MP_Integer withobj, MP_Integer overwrite);
	STDMETHOD(SaveWithCompactionMode)(MPCObject* obj, MP_SaveCompactionMode iCompactionMode);
	STDMETHOD(RollbackToPath)(MPCObject* obj, const MP_Path* path, MP_Integer iBeforeSignature );

	STDMETHOD(CanSaveWithSignature)(MPCObject* pRootObj);

	STDMETHOD_(MPCSignatureHistory*, CreateSignatureHistory)( MPCObject* obj, HRESULT* phres = NULL );

	STDMETHOD_(MPCObject*, OpenFileFromHandle)(const MP_Path* path, void* hFileHandle, HRESULT* phres, MP_AccessMode access=MP_UPDATE ) ;

	ImplSession( CMediaLoader* ldr, void* hIns, HRESULT* phres = NULL );
	~ImplSession();
	MPCObject* CreateMPCObject( MP_File* mp_file, MP_Integer delete_mp_file, const MP_WPath* filepath, HRESULT* phres=NULL );
	HRESULT CheckFilePath( const MP_WPath* path );
	HRESULT CheckFilePathForOpen( const MP_WPath* path );
	MP_File* CreateLockFile( const MP_WPath* path, HRESULT* phres );
	MP_File* CreateReserveFile( const MP_WPath* path, HRESULT* phres );

	// V7 Unicode I/F
	STDMETHOD_(MPCObject*, OpenFileW)(const MP_WPath* path, HRESULT* phres, MP_AccessMode access=MP_UPDATE ) ;
	STDMETHOD(SaveAsW)(MPCObject* obj, const MP_WPath* path) ;
	STDMETHOD(SaveToPathW)(MPCObject* obj, const MP_WPath* path, MP_Integer withobj, MP_Integer overwrite);
	STDMETHOD(SaveWithSignatureW)(MPCObject* pRootObj, MPCObject* pSignatureObj, const MP_WPath* path, MP_Integer withobj, MP_Integer overwrite);
	STDMETHOD(RollbackToPathW)(MPCObject* obj, const MP_WPath* path, MP_Integer iBeforeSignature );
	STDMETHOD_(MPCObject*, OpenFileFromHandleW)(const MP_WPath* path, void* hFileHandle, HRESULT* phres, MP_AccessMode access=MP_UPDATE ) ;

private:
	HRESULT CheckFilePathAux( const MP_WPath* path, int iMaxPathLen );
	HRESULT SaveInclemantalToPath( MPCObject* mpcobj, const MP_WPath* path, MP_Integer withobj, MP_Integer overwrite );
	HRESULT SaveInclemantalToFileObject( MPCObject* mpcobj, const MP_File* mp_file, MP_Integer withobj );
	HRESULT SaveWithSignatureInternal(MPCObject* pRootObj, MPCObject* pSignatureObj, const MP_WPath* path, MP_Integer withobj, MP_Integer overwrite, MP_File** ppLockFile, MP_File** ppReserveFile);

	HRESULT GetSignaturePositionInDoc( MPCObject* mpcobj );
	HRESULT GetSignatureVersion( MPCObject* mpcobj, char* pText );
	HRESULT GetSignatureVersion( ImplStgObj* stgobj, char* pText );
	HRESULT SetThisSigVerToHistory( MPCObject* mpcobj, ImplSignatureHistory* pHistory );
	HRESULT SetHasNextSigToHistory( MPCObject* mpcobj, ImplSignatureHistory* pHistory );
	HRESULT SetHasNextEditToHistory( MPCObject* mpcobj, ImplSignatureHistory* pHistory );
	ImplStgObj* GetNextSigStgObj( MPCObject* mpcobj, HRESULT *phres = NULL );
	HRESULT GetSigNumInDoc( MPCObject* mpcobj );
	HRESULT SetNextSigVerToHistory( MPCObject* mpcobj, ImplSignatureHistory* pHistory );
	ImplStgObj* GetNthSigStgObj( MPCObject* mpcobj, MP_Integer nth, HRESULT* phres );

	MPCInterface* GetSPIBindPD3() {
		if ( !m_bindpd3) m_bindpd3 = (MPCInterface*)::LoaderCreateMPCObject(this, 2, NULL);
		return m_bindpd3;
	};
	MPCInterface* GetSPIBindCanvas() {
		if ( !m_bindcanvas) m_bindcanvas = (MPCInterface*)::LoaderCreateMPCObject(this, 3, NULL);
		return m_bindcanvas;
	};

	MPCInterface* GetSPIBindMPCLT() {
		if ( !m_bindmpclt) m_bindmpclt = (MPCInterface*)::LoaderCreateMPCObject(this, 4, NULL);
		return m_bindmpclt;
	};

	MPCInterface* GetSPISecuPswd() {
		if ( !m_SecuSPI_Pswd) m_SecuSPI_Pswd = (MPCInterface*)::LoaderCreateMPCObject(this, 5, NULL);
		return m_SecuSPI_Pswd;
	};

	MPCInterface* GetSPISecuDDSA() {
		if ( !m_SecuSPI_DDSA) m_SecuSPI_DDSA = (MPCInterface*)::LoaderCreateMPCObject(this, 6, NULL);
		return m_SecuSPI_DDSA;
	};

	MPCInterface* GetSPISecuSelector() {
		if ( !m_SecuSelector) m_SecuSelector = (MPCInterface*)::LoaderCreateMPCObject(this, 7, NULL);
		return m_SecuSelector;
	};
	MPCInterface* GetAutoRotate() {
		if ( !m_autorotate) m_autorotate = (MPCInterface*)::LoaderCreateMPCObject(this, 9, NULL);
		return m_autorotate;
	};
	// V4.1
	MPCInterface* GetPModel() {
		if ( !m_pmodel) m_pmodel = (MPCInterface*)::LoaderCreateMPCObject(this, 10, NULL);
		return m_pmodel;
	};

	// V5
	MPCInterface* GetSignature() {
		if ( !m_signature) m_signature = (MPCInterface*)::LoaderCreateMPCObject(this, 11, NULL); // 仮
		return m_signature;
	};
	MPCInterface* GetSPISecuPswd128() {
		if ( !m_SecuSPI_Pswd128) m_SecuSPI_Pswd128 = (MPCInterface*)::LoaderCreateMPCObject(this, 11, NULL);
		return m_SecuSPI_Pswd128;
	};
	MPCInterface* GetSPISecuPkst() {
		if ( !m_SecuSPI_Pkst) m_SecuSPI_Pkst = (MPCInterface*)::LoaderCreateMPCObject(this, 12, NULL);
		return m_SecuSPI_Pkst;
	};
	MPCInterface* GetSPISecuSDES() {
		if ( !m_SecuSPI_SDES) m_SecuSPI_SDES = (MPCInterface*)::LoaderCreateMPCObject(this, 13, NULL);
		return m_SecuSPI_SDES;
	};

	// V6
	MPCInterface* GetSPIBindTextSearch() {
		if ( !m_bindts ) m_bindts = (MPCInterface*)::LoaderCreateMPCObject(this, 14, NULL);
		return m_bindts;
	}

	MP_Integer BackUpOrgFileIfToBeDeleted( ImplStgTree* tree, mpcwcstring& backpath, HRESULT* phres );

	void DestroyAllFile();

	HRESULT HasOrphanSignature( MPCObject* pRootObj );

	MPCObject* OpenFileImpl( const MP_WPath* path, void* hFileHandle, HRESULT* phres, MP_AccessMode access );

};

ImplSessionForDLL* ImplSessionForDLL_Create(ImplSession* session);
void ImplSessionForDLL_Destroy(ImplSessionForDLL* ptr);

ImplSPISession* ImplSPISession_Create(ImplSession* session);
void ImplSPISession_Destroy(ImplSPISession* ptr);

ImplFormatAttribute*  ImplFormatAttribute_Create(ImplSession* session);
void ImplFormatAttribute_Destroy(ImplFormatAttribute* fmtattr);

ImplMediaIDManager*	ImplMediaIDManager_Create();
void ImplMediaIDManager_Destroy(ImplMediaIDManager* ifobj);

ImplSPI_MP_File* ImplSPI_MP_File_Create(ImplSession* session);
void ImplSPI_MP_File_Destroy(ImplSPI_MP_File* ifobj);

ImplCompressedMPAttribute* ImplCompressedMPAttribute_Create(ImplSession* session);
void ImplCompressedMPAttribute_Destroy(ImplCompressedMPAttribute* obj);

ImplSpecialAttribute* ImplSpecialAttribute_Create(ImplSession* session);
void ImplSpecialAttribute_Destroy(ImplSpecialAttribute* obj);

ImplBigAlloc* ImplBigAlloc_Create(ImplSession* session);
void ImplBigAlloc_Destroy(ImplBigAlloc* obj);

ImplMPCSFXOperations* ImplMPCSFXOperations_Create( ImplSession* session );
void ImplMPCSFXOperations_Destroy( ImplMPCSFXOperations* obj );

MPCTextAttributeHelper* MPCTextAttributeHelper_Create();
void MPCTextAttributeHelper_Destroy(MPCTextAttributeHelper* obj);

#endif

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//97.10.21 - Nagano - V3.0用変更
//97.12.16 - Nagano - AR1843:ImplMPCSFXOperationsを追加
//98.5.28 - Nagano - V3.1:CreateMPCObject()を追加.CreateFileMPCObject()対応.
//98.6.9 - Nagano - AR2821:CreateMPCObject()の引数にファイルパスを追加
//98.6.9 - Nagano - V3.1:SaveToPath(), SaveToFileObject()追加
//---- お試し版990531リリース
//1999.06.14 - Tashiro - V4開発: ISpecialAttribute(文字認識結果取得用I/F)を追加
//1999.06.27 - Tashiro - V4開発: BD因数化の実装 m_TempFileのクラス名変更
//1999.06.29 - Ichiriki - AutoRotateインタフェースの追加
//1999.06.29 - Ichiriki - セキュリティセレクタの番号を7に修正
//2000.09.26 - Nakazawa - V4.1 プロセスモデルSPIの実装追加
//---- V5
//2002.02.23 - Tashiro - MPCSignature追加、MPCSession拡張の仮実装
//2002.02.28 - Tashiro - 署名関連操作の修正
//2002.04.16 - Tashiro - インクルード構成を変更(コンパイル効率の改善のため)
//2002.04.19 - Tashiro - 署名検証動作の実装
//2002.05.18 - Tashiro - 署名文書の別名保存時に追記保存相当の動作をする
//2002.05.18 - Tashiro - AR7352 署名ロールバック機能の実装
//2002.05.21 - Tashiro - AR7397 署名があってもスクラッチなら追記保存はしない
//2002.06.10 - Tashiro - AR7436 ファイルオブジェクトに対するSaveIncrementalを実装
//2002.11.12 - Tashiro - 5.0.2 AR6978対応 開くときはパス長を259バイトまで許すように修正
//2004.03.26 - Tashiro - 5.0.6 AR9149追加対策 予約ファイル作成メソッド、署名保存動作を後処理のためにラップ
//---- V6
//2004.03.30 - Komoda  - 6.0 テキスト検索SPIを追加
//2004.07.29 - Tashiro - AR10326 署名履歴表示機能の追加
//2006.01.16 - Tashiro - AR12665 署名可能か確認するメソッド追加
//---- V6.2
//2006.07.20 - Tashiro - セキュリティ追加対応
//2006.07.20 - Tashiro - DE向けファイルオープン機能追加
//---- V7
//2007.12.04 - Komoda  - 7.0 テキスト属性ヘルパ用関数を追加
