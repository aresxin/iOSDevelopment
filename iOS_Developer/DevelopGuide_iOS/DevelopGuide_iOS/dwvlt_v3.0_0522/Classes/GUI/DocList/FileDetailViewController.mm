//
//  FileDetailViewController.m
//  DWViewer
//
//  Created by tongtiexin on 11-6-3.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "FileDetailViewController.h"
#import "DWFileInfo.h"
#import "Utility.h"
#import "DWViewerGUIConst.h"
#import "DocumentSettingsManager.h"

#define LOCALSTRING(_S_) NSLocalizedString(_S_,nil)
#define TAG_UPDATE_NAME 100
#define CELL_DETAIL_LABEL_HEIGHT 25
#define TAG_CELL_TEXT_LABEL 10
#define CELL_DEFAULT_HEIGHT 44.0

// zhaijie 2012.03.30 start
// 『セキュリティ』の情報の対応
#define TAG_CELL_TEXT_LABEL_SEC  11
#define TAG_CELL_VALUE_LABEL_SEC 12
// zhaijie 2012.03.30 start

// lixin 2011/10/10 start 
// NS-AR2001 の対応
/*
// 20110622 tongtx start
// AR17856 の対応
//#define DETAIL_LABEL_MAX_WIDTH_IPHONE 260
#define DETAIL_LABEL_MAX_VWIDTH_IPHONE 187
// 20110622 tongtx end

//#define DETAIL_LABEL_MAX_WIDTH_IPAD 554
#define DETAIL_LABEL_DEFAULT_HEIGHT 19
#define DETAIL_LABEL_MAX_ROWS 100

#define DETAIL_LABEL_MAX_HWIDTH_IPHONE 347
#define DETAIL_LABEL_DEFAULT_FONT_SIZE 15
#define DETAIL_LABEL_MAX_VWIDTH_IPAD 565
#define DETAIL_LABEL_MAX_HWIDTH_IPAD 821
*/
#define DETAIL_LABEL_MAX_VWIDTH_IPHONE 207
#define DETAIL_LABEL_DEFAULT_HEIGHT 14
#define DETAIL_LABEL_MAX_ROWS 0
#define DETAIL_LABEL_MAX_HWIDTH_IPHONE 367
#define DETAIL_LABEL_MAX_VWIDTH_IPAD 581
#define DETAIL_LABEL_MAX_HWIDTH_IPAD 840
#define DETAIL_LABEL_MAX_HEIGHT      20000
// lixin 2011/10/10 end

@implementation FileDetailViewController

#pragma mark -
#pragma mark Initialization

