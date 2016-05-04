/*
 * PolygonAnnotationManager.h
 *
 *  Created on: 2011/05/20
 *      Author: bito
 */

#ifndef POLYGONANNOTATIONMANAGER_H_
#define POLYGONANNOTATIONMANAGER_H_

#include "AnnotationManager.h"

class PolygonAnnotationManager : public AnnotationManager
{
private:
	HRESULT GetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT GetAnnotationPosition(AnnotationParameter* param);
	MP_ObjectType GetAnnotationType(void);
	POINT GetPosition(AnnotationParameter* param);
};

#endif /* POLYGONANNOTATIONMANAGER_H_ */
