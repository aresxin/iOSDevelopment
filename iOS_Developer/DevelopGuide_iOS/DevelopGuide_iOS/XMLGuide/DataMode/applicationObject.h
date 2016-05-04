//
//  applicationObject.h
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface applicationObject : NSObject {
	NSString           *applicationId_;
	NSString           *applicationName_;
	NSString           *applicationCL_;
	NSMutableArray     *members_;
	NSString           *running_;
}
@property (nonatomic, retain) NSString  *applicationId;
@property (nonatomic, retain) NSString  *applicationName;
@property (nonatomic, retain) NSString  *applicationCL;
@property (nonatomic, retain) NSMutableArray  *members;
@property (nonatomic, retain) NSString  *running;
@end
