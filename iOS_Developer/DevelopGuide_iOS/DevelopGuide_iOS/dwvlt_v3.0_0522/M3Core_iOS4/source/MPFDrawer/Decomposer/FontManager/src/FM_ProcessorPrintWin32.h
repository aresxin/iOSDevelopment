/*
	Copyright (C) Fuji Xerox Co; Ltd. 2004. All rights reserved.
 
	FM_ProcessorPrintWin32.c -- definition of Font Manager 

	Created:	Oct 20, 2002 By Kunihiko Kobayashi 
	Modified:   Apr 12, 2004 By Kunihiko Kobayashi, AR1473

*/


#include "FM_Define.h"

#ifdef FM_LINK_PROCESSORPRINTWIN32  /* defined in FM_Define.h */

#ifndef _FM_PROCESSORPRINTWIN32_H_INCLUDED_
#define _FM_PROCESSORPRINTWIN32_H_INCLUDED_

#include "FM_Processor.h"
#include "FM_FontRegister.h"
#include "FM_DataFontSupport.h"
#include "FM_FontCache.h"
#include "OL_OutlineLib.h"


/* WINDOWS SYSTEM */
typedef enum {
	FM_WIN32_SYSTEM_UNDEF		= 0,
	FM_WIN32_SYSTEM_WIN95,
	FM_WIN32_SYSTEM_WIN98,
	FM_WIN32_SYSTEM_WINME,
	FM_WIN32_SYSTEM_WINNT4,
	FM_WIN32_SYSTEM_WIN2K,
	FM_WIN32_SYSTEM_WINXP
} FM_WIN32_SYSTEM;


typedef struct {

    FM_Processor	super;
    FM_PageInfo 	pageInfo;
    FM_Matrix		deviceMatrix;
    FM_Matrix		fontMatrix;
    FM_Attribute	attribute;
    FM_LogFont		logFont;
    FM_TextAlign	defaultAlign;
    FM_FontRegister	*fontRegister;
    FM_DataFontSupport	*dataFontSupport;
    FM_FontCache	*fontCache;
    OL_OutlineLib	*OL;
    long		resolutionX;
    long		resolutionY;
    double		deviceAngle;
    double		deviceScaleX;
    double		deviceScaleY;
    double		fontAngle;
    double		fontScaleX;
    double		fontScaleY;
    double		finalAngle;
    double		finalScaleX;
    double		finalScaleY;
	float		pointSize;
    long		fontRegisterFlag;
    long		outlineFlag;
	long		emulationSet;
	long		drawingMode;

    void		*fontHandle;
    void		*memoryHandle;
    void		*deviceHandle;

	char		*cacheAddress;
	long		cacheHit;
	long		cacheMiss;

	long		systemVersion;

} FM_ProcessorPrintWin32;



/* public */
void* 	FM_ProcessorPrintWin32_New(void *MI, void *PM, long resoX, long resoY);
void 	FM_ProcessorPrintWin32_Delete(void *handle);
long 	FM_ProcessorPrintWin32_StartPage(void *handle, FM_PageInfo *pageInfo);
long 	FM_ProcessorPrintWin32_EndPage(void *handle);
long	FM_ProcessorPrintWin32_StartAttribute(void *handle, FM_Attribute *attribute);
long	FM_ProcessorPrintWin32_EndAttribute(void *handle);
long 	FM_ProcessorPrintWin32_SetLogFont(void *handle, FM_LogFont *logFont, FM_Matrix *deviceMatrix);
long 	FM_ProcessorPrintWin32_DrawCodeFont(void *handle, FM_Point *startPoint, 
					    FM_CodeString *codeString, FM_RectOption rectOption, FM_Rect *rectArea);
long 	FM_ProcessorPrintWin32_DrawDataFont(void *handle, FM_Point *startPoint, 
					    FM_DataCharacter *dataCharacter, FM_Matrix *deviceMatrix);
long 	FM_ProcessorPrintWin32_StartFontRegister(void *handle);
long 	FM_ProcessorPrintWin32_EndFontRegister(void *handle);
long 	FM_ProcessorPrintWin32_GetFontRegister(void *handle, char **dataAddress, long *numOfChar);



/* private */
long	FM_ProcessorPrintWin32_CreatePitchData(void *handle, 
					       FM_CodeString *codeString, 
					       int **pitch);
