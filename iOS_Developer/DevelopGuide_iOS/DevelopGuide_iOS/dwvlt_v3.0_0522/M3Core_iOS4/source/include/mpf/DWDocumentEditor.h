/*
 *  DWDocumentEditor.h
 *  dwcore(iOS4)
 *
 *  Created by bito on 11/06/01.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DWDOCUMENTEDITOR_H_
#define DWDOCUMENTEDITOR_H_

#include "mpc_api.h"
#include "anparameter.h"

class DWDocumentEditor
{
public:
	DWDocumentEditor(void) {};
	virtual ~DWDocumentEditor(void) {};
	
	virtual HRESULT CreateAnnotation(MPCSession* session, AnnotationParameter* param, MPCObject** object) = 0;
	virtual HRESULT GetAnnotationParameter(MPCObject* object, AnnotationParameter* param) = 0;
	virtual HRESULT SetAnnotationParameter(MPCObject* object, AnnotationParameter* param) = 0;
	virtual HRESULT AddAnnotation(MPCObject* parent, MPCObject* object, MP_Pos position) = 0;
	virtual HRESULT RemoveAnnotation(MPCObject* parent, MPCObject* object) = 0;
	virtual HRESULT DestroyAnnotation(MPCObject* object) = 0;
	virtual HRESULT CopyAnnotation(MPCObject* src, MPCObject** dst) = 0;
	virtual HRESULT SetAnnotationPosition(MPCObject* parent, MPCObject* object, MP_Pos position) = 0;
	virtual HRESULT HowManyAnnotations(MPCObject* object, int* num) = 0;
	virtual HRESULT GetAnnotationInformation(MPCObject* object, int nth, MP_ObjectType* type, MP_Rect* rect) = 0;
	virtual HRESULT GetAnnotation(MPCObject* parent, int nth, MPCObject** object) = 0;
};

DWDocumentEditor* CreateDWDocumentEditor(void);
void DestroyDWDocumentEditor(DWDocumentEditor* editor);

#endif /* DWDOCUMENTEDITOR_H_ */