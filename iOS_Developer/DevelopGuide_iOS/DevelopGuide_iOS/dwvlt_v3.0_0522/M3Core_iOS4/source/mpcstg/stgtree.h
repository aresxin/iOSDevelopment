// File: STGTREE.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_TREE_H__
#define __STG_TREE_H__

#include "okd_pub.h"
#include "stg.h"
#include "../mpcinc/mpc_secu.h"

const MP_Integer TREE_IMAGE_SIZE = 1024*64;	// 64Kbyte
const MP_Integer INCREMENTAL_SAVE_MODE = 0;
const MP_Integer COMPACTION_SAVE_MODE = 1;

const MP_Integer SIG_SAVE_MODE_NONE = 0;
const MP_Integer SIG_SAVE_MODE_BEFORE = 1;
const MP_Integer SIG_SAVE_MODE_AFTER = 2;

#define NO_SECU_PERM (MP_PERM_FULL | MP_PERM_DOC_EDIT | MP_PERM_ANNO_EDIT | MP_PERM_PRINT | MP_PERM_COPY)

class MPC_FileMap;
class CSimpleMutex;

class ImplStgTree {

public:
	ImplSession*	m_Session;	//自分が属しているセッション
	MP_OKDEncodePublic*	m_OKDEncode;
	MP_OKDDecodePublic*	m_OKDDecode;
	ImplStgFileIO*	m_File;	//自分が開かれたファイル
	mpcwcstring	m_FilePath;	//自分が開かれたファイルのパス
	ImplStgObj*	m_RootStgObj;
	MPCObject*	m_RootMpcObj;
	ImplStgMemIO*	m_FileTree;	//ファイルから読み込んだツリーイメージ
	long	m_FileFormatVersion;
	OBJECT_TYPE	m_FileRootStgObjType;	//ファイルから得たルートオブジェクトのクラス
	long	m_FileBDNum;	//ファイルにあったバルクデータの数
	long*	m_FileBDOffset;	//各バルクデータのファイル中での位置
	long	m_FileDeletedLen;	//ファイル内で無効になっているバイト数
	long	m_FileOriginalTreeSize;	//圧縮前のツリーイメージのバイト数
	long	m_FileTreeSize;	//圧縮後のツリーイメージのバイト数
	unsigned long	m_FileTreeCheckSum;	//圧縮後のツリーイメージのハッシュ(XOR)
	long	m_FileTreeOffset;	//ファイル中でのツリーイメージの位置
	long	m_FileTrailerSize;	//ファイル中のトレーラのバイト数
	long	m_CurrentFileBDNum;	//ファイル内で有効なバルクデータの数
	long	m_CurrentFileDeletedLen;	//ファイル内で有効なバルクデータのバイト数
	long	m_OldCurrentFileDeletedLen;	//Save時の退避用
	long	m_OldCurrentFileBDNum;

	MP_Integer	m_DefectFound;	//データチェック機能、通常アクセスで異常が見つかっているか

	//V4 因数化
	long	m_FileReusableBDNum;	//オープン時の因数化可能BDの数
	long	*m_FileReusableBDInfo;	//オープン時の因数化可能BD情報(BDID＋チェックサム)

	//V4 Security
	MPCSecuritySPI*	m_SecuritySPI;	//ロードしているセキュリティモジュール
	MPS_SecurityObj*	m_SecurityHandle;	//セキュリティオブジェクト
	long	m_SecurityID;
		//セキュリティモジュールのID 0 / MP_S_PROTECTED_BY_PSWD / MP_S_PROTECTED_BY_DDSA
	MPS_SecurityInfo	m_SecurityInfo;	//セキュリティモジュールへ渡す可変長バイト列
	long	m_FileTreeEncryptedSize;	//Treeの暗号化後の長さ(バイト)
	MP_Octet*	m_FileTreeHash;	//暗号化されたTreeのハッシュ値
	MP_Octet*	m_FileTrailerMAC;	//Trailerの改ざんチェック用のMAC値
	MP_Integer	m_OpenMode;	//文書が(認証されて)開かれているか
	UINT64	m_SessionKey;	//セッション鍵
	MP_Permission	m_AuthenticatedPerm;	//認証されている権利
	char m_SecurityLabel[MPS_SECURITYLABEL_SIZE];	//セキュリティモジュールの種別をあらわす文字列
	MP_AuthMode	m_AuthMode; //OpenMP時に対話認証だったか否か

