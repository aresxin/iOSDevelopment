/*
 * FreehandAnnotationManager.h
 *
 *  Created on: 2011/05/20
 *      Author: bito
 */

#ifndef FREEHANDANNOTATIONMANAGER_H_
#define FREEHANDANNOTATIONMANAGER_H_

#include "AnnotationManager.h"

class FreehandAnnotationManager : public AnnotationManager
{
private:
	HRESULT GetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT GetAnnotationPosition(AnnotationParameter* param);
	MP_ObjectType GetAnnotationType(void);
	POINT GetPosition(AnnotationParameter* param);
};

#endif /* FREEHANDANNOTATIONMANAGER_H_ */
