//
//  FacingSettingsViewController.m
//  DWViewer
//
//  Created by sun on 10-10-22.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "FacingSettingsViewController.h"
#import "DocumentViewController.h"
#import "DWViewerGUIConst.h"
#import "Utility.h"

@implementation FacingSettingsViewController
@synthesize delegate;
@synthesize index;

#pragma mark -
#pragma mark Initialization


- (id)initWithStyle:(UITableViewStyle)style {
    if ((self = [super initWithStyle:UITableViewStylePlain])) {
		index = 0;
		list = [[NSArray alloc] initWithObjects: NSLocalizedString(@"TOOLBAR_BUTTON_SINGLEPAGE", nil), 
				NSLocalizedString(@"TOOLBAR_BUTTON_FACING_WITHOUTHEADPAGE", nil), 
				NSLocalizedString(@"TOOLBAR_BUTTON_FACING_WITHHEADPAGE", nil), (char*)nil];
		
		listIconName = [[NSArray alloc] initWithObjects:_IPAD_FACING_SINGLE_ICON_, 
						_IPAD_FACING_DOUBLE_ICON_, _IPAD_FACING_FRONTCOVER_ICON_, (char*)nil];
    }
    return self;
}

#pragma mark -
#pragma mark View lifecycle


- (void)viewDidLoad {
	//[self.view setBackgroundColor:[UIColor blackColor]];
	//self.tableView.rowHeight = 30.0;
	//[self.view setAlpha:0.5];
	[super viewDidLoad];
}

// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if (Utility::UIDeviceIsiPad() == NO)
	{
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
}

#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // Return the number of rows in the section.
    return [list count];
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault 
									   reuseIdentifier:CellIdentifier] autorelease];
    }
	cell.textLabel.font = [UIFont fontWithName:@"Arial" size:20.0];
	//cell.textLabel.textColor = [UIColor whiteColor];
	cell.textLabel.textAlignment = UITextAlignmentLeft;
	
	NSUInteger row = [indexPath row];
    cell.textLabel.text = [list objectAtIndex:row];
	cell.imageView.image = [UIImage imageNamed:[listIconName objectAtIndex:row]];
	
	// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 start 
	// change by lixin 20110607  DW_iPhoneEnhance_12
    cell.accessoryType = (indexPath.row == index) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
	// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 end
	
    return cell;
}

#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	int newRow = [indexPath row];
    int oldRow = index;

    if (newRow != oldRow)
    {
		// AR No.19
        index = indexPath.row;
    }
	//modify Toolbar subMenu by sun.chl 101126
	[delegate didFacingSettingsChanged:self.index];
	
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}


#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    // Relinquish ownership of anything that can be recreated in viewDidLoad or on demand.
    // For example: self.myOutlet = nil;
}

- (void)dealloc {
	[list release];
	// Memory Leak の対応 start
	[listIconName release];
	// Memory Leak の対応 end
    [super dealloc];
}

@end

