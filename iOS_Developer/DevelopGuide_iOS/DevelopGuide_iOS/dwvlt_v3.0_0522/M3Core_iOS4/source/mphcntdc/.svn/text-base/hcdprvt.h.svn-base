// $Archive: /DocuWorks/70/Source/mphcntdc/HCDPRVT.H $
//
// Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved. 
//
// $Author: chikyu $
// $Date: 2009/12/22 08:11:28 $
// $Revision: 1.5 $

// File: hcdprvt.h
// Author: Takashi Matsumoto
// Copyright(C) 1996-2004 by Fuji Xerox Co,. Ltd. All right reserved.  

#ifndef HCDPRVT_H
#define HCDPRVT_H

//#include <windows.h>
#include <limits.h>
#include <hcntdoc.h>
#include <icontdoc.h>
#include <stg_spi.h>
#include <array_p.h>
#include <mpc_gui.h>
#include <mpc_text.h>
#include <spgettext.h>

enum GUINotificationType {
	AAAOnRemoveFromMemory,
		// メモリからの消滅。MPCObject::Destroy() からコールする

// 以下未実装
	AAAOnChangePresentation,
	AAAOnChangeDimension,
	AAAOnMoveChild,
	AAAOnResizeChild,
	AAAOnReorderChild,
	AAAPostLinkChild,
	AAAPreUnlinkChild,
	AAAPostUnlinkChild
};


class HeteroContDoc : public IHeteroContDoc {

public:
	// MPCInterface
	STDMETHOD_(void*, GetInterface)(
		MP_RefInterfaceID riid, HRESULT* phres = NULL);
	STDMETHOD(Destroy)();

	// MPCObject
	STDMETHOD_(MPCSession*, GetSession)();
	STDMETHOD(GetClassID)();
	STDMETHOD(GetIFID)();
	STDMETHOD_(MPCObject*, Duplicate)(HRESULT* phres = NULL);
	STDMETHOD(DoProcedure)(
		MP_Integer procedureID, MPCObject *mpcobj, void *argument,
		void **result);
	STDMETHOD(SetAttribute)(
		const MP_AName* aname, const MP_AValue* avalue = NULL,
		MP_Integer nth_element = -1);
	STDMETHOD(SetAttributeF)(
		const MP_AName* aname, const MP_Path* path,
		MP_Integer nth_element = -1);
	STDMETHOD(GetAttribute)(
		const MP_AName* aname, MP_AValue* rtn_avalue = NULL,
		MP_Integer nth_element = -1);
	STDMETHOD(GetAttributeF)(
		const MP_AName* aname, const MP_Path* path,
		MP_Integer nth_element = -1);
	STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize);
	STDMETHOD(CanLinkChild)(
		MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs = NULL);
	STDMETHOD(LinkChild)(
		MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs = NULL);
	STDMETHOD_(MPCObject*, UnlinkChild)(MP_Integer nth, HRESULT* phres = NULL);
	STDMETHOD(GetNumberOfChildren)();
	STDMETHOD_(MPCObject*, GetNthChild)(MP_Integer nth, HRESULT* phres = NULL);
	STDMETHOD(ChangeChildOrder)(
		MP_Integer src_nth, MP_Integer dst_nth = MP_TOPMOST);
	STDMETHOD(GetChildPosition)(MPCObject* child_obj);
	STDMETHOD_(MPCObject*, GetParent)();
	STDMETHOD_(MPCObject*, GetMP)();
	STDMETHOD(SetPartAttribute)(
		MP_Integer nth_part, const MP_AName* aname,
		const MP_AValue* avalue=NULL, MP_Integer nth_element = -1);
	STDMETHOD(GetPartAttribute)(
		MP_Integer nth_part, const MP_AName* aname,
		MP_AValue* rtn_avalue=NULL, MP_Integer nth_element = -1);
	STDMETHOD(EnumPartAttribute)(
		MP_Integer nth_part, MP_AName* aname, MP_Integer namesize);
	STDMETHOD(SetAttributeFW)(
		const MP_AName* aname, const MP_WPath* path,
		MP_Integer nth_element = -1);
	STDMETHOD(GetAttributeFW)(
		const MP_AName* aname, const MP_WPath* path,
		MP_Integer nth_element = -1);

	// 	MPCContDocument