long	FM_ProcessorPrintWin32_CheckMatrix(void *handle, 
					   FM_Matrix *matrix, 
					   double *angle, 
					   double *scaleX, 
					   double *scaleY);
long	FM_ProcessorPrintWin32_GetNoRotatedDeviceStringArea(void *handle, 
							    FM_CodeString *codeString, 
							    int *pitchArray, 
							    FM_StringArea *area);
long	FM_ProcessorPrintWin32_DecideDrawPoint(void *handle, 
					       FM_CodeString *codeString, 
					       FM_Point *drawPoint, 
					       FM_Point *nextPoint, 
					       FM_StringArea *stringArea);
void	FM_ProcessorPrintWin32_MultipleMatrix(void *handle, 
					      FM_Matrix *result, 
					      FM_Matrix *left, 
					      FM_Matrix *right);
void 	FM_ProcessorPrintWin32_MatrixPoint(void *handle, 
					   FM_Matrix *matrix, 
					   FM_Point *point, 
					   FM_Point *ans);
long 	FM_ProcessorPrintWin32_DrawText(void *handle, 
					FM_Point *paintPoint, 
					FM_CodeString *codeString, 
					int *pitchArray);
long 	FM_ProcessorPrintWin32_DrawCharacterByBitmap(void *handle, 
						     unsigned char code[2], 
						     FM_Matrix *matrix, 
						     FM_Encoding codeEncoding, 
						     double drawX, 
						     double drawY);  
long 	FM_ProcessorPrintWin32_DrawCharacterByOutline(void *handle, 
						      unsigned char code[2], 
						      FM_Matrix *matrix, 
						      FM_Encoding codeEncoding, 
						      double drawX, 
						      double drawY);
long    FM_ProcessorPrintWin32_ConvertOutline(void *handle, 
					      void *bufferGDI, 
					      int bufferGDISize, 
					      OL_Outline *outline);
long	FM_ProcessorPrintWin32_MatrixOutline(void *handle, 
					     OL_Outline *outline, 
					     FM_Matrix *matirx);
long 	FM_ProcessorPrintWin32_DrawTextBackground(void *handle, 
						  FM_Point *paintPoint, 
						  FM_StringArea *stringArea, 
						  unsigned char bkColor[3]);
long	FM_ProcessorPrintWin32_DrawStrikeout(void *handle, 
					     FM_Point *paintPoint, 
					     FM_StringArea *stringArea);
long	FM_ProcessorPrintWin32_DrawUnderline(void *handle, 
					     FM_Point *paintPoint, 
					     FM_StringArea *stringArea);
long 	FM_ProcessorPrintWin32_RegistFontBBox(void *handle, 
					      FM_Point *paintPoint, 
					      FM_CodeString *codeString, 
					      FM_StringArea *stringArea, 
					      int *pitchArray);
long 	FM_ProcessorPrintWin32_MakeClipArea(void *handle, 
					    FM_Rect *clipArea, 
					    long *clipSave);
long 	FM_ProcessorPrintWin32_DrawRect1(void *handle, 
					FM_Point point[4],
					long rotateFlag);
long 	FM_ProsessorPrintWin32_DrawRect2(void *handle, 
					 FM_Rect *rectArea, 
					 unsigned char color[3]);
void 	FM_ProcessorPrintWin32_PointFixedToDouble(void *handle, 
						  void *GDIpointfx, 
						  double *x, 
						  double *y);

/* added for TextOut() */

long	FM_ProcessorPrintWin32_DecideDrawPointBM(void *handle, 
					       FM_CodeString *codeString, 
					       FM_Point *drawPoint, 
					       FM_Point *nextPoint, 
					       FM_StringArea *stringArea);
long 	FM_ProcessorPrintWin32_DrawTextBM(void *handle, 
					FM_Point *paintPoint, 
					FM_CodeString *codeString, 
					int *pitchArray);
long 	FM_ProcessorPrintWin32_DrawCharacterByTextOut(void *handle, 
						     unsigned char code[2], 
						     FM_Matrix *matrix, 
						     FM_Encoding codeEncoding, 
						     double drawX, 
						     double drawY); 

long	FM_ProcessorPrintWin32_GetSystemVersion(void *handle);
					
#endif

#endif /* FM_PRINT_WIN32 */
