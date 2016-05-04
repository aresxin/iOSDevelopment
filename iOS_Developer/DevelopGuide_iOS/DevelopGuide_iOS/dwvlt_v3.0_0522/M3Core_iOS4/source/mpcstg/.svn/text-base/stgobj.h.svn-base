// File: STGOBJ.H
// Auther: Osamu Nagano
// Copyright(C) 1997 by Fuji Xerox Co,. Ltd. All right reserved.

#ifndef __STG_STGOBJ_H__
#define __STG_STGOBJ_H__

#include "mpc_spi.h"
#include "array_p.h"
#include "stg.h"

MPC_EXTERN_GUID(IID_CStorageObject, 0x1373);

class ImplStgObj  : public IStgObject {

public:
	ImplStgTree*	m_Tree;
	TRID			m_TRID;			// mTree->m_FileTree内のレコードを指すoffset.スクラッチのときは-INVALID_TRID.
	TRID			m_NewTRID;		// Save,SaveAs用TRID
	OBJECT_TYPE		m_ObjectType;
	ImplStgObj*		m_ParentStgObj;
	ImplStgAttManager*	m_AttMgn;
	MP_PtrArray*	m_ChildArray;	// 子配列."NULL"または"子がすべてロードされている状態"のどちらか．

	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres = NULL);
	STDMETHOD(Destroy)();
	STDMETHOD_(IStgObject*,Duplicate)(HRESULT* phres = NULL);
	STDMETHOD_(IStgObject*,ShallowDuplicate)(HRESULT* phres = NULL);
	STDMETHOD_(IStgObject*, CreateIStgObject)(MP_RefObjectType clsid, HRESULT* phres = NULL);
	STDMETHOD(GetNumberOfChildren)();
	STDMETHOD_(IStgObject*,GetNthChild)(long nth, HRESULT* phres = NULL);
	STDMETHOD(GetChildPosition)(IStgObject* obj);
	STDMETHOD(InsertChild)(IStgObject* obj, long nth);
	STDMETHOD_(IStgObject*,RemoveChild)(long nth, HRESULT* phres = NULL);
	STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue = NULL, MP_Integer nth_element = -1, MP_Integer do_assign = 1);
	STDMETHOD(SetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element = -1, MP_Integer do_assign = 1);
	STDMETHOD(GetAttribute)(const MP_AName* aname, MP_AValue* rtn_avalue = NULL, MP_Integer nth_element = -1);
	STDMETHOD(GetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element = -1);
	STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize);
	STDMETHOD(GetStorageVersion)();
	STDMETHOD_(MP_ObjectType, GetObjectType)();
	STDMETHOD(SetObjectType)(MP_RefObjectType clsid);
	STDMETHOD(SetCurrentDateTime)(const MP_AName* aname = NULL );
	STDMETHOD(GetFilePath)(MP_Integer size, MP_Path* path);

	// V4 Security
    // セキュリティ対応 12/03/02 Bito
    // セキュリティ認証に必要なデータを引数に追加
    STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL, void* authdata = NULL);
	//STDMETHOD(OpenMP)(MP_AuthInfo* auth = NULL);
	STDMETHOD(AddAuthentication)(MP_Permission perm);
	STDMETHOD(EditSecurity)();
	STDMETHOD_(MP_Permission, GetPermission)(HRESULT* hres = NULL);
	STDMETHOD_(MP_Permission, GetAuthenticatedPermission)(HRESULT* hres = NULL);
	STDMETHOD(ShowSecurityInfo)();
	STDMETHOD(CheckData)(MP_Integer* nth_page, MP_Integer* nth_org, MP_Integer* others, MPC_AdvCancelInfo* info = NULL);
	STDMETHOD(OnBeginPrint)(MP_Canvas* pCanvas, MPCObject* pBasicPage);
	STDMETHOD(OnEndPrint)(MP_Canvas* pCanvas, MPCObject* pBasicPage);
	// V4.1 Security
	STDMETHOD(CreateSecurityWithTemplate)(MPC_SecurityTemplate* pTemplate);
	// V5
	STDMETHOD(GetNumberOfObjectsWithGivenType)( MP_ObjectType type );
	STDMETHOD_(MP_VerificationCondition, MakeVerificationCondition)(HRESULT* phres = NULL);
	STDMETHOD(DestroyDocImage)();
	STDMETHOD(GetSaveStorageVersion)();
	// V6
	STDMETHOD(GetTrailerAttribute)(unsigned long iTag, MP_AValue* rtn_avalue=NULL);

	STDMETHOD(ReleaseSecurity)();
	STDMETHOD(AddAuthenticationEx)(MP_AuthInfo* auth);

	// V62
	STDMETHOD(GetSecurityModuleData)(char* pModuleData);

	STDMETHODIMP GetSpecialAttribute( const MP_AName* aname, MP_AValue* rtn_avalue, MP_Integer nth_element );
	
	// V7 Unicode版I/F
	STDMETHOD(SetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element = -1, MP_Integer do_assign = 1);
	STDMETHOD(GetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element = -1);
	STDMETHOD(GetFilePathW)(MP_String& path);

	ImplStgObj( OBJECT_TYPE object_type, ImplStgTree* tree, TRID trid, ImplStgObj* parent, HRESULT *phres );
	~ImplStgObj();
	HRESULT DestroyWithChildren(void);
	ImplStgObj* GetParent(void);
	MP_Integer AdjustNth( MP_Integer nth );
	ImplStgObj* GetCopyWithChildren( HRESULT* phres );
	HRESULT	IntoScratch( MP_Integer remove_file_flag, MP_Integer do_decrypt );
	HRESULT	SeparateFromFile( MP_Integer remove_file_flag, MP_Integer do_decrypt );
	HRESULT	CompleteSeparateFromFile(void);
	HRESULT	UndoSeparateFromFile(void);
	HRESULT SetTreeWithChildren( ImplStgTree* tree );
	HRESULT LoadAllChildren(void);
	ImplStgObj* NextStgObj( long& level );
	STDMETHODIMP SetCompressedAttribute( const MP_AName* aname, const MP_AValue* avalue, MP_Integer nth_element, MP_Integer do_assign );
	STDMETHODIMP GetCompressedAttribute( const MP_AName* aname, MP_AValue* rtn_avalue, MP_Integer nth_element );
