#ifndef EMF_GDI_COMMENT_H
#define EMF_GDI_COMMENT_H

#include "w2mpf_gdi_def.h"

namespace EMFGenCom {

class EMFCore;

class EMFGDIComment
{
public:
	static int Fillpath(EMFCore& emf_core);
	static int Beginpath(EMFCore& emf_core);
	static int Polygon(DWORD num_points, const POINT* points, EMFCore& emf_core);
	static int PolygonS(DWORD num_points, const POINTS* points, EMFCore& emf_core);
	static int Ellipse(const RECT& rect, EMFCore& emf_core);
	static int Ellipse(int left, int top, int right, int bottom, EMFCore& emf_core);
};

}
#endif
