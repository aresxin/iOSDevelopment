/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_Pattern.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */



#ifndef _OL_PATTERN_H_INCLUDED_
#define _OL_PATTERN_H_INCLUDED_


#include "OL_Config.h"
#include "OL_Types.h"
#include "OL_TypesExt.h"
#include "OL_Common.h"
#include "OL_Path.h"
#include "OL_Composer.h"
#include "OL_Error.h"
#include "OL_Context.h"

enum {
    OL_PATTERN         	= 0,
    OL_PATTERN_BITMAP         = 1,
    OL_PATTERN_BITMAP_GRAY    = 2,
    OL_PATTERN_EDGELIST       = 3,
    OL_PATTERN_EDGELIST_GRAY  = 4
  };

typedef struct OL_Pattern_t {
    OL_Context			*context;
    OL_Path			*path_data;
    OL_UINT32			data_size;
    OL_UINT8			*data;
    OL_ComposerControl		comp_ctrl;
    OL_UINT16			depth;
    CMP_ComposerIF		*composer;
    OL_SHORT			weight_diff;
    OL_Decoration_Param		comp_param;
    OL_STATUS			status;
    OL_PatternType		type;
    OL_UINT32			obtype;
    OL_VOID			*child;
    OL_INT			resolutionX;
    OL_INT			resolutionY;

    OL_STATUS			(*Purge)(struct OL_Pattern_t *handle);
    OL_STATUS			(*BuildPattern)(struct OL_Pattern_t *handle, 
						OL_PatternInfo *p_info, 
						OL_USHORT cs);
#ifdef OL_DEBUG
    OL_VOID 			(*PrintInfo)(struct OL_Pattern_t *handle);
#endif

} OL_Pattern;
    

OL_Pattern* 		OL_Pattern_New(OL_Context *context, OL_UINT32 obtype, OL_INT resoX, OL_INT resoY);
OL_VOID 		OL_Pattern_Delete(OL_Pattern *handle);
OL_STATUS 		OL_Pattern_Init(OL_Pattern *handle, 
					OL_ComposerControl ctlVal, 
					CMP_ComposerIF *comp, 
					OL_Decoration_Param *decParam);
OL_STATUS 		OL_Pattern_Initialize(OL_Pattern *handle);
OL_STATUS		OL_Pattern_PutPath(OL_Pattern *handle, OL_Path *path);
OL_STATUS		OL_Pattern_GetPInfo(OL_Pattern *handle, 
					    OL_PatternInfo *p_info, OL_Path *path);
OL_VOID   		OL_Pattern_PutWeightDiff(OL_Pattern *handle, OL_SHORT w);

/* virtual */
OL_STATUS 		OL_Pattern_Purge(OL_Pattern *handle);
OL_STATUS		OL_Pattern_BuildPattern(OL_Pattern *handle, 
						OL_PatternInfo *p_info, OL_USHORT cs);
					   
#ifdef OL_DEBUG
OL_VOID			OL_Pattern_PrintInfo(OL_Pattern *handle);
#endif


typedef struct OL_PatternBitmap_t {
    OL_Pattern		*super;
    OL_BitmapInfo	*bitmap_info;
    OL_VOID		*child;
} OL_PatternBitmap;

OL_PatternBitmap* 	OL_PatternBitmap_New(OL_Pattern *super, OL_UINT32 obtype);
OL_VOID 		OL_PatternBitmap_Initialize(OL_PatternBitmap *handle);
OL_VOID			OL_PatternBitmap_Delete(OL_PatternBitmap *handle);

/* virtual */
OL_STATUS 		OL_PatternBitmap_Purge(OL_Pattern *handle);
OL_STATUS		OL_PatternBitmap_BuildPattern(OL_Pattern *handle, 
						      OL_PatternInfo *p_info, OL_USHORT cs);
#ifdef OL_DEBUG
OL_VOID			OL_PatternBitmap_PrintInfo(OL_Pattern *handle);
#endif
    




typedef struct OL_PatternBitmapGray_t {
    OL_PatternBitmap 	*super;
} OL_PatternBitmapGray;

OL_PatternBitmapGray 	*OL_PatternBitmapGray_New(OL_PatternBitmap *super);
OL_VOID 		OL_PatternBitmapGray_Delete(OL_PatternBitmapGray *handle);






typedef struct OL_PatternEdgelist_t {
    OL_Pattern        	*super;
    OL_EdgeListInfo	*edgelist_info;
    OL_VOID		*child;
} OL_PatternEdgelist;

OL_PatternEdgelist* 	OL_PatternEdgelist_New(OL_Pattern *super, OL_UINT32 obtype);
OL_VOID 		OL_PatternEdgelist_Initialize(OL_PatternEdgelist *handle);
OL_VOID			OL_PatternEdgelist_Delete(OL_PatternEdgelist *handle);

/* virtual */
OL_STATUS 		OL_PatternEdgelist_Purge(OL_Pattern *handle);
OL_STATUS		OL_PatternEdgelist_BuildPattern(OL_Pattern *handle, 
							OL_PatternInfo *p_info, OL_USHORT cs);
#ifdef OL_DEBUG
OL_VOID 		OL_PatternEdgelist_PrintInfo(OL_Pattern *handle);
#endif



typedef struct OL_PatternEdgelist_gray_t {
    OL_PatternEdgelist        	*super;
} OL_PatternEdgelistGray;

OL_PatternEdgelistGray	*OL_PatternEdgelistGray_New(OL_PatternEdgelist *super);
OL_VOID 		OL_PatternEdgelistGray_Delete(OL_PatternEdgelistGray *handle);


#endif //_OL_PATTERN_H_INCLUDED_
