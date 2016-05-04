// File: IMPL_MP.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.
//
#include "mpc_spi.h"

MPC_EXTERN_GUID(OT_MP_PART, 0x1302);

MPC_EXTERN_GUID(IID_ImplProfile, 0x1370);

MPC_EXTERN_GUID(IID_MPCPaperRoot, 0x1305);

class ImplProfile;
class ImplPersistMPProfile;

class ImplMPContDocInteraction;
class ImplMPContainer;
class ImplMPNotificationRegister;
class ImplMPContent;
class ImplMPHintFromGUI;

class ImplPageRoot;
class ImplPRootContainer;
class ImplPRootReferenceMID;

class ImplReadOnlyPersistMPProfile;

/****************************************************
 *	METAPAPERの MPCProfileインタフェースの定義
 *****************************************************/

class ImplProfile : public MPCProfile
{
public:
	// basic manipulations
	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres=NULL) ;
	STDMETHOD(Destroy)() ;
	STDMETHOD(DestroyFirst)() ;
    
	STDMETHOD_(MPCSession*,GetSession)() ;
	STDMETHOD_(MP_ObjectType, GetClassID)() ;
	STDMETHOD_(MP_InterfaceID, GetIFID)() ;
	STDMETHOD_(MPCObject*,Duplicate)(HRESULT* phres=NULL) ;
	STDMETHOD(DoProcedure)(MP_Integer procedureID, MPCObject *pCaller, void *argument, void **result);
    
	// attribute manipulations
	STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(SetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element=-1) ;
    
	STDMETHOD(GetAttribute)(const MP_AName* aname, MP_AValue* rtn_avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(GetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element=-1) ;
    
	STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize) ;
    
	// structure manipulations
	STDMETHOD(CanLinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL) ;
	STDMETHOD(LinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL) ;
	STDMETHOD_(MPCObject*,UnlinkChild)(MP_Integer nth, HRESULT* phres=NULL) ;
	STDMETHOD(GetNumberOfChildren)() ;	// use return value
	STDMETHOD_(MPCObject*,GetNthChild)(MP_Integer nth, HRESULT* phres=NULL) ;
	STDMETHOD(ChangeChildOrder)(MP_Integer src_nth, MP_Integer dst_nth = MP_TOPMOST) ;
	STDMETHOD(GetChildPosition)(MPCObject* child_obj) ;	// use return value
	STDMETHOD_(MPCObject*, GetParent)() ;
	STDMETHOD_(MPCObject*, GetMP)() ;
    
	// Part manipulations
	STDMETHOD(SetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(GetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, MP_AValue* rtn_avalue=NULL, MP_Integer nth_element=-1) ;
    
	STDMETHOD(EnumPartAttribute)(MP_Integer nth_part, MP_AName* aname, MP_Integer namesize) ;
    
    // profile
    // セキュリティ対応 12/03/02 Bito
    // セキュリティ認証に必要なデータを引数に追加
    STDMETHOD(OpenMP)(MP_AuthInfo* auth=NULL, void* authdata = NULL) ;
	//STDMETHOD(OpenMP)(MP_AuthInfo* auth=NULL) ;
    STDMETHOD(DELETED_SetAplLog)( /*MP_LogInfo* log*/ ) {
		return MP_E_NOTIMPL; };
	STDMETHOD(DefineAttribute)(const MP_AName* aname, MP_AType atype, MP_Integer nth_element = -1) ;
	STDMETHOD(UndefineAttribute)(const MP_AName* aname) ;
    //	STDMETHOD(NotifyAplEvent)(MP_EvName* evname, MP_Integer pre_post=MP_POST) ;
    //	STDMETHOD(OnDraw)(MP_Canvas* canvas) ;
	STDMETHOD_(MPCProfile*,ShallowDuplicate)(HRESULT* phres = NULL) ;
	STDMETHOD(GetStorageVersion)() ;
	STDMETHOD(GetFilePath)(MP_Integer size, MP_Path* path) ;
    
	STDMETHOD(AddAuthentication)(MP_Permission perm) ;
	STDMETHOD(EditSecurity)() ;
	STDMETHOD_(MP_Permission, GetPermission)(HRESULT* phres = NULL) ;
	STDMETHOD_(MP_Permission, GetAuthenticatedPermission)(HRESULT* phres = NULL) ;
	STDMETHOD(ShowSecurityInfo)() ;
	STDMETHOD(CheckData)(MP_Integer* nth_page, MP_Integer* nth_org, MP_Integer* others, MPC_AdvCancelInfo* info = NULL) ;
	// V4.1追加
	STDMETHOD(CreateSecurityWithTemplate)(MPC_SecurityTemplate* pTemplate);
	// V5
	STDMETHOD(GetNumberOfSignatures)();
	STDMETHOD_(MPCObject*, GetNthSignatureObject)(MP_Integer nth, HRESULT* phres = NULL);
	STDMETHOD(GetSaveStorageVersion)();
	// V6
	STDMETHOD(GetTrailerAttribute)(unsigned long iTag, MP_AValue* rtn_avalue=NULL);
    
	STDMETHOD(ReleaseSecurity)();
	STDMETHOD(AddAuthenticationEx)(MP_AuthInfo* auth) ;
    
	// V62
	STDMETHOD(GetSecurityModuleData)(char* pModuleData);
    
	// V7 Unicode I/F
	STDMETHOD(GetFilePathW)(MP_String &path);
	STDMETHOD(SetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element=-1) ;
	STDMETHOD(GetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element=-1) ;
    
    
    // 内部メソッド
	STDMETHOD_(MPCObject*, GetReferenceObject)(MP_PtrArray* midarray, IStgObject** rtn_stgobj, IStgObject** rtn_part, HRESULT* phres) ;
	STDMETHOD(SetPartPos)(MP_Integer nth_part, const MP_AName* aname, const MP_AValue* avalue);
	STDMETHOD(SendPreChange)(IContainer* iparent, MP_ContentChangeInfo changeinfo);
	STDMETHOD(SendPostChange)(IContainer* iparent, MP_ContentChangeInfo changeinfo, MP_Rect rect);
    
	IStgObject* m_stgobj;
	ImplPersistMPProfile* m_PersistMPCObject;
	ImplReadOnlyPersistMPProfile* m_ReadOnlyPersist;
	MPCSession* m_session;
	long m_dirty;
    
	MPCObject*	m_mpcparent;	// 親MPCオブジェクト
	ImplMPContent*	m_icontent;
    //恐らくテンプレートの子供になる時に必要だろうから
    
	MP_Children*	m_array_pcont;
	MP_Children*	MyChildren() { return m_array_pcont; };
    
	ImplMPContainer*	m_icontainer;	//Profile contentの親の窓口
    
	MPCObject*	m_MPCPageRoot;
	MP_Children*	m_array_bpage;
    
	MPCObject*	m_MPCContDocRoot;
	MP_Children*	m_array_cdoc;	// MPはContDocルート用、バインダはDocルート用と兼用している
    
	STDMETHOD(SetCachePage)(MPCObject* bpage);
	MP_PtrArray*	m_array_cachedpage;
    
	ImplMPContDocInteraction*	m_IMPContDocInteraction;
    //	ImplMPNotificationRegister*	m_IMPNotificationRegister;
    
	MPCRegisterForGUI* m_RegisterForGUI;
	STDMETHOD_(void*, GetMPCRegisterForGUI)();
	STDMETHOD_(void, DestroyMPCRegisterForGUI)();
    
	IReferenceMID*	m_ReferenceMID;
	STDMETHOD_(void*, GetIReferenceMID)();
	STDMETHOD_(void, DestroyIReferenceMID)();
    
	ImplMPHintFromGUI*	m_HintFromGUI;
	STDMETHOD_(void*, GetMPCHintFromGUI)();
	STDMETHOD_(void, DestroyMPCHintFromGUI)();
    
	MPCConvertVersion*	m_ConvertVersion;
	STDMETHOD_(void*, GetMPCConvertVersion)();
	STDMETHOD_(void, DestroyMPCConvertVersion)();
    
	ImplProfile();
	virtual ~ImplProfile();
    
    // V4追加
	STDMETHOD_(ImplProfile*, NewThis)();
	STDMETHOD(GetNumberOfPage)(MP_Integer* p_long);
	STDMETHOD(InitializeMPStorageTree)(IStgObject* m_stgobj);
	STDMETHOD(SaveCompleted)();	//BinderとMPでPersistインタフェース処理を変えるために追加
    
	MPCInternalDocument* m_internalDocument;
	STDMETHOD_(void*, GetMPCInternalDocument)();
	STDMETHOD_(void, DestroyMPCInternalDocument)();
};

