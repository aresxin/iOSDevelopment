/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_ProcessorViewWinCE.h -- definition of Font Manager 

	Created:	Jun 28, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#include "FM_Define.h"

#ifdef FM_VIEW_WINCE /* defineded in FM_Define.h */

#ifndef _FM_PROCESSORVIEWWINCE_H_INCLUDED_
#define _FM_PROCESSORVIEWWINCE_H_INCLUDED_

#include "FM_Processor.h"
#include "FM_FontRegister.h"
#include "FM_CodeConverter.h"

typedef struct {

    FM_Processor	super;
    FM_PageInfo 	pageInfo;
    FM_Matrix		deviceMatrix;
    FM_Matrix		fontMatrix;
    FM_Attribute 	attribute;
    FM_LogFont		logFont;
    FM_TextAlign	defaultAlign;
    FM_FontRegister	*fontRegister;
	FM_CodeConverter *codeConverter;
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
    long		fontRegisterFlag;
    void		*fontHandle;

} FM_ProcessorViewWinCE;

/* public */
void* 	FM_ProcessorViewWinCE_New(void *MI, void *PM, long resoX, long resoY);
void 	FM_ProcessorViewWinCE_Delete(void *handle);
long 	FM_ProcessorViewWinCE_StartPage(void *handle, FM_PageInfo *pageInfo);
long 	FM_ProcessorViewWinCE_EndPage(void *handle);
long	FM_ProcessorViewWinCE_StartAttribute(void *handle, FM_Attribute *attribute);
long	FM_ProcessorViewWinCE_EndAttribute(void *handle);
long 	FM_ProcessorViewWinCE_SetLogFont(void *handle, FM_LogFont *logFont, FM_Matrix *deviceMatrix);
long 	FM_ProcessorViewWinCE_DrawCodeFont(void *handle, FM_Point *startPoint, 
					   FM_CodeString *codeString, FM_RectOption rectOption, FM_Rect *rectArea, FM_Point *adjustment);
long 	FM_ProcessorViewWinCE_DrawDataFont(void *handle, FM_Point *startPoint, 
					   FM_DataCharacter *dataCharacter, FM_Matrix *deviceMatrix);
long 	FM_ProcessorViewWinCE_StartFontRegister(void *handle);
long 	FM_ProcessorViewWinCE_EndFontRegister(void *handle);
long 	FM_ProcessorViewWinCE_GetFontRegister(void *handle, char **dataAddress, long *numOfChar);

/* private */
long	FM_ProcessorViewWinCE_CreatePitchData(void *handle, 
											  FM_CodeString *codeString, 
											  long numCharacter, 
											  int **pitch);
long	FM_ProcessorViewWinCE_CheckMatrix(void *handle, 
										  FM_Matrix *matrix, 
										  double *angle, 
										  double *scaleX, 
										  double *scaleY);
long	FM_ProcessorViewWinCE_GetNoRotatedDeviceStringArea(void *handle, 
							   unsigned char *unicodeString,
							   int *pitchArray, 
							   int numCharacters,
							   FM_StringArea *area);
long	FM_ProcessorViewWinCE_DecideDrawPoint(void *handle, 
											  FM_CodeString *codeString, 
											  FM_Point *drawPoint, 
											  FM_Point *nextPoint, 
											  FM_StringArea *stringArea);
long FM_ProcessorViewWinCE_MakeClipArea(void *handle, 
										FM_Rect *clipArea, 
										FM_Point *drawPoint, 
										FM_StringArea *stringArea, 
										FM_Rect *clipRect, 
										long *clipType, 
										FM_ClipEdge **clipEdgeArray, 
										long *clipNumEdges,
										unsigned char **clipBuffer);
long FM_ProcessorViewWinCE_RestoreClipArea(void *handle, 
										   FM_Rect *clipRect, 
										   unsigned char *clipBuffer, 
										   FM_ClipEdge *clipEdgeArray, 
										   long clipEdgeNum);
long FM_ProcessorViewWinCE_RegistFontBBox(void *handle, 
					  FM_Point *paintPoint, 
					  FM_CodeString *codeString, 
					  FM_StringArea *stringArea, 
					  int *pitchArray);
long FM_ProsessorViewWinCE_DrawRect(void *handle, 
				    FM_Rect *rectArea, 
				    unsigned char color[3]);
void FM_ProcessorViewWinCE_MultipleMatrix(void *handle, 
											 FM_Matrix *result, 
											 FM_Matrix *left, 
											 FM_Matrix *right);
void FM_ProcessorViewWinCE_MatrixPoint(void *handle, 
									   FM_Matrix *matrix, 
									   FM_Point *point, 
									   FM_Point *ans);

#endif

#endif /* FM_VIEW_WINCE */
