/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_Config.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */


#ifndef _OL_CONFIG_H_INCLUDED_
#define _OL_CONFIG_H_INCLUDED_

/* 
 *   confing 
 */
/* #define OL_CONTEXT_MI_LINK */
#define OL_CMP_WEIGHT
/* #define OL_RAW_PATTERN */

/* 
 *   debug setting 
 */
#ifdef OL_DEBUG
/* #     define OL_DEBUG_FONTSERVER */
#       define OL_DEBUG_PATTERN    
#       define OL_DEBUG_PATTERN_EDGELISTPATTERN
#       define OL_DEBUG_PATH
#else
#       undef OL_DEBUG_FONTSERVER
#       undef OL_DEBUG_PATTERN
#       undef OL_DEBUG_PATH
#endif //OL_DEBUG

/* #define OL_COVERAGE */


/* 
 *   defalult 
 */
#define OL_DEFAULT_PATTERNLISTSIZE            1000
#define OL_DEFAULT_PATHSIZE                   750
#define OL_DEFAULT_INST_SIZE                  10000

#define OL_DEFAULT_CONTOUR_WIDTH              1
#define OL_DEFAULT_BOLD_DIFF                  2       /* power of 2 is recomended */
#define OL_DEFAULT_CONTOUR_DIFF               1


#define OL_DEFAULT_SCANCTRL                   OL_CC_SCANCTRL_ON
#define OL_DEFAULT_GRIDFIT                    OL_CC_GRIDFIT_OFF
#define OL_DEFAULT_FILLRULE                   OL_CC_FILLRULE_NZW
#define OL_DEFAULT_PAINT                      OL_CC_PAINT_FILL
#ifdef OL_USE_GRAYSCALE
#       define OL_DEFAULT_GRAYSCALE           OL_CC_GRAYSCALE_2
#else
#       define OL_DEFAULT_GRAYSCALE           OL_CC_GRAYSCALE_1
#endif //OL_USE_GRAYSCALE
#define OL_DEFAULT_OUTPUTFORMAT               OL_CC_EDGELIST
/* #define OL_DEFAULT_OUTPUTFORMAT             OL_CC_BITMAP */
#define OL_DEFAULT_SCANCTRL_THRESHOLD         70

#define OL_BOLDTHRESHOLD		      10 /* Globe setting */
#define OL_BOLDTYPE			      3  /* heisei (Globe setting) */
/* #define OL_BOLDTYPE			      4   ryobi */



#endif //_OL_CONFIG_H_INCLUDED_
