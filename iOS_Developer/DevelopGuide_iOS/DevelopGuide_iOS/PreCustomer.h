//
//  PreCustomer.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface PreCustomer : NSManagedObject

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
@property (nonatomic, retain) NSString * reservedAtt1;
@property (nonatomic, retain) NSString * reservedAtt2;
@property (nonatomic, retain) NSString * reservedAtt3;
@property (nonatomic, retain) NSString * reservedAtt4;
@property (nonatomic, retain) NSString * reservedAtt5;
@property (nonatomic, retain) NSNumber * reservedAtt6;
@property (nonatomic, retain) NSNumber * reservedAtt7;
@property (nonatomic, retain) NSNumber * reservedAtt8;
@property (nonatomic, retain) NSNumber * reservedAtt9;
@property (nonatomic, retain) NSNumber * reservedAtt10;
@property (nonatomic, retain) NSNumber * reservedAtt11;
@property (nonatomic, retain) NSNumber * reservedAtt12;
@property (nonatomic, retain) NSNumber * reservedAtt13;
@property (nonatomic, retain) NSString * sale_id;
@property (nonatomic, retain) NSString * sex_id;
@property (nonatomic, retain) NSString * uCarShowID;
@property (nonatomic, retain) NSString * uProjectId;
@property (nonatomic, retain) NSNumber * isDel;

@end