	// V5 128bit暗号対応
	MPCCryptKey m_ReadDataKeyEx;	// ファイルを読むときのデータ鍵(V5以降)
	MPCCryptKey m_WriteDataKeyEx;	// ファイルを書くときのデータ鍵(V5以降)
	MP_Integer m_FileTrailerMACLen;	// Trailerの改ざんチェック用のMAC値の長さ

	//V5 Signature
	MP_Integer m_SignatureNum; //文書に既に付けられている署名の数
	MP_Integer m_SignatureDataLen; //トレーラ内の署名モジュール固有データのサイズ
	long m_SignatureDataOffset; //トレーラ内の署名モジュール固有データの開始位置
	MP_Octet* m_SignatureData; //トレーラ内の署名モジュール固有データ
	long m_LastRollBackSize; //署名直前/直後の文書のファイルサイズ
	MP_Integer m_SaveSignatureMode; //保存時の署名無し/署名直前/署名直後
	long m_FileSize; //開いたファイルのサイズ
	int m_iRollbackTarget; // 開いた文書がロールバック先(＝署名して保存した直後)のときは0以外
	MPC_FileMap* m_pFileMap;
	mpcwcstring m_FileMapPath;
	void* m_pFileCopyImage;
	long m_iLastDocType;

	unsigned int m_old_seed;	// マルチスレッド対応

	ImplStgTree( ImplSession* session );
	~ImplStgTree();
	HRESULT Destroy(void);
	ImplStgObj* OpenFile( MP_File* mp_file, MP_Integer delete_mp_file, const MP_WPath* filepath, HRESULT* phres );
	HRESULT ReadHeader(void);
	HRESULT ReadTree(void);
	HRESULT ReadTrailer(void);
	HRESULT DestroyAllStgObj( ImplStgObj* stgobj );
	HRESULT Save(MP_Integer iCompactionMode = MP_SAVE_COMPACTION_AUTO);
	HRESULT SaveAs( ImplStgFileIO* mp_file, MP_Integer renew_obj );
	HRESULT SaveAsIncremental( ImplStgFileIO* save_file, MP_Integer renew_obj );
	HRESULT SaveIncremental( ImplStgWriteData* write_data );
	HRESULT SaveIncrementalToFile( ImplStgWriteData* write_data, ImplStgFileIO* save_file, MP_Integer renew_obj );
	HRESULT SaveCompaction( ImplStgWriteData* wite_data, ImplStgFileIO* save_file, MP_Integer renew_obj );
	ImplStgReadOnlyDataIO* GetBDStgDataIO( BDID bdid, HRESULT* phres = NULL );
	HRESULT SetAttributeToTempBDMgr( const MP_AName* aname, ATTR_ID aid, const MP_AValue* avalue, ImplStgAtt* rtn_att, MP_Integer do_compress, MP_Integer do_encrypt, MP_Integer reusable );
	HRESULT SetAttributeFToTempBDMgr( const MP_AName* aname, ATTR_ID aid, MP_AType atype, const MP_WPath* path, ImplStgAtt* rtn_att, MP_Integer reusable );
	TRID GetNextChildTRID( TRID& crr_trid, long& my_level, OBJECT_TYPE& rtn_assortment );
	long GetAttributeOffset( TRID trid, long& rtn_att_size );
	long GetNumberOfAttributes( TRID trid );
	long GetAttributeSize( TRID trid, ATTR_ID aid, long& index, char* delete_flag );
	long GetAtt( TRID trid, TAG_TYPE aid, ImplStgAtt* rtn_att );
	HRESULT GetAtt( long offset, ImplStgAtt* rtn_att );
	HRESULT GetAttribute( TRID trid, TAG_TYPE aid, MP_AValue* rtn_avalue, MP_Integer do_decompress, MP_Integer do_decrypt, char* delete_flag );
	HRESULT GetBDAttribute( ImplStgAtt* att, MP_AValue* rtn_avalue, MP_Integer do_decompress, MP_Integer do_decrypt );
	HRESULT GetAttributeF( TRID trid, TAG_TYPE aid, const MP_WPath* path, char* delete_flag );
	HRESULT GetBDAttributeF( ImplStgAtt* att, const MP_WPath* path );
	HRESULT DelAttribute( TRID trid, ATTR_ID aid, char* delete_flag );
	ATTR_ID EnumAID( TRID trid, ATTR_ID aid, char* m_DelAtt );
	HRESULT InitSeparateFromFile(void);
	HRESULT UndoSeparateFromFile(void);
	HRESULT SeparateAttributeFromFile( TRID trid, MP_PtrArray* new_att, char* delete_flag, MP_Integer remove_file_flag, MP_Integer do_decrypt );
#ifndef SFXVW
	long EncodeAttribute( TRID trid, ImplStgWriteData* write_data, ImplStgMemIO* encode_att, char* delete_flag, HRESULT* phres );
	//v4
	HRESULT CheckValidTreeBD( TRID trid, ImplStgWriteData* write_data, char* delete_flag );
	HRESULT CheckBD( TRID trid, char* delete_flag, MPC_AdvCancelInfo* info );
#endif //SFXVW
	HRESULT IsReusableBD( BDID bdid );
#ifndef SFXVW
	BDID SearchSameBD( ImplStgReadOnlyDataIO* bd_io, HRESULT* phres );
#endif //SFXVW
	HRESULT GetAttFromBDID( BDID bdid, ImplStgAtt* rtn_att );
	HRESULT GetSecuSPIIfNecessary();
	HRESULT ChangeWriteDataKey();

