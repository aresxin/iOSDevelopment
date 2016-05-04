//
//  QuickLookTableController.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-4-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "QuickLookTableController.h"


@implementation QuickLookTableController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
//        files = [[NSMutableArray alloc] initWithObjects:@"Text Document.txt",
//                 @"Image Document.jpg",
//                 @"PDF Document.pdf",
//                 @"HTML Document.html", nil];
        files = [[NSMutableArray alloc] initWithObjects:
                                @"VID_20130724_143040.mp4",
                  nil];

    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void) dealloc
{
    [files release];
    [super dealloc];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
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

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [files count];
}

#pragma mark -
#pragma mark fileSize
/*
 * 将文件的size转换为字符串
 */
- (NSString *)formattedFileSize:(unsigned long long)size
{
	NSString *formattedStr = nil;
    if (size == 0) 
		formattedStr = @"Empty";
	else 
		if (size > 0 && size < 1024) 
			formattedStr = [NSString stringWithFormat:@"%qu bytes", size];
        else 
            if (size >= 1024 && size < pow(1024, 2)) 
                formattedStr = [NSString stringWithFormat:@"%.1f KB", (size / 1024.)];
            else 
                if (size >= pow(1024, 2) && size < pow(1024, 3))
                    formattedStr = [NSString stringWithFormat:@"%.2f MB", (size / pow(1024, 2))];
                else 
                    if (size >= pow(1024, 3)) 
                        formattedStr = [NSString stringWithFormat:@"%.3f GB", (size / pow(1024, 3))];
	
	return formattedStr;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
    }
    
    // Configure the cell...
    cell.textLabel.text = [files objectAtIndex:indexPath.row];
    NSError *error;
//    NSString *fileURLString = [NSURL fileURLWithPath:[[NSBundle mainBundle] pathForResource:[files objectAtIndex:indexPath.row] ofType:nil]];
    NSString *fileURLString = [[NSBundle mainBundle] pathForResource:[files objectAtIndex:indexPath.row] ofType:nil];

    NSDictionary *fileAttributes = [[NSFileManager defaultManager] attributesOfItemAtPath:fileURLString  error:&error];
    NSInteger fileSize = [[fileAttributes objectForKey:NSFileSize] intValue];
    
    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@",
                                 [self formattedFileSize:fileSize]];
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

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    QLPreviewController *previewController = [[QLPreviewController alloc] init];
    previewController.dataSource = self;
    previewController.delegate = self;
    
    // start previewing the document at the current section index
    //previewController.currentPreviewItemIndex = indexPath.row;
    previewController.currentPreviewItemIndex = indexPath.row;
    [[self navigationController] pushViewController:previewController animated:YES];
    [previewController release];

}

#pragma mark -
#pragma mark QLPreviewControllerDataSource

// Returns the number of items that the preview controller should preview
- (NSInteger)numberOfPreviewItemsInPreviewController:(QLPreviewController *)previewController
{
    return [files count];
}


// returns the item that the preview controller should preview
- (id)previewController:(QLPreviewController *)previewController previewItemAtIndex:(NSInteger)idx
{
    NSURL *fileURL = nil;
    
    //NSError *error;
    NSString *docPath = [[NSBundle mainBundle] pathForResource:[files objectAtIndex:idx] 
                                                        ofType:nil];
    fileURL = [NSURL fileURLWithPath:docPath];
    
    BOOL res = [QLPreviewController canPreviewItem:fileURL];
	if (res)
	{
		NSLog(@"OK");
	}
    return fileURL;
}

#pragma mark -
#pragma mark QLPreviewControllerDelegate
/*!
 * @abstract Invoked before the preview controller is closed.
 */
- (void)previewControllerWillDismiss:(QLPreviewController *)controller
{
    
}
- (void)previewControllerDidDismiss:(QLPreviewController *)controller
{
    // if the preview dismissed (done button touched), use this method to post-process previews
}

/*!
 * @abstract Invoked by the preview controller before trying to open an URL tapped in the preview.
 * @result Returns NO to prevent the preview controller from calling -[UIApplication openURL:] on url.
 * @discussion If not implemented, defaults is YES.
 */
- (BOOL)previewController:(QLPreviewController *)controller shouldOpenURL:(NSURL *)url forPreviewItem:(id <QLPreviewItem>)item
{
    return YES;
}

/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a zoom effect.
 * @discussion Return the origin of the zoom. It should be relative to view, or screen based if view is not set. The controller will fade in/out if the rect is CGRectZero.
 */
/*
- (CGRect)previewController:(QLPreviewController *)controller frameForPreviewItem:(id <QLPreviewItem>)item inSourceView:(UIView **)view
{
}
*/
/*!
 * @abstract Invoked when the preview controller is about to be presented full screen or dismissed from full screen, to provide a smooth transition when zooming.
 * @param contentRect The rect within the image that actually represents the content of the document. For example, for icons the actual rect is generally smaller than the icon itself.
 * @discussion Return an image the controller will crossfade with when zooming. You can specify the actual "document" content rect in the image in contentRect.
 */
/*
- (UIImage *)previewController:(QLPreviewController *)controller transitionImageForPreviewItem:(id <QLPreviewItem>)item contentRect:(CGRect *)contentRect
{}
 */
@end
