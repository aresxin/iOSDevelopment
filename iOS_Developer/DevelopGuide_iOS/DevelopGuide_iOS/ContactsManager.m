//
//  ContactsManager.m
//  QuickContacts
//
//  Created by neusoft  on 11-6-8.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ContactsManager.h"
@implementation Contacts
@synthesize contactName;
@synthesize contactPhoneNumber;
@synthesize contactAddress;
@synthesize contactEmail;
@synthesize contactCompany;
@synthesize contactTel;

- (id)init{
	if ((self = [super init])) {
		self.contactName = @" ";
		self.contactPhoneNumber = @" ";
		self.contactAddress = nil;
		self.contactEmail = @" ";
		self.contactCompany = @" ";
		self.contactTel = @" ";
	}
	return self;
}

- (NSString*)description
{
	NSString *result = [NSString stringWithFormat:@"%@; %@; %@; %@; %@;",
						contactName,contactPhoneNumber,contactEmail,
						contactCompany,contactTel];
	NSLog(@"description is %@",result);
	NSLog(@"address is %@",[contactAddress objectForKey:@"街道"]);
	return result;
}

- (void) dealloc
{
	[contactName release];
	[contactPhoneNumber release];
	[contactAddress release];
	[contactEmail release];
	[contactCompany release];
	[contactTel release];
	[super dealloc];
}
@end


@implementation ContactsManager


- (id)init{
	if ((self = [super init])) {
	}
	return self;
}

#pragma mark -
#pragma mark getContactsInfo
- (NSMutableArray *) getContactsList
{
	NSMutableArray *contactArr = [[NSMutableArray alloc] init];
	
	NSMutableArray* personArray = [[[NSMutableArray alloc] init] autorelease];
	
    ABAddressBookRef addressBook = ABAddressBookCreate();
	
	NSString *firstName = nil;
	
	personArray = (NSMutableArray *)ABAddressBookCopyArrayOfAllPeople(addressBook);
	
	Contacts *contactInfo = nil;
	
	for (id person in personArray)
	{
		
		contactInfo = [[Contacts alloc] init];
		//get person property
		
		//get contactName
 		firstName = (NSString *)ABRecordCopyValue(person, kABPersonFirstNameProperty);
		NSLog(@"===%@",firstName);
		if (firstName != nil) {contactInfo.contactName = firstName;}
		
		
		//get contactPhoneNumber
		ABMultiValueRef phones = (ABMultiValueRef) ABRecordCopyValue(person, kABPersonPhoneProperty);
		if (ABMultiValueGetCount(phones) != 0) {
			for (int i = 0; i < ABMultiValueGetCount(phones); i++) {
				NSString *num = (NSString *)ABMultiValueCopyValueAtIndex(phones, i);
				NSLog(@"contact num is %@ and %d",num,i);
				if (i == 0 ) {
					//get phonenumber
					contactInfo.contactPhoneNumber = num;
				}
				if (i == 1) {
					//get contactTel
					contactInfo.contactTel = num;
				}
			}
			
		}
		
		//get contactEmail
		ABMultiValueRef mails = (ABMultiValueRef) ABRecordCopyValue(person, kABPersonEmailProperty);
		for(int i = 0 ;i < ABMultiValueGetCount(mails); i++)
		{
			NSString *mail = (NSString *)ABMultiValueCopyValueAtIndex(mails, i); 
			if (i == 0) {
				contactInfo.contactEmail = mail;
			}
			NSLog(@"mail is %@",mail);
		}
		
		//get contactCompany
		NSString *companyName = (NSString *)ABRecordCopyValue(person, kABPersonOrganizationProperty);
		if (companyName != nil) {
			contactInfo.contactCompany = companyName;
		}
		NSLog(@"===%@",companyName);
		
		//get contactAddress
		contactInfo.contactAddress = [self getContactsAddrssWith:person];
		
		[contactInfo description];
		[contactArr addObject:contactInfo];
		//release
		[contactInfo release];
	}		
	//释放内存
	CFRelease(addressBook);
	
	return [contactArr autorelease];
}
//get address
- (NSMutableDictionary *) getContactsAddrssWith:(ABRecordRef)person
{
	NSMutableDictionary *addressDic = [[NSMutableDictionary alloc] init];
	//读取地址多值
	ABMultiValueRef address = ABRecordCopyValue(person, kABPersonAddressProperty);
	int count = ABMultiValueGetCount(address);    
	
	for(int j = 0; j < count; j++)
	{
		//获取地址Label
		//NSString* addressLabel = (NSString*)ABMultiValueCopyLabelAtIndex(address, j);

		//获取該label下的地址6属性
		NSDictionary* personaddress =(NSDictionary*) ABMultiValueCopyValueAtIndex(address, j);        
		NSString* country = [personaddress valueForKey:(NSString *)kABPersonAddressCountryKey];
		if(country != nil)
			[addressDic setObject:country forKey:@"国家"];
		
		NSString* city = [personaddress valueForKey:(NSString *)kABPersonAddressCityKey];
		if(city != nil)
			[addressDic setObject:city forKey:@"城市"];
		
		NSString* state = [personaddress valueForKey:(NSString *)kABPersonAddressStateKey];
		if(state != nil)
		    [addressDic setObject:state forKey:@"省"];
		
		NSString* street = [personaddress valueForKey:(NSString *)kABPersonAddressStreetKey];
		if(street != nil)
			[addressDic setObject:street forKey:@"街道"];
		
		NSString* zip = [personaddress valueForKey:(NSString *)kABPersonAddressZIPKey];
		if(zip != nil)
			[addressDic setObject:zip forKey:@"邮编"];
		
		NSString* coutntrycode = [personaddress valueForKey:(NSString *)kABPersonAddressCountryCodeKey];
		if(coutntrycode != nil)
			[addressDic setObject:coutntrycode forKey:@"国家编号"];    
	}	
	return [addressDic autorelease];
}

