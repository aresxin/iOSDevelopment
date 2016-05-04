//
//  MXDUIBezierPathPoint.h
//  QuartzBridge(iOS4)
//
//  Created by jonah on 10-9-12.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "buildenvironment.h"

/*
typedef enum {
    NSMoveToBezierPathElement,
    NSLineToBezierPathElement,
    NSCurveToBezierPathElement,
    NSClosePathBezierPathElement
} NSBezierPathElement;
*/

@interface MXDUIBezierPathPoint : NSObject {
	NSPoint point0;
	NSPoint point1;
	NSPoint point2;
	NSBezierPathElement elementtype;
}

- (id)init;
- (id)initWithPoint0:(NSPoint)p point1:(NSPoint)p1 point2:(NSPoint)p2 
		 elementtype:(NSBezierPathElement)type;

- (void)setPoint0:(NSPoint)p;
- (void)setPoint1:(NSPoint)p;
- (void)setPoint2:(NSPoint)p;
- (void)setType:(NSBezierPathElement)type;

- (NSBezierPathElement)getType;
- (NSPoint)getPoint0;
- (NSPoint)getPoint1;
- (NSPoint)getPoint2;

// for test
- (void)dump;

@end
