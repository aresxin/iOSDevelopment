//
//  TestPropertyListing.m
//  DevelopGuide_iOS
//
//  Created by clay on 13-1-9.
//
//

#import "TestPropertyListing.h"

@implementation TestPropertyListing
@synthesize sex;
@synthesize name;
@synthesize age;

- (id) init
{
    self = [super init];
    if (self) {
        self.name = @"";
        self.age = @"";
        self.sex = @"";
    }
    
    return self;
}

- (void) dealloc
{
    [name release];
    [age release];
    [sex release];
    [super dealloc];
}
@end