- (id)initWithStyle:(UITableViewStyle)style andFileInfo:(DWFileInfo *)fInfo
{
    self = [super initWithStyle:style];
    if (self) {
		if (fInfo == nil) {
			return nil;
		}
		fileInfo = [fInfo retain];

		documentSettingsMgr = [[DocumentSettingsManager alloc] init];
		[self initTitlesAndContents];
		//maxWidth = Utility::UIDeviceIsiPad() ? DETAIL_LABEL_MAX_WIDTH_IPAD:DETAIL_LABEL_MAX_HWIDTH_IPHONE;
    }
    return self;
}
#pragma mark -
#pragma mark initialized titles and contents
- (void) initTitlesAndContents 
{
	titles = [[NSMutableArray alloc] init];
	contents = [[NSMutableArray alloc] init];
	
    // 1. init first section 
	NSArray *firstSectionTitles = [NSArray arrayWithObjects:LOCALSTRING(@"MSG_FILE_NAME"),
                                   LOCALSTRING(@"MSG_FILE_MODIFIED_DATE"),
                                   LOCALSTRING(@"MSG_FILE_SIZE"),(char*)0];
	NSArray *firstSectionValues = [NSMutableArray arrayWithObjects:fileInfo.fileName,
                                   fileInfo.fileUpdateDate,fileInfo.fileSize,(char*)nil];
	
	// 2. init second section 
	NSMutableArray *secondSectionTitles = [NSMutableArray arrayWithCapacity:3];
	NSMutableArray *secondSectionValues = [NSMutableArray arrayWithCapacity:3]; 
	
	// zhaijie 2012.03.30 start
	// 『セキュリティ』の情報の対応
	
	/*
	if (fileInfo.fileTitle != nil) {
		[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_TITLE")];
		[secondSectionValues addObject:fileInfo.fileTitle];
	}
	if (fileInfo.fileSubtitle != nil) {
		[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_SUBTITLE")];
		[secondSectionValues addObject:fileInfo.fileSubtitle];
	}
	if (fileInfo.fileAuthor != nil) {
		[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_AUTHOR")];
		[secondSectionValues addObject:fileInfo.fileAuthor];
	}
	*/
	
	if (fileInfo.fileProtected == YES)
	{
		[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_TITLE")];
		[secondSectionValues addObject:@""];
		
		[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_SUBTITLE")];
		[secondSectionValues addObject:@""];
		
		[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_AUTHOR")];
		[secondSectionValues addObject:@""];
	}
	else
	{
		if (fileInfo.fileTitle != nil) {
			[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_TITLE")];
			[secondSectionValues addObject:fileInfo.fileTitle];
		}
		if (fileInfo.fileSubtitle != nil) {
			[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_SUBTITLE")];
			[secondSectionValues addObject:fileInfo.fileSubtitle];
		}
		if (fileInfo.fileAuthor != nil) {
			[secondSectionTitles addObject:LOCALSTRING(@"MSG_FILE_AUTHOR")];
			[secondSectionValues addObject:fileInfo.fileAuthor];
		}
	}
	
	
	
	// 3. init third section 
	NSMutableArray *thirdSectionTitles = [NSMutableArray arrayWithCapacity:2];
	NSMutableArray *thirdSectionValues = [NSMutableArray arrayWithCapacity:2];
	
	// zhaijie 2012.03.30 start
	// 『セキュリティ』の情報の対応
	
	/*
	if (fileInfo.fileKeyword != nil) {
		[thirdSectionTitles addObject:LOCALSTRING(@"MSG_FILE_KEYWORD")];
		[thirdSectionValues addObject:fileInfo.fileKeyword];
	}
	if (fileInfo.fileRemark != nil) {
		[thirdSectionTitles addObject:LOCALSTRING(@"MSG_FILE_REMARK")];
		[thirdSectionValues addObject:fileInfo.fileRemark];
	}
	 */
	
	if (fileInfo.fileProtected == YES)
	{
		[thirdSectionTitles addObject:LOCALSTRING(@"MSG_FILE_KEYWORD")];
		[thirdSectionValues addObject:@""];
		
		[thirdSectionTitles addObject:LOCALSTRING(@"MSG_FILE_REMARK")];
		[thirdSectionValues addObject:@""];
	}
	else
	{
		if (fileInfo.fileKeyword != nil) {
			[thirdSectionTitles addObject:LOCALSTRING(@"MSG_FILE_KEYWORD")];
			[thirdSectionValues addObject:fileInfo.fileKeyword];
		}
		if (fileInfo.fileRemark != nil) {
			[thirdSectionTitles addObject:LOCALSTRING(@"MSG_FILE_REMARK")];
			[thirdSectionValues addObject:fileInfo.fileRemark];
		}
	}
	
	
	// 4. init forth section 
	NSArray *fouthSectionTitles = [NSArray arrayWithObjects:LOCALSTRING(@"BUTTON_TITLE_SENDMAIL"),
								   LOCALSTRING(@"BUTTON_TITLE_OPENMODE"),(char*)nil];
	
	[titles addObject:firstSectionTitles];
	[contents addObject:firstSectionValues];
	if ([secondSectionTitles count] > 0) {
		[titles addObject:secondSectionTitles];
		[contents addObject:secondSectionValues];
	}
	if ([thirdSectionTitles count] > 0) {
		[titles addObject:thirdSectionTitles];
		[contents addObject:thirdSectionValues];
	}
	
	// zhaijie 2012.03.30 start
	// 『セキュリティ』の情報の対応

	if (fileInfo.fileProtected == YES)
	{
		// 5.init protect file section
		NSMutableArray *protectSectionTitles = [NSMutableArray arrayWithCapacity:4];
		NSMutableArray *protectSectionValues = [NSMutableArray arrayWithCapacity:4];
		
		// 5.1.Document Edit
		[protectSectionTitles addObject:LOCALSTRING(@"MSG_DOC_EDIT")];
		if ((fileInfo.filePermission & MP_PERM_DOC_EDIT) == MP_PERM_DOC_EDIT) 
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_PERMISSION")];
		}
		else
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_UNPERMISSION")];
		}
		// 5.2.Annotation Edit
		[protectSectionTitles addObject:LOCALSTRING(@"MSG_ANNO_EDIT")];
		if ((fileInfo.filePermission & MP_PERM_ANNO_EDIT) == MP_PERM_ANNO_EDIT) 
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_PERMISSION")];
		}
		else
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_UNPERMISSION")];
		}
		// 5.3.Print
		[protectSectionTitles addObject:LOCALSTRING(@"MSG_PRINT")];
		if ((fileInfo.filePermission & MP_PERM_PRINT) == MP_PERM_PRINT) 
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_PERMISSION")];
		}
		else
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_UNPERMISSION")];
		}
		// 5.4.Copy
		[protectSectionTitles addObject:LOCALSTRING(@"MSG_COPY")];
		if ((fileInfo.filePermission & MP_PERM_COPY) == MP_PERM_COPY) 
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_PERMISSION")];
		}
		else
		{
			[protectSectionValues addObject:LOCALSTRING(@"MSG_GET_RESULT_UNPERMISSION")];
		}
		
		[titles addObject:protectSectionTitles];
		[contents addObject:protectSectionValues];		
	}
	
	// zhaijie 2012.03.30 end
	
	[titles addObject:fouthSectionTitles];
}

