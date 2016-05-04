//
//  addContactViewController.h
//  QuickContacts
//
//  Created by 杨 金鑫 on 11-5-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>

@interface addContactViewController : UITableViewController {
	NSMutableArray *titleArr;
	UITextField    *fieldContactName;
	UITextField    *fieldlastName;
	UITextField    *fieldTelNum;
	NSInteger      editIndex;
	NSInteger      contactIndex;
}
@property NSInteger editIndex;
@property NSInteger contactIndex;
- (void) initFooter;
- (BOOL)addPhone:(ABRecordRef)person phone:(NSString*)phone;
- (void) initEditContactInfo;
@end
