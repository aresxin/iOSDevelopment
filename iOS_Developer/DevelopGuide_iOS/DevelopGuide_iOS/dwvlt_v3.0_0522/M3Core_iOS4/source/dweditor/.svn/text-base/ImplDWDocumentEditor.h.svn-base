/*
 *  ImplDWDocumentEditor.h
 *  dwcore(iOS4)
 *
 *  Created by bito on 11/06/01.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IMPLDWDOCUMENTEDITOR_H_
#define IMPLDWDOCUMENTEDITOR_H_

#include "mpc_api.h"
#include "anparameter.h"
#include "DWDocumentEditor.h"

class ImplDWDocumentEditor : public DWDocumentEditor
{
public:
	ImplDWDocumentEditor(void) {};
	~ImplDWDocumentEditor(void) {};
	
	HRESULT CreateAnnotation(MPCSession* session, AnnotationParameter* param, MPCObject** object);
	HRESULT GetAnnotationParameter(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAnnotationParameter(MPCObject* object, AnnotationParameter* param);
	HRESULT AddAnnotation(MPCObject* parent, MPCObject* object, MP_Pos position);
	HRESULT RemoveAnnotation(MPCObject* parent, MPCObject* object);
	HRESULT DestroyAnnotation(MPCObject* object);
	HRESULT CopyAnnotation(MPCObject* src, MPCObject** dst);
	HRESULT SetAnnotationPosition(MPCObject* parent, MPCObject* object, MP_Pos position);
	HRESULT HowManyAnnotations(MPCObject* object, int* num);
	HRESULT GetAnnotationInformation(MPCObject* object, int nth, MP_ObjectType* type, MP_Rect* rect);
	HRESULT GetAnnotation(MPCObject* parent, int nth, MPCObject** object);
};

HRESULT IsParentObject(MPCObject* object);

#endif /* IMPLDWDOCUMENTEDITOR_H_ */