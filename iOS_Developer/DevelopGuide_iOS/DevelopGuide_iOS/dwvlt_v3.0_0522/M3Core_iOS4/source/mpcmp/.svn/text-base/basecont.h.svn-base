// File: BASECONT.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.


#include "mpc_api.h"
#include "mpc_spi.h"
#include "mpc_pd.h"
#include "attruty.h"
#include "reg4gui.h"


MPC_EXTERN_GUID(CLSID_BASICCONT, 0x13E0);

STDMETHODIMP  G_DrawChildMark(MP_Canvas* canvas, MP_Rect childrect);

class ImplBasicMedia : public MPCMedia
{
private:
	MP_Integer m_for_debug_objtype;	//デバッグ時にオブジェクトタイプを見るため（削除するので参照禁止）

public:
// basic manipulations
	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres=NULL) ;
	STDMETHOD(Destroy)() ;
	STDMETHOD(DestroyFirst)() ;

	STDMETHOD_(MPCSession*,GetSession)() {
		return m_session; };

	STDMETHOD_(MP_ObjectType, GetClassID)() {
		return m_stgobj->GetObjectType(); };

	STDMETHOD_(MP_InterfaceID, GetIFID)() {
		return IID_MPCMedia; };

	STDMETHOD_(MPCObject*,Duplicate)(HRESULT* phres=NULL) ;

	STDMETHOD(DoProcedure)(MP_Integer procedureID, MPCObject *pCaller, void *argument, void **result) {
		return MP_E_NOINTERFACE; };

// attribute manipulations
	STDMETHOD(SetAttribute)(const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(SetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element=-1) ;

	STDMETHOD(GetAttribute)(const MP_AName* aname, MP_AValue* rtn_avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(GetAttributeF)(const MP_AName* aname, const MP_Path* path, MP_Integer nth_element=-1) ;

	STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize) {
		return m_stgobj->EnumAttribute(aname, namesize); };

	//V7 Unicode I/F
	STDMETHOD(SetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element=-1) ;
	STDMETHOD(GetAttributeFW)(const MP_AName* aname, const MP_WPath* path, MP_Integer nth_element=-1) ;	

	// structure manipulations
	STDMETHOD(CanLinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL)  {
		return MP_E_UNEXPECTED; };

	STDMETHOD(LinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL)  {
		return MP_E_UNEXPECTED; };

	STDMETHOD_(MPCObject*,UnlinkChild)(MP_Integer nth, HRESULT* phres=NULL)  {
		if(phres) *phres=MP_E_UNEXPECTED; return NULL; };

	STDMETHOD(GetNumberOfChildren)()  {
		return MP_E_UNEXPECTED; };

	STDMETHOD_(MPCObject*,GetNthChild)(MP_Integer nth, HRESULT* phres=NULL)  {
		if(phres) *phres=MP_E_UNEXPECTED; return NULL; };

	STDMETHOD(ChangeChildOrder)(MP_Integer src_nth, MP_Integer dst_nth = MP_TOPMOST) {
		return MP_E_UNEXPECTED; };

	STDMETHOD(GetChildPosition)(MPCObject* child_obj)  {
		return MP_E_UNEXPECTED; };

	STDMETHOD_(MPCObject*, GetParent)() {
		return m_mpcparent; };

	STDMETHOD_(MPCObject*, GetMP)() {
		return m_mpcparent ? m_mpcparent->GetMP() : NULL; };

// Part manipulations
	STDMETHOD(SetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1)  {
		return MP_E_UNEXPECTED; };
	STDMETHOD(GetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, MP_AValue* rtn_avalue=NULL, MP_Integer nth_element=-1)  {
		return MP_E_UNEXPECTED; };
	STDMETHOD(EnumPartAttribute)(MP_Integer nth_part, MP_AName* aname, MP_Integer namesize)  {
		return MP_E_UNEXPECTED; };

// MPCMedia
	STDMETHOD(DrawSelf)(MP_Canvas* canvas, MPCObject* parent, MP_Integer isPrint=0);

	STDMETHOD(OnDraw)(MP_Canvas* canvas, MPCObject* parent=NULL) {
			return DrawSelf(canvas,parent,0);
		};
	STDMETHOD(OnPrint)(MP_Canvas* canvas, MPCObject* parent=NULL) {
			return DrawSelf(canvas,parent,1);
		};

	STDMETHOD(CanRotate)(MP_Integer degree);
	STDMETHOD(Rotate)(MP_Integer degree);

	STDMETHOD_(ImplBasicMedia*, NewThis)() {
		return new ImplBasicMedia(CLSID_BASICCONT); };

	STDMETHOD_(void, InitStgObject)(IStgObject* stgobj, MPCSession* session) {
			stgobj->SetObjectType(CLSID_BASICCONT);
			MPCAValue avalue;
			MP_Dim	dim = {1000, 1000};
			avalue = dim;
			avalue.Store(stgobj, "#dim");
		};

	STDMETHOD(SendPreChange)(IContainer* iparent, MP_ContentChangeInfo changeinfo);
	STDMETHOD(SendPostChange)(IContainer* iparent, MP_ContentChangeInfo changeinfo, MP_Rect rect);

	// AR2837
	STDMETHOD_(void, SpoilNotification)() {
			m_spoiled_notification = 1;
		};
	STDMETHOD_(void, UnspoilNotification)() {
			m_spoiled_notification = 0;
		};
	MP_ContentChangeInfo	m_spoiled_notification;


	IPersistMPCObject* m_PersistMPCObject;
	STDMETHOD_(void*, GetIPersistMPCObject)();
	STDMETHOD_(void, DestroyIPersistMPCObject)();

	IReadOnlyPersist* m_ReadOnlyPersistMPCObject;
	STDMETHOD_(void*, GetIReadOnlyPersistMPCObject)();
	STDMETHOD_(void, DestroyIReadOnlyPersistMPCObject)();

	IContent*	m_icontent;
	STDMETHOD_(void*, GetIContent)();
	STDMETHOD_(void, DestroyIContent)();

	MPCRegisterForGUI* m_RegisterForGUI;
	STDMETHOD_(void*, GetMPCRegisterForGUI)();
	STDMETHOD_(void, DestroyMPCRegisterForGUI)();

	ImplBasicMedia(MP_RefObjectType type);
	virtual ~ImplBasicMedia();

	IStgObject* m_stgobj;
	MPCObject*	m_mpcparent;
	MPCSession*	m_session;
	long m_dirty;	
};

