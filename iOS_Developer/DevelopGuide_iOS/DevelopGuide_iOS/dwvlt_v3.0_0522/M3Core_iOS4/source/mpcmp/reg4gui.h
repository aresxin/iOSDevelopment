// File: REG4GUI.H
// Auther: Hideki Ichiriki
// Copyright(C) 1996 by Fuji Xerox Co,. Ltd. All right reserved.

/*
* 	reg4gui.h : Core model の実装に使う内部用ヘッダ
*/
#ifndef MP_REG4GUI_H
#define MP_REG4GUI_H

#include "mpc_api.h"

mpinterface MPCRegisterForGUI;

MPCRegisterForGUI* ImplRegisterForGUI_Create(MPCObject* mpcobj);
void ImplRegisterForGUI_Destroy(MPCRegisterForGUI* reg4gui);

enum GUINotificationType {
	AAAOnRemoveFromMemory,
		// メモリからの消滅。MPCObject::Destroy() からコールする

	AAAOnChangePresentation,
		// 見栄えの変更。
		//	1. 自分の表示が変わった時 (Media毎に異なる. PDの変化だけとは限らない)
		//	2. 子供の見栄えが変わった時は親の見栄えも変わる
		//			lContainer::PostChangeContent(MP_CONTENTCHANGEINFO_PRESENTATION) で子供の見栄えの変化を知る
		//	3. 子供の寸法が変わった時
		//			lContainer::PostChangeContent(MP_CONTENTCHANGEINFO_DIMENSION)
		//				大きくなった場合は、変更後の寸法
		//				小さくなった場合は、変更前の寸法
		//					（両方の領域を２回発行すればよい）
		//	4. 子供の位置が移動した時
		//			SetPartAttribute("#pos")
		//				移動前と移動後の両方の領域を２回発行する
		//	5. 子供が増減した時
		//			LinkChild / UnlinkChild
	AAAOnChangeDimension,
		// 自分の寸法が変わった時
		//	SetAttribute("#dim")

	AAAOnMoveChild,
		// 子供の位置が移動した時
		//		SetPartAttribute("#pos")	
	AAAOnResizeChild,
		//	子供の寸法が変わった時。引数で変更前の寸法を通知する。
		//	lContainer::PostChangeContent(MP_CONTENTCHANGEINFO_DIMENSION)	
	AAAOnReorderChild,
		// 子供の順序が変わった時
		//		ChangeChildOrder()
	AAAPostLinkChild,
		//子供が増えた時。増えた後で
		// LinkChild()
	AAAPreUnlinkChild,
	AAAPostUnlinkChild
		//子供が減る前後に
		//	UnlinkChild()
};

void SendGUINotification(MPCRegisterForGUI* reg4gui, MPCObject*mpcobj, GUINotificationType type, MPCObject* child, MP_Rect rect = MP_NULL_RECT);

#endif //MP_REG4GUI_H

//
//CHANGE LOG
//96.2.1 - Ichiriki - 作成
//96.6.10 - Ichiriki - Integ用変更
