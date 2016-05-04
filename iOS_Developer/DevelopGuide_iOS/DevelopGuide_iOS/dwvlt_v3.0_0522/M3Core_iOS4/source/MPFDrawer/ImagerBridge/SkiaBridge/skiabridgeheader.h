#pragma once

#ifndef SKBRIDGEHEADER_DEFINED
#define SKBRIDGEHEADER_DEFINED

/* Binary raster ops */
#define ROP2_BLACK            1   /*  0       */
#define ROP2_NOTMERGEPEN      2   /* DPon     */
#define ROP2_MASKNOTPEN       3   /* DPna     */
#define ROP2_NOTCOPYPEN       4   /* PN       */
#define ROP2_MASKPENNOT       5   /* PDna     */
#define ROP2_NOT              6   /* Dn       */
#define ROP2_XORPEN           7   /* DPx      */
#define ROP2_NOTMASKPEN       8   /* DPan     */
#define ROP2_MASKPEN          9   /* DPa      */
#define ROP2_NOTXORPEN        10  /* DPxn     */
#define ROP2_NOP              11  /* D        */
#define ROP2_MERGENOTPEN      12  /* DPno     */
#define ROP2_COPYPEN          13  /* P        */
#define ROP2_MERGEPENNOT      14  /* PDno     */
#define ROP2_MERGEPEN         15  /* DPo      */
#define ROP2_WHITE            16  /*  1       */
#define ROP2_LAST             16

/* COLORREF definition */

 #define COLOR_BLACK		0xFF000000
 #define COLOR_RED			0xFFFF0000
 #define COLOR_GREEN		0xFF00FF00
 #define COLOR_BLUE			0xFF0000FF
 #define COLOR_YELLOW       0xFFFFFF00
 #define COLOR_MAGENTA		0xFFFF00FF
 #define COLOR_CYAN			0xFF00FFFF
 #define COLOR_WHITE		0xFFFFFFFF


#define COLOR_DARK_RED		0xFF808080
#define COLOR_DARK_GREEN	0xFF008000
#define COLOR_DARK_YELLOW	0xFF808000
#define COLOR_DARK_BLUE		0xFF000080
#define COLOR_DARK_MAGENTA	0xFF800080
#define COLOR_DARK_CYAN		0xFF008080
#define COLOR_DARK_GRAY     0xFF808080

#define COLOR_MONEY_GREEN	0xFFC0DCC0
#define COLOR_SKYBLUE		0xFFA6CAF0
#define COLOR_CREAM			0xFFFFFBF0
#define COLOR_MEDIUMGRAY	0xFFA0A0A0
#define COLOR_LIGHTGRAY		0xFFC0C0C0

#define COLOR_UNKNOWN		0xFF008284

// LOG
#include <android/log.h>

#define LOG_BRIDGE_TAG		"BRIDGE_SKIA"
#define SKIABRIDGE_DEBUG_INFO(...)	__android_log_print(ANDROID_LOG_INFO, LOG_BRIDGE_TAG, __VA_ARGS__)

#ifndef SK_A32_SHIFT
	#define SK_A32_SHIFT 24
	#define SK_R32_SHIFT 16
	#define SK_G32_SHIFT 8
	#define SK_B32_SHIFT 0
#endif

// DEBUG define
//#define _SKIADEBUG_FUNCTION_CALL

#endif	// SKBRIDGEHEADER_DEFINED
