//
//  TestPropertyListing.h
//  DevelopGuide_iOS
//
//  Created by clay on 13-1-9.
//
//

#import <Foundation/Foundation.h>

@interface TestPropertyListing : NSObject {
    NSString      *name;
    NSString      *sex;
    NSString      *age;
}
@property (nonatomic, retain)  NSString      *name;
@property (nonatomic, retain)  NSString      *sex;
@property (nonatomic, retain)  NSString      *age;
@end