#pragma mark -
#pragma mark View lifecycle
- (void)viewDidLoad {
    [super viewDidLoad];
	self.title = NSLocalizedString(@"MSG_FILE_TABLE_TITLE",nil);
    
    // yangjx 20110711 start
	// AR 17919 の対応
	self.navigationController.navigationBar.hidden = NO;
	// yangjx 20110711 end
	
	// zhaijie 2012.03.30 start
	// 『セキュリティ』の情報の対応
	orientation_ = self.interfaceOrientation;
	// zhaijie 2012.03.30 end
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if (interfaceOrientation == UIInterfaceOrientationPortrait ||
		interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
	{
		maxWidth = Utility::UIDeviceIsiPad() ? DETAIL_LABEL_MAX_VWIDTH_IPAD:DETAIL_LABEL_MAX_VWIDTH_IPHONE;
	}
	else 
    {
		maxWidth = Utility::UIDeviceIsiPad() ? DETAIL_LABEL_MAX_HWIDTH_IPAD:DETAIL_LABEL_MAX_HWIDTH_IPHONE;
	}

   	if (Utility::UIDeviceIsiPad() == NO)
	{
		return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
	}
	else
	{
		return YES;
	}
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    if ([fileUpdateAlert isVisible]) {
        UITextField* field = (UITextField *)[fileUpdateAlert viewWithTag:TAG_UPDATE_NAME];
        [self resetTextFieldFrameForRotation:field withOrientation:toInterfaceOrientation];
	}
	
	// zhaijie 2012.03.30 start
	// 『セキュリティ』の情報の対応
	orientation_ = toInterfaceOrientation;
	[self.tableView reloadData];
	// zhaijie 2012.03.30 end
}

#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return [titles count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [[titles objectAtIndex:section] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = nil;
	static NSString *CellIdentifier2 = nil;
    UITableViewCell *cell = nil;

	if (indexPath.section != [titles count] - 1) {
		cell = 	[tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	} else {
		cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier2];
	}
    
    if (cell == nil) {
		if (indexPath.section != [titles count] - 1 ) {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue2 reuseIdentifier:CellIdentifier] autorelease];
		} else {
			cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier2] autorelease];
		}
	}
	
	// 20110622 tongtx start
	// AR5 の対応
    /*
	if ((indexPath.section == 0 && indexPath.row == 0) || (indexPath.section == [titles count] - 1)) {
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	} else {
		cell.selectionStyle = UITableViewCellSelectionStyleNone;
	}
	*/
    // 20110622 tongtx end
	[self configUITableViewCell:cell cellForRowAtIndexPath:indexPath];
    return cell;
}

