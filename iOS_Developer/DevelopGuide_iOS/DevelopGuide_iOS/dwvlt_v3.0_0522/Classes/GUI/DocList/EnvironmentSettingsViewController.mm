//
//  EnvironmentSettingsViewController.m
//  DWViewer
//
//  Created by sun on 10-10-22.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "EnvironmentSettingsViewController.h"
#import "DocumentSettingsManager.h"
#import "ScaleSpecifyViewController.h"
// AR NO.17539 の対応 start
#import "Utility.h"
// AR NO.17539 の対応 end
//add by yangjx 0608 start
#import "DWViewerGUIConst.h"

// liuqw 2012.03.02 start
// アプリ内課金による機能制限
#import "DWRemoveLimitViewController.h"
// liuqw 2012.03.02 end

#define ALERT_DEL_TAG 1002
#define TAG_DEL_BUTTON 1005

// liuqw 2012.03.02 start
// アプリ内課金による機能制限
#define TAG_PAY_BUTTON 1006
// liuqw 2012.03.02 end

#define DEL_BUTTON_SIZE 30
//add by yangjx 0608 end
@implementation EnvironmentSettingsViewController
@synthesize keepDocumentStatus;
// FileSort の対応 start
@synthesize fileSortItemIndex;
@synthesize fileSortModeIndex;
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
@synthesize specifyScaleModeIndex;
@synthesize specifyScaleValue;
// 「拡大率指定の追加」の対応 end

@synthesize delegate;

#pragma mark -
#pragma mark Initialization


- (id)initWithStyle:(UITableViewStyle)style {
    if ((self = [super initWithStyle:UITableViewStyleGrouped])) {
    }
    return self;
}

#pragma mark -
#pragma mark View lifecycle


- (void)viewDidLoad {
    [super viewDidLoad];
	self.title = NSLocalizedString(@"MENU_SETTINGVIEW_TITLE", nil);
	
	// init back button.
	UIBarButtonItem *buttonBack = [[UIBarButtonItem alloc]
								   initWithTitle:NSLocalizedString(@"BUTTON_TITLE_CLOSE", nil) 
								   style:UIBarButtonItemStyleBordered 											 
								   target:self 											
								   action:@selector(actionBackToMenu)];
	self.navigationItem.leftBarButtonItem = buttonBack;
	[buttonBack release];

	// init switch button.
	self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
	buttonSwitch = [[UISwitch alloc]init];
	[buttonSwitch addTarget:self action:@selector(actionSwitchButtonValueChanged) 
		  forControlEvents:UIControlEventValueChanged];
	
	// init footer.
	CGRect footerRect = CGRectMake(0, 0, 320, 40);
	UILabel *footer = [[UILabel alloc]initWithFrame:footerRect];
	footer.backgroundColor = [self.tableView backgroundColor];
    footer.opaque = YES;
    footer.font = [UIFont boldSystemFontOfSize:10];
	footer.numberOfLines = 0; 
    footer.text = NSLocalizedString(@"MSG_VERSION", nil);
	footer.textAlignment = UITextAlignmentCenter;
    self.tableView.tableFooterView = footer;
    [footer release];
	
	//Trash file Del add by yangjx 0613 start
	// init document setting manager.
	documentSettingsMgr = [[DocumentSettingsManager alloc]init];
	//Trash file Del add by yangjx 0613 end
}

- (void)viewWillAppear:(BOOL)animated {
	
	self.navigationController.toolbar.hidden = YES;
	// set keepDocumentStatus.
	buttonSwitch.on = keepDocumentStatus;
	
	// FileSort の対応 start
	[self.tableView reloadData];
	// FileSort の対応 end
	
    [super viewWillAppear:animated];
}


- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}


- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
}


