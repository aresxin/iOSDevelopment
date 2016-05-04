//
//  addContactViewController.m
//  QuickContacts
//
//  Created by 杨 金鑫 on 11-5-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "addContactViewController.h"


@implementation addContactViewController
@synthesize editIndex;
@synthesize contactIndex;
- (id)initWithStyle:(UITableViewStyle)style {
    // Override initWithStyle: if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
    if (self = [super initWithStyle:style]) {
		titleArr = [[NSMutableArray alloc] initWithObjects:@"FirstName:",@"LastName:",@"iPhone:",nil];
    }
    return self;
}



- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
	[self initFooter];
	
	// 2. init name field
	CGRect textFieldRect = CGRectMake(125, 8, 160, 28);
	fieldContactName = [[UITextField alloc] initWithFrame:textFieldRect];
	fieldContactName.borderStyle = UITextBorderStyleRoundedRect;
	fieldContactName.tag = 100;
	fieldContactName.returnKeyType = UIReturnKeyDone;
	[fieldContactName addTarget:self
						 action:@selector(actionTextFieldEndEdit:)
			   forControlEvents:UIControlEventEditingDidEndOnExit];
	
	fieldlastName = [[UITextField alloc] initWithFrame:textFieldRect];
	fieldlastName.borderStyle = UITextBorderStyleRoundedRect;
	fieldlastName.tag = 101;
	fieldlastName.returnKeyType = UIReturnKeyDone;
	[fieldlastName addTarget:self
						 action:@selector(actionTextFieldEndEdit:)
			   forControlEvents:UIControlEventEditingDidEndOnExit];
	
	// 3. init tel num field
	fieldTelNum = [[UITextField alloc] initWithFrame:textFieldRect];
	fieldTelNum.borderStyle = UITextBorderStyleRoundedRect;
	fieldTelNum.tag = 102;
	fieldTelNum.returnKeyType = UIReturnKeyDone;
	[fieldTelNum addTarget:self
						 action:@selector(actionTextFieldEndEdit:)
			   forControlEvents:UIControlEventEditingDidEndOnExit];
	if (editIndex == 1) {
		[self initEditContactInfo];
	}
	
}
#pragma mark -
#pragma mark init
- (void) initEditContactInfo
{
	//返回所有联系人到一个数组中
	ABAddressBookRef addressBook = ABAddressBookCreate();
	CFArrayRef personArray = ABAddressBookCopyArrayOfAllPeople(addressBook);
	ABRecordRef ref = CFArrayGetValueAtIndex(personArray, contactIndex);
	fieldContactName.text = (NSString *)ABRecordCopyValue(ref, kABPersonFirstNameProperty);
	fieldlastName.text = (NSString *)ABRecordCopyValue(ref, kABPersonLastNameProperty);
	ABMultiValueRef phones = (ABMultiValueRef) ABRecordCopyValue(ref, kABPersonPhoneProperty);
	if (ABMultiValueGetCount(phones) != 0) {
		fieldTelNum.text = (NSString *)ABMultiValueCopyValueAtIndex(phones, 0);
	}
	//释放内存
	CFRelease(personArray);
	CFRelease(phones);
	CFRelease(addressBook);
	
	
}

