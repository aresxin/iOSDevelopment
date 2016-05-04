#import <UIKit/UIKit.h>
 
@interface UILabel (ContentSize)
 - (CGSize)contentSize;
-(float)resizeToFit;
-(float)expectedHeight;
@end