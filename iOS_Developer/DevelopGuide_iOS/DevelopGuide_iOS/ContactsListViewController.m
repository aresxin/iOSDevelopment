//
//  ContactsListViewController.m
//  QuickContacts
//
//  Created by 杨 金鑫 on 11-5-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ContactsListViewController.h"
#import "addContactViewController.h"

@implementation ContactsListViewController
@synthesize contactArr;


- (id)initWithStyle:(UITableViewStyle)style {
    // Override initWithStyle: if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
    if (self = [super initWithStyle:style]) {
    }
    return self;
}



- (void)viewDidLoad {
    [super viewDidLoad];

	[self initFooter];
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
     self.navigationItem.rightBarButtonItem = self.editButtonItem;
	
}


- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
	[self initContactInfo];
	[self.tableView reloadData];
}

#pragma mark -
#pragma mark init
- (void) initFooter
{
	// init footerView 
	CGRect footerViewRect = CGRectMake(0, 0, 320, 60);
	UIView *footerView = [[UIView alloc] initWithFrame:footerViewRect];
	footerView.backgroundColor = [self.tableView backgroundColor];
	//add button into view
	// draw select button
	UIButton* buttonStartSelect = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	buttonStartSelect.frame = CGRectMake(5, 0, 310, 40);
	[buttonStartSelect setTitle:@"Add Contact" forState:UIControlStateNormal];
	[buttonStartSelect addTarget:self action:@selector(actionTouchAddButton) 
				forControlEvents:UIControlEventTouchUpInside]; 
	[footerView addSubview:buttonStartSelect];
	self.tableView.tableFooterView = footerView;
	[footerView release];  
	
}

- (void) initContactInfo
{
	if (self.contactArr != nil) {
		[self.contactArr removeAllObjects];
		//[contactArr release];
		//self.contactArr = nil;
	}
	self.contactArr = [[NSMutableArray alloc] init];
	NSMutableArray* personArray = [[[NSMutableArray alloc] init] autorelease];
    ABAddressBookRef addressBook = ABAddressBookCreate();
	NSString *firstName, *lastName, *fullName;
	personArray = (NSMutableArray *)ABAddressBookCopyArrayOfAllPeople(addressBook);
	
	for (id person in personArray)
	{
		//get person property
		
 		firstName = (NSString *)ABRecordCopyValue(person, kABPersonFirstNameProperty);
		firstName = [firstName stringByAppendingFormat:@"/"];
		lastName = (NSString *)ABRecordCopyValue(person, kABPersonLastNameProperty);
		fullName = [firstName stringByAppendingFormat:@"%@",lastName];
		NSLog(@"===%@",fullName);
		if (fullName == nil) {
			fullName = (NSString *)ABRecordCopyValue(person, kABPersonOrganizationProperty);
			NSLog(@"===%@",fullName);
		}
		NSString *companyName = (NSString *)ABRecordCopyValue(person, kABPersonOrganizationProperty);
		NSLog(@"===%@",companyName);
		
				
		
		ABMultiValueRef mails = (ABMultiValueRef) ABRecordCopyValue(person, kABPersonEmailProperty);
		for(int i = 0 ;i < ABMultiValueGetCount(mails); i++)
		{
			NSString *mail = (NSString *)ABMultiValueCopyValueAtIndex(mails, i); 
			NSLog(@"mail is %@",mail);
		}
		
		ABMultiValueRef phones = (ABMultiValueRef) ABRecordCopyValue(person, kABPersonPhoneProperty);
		if (ABMultiValueGetCount(phones) != 0) {
			NSString *phone = (NSString *)ABMultiValueCopyValueAtIndex(phones, 0);
			NSLog(@"===%@",phone);
			for (int i = 0; i < ABMultiValueGetCount(phones); i++) {
				NSString *num = (NSString *)ABMultiValueCopyValueAtIndex(phones, i);
				NSLog(@"contact num is %@ and %d",num,i);
			}
            fullName = [fullName stringByAppendingFormat:@" %@",phone];
		}
		
		//address
	
		//读取地址多值
        ABMultiValueRef address = ABRecordCopyValue(person, kABPersonAddressProperty);
        int count = ABMultiValueGetCount(address);    
        
        for(int j = 0; j < count; j++)
        {
            //获取地址Label
            NSString* addressLabel = (NSString*)ABMultiValueCopyLabelAtIndex(address, j);
			NSLog(@"addrssslabel is %@",addressLabel);
			//获取該label下的地址6属性
            NSDictionary* personaddress =(NSDictionary*) ABMultiValueCopyValueAtIndex(address, j);  
			NSString *street = [personaddress valueForKey:(NSString *)kABPersonAddressStreetKey];
			NSLog(@"steer is %@",street);
          //  NSString* country = [personaddress valueForKey:(NSString *)kABPersonAddressCountryKey];
//            if(country != nil)
//               // textView.text = [textView.text stringByAppendingFormat:@"国家：%@\n",country];
//            NSString* city = [personaddress valueForKey:(NSString *)kABPersonAddressCityKey];
//            if(city != nil)
//             //   textView.text = [textView.text stringByAppendingFormat:@"城市：%@\n",city];
//            NSString* state = [personaddress valueForKey:(NSString *)kABPersonAddressStateKey];
//            if(state != nil)
//              //  textView.text = [textView.text stringByAppendingFormat:@"省：%@\n",state];
//            NSString* street = [personaddress valueForKey:(NSString *)kABPersonAddressStreetKey];
//            if(street != nil)
//               // NSString *street = [textView.text stringByAppendingFormat:@"街道：%@\n",street];
//			    NSLog(@"street is %@",street)
//            NSString* zip = [personaddress valueForKey:(NSString *)kABPersonAddressZIPKey];
//            if(zip != nil)
//               // textView.text = [textView.text stringByAppendingFormat:@"邮编：%@\n",zip];    
//            NSString* coutntrycode = [personaddress valueForKey:(NSString *)kABPersonAddressCountryCodeKey];
           // if(coutntrycode != nil)
               // textView.text = [textView.text stringByAppendingFormat:@"国家编号：%@\n",coutntrycode];    
        }
        
		
		if (fullName != nil) {
			[self.contactArr addObject:fullName];
		}
		
	}		
	//释放内存
	CFRelease(addressBook);
	
}

