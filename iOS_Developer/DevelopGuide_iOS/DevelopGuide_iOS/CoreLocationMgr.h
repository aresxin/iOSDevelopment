//
//  CoreLocationMgr.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-19.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@protocol didFinishLocation <NSObject>

@optional
- (void) didFinishGetLocation:(CLLocation *)location_;

@end

@interface CoreLocationMgr : NSObject <CLLocationManagerDelegate>{
    CLLocationManager   *locationMgr_;
    CLLocation          *location_;
    id <didFinishLocation> delegate;
}

@property (nonatomic, retain)   CLLocationManager   *locationMgr;
@property (nonatomic, retain)   CLLocation          *location;
@property (nonatomic, assign)   id <didFinishLocation> delegate;
+ (CoreLocationMgr *) sharedAsyncSocketImpl;

- (void) startUpdataLocation;
- (void) stopUpdataLocation;
@end

