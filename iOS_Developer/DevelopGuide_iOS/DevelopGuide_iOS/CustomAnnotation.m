//
//  CustomAnnotation.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CustomAnnotation.h"

@implementation CustomAnnotation
@synthesize coordinate;
@synthesize title;
@synthesize subtitle;

-(id) initWithCoords:(CLLocationCoordinate2D) coords 
           withTitle:(NSString *)title_ 
        withSubTitle:(NSString *)subTitle_
{
    self = [super init];
    if (self) {
        coordinate = coords;
        self.title = title_;
        self.subtitle = subTitle_;
    }
    return self;
}

- (void) dealloc
{
    [title release];
    [subtitle release];
    [super dealloc];
}
@end