	// V4 Security
    // セキュリティ対応 12/03/02 Bito
    // セキュリティ認証に必要なデータを引数に追加
    STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL, void* authdata = NULL);
	//STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL);
	STDMETHOD(AddAuthentication)(MP_Permission perm);
	STDMETHOD(AddAuthenticationEx)(MP_AuthInfo* auth);
	STDMETHOD(EditSecurity)( ImplStgObj* stgobj, MPC_SecurityTemplate* pTemplate = NULL );
	STDMETHOD_(MP_Permission, GetPermission)(HRESULT* hres = NULL);
	STDMETHOD_(MP_Permission, GetAuthenticatedPermission)(HRESULT* hres = NULL);
	STDMETHOD(ShowSecurityInfo)();
#ifndef SFXVW
	STDMETHOD(CheckData)(MP_Integer* nth_page, MP_Integer* nth_org, MP_Integer* others, MPC_AdvCancelInfo* info = NULL);
#endif //SFXVW
	STDMETHOD(OnBeginPrint)(MP_Canvas* pCanvas, MPCObject* pBasicPage);
	STDMETHOD(OnEndPrint)(MP_Canvas* pCanvas, MPCObject* pBasicPage);

	STDMETHOD(ReleaseSecurity)( ImplStgObj* stgobj );

	// V5 Signature
	HRESULT DestroyDocImage();
#ifndef SFXVW
	STDMETHOD(GetSaveStorageVersion)();
	// AR9607対策のため引数を変更
	STDMETHOD(Rollback)(MP_File* mp_file, MP_Integer iNthSignature, MP_Integer iBeforeSignature );

	HRESULT ChangeOpenedFile(const MP_WPath* path, MP_Integer bDontCopy = 0);
	HRESULT ChangeOpenedFileObject(const MP_File* mpfile);
	MP_VerificationCondition MakeVerificationCondition( void* pDocImage, long iPrevDocEnd );
	MP_VerificationCondition MakeVerificationConditionFull( int iSigOrder, HRESULT *phres = NULL );
	HRESULT WriteVerificationData( void* pData );
	void* CreateDocImage( MP_WPath* pszTempPath = NULL );

	void* CreateRollbackedDocImage( MP_WPath* pszTempPath, MP_Integer iSigOrder, MP_Integer iBeforeSignature );
	HRESULT CopyDocAfter( const MP_WPath* path );

	long ReadLastDocType( long iPrevDocEnd );

	class CBackUp
	{
	public:
		CBackUp( ImplStgTree* pTree, HRESULT* phres = NULL );
		~CBackUp();
		HRESULT SaveStgInfo( ImplStgObj* pStgObj );
		HRESULT RestoreStgInfo( ImplStgObj* pStgObj );
		HRESULT RestoreTree( ImplStgTree* pTree );
		HRESULT IsBackedUp( ImplStgObj* pStgObj );
	private:
		ImplStgTree* m_pTree;
		TRID* m_pTRID;
		unsigned long int m_iSizeTRID;
		MP_PtrArray* m_pArrayStgObj;
		MP_PtrArray* m_pArrayAttMgn;

		long	m_FileFormatVersion;
		long	m_FileBDNum;
		long	m_FileOriginalTreeSize;
		long	m_FileTreeSize;
		unsigned long	m_FileTreeCheckSum;
		long	m_FileTrailerSize;
		long	m_FileDeletedLen;
		long	m_CurrentFileBDNum;
		long	m_CurrentFileDeletedLen;
		ImplStgMemIO*	m_FileTree;
		long*	m_FileBDOffset;
		long	*m_FileReusableBDInfo;
		long	m_FileReusableBDNum;
		long m_SignatureDataOffset;
		int m_iRollbackTarget;
		ImplStgFileIO*	m_File;
		long m_FileSize;
		long m_LastRollBackSize;
		MPCCryptKey m_ReadDataKeyEx;


	};
	CBackUp* m_pBackUp;

	HRESULT CreateBackUp();
	HRESULT ClearBackUp();
	HRESULT RestoreFromBackUp();
