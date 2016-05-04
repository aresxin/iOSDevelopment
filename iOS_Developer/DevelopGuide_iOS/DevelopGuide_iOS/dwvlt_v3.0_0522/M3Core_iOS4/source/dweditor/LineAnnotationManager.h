/*
 * LineAnnotationManager.h
 *
 *  Created on: 2011/05/20
 *      Author: bito
 */

#ifndef LINEANNOTATIONMANAGER_H_
#define LINEANNOTATIONMANAGER_H_

#include "AnnotationManager.h"

class LineAnnotationManager : public AnnotationManager
{
private:
	HRESULT GetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT SetAttribute(MPCObject* object, AnnotationParameter* param);
	HRESULT GetAnnotationPosition(AnnotationParameter* param);
	MP_ObjectType GetAnnotationType(void);
	POINT GetPosition(AnnotationParameter* param);
};

#endif /* LINEANNOTATIONMANAGER_H_ */