- (void)configUITableViewCell:(UITableViewCell *)cell cellForRowAtIndexPath:(NSIndexPath *)indexPath{

    // tongtx 20110706 start
	// AR NO.17903 の対応
	id content = nil;
	if ([contents count] > indexPath.section && [[contents objectAtIndex:indexPath.section] count] > indexPath.row) {
		content = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
	}
	// tongtx 20110706 end
	
	if (indexPath.section != [titles count] - 1)
	{
		// zhaijie 2012.03.30 start
		// 『セキュリティ』の情報の対応
		if (fileInfo.fileProtected == YES && indexPath.section == 3)
		{
			CGFloat offsetX			= nil;
			UILabel *labelTitle_	= nil;
			UILabel *labelValue_	= nil;
			CGRect  labelFrame		= CGRectZero;
			
			if (Utility::UIDeviceIsiPad() == NO)
			{
				if (UIInterfaceOrientationIsPortrait(orientation_))
				{
					labelFrame = CGRectMake(MP_PERM_LABLEVALUE_HORIZONTAL_X_IPHONE, 8, 70, 30);
				}
				else
				{
					labelFrame = CGRectMake(MP_PERM_LABLEVALUE_VARTICAL_X_IPHONE, 8, 70, 30);
				}
			}
			else
			{
				if (UIInterfaceOrientationIsLandscape(orientation_))
				{
					labelFrame = CGRectMake(MP_PERM_LABLEVALUE_VARTICAL_X_IPAD, 8, 70, 30);
				}
				else
				{
					labelFrame = CGRectMake(MP_PERM_LABLEVALUE_HORIZONTAL_X_IPAD, 8, 70, 30);
				}
			}
			
			UILabel *label_ = (UILabel*)[cell viewWithTag:TAG_CELL_TEXT_LABEL_SEC];
			if (label_ != nil)
			{
				label_.text = [[titles objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
				label_ = (UILabel*)[cell viewWithTag:TAG_CELL_VALUE_LABEL_SEC];
				label_.frame = labelFrame;
			}
			else
			{
				offsetX = Utility::UIDeviceIsiPad() ? MP_PERM_LABLETITLE_LEFT_OFFSETX_IPAD:MP_PERM_LABLETITLE_LEFT_OFFSETX_IPHONE;
				labelTitle_ = [[UILabel alloc] initWithFrame:CGRectMake(offsetX, 8, 120, 30)];
				labelTitle_.tag = TAG_CELL_TEXT_LABEL_SEC;
				labelTitle_.backgroundColor = [UIColor clearColor];
				labelTitle_.text = [[titles objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
				labelTitle_.font = [UIFont boldSystemFontOfSize:FILE_TITLE_FONT_SIZE];
				labelTitle_.textColor = cell.textLabel.textColor;
				labelTitle_.textAlignment = UITextAlignmentLeft;
				[cell addSubview:labelTitle_];
				[labelTitle_ release];
				
				labelValue_ = [[UILabel alloc] initWithFrame:labelFrame];
				labelValue_.tag = TAG_CELL_VALUE_LABEL_SEC;
				labelValue_.textAlignment = UITextAlignmentLeft;
				labelValue_.text = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
				labelValue_.font = [UIFont boldSystemFontOfSize:FILE_TITLE_FONT_SIZE];
				labelValue_.backgroundColor = [UIColor clearColor];
				[cell addSubview:labelValue_];
				[labelValue_ release];
			}
			
			cell.selectionStyle = UITableViewCellSelectionStyleNone;
			cell.accessoryType =  UITableViewCellAccessoryNone;
			cell.detailTextLabel.textColor = [UIColor blackColor];
			
			return;
		}
		// zhaijie 2012.03.30 end
		
		
		cell.textLabel.text = @" ";
		
		if ([cell viewWithTag:TAG_CELL_TEXT_LABEL]) {
			((UILabel *)[cell viewWithTag:TAG_CELL_TEXT_LABEL]).text = [[titles objectAtIndex:indexPath.section] 
																		objectAtIndex:indexPath.row];
		} else {
			CGFloat offsetX = Utility::UIDeviceIsiPad() ? FILE_TITLE_FONT_OFFSETX_IPAD:FILE_TITLE_FONT_OFFSETX_IPHONE;
			UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(offsetX, 8, 75, 30)];
			
			label.tag = TAG_CELL_TEXT_LABEL;
			label.backgroundColor = [UIColor clearColor];
			label.text = [[titles objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
			// lixin 2011/10/10 start 
			// NS-AR2001 の対応
			//label.font = [UIFont fontWithName:@"Helvetica-Bold" size:FILE_TITLE_FONT_SIZE];
			label.font = [UIFont boldSystemFontOfSize:FILE_TITLE_FONT_SIZE];
			// lixin 2011/10/10 end
			
			label.textAlignment = UITextAlignmentRight;
			
			label.textColor = cell.textLabel.textColor;
			[cell addSubview:label];
			[label release];
		}
		
		// 20110623 tongtx start
		// AR5 の対応
		/*
		 if (indexPath.section == 0) {
		 if (indexPath.row == 1) {
		 cell.detailTextLabel.text = Utility::formatFileUpdateDate([[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row],DATE_FILE_FORMAT);
		 } else if (indexPath.row == 2) {
		 cell.detailTextLabel.text = Utility::formatFileSize([[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row]);
		 } else {
		 cell.detailTextLabel.text = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
		 }
		 } else {
		 cell.detailTextLabel.text = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
		 }
		 */
		if (indexPath.section == 0) {
            
            // liuqw 20110623 start
            // AR NO.17868 の対応
            if (indexPath.row == 0) {
                // 2011/06/30 M.Chikyu start
                /*
				 cell.detailTextLabel.textColor = [UIColor blueColor]; 
				 */
                cell.detailTextLabel.textColor = cell.textLabel.textColor;
                // 2011/06/30 M.Chikyu end
            } else {
                cell.detailTextLabel.textColor = [UIColor blackColor];
			}
            // liuqw 20110623 end
            
			if (indexPath.row == 1) {
				cell.selectionStyle = UITableViewCellSelectionStyleNone;
				cell.accessoryType =  UITableViewCellAccessoryNone;
                
                // tongtx 20110706 start
				// AR NO.17903 の対応
                //cell.detailTextLabel.text = Utility::formatFileUpdateDate([[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row],DATE_FILE_FORMAT);
				cell.detailTextLabel.text = Utility::formatFileUpdateDate((NSDate *)content,DATE_FILE_FORMAT);
				// tongtx 20110706 end
                
			} else if (indexPath.row == 2) {
				cell.selectionStyle = UITableViewCellSelectionStyleNone;
				cell.accessoryType =  UITableViewCellAccessoryNone;
                
                // tongtx 20110706 start
				// AR NO.17903 の対応
                //cell.detailTextLabel.text = Utility::formatFileSize([[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row]);
				cell.detailTextLabel.text = Utility::formatFileSize((NSNumber *)content);
				// tongtx 20110706 end
                
			} else {
				cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
				cell.selectionStyle = UITableViewCellSelectionStyleBlue;
				cell.detailTextLabel.text = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
                
                // tongtx 20110706 start
				// AR NO.17903 の対応
                //cell.detailTextLabel.text = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
                cell.detailTextLabel.text = (NSString *)content;
				// tongtx 20110706 end
			}
		} else {
			cell.selectionStyle = UITableViewCellSelectionStyleNone;
			cell.accessoryType =  UITableViewCellAccessoryNone;
            
            // tongtx 20110706 start
			// AR NO.17903 の対応
			//cell.detailTextLabel.text = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
			cell.detailTextLabel.text = (NSString *)content;
			// tongtx 20110706 end
            
			// liuqw 20110623 start
            // AR NO.17868 の対応
			cell.detailTextLabel.textColor = [UIColor blackColor];
			// liuqw 20110623 end
		}
		// 20110623 tongtx end
		cell.detailTextLabel.numberOfLines = DETAIL_LABEL_MAX_ROWS;
		
		// lixin 2011/10/10 start 
		// NS-AR2001 の対応
		cell.detailTextLabel.font = [UIFont boldSystemFontOfSize:FILE_TITLE_FONT_SIZE];
		// lixin 2011/10/10 end
	} else {
		// 20110623 tongtx start
		// AR5 の対応
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
		cell.selectionStyle = UITableViewCellSelectionStyleBlue;
		// 20110623 tongtx end
        
		// tongtx 20110706 start
		// AR NO.17903 の対応
        //cell.textLabel.text = [[titles objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
		if ([titles count] > indexPath.section && [[titles objectAtIndex:indexPath.section] count] > indexPath.row) {
			cell.textLabel.text = [[titles objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
		}
		// tongtx 20110706 end
	}
}

// forbid starting with "."
#pragma mark -
#pragma mark UITextFieldDelegate
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string{
    if (range.location == 0 && [string isEqualToString:@"."]) {
		return NO;
	} else {
		return YES;
	}
}

#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
	if (indexPath.section == 0 && indexPath.row == 0) {
		if (fileUpdateAlert == nil) {
			// tongtx 20110127 start
			// AR17877
			/*
			UIAlertView *updateFileNameAlert = [[UIAlertView alloc] initWithTitle:LOCALSTRING(@"FILE_NAME_MODIFY") 
																		  message:@"     "
																		 delegate:self 
																cancelButtonTitle:LOCALSTRING(@"BUTTON_TITLE_CANCEL") 
																otherButtonTitles:LOCALSTRING(@"BUTTON_TITLE_OK"),nil];
			*/
			
			UIAlertView *updateFileNameAlert = [[UIAlertView alloc] initWithTitle:LOCALSTRING(@"FILE_NAME_MODIFY") 
																	  message:@"     "
																	 delegate:self 
															cancelButtonTitle:LOCALSTRING(@"BUTTON_TITLE_OK") 
															otherButtonTitles:LOCALSTRING(@"BUTTON_TITLE_CANCEL"),(char*)0];
			// tongtx 20110127 end
			UITextField *textField = [[UITextField alloc] init];
			textField.delegate = self;
			textField.borderStyle = UITextBorderStyleRoundedRect;
			[updateFileNameAlert addSubview:textField];
			textField.tag = TAG_UPDATE_NAME;
			fileUpdateAlert = [updateFileNameAlert retain];
			[textField release];
			[updateFileNameAlert release];
		}
        
		[fileUpdateAlert show];
		UITextField *nameTextField = (UITextField *)[fileUpdateAlert viewWithTag:TAG_UPDATE_NAME];
		nameTextField.text = [fileInfo.fileName stringByDeletingPathExtension];
		[nameTextField becomeFirstResponder];
	}
    
	if (indexPath.section == [titles count] - 1) {
		if (indexPath.row == 0) {
			[self sendEmailWithAttachment];
		} else {
			[self openFileWithOthers:[tableView cellForRowAtIndexPath:indexPath]];
		}
	}
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
	if ( (indexPath.section == [titles count] -1) || 
		(indexPath.section == 0 && (indexPath.row == 1 || indexPath.row == 2))) {
		return CELL_DEFAULT_HEIGHT;
	} else {
		NSString *message = [[contents objectAtIndex:indexPath.section] objectAtIndex:indexPath.row];
		// lixin 2011/10/10 start 
		// NS-AR2001 の対応
		/*
		CGRect frame = CGRectMake(0, 0, maxWidth, 1000); 
		CGSize calcSize = [message sizeWithFont:[UIFont systemFontOfSize:DETAIL_LABEL_DEFAULT_FONT_SIZE] 
							  constrainedToSize:frame.size 
								  lineBreakMode:UILineBreakModeTailTruncation];
		 */
		CGSize calcSize = [message sizeWithFont:[UIFont boldSystemFontOfSize:FILE_TITLE_FONT_SIZE]
							  constrainedToSize:CGSizeMake(maxWidth, DETAIL_LABEL_MAX_HEIGHT) 
								  lineBreakMode:UILineBreakModeWordWrap];
		// lixin 2011/10/10 end
		float height = calcSize.height;
		if (height <= DETAIL_LABEL_DEFAULT_HEIGHT) {
			height = CELL_DEFAULT_HEIGHT;
		} else {
			height = CELL_DEFAULT_HEIGHT - DETAIL_LABEL_DEFAULT_HEIGHT + height;
		}
		return height;
	}
}

- (void) resetTextFieldFrame:(UITextField *)textField
{
    UILabel* labelTitle_ =  ((UILabel*)[[fileUpdateAlert subviews]objectAtIndex:1]);
    if (labelTitle_ != nil) {
        float originX = 45;
        float originY = labelTitle_.frame.origin.y + labelTitle_.frame.size.height;   
        float width = 200;
        float height = 30;
        float offset = 3;
        
        if (Utility::UIDeviceIsiPad() == NO) {
            if ([self UIDeviceIsPortrait] == YES) {
                height = 30;
                offset = 4;
            } else {
                height = 27;
                offset = 2;
            }
        } else {
            if ([self UIDeviceIsPortrait] == YES) {
                height = 30;
                offset = 4;
            } else {
                height = 27;
                offset = 4;
            }
        }
        
        textField.frame = CGRectMake(originX, originY + offset, width, height);
    }
}

- (void) resetTextFieldFrameForRotation:(UITextField *)textField 
                        withOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    if (Utility::UIDeviceIsiPad() == NO) {
        if (toInterfaceOrientation != self.interfaceOrientation) {
            float originX, originY, width, height;
            if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation)) {
                originX = textField.frame.origin.x;
                originY = textField.frame.origin.y - 8;    
                width = 200;
                height = 27;
            } else {
                originX = textField.frame.origin.x;
                originY = textField.frame.origin.y + 8;    
                width = 200;
                height = 30;
            }
            textField.frame = CGRectMake(originX, originY, width, height);
        }
    } else {
        float originX, originY, width, height;
        if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation)) {
            originX = textField.frame.origin.x;
            originY = textField.frame.origin.y - 8;
            width = 200;
            height = 27;
        } else {
            originX = textField.frame.origin.x;
            originY = textField.frame.origin.y + 8;
            width = 200;
            height = 30;
        }
        textField.frame = CGRectMake(originX, originY, width, height);
    }
}

- (void) willPresentAlertView:(UIAlertView *)alertView
{
	UITextField *nameTextField = (UITextField *)[fileUpdateAlert viewWithTag:TAG_UPDATE_NAME];
    [self resetTextFieldFrame:nameTextField];    
}

- (BOOL)UIDeviceIsPortrait
{
	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) || 
		(self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)){
		return YES;
	} else{
		return NO;
	}
}

