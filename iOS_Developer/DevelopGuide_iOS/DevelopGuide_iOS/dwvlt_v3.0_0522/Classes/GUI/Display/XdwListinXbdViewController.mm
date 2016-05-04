//
//  XdwListinXbdViewController.m
//  DWViewer
//
//  Created by icd-lixin on 6/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "XdwListinXbdViewController.h"
#import "DWViewerGUIConst.h"
#import "Utility.h"

@implementation XdwListinXbdViewController
@synthesize delegate;
@synthesize nameLabelRect;
@synthesize pageLabelRect;
// lixin 20110626 DW_iPhoneEnhance_12 start
// AR.17872 の対応 
@synthesize selectDocIndex;
// lixin 20110626 DW_iPhoneEnhance_12 end
#pragma mark -
#pragma mark Initialization

- (id) initWithPageViewManager:(PageViewManager*)mgr
{
	if ((self = [super initWithStyle:UITableViewStylePlain]))
	{
		xdwDocCount = 0;
        fileInfo = nil;

        if ((DocumentType)pageViewMgr.documentType == DOC_TYPE_XDW) {
            pageViewMgr = mgr;
			
            fileInfo = [pageViewMgr getBinderFileInfo];
            xdwDocCount = fileInfo->GetBinderCount();
        }
        
        // lixin 20110626 DW_iPhoneEnhance_12 start
        // AR.17872 の対応 
        selectDocIndex = 0;
        // lixin 20110626 DW_iPhoneEnhance_12 end
    }
    return self;
}

#pragma mark -
#pragma mark View lifecycle


- (void)viewDidLoad {
    [super viewDidLoad];
   [self.tableView setSeparatorColor:[UIColor clearColor] ];	
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
	// 2012.02.01(Ver2.1 New) M.Chikyu
	/*
	[[UIApplication sharedApplication] setStatusBarHidden:NO 
											withAnimation:UIStatusBarAnimationNone];
	 */
	// 2012.02.01(Ver2.1 New) M.Chikyu
	[self.navigationController setNavigationBarHidden:NO animated:NO];
	[self.navigationController setToolbarHidden:NO animated:NO];
    [self.tableView reloadData];
}

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
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return xdwDocCount;
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
	
	if ( [cell.contentView subviews] ) {
		for (UIView *subview in [cell.contentView subviews] ) {
			[subview removeFromSuperview];
		}
	}
	
    if (fileInfo != nil) {
        // set annotation page number.
        UILabel *labelDocName = [[UILabel alloc] initWithFrame:nameLabelRect];
        [labelDocName setBackgroundColor:[UIColor clearColor]];
        labelDocName.textColor = [UIColor whiteColor];
        
        // lixin 20110708 DW_iPhoneEnhance_12 start
		// AR.17910 の対応
		
		//labelDocName.font = [UIFont fontWithName:@"Times New Roman" size:_ANNOTATION_LIST_TEXT_FONTSIZE_];
		labelDocName.font = [UIFont fontWithName:@"Arial" size:_ANNOTATION_LIST_TEXT_FONTSIZE_];
		
		// lixin 20110708 DW_iPhoneEnhance_12 end
        
        labelDocName.textAlignment = UITextAlignmentLeft;
        labelDocName.numberOfLines = 2;
        
        labelDocName.text = [NSString stringWithCString:fileInfo->GetNameOfBinderDoc([indexPath row])
                                            encoding:NSUTF8StringEncoding];
        
        
        
        // set name label size
        
        // lixin 20110708 DW_iPhoneEnhance_12 start
		// AR.17910 の対応
		
		//CGSize size = CGSizeMake(320, 2000);
		CGSize size = CGSizeMake(10000, 2000);
		
		// lixin 20110708 DW_iPhoneEnhance_12 end
        
        CGSize labelSize = [labelDocName.text sizeWithFont:labelDocName.font 
                                         constrainedToSize:size
                                             lineBreakMode:UILineBreakModeClip];
        CGSize labelNameSize = labelDocName.frame.size;
        
        // lixin 20110708 DW_iPhoneEnhance_12 start
		// AR.17910 の対応
		
		/*
        if ( labelSize.width > labelNameSize.width )
        {
            labelNameSize.height = _ANNOTATION_LIST_TEXT_FONTSIZE_*2.4;
        }
        else
        {
            labelNameSize.height = _ANNOTATION_LIST_TEXT_FONTSIZE_*1.2;
        }
        */
		
		if ( labelSize.width > labelNameSize.width )
        {
			labelNameSize.height = labelDocName.font.lineHeight * 2;
        }
        else
        {
            labelNameSize.height = labelDocName.font.lineHeight;
        }
        
		// lixin 20110708 DW_iPhoneEnhance_12 end
        
        [labelDocName setFrame:CGRectMake(nameLabelRect.origin.x,
                                          5,
                                          labelNameSize.width, 
                                          labelNameSize.height)];
        
        [cell.contentView addSubview:labelDocName];
        [labelDocName release];
        
        // set page count label.
        UILabel *labelPageCount = [[UILabel alloc] initWithFrame:pageLabelRect];
        [labelPageCount setBackgroundColor:[UIColor clearColor]];
        labelPageCount.textColor = [UIColor whiteColor];
        labelPageCount.font = [UIFont fontWithName:@"Arial" size:_ANNOTATION_LIST_TEXT_FONTSIZE_];
        labelPageCount.text = [NSString stringWithFormat:@"%d", fileInfo->GetPageCntOfBinderDoc(indexPath.row)];
        labelPageCount.textAlignment = UITextAlignmentCenter;
        [cell.contentView addSubview:labelPageCount];
        [labelPageCount release];
    }

	// lixin 20110626 DW_iPhoneEnhance_12 start
	// AR.17872 の対応 
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
	if (indexPath.row == selectDocIndex)
	{
		[cell.contentView setBackgroundColor:[UIColor blueColor]];
	}
	else
	{
		[cell.contentView setBackgroundColor:[UIColor clearColor]];
	}
	// lixin 20110626 DW_iPhoneEnhance_12 end
	
    return cell;
}

#pragma mark -
#pragma mark Table View Delegate methods
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return _ANNOTATION_LIST_LINE_HEIGHT_;
}


#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSInteger index = [indexPath row];
	
	int pageNumberInBinder = 0;
	if (fileInfo != nil)
    {
        if (fileInfo->GetPageCntOfBinderDoc(index) != 0)
        {
            for (int i = 0; i < index; i++)
            {
                pageNumberInBinder += fileInfo->GetPageCntOfBinderDoc(i);
            }
			[delegate didSelectXdwDocInTable:pageNumberInBinder];
        }
    }
}

// lixin 20110830 DW_iPhoneViewer_20の追加 start
#pragma mark -
#pragma mark reload data for edit annotation
- (void) reloadDataWithPageViewManager:(PageViewManager*)mgr
{
	xdwDocCount = 0;
	fileInfo = nil;
	
	if ((DocumentType)pageViewMgr.documentType == DOC_TYPE_XDW) {
		pageViewMgr = mgr;
		
		fileInfo = [pageViewMgr getBinderFileInfo];
		xdwDocCount = fileInfo->GetBinderCount();
	}

	selectDocIndex = 0;
}
// lixin 20110830 end

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

