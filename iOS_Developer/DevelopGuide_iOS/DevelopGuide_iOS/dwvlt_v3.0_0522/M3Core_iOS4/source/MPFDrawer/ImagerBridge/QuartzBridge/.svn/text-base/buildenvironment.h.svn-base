/*
 *  buildenvironment.h
 *  DWQuartzBridge
 *
 *  Created by jonah on 10-8-4.
 *  Copyright 2010 NEUSOFT. All rights reserved.
 *
 */

#ifndef BUILD_ENVIRONMENT_H
#define BUILD_ENVIRONMENT_H

#ifdef _PF_IOS_
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>

#define NSMakePoint	CGPointMake
#define NSMakeSize	CGSizeMake
#define NSMakeRect	CGRectMake

#define NSIntersectsRect CGRectIntersectsRect

#define NSMinX		CGRectGetMinX
#define NSMinY		CGRectGetMinY
#define NSWidth		CGRectGetWidth
#define NSHeight	CGRectGetHeight

typedef UIColor		NSColor;
// typedef UIBezierPath NSBezierPath;

struct RGBColor {
	unsigned short      red;                    /*magnitude of red component*/
	unsigned short      green;                  /*magnitude of green component*/
	unsigned short      blue;                   /*magnitude of blue component*/
};

// define some data type for iphone
typedef enum {
    NSMoveToBezierPathElement,
    NSLineToBezierPathElement,
    NSCurveToBezierPathElement,
    NSClosePathBezierPathElement
} NSBezierPathElement;

typedef CGPoint NSPoint;
typedef CGSize NSSize;
typedef CGRect NSRect;

#else

#include <ApplicationServices/ApplicationServices.h>
#endif

#endif // BUILD_ENVIRONMENT_H