- (void) initFooter
{
	// init footerView 
	CGRect footerViewRect = CGRectMake(0, 0, 320, 60);
	UIView *footerView = [[UIView alloc] initWithFrame:footerViewRect];
	footerView.backgroundColor = [self.tableView backgroundColor];
	//add button into view
	if (editIndex == 0) {
		UIButton* buttonStartSelect = [UIButton buttonWithType:UIButtonTypeRoundedRect];
		buttonStartSelect.frame = CGRectMake(5, 0, 310, 40);
		[buttonStartSelect setTitle:@"ADD" forState:UIControlStateNormal];
		[buttonStartSelect addTarget:self action:@selector(actionTouchAddButton) 
					forControlEvents:UIControlEventTouchUpInside]; 
		[footerView addSubview:buttonStartSelect];
		
	}else {
		UIButton* buttonEdit = [UIButton buttonWithType:UIButtonTypeRoundedRect];
		buttonEdit.frame = CGRectMake(5, 0, 310, 40);
		[buttonEdit setTitle:@"EDIT DONE" forState:UIControlStateNormal];
		[buttonEdit addTarget:self action:@selector(actionTouchEditButton) 
			 forControlEvents:UIControlEventTouchUpInside]; 
		[footerView addSubview:buttonEdit];		
	}
	self.tableView.tableFooterView = footerView;
	[footerView release];  
	
}
#pragma mark -
#pragma mark action
- (void)actionTextFieldEndEdit:(id)sender
{
	[sender resignFirstResponder];
}
//修改联系人
- (void) actionTouchEditButton
{
	if ([fieldTelNum.text length] == 0 
		|| [fieldContactName.text length] == 0
		|| [fieldlastName.text length] == 0)
	{
		UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:nil
														   message:@"信息不完整!"
														  delegate:self
												 cancelButtonTitle:@"确定"
												 otherButtonTitles:nil, (char*)nil];
		
		[alertView show];
		[alertView release];	
		
	}
	else
	{
		CFErrorRef error = NULL;
		BOOL result;
		//返回所有联系人到一个数组中
		ABAddressBookRef addressBook = ABAddressBookCreate();
		CFArrayRef personArray = ABAddressBookCopyArrayOfAllPeople(addressBook);
		ABRecordRef ref = CFArrayGetValueAtIndex(personArray, contactIndex);
		//modify contactInfo
		//设置相关属性
		result = ABRecordSetValue(ref, kABPersonFirstNameProperty, 
								  (CFStringRef)fieldContactName.text, &error) 
		&&
		ABRecordSetValue(ref, kABPersonLastNameProperty, 
						 (CFStringRef)fieldlastName.text, &error)
		&&
		[self addPhone:ref phone:fieldTelNum.text];
		
		// 保存到地址本
		result = ABAddressBookSave(addressBook, &error);
		
		//释放内存
		CFRelease(personArray);
		CFRelease(addressBook);
		
		[self.navigationController popViewControllerAnimated:YES];
		
	}
}
//增加联系人
- (void) actionTouchAddButton
{
	if ([fieldTelNum.text length] == 0 
		|| [fieldContactName.text length] == 0
		|| [fieldlastName.text length] == 0)
	{
		UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:nil
														   message:@"信息不完整!"
														  delegate:self
												 cancelButtonTitle:@"确定"
												 otherButtonTitles:nil, (char*)nil];
		
		[alertView show];
		[alertView release];	
		
	}
	else 
	{
		ABAddressBookRef addressBook = ABAddressBookCreate();
		
		CFErrorRef error = NULL;
		BOOL result;
		
		//创建一个空记录
		ABRecordRef person = ABPersonCreate();
		
		//设置相关属性
		result = ABRecordSetValue(person, kABPersonFirstNameProperty, 
								  (CFStringRef)fieldContactName.text, &error) 
		&&
		ABRecordSetValue(person, kABPersonLastNameProperty, 
						 (CFStringRef)fieldlastName.text, &error)
		&&
		[self addPhone:person phone:fieldTelNum.text];
		
		//增加记录
		result = ABAddressBookAddRecord(addressBook, person, &error);
		
		// 保存到地址本
		result = ABAddressBookSave(addressBook, &error);
		//release
		CFRelease(addressBook);
		CFRelease(person);
		[self.navigationController popViewControllerAnimated:YES];
	}
}

- (BOOL)addPhone:(ABRecordRef)person phone:(NSString*)phone
{
	ABMutableMultiValueRef multi = ABMultiValueCreateMutable(kABMultiStringPropertyType);
	
	CFErrorRef anError = NULL;
	
	ABMultiValueIdentifier multivalueIdentifier;
	
	if (!ABMultiValueAddValueAndLabel(multi, (CFStringRef)phone, kABPersonPhoneMobileLabel, &multivalueIdentifier)){
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
- (BOOL)addAddress:(ABRecordRef)person street:(NSString*)street
{
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
	values[0] = (CFStringRef)street;
	values[1] = CFSTR("dssd");
	values[2] = CFSTR("dsd");
	values[3] = CFSTR("ds");
	values[4] = CFSTR("dsd");
	
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
//添加图片
+ (BOOL)addImage:(ABRecordRef)person image:(UIImage*)image
{
	CFErrorRef error = NULL;
	
	// remove old image data firstly
	ABPersonRemoveImageData(person, NULL);
	
	// add new image data
	BOOL result = ABPersonSetImageData (
										person,
										(CFDataRef)UIImagePNGRepresentation(image),
										&error
										);
	
	//    CFRelease(error);
	
	return result;
}


- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
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
    return [titleArr count];
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
    // Set up the cell...
	cell.textLabel.text = [titleArr objectAtIndex:indexPath.row];
	switch (indexPath.row) {
		case 0:
			[cell.contentView addSubview:fieldContactName];
			break;
		case 1:
			[cell.contentView addSubview:fieldlastName];
			break;
		case 2:
			[cell.contentView addSubview:fieldTelNum];
			break;
		default:
			break;
	}
	return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    // Navigation logic may go here. Create and push another view controller.
	// AnotherViewController *anotherViewController = [[AnotherViewController alloc] initWithNibName:@"AnotherView" bundle:nil];
	// [self.navigationController pushViewController:anotherViewController];
	// [anotherViewController release];
}


/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/


/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:YES];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/


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
	[titleArr release];
	[fieldTelNum release];
	[fieldContactName release];
	[fieldlastName release];
    [super dealloc];
}


@end

