// File: mpc_pchk.h
// Auther: Shinsuke Nakazawa
// Copyright(C) 1999 by Fuji Xerox Co., Ltd. All right reserved.

/*
  V4セキュリティ機能で、認証済みパーミッションチェック＆追加認証の共通コードをまとめた。
  本当はチェックが必要な各オブジェクト内のメソッドに設けたいのだが、
  それでは修正量が膨大になるのでインライン関数化した。
*/

#ifndef _MPC_PCHK_H_
#define _MPC_PCHK_H_

#include "mpc_api.h"
#include "mpc_spi.h"

// ストレージオブジェクトから checkPerm で示すパーミッションが認可されているかどうか聞いて、
// 認可されていなくて bAddAuth が立っていたら追加認証を行う。
inline HRESULT PermCheckFromStgObj(IStgObject* stgobj, MP_Permission checkPerm, BOOL_XD* pbProtected = NULL, BOOL_XD bAddAuth = TRUE)
{
	if (stgobj == NULL)	// ストレージがない場合はスクラッチとみなして常にOK
		return MP_NOERROR;
	// 認証パーミッションチェック
	return stgobj->AddAuthentication(checkPerm);

	// 従来は以下のコード、これを AddAuth 内で行う
/*	MP_Permission authPerm = stgobj->GetAuthenticatedPermission();
	if ((authPerm & checkPerm) != checkPerm) {	// 含まれていなかった
		HRESULT hRes = MP_E_NORPERMISSION;
		if (bAddAuth) {	// 追加認証
			MP_Permission perm = stgobj->GetPermission();
			if ((perm & checkPerm) == checkPerm) {	// もし文書に許可されていたら追加認証を行う
				hRes = stgobj->AddAuthentication(checkPerm);
			}
		}
		if (hRes != MP_NOERROR)
			return MP_E_NORPERMISSION;	// 追加認証失敗(hResを返すべきか？)
	}
	return MP_NOERROR;*/
}

inline HRESULT PermCheckFromMPCObject(MPCObject* obj, MP_Permission checkPerm, BOOL_XD* pbProtected = NULL, BOOL_XD bAddAuth = TRUE)
{
	if (obj == NULL)
		return MP_E_INVALIDARG;
	MPCProfile* profile = NULL;
	if (obj->GetClassID() == CLSID_BINDER) {
		// バインダの場合はいきなりプロファイルを取得できる
		profile = (MPCProfile*)obj->GetInterface(IID_MPCProfile);
	} else {
		MPCObject* mp = obj->GetMP();
		if (mp == NULL)			// MPがない場合はスクラッチとみなしてOKを返す
			return MP_NOERROR;
		profile = (MPCProfile*)mp->GetInterface(IID_MPCProfile);
	}
	if (profile == NULL)	// プロファイルがない場合もOK
		return MP_NOERROR;
	// 認証パーミッションチェック
	return profile->AddAuthentication(checkPerm);

	// 従来は以下のコード、これを AddAuth 内で行う
/*	MP_Permission authPerm = profile->GetAuthenticatedPermission();
	if ((authPerm & checkPerm) != checkPerm) {	// 含まれていなかった
		HRESULT hRes = MP_E_NORPERMISSION;
		if (bAddAuth) {	// 追加認証
			MP_Permission perm = profile->GetPermission();
			if ((perm & checkPerm) == checkPerm) {	// もし文書に許可されていたら追加認証を行う
				hRes = profile->AddAuthentication(checkPerm);
			}
		}
		if (hRes != MP_NOERROR)
			return MP_E_NOPERMISSION;	// 追加認証失敗(hResを返すべきか？)
	}
	return MP_NOERROR;*/
}

#endif // _MPC_PCHK_H_

// CHANGE LOG
// 1999.06.14 - Nakazawa - 新規作成
// 1999.07.06 - Nakazawa - 認証パーミッションチェックでいきなり AddAuthentication を呼ぶように修正(コード量削減がねらい)
// 1999.08.27 - Nakazawa - コメント変更
// 1999.09.03 - Nakazawa - AR4694対応：パーミッションチェックの不具合修正