#pragma mark -
#pragma mark UIActionSheet delegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
	if ([alertView isEqual:fileUpdateAlert]) {
		if (buttonIndex == alertView.cancelButtonIndex) {
            NSString *newFileName = nil;
            
            // liuqw 2011/07/01 start
            // AR NO.17883 の対応
            
            UITextField* field = ((UITextField *)[fileUpdateAlert viewWithTag:TAG_UPDATE_NAME]);
            if (field == nil) 
                return;
            
            NSMutableString* fieldString = [[[NSMutableString alloc]init]autorelease];
            if ([[fileInfo.fileName pathExtension] length] > 0) {
				[fieldString appendFormat:@"%@.%@", field.text, [fileInfo.fileName pathExtension]];
			} else {
				[fieldString appendFormat:@"%@", field.text];
			}
            
            newFileName = [NSString stringWithString:fieldString];
            
            /*
			if ([[fileInfo.fileName pathExtension] length] > 0) {
				newFileName = [((UITextField *)[fileUpdateAlert viewWithTag:TAG_UPDATE_NAME]).text stringByAppendingPathExtension:[fileInfo.fileName pathExtension]];
			} else {
				newFileName = ((UITextField *)[fileUpdateAlert viewWithTag:TAG_UPDATE_NAME]).text;
			}
            */ 
            
            // liuqw 2011/07/01 end

			// 20110623 tongtx start
			// AR17853の対応
			/*
			FileUpdateErrorCode errorCode = [documentSettingsMgr updateFileNameWithSrcName:fileInfo.fileName 
																			  withDestName:newFileName];
			if (errorCode == FILEUPDATE_ERRORCODE_SUCCESS) {
				fileInfo.fileName = newFileName;
			}
			[self didUpdateFileNameFinish:errorCode];
			*/
			
			if (![newFileName isEqualToString:fileInfo.fileName]) {
				FileUpdateErrorCode errorCode = [documentSettingsMgr updateFileNameWithSrcName:fileInfo.fileName 
																				  withDestName:newFileName];
				if (errorCode == FILEUPDATE_ERRORCODE_SUCCESS) {
					fileInfo.fileName = newFileName;
				}
				[self didUpdateFileNameFinish:errorCode];
			}
			// 20110623 tongtx end
		}
	} else {
		if (![alertView.message isEqualToString:LOCALSTRING(@"FILE_UPDATE_SUCCESS")]) {
			UITextField *textField = (UITextField *)[fileUpdateAlert viewWithTag:TAG_UPDATE_NAME];
			[fileUpdateAlert show];
			textField.text = [fileInfo.fileName stringByDeletingPathExtension];
			[textField becomeFirstResponder];
		}
	}
}

