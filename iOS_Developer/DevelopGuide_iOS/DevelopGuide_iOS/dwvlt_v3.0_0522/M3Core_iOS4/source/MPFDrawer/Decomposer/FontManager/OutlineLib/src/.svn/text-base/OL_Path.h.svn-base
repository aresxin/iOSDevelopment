/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_Path.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */

#ifndef _OL_PATH_H_INCLUDED_
#define _OL_PATH_H_INCLUDED_


#include "OL_Config.h"
#include "OL_Types.h"
#include "OL_TypesExt.h"
#include "OL_Common.h"
#include "OL_Error.h"
#include "OL_Context.h"


#define OL_OFF_CURVE		0x00
#define OL_ON_CURVE		0x01

#define	OL_TT_OFFPOINT		(0x00)
#define	OL_TT_ONPOINT		(0x01)
#define	OL_TT_STARTPOINT	(0x10)
#define	OL_TT_ENDPOINT		(0x20)
#define OL_TT_SEPOINT		(0x30)
#define	OL_TT_STARTPOINT_OFF	(0x10)
#define	OL_TT_STARTPOINT_ON	(0x10 | 0x01)
#define OL_TT_ENDPOINT_OFF	(0x20)
#define OL_TT_ENDPOINT_ON	(0x20 | 0x01)
#define OL_TT_POINTFLAG		(0x0F)
#define OL_TT_BOUNDFLAG		(0xF0)


typedef struct OL_Position_t {
    OL_REAL	x, y;
} OL_Position;


typedef struct OL_Point_t {
    OL_REAL		org_x, org_y;
    OL_REAL		x, y;
    OL_SHORT		ix, iy;
    OL_BYTE		attribute;
    OL_BYTE		group_number;
} OL_Point;


typedef struct OL_Segment_t {
    OL_SegmentType	type;
    OL_Position		pos[3];
} OL_Segment;


typedef struct Flib_Path_t {
    OL_Context		*context;
    OL_ULONG		num_of_point;
    OL_ULONG		max_num_of_point;
    OL_MATRIX32		mtx;
    OL_Point		*point;
    OL_Point		*max_point;
    OL_Point		*read_ptr;
    OL_Point		*write_ptr;
    OL_Point		*start_point;
    OL_Point		dummy;
    OL_STATUS		status;
} OL_Path;
    

OL_Path*	OL_Path_New(OL_Context *context, OL_ULONG n);
OL_VOID		OL_Path_Delete(OL_Path *handle);
OL_STATUS	OL_Path_Initialize(OL_Path *handle, OL_ULONG n);
OL_VOID		OL_Path_Scale(OL_Path *handle, OL_MATRIX32 *m);
OL_VOID		OL_Path_GetMetrics(OL_Path *handle, OL_MetricsInfo *m_info);
OL_INT		OL_Path_GetNPoint(OL_Path *handle);
OL_VOID		OL_Path_GetPoint(OL_Path *handle, OL_Point *p);
OL_VOID		OL_Path_PutPoint(OL_Path *handle, OL_Point *p);
OL_VOID		OL_Path_GetPoint2(OL_Path *handle, OL_ULONG n, OL_Point *p);
OL_VOID		OL_Path_PutPoint2(OL_Path *handle, OL_ULONG n, OL_Point *p);
OL_VOID		OL_Path_PutXPoint(OL_Path *handle, OL_ULONG n, OL_Point *p);
OL_VOID		OL_Path_PutYPoint(OL_Path *handle, OL_ULONG n, OL_Point *p);
OL_VOID		OL_Path_PutAttribute(OL_Path *handle, OL_ULONG n, OL_Point *p);
OL_VOID		OL_Path_PutGroup(OL_Path *handle, OL_ULONG n, OL_Point *p);
OL_VOID		OL_Path_PutPath(OL_Path *handle, OL_Path *path);
OL_VOID		OL_Path_PutSegment(OL_Path *handle, OL_Segment *s);
OL_STATUS	OL_Path_Resize(OL_Path *handle, OL_ULONG n);


#endif  //_OL_PATH_H_INCLUDED_
