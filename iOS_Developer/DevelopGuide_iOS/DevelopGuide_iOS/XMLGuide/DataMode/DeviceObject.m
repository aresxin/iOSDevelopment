//
//  DeviceObject.m
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DeviceObject.h"


@implementation DeviceObject
@synthesize deviceId = deviceId_;
@synthesize deviceName = deviceName_;
@synthesize deviceCL = deviceCL_;
@synthesize ipAddress = ipAddress_;
@synthesize applications = applications_;
@synthesize power = power_;;
- (id) init
{
	self = [super init];
	
	if (self) {
		self.deviceId = nil;
		self.deviceName = nil;
		self.deviceCL = nil;
		self.ipAddress = nil;
		applications_ = [[NSMutableArray alloc] init];
		self.power = nil;
	}
	
	return self;
}

- (NSString *)deviceDescription{
	NSString *deviceDes = [NSString stringWithFormat:@"%@-%@-%@-%@-%@",
						  deviceId_,deviceName_,deviceCL_,ipAddress_,power_];
	return deviceDes;
}


- (void)dealloc {
	[deviceId_ release];
	[deviceName_ release];
	[deviceCL_ release];
	[ipAddress_ release];
	[applications_ release];
	[power_  release];
    [super dealloc];
}

@end