#define NTH_PAGE_ROOT	0
#define NTH_PROFILE		1
#define NTH_CDOC_ROOT	2
#define NTH_PAPER_ROOT	3


/****************************************************
 *	METAPAPERの PageRoot インタフェースの定義
 *****************************************************/

class ImplPageRoot : public MPCObject
{
public:
	// basic manipulations
	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres=NULL) ;
	STDMETHOD(Destroy)() ;
	STDMETHOD_(MPCSession*,GetSession)() ;
	STDMETHOD_(MP_ObjectType,GetClassID)() ;
	STDMETHOD_(MP_InterfaceID,GetIFID)() ;
	STDMETHOD_(MPCObject*,Duplicate)(HRESULT* phres=NULL) ;
	STDMETHOD(DoProcedure)(MP_Integer procedureID, MPCObject *pCaller, void *argument, void **result);
    
	// attribute manipulations
	STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(SetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element=-1) ;
    
	STDMETHOD(GetAttribute)(const MP_AName* aname, MP_AValue* rtn_avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(GetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element=-1) ;
    
	STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize) ;
    
	// V7 Unicode I/F
	STDMETHOD(SetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element=-1) ;
	STDMETHOD(GetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element=-1) ;
    
	// structure manipulations
	STDMETHOD(CanLinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL) ;
	STDMETHOD(LinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL) ;
	STDMETHOD_(MPCObject*,UnlinkChild)(MP_Integer nth, HRESULT* phres=NULL) ;
	STDMETHOD(GetNumberOfChildren)() ;	// use return value
	STDMETHOD_(MPCObject*,GetNthChild)(MP_Integer nth, HRESULT* phres=NULL) ;
	STDMETHOD(ChangeChildOrder)(MP_Integer src_nth, MP_Integer dst_nth = MP_TOPMOST) ;
	STDMETHOD(GetChildPosition)(MPCObject* child_obj) ;	// use return value
	STDMETHOD_(MPCObject*, GetParent)() ;
	STDMETHOD_(MPCObject*, GetMP)() ;
    
	// Part manipulations
	STDMETHOD(SetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(GetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, MP_AValue* rtn_avalue=NULL, MP_Integer nth_element=-1) ;
    
	STDMETHOD(EnumPartAttribute)(MP_Integer nth_part, MP_AName* aname, MP_Integer namesize) ;
    
    
	ImplPageRoot(ImplProfile* mpcprofile, HRESULT* phres);
	virtual ~ImplPageRoot();
    
	virtual MP_Children* MyChildren() { return m_mpcobj->m_array_bpage; };
    
	ImplProfile*	m_mpcobj;
	ImplPRootContainer* m_ImplPRootContainer;
};

