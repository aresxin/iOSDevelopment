//
//  DWAnnotationInfo.m
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "DWAnnotationInfo.h"

// ------------------------------------------------
// common annotation
@implementation DWAnnotationInfo
@synthesize pageIndex;
@synthesize annoIndex;
@synthesize annoRect;
@synthesize annoType;
@synthesize pageScale;
@synthesize isFixed;
@end

// ------------------------------------------------
// Text annotation
@implementation DWTextAnnotationInfo

@end

// ------------------------------------------------
// freehand annotation
@implementation DWFreehandAnnotationInfo
@synthesize lineWidth;
@synthesize lineColor;
@synthesize linePoints = linePoints_;

// wangpp 2012.2.29 start
// freehand transparent
@synthesize transparent;
// wangpp 2012.2.29 end

- (id) init
{
    if (self = [super init]) {
        linePoints_ = [[NSMutableArray alloc]init];
    }
    
    return self;
}

- (void) dealloc
{
    [linePoints_ release];
    [super dealloc];
}

@end

// ------------------------------------------------
// notepade annotation
@implementation DWNotepadAnnotationInfo

@end

// ------------------------------------------------
// line annotation
@implementation DWLineAnnotationInfo

@end

// ------------------------------------------------
// Rectangle annotation
@implementation DWRectangleAnnotationInfo

@end

// ------------------------------------------------
// Ellipse annotation
@implementation DWEllipseAnnotationInfo

@end

// ------------------------------------------------
// Polygon annotation
@implementation DWPolygonAnnotationInfo

@end

// ------------------------------------------------
// text notepad annotation
@implementation DWTextNotepadAnnotationInfo
@synthesize notepadColor;
@synthesize textFontsize;
@synthesize textFontColor;
@synthesize isAutoResize;
@synthesize textContent = textContent_;
@synthesize textAnnSize;
@synthesize charSet;
@synthesize textFontName;
@synthesize hasTextAnnotation;
@synthesize pitchAndFamily;
@synthesize isUpdateText;
// yangjx 2011/09/15 start
// NS-AR(011/1003/1004) の対応
@synthesize textAnnotCount;
// yangjx 2011/09/15 end

- (void) dealloc
{
	[textFontName release];
    [textContent_ release];
    [super dealloc];
}
@end

// yangjx 2012.4.16 start
// ------------------------------------------------
// Login annotation
@implementation DWLoginAnnotationInfo
@synthesize loginAnnIndex;
@end
// yangjx 2012.4.16 end
