//
//  FontSettingsViewController.m
//  DWViewer
//
//  Created by sun on 10-10-22.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "FontSettingsViewController.h"
#import "DWViewerGUIConst.h"


@implementation FontSettingsViewController
@synthesize delegate;
@synthesize index;

#pragma mark -
#pragma mark Initialization


- (id)initWithStyle:(UITableViewStyle)style {
    if ((self = [super initWithStyle:UITableViewStylePlain])) {
		index = 0;
		list = [[NSArray alloc] initWithObjects: NSLocalizedString(@"TOOLBAR_BUTTON_CROSSBOOKS", nil), 
				NSLocalizedString(@"TOOLBAR_BUTTON_VERTICALBOOKS", nil), nil];
		
		listIconName = [[NSArray alloc] initWithObjects:_IPAD_HORIZONTAL_ICON_, 
						_IPAD_VERTICAL_ICON_, nil];
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


/*
- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
}
*/
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
	cell.imageView.image = [UIImage imageNamed:[listIconName objectAtIndex:row]];
    cell.textLabel.text = [list objectAtIndex:row];
	
	// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 start 
	// change by lixin 20110607 DW_iPhoneEnhance_12
    cell.accessoryType = (indexPath.row == index) ? UITableViewCellAccessoryCheckmark : UITableViewCellAccessoryNone;
	// 1.4表示される項目はチェックマーク付き(iPad)の状態になる の対応 end
    
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
	[delegate didFontSettingsChanged:self.index];
    
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

