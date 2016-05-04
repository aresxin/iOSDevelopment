//
//  FileSortSettingsViewController.m
//  DWViewer
//
//  Created by liuqw on 11-2-18.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "FileSortSettingsViewController.h"
#import "Utility.h"
// yangjx 20110622 start
// AR17848 sortの対応
#import "DocumentSettingsManager.h"
// yangjx 20110622 end
@implementation FileSortSettingsViewController

@synthesize sortItemIndex;
@synthesize sortModeIndex;
@synthesize delegate;

#pragma mark -
#pragma mark Initialization


- (id)initWithStyle:(UITableViewStyle)style {
    // Override initWithStyle: if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
    if ((self = [super initWithStyle:style])) {
    }
    return self;
}



#pragma mark -
#pragma mark View lifecycle


- (void)viewDidLoad {
    [super viewDidLoad];
	self.title = NSLocalizedString(@"MSG_FILE_SORT_TITLE", nil);
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
	
	// yangjx 20110622 start
	// AR17848 sortの対応
	self.navigationController.toolbar.hidden = YES;
	// yangjx 20110622 end
}



- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}
// yangjx 20110622 start
// AR17848 sortの対応
- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
	DocumentSettingsManager *documentSettingsMgr = [[DocumentSettingsManager alloc] init];
	[documentSettingsMgr writeDocumentSettingsWithFileSortItemIndex:sortItemIndex 
											  withFileSortModeIndex:sortModeIndex];
	[documentSettingsMgr release];
}
// yangjx 20110622 end
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
    return 2;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // Return the number of rows in the section.
	if (section == 0) 
		return 3;
	else
		return 2;
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];

    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
		cell.selected = NO;
		
		// liuqw 20110329 start
		// ソート機能の不具合の対応
		
		//cell.selectionStyle = UITableViewCellSelectionStyleNone;
		cell.selectionStyle = UITableViewCellSelectionStyleBlue;
		
		// liuqw 20110329 end
    }
	
	if (indexPath.section == 0) 
	{
		switch (indexPath.row) {
			case 0:
				cell.textLabel.text = NSLocalizedString(@"MSG_SORT_BY_FILENAME", nil);
				if (sortItemIndex == 0) {
					cell.accessoryType = UITableViewCellAccessoryCheckmark;
				}
				break;
			case 1:
				cell.textLabel.text = NSLocalizedString(@"MSG_SORT_BY_FILECREATEDATE", nil);
				if (sortItemIndex == 1) {
					cell.accessoryType = UITableViewCellAccessoryCheckmark;
				}
				break;
			case 2:
				cell.textLabel.text = NSLocalizedString(@"MSG_SORT_BY_FILESIZE", nil);
				if (sortItemIndex == 2) {
					cell.accessoryType = UITableViewCellAccessoryCheckmark;
				}
				break;
			default:
				break;
		}
	}
	else 
	{
		switch (indexPath.row) {
			case 0:
				cell.textLabel.text = NSLocalizedString(@"MSG_SORT_MODE_ASC", nil);
				if (sortModeIndex == 0) {
					cell.accessoryType = UITableViewCellAccessoryCheckmark;
				}
				break;
			case 1:
				cell.textLabel.text = NSLocalizedString(@"MSG_SORT_MODE_DESC", nil);
				if (sortModeIndex == 1) {
					cell.accessoryType = UITableViewCellAccessoryCheckmark;
				}
				break;
			default:
				break;
		}
	}
	
    return cell;
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
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
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


#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
	
	cell.accessoryType = UITableViewCellAccessoryCheckmark;
	
	if (indexPath.section == 0)
	{
		sortItemIndex = indexPath.row;
	} 
	else 
	{
		sortModeIndex = indexPath.row;
	}

	[delegate didFileSortCheckValueChanged:self];
	
}

-(NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSIndexPath *oldIndexPath = nil;
	
	switch (indexPath.section) {
		case 0:
			oldIndexPath = [NSIndexPath indexPathForRow:sortItemIndex inSection:indexPath.section];
			break;
		case 1:
			oldIndexPath = [NSIndexPath indexPathForRow:sortModeIndex inSection:indexPath.section];
			break;
		default:
			break;
	}
	
	UITableViewCell *oldcell = [tableView cellForRowAtIndexPath:oldIndexPath];
	if (oldIndexPath != indexPath) 
	{
		oldcell.accessoryType = UITableViewCellAccessoryNone;
	}
	else 
	{
		return nil;
	}
	
	return indexPath;
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
    [super dealloc];
}


@end

