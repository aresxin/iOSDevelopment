//
//  ContactsManager.h
//  QuickContacts
//
//  Created by neusoft  on 11-6-8.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>

@interface Contacts : NSObject
{
	NSString *contactName;
	NSString *contactPhoneNumber;
	NSMutableDictionary *contactAddress;
	NSString *contactEmail;
	NSString *contactCompany;
	NSString *contactTel;
}

@property (nonatomic, retain) NSString *contactName;
@property (nonatomic, retain) NSString *contactPhoneNumber;
@property (nonatomic, retain) NSMutableDictionary *contactAddress;
@property (nonatomic, retain) NSString *contactEmail;
@property (nonatomic, retain) NSString *contactCompany;
@property (nonatomic, retain) NSString *contactTel;

@end


@interface ContactsManager : NSObject {
	
}
//获得联系人列表
- (NSMutableArray *) getContactsList;
//get address
- (NSMutableDictionary *) getContactsAddrssWith:(ABRecordRef)person;
//修改联系人
- (void) setContactsList:(NSMutableArray *)contactArr 
			   withIndex:(NSInteger)index
	   withContactObject:(Contacts *)contactInfo;
- (BOOL)addPhone:(ABRecordRef)person phone:(NSString*)phone tel:(NSString *)tel;
- (BOOL)addEmail:(ABRecordRef)person Email:(NSString *)mail;
//添加联系人地址
- (BOOL)addAddress:(ABRecordRef)person street:(NSDictionary *)addressDic;
@end
