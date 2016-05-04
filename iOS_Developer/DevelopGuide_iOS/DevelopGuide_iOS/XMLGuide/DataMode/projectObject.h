//
//  projectObject.h
//  Deveice
//
//  Created by neusoft  on 11-8-26.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface projectObject : NSObject {
	NSString     *projectId_;
	NSString     *projectName_;
	NSString     *videoindex;
}
@property (nonatomic, retain) NSString *projectId;
@property (nonatomic, retain) NSString *projectName;
@property (nonatomic, retain) NSString *videoindex;
@end
