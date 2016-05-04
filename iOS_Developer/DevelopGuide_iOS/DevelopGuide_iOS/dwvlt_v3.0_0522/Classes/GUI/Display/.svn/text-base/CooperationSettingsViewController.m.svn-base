    //
//  CooperationSettingsViewController.m
//  DWViewer
//
//  Created by liuqw on 11-2-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CooperationSettingsViewController.h"


@implementation CooperationSettingsViewController
@synthesize delegate;

- (id)initWithStyle:(UITableViewStyle)style {
    if ((self = [super initWithStyle:UITableViewStylePlain])) {
		list = [[NSArray alloc] initWithObjects: NSLocalizedString(@"BUTTON_TITLE_SENDMAIL", nil), 
												 NSLocalizedString(@"BUTTON_TITLE_OPENMODE", nil), nil];
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
	cell.textLabel.textAlignment = UITextAlignmentLeft;
	
	NSUInteger row = [indexPath row];
    cell.textLabel.text = [list objectAtIndex:row];
    
    return cell;
}

#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[delegate didClickedCooperationMenuButtonIndex:indexPath.row];
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
    [super dealloc];
}



@end
