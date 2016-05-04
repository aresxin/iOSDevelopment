//
//  FadeScrollView.m
//  scroll_test
//
//  Created by Maxim Keegan on 24.04.12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "FadeScrollView.h"
#import <QuartzCore/QuartzCore.h>

@implementation FadeScrollView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

- (id) initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    if (self) {
        // Initialization code

    }
    return self;
}

- (void) layoutSubviews {
    float fadeHeight = 50.0;

    CALayer *l = [CALayer layer];
    l.frame = self.bounds;

    CAGradientLayer *l1 = [CAGradientLayer layer];
    l1.frame = CGRectMake(self.contentOffset.x, -fadeHeight, self.bounds.size.width, fadeHeight);
    l1.colors = [NSArray arrayWithObjects:(id)[UIColor clearColor].CGColor, (id)[UIColor whiteColor].CGColor, nil];
    l1.endPoint = CGPointMake(0.1, 1.0);
    l1.startPoint = CGPointMake(0.0, 0.0);
    [l addSublayer:l1];

    CAGradientLayer *l2 = [CAGradientLayer layer];
    l2.frame = CGRectMake(self.contentOffset.x, self.bounds.size.height , self.bounds.size.width, fadeHeight);
    l2.colors = [NSArray arrayWithObjects:(id)[UIColor whiteColor].CGColor, (id)[UIColor clearColor].CGColor, nil];
    [l addSublayer:l2];

    CALayer *l3 = [CALayer layer];
    l3.backgroundColor = [UIColor whiteColor].CGColor;
    l3.frame = CGRectMake(self.contentOffset.x, 0, self.bounds.size.width, self.bounds.size.height);
    [l addSublayer:l3];
    
    self.layer.mask = l;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

@end
