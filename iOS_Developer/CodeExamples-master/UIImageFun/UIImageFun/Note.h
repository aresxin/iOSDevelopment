//
//  Note.h
//  UIImageFun

#import <Foundation/Foundation.h>
@interface Note : NSObject
@property (nonatomic, readonly) NSString *text;
@property (nonatomic, readonly) UIImageView *noteView;
- (id)initWithText:(NSString *)text fontSize:(float)fontSize noteChrome:(UIImage *)img edgeInsets:(UIEdgeInsets)insets maximumWidth:(CGFloat)width topLeftCorner:(CGPoint)corner;
@end
