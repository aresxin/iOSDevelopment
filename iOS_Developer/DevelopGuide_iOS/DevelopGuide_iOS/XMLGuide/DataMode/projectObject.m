//
//  projectObject.m
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "projectObject.h"


@implementation projectObject
@synthesize projectId = projectId_;
@synthesize projectName = projectName_;
@synthesize videoindex;
- (id) init
{
	self = [super init];
	if (self) {
		self.projectId = nil;
		self.projectName = nil;
		self.videoindex = nil;
	}
	return self;
}

- (NSString *) projectDescription
{
	NSString *projectDes = [NSString stringWithFormat:@"%@-%@",
								projectId_,projectName_];
	return projectDes;
	
}


- (void) dealloc
{
	[projectId_ release];
	[projectName_ release];
	[videoindex release];
	[super dealloc];
}
@end
