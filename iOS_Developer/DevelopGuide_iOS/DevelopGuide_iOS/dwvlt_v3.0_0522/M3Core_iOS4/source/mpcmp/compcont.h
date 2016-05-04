// File: COMPCONT.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
*	compcont.h : 他のコンテントの親になれるコンテントの基本実装
*/
#include "basecont.h"
#include "objtypes.h"

MPC_EXTERN_GUID(CLSID_COMPOSITECONT, 0x13E4);

MPC_EXTERN_GUID(OT_BASIC_PART, 0x13E3);

/***********************************************************
*  ImplCompositeMedia : 子供を持てるコンテントの基本実装
***********************************************************/

class ImplCompositeMedia  : public ImplBasicMedia
{
public:
// basic manipulations
	STDMETHOD_(void*,GetInterface)(MP_RefInterfaceID riid, HRESULT* phres=NULL) ;
	STDMETHOD(Destroy)();
	STDMETHOD(DestroyFirst)() ;

// structure manipulations
	STDMETHOD(CanLinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL) ;

	STDMETHOD(LinkChild)(MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs=NULL) ;

	STDMETHOD_(MPCObject*,UnlinkChild)(MP_Integer nth, HRESULT* phres=NULL) ;

	STDMETHOD(GetNumberOfChildren)() {
		return MyChildren()->GetNumberOfChildren(); };

	STDMETHOD_(MPCObject*,GetNthChild)(MP_Integer nth, HRESULT* phres=NULL) {
		return MyChildren()->GetNthChild(nth, phres); };

	STDMETHOD(ChangeChildOrder)(MP_Integer src_nth, MP_Integer dst_nth = MP_TOPMOST) ;

	STDMETHOD(GetChildPosition)(MPCObject* mpcchild) {
		return MyChildren()->GetChildPosition(mpcchild); };

// Part manipulations
	STDMETHOD(SetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, const MP_AValue* avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(GetPartAttribute)(MP_Integer nth_part, const MP_AName* aname, MP_AValue* rtn_avalue=NULL, MP_Integer nth_element=-1) ;
	STDMETHOD(EnumPartAttribute)(MP_Integer nth_part, MP_AName* aname, MP_Integer namesize) ;

// MPCMedia
	STDMETHOD(OnDraw)(MP_Canvas* canvas, MPCObject* parent=NULL) {
        MPC_Callback *old_badalloc = MPC_SetCallback(MP_CBID_BADALLOC , 0);
		DrawSelf(canvas, parent, 0);
		HRESULT hres = DrawChild(canvas, parent, 0);
        MPC_SetCallback(MP_CBID_BADALLOC , old_badalloc);
		return hres;
	};

	STDMETHOD(OnPrint)(MP_Canvas* canvas, MPCObject* parent=NULL) {
#ifndef _M3CORE_MP_
        HDC_XD hDC = canvas->GetHDC();
        BOOL_XD isDisplay = FALSE;
        MPC_Callback *old_badalloc = 0;
        if ((GetDeviceCaps(hDC, TECHNOLOGY)) == DT_RASDISPLAY) {
            old_badalloc = MPC_SetCallback(MP_CBID_BADALLOC , 0);
            isDisplay = TRUE;
        }
		DrawSelf(canvas, parent, 1);
		HRESULT hres = DrawChild(canvas, parent, 1);
        if (isDisplay)
            MPC_SetCallback(MP_CBID_BADALLOC , old_badalloc);
        return hres;
#else
		DrawSelf(canvas, parent, 1);
		HRESULT hres = DrawChild(canvas, parent, 1);
        return hres;
#endif // _M3CORE_MP_
	};


	STDMETHOD(DrawChild)(MP_Canvas* canvas, MPCObject* parent, MP_Integer isPrint=0) ;
	STDMETHOD(DrawOneChild)(MPCObject* mpcchild, MP_Canvas* canvas, MP_Rect childrect, MP_Integer isPrint=0) ;

	STDMETHOD(CanRotate)(MP_Integer degree) ;
	STDMETHOD(Rotate)(MP_Integer degree) ;

	STDMETHOD(CanRotateSelf)(MP_Integer degree) ;
	STDMETHOD(RotateSelf)(MP_Integer degree) ;

	STDMETHOD(DoConvert)(MP_Integer version=0) ;

	STDMETHOD(DoConvertSelf)(MP_Integer version=0) {
		return MP_NOERROR;
		};


	STDMETHOD_(ImplBasicMedia*, NewThis)() {
		return new ImplCompositeMedia(CLSID_COMPOSITECONT); };

	STDMETHOD_(void, InitStgObject)(IStgObject* stgobj, MPCSession* session) {
		stgobj->SetObjectType(CLSID_COMPOSITECONT); };

	STDMETHOD(GetPartType)() {
		return OT_BASIC_PART; } ;

	STDMETHOD(SetPartPos)(MP_Integer nth_part, const MP_AName* aname, const MP_AValue* avalue);

	IContainer*	m_icontainer;
	STDMETHOD_(void*, GetIContainer)();
	STDMETHOD_(void, DestroyIContainer)();

	IReferenceMID* m_ReferenceMID;
	STDMETHOD_(void*, GetIReferenceMID)();
	STDMETHOD_(void, DestroyIReferenceMID)();

	MPCConvertVersion*	m_ConvertVersion;
	STDMETHOD_(void*, GetMPCConvertVersion)();
	STDMETHOD_(void, DestroyMPCConvertVersion)();

	// ImplBasicMedia の IPersistMPCObject をオーバライドしている
	STDMETHOD_(void*, GetIPersistMPCObject)();
	STDMETHOD_(void, DestroyIPersistMPCObject)();

	ImplCompositeMedia(MP_RefObjectType type);
	virtual ~ImplCompositeMedia();

//	STDMETHOD_(void, CheckAndSaveChildIconPD)(IStgObject* stgchild, MP_Integer nth) {
//			return;
//		};

	long	m_isCachePD;
	STDMETHOD_(void, SetCache)( MP_Integer on_off );

	MP_Children*	m_children;
	MP_Children*	MyChildren() {
		return m_children; };

	STDMETHOD(DrawChildMark)(MP_Canvas* canvas, MP_Rect childrect) ;
	STDMETHOD(GetCurrentDrawLayer)();
};

class ImplPersistCompositeMedia : public ImplPersistBasicMedia
{
public:
	STDMETHOD(IsDirty)() ;
	STDMETHOD_(IStgObject*, Synchronize)() ;
	STDMETHOD(SaveCompleted)(IStgObject* stgobj) ;
	STDMETHOD(OnLoad)(IStgObject* stgobj, MPCObject* parent, MPCSession* session) ;
	STDMETHOD(OnReload)(IStgObject* stgobj, MPCObject* parent, MPCSession* session) ;

