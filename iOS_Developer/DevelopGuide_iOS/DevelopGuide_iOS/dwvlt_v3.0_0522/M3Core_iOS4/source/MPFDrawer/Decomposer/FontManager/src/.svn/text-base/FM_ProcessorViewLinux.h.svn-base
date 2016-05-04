/* Copyright (C) 2003 by Fuji Xerox Co.,Ltd All rights reserved. */

/**
 *  @file    FM_ProcessorViewLinux.h
 *  @brief   Linux用フォント処理関数定義.
 *
 *  @author  DPSC サービス開発部 第3サービス開発室 TD-G 山本紀夫
 *  @version 1.0
 *  @date    2003年4月8日
 */

#ifndef FM_PROCESSOR_VIEW_LINUX_H_INCLUDED
#define FM_PROCESSOR_VIEW_LINUX_H_INCLUDED

#include "FM_Define.h"

#ifdef FM_VIEW_LINUX /* defined in FM_Define.h */

#include "FM_CodeConverter.h"
#include "FM_FontRegister.h"
#include "FM_Processor.h"
#include "FM_Type.h"
#include "FM_TypeExt.h"

typedef struct {
    FM_Processor super;
    FM_PageInfo pageInfo;
    FM_Matrix deviceMatrix;
    FM_Matrix fontMatrix;
    FM_Attribute attribute;
    FM_LogFont logFont;
    FM_TextAlign defaultAlign;
    FM_FontRegister *fontRegister;
    FM_CodeConverter *codeConverter;
    long resolutionX;
    long resolutionY;
    double deviceAngle;
    double deviceScaleX;
    double deviceScaleY;
    double fontAngle;
    double fontScaleX;
    double fontScaleY;
    double finalAngle;
    double finalScaleX;
    double finalScaleY;
    long fontRegisterFlag;
    void *fontHandle;
            /* 最終的には, この変数経由でImagerオブジェクトをもらい,
               IMG_DrawFont関数でフォント描画する予定. */
} FM_ProcessorViewLinux;

/* public */
void *FM_ProcessorViewLinux_New(void *MI, void *PM, long resoX, long resoY);
void FM_ProcessorViewLinux_Delete(void *handle);
long FM_ProcessorViewLinux_StartPage(void *handle, FM_PageInfo *pageInfo);
long FM_ProcessorViewLinux_EndPage(void *handle);
long FM_ProcessorViewLinux_StartAttribute(void *handle,
                                            FM_Attribute *attribute);
long FM_ProcessorViewLinux_EndAttribute(void *handle);
long FM_ProcessorViewLinux_SetLogFont(void *handle, FM_LogFont *logFont,
                                            FM_Matrix *deviceMatrix);
long FM_ProcessorViewLinux_DrawCodeFont(void *handle,
                                FM_Point *startPoint, FM_CodeString *codeString,
                                FM_RectOption rectOption, FM_Rect *rectArea,
                                FM_Point *adjustment);
long FM_ProcessorViewLinux_DrawDataFont(void *handle, FM_Point *startPoint,
                                        FM_DataCharacter *dataCharacter,
                                        FM_Matrix *deviceMatrix);
long FM_ProcessorViewLinux_StartFontRegister(void *handle);
long FM_ProcessorViewLinux_EndFontRegister(void *handle);
long FM_ProcessorViewLinux_GetFontRegister(void *handle,
                                        char **dataAddress, long *numOfChar);

/* private */
long FM_ProcessorViewLinux_CreatePitchData(void *handle,
                                            FM_CodeString *codeString,
                                            long numCharacter, int **pitch);
long FM_ProcessorViewLinux_CheckMatrix(void *handle,
                                        FM_Matrix *matrix, double *angle,
                                        double *scaleX, double *scaleY);
long FM_ProcessorViewLinux_GetNoRotatedDeviceStringArea(void *handle,
                                unsigned char *unicodeString, int *pitchArray,
                                int numCharacters, FM_StringArea *area);
long FM_ProcessorViewLinux_DecideDrawPoint(void *handle,
                                FM_CodeString *codeString, FM_Point *drawPoint,
                                FM_Point *nextPoint, FM_StringArea *stringArea);
long FM_ProcessorViewLinux_MakeClipArea(void *handle,
            FM_Rect *clipArea, FM_Point *drawPoint, FM_StringArea *stringArea,
            FM_Rect *clipRect, long *clipType, FM_ClipEdge **clipEdgeArray,
            long *clipNumEdges, unsigned char **clipBuffer);
long FM_ProcessorViewLinux_RestoreClipArea(void *handle,
                                FM_Rect *clipRect, unsigned char *clipBuffer,
                                FM_ClipEdge *clipEdgeArray, long clipEdgeNum);
long FM_ProcessorViewLinux_RegistFontBBox(void *handle,
                                FM_Point *paintPoint, FM_CodeString *codeString,
                                FM_StringArea *stringArea, int *pitchArray);
long FM_ProsessorViewLinux_DrawRect(void *handle, FM_Rect *rectArea,
                                            unsigned char color[3]);
void FM_ProcessorViewLinux_MultipleMatrix(void *handle, FM_Matrix *result,
                                            FM_Matrix *left, FM_Matrix *right);
void FM_ProcessorViewLinux_MatrixPoint(void *handle,
                                        FM_Matrix *matrix, FM_Point *point,
                                        FM_Point *ans);

#endif /* FM_VIEW_LINUX */

#endif /* FM_PROCESSOR_VIEW_LINUX_H_INCLUDED */
