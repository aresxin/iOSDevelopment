/*
 * NotepadAnnotationManager.h
 *
 *  Created on: 2011/05/20
 *      Author: bito
 */

#ifndef NOTEPADANNOTATIONMANAGER_H_
#define NOTEPADANNOTATIONMANAGER_H_

#include "AnnotationManager.h"

class NotepadAnnotationManager : public AnnotationManager
{
public:
	HRESULT AddAnnotation(MPCObject* parent, MPCObject* object, MP_Pos position);
	HRESULT RemoveAnnotation(MPCObject* parent, MPCObject* object);
	HRESULT SetAnnotationPosition(MPCObject* parent, MPCObject* object, MP_Pos position);

private:
	HRESULT UpdateInfo(MPCObject* object, MPCObject* child, AnnotationParameter* param);
	HRESULT GetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT GetAnnotationPosition(AnnotationParameter* param);
	MP_ObjectType GetAnnotationType(void);
	POINT GetPosition(AnnotationParameter* param);
};

#endif /* NOTEPADANNOTATIONMANAGER_H_ */
