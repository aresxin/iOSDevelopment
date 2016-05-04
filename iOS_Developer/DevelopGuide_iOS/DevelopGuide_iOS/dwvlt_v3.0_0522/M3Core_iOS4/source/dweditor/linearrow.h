#ifndef _LINE_ARROW_H
#define _LINE_ARROW_H

#include "w2mpf_def.h"

struct LineAnnotationParameter;

struct LineArrow {
	enum { ARROW_POINTS = 3 };
	POINT startPoint;
	POINT endPoint;
	POINT startArrow[ARROW_POINTS];
	POINT endArrow[ARROW_POINTS];
	SIZE size;
	
	LineArrow(const LineAnnotationParameter& param, int& result);
private:
	void arrowPosition(const LineAnnotationParameter& lineParam);
	void normalize(const LineAnnotationParameter& lineParam);
};

#endif
