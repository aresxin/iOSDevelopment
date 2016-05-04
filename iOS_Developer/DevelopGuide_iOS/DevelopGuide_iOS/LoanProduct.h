//
//  LoanProduct.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class LoanType;

@interface LoanProduct : NSManagedObject

@property (nonatomic, retain) NSNumber * discountcharge;
@property (nonatomic, retain) NSData * firstpayPercent;
@property (nonatomic, retain) NSData * interestrate;
@property (nonatomic, retain) NSData * lastpayPercent;
@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) NSData * period;
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
@property (nonatomic, retain) LoanType *loantype;

@end
