//
//  DWAnnotationInfo.h
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <Foundation/Foundation.h>

// ------------------------------------------------
// common annotation
@interface DWAnnotationInfo : NSObject {
    int         pageIndex;
    int         annoIndex;
    CGRect      annoRect;
    long        annoType;
	long        pageScale;
    BOOL        isFixed;
}
@property int pageIndex;
@property int annoIndex;
@property CGRect annoRect;
@property long annoType;
@property long pageScale;
@property BOOL isFixed;

@end

// ------------------------------------------------
// Text annotation
@interface DWTextAnnotationInfo : DWAnnotationInfo {
    
}

@end

// ------------------------------------------------
// freehand annotation
typedef unsigned long	COLORREF;
@interface DWFreehandAnnotationInfo : DWAnnotationInfo {
    int             lineWidth;
    COLORREF        lineColor;   
    NSMutableArray* linePoints_;
	
	// wangpp 2012.2.29 start
	// freehand transparent
	BOOL            transparent;
	// wangpp 2012.2.29 end
}
@property int lineWidth;
@property COLORREF lineColor;
@property (nonatomic, readonly) NSMutableArray* linePoints;

// wangpp 2012.2.29 start
// freehand transparent
@property BOOL transparent;
// wangpp 2012.2.29 end

@end

// ------------------------------------------------
// notepade annotation
@interface DWNotepadAnnotationInfo : DWAnnotationInfo {
}

@end

// ------------------------------------------------
// line annotation
@interface DWLineAnnotationInfo : DWAnnotationInfo {
    
}

@end

// ------------------------------------------------
// Rectangle annotation
@interface DWRectangleAnnotationInfo : DWAnnotationInfo {
    
}

@end

// ------------------------------------------------
// Ellipse annotation
@interface DWEllipseAnnotationInfo : DWAnnotationInfo {
    
}

@end

// ------------------------------------------------
// Polygon annotation
@interface DWPolygonAnnotationInfo : DWAnnotationInfo {
    
}

@end

// ------------------------------------------------
// text notepad annotation
@interface DWTextNotepadAnnotationInfo : DWAnnotationInfo {
    COLORREF    notepadColor;
    int         textFontsize;
    COLORREF    textFontColor;
    bool        isAutoResize;
    NSString*   textContent_;
	int         charSet;
	NSString*   textFontName;
	int         pitchAndFamily;
    
    CGSize      textAnnSize;
	
	BOOL        hasTextAnnotation;
    BOOL        isUpdateText;
    // yangjx 2011/09/15 start
    // NS-AR(011/1003/1004) の対応
    int         textAnnotCount;
    // yangjx 2011/09/15 end

}
@property COLORREF notepadColor;
@property int textFontsize;
@property COLORREF textFontColor;
@property bool isAutoResize;
@property CGSize textAnnSize;
@property (nonatomic, retain) NSString* textContent;
@property (nonatomic, retain) NSString* textFontName;
@property int charSet;
@property int pitchAndFamily;
@property BOOL hasTextAnnotation;
@property BOOL isUpdateText;
// yangjx 2011/09/15 start
// NS-AR(011/1003/1004) の対応
@property int textAnnotCount;
// yangjx 2011/09/15 end
@end

// yangjx 2012.4.16 start
// ------------------------------------------------
// Login annotation
@interface DWLoginAnnotationInfo : DWAnnotationInfo {
	int loginAnnIndex;
}
@property int loginAnnIndex;
@end
// yangjx 2012.4.16 end
