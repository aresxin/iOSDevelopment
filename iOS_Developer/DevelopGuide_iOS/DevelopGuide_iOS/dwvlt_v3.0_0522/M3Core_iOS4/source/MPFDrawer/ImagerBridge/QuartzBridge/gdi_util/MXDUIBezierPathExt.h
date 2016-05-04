//
//  MXDUIBezierPathExt.h
//  QuartzBridge(iOS4)
//
//  Created by jonah on 10-9-12.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MXDUIBezierPathPoint.h"

@interface MXDUIBezierPathExt : NSObject {
	int _elementCount;
	NSMutableArray *_pointsArray;
	UIBezierPath *_tmpBezierPath;
}

+ (MXDUIBezierPathExt*)bezierPath;
+ (MXDUIBezierPathExt*)bezierPathWithRect:(CGRect)rect;

- (void)appendPath:(UIBezierPath *)bezierPath;

// Elements.
- (NSInteger)elementCount;

// `points' should contain space for at least three points.  `points'
// may be NULL.  In the case of NSCurveToBezierPathElement, the order
// of the points is controlPoint1 (points[0]), controlPoint2 (points[1]),
// endPoint (points[2]).
- (NSBezierPathElement)elementAtIndex:(NSInteger)index
					 associatedPoints:(CGPoint*)points;

// Path modifications.
- (MXDUIBezierPathExt*)bezierPathByReversingPath;
- (void)applyTransform:(CGAffineTransform)transform;
- (void)removeAllPoints;

- (void)moveToPoint:(CGPoint)point;

- (void)addLineToPoint:(CGPoint)point;

- (void)addCurveToPoint:(CGPoint)endPoint 
		  controlPoint1:(CGPoint)controlPoint1 
		  controlPoint2:(CGPoint)controlPoint2;

- (void)closePath;

@end