#endif //SFXVW

	//V6
	HRESULT GetTrailerAttribute(unsigned long iTag, MP_AValue* rtn_avalue=NULL);
	HRESULT HasTMBAttribute();
	HRESULT HasEditAfterNthSignature( int iSigOrder );

	//V62
	STDMETHOD(GetSecurityModuleData)(char* pModuleData);

private:
	inline void SetResult( HRESULT* phRes, HRESULT hRes ) {
		if ( phRes != NULL ) *phRes = hRes;
	};
	HRESULT ReadTrailerOnMem(ImplStgMemIO* trailer);
	HRESULT ReadHeaderOnMem6Later(ImplStgMemIO* header);
	HRESULT ReadHeaderOnMemBefore6(ImplStgMemIO* header);
	HRESULT GetTrailerAttributeOnMem(ImplStgMemIO* trailer, unsigned long iTag, MP_AValue* rtn_avalue);
	HRESULT GetTrailerAttributeOnMemAux(ImplStgMemIO* trailer, unsigned long iTag, MP_AValue* rtn_avalue, unsigned char* pValBuff, long int iTrailerSize);
	MP_AType GetTrailerAttributeType( TAG_TYPE iTag );

	// AR9607対策のため追加
	HRESULT OpenMPWithSameAuth( ImplStgTree* pRefTree );

	long SecurityIdFromLabel( const char* pcLabel );

#ifndef SFXVW
	HRESULT NeedsV5Format();
	HRESULT NeedsV6Format();
	HRESULT NeedsV7Format();
	HRESULT HasV6PD();
	HRESULT HasLargePage();
	HRESULT HasUnicodeAttribute();
	BDID SearchSameBDAux( ImplStgReadOnlyDataIO* new_io, MP_Integer  has_tag, long *ret_compressed_size, HRESULT* phres );
	HRESULT CheckBeforeSave( ImplStgFileIO* mp_file );
	long ReadPrevLastDocEnd( long iPrevDocEnd );
	long ReadSignatureDataStart( long iPrevDocEnd );
	int ReadSignatureDataLen( long iPrevDocEnd );
	HRESULT SkipToSignatureTags( ImplStgMemIO* trailer, long iTrailerSize );
	HRESULT GetTrailerMacPos( ImplStgMemIO* trailer );
	HRESULT ReadSecurityID( ImplStgMemIO* trailer, long iTrailerSize );
	HRESULT RewriteHeaderVersion( ImplStgFileIO* mp_file, int iVersion );
	HRESULT RewriteTrailerVersion( ImplStgFileIO* mp_file, int iVersion );
#endif //SFXVW

#ifndef SFXVW
    // セキュリティ対応 12/03/02 Bito
    // セキュリティ認証に必要なデータを引数に追加
    STDMETHOD(OpenMP_Private)(MP_AuthInfo* auth = NULL, void* authdata = NULL);
	//STDMETHOD(OpenMP_Private)(MP_AuthInfo* auth = NULL);
#endif //SFXVW

};

#endif