	STDMETHOD(UnloadChild)(MP_Integer nth = MP_ALL_CHILDREN) ;
	STDMETHOD(Unload)(MPCObject* parent) ;

	ImplPersistCompositeMedia(ImplCompositeMedia* mpcobj) : ImplPersistBasicMedia (mpcobj) {
		return; };
	virtual ~ImplPersistCompositeMedia() {
		return; };
	MP_Children*	MyChildren() { return ((ImplCompositeMedia*)m_mpcobj)->m_children; };
};

class ImplContainer : public IContainer
{
public:
	STDMETHOD(PreChangeContent)(MPCObject* content, MP_ContentChangeInfo change_info) ;
	STDMETHOD(PostChangeContent)(MPCObject* content, MP_ContentChangeInfo change_info, MP_Rect rect ) ;
	STDMETHOD(MoveXYPosition)(MPCObject* content, MP_Pos position) ;

	ImplContainer(ImplCompositeMedia* mpcobj) {
		m_mpcobj = mpcobj; };

	virtual ~ImplContainer() {
		return; };

	MP_Children*	MyChildren() {
		return m_mpcobj->m_children; };

	ImplCompositeMedia* m_mpcobj;
};

class ImplReferenceMID : public IReferenceMID
{
public:
	STDMETHOD_(MPCObject*, GetReferenceObject)(MP_PtrArray* midarray, IStgObject** rtn_stgobj, IStgObject** rtn_part , HRESULT* phres ) ;
	STDMETHOD(GenerateMIDArray)(MP_PtrArray* midarray, MPCObject* mpcchild, MPCObject** rtn_ancestor) ;

	ImplCompositeMedia* m_mpcobj;

	ImplReferenceMID(ImplCompositeMedia* mpcobj) {
		m_mpcobj = mpcobj; };

	MP_Children*	MyChildren() {
		return m_mpcobj->m_children; };
};

class ImplConvertVersion : public MPCConvertVersion
{
public:
	ImplCompositeMedia* m_mpcobj;

	ImplConvertVersion(ImplCompositeMedia* mpcobj) {
		m_mpcobj = mpcobj; };

	STDMETHOD(DoConvert)(MP_Integer version=0) {
		return m_mpcobj->DoConvert(version);
		};
};

// AR12815対応 直線アノテの検査を行う
BOOL_XD IsItThisAnn(IStgObject* stgobj, MP_Canvas* canvas, LONG type);

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
//96.7.9 - Ichiriki - Rotate デフォルト実装
//96.7.25 - Ichiriki - 性能改善
//96.7.26 - Ichiriki - AR449対応
//96.8.8 - Ichiriki - 8/7 メールレビューにより境界マージン処理を除去
//97.09.22 - ysato - ImplCompositeMedia::DrawChildMark()追加
//97.10.17 - matsu - ImplCompositeMedia::OnDraw, OnPrintで、メモリ不足時のCallbackを無効にするコードを追加
//97.11.7 - Ichiriki - AR1432, CheckAndSaveChildIconPD()の追加
//97.12.12 - Ichiriki - AR1808.V3変換,MPCConvertVersionの追加
//97.12.22 - Ichiriki - AR2057 代理ペン用変更。DrawSelfをbasecontに移動
//99.7.27 - Ichiriki - AR3644 バインダのアノテ非表示対応＝GetCurrentDrawLayer()追加
//99.9.6 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減。CheckAndSaveChildIconPD削除
