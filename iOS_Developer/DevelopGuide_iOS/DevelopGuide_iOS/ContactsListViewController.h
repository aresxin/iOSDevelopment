//
//  ContactsListViewController.h
//  QuickContacts
//
//  Created by 杨 金鑫 on 11-5-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>

@interface ContactsListViewController : UITableViewController {
	NSMutableArray *contactArr;
}
@property (nonatomic,retain) NSMutableArray *contactArr;
- (void) initContactInfo;
- (void) initFooter;
- (void) deleteContactFromAddressBookWithIndex:(NSInteger)contactId;
@end
