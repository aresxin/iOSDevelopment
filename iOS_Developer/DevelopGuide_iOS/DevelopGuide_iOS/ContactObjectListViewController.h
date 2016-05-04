//
//  ContactObjectListViewController.h
//  QuickContacts
//
//  Created by neusoft  on 11-6-8.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ContactsManager.h"
@class ContactsManager;
@interface ContactObjectListViewController : UITableViewController {
	NSMutableArray *contacts;
	ContactsManager *contactMgr;
}
@property (nonatomic, retain) NSMutableArray *contacts;
@end
