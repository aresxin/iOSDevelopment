/*
 * TextAnnotationManager.h
 *
 *  Created on: 2011/05/20
 *      Author: bito
 */

#ifndef TEXTANNOTATIONMANAGER_H_
#define TEXTANNOTATIONMANAGER_H_

#include "AnnotationManager.h"

class TextAnnotationManager : public AnnotationManager
{
private:
	HRESULT GetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT GetAnnotationPosition(AnnotationParameter* param);
	MP_ObjectType GetAnnotationType(void);
	POINT GetPosition(AnnotationParameter* param);
	
	HRESULT UpdateParentPD(MPCObject* parent, MPCObject* object, AnnotationParameter* param);
};

#endif /* TEXTANNOTATIONMANAGER_H_ */
