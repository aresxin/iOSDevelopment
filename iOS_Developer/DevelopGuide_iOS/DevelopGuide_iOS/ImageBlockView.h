//
//  ImageBlockView.h
//  QuartzTest
//
//  Created by tuyuer tuyuer on 10/24/11.
//  Copyright 2011 tuyuer. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface ImageBlockView : UIView {
	int iValue;
	int jValue;
}
- (id)initWithiValue:(int)i jValue:(int)j;
- (void)sliceWithImage:(UIImage *)imageTemp iValue:(int)i jValue:(int)j;
@end
