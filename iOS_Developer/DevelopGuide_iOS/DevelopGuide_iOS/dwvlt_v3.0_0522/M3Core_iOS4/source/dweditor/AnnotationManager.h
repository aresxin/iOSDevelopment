/*
 * AnnotationManager.h
 *
 *  Created on: 2011/07/22
 *      Author: bito
 */

#ifndef ANNOTATIONMANAGER_H_
#define ANNOTATIONMANAGER_H_

#include "mpc_api.h"
#include "anparameter.h"
#include "corecmmdef.h"

// 全てのアノテーションのマネージャクラスの基本となるクラス
class AnnotationManager
{
// 全アノテーションの共通実装
public:
	HRESULT CreateAnnotation(MPCSession* session, AnnotationParameter* param, MPCObject** object);
	HRESULT GetAnnotationParameter(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAnnotationParameter(MPCObject* object, AnnotationParameter* param);
	
private:
	HRESULT UpdateInfo(MPCObject* object, AnnotationParameter* param);
	HRESULT IsCorrectFiliation(MPCObject* object);

protected:
	HRESULT UpdatePD(MPCObject* object, AnnotationParameter* param);
	
// アノテーションの種類に依存した固有実装(継承クラスで実装)
private:
	virtual HRESULT GetAttribute(MPCObject* object, AnnotationParameter* param) = 0;
	virtual HRESULT SetAttribute(MPCObject* object, AnnotationParameter* param) = 0;
	virtual HRESULT GetAnnotationPosition(AnnotationParameter* param) = 0;
	virtual MP_ObjectType GetAnnotationType(void) = 0;
	virtual POINT GetPosition(AnnotationParameter* param) = 0;

	virtual HRESULT UpdateParentPD(MPCObject* parent, MPCObject* object, AnnotationParameter* param) { return MP_E_INVALIDARG; };
	virtual HRESULT UpdateInfo(MPCObject* object, MPCObject* child, AnnotationParameter* param) { return MP_E_INVALIDARG; };
};

#endif /* ANNOTATIONMANAGER_H_ */