//
//CHANGE LOG
//97.10.21 - Nagano - 作成
//97.10.28 - Nagano - ディスクフル・エラー処理を追加
//97.11.06 - Nagano - Checksum導入による変更
//97.12.17 - Nagano - AR1951:SaveCompaction()の引数変更.
//97.12.19 - Nagano - AR2026:ImplAttMgr::SeparateFromFile()にremove_file_flagを追加
//98.05.28 - Nagano - V3.1:m_HoldFilepathを追加.CreateFileMPCObject()対応.
//98.06.09 - Nagano - AR2821:m_FilePathを追加
//98.06.09 - Nagano - V3.1:SaveToPath(), SaveToFileObject()追加
//98.10.21 - Komoda - V4開発:ImplStgTreeのGetChildTRID()をGetNextChildTRID()に変更
//99.05.18 - Tashiro - V4.0: Security関連メソッドの追加
//---- お試し版990531リリース
//1999.06.09 - Tashiro - V4開発: BDの暗号化/復号の実装
//1999.06.09 - Tashiro - V4開発: BD(保護あり/なし)のデータチェック機能実装
//1999.06.10 - Tashiro - V4開発: データチェックのコールバック実装
//1999.06.11 - Tashiro - V4開発: セキュリティSPIの変更に対応
//1999.06.25 - Tashiro - V4開発: BD因数化の実装
//1999.07.01 - Tashiro - V4開発: セキュリティシステムがインストールされていないときの仕様に対応
//---- 990701ビルド
//1999.07.02 - Tashiro - V4開発: コメント追加、定数定義移動
//1999.07.06 - Tashiro - V4開発: データ異常が見つかっているときにSave/SaveAsを許さない実装を追加
//1999.07.06 - Tashiro - V4開発: 全更新保存のときは必ず鍵が変えるように修正
//1999.07.23 - Tashiro - V4開発: 1GB超チェックを追加
//---- 990726インテグ
//1999.07.28 - Tashiro - V4開発: 「1GB」はmpc_api.h(MPC_MAX_FILE_SIZE)に定義してあったのでそれを使う
//1999.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//1999.09.06 - Tashiro - V4 AR4745 自己解凍文書用ビューワサイズ削減 追加
//2000.09.25 - Nakazawa - V4.1 EditSecurity()にテンプレート用引数を追加
//---- V5
//2002.02.23 - Tashiro - 署名関連の拡張の仮実装
//2002.03.05 - Tashiro - 自己解凍でビルドできるように修正
//2002.04.19 - Tashiro - 署名検証動作の実装
//2002.05.12 - Tashiro - 検証用ファイルイメージの管理を変更
//2002.05.14 - Nakazawa - V5 128bit暗号対応
//2002.05.18 - Tashiro - ファイルバージョン変更動作を実装
//2002.05.18 - Tashiro - AR7352 署名ロールバック機能の実装
//2002.05.22 - Tashiro - 不要メソッドの削除
//2002.05.23 - Tashiro - AR7456 署名保存時にヘッダをV5にする
//2002.06.10 - Tashiro - AR7436 ファイルオブジェクトに対するSaveIncrementalを実装
//2002.06.20 - Tashiro - AR7457 7458 オブジェクト更新をしない追記保存動作を追加
//2002.06.28 - Tashiro - AR7369 保存後のファイルバージョンを問い合わせるメソッド追加
//2002.07.12 - Tashiro - AR7978 保護+署名文書の追記保存でMACをつぶさない判定の修正
//2002.07.28 - Tashiro - AR7880 署名保存時エラーの復帰処理強化
//2002.11.12 - Tashiro - 5.0.2 AR8297 V4フォーマットに戻すときトレーラのタグも戻す
//---- 6.0開発
//2004.04.06 - Tashiro - V6.0 OM_MODEST_READ導入のためのエラー処理強化
//2004.04.06 - Tashiro - V6.0 V6フォーマット追加対応
//2004.05.12 - Tashiro - V6.0 TMBトレーラ属性対応
//2004.06.29 - Tashiro - AR9607対策 RollBack()引数変更、OpenMPWithSameAuth()追加
//2004.07.16 - Tashiro - AR9358/10026 ツリー内の署名バージョン読み込み実装
//2004.07.29 - Tashiro - AR9358/10026 ツリー内の署名バージョンをキャンセル
//2004.07.29 - Tashiro - AR10326 署名履歴表示機能の追加
//2004.11.29 - Tashiro - AR11868 署名後にファイルバージョンが変わる場合を考慮して検証動作を修正
// --- 6.0.4 ---
//2005.09.29 - Tashiro - APIセキュリティ機能拡張のための実装追加
//---- 6.0.5 ----
//2005.10.17 - Kudo - x64対応：2.0の宣言追加
//----- マルチスレッド対応
//2006.05.26 - Kudo - マルチスレッド対応：乱数のseedをメンバとして保持
//2006.06.07 - Kudo - の排他処理追加
//2006.06.22 - Kudo - の排他処理の漏れ対応
//---- 6.2
//2006.07.20 - Tashiro - セキュリティ追加対応
//2006.08.10 - Tashiro - セキュリティI/F 6.2拡張
//2006.10.26 - Kudo - AR13264 OpenSecurityはの複合化/再暗号化の部分だけを排他する
//---- 7.0
//2007.07.02 - Komoda - VS2005のコンパイルエラー除去
//2007.11.29 - Komoda - V7.0 NeedsV7Format()他の追加
//2007.12.10 - Kitahashi - 2.1対応
