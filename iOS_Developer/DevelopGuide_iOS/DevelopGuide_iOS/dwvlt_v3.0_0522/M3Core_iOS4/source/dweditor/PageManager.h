/*
 *  PageManager.h
 *  dwcore(iOS4)
 *
 *  Created by bito on 11/05/30.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PAGEMANAGER_H_
#define PAGEMANAGER_H_

#include "mpc_api.h"

class PageManager
{
public:
	HRESULT AddAnnotation(MPCObject* parent, MPCObject* object, MP_Pos position);
	HRESULT RemoveAnnotation(MPCObject* parent, MPCObject* object);
	HRESULT SetAnnotationPosition(MPCObject* parent, MPCObject* object, MP_Pos position);
};

HRESULT IsAnnotationObject(MPCObject* object);

#endif /* PAGEMANAGER_H_ */