- (void)didUpdateFileNameFinish:(FileUpdateErrorCode)errorCode{
	NSString *message = nil;
	switch (errorCode) {
		case FILEUPDATE_ERRORCODE_SUCCESS:
        // liuqw 2011/07/11 start
        // AR NO.17915 の対応
            
            /*
			message = LOCALSTRING(@"FILE_UPDATE_SUCCESS");
			if ([contents count] > 0 && [[contents objectAtIndex:0] count] > 0) {
				[[contents objectAtIndex:0] replaceObjectAtIndex:0 withObject:fileInfo.fileName];
				[self.tableView reloadData];
			}
			break;
            */
            
            if ([contents count] > 0 && [[contents objectAtIndex:0] count] > 0) {
				[[contents objectAtIndex:0] replaceObjectAtIndex:0 withObject:fileInfo.fileName];
				[self.tableView reloadData];
			}
            return;
          
        /*    
		case FILEUPDATE_ERRORCODE_NOT_EXISTED:
			message = LOCALSTRING(@"FILE_UPDATE_NO_EXISTED");
			break;
		case FILEUPDATE_ERRORCODE_FILENAME_EMPTY:
			message = LOCALSTRING(@"FILE_UPDATE_EMPTY");
			break;
        */
            
        case FILEUPDATE_ERRORCODE_NOT_EXISTED:
		case FILEUPDATE_ERRORCODE_FILENAME_EMPTY:
			message = LOCALSTRING(@"FILE_UPDATE_FAILURE");
			break;    
            
        // liuqw 2011/07/11 end
            
		case FILEUPDATE_ERRORCODE_OVERLENGTH:
			message = LOCALSTRING(@"FILE_UPDATE_OVERLENGTH");
			break;
		case FILEUPDATE_ERRORCODE_FILENAME_EXISTED:
			message = LOCALSTRING(@"FILE_UPDATE_EXISTED");
			break;
		case FILEUPDATE_ERRORCODE_INVALID_CHAR:
            // liuqw 20110629 start
            // AR NO.17883 の対応
            message = LOCALSTRING(@"FILE_UPDATE_ILLEGAL");
			break;
            // liuqw 20110629 end
        case FILEUPDATE_ERRORCODE_OTHERS:
			message = LOCALSTRING(@"FILE_UPDATE_FAILURE");
			break;
		default:
			break;
	}
    
	UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil  
														message:message 
													   delegate:self 
											  cancelButtonTitle:LOCALSTRING(@"BUTTON_TITLE_OK") 
											  otherButtonTitles:nil];
	[alertView show];
	[alertView release];
}