// 内部オブジェクトの生成と破棄

MPCObject* MPCPageRoot_Create(ImplProfile* mpcprofile, HRESULT *phres);
void MPCPageRoot_Destroy(MPCObject* mpcobj);

MPCObject* MPCContDocRoot_Create(ImplProfile* mpcprofile, HRESULT *phres);
void MPCContDocRoot_Destroy(MPCObject* mpcobj);

ImplMPNotificationRegister*	ImplMPNotificationRegister_Create(ImplProfile* mpcobj);
void ImplMPNotificationRegister_Destroy(ImplMPNotificationRegister* ifobj);

ImplMPContainer*	ImplMPContainer_Create(ImplProfile* mpcobj);
void ImplMPContainer_Destroy(ImplMPContainer* ifobj);

ImplMPContDocInteraction*	ImplMPContDocInteraction_Create(ImplProfile* mpcobj);
void ImplMPContDocInteraction_Destroy(ImplMPContDocInteraction* ifobj);

ImplPersistMPProfile* ImplPersistMPProfile_Create(ImplProfile* implprof);
void ImplPersistMPProfile_Destroy(ImplPersistMPProfile* ifobj);

ImplMPContent*	ImplMPContent_Create(ImplProfile* mpcobj);
void ImplMPContent_Destroy(ImplMPContent* ifobj);

ImplReadOnlyPersistMPProfile* ImplReadOnlyPersistMPProfile_Create(ImplProfile* implprof);
void ImplReadOnlyPersistMPProfile_Destroy(ImplReadOnlyPersistMPProfile* ifobj);


//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.25 - Ichiriki - 性能改善
//96.8.8 - Ichiriki - PDフォーマット変更に伴う、３→４コンバート
//96.8.26 - Ichiriki - AR863 コンバート処理削除
//97.3.14 - Nagano - AR466:ImplMPHintFromGUIの追加
//97.10.14 - Ichiriki - MPCProfileに、ShallowDuplicate, GetStorageVersion, GetFilePathを追加
//97.10.20 - Ichiriki - 未使用のAidToNumberNameを削除
//97.12.12 - Ichiriki - AR1808.V3変換,MPCConvertVersionの追加
//99.5.18 - Ichiriki - V4: ImplProfileにセキュリティ関係の定義を追加
//99.5.20 - Ichiriki - V4: バインダ対応, PageRoot実装をバインダと共有できるよう移動
//99.8.17 - Ichiriki - AR4199 STDMETHOD(SaveCompleted)() 追加
//00.9.25 - Nakazawa - V4.1 ImplProfileにCreateSecurityWithTemplate追加
//---V5
//2002.02.23 - Tashiro - 署名関連の操作をMPCProfileに追加
//2002.06.28 - Tashiro - AR7369 保存後のファイルバージョンを問い合わせるメソッド追加
//----V6開発
//2004.05.12 - Tashiro - V6.0 TMBトレーラ属性対応
// --- 6.0.4 ---
//2005.09.30 - Tashiro - APIセキュリティ機能拡張のためにMPCProfileにメソッド追加
// --- 6.2 ---
//2006.08.10 - Tashiro - セキュリティI/F 6.2拡張
// --- 7.0 ---
//2008.09.01 - Tashiro - V7.0 AR15514 SynchronizeしないでIStgObjectを取得する新I/Fの実装を追加