#ifndef SFXVW
	HRESULT GetNewBDArray( ImplStgWriteData* write_data );
	HRESULT EncodeTree( ImplStgWriteData* write_data, long level );
	HRESULT SaveComplete( ImplStgObj* root_stgobj );
#endif //SFXVW

	//v4 Security

#ifndef SFXVW
	HRESULT CheckBD( MPC_AdvCancelInfo* info );
		//ファイル内にある自分の属性のハッシュを検定する。
		//保護なしはチェックサム、保護ありはSHA1。
#endif //SFXVW
	HRESULT CanEdit();
		//現在の認証状態で自分が変更可能か調べる。
	HRESULT CanEditChild( ImplStgObj* child );
		//現在の認証状態で子供が変更可能か調べる。
	HRESULT GetCategoryOfProtection();
		//自分のクラスIDに応じて文書要素かアノテか等を答える。
	HRESULT IsAttAlwaysWritable( const MP_AName* aname );
		//この属性は認証状態に関わらず書き込める。
	HRESULT IsAttAlwaysReadProtected( const MP_AName* aname );
		//この属性は認証状態に関わらず読み出せない。
	HRESULT IsAttAlwaysWriteProtected( const MP_AName* aname );
		//この属性は認証状態に関わらず書き込めない。
	HRESULT IsAttCopyProtected( const MP_AName* aname );
		//この属性は転記禁止のとき読み出せない。
	HRESULT IsAttSpecialyReadable( const MP_AName* aname );
		//この属性はISpecialAttribute経由で読み出せる。
	HRESULT IsAttReadableEvenIfRestricted( const MP_AName* aname );
		//この属性は転記禁止時にUnlinkされていても読み出せる。
	HRESULT SetLinkRestriction( const ImplStgTree* native_tree );
		//元のツリーにLinkされるまでアクセス不可能にする。
		//転記禁止時にUnlinkされたとき。
	HRESULT GetLinkRestriction( ImplStgTree** ret_native_tree = NULL );
		//元のツリーにLinkされるまでアクセス不可能な状態か調べる。
	HRESULT DelLinkRestriction( );
		//アクセス不可能状態を解除する。元のツリーにLinkされたとき。
	HRESULT AddPermIfNecessary( MP_Permission perm );
		//パミッションが無ければ追加を試みる。すでにあればMP_S_OK。
	HRESULT IsReusableMode();
		//因数化対象属性をセットするモードになっているか。
		//"~reuse"がセットされていればMP_S_OK;

	// V5
	HRESULT ChangeTree( ImplStgTree* pNewTree );
		// 自分以下のm_Treeをすべて変更する。ルートオブジェクトのみ

	ImplStgObj* GetNthSignatureObject(MP_Integer nth, HRESULT* hres = NULL);

	HRESULT IncludesSignatureObject();

};

