//
//  PreCustomerObject.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import <Foundation/Foundation.h>

@interface PreCustomerObject : NSObject {
     NSManagedObjectID * managedObjectID;
     NSString * brand_id;
     NSNumber * cConvertProject;
     NSString * city_id;
     NSDate * close_date;
     NSString * comment;
     NSDate * dCreate;
     NSDate * dHopeTryDriveBegin;
     NSDate * dHopeTryDriveEnd;
     NSString * intent_auto;
     NSString * mail;
     NSString * mobile;
     NSString * name;
     NSString * preCustomerid;
     NSString * sale_id;
     NSString * sex_id;
     NSString * uCarShowID;
     NSString * uProjectId;
     NSNumber * isDel;

}
@property (nonatomic, retain) NSManagedObjectID * managedObjectID;
@property (nonatomic, retain) NSString * brand_id;
@property (nonatomic, retain) NSNumber * cConvertProject;
@property (nonatomic, retain) NSString * city_id;
@property (nonatomic, retain) NSDate * close_date;
@property (nonatomic, retain) NSString * comment;
@property (nonatomic, retain) NSDate * dCreate;
@property (nonatomic, retain) NSDate * dHopeTryDriveBegin;
@property (nonatomic, retain) NSDate * dHopeTryDriveEnd;
@property (nonatomic, retain) NSString * intent_auto;
@property (nonatomic, retain) NSString * mail;
@property (nonatomic, retain) NSString * mobile;
@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) NSString * preCustomerid;
@property (nonatomic, retain) NSString * sale_id;
@property (nonatomic, retain) NSString * sex_id;
@property (nonatomic, retain) NSString * uCarShowID;
@property (nonatomic, retain) NSString * uProjectId;
@property (nonatomic, retain) NSNumber * isDel;
@end