#pragma mark -
#pragma mark setContactInfo
//修改联系人
- (void) setContactsList:(NSMutableArray *)contactArr 
			   withIndex:(NSInteger)index
	   withContactObject:(Contacts *)contactInfo
{
	if ([contactArr count] == 0 ||
		contactInfo == nil) {
		return;
	}
	Contacts *contact = [contactInfo retain];
	[contactArr replaceObjectAtIndex:index withObject:contactInfo];	
	
	CFErrorRef error = NULL;
	BOOL result;
	//返回所有联系人到一个数组中
	ABAddressBookRef addressBook = ABAddressBookCreate();
	CFArrayRef personArray = ABAddressBookCopyArrayOfAllPeople(addressBook);
	ABRecordRef ref = CFArrayGetValueAtIndex(personArray, index);
	
	//modify contactInfo
	//设置相关属性
	result = ABRecordSetValue(ref, kABPersonFirstNameProperty, 
							  (CFStringRef)contact.contactName, &error) 
	&&
	ABRecordSetValue(ref, kABPersonOrganizationProperty, 
					 (CFStringRef)contact.contactCompany, &error)
	&&
	[self addPhone:ref phone:contact.contactPhoneNumber 
			   tel:contact.contactTel]
	&&
	[self addEmail:ref Email:contact.contactEmail]
	&&
	[self addAddress:ref street:contact.contactAddress];
	// 保存到地址本
	result = ABAddressBookSave(addressBook, &error);
	
	//释放内存
	CFRelease(personArray);
	CFRelease(addressBook);
	[contact release];
	
}
//修改联系人电话
- (BOOL)addPhone:(ABRecordRef)person phone:(NSString*)phone tel:(NSString *)tel
{
	ABMutableMultiValueRef multi = ABMultiValueCreateMutable(kABMultiStringPropertyType);
	
	CFErrorRef anError = NULL;
	
	ABMultiValueIdentifier multivalueIdentifier;
	
	if (!ABMultiValueAddValueAndLabel(multi, (CFStringRef)phone, kABPersonPhoneMobileLabel, &multivalueIdentifier)){
		CFRelease(multi);
		return NO;
	}
	if (!ABMultiValueAddValueAndLabel(multi, (CFStringRef)tel, kABPersonPhoneIPhoneLabel, &multivalueIdentifier)){
		CFRelease(multi);
		return NO;
	}
	
	if (!ABRecordSetValue(person, kABPersonPhoneProperty, multi, &anError)){
		CFRelease(multi);
		return NO;
	}
	
	CFRelease(multi);
	return YES;
}
//修改联系人mail 
- (BOOL)addEmail:(ABRecordRef)person Email:(NSString *)mail
{
	ABMutableMultiValueRef multi = ABMultiValueCreateMutable(kABMultiStringPropertyType);
	
	CFErrorRef anError = NULL;
	
	ABMultiValueIdentifier multivalueIdentifier;
	
	if (!ABMultiValueAddValueAndLabel(multi, (CFStringRef)mail, kABWorkLabel, &multivalueIdentifier)){
		CFRelease(multi);
		return NO;
	}
		
	if (!ABRecordSetValue(person, kABPersonPhoneProperty, multi, &anError)){
		CFRelease(multi);
		return NO;
	}
	
	CFRelease(multi);
	return YES;
}

//添加联系人地址
- (BOOL)addAddress:(ABRecordRef)person street:(NSMutableDictionary *)addressDic
{
	if (addressDic == nil) {
		return NO;
	}
	ABMutableMultiValueRef address = ABMultiValueCreateMutable(kABDictionaryPropertyType);
	
	static int homeLableValueCount = 5;
	
	// Set up keys and values for the dictionary.
	CFStringRef keys[homeLableValueCount];
	CFStringRef values[homeLableValueCount];
	keys[0] = kABPersonAddressStreetKey;
	keys[1] = kABPersonAddressCityKey;
	keys[2] = kABPersonAddressStateKey;
	keys[3] = kABPersonAddressZIPKey;
	keys[4] = kABPersonAddressCountryKey;
	values[0] = (CFStringRef)[addressDic objectForKey:@"街道"];
	values[1] = (CFStringRef)[addressDic objectForKey:@"城市"];
	values[2] = (CFStringRef)[addressDic objectForKey:@"省"];
	values[3] = (CFStringRef)[addressDic objectForKey:@"邮编"];
	values[4] = (CFStringRef)[addressDic objectForKey:@"国家"];
	
	CFDictionaryRef aDict = CFDictionaryCreate(
											   kCFAllocatorDefault,
											   (void *)keys,
											   (void *)values,
											   homeLableValueCount,
											   &kCFCopyStringDictionaryKeyCallBacks,
											   &kCFTypeDictionaryValueCallBacks
											   );
	
	// Add the street address to the person record.
	ABMultiValueIdentifier identifier;
	
	BOOL result = ABMultiValueAddValueAndLabel(address, aDict, kABHomeLabel, &identifier);
	
	CFErrorRef error = NULL;
	result = ABRecordSetValue(person, kABPersonAddressProperty, address, &error);
	
	CFRelease(aDict);
	CFRelease(address);
	
	return result;
}

- (void) dealloc
{
	[super dealloc];
}
@end
