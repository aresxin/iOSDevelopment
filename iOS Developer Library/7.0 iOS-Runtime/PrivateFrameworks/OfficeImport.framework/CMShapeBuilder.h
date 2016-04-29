/* Generated by RuntimeBrowser
   Image: /System/Library/PrivateFrameworks/OfficeImport.framework/OfficeImport
 */

@class NSDictionary, OADOrientedBounds;

@interface CMShapeBuilder : NSObject {
    NSDictionary *_adjustValues;
    int _format;
    OADOrientedBounds *_orientedBounds;
    int _type;
}

+ (struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })canonicalBounds;

- (struct CGAffineTransform { float x1; float x2; float x3; float x4; float x5; float x6; })affineTransform;
- (struct CGPath { }*)copyShapeWithTransform:(struct CGAffineTransform { float x1; float x2; float x3; float x4; float x5; float x6; })arg1;
- (void)dealloc;
- (BOOL)isOffice12;
- (float)maxAdjustedValue;
- (void)setAdjustValues:(id)arg1;
- (void)setFileFormat:(int)arg1;
- (void)setOrientedBounds:(id)arg1;
- (void)setShapeType:(int)arg1;

@end