#pragma mark -
#pragma mark sendEmail with attach
- (void)sendEmailWithAttachment{
	if (([fileInfo.fileSize floatValue] / pow(1024, 2)) > EMAIL_MAX_FILE_SIZE) {
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil 
															message:LOCALSTRING(@"MSG_WARING_FILESIZE_OUT") 
														   delegate:nil
												  cancelButtonTitle:LOCALSTRING(@"BUTTON_TITLE_OK") 
												  otherButtonTitles:nil];
		[alertView show];
		[alertView release];
	}
	else {
		Class mailClass = NSClassFromString(@"MFMailComposeViewController");
		if (mailClass != nil && [MFMailComposeViewController canSendMail]) {
			NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
			NSString *attachPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:fileInfo.fileName];
			MFMailComposeViewController *picker = [[MFMailComposeViewController alloc] init];
			picker.mailComposeDelegate = self;
			// tongtx 20110627 start
			// AR17880
			//NSString *mimeType = Utility::getAttachmentMIMEType([fileInfo.fileName pathExtension]);
			NSString *mimeType = Utility::getAttachmentMIMEType(attachPath);
			// tongtx 20110627 end
		
			NSData *attachmentData = [NSData dataWithContentsOfFile:attachPath];
			if (mimeType != nil && [attachmentData length] > 0){
				[picker addAttachmentData:attachmentData 
								 mimeType:mimeType 
								 fileName:fileInfo.fileName];
				[self presentModalViewController:picker animated:YES];
				[picker release];
			}
		}
	}
}