#ifndef SFXVW
	STDMETHOD(RequestRegeneration)();
	STDMETHOD(BreakRegeneration)();

	// IHeteroContDoc

	STDMETHOD(UpdateBody)(const char* infPathName, int page = -1);
	// 09.07.14 - M.Chikyu UNICODE対応
	STDMETHOD(UpdateBodyW)(const MP_WPath* infPathNameW, int page = -1);

	STDMETHOD(SetNative)(const char* pathName);

	STDMETHOD_(MPCObject*, GetReferencePage)(
		MP_Integer nth, HRESULT* phres = NULL);
	STDMETHOD(SetNativeFile)(const MP_Path* pathName, MP_TAType tatype, int codepage);
	STDMETHOD(SetNativeFileW)(const MP_WPath* pathName, MP_TAType tatype, int codepage);
	STDMETHOD(SetNativeName)(const char* name, MP_TAType tatype, int codepage);
	STDMETHOD(SetNativeNameW)(const MP_Text* name, MP_TAType tatype, int codepage);
#endif //SFXVW
	STDMETHOD(GetNativeData)(const MP_Path* pathName);
	STDMETHOD(GetNativeDataW)(const MP_WPath* pathName);
	STDMETHOD(GetNativeName)(MP_MBString& name, MP_TAType& tatype, int codepage);
	STDMETHOD(GetNativeNameW)(MP_String& name, MP_TAType& tatype, int codepage);

	class ContDocument : public IContDocument {
	public:
		HeteroContDoc* m_this;
		STDMETHOD(PreTakeIn)(MPCObject* cdoc_root, MP_Integer nth);
		STDMETHOD(PostTakeIn)(MPCObject* cdoc_root, MP_Integer nth);
		STDMETHOD(PreTakeOut)(MPCObject* cdoc_root, MP_Integer nth);
		STDMETHOD(PostTakeOut)(MPCObject* cdoc_root, MP_Integer nth);
		STDMETHOD(UnlinkAndReferTo)(MPCObject* bcont, MP_AValue* refmid);
		STDMETHOD(NotifyDetachReference)(MP_AValue* refmid, MPCObject* bcont);
	} m_contDoc;

	class PersistMPCObject : public IPersistMPCObject {
	public:
		HeteroContDoc* m_this;
		STDMETHOD(IsDirty)();
		STDMETHOD_(IStgObject*, Synchronize)();
		STDMETHOD(SaveCompleted)(IStgObject* stgobj);
		STDMETHOD(OnCreate)(IStgObject* stgobj, MPCSession* session);
		STDMETHOD(OnLoad)(
			IStgObject* stgobj, MPCObject* parent, MPCSession* session);
		STDMETHOD(OnReload)(
			IStgObject* stgobj, MPCObject* parent, MPCSession* session);
		STDMETHOD(UnloadChild)(MP_Integer nth = -1);
		STDMETHOD(Unload)(MPCObject* parent);
	} m_persist;

	class ReadOnlyPersist : public IReadOnlyPersist {
	public:
		HeteroContDoc* m_this;
		STDMETHOD_(IStgObject*, GetStgObjWithoutSync)() {
			return m_this->m_storage; } ;
	} m_readonlyPersist;

	class ImplRegisterForGUI : public MPCRegisterForGUI {
	public:
		HeteroContDoc* m_this;
		STDMETHOD(RegisterGUI)(INotificationToGUI* gui, MPCObject* mpcobj = NULL);
		STDMETHOD(UnregisterGUI)(INotificationToGUI* gui, MPCObject* mpcobj = NULL);
	} m_forGui;

	void SendGUINotification(
		GUINotificationType type, MPCObject* child, MP_Rect rect = MP_NULL_RECT);


	MPCSession* m_session;
	MPCObject* m_parent;
	IStgObject* m_storage;
	int m_dirty;
	MP_PtrArray* m_children;
	MP_PtrArray* m_guis;