- (void)viewDidDisappear:(BOOL)animated {
    [super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation 
{
	//return YES;
	// AR NO.17539 の対応 start
	if (Utility::UIDeviceIsiPad() == NO)
	{
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
	// AR NO.17539 の対応 end
}

//modify by yangjx 0608 start
- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0)
{
    [self.tableView reloadData];
}
//modify by yangjx 0608 end

#pragma mark -
#pragma mark Table view data source
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // liuqw 2012.03.02 start
	// アプリ内課金による機能制限
	
    //return 4;
	
	return 6;
	// liuqw 2012.03.02 end
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	return 1;
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = nil;
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] 
				 initWithStyle:UITableViewCellStyleValue1 
				 reuseIdentifier:CellIdentifier] autorelease];
    }
	
    // FileSort の対応 start
	/*
	 cell.textLabel.text = NSLocalizedString(@"MSG_SAVEFILESTATE", nil);
	 cell.textLabel.font = [UIFont fontWithName:@"Arial" size:12.0];
	 cell.selectionStyle = UITableViewCellSelectionStyleNone;
	 cell.accessoryView = buttonSwitch;
	 //Ar No.22
	 cell.textLabel.numberOfLines = 2;
	 */

	if (indexPath.section == 0) 
	{
		cell.textLabel.text = NSLocalizedString(@"MSG_SAVEFILESTATE", nil);
		cell.textLabel.font = [UIFont fontWithName:@"Arial" size:12.0];
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
		cell.accessoryView = buttonSwitch;
		//Ar No.22
		cell.textLabel.numberOfLines = 2;
	}
	else if (indexPath.section == 1)
	{
		NSString *fileSortTypeLabel = @"";
		switch (fileSortItemIndex) {
			case 0:
				fileSortTypeLabel = [fileSortTypeLabel stringByAppendingString:NSLocalizedString(@"MSG_SORT_BY_FILENAME", nil)];
				break;
			case 1:
				fileSortTypeLabel = [fileSortTypeLabel stringByAppendingString:NSLocalizedString(@"MSG_SORT_BY_FILECREATEDATE", nil)];
				break;
			case 2:
				fileSortTypeLabel = [fileSortTypeLabel stringByAppendingString:NSLocalizedString(@"MSG_SORT_BY_FILESIZE", nil)];
				break;
			default:
				break;
		}
		
		fileSortTypeLabel = [fileSortTypeLabel stringByAppendingString:@" "];
		
		switch (fileSortModeIndex) {
			case 0:
				fileSortTypeLabel = [fileSortTypeLabel stringByAppendingString:NSLocalizedString(@"MSG_SORT_MODE_ASC", nil)];
				break;
			case 1:
				fileSortTypeLabel = [fileSortTypeLabel stringByAppendingString:NSLocalizedString(@"MSG_SORT_MODE_DESC", nil)];
				break;
			default:
				break;
		}

		cell.textLabel.text = NSLocalizedString(@"MSG_FILE_SORT_TYPE", nil);
		cell.textLabel.font = [UIFont fontWithName:@"Arial" size:12.0];
		cell.detailTextLabel.text = fileSortTypeLabel;
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	}
    // 「拡大率指定の追加」の対応 start
    else if (indexPath.section == 2)
	{
		NSString *labelSpecifyScale = @"";
        if (specifyScaleModeIndex == 0) {
            labelSpecifyScale = NSLocalizedString(@"TITLE_INPUT_SCALE", nil);
        } else {
            int scale = specifyScaleValue;
            NSString* message = [NSString stringWithFormat:@"%@ %d%%", NSLocalizedString(@"TITLE_FIXED_SCALE", nil), scale];
            labelSpecifyScale = message;
        }
		        
		cell.textLabel.text = NSLocalizedString(@"TITLE_SPECIFY_SCALE", nil);
		cell.textLabel.font = [UIFont fontWithName:@"Arial" size:12.0];
		cell.detailTextLabel.text = labelSpecifyScale;
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
	}
	
	// wangpp 2012.3.29 start
	// login
	else if(indexPath.section == 3)
	{
		cell.textLabel.text = NSLocalizedString(@"TITLE_LOGIN_ANNOTATION_EDIT", nil);
		cell.textLabel.font = [UIFont fontWithName:@"Arial" size:12.0];
		cell.accessoryType =  UITableViewCellAccessoryDisclosureIndicator;
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	}
	// wangpp 2012.3.29 end
	
	// liuqw 2012.03.26 start
	// アプリ内課金による機能制限
	else if (indexPath.section == 4) 
	{
		cell.textLabel.text = NSLocalizedString(@"MSG_PAYM_CELL_TEXTLABLE_TEXT", nil);
		cell.textLabel.font = [UIFont fontWithName:@"Arial" size:12.0];
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	}
	
	// liuqw 2012.03.26 end
	
    // 「拡大率指定の追加」の対応 end
    //modify by yangjx 0608 start
	
		
	// liuqw 2012.03.02 start
	// アプリ内課金による機能制限
	/*
	else if (indexPath.section == 3)
	 */
	else if (indexPath.section == 5)
	// liuqw 2012.03.02 end	
	{
        cell.selectionStyle = UITableViewCellSelectionStyleNone;

        UIButton *button = (UIButton *) [cell.contentView viewWithTag:TAG_DEL_BUTTON];
		if (button == nil) {
            // liuqw 20110623 start
            // AR NO.17869 の対応
            
            //UIButton* buttonDelete = [UIButton buttonWithType:UIButtonTypeRoundedRect];
            UIButton* buttonDelete = [UIButton buttonWithType:UIButtonTypeCustom];
            [buttonDelete setTitle:NSLocalizedString(@"MSG_DELETE_MODE", nil) 
                          forState:UIControlStateNormal];
            [buttonDelete setTitleColor:[UIColor redColor] 
                               forState:UIControlStateNormal];
            [buttonDelete addTarget:self
                             action:@selector(actionOnTouchDeleteTempFileButton) 
                   forControlEvents:UIControlEventTouchUpInside]; 
            buttonDelete.titleLabel.textAlignment = UITextAlignmentCenter;
            buttonDelete.titleLabel.font = [UIFont fontWithName:@"Arial" size:14.0];
            //buttonDelete.frame = CGRectMake(0, 0, cell.contentView.frame.size.width, 44);
            buttonDelete.frame = CGRectMake(0, 0, cell.contentView.frame.size.width, 
                                            cell.contentView.frame.size.height);
            buttonDelete.tag = TAG_DEL_BUTTON;
            
            
            if ([self isTrashEmpty] == NO)
            {
                buttonDelete.enabled = YES;
                buttonDelete.titleLabel.textColor = [UIColor redColor];
            }
            else
            {
                buttonDelete.enabled = NO;
                buttonDelete.titleLabel.textColor = [UIColor colorWithRed:0.96 
                                                                    green:0.59 
                                                                     blue:0.47 
                                                                    alpha:1];
            }
            // liuqw 20110623 end
            
            [cell.contentView addSubview:buttonDelete];
        } else {
            // liuqw 20110623 start
            // AR NO.17869 の対応
            
            //button.frame = CGRectMake(0, 0, cell.contentView.frame.size.width, 44);
            button.frame = CGRectMake(0, 0, cell.contentView.frame.size.width,  
                                      cell.contentView.frame.size.height);
            
            if ([self isTrashEmpty] == NO)
            {
                button.enabled = YES;
                button.titleLabel.textColor = [UIColor redColor];
            }
            else
            {
                button.enabled = NO;
                button.titleLabel.textColor = [UIColor colorWithRed:0.96 
                                                              green:0.59
                                                               blue:0.47 
                                                              alpha:1];
            }
            // liuqw 20110623 end
        }
    }
    //modify by yangjx 0608 end
	// FileSort の対応 end
	
    return cell;
}

