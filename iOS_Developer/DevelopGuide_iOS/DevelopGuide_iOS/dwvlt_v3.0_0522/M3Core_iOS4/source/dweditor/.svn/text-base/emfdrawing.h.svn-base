#ifndef EMF_DRAWING_H
#define EMF_DRAWING_H

#include "w2mpf_gdi_def.h"

namespace EMFGenCom {

class EMFCore;

class EMFDrawing
{
public:
	static POINT GetRotatePosRadian(double rotation_radian, POINT origin_point, POINT center_point);
	static double GetLineAngle(POINT start_point, POINT end_point);
	static RECT GetRectFromExtent(int origin_x, int origin_y, int width, int height);
	static void GetCornerPointsFromExtent(int origin_x, int origin_y, int width, int height, POINT* corner_points);
	static int ChangeLineToRectangle(POINT start_point, POINT end_point, double thickness, POINT* corner_points);
	static RECT ChangePointToRect(POINT point, int thickness);
	static int CreateSolidLineWithPoints(int num_points, const POINT *points, int thickness, EMFCore& emf_core);
	static int CreateTransparencyLineWithPoints(int num_points, const POINT *points, int thickness, EMFCore& emf_core);
};

}
#endif
