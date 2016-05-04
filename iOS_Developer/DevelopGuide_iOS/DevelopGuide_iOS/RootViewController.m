//
//  RootViewController.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-9.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "RootViewController.h"
#import "GUIConst.h"
#import "Utility.h"
#import "XMLViewController.h"
#import "UIImageGuideController.h"
#import "SocketController.h"
#import "ChatViewController.h"
#import "webViewController.h"
#import "LocationViewController.h"
#import "JSONParseController.h"
#import "TimeTableViewController.h"
#import "DrawMenuViewController.h"
#import "QuickContactsViewController.h"
#import "PaomaViewController.h"
#import "TouchFrameViewController.h"
#import "CreatePDFViewController.h"
#import "PurchaseTestViewController.h"
#import "DataPersistence.h"
#import "LocationNotificationViewController.h"
#import "CoreImageViewController.h"
#import "AdViewController.h"
#import "bluetoothVoiceViewController.h"
#import "CMViewController.h"
#import "QuickLookTableController.h"
#import "MapViewController.h"
#import "AsyncTableViewController.h"
#import "QuartzTestViewController.h"
#import "CoreAnimationTestController.h"
#import "ViewController.h"
#import "AssetsLibrary.h"
#import "GifViewController.h"
#import "TouchMoveScaleDemoViewController.h"
#import "CoreDataController.h"
#import "LayerFunViewController.h"
#import "BlockTestViewController.h"
#import "nstimerViewController.h"
#import "AnimationViewController.h"
#import "MainViewController.h"
#import "Product.h"
#import "CustomerDetailViewController.h"
#import "KvoMainController.h"
#import "ImageLayerViewController.h"
#import "GCDViewController.h"
#import "NSPredicateTest.h"
#import "NotificationTestViewController.h"
#import "DSPAVideoPlayViewController.h"
#import "DSPAFocusVideoViewController.h"
@implementation RootViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = _RootViewController_TITLE_;
    NSString *path = [[Utility getResourceFilePath:_STUDYMODELIST_] retain];
    if ([path length] > 0) {
        NSDictionary *dic = [NSDictionary dictionaryWithContentsOfFile:path];
        NSArray *array_ = [dic objectForKey:DIR_KEY];
        studyList = [[NSMutableArray alloc] initWithArray:array_ 
                                                copyItems:YES];
    }

}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
  
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