#pragma mark -
#pragma mark  MFMailComposeViewControllerDelegate
- (void)mailComposeController:(MFMailComposeViewController *)controller 
		  didFinishWithResult:(MFMailComposeResult)result 
						error:(NSError *)error{
	[self becomeFirstResponder];
	[self dismissModalViewControllerAnimated:YES];
}

#pragma mark -
#pragma mark openMode
- (void)openFileWithOthers:(UIView *)inView{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *attachPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:fileInfo.fileName];
	NSURL *fileURL = [NSURL fileURLWithPath:attachPath];
	UIDocumentInteractionController *docInteractionController = 
	[UIDocumentInteractionController interactionControllerWithURL:fileURL];
	interactionController = [docInteractionController retain];
	if(Utility::UIDeviceIsiPad()) {
		[interactionController presentOpenInMenuFromRect:CGRectMake(-100, 0, self.view.frame.size.width, self.view.frame.size.height) 
												  inView:inView animated:YES];
	} else {
		[interactionController presentOpenInMenuFromRect:self.view.frame 
												  inView:self.view animated:YES];
	}
}

#pragma mark -
#pragma mark dismiss interactionview
// tongtx 20110711 start
// AR17920 の対応 (20110712 M.Chikyu)
- (void)removeModalView{
	if (interactionController != nil) {
		[interactionController dismissMenuAnimated:NO];
	}
}
// tongtx 20110711 end

#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
}

- (void)dealloc {
	[interactionController release];
	[titles release];
	[fileInfo release];
	[contents release];
	[fileUpdateAlert release];
	[documentSettingsMgr release];
    [super dealloc];
}


@end

