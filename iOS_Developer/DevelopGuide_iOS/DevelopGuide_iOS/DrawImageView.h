//
//  DrawImageView.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-14.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef enum {
    drawAtPoint = 0,
}DrawMode;

@interface DrawImageView : UIView {
    UIImage     *drawImg_;
}
@property   (nonatomic, retain) UIImage *drawImg;
@end
