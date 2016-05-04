//
//  DWEditFacingPageViewController.m
//  DWViewer
//
//  Created by icd-lixin on 8/13/11.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "DWEditFacingPageViewController.h"


@implementation DWEditFacingPageViewController
@synthesize delegate;

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	// 2012.02.20 M.Chikyu start.
	/*
	// 2012.02.01(Ver2.1 New) M.Chikyu
//	return YES;
	
	if (interfaceOrientation == self.interfaceOrientation)
	{
		return YES;
	}
	else
	{
		return NO;
	}
	// 2012.02.01(Ver2.1 New) M.Chikyu
	 */
	
	return YES;

	// 2012.02.20 M.Chikyu end.
}


#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 2;
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
	
	cell.textLabel.font = [UIFont fontWithName:@"Arial" size:20.0];
	
	if ([indexPath row] == 0)
	{
		cell.textLabel.text = NSLocalizedString(@"TOOLBAR_BUTTON_LEFTPAGE", nil);
	}
	else
	{
		cell.textLabel.text = NSLocalizedString(@"TOOLBAR_BUTTON_RIGHTPAGE", nil);
	}
    
    return cell;
}

#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[delegate didChoosePageToEditWithButtonIndex:[indexPath row]];
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
}


#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
}


- (void)dealloc {
    [super dealloc];
}


@end

