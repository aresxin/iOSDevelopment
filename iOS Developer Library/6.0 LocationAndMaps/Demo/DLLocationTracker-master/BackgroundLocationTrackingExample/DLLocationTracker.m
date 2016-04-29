//
//  KWLocationTracker.m
//  Kawiky
//
//  Created by Denis Lebedev on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "DLLocationTracker.h"
//#import "KWConstants.h"


#define IS_OS_8_OR_LATER ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)

static CGFloat const kMinUpdateDistance = 10.f;
static NSTimeInterval const kMinUpdateTime = 90.f;
static NSTimeInterval const kMaxTimeToLive = 30.f;

static NSString *const kArchivedLocationKey = @"com.Company.Defaults.ArchivedLocation";

@interface DLLocationTracker () {
@private     
    UIBackgroundTaskIdentifier bgTask;
}

@end

@implementation DLLocationTracker

#pragma mark - NSObject

- (id)init {
    if (self = [super init]) {
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidBecomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationDidEnterBackground) name:    UIApplicationDidEnterBackgroundNotification object:nil];
        self.locationManager = [[CLLocationManager alloc] init];
        self.locationManager.delegate = self;
        //self.locationManager.desiredAccuracy = kCLLocationAccuracyKilometer;
        self.locationManager.distanceFilter  = kCLDistanceFilterNone;
        //self.locationManager.activityType = CLActivityTypeOtherNavigation;
        self.locationManager.activityType = CLActivityTypeFitness;
        self.locationManager.pausesLocationUpdatesAutomatically = NO;
        
        
        //
        self.backgroundlocationManager = [[CLLocationManager alloc] init];
        self.backgroundlocationManager.delegate = self;
        self.backgroundlocationManager.desiredAccuracy = kCLLocationAccuracyHundredMeters;
        self.backgroundlocationManager.distanceFilter = kCLDistanceFilterNone;
        self.backgroundlocationManager.activityType = CLActivityTypeFitness;
        self.backgroundlocationManager.pausesLocationUpdatesAutomatically = NO;
    }
    return self;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - Notification handlers

- (void)applicationDidBecomeActive {
    [self.backgroundlocationManager stopMonitoringSignificantLocationChanges];
    
    if(IS_OS_8_OR_LATER) {
        [self.locationManager requestAlwaysAuthorization];
    }
    [self.locationManager startUpdatingLocation];
}

- (void)applicationDidEnterBackground {
    [self.locationManager stopUpdatingLocation];
    
    if(IS_OS_8_OR_LATER) {
        [self.backgroundlocationManager requestAlwaysAuthorization];
    }
    [self.backgroundlocationManager startMonitoringSignificantLocationChanges];
    
    
    if (![CLLocationManager significantLocationChangeMonitoringAvailable]) {
        
    }
}

#pragma mark - Public

- (void)startUpdatingLocation {
    [self stopUpdatingLocation];
    if(IS_OS_8_OR_LATER) {
        [self.locationManager requestAlwaysAuthorization];
    }
//    [self.locationManager startMonitoringSignificantLocationChanges];
//    return;
    
    [self isInBackground] ? [self.backgroundlocationManager startMonitoringSignificantLocationChanges] : [self.locationManager startUpdatingLocation];
}

- (void)stopUpdatingLocation {
    [self.locationManager stopUpdatingLocation];
    [self.backgroundlocationManager stopMonitoringSignificantLocationChanges];
}

- (void)endBackgroundTask {
    if (bgTask != UIBackgroundTaskInvalid) {
        [[UIApplication sharedApplication] endBackgroundTask:bgTask];
        bgTask = UIBackgroundTaskInvalid;
    }
}
#pragma mark - Private

- (BOOL)isInBackground {
    return [UIApplication sharedApplication].applicationState == UIApplicationStateBackground;
}

#pragma mark - CLLocationManager Delegate

- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation {
//    if (oldLocation && ([newLocation.timestamp timeIntervalSinceDate:oldLocation.timestamp] < kMinUpdateTime ||
//                        [newLocation distanceFromLocation:oldLocation] < kMinUpdateDistance)) {
//        return;
//    }
    
    if ([self isInBackground]) {
        if (self.locationUpdatedInBackground) {
            bgTask = [[UIApplication sharedApplication] beginBackgroundTaskWithExpirationHandler: ^{
                [[UIApplication sharedApplication] endBackgroundTask:bgTask];
            }];
            
            self.locationUpdatedInBackground(newLocation);
            [self endBackgroundTask];
        }
    } else {
        if (self.locationUpdatedInForeground) {
            self.locationUpdatedInForeground(newLocation);
        }
    }
}

@end
