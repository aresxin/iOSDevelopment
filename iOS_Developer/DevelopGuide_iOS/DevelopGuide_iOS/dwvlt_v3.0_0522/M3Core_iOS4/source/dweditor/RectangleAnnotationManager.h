/*
 * RectangleAnnotationManager.h
 *
 *  Created on: 2011/05/20
 *      Author: bito
 */

#ifndef RECTANGLEANNOTATIONMANAGER_H_
#define RECTANGLEANNOTATIONMANAGER_H_

#include "AnnotationManager.h"

class RectangleAnnotationManager : public AnnotationManager
{
private:
	HRESULT GetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT GetAnnotationPosition(AnnotationParameter* param);
	MP_ObjectType GetAnnotationType(void);
	POINT GetPosition(AnnotationParameter* param);
};

#endif /* RECTANGLEANNOTATIONMANAGER_H_ */
