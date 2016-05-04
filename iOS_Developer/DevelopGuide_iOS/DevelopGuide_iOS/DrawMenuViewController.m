//
//  DrawMenuViewController.m
//  DrawLine
//
//  Created by neusoft  on 11-7-11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawMenuViewController.h"
#import "DrawLineViewController.h"
#import "DrawText.h"
#import "DrawtextViewController.h"
#import "DrawCurvesViewController.h"
#import "DrawAnagrViewController.h"
#import "DrawMaskImageViewController.h"
#import "DrawClippingViewController.h"
#import "DrawChartViewController.h"

@implementation DrawMenuViewController


#pragma mark -
#pragma mark Initialization


- (id)initWithStyle:(UITableViewStyle)style {
    // Override initWithStyle: if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization.
		titleList = [[NSMutableArray alloc] init];
		[titleList addObject:@"Draw Line"];
		[titleList addObject:@"Draw Text"];
		[titleList addObject:@"Draw Curves"];
		[titleList addObject:@"Draw Analyze"];
		[titleList addObject:@"Draw MaskImage"];
		[titleList addObject:@"Draw Clipping"];
        [titleList addObject:@"Draw Chart"];
    }
    return self;
}



#pragma mark -
#pragma mark View lifecycle


- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
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
    // Return YES for supported orientations.
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
    return [titleList count];
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
    // Configure the cell...
    cell.textLabel.text = [titleList objectAtIndex:indexPath.row];
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
        // Delete the row from the data source.
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
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
    // Navigation logic may go here. Create and push another view controller.
	switch (indexPath.row) {
		case 0:
			;
			DrawLineViewController *line = [[DrawLineViewController alloc] initWithNibName:@"DrawLineViewController" bundle:nil];
			[self.navigationController pushViewController:line animated:YES];
			[line release];
			break;
		case 1:
			;
			DrawtextViewController *drawT = [[DrawtextViewController alloc] init];
			[self.navigationController pushViewController:drawT animated:YES];
			[drawT release];
			break;
		case 2:
			;
			DrawCurvesViewController *curcontroller = [[DrawCurvesViewController alloc] init];
			[self.navigationController pushViewController:curcontroller animated:YES];
			[curcontroller release];
			break;
		case 3:
			;
			DrawAnagrViewController *dA = [[DrawAnagrViewController alloc] init];
			[self.navigationController pushViewController:dA animated:YES];
			[dA release];
			break;
		case 4:
			;
			DrawMaskImageViewController *mask = [[DrawMaskImageViewController alloc] init];
			[self.navigationController pushViewController:mask animated:YES];
			[mask release];
				
			break;
		case 5:
			;
			DrawClippingViewController *clip = [[DrawClippingViewController alloc] init];	
			[self.navigationController pushViewController:clip animated:YES];
			[clip release];
			break;
        case 6:
            ;
            DrawChartViewController *chart = [[DrawChartViewController alloc] init];
            [self.navigationController pushViewController:chart animated:YES];
            [chart release];
            break;
			
		default:
			break;
	}
	
}


#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    // Relinquish ownership of anything that can be recreated in viewDidLoad or on demand.
    // For example: self.myOutlet = nil;
}


- (void)dealloc {
	[titleList release];
    [super dealloc];
}


@end