/*
 // Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	// Return YES for supported orientations.
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
 */

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return [studyList count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 1;
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }

    // Configure the cell.
    cell.textLabel.text = [studyList objectAtIndex:indexPath.section];
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
        // Delete the row from the data source.
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }
    else if (editingStyle == UITableViewCellEditingStyleInsert)
    {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (indexPath.section == 0) 
    {
        XMLViewController *vc = [[XMLViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 1) 
    {
        UIImageGuideController *vc = [[UIImageGuideController alloc] initWithNibName:@"UIImageGuideController" bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 2) 
    {
        SocketController *vc = [[SocketController alloc] initWithNibName:@"SocketController" 
                                                                  bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 3) 
    {
        ChatViewController *vc = [[ChatViewController alloc] initWithNibName:@"ChatViewController" 
                                                                      bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 4) 
    {
        LocationViewController *vc = [[LocationViewController alloc] initWithNibName:@"LocationViewController" bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }

    if (indexPath.section == 5) 
    {
        webViewController *vc = [[webViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }

    if (indexPath.section == 6) 
    {
        JSONParseController *vc = [[JSONParseController alloc] initWithNibName:@"JSONParseController" bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 7) 
    {
        TimeTableViewController *vc = [[TimeTableViewController alloc] initWithNibName:@"TimeTableViewController" bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }

    if (indexPath.section == 8) 
    {
        DrawMenuViewController  *vc = [[DrawMenuViewController alloc] initWithStyle:UITableViewStylePlain];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 9) 
    {
        QuickContactsViewController *vc = [[QuickContactsViewController alloc] initWithStyle:UITableViewStyleGrouped];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    
    if (indexPath.section == 11) {
        PaomaViewController *vc = [[PaomaViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 12) {
        TouchFrameViewController *vc = [[TouchFrameViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 13) {
        CreatePDFViewController *vc = [[CreatePDFViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    
    if (indexPath.section == 14) {
        PurchaseTestViewController *vc = [[PurchaseTestViewController alloc] 
                                          initWithNibName:@"PurchaseTestViewController" 
                                          bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    
    if (indexPath.section == 15) {
        DataPersistence *vc = [[DataPersistence alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 16) {
        LocationNotificationViewController *vc = [[LocationNotificationViewController 
                                                   alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 17) {
        CoreImageViewController *vc = [[CoreImageViewController alloc] initWithNibName:@"CoreImageViewController" bundle:nil];
        [self.navigationController pushViewController:vc 
                                             animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 18) {
        AdViewController *vc = [[AdViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 19) {
        bluetoothVoiceViewController *vc = [[bluetoothVoiceViewController alloc] initWithNibName:@"bluetoothVoiceViewController" bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 20) {
        CMViewController *vc = [[CMViewController alloc] initWithNibName:@"CMViewController" 
                                                                  bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 21) {
        QuickLookTableController *vc = [[QuickLookTableController alloc] initWithStyle:UITableViewStyleGrouped];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 22) {
        MapViewController *vc = [[MapViewController alloc] 
                                 initWithNibName:@"MapViewController" bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 23) {
       AsyncTableViewController *vc  =[[AsyncTableViewController alloc] 
                                       initWithStyle:UITableViewStyleGrouped];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 24) {
        QuartzTestViewController  *vc  =[[QuartzTestViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }

    
    if (indexPath.section == 25) {
        CoreAnimationTestController *vc = [[CoreAnimationTestController alloc] 
                                           initWithNibName:@"CoreAnimationTestController" bundle:nil];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];

    }
    
    if (indexPath.section == 26) {
        ViewController *vc = [[ViewController alloc] init];
        [self.navigationController pushViewController:vc animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 27) {
        AssetsLibrary *a = [[AssetsLibrary alloc] init];
        [self.navigationController pushViewController:a 
                                             animated:YES];
        [a release];
    }
    
    if (indexPath.section == 28) {
        GifViewController *gig = [[GifViewController alloc] init];
        [self.navigationController pushViewController:gig 
                                             animated:YES];
        [gig release];
    }
    
    if (indexPath.section == 29) {
        TouchMoveScaleDemoViewController *vc = [[TouchMoveScaleDemoViewController alloc] init];
        [self.navigationController pushViewController:vc 
                                             animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 30) {
        CoreDataController *vc = [[CoreDataController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }
    
    
    if (indexPath.section == 31) {
        LayerFunViewController *vc = [[LayerFunViewController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        //[vc release];
    }
    
    if (indexPath.section == 32) {
        BlockTestViewController *vc = [[BlockTestViewController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }

    if (indexPath.section == 33) {
        nstimerViewController *vc = [[nstimerViewController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 34) {
        AnimationViewController *vc = [[AnimationViewController alloc] initWithNibName:@"AnimationViewController"
                                                                                bundle:nil];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }
   
    
    if (indexPath.section == 35)
    {
        NSArray *listContent = [[NSArray alloc] initWithObjects:
                                [Product productWithType:@"Device" name:@"iPhone"],
                                [Product productWithType:@"Device" name:@"iPod"],
                                [Product productWithType:@"Device" name:@"iPod touch"],
                                [Product productWithType:@"Desktop" name:@"iMac"],
                                [Product productWithType:@"Desktop" name:@"Mac Pro"],
                                [Product productWithType:@"Portable" name:@"iBook"],
                                [Product productWithType:@"Portable" name:@"MacBook"],
                                [Product productWithType:@"Portable" name:@"MacBook Pro"],
                                [Product productWithType:@"Portable" name:@"PowerBook"], nil];
        
        
        // Create and configure the main view controller.
        MainViewController *mainViewController = [[MainViewController alloc] initWithNibName:@"MainView" bundle:nil];
        mainViewController.listContent = listContent;
        [self.navigationController pushViewController:mainViewController
                                             animated:YES];
        [mainViewController release];
        [listContent release];

//        CustomerDetailViewController *vc = [[CustomerDetailViewController alloc] initWithStyle:UITableViewStyleGrouped];
//        [self.navigationController pushViewController:vc
//                                             animated:YES];
//        [vc release];
        }

    if (indexPath.section == 36)
    {
        KvoMainController *kvo = [[KvoMainController alloc] init];
        [self.navigationController pushViewController:kvo
                                             animated:YES];
        [kvo release];
    }
    
    
    if (indexPath.section == 37)
    {
        ImageLayerViewController *vc = [[ImageLayerViewController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 38)
    {
        GCDViewController *vc = [[GCDViewController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }

    
    if (indexPath.section == 39) {
        NSPredicateTest *vc = [[NSPredicateTest alloc] initWithNibName:@"NSPredicateTest"
                                                                bundle:nil];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }
    

    if (indexPath.section == 40)
    {
        NotificationTestViewController *vc = [[NotificationTestViewController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }
    
    if (indexPath.section == 41)
    {
        DSPAFocusVideoViewController *vc = [[DSPAFocusVideoViewController alloc] init];
        [self.navigationController pushViewController:vc
                                             animated:YES];
        [vc release];
    }

}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload
{
    //[super viewDidUnload];

    // Relinquish ownership of anything that can be recreated in viewDidLoad or on demand.
    // For example: self.myOutlet = nil;
}

- (void)dealloc
{
    [super dealloc];
}

@end