// FileSort の対応 start
#pragma mark -
#pragma mark Table view delegate
//modify by yangjx 0608 start
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
	if (indexPath.section == 1) {
		FileSortSettingsViewController *filesortController = [[FileSortSettingsViewController alloc] initWithStyle:UITableViewStyleGrouped];
		filesortController.delegate = self;
		filesortController.sortItemIndex = fileSortItemIndex;
		filesortController.sortModeIndex = fileSortModeIndex;
		[self.navigationController pushViewController:filesortController animated:YES];
		[filesortController release];
    }
    // 「拡大率指定の追加」の対応 start
    else if (indexPath.section == 2)
	{
        int specifyMode = specifyScaleModeIndex;
        if (specifyScaleModeIndex == 0) {
            specifyScaleValue = 100;
        }
        int specifyScale = specifyScaleValue;
        ScaleSpecifyViewController *scaleSpecifyController = [[ScaleSpecifyViewController alloc] initWithStyle:UITableViewStyleGrouped 
                                                                                               withSpecifyMode:specifyMode 
                                                                                                withFixedScale:specifyScale];
        scaleSpecifyController.delegate = self;
		[self.navigationController pushViewController:scaleSpecifyController animated:YES];
		[scaleSpecifyController release];
	}
    // 「拡大率指定の追加」の対応 end

	// wangpp 2012.3.29 start
	// logIn
	else if (indexPath.section == 3) 
	{
		DWLoginAnnPropertySettingsController* controller = [[DWLoginAnnPropertySettingsController alloc]
															initWithActionType:kLoginActionEdit
															andOrientation:self.interfaceOrientation];
		controller.delegate = self;
		
		[self.navigationController pushViewController:controller animated:YES];
		
		[controller release];
	}
	// wangpp 2012.3.29 end
	
	// liuqw 2012.03.26 start
	// アプリ内課金による機能制限
	else if (indexPath.section == 4) {
		
		DWRemoveLimitViewController *controller_ = [[DWRemoveLimitViewController alloc]initWithStyle:UITableViewStyleGrouped];
		[self.navigationController pushViewController:controller_ animated:YES];
		[controller_ release];
	}
	
	// liuqw 2012.03.26 end
}