class ImplPersistBasicMedia : public IPersistMPCObject
{
public:
	STDMETHOD(IsDirty)() {
		return m_mpcobj->m_dirty ; };

	STDMETHOD_(IStgObject*, Synchronize)() {
		return m_mpcobj->m_stgobj; } ;

	STDMETHOD(SaveCompleted)(IStgObject* stgobj) {
		m_mpcobj->m_stgobj = stgobj; m_mpcobj->m_dirty = MP_S_FALSE; return MP_NOERROR; };

	STDMETHOD(OnCreate)(IStgObject* stgobj, MPCSession* session) ;

	STDMETHOD(OnLoad)(IStgObject* stgobj, MPCObject* parent, MPCSession* session) ;

	STDMETHOD(OnReload)(IStgObject* stgobj, MPCObject* parent, MPCSession* session) ;

	STDMETHOD(UnloadChild)(MP_Integer nth = MP_ALL_CHILDREN) {
		return MP_E_UNEXPECTED; };

	STDMETHOD(Unload)(MPCObject* parent) ;

	ImplPersistBasicMedia(ImplBasicMedia* mpcobj) {
		m_mpcobj = mpcobj; };

	virtual ~ImplPersistBasicMedia() {
		return; };

	ImplBasicMedia* m_mpcobj;
};

class ImplReadOnlyPersistBasicMedia : public IReadOnlyPersist
{
public:
	STDMETHOD_(IStgObject*, GetStgObjWithoutSync)() {
		return m_mpcobj->m_stgobj; } ;

	ImplReadOnlyPersistBasicMedia(ImplBasicMedia* mpcobj) {
		m_mpcobj = mpcobj; };

	virtual ~ImplReadOnlyPersistBasicMedia() {
		return; };

	ImplBasicMedia* m_mpcobj;
};

class Impl_IContent : public IContent {
public:
	STDMETHOD(PreAttach)(MPCObject* parent, MP_Integer nth, MP_Attrs* part_attrs) {
		return m_mpcobj->m_mpcparent ? MP_S_FALSE : MP_S_OK; };

	STDMETHOD(PostAttach)(MPCObject* parent, MP_Integer nth, MP_Attrs* part_attrs) {
		m_mpcobj->m_mpcparent = parent; return MP_NOERROR; };

	STDMETHOD(PreDetach)(MPCObject* parent, MP_Integer nth) {
		return MP_S_OK; };

	STDMETHOD(PostDetach)(MPCObject* parent, MP_Integer nth) {
		m_mpcobj->m_mpcparent = NULL; return MP_NOERROR; };

	Impl_IContent(ImplBasicMedia* mpcobj) {
		m_mpcobj = mpcobj; };

	virtual ~Impl_IContent() {
		return; };

	ImplBasicMedia* m_mpcobj;
};

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//97.12.22 - Ichiriki - AR2057 代理ペン用変更。G_DrawChildMarkとDrawSelfの移動
//98.06.16 - Ichiriki - AR2837 LinkChild時の不要領域描画の回避, SpoilNotification追加
//08.9.1 - Tashiro - V7 AR15514 SynchronizeしないでIStgObjectを取得する新I/Fの実装を追加