#pragma mark -
#pragma mark actionTouch
- (void) actionTouchAddButton
{
	NSLog(@"Add a contact");
	addContactViewController *viewController = [[addContactViewController alloc] 
												initWithStyle:UITableViewStyleGrouped];
	[self.navigationController pushViewController:viewController animated:YES];
	[viewController release];
}


#pragma mark -
#pragma mark deleteContactFromAddressBookWithIndex
- (void) deleteContactFromAddressBookWithIndex:(NSInteger)contactId
{
	//返回所有联系人到一个数组中
	ABAddressBookRef addressBook = ABAddressBookCreate();
	CFArrayRef personArray = ABAddressBookCopyArrayOfAllPeople(addressBook);
	CFIndex personCount = ABAddressBookGetPersonCount(addressBook);
	for (int i =0;i<personCount;i++){
		if (i == contactId) {
		   ABRecordRef ref = CFArrayGetValueAtIndex(personArray, i);
		   ABAddressBookRemoveRecord(addressBook, ref, nil);
		}
	}
	 //保存电话本
	ABAddressBookSave(addressBook, nil);
	 //释放内存
	CFRelease(addressBook);
	
}
/*
- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}
*/
/*
- (void)viewWillDisappear:(BOOL)animated {
	[super viewWillDisappear:animated];
}
*/
/*
- (void)viewDidDisappear:(BOOL)animated {
	[super viewDidDisappear:animated];
}
*/

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}


#pragma mark Table view methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.contactArr count];
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
    // Set up the cell...
	cell.textLabel.text = [self.contactArr objectAtIndex:indexPath.row];
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	addContactViewController *viewController = [[addContactViewController alloc] 
												initWithStyle:UITableViewStyleGrouped];
	viewController.editIndex = 1;
	viewController.contactIndex = indexPath.row;
	[self.navigationController pushViewController:viewController animated:YES];
	[viewController release];
}



// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}




// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        //[tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:YES];
		NSLog(@"delete a contact");
		[self deleteContactFromAddressBookWithIndex:indexPath.row];
		[self initContactInfo];
		[self.tableView reloadData];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}



/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/


/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/


- (void)dealloc {
	[contactArr release];
    [super dealloc];
}


@end