// FileSort の対応 end
#pragma mark -
#pragma mark alertView delegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (buttonIndex == 0) {
		//add by yangjx 0613 start
		[documentSettingsMgr deleteAllFilesFromTrashDirectory];
		//add by yangjx 0613 end
        
        // liuqw 20110623 start
        // AR NO.17869 の対応
        [self.tableView reloadData];
        // liuqw 20110623 end
	}
}
//modify by yangjx 0608 end

// wangpp 2012.4.13 start
// login
#pragma mark -
#pragma mark alertView delegate
- (void) didSelectLoginAnnotationWithAnnotationIndex:(int)index
{
	DWViewerAppDelegate* applicationDelegate_ = (DWViewerAppDelegate*)[[UIApplication sharedApplication] delegate];
	applicationDelegate_.loginSetingIndex = index;
}
// wangpp 2012.4.13 end


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


- (void) actionSwitchButtonValueChanged
{
	keepDocumentStatus = buttonSwitch.on;
	[delegate didSwitchButtonValueChanged:self];
}

// FileSort の対応 start
- (void) didFileSortCheckValueChanged:(FileSortSettingsViewController *)sender
{
	fileSortItemIndex = sender.sortItemIndex;
	fileSortModeIndex = sender.sortModeIndex;
}
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
- (void)didSpecifyScaleModeChanged:(ScaleSpecifyViewController *)sender
{
    specifyScaleModeIndex = sender.specifyScaleMode;
    specifyScaleValue = sender.fixedScale;
}
// 「拡大率指定の追加」の対応 end