#ifndef SFXVW
	BOOL_XD m_fBreakRegeneration;
#endif //SFXVW

	HeteroContDoc();
};

class CBodyContentText;
class CBodyContentSelectText;
class CBodyContentFind;
class CBodyContentPDCache;

class HeteroBodyCont : public IHeteroBodyCont {

public:
	// MPCInterface
	STDMETHOD_(void*, GetInterface)(
		MP_RefInterfaceID riid, HRESULT* phres = NULL);
	STDMETHOD(Destroy)();

	// MPCObject
	STDMETHOD_(MPCSession*, GetSession)();
	STDMETHOD(GetClassID)();
	STDMETHOD(GetIFID)();
	STDMETHOD_(MPCObject*, Duplicate)(HRESULT* phres = NULL);
	STDMETHOD(DoProcedure)(
		MP_Integer procedureID, MPCObject *mpcobj, void *argument,
		void **result);
	STDMETHOD(SetAttribute)(
		const MP_AName* aname, const MP_AValue* avalue=NULL,
		MP_Integer nth_element = -1);
	STDMETHOD(SetAttributeF)(
		const MP_AName* aname, const MP_Path* path,
		MP_Integer nth_element = -1);
	STDMETHOD(GetAttribute)(
		const MP_AName* aname, MP_AValue* rtn_avalue = NULL,
		MP_Integer nth_element = -1);
	STDMETHOD(GetAttributeF)(
		const MP_AName* aname, const MP_Path* path,
		MP_Integer nth_element = -1);
	STDMETHOD(EnumAttribute)(MP_AName* aname, MP_Integer namesize);
	STDMETHOD(CanLinkChild)(
		MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs = NULL);
	STDMETHOD(LinkChild)(
		MPCObject* obj, MP_Integer nth, MP_Attrs* part_attrs = NULL);
	STDMETHOD_(MPCObject*, UnlinkChild)(MP_Integer nth, HRESULT* phres = NULL);
	STDMETHOD(GetNumberOfChildren)();
	STDMETHOD_(MPCObject*, GetNthChild)(MP_Integer nth, HRESULT* phres = NULL);
	STDMETHOD(ChangeChildOrder)(
		MP_Integer src_nth, MP_Integer dst_nth = MP_TOPMOST);
	STDMETHOD(GetChildPosition)(MPCObject* child_obj);
	STDMETHOD_(MPCObject*, GetParent)();
	STDMETHOD_(MPCObject*, GetMP)();
	STDMETHOD(SetPartAttribute)(
		MP_Integer nth_part, const MP_AName* aname,
		const MP_AValue* avalue = NULL, MP_Integer nth_element = -1);
	STDMETHOD(GetPartAttribute)(
		MP_Integer nth_part, const MP_AName* aname,
		MP_AValue* rtn_avalue = NULL, MP_Integer nth_element = -1);
	STDMETHOD(EnumPartAttribute)(
		MP_Integer nth_part, MP_AName* aname, MP_Integer namesize);
	STDMETHOD(SetAttributeFW)(
		const MP_AName* aname, const MP_WPath* path,
		MP_Integer nth_element = -1);
	STDMETHOD(GetAttributeFW)(
		const MP_AName* aname, const MP_WPath* path,
		MP_Integer nth_element = -1);

	// 	MPCMedia
	STDMETHOD(OnDraw)(MP_Canvas* canvas, MPCObject* parent=NULL);
	STDMETHOD(OnPrint)(MP_Canvas* canvas, MPCObject* parent=NULL);
	STDMETHOD(CanRotate)(MP_Integer degree);
	STDMETHOD(Rotate)(MP_Integer degree);

#ifndef SFXVW
	// IHeteroBodyCont
	STDMETHOD(Update)(const char* infPathName, int page);
	// 09.07.14 - M.Chikyu UNICODE対応
	STDMETHOD(UpdateW)(const MP_WPath* infPathName, int page);

