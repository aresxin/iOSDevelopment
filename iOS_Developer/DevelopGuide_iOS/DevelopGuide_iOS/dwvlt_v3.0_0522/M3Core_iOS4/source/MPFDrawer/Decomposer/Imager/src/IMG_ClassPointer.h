/*
 * Copyright(C) 2001-2002 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_ClassPointer.h - ROP置換処理クラスのポインタの定義
 *
 */

#ifndef INC_IMG_ClassPointer_h
#define INC_IMG_ClassPointer_h

typedef struct img_command							* IMG_CommandPtr;

typedef struct img_commandcheck						* IMG_CommandCheckPtr;
typedef struct img_commandcheckattribute			* IMG_CommandCheckAttributePtr;
typedef struct img_commandcheckcompare				* IMG_CommandCheckComparePtr;
typedef struct img_commandcheckequality				* IMG_CommandCheckEqualityPtr;
typedef struct img_commandcheckgraphicscolor		* IMG_CommandCheckGraphicsColorPtr;
typedef struct img_commandcheckimagecolor			* IMG_CommandCheckImageColorPtr;
typedef struct img_commandcheckimageshapeequality	* IMG_CommandCheckImageShapeEqualityPtr;
typedef struct img_commandcheckgraphicsshapeequality* IMG_CommandCheckGraphicsShapeEqualityPtr;
typedef struct img_commandcheckresult				* IMG_CommandCheckResultPtr;

typedef struct img_commandconverter					* IMG_CommandConverterPtr;
typedef struct img_commandconverterditodm			* IMG_CommandConverterDiToDmPtr;
typedef struct img_commandconverteric				* IMG_CommandConverterIcPtr;
typedef struct img_commandconvertersctopm			* IMG_CommandConverterScToPmPtr;
typedef struct img_commandconverterscvalue			* IMG_CommandConverterScValuePtr;
typedef struct img_commandconverterbrush			* IMG_CommandConverterBrushPtr;
typedef struct img_commandconverterdicolor			* IMG_CommandConverterDiColorPtr;

typedef struct img_commandevaluator					* IMG_CommandEvaluatorPtr;
typedef struct img_commandbilist					* IMG_CommandBiListPtr;
typedef struct img_commandbilistiterator			* IMG_CommandBiListIteratorPtr;
typedef struct img_commandlist						* IMG_CommandListPtr;
typedef struct img_commandlistiterator				* IMG_CommandListIteratorPtr;
typedef struct img_commandlistcondition				* IMG_CommandListConditionPtr;
typedef struct img_commandlistconditionset			* IMG_CommandListConditionSetPtr;
typedef struct img_commandpipegradation				* IMG_CommandPipeGradationPtr;
typedef struct img_commandprocessor					* IMG_CommandProcessorPtr;
typedef struct img_commandsequence					* IMG_CommandSequencePtr;
typedef struct img_drawingattribute					* IMG_DrawingAttributePtr;
typedef struct img_drawsequence						* IMG_DrawSequencePtr;
typedef struct img_pathcommandstorage				* IMG_PathCommandStoragePtr;
typedef struct img_currentclipstorage				* IMG_CurrentClipStoragePtr;

typedef struct img_ropsequence						* IMG_RopSequencePtr;
typedef struct img_ropsequence4step					* IMG_RopSequence4StepPtr;
typedef struct img_ropsequence3step					* IMG_RopSequence3StepPtr;
typedef struct img_ropsequence2step					* IMG_RopSequence2StepPtr;
typedef struct img_ropsequence1step					* IMG_RopSequence1StepPtr;
typedef struct img_ropsequence1stepnodraw			* IMG_RopSequence1StepNoDrawPtr;
typedef struct img_ropreducer						* IMG_RopReducerPtr;

typedef struct img_scanlinecombiner					* IMG_ScanlineCombinerPtr;

typedef struct img_tagfilter						* IMG_TagFilterPtr;
typedef struct img_tagfilter2bit					* IMG_TagFilter2BitPtr;
typedef struct img_tagfilter4bit					* IMG_TagFilter4BitPtr;

typedef struct img_commandfilter					* IMG_CommandFilterPtr;
typedef struct img_commandfilterterminator			* IMG_CommandFilterTerminatorPtr;
typedef struct img_commandfilterropreduction		* IMG_CommandFilterRopReductionPtr;
typedef struct img_commandfiltergradation			* IMG_CommandFilterGradationPtr;
typedef struct img_commandfiltercombiner			* IMG_CommandFilterCombinerPtr;

typedef struct img_thinlinedetection				* IMG_ThinLineDetectionPtr;
typedef struct img_graphicscontext					* IMG_GraphicsContextPtr;

#endif /* INC_IMG_ClassPointer_h */

/*
 * Log
 * 17.Jan.2002 Yozo Kashima 新規作成。
 * 23.Dec.2003 Yozo Kashima AR#1439(Imagerでのタグ拡張のためのクラスを追加)。
 */

/* end of IMG_ClassPointer.h */
