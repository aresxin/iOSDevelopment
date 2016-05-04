#ifndef _POLYGON_POINTS_H
#define _POLYGON_POINTS_H

#include "w2mpf_def.h"
#include "anparameter.h"

struct PolygonPoints
{
	SIZE size;
	MyArray<POINT> points;

	PolygonPoints(const MyArray<POINT>& argpoints);
};

#endif
