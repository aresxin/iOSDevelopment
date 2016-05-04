/*
 *  Utility.mm
 *  DWViewer
 *
 *  Created by tongjo on 10-11-14.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Utility.h"

// max view count.
// If change this value, please use singular.
//const int Utility::INIT_VIEW_COUNT = 51;
const int Utility::INIT_VIEW_COUNT = 5;

const float Utility::MIN_SCALE = 1.0f;

const float Utility::MAX_SCALE = 4.0f;

const int Utility::DW_DEFAULT_DPI = 75;

// liuqw 20110622 start
// AR NO.17847 の対応
const int Utility::DW_IPAD_DPI = 132;
const int Utility::DW_IPHONE_DPI = 163;
// liuqw 20110622 end

const float Utility::DEFAULT_DEVICE_SCALE_FACTOR = 1.0f;

float Utility::CURR_DEVICE_SCALE_FACTOR = Utility::DEFAULT_DEVICE_SCALE_FACTOR;

// back ground's cloor
const float Utility::BACK_GROUND_WHITE_COLOR = 255/255.0f;
const float Utility::BACK_GROUND_GRAY_COLOR = 200/255.0f;

// file list 500 limit message font size. add by lixin 20101220
const int Utility::IPHONE_LIMIT_UI_FONT_SIZE = 16;
const int Utility::IPAD_LIMIT_UI_FONT_SIZE = 16;

// FileSort の対応 start
const int Utility::IPHONE_LIMIT_UI_FONT_ATTRIBUTESIZE = 12;
const int Utility::IPAD_LIMIT_UI_FONT_ATTRIBUTESIZE = 12;
// FileSort の対応 end

// 「拡大操作の基準の変更」の対応 start
const int Utility::MAX_SPECIFY_SCALE = 200;
// 「拡大操作の基準の変更」の対応 end

// lixin 20110821 DW_iPhoneViewer_20 start	
// annotation property default setting
/*
const UIColor* Utility::DEFAULT_COLOR_FREEHAND = [[UIColor alloc]initWithRed:(255.0 / 255.0) 
                                                                       green:(255.0 / 255.0) 
                                                                        blue:(0.0 / 255.0)
                                                                       alpha:1];
 */
UIColor* Utility::DEFAULT_COLOR_FREEHAND = [[UIColor alloc]initWithRed:(255.0 / 255.0) 
																 green:(255.0 / 255.0) 
																  blue:(0.0 / 255.0)
																 alpha:1];

const int      Utility::DEFAULT_LINESIZE_FREEHAND = 7;

//  wangpp 2012.2.28 start
// freehand transparent
const BOOL    Utility::DEFAULT_TRANSPARENT_FREEHAND = YES;
// wangpp 2012.2.28 end

/*
const UIColor* Utility::DEFAULT_COLOR_NOTEPAD = [[UIColor alloc]initWithRed:(205.0 / 255.0) 
                                                                      green:(250.0 / 255.0) 
                                                                       blue:(210.0 / 255.0)
                                                                      alpha:1];
*/
UIColor* Utility::DEFAULT_COLOR_NOTEPAD = [[UIColor alloc]initWithRed:(205.0 / 255.0) 
																green:(250.0 / 255.0) 
																 blue:(210.0 / 255.0)
																alpha:1];

/*
const UIColor* Utility::DEFAULT_FONTCOLOR_NOTEPAD = [[UIColor alloc]initWithRed:(0.0 / 255.0)
                                                                          green:(0.0 / 255.0) 
                                                                           blue:(0.0 / 255.0)
                                                                          alpha:1];
*/
UIColor* Utility::DEFAULT_FONTCOLOR_NOTEPAD = [[UIColor alloc]initWithRed:(0.0 / 255.0)
																	green:(0.0 / 255.0) 
																	 blue:(0.0 / 255.0)
																	alpha:1];

const int      Utility::DEFAULT_FONTSIZE_NOTEPAD = 12;

// wangpp 2012.4.13 start
// login
const int      Utility::DEFAULT_INDEX_LOGIN = 0;
// wangpp 2012.4.13 end

// DW_iPhoneViewer_20 end