	STDMETHOD(SetPD)(MP_PD* pd, MP_Dim dim);
#endif //SFXVW
	STDMETHOD_(MP_PD*,GetPD)(HRESULT* phres = NULL);

	class Content : public IContent {
	public:
		HeteroBodyCont* m_this;
		STDMETHOD(PreAttach)(
			MPCObject* parent, MP_Integer nth, MP_Attrs* part_attrs);
		STDMETHOD(PostAttach)(
			MPCObject* parent, MP_Integer nth, MP_Attrs* part_attrs);
		STDMETHOD(PreDetach)(MPCObject* parent, MP_Integer nth);
		STDMETHOD(PostDetach)(MPCObject* parent, MP_Integer nth);
	} m_content;

	class PersistMPCObject : public IPersistMPCObject {
	public:
		HeteroBodyCont* m_this;
		STDMETHOD(IsDirty)();
		STDMETHOD_(IStgObject*, Synchronize)();
		STDMETHOD(SaveCompleted)(IStgObject* stgobj);
		STDMETHOD(OnCreate)(IStgObject* stgobj, MPCSession* session);
		STDMETHOD(OnLoad)(
			IStgObject* stgobj, MPCObject* parent, MPCSession* session);
		STDMETHOD(OnReload)(
			IStgObject* stgobj, MPCObject* parent, MPCSession* session);
		STDMETHOD(UnloadChild)(MP_Integer nth = -1);
		STDMETHOD(Unload)(MPCObject* parent);
	} m_persist;

#ifndef SFXVW
	class Convert : public MPCConvertVersion {
	public:
		HeteroBodyCont* m_this;
		STDMETHOD(DoConvert)(MP_Integer version=0);
	} m_convert;
#endif //SFXVW


	MPCSession* m_session;
	MPCObject* m_parent;
	IStgObject* m_storage;
	int m_dirty;

	// テキスト検索用インタフェース
	CBodyContentText* m_bodyContentText;
	CBodyContentSelectText* m_bodyContentSelectText;
	CBodyContentFind* m_bodyContentFind;

	CBodyContentPDCache* GetBodyContentPDCache();

	HeteroBodyCont();
	~HeteroBodyCont();

private:
	// AR10940
	//	m_bodyContentPDCacheは必要になったら生成するので
	//	他クラスからはGetBodyContentPDCache()でアクセスさせる
	CBodyContentPDCache* m_bodyContentPDCache;
};

MPC_EXTERN_GUID(CLSID_REFCHILD, 0x1001);
#define ANAME_REFID "refid"

#endif // HCDPRVT_H

// CHANGE LOG
// 96.3.3 - Matsumoto - 生成
// 96.7.3 - Nagano - SetPD()追加
// 97.1.21 - RegisterForGUIを実装
// 97.9.12 - Matsumoto - GetPDを追加
// 97.10.21 - Matsumoto - テキスト検索用インタフェース追加
// 97.12.12 - Ichiriki - AR1808 V3変換 MPCConvertVersionの追加
// 98.6.16 - Ichiriki - V3.1:6/16設計ボード〜EXTERN_GUIDの定義変更
// 99.6.10 - Ichiriki - V4検索追加（6/10佐藤 Notesメールの依頼に対応）
// 99.9.6 - Ichiriki - V4 AR4745 自己解凍文書用ビューワサイズ削減
// 2002.04.17 - Komoda - V5.0 HeteroContDocにm_fBreakRegenerationを追加
// 2004.03.29 - Komoda - V6.0 Find6対応
// 2004.09.30 - Tashiro - AR10940 95系で多ページ文書のクローズに時間がかかる現象の回避
// 2007.12.06 - Komoda - V7.0 Unicode I/Fの追加
// 2008.09.01 - Tashiro - V7.0 AR15514 SynchronizeしないでIStgObjectを取得する新I/Fの実装を追加
