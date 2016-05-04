//
//  mxd_rgn_utils.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#ifndef MXD_RGN_UTILS_H
#define MXD_RGN_UTILS_H

#include "mxd_original_define.h"


// リージョン用のC関数定義
MXD_RegionData* rgn_allocRegionData( int rectNum );
MXD_RegionData*  rgn_reallocRegionData( MXD_RegionData* rgnDataPtr, int rectNum  );
void	rgn_clearRegionData( MXD_RegionData* rgnDataPtr );
bool	rgn_overwriteRegionData( MXD_RegionData** rgnDataHdl, const MXD_RegionData* srcRgnDataPtr );
bool	rgn_overwirteOptimizedRgnData( MXD_RegionData** rgnDataHdl, const MXD_RegionData* srcRgnDataPtr );
bool	rgn_addRect( const CGRect* rectPtr, MXD_RegionData** rgnDataHdl );
float   rgn_minimumXLineOfHigherTheLine( const MXD_RegionData* rgnDataPtr, float line );
float   rgn_minimumYLineOfHigherTheLine( const MXD_RegionData* rgnDataPtr, float line );
bool	rgn_sliceOutRegionData(
							const MXD_RegionData* rgnDataPtr,
							float   lowerLine,
							float   higherLine,
							MXD_RegionData** resultRgnDataHdl
						);
bool		rgn_copyRegionData(
				const MXD_RegionData*   rgnData1Ptr,
				const MXD_RegionData*   rgnData2Ptr,
				MXD_RegionData**		rgnDataHdl
			);
bool		rgn_andRegionData(
				const MXD_RegionData*   rgnData1Ptr,
				const MXD_RegionData*   rgnData2Ptr,
				MXD_RegionData**		rgnDataHdl
			);
bool		rgn_orRegionData(
				const MXD_RegionData*   rgnData1Ptr,
				const MXD_RegionData*   rgnData2Ptr,
				MXD_RegionData**		rgnDataHdl
			);
bool		rgn_xorRegionData(
				const MXD_RegionData*   rgnData1Ptr,
				const MXD_RegionData*   rgnData2Ptr,
				MXD_RegionData**		rgnDataHdl
			);
bool		rgn_diffRegionData(
				const MXD_RegionData*   rgnData1Ptr,
				const MXD_RegionData*   rgnData2Ptr,
				MXD_RegionData**		rgnDataHdl
			);
bool		equalRgnData( 
				const MXD_RegionData*   rgnData1Ptr,
				const MXD_RegionData*   rgnData2Ptr
			);
#endif // MXD_RGN_UTILS_H
