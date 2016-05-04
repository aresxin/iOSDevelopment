//
//  CustomAnnotation.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
@interface CustomAnnotation : NSObject <MKAnnotation> {
    CLLocationCoordinate2D coordinate;
	NSString *subtitle;
	NSString *title;
}
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
// Title and subtitle for use by selection UI.
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *subtitle;
-(id) initWithCoords:(CLLocationCoordinate2D) coords 
           withTitle:(NSString *)title_ 
        withSubTitle:(NSString *)subTitle_; 
@end
