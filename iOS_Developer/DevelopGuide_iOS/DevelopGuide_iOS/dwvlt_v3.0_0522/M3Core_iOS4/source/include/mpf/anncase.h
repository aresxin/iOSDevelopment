/*
 * anncase.h
 *
 *  Created on: 2012/03/28
 *      Author: Toshiyuki Komoda
 */

#ifndef ANNOTATION_CASE_H_
#define ANNOTATION_CASE_H_

#include "mpc_api.h"


////////////////////////////////////////////////////////////////////////////
// MPFアノテーションケースオブジェクト
//
//  アノテーションケースは、再利用するアノテーションを登録するオブジェクトである
//  アノテーションケースはルートのオブジェクトとして使用する
//
//  LinkChild/UnlinkChildでアノテーションの登録/削除を行う
//  %image属性のSetPartAttribute/GetPartAttributeでプレビュー画像の登録/参照を行う
////////////////////////////////////////////////////////////////////////////

const MP_InterfaceID OT_ANNOTATION_CASE = 0xC049;

MPCObject* CreateAnnotationCase(MP_RefObjectType objectType, HRESULT* phres = 0);

// 対称性のために作成するが、メンバ変数のDestroyで破棄しても可
HRESULT DestroyAnnotationCase(MPCObject* annotationCase);

// プレビュー画像を登録するためのPart属性
static const MP_AName* ANAME_IMAGE = "%image";

////////////////////////////////////////////////////////////////////////////

/* 
 // アノテーションケースの新規作成
 HRESULT hres = 0;
 MPCObject* anncase = session->CreateScratchMPCObject(OT_ANNOTATION_CASE, &hres);
 if (anncase == NULL) error;
 
 // アノテーションの登録
 const int LAST_POS = -1;
 hres = anncase->LinkChild(annotation, LAST_POS);
 if (hres != MP_NOERROR) error;
 
 // プレビュー画像の登録
 MP_AValue avimage;
 avimage.asize = imageSize;
 avimage.atype = MP_A_OCTS;
 avimage.adata = imageData;
 hres = anncase->SetPartAttribute(i, ANAME_IMAGE, &avimage);
 if (hres != MP_NOERROR) error;
 
 // 登録された個数の問合せ
 MP_Integer num = anncase->GetNumberOfChildren();
 if (num < 0) error;
 
 // アノテーションの取り出し
 MPCObject* ann0 = anncase->GetNthChild(i, &hres);
 if (ann0 == NULL) error;
 
 // プレビュー画像の取り出し
 MP_AValue avimage;
 avimage.asize = 0;
 avimage.atype = MP_A_UNKNOWN;
 avimage.adata = NULL;
 hres = anncase->GetPartAttribute(i, ANAME_IMAGE, &avimage);
 if (avimage.asize <= 0) error;
 
 char* buffer = (char*)malloc(avimage.asize);
 avimage.adata = buffer;
 hres = anncase->GetPartAttribute(i, ANAME_IMAGE, &avimage);
 if (hres != MP_NOERROR) error;
 
 // アノテーションの削除
 MPCObject* ann1 = anncase->UnlinkChild(i, &hres);
 if (ann1 == NULL) error;
 if (ann1 != NULL) ann1->Destroy();
 
 // アノテーションケースのファイル保存とクローズ
 hres = session->SaveAs(anncase, casepath);
 if (hres != MP_NOERROR) error;
 session->CloseFile(anncase, 0);
 
 
 // アノテーションケースファイルのオープン
 MPCObject* anncase = session->OpenFile(casepath, &hres, MP_UPDATE);
 if (anncase == NULL) error;
 
 // アノテーションケースファイルの更新保存とクローズ
 hres = session->Save(anncase);
 if (hres != MP_NOERROR) error;
 session->CloseFile(anncase, 0);
 
 */

#endif /* ANNOTATION_CASE_H_ */
