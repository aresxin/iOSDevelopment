//
//  PreCusDataManager.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import "PreCusDataManager.h"
#import "PreCustomerObject.h"
#import "PreCustomer.h"
#import "XXStore.h"

#define TABLE_NAME_PRECUSTOMER @"PreCustomer"
@implementation PreCusDataManager

static PreCusDataManager *instance;

+ (PreCusDataManager*)sharedInstance
{
    if (instance == nil) {
        instance = [[PreCusDataManager alloc]init];
    }
    return instance;
}

- (id)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void)dealloc
{
    
    [super dealloc];
}

#pragma mark -
#pragma mark DB
- (PreCustomer *) insertPreCustomer:(PreCustomerObject *)preCus
{
    PreCustomer *preCustomer = (PreCustomer*)[[XXStore shareStore]insertNewObjectForEntityForName:TABLE_NAME_PRECUSTOMER];
    preCus.managedObjectID = preCustomer.objectID;
    
    preCustomer.brand_id = preCus.brand_id;
    preCustomer.city_id  = preCus.city_id;
    preCustomer.name     = preCus.name;
    
  
    [[XXStore shareStore] saveContext];
    return preCustomer;
}

@end
