//
//  KWLocationTracker.h
//  Kawiky
//
//  Created by Denis Lebedev on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>

typedef void(^locationHandler)(CLLocation *location);

@interface DLLocationTracker : NSObject <CLLocationManagerDelegate>

@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic, strong) CLLocationManager *backgroundlocationManager;

@property (nonatomic, copy) locationHandler locationUpdatedInForeground;
@property (nonatomic, copy) locationHandler locationUpdatedInBackground;

- (void)startUpdatingLocation;
- (void)stopUpdatingLocation;
- (void)endBackgroundTask;

@end
