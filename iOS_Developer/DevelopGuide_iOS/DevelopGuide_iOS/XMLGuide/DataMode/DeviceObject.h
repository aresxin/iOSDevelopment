//
//  DeviceObject.h
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface DeviceObject : NSObject {
	NSString *deviceId_;
	NSString *deviceName_;
	NSString *deviceCL_;
	NSString *ipAddress_;
	NSMutableArray *applications_;
	NSString *power_;
}
@property (nonatomic, retain) NSString *deviceId;
@property (nonatomic, retain) NSString *deviceName;
@property (nonatomic, retain) NSString *deviceCL;
@property (nonatomic, retain) NSString *ipAddress;
@property (nonatomic, retain) NSMutableArray *applications;
@property (nonatomic, retain) NSString *power;
@end
