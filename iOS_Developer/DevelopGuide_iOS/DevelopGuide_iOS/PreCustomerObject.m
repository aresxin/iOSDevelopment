//
//  PreCustomerObject.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import "PreCustomerObject.h"

@implementation PreCustomerObject
@synthesize managedObjectID;
@synthesize brand_id;
@synthesize cConvertProject;
@synthesize city_id;
@synthesize close_date;
@synthesize comment;
@synthesize dCreate;
@synthesize dHopeTryDriveBegin;
@synthesize dHopeTryDriveEnd;
@synthesize intent_auto;
@synthesize mail;
@synthesize mobile;
@synthesize name;
@synthesize preCustomerid;
@synthesize sale_id;
@synthesize sex_id;
@synthesize uCarShowID;
@synthesize uProjectId;
@synthesize isDel;

- (void) dealloc
{
    self.managedObjectID = nil;
    self.brand_id = nil;
    self.cConvertProject = nil;
    self.city_id = nil;
    self.close_date = nil;
    self.comment = nil;
    self.dCreate = nil;
    self.dHopeTryDriveBegin = nil;
    self.dHopeTryDriveEnd = nil;
    self.intent_auto = nil;
    self.mail = nil;
    self.mobile = nil;
    self.name = nil;
    self.preCustomerid = nil;
    self.sale_id = nil;
    self.sex_id = nil;
    self.uCarShowID = nil;
    self.uProjectId = nil;
    self.isDel = nil;
    [super dealloc];
}
@end