#endif

//
//CHANGE LOG
//97.10.21 - Nagano - 作成
//97.10.28 - Nagano - ディスクフル・エラー処理を追加
//97.12.19 - Nagano - AR2026:ImplAttMgr::SeparateFromFile()にremove_file_flagを追加
//99.05.27 - Tashiro - V4開発: セキュリティ機能の仮実装
//---- お試し版990531リリース
//1999.06.09 - Tashiro - V4開発: do_decrypt/do_encrypt引数追加
//1999.06.09 - Tashiro - V4開発: BD(保護あり/なし)のデータチェック機能実装
//1999.06.10 - Tashiro - V4開発: データチェックのコールバック実装
//1999.06.14 - Tashiro - V4開発: GetSpecialAttribute(文字認識結果取得用I/F)を追加
//1999.06.15 - Tashiro - V4開発: 自動的に追加認証する仕様を実装
//1999.06.25 - Tashiro - V4開発: BD因数化の実装
//---- 990707インテグ
//1999.07.22 - Tashiro - V4開発: AR3991 転記権なしでUnlinkされたオブジェクトで#dimだけは読み出せるように修正
//---- 990830インテグ
//1999.09.06 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
//1999.09.06 - Tashiro - V4 AR4745 自己解凍文書用ビューワサイズ削減 追加
//2000.09.25 - Nakazawa - V4.1 CreateSecurityWithTemplate追加
//---- V5
//2002.02.23 - Tashiro - 署名関連の拡張の仮実装
//2002.04.19 - Tashiro - 署名検証動作の実装
//2002.04.29 - Tashiro - 署名の数→指定タイプの子孫の数にI/Fを一般化
//2002.05.12 - Tashiro - 検証用ファイルイメージの管理を変更
//2002.06.28 - Tashiro - AR7369 保存後のファイルバージョンを問い合わせるメソッド追加
//---- V6
//2004.05.12 - Tashiro - V6.0 TMBトレーラ属性対応
//2004.07.29 - Tashiro - AR10326 署名履歴表示機能の追加
// --- 6.0.4 ---
//2005.09.29 - Tashiro - APIセキュリティ機能拡張のためにIStgObjectにメソッド追加
//---- 6.0.5 ----
//2005.10.17 - Kudo - x64対応：2.0の宣言追加
//2006.01.16 - Tashiro - AR12665 自分以下に署名オブジェクトがあるか確認するメソッド追加
//---- 6.2 ----
//2006.06.06 - Kudo - の排他処理追加
//2006.08.10 - Tashiro - セキュリティI/F 6.2拡張
//---- 7.0 ----
//2007.12.10 - Kitahashi - 2.1対応