- (void) actionBackToMenu
{
	DocumentSettingsManager *docSettingManager = [[DocumentSettingsManager alloc] init];
	/*
	if (keepDocumentStatus == YES) {
		[docSettingManager writeKeepDocumentStatus:keepDocumentStatus];
	} else {
		[docSettingManager deleteAllSettingsFileInDirectory];
	}
	 */
	
	// FileSort の対応 start
    // 「拡大率指定の追加」の対応 start
    /*
	[docSettingManager writeDocumentSettingsWithKeepStatus:keepDocumentStatus
									 withFileSortItemIndex:fileSortItemIndex
									 withFileSortModeIndex:fileSortModeIndex];
    */
    [docSettingManager writeDocumentSettingsWithKeepStatus:keepDocumentStatus
									 withFileSortItemIndex:fileSortItemIndex
									 withFileSortModeIndex:fileSortModeIndex 
                                           withSpecifyMode:specifyScaleModeIndex
                                          withSpecifyScale:specifyScaleValue];
    // 「拡大率指定の追加」の対応 end
	if (keepDocumentStatus == NO) {
		[docSettingManager deleteAllSettingsFileInDirectory];
	}
	// FileSort の対応 end
	
	[docSettingManager release];
	
	[self.parentViewController dismissModalViewControllerAnimated:YES];
	
}
//edit modify by yangjx 0616 start
- (void) actionOnTouchDeleteTempFileButton
{
	NSString *message = nil;
	NSInteger fileCount = 0;
	NSArray *rootPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, 
															 NSUserDomainMask, 
															 YES); 
	NSString *documentsPath = [rootPaths objectAtIndex:0];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString *trashDirectoryPath = [documentsPath stringByAppendingString:_TRASH_DIR_];
	BOOL isDirectoryExist = [fileManager fileExistsAtPath:trashDirectoryPath];
	if (isDirectoryExist) {
		NSArray *fileItemList = [fileManager contentsOfDirectoryAtPath:trashDirectoryPath error:nil];
		fileCount = [fileItemList count];
	}
	
    // liuqw 20110623 start
    // AR NO.17869 の対応
    /*
    UIAlertView *alertView = nil; 
	if (fileCount == 0) {
		message = NSLocalizedString(@"MSG_WARING_NO_TRASHFILE", nil);
		alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
											  message:message
											 delegate:self
									cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
									otherButtonTitles:nil];
	} else {
		message = [NSString stringWithFormat:NSLocalizedString(@"MSG_WARING_DELETE_FILE", nil),fileCount];
		alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
											  message:message
											 delegate:self
									cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
									otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), (char*)nil];
	}
     
    alertView.tag = ALERT_DEL_TAG;
    [alertView show];
    [alertView release]; 
    */
    if (fileCount > 0) {
		message = [NSString stringWithFormat:NSLocalizedString(@"MSG_DELETE_ALL_FILE", nil), fileCount];
		UIAlertView *alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
											  message:message
											 delegate:self
									cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
									otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), (char*)nil];
        alertView.tag = ALERT_DEL_TAG;
        [alertView show];
        [alertView release];
	}

    // liuqw 20110623 end
}
//edit modify by yangjx 0616 end

// liuqw 20110623 start
// AR NO.17869 の対応
- (BOOL) isTrashEmpty
{
    NSInteger fileCount = 0;
	NSArray *rootPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, 
															 NSUserDomainMask, 
															 YES); 
	NSString *documentsPath = [rootPaths objectAtIndex:0];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString *trashDirectoryPath = [documentsPath stringByAppendingString:_TRASH_DIR_];
	BOOL isDirectoryExist = [fileManager fileExistsAtPath:trashDirectoryPath];
	if (isDirectoryExist) {
		NSArray *fileItemList = [fileManager contentsOfDirectoryAtPath:trashDirectoryPath error:nil];
		fileCount = [fileItemList count];
	}
    
    if (fileCount > 0) {
        return NO;
    }
    
    return YES;
}
// liuqw 20110623 end

- (void)dealloc {
	[buttonSwitch release];
	//Trash file Del add by yangjx 0613 start
	[documentSettingsMgr release];
	//Trash file Del add by yangjx 0613 end
    [super dealloc];
}

@end

