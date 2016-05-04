//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//
//  mxd_color.h
//

#ifndef MXD_COLOR_H
#define MXD_COLOR_H

#ifdef __BIG_ENDIAN__
#define MXD32BIT_BLACK_HOST	0xFF000000
#else
#define MXD32BIT_BLACK_HOST	0x000000FF
#endif

#define WMF_BLACK	0x00000000

#ifdef __BIG_ENDIAN__
#define WMF_WHITE	0xFFFFFF00
#else
#define WMF_WHITE	0x00FFFFFF
#endif

#define WMF_RGB_MASK	WMF_WHITE

#endif