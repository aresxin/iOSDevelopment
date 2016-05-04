//
//  CoreLocationMgr.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-19.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "CoreLocationMgr.h"


@implementation CoreLocationMgr

@synthesize locationMgr = locationMgr_;
@synthesize location = location_;
@synthesize delegate;

static  CoreLocationMgr *locationManager = nil;
+ (CoreLocationMgr *) sharedAsyncSocketImpl
{    
    @synchronized(self)
    {
        if (locationManager == nil) {
            locationManager = [[self alloc] init];
        }
    }
    return locationManager;
}

- (id) init
{
    self = [super init];
    if (self) {
        locationMgr_ = [[CLLocationManager alloc] init];
        locationMgr_.delegate = self;
        // 指定定位级别
        locationMgr_.desiredAccuracy = kCLLocationAccuracyBest;
        
        self.location = nil;
    }
    return self;
}

- (void) startUpdataLocation
{
    [locationMgr_ startUpdatingLocation];
}

- (void) stopUpdataLocation
{
    [locationMgr_ stopUpdatingLocation];
}

#pragma make -
#pragma make CLLocationManagerDelegate methods
- (void)locationManager:(CLLocationManager *)manager
	didUpdateToLocation:(CLLocation *)newLocation
           fromLocation:(CLLocation *)oldLocation
{
    self.location = newLocation;
#ifdef _DEBUG_
    NSLog(@"经纬度 is ----%gm, %gm",location_.coordinate.latitude,
          location_.coordinate.longitude);
    
    NSLog(@"范围半径 is -----%gm",location_.horizontalAccuracy);
    
    NSLog(@"海拔 is -----%gm",location_.altitude);
    
    NSLog(@"海拔精确程度 is -----%gm",location_.verticalAccuracy);
#endif
    [delegate didFinishGetLocation:newLocation];
}

- (void)locationManager:(CLLocationManager *)manager
       didFailWithError:(NSError *)error
{
#ifdef _DEBUG_
    NSLog(@"get location error");
#endif
}

- (void)locationManager:(CLLocationManager *)manager
       didUpdateHeading:(CLHeading *)newHeading
{
}

- (BOOL)locationManagerShouldDisplayHeadingCalibration:(CLLocationManager *)manager
{
    return YES;
}

#define ios4 later
- (void)locationManager:(CLLocationManager *)manager
         didEnterRegion:(CLRegion *)region
{
}

#define ios4 later
- (void)locationManager:(CLLocationManager *)manager
          didExitRegion:(CLRegion *)region
{}

#define ios4 later
- (void)locationManager:(CLLocationManager *)manager
monitoringDidFailForRegion:(CLRegion *)region
              withError:(NSError *)error 
{}

#define ios42 later
- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status
{}

- (void) dealloc
{
    [locationMgr_ release];
    [location_ release];
    [super dealloc];
}

@end
