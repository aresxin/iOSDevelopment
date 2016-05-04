//
//  UIScreen+Device.m
//  SnapMovie
//
//  Created by CN40436 on 15/2/6.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "UIScreen+Device.h"

static UIScreenIdiom sharedScreenIdiom = NSIntegerMax;

@implementation UIScreen (Device)

+ (UIScreenIdiom)mainScreenIdiom;
{
    static dispatch_once_t pred;
    dispatch_once(&pred, ^{
        // get device family
        NSArray *family = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"UIDeviceFamily"];
        BOOL supportPad = NO;
        for (NSString *device in family) {
            NSInteger value = [device integerValue];
            if (value == 2) {
                supportPad = YES;
            }
        }

        // check screen size
        UIScreen *screen = [UIScreen mainScreen];
        CGSize size = [screen bounds].size;
        if (screen.scale == 3.0) {
            if ((size.width == 414 && size.height == 736)) {
                sharedScreenIdiom = UIScreenIdiomPhone6Plus;
                //WriteWarning(@"This is a iPhone6 plus on standard mode.");
            } else {
                sharedScreenIdiom = UIScreenIdiomPhone6;
                //WriteWarning(@"This is a iPhone6 plus on zoomed mode.");
            }
        } else if (size.width == 375 && size.height == 667) {
            sharedScreenIdiom = UIScreenIdiomPhone6;
            //WriteWarning(@"This is a iPhone6.");
        } else if (size.width == 320 && size.height == 568) {
            sharedScreenIdiom = UIScreenIdiomPhone5;
            //WriteWarning(@"This is a iPhone5.");
        } else if (size.width == 320 && size.height == 480) {
            sharedScreenIdiom = UIScreenIdiomPhone4;
            //WriteWarning(@"This is a iPhone4.");
        } else if (screen.scale > 2.9) {
            sharedScreenIdiom = UIScreenIdiomPhone6Plus;
            //WriteWarning(@"This is a iPhone6 plus scale 3.");
        } else {
            // check device family
            if (supportPad) {
                // if ipad is supported
                sharedScreenIdiom = UIScreenIdiomPad;
                //WriteWarning(@"This is a iPad.");
            } else {
                // if ipad is not supported the pad will treat as iPhone4
                sharedScreenIdiom = UIScreenIdiomPhone4;
                //WriteWarning(@"This is a iPad but it will be deal as iPhone4.");
            }
        }
       // WriteWarning(@"Scale:%f Size:%@", screen.scale, NSStringFromCGSize(size));
    });
    return sharedScreenIdiom;
}
@end
