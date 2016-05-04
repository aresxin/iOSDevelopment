//
//  applicationObject.m
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "applicationObject.h"


@implementation applicationObject
@synthesize applicationId = applicationId_;
@synthesize applicationName = applicationName_;
@synthesize applicationCL = applicationCL_;
@synthesize members = members_;
@synthesize running = running_;

- (id) init
{
	self = [super init];
	if (self) {
		self.applicationId = nil;
		self.applicationName = nil;
		self.applicationCL = nil;
		members_ = [[NSMutableArray alloc] init];
		self.running = nil;
	}
	return self;
}

- (NSString *) applicationDescription
{
	NSString *applicationDes = [NSString stringWithFormat:@"%@-%@-%@-%@",
						   applicationId_,applicationName_,applicationCL_,running_];
	return applicationDes;
	
}

- (void) dealloc
{
	[applicationId_ release];
	[applicationName_  release];
	[applicationCL_ release];
	[members_ release]; 
	[running_ release];
	[super dealloc];
}
@end
