//
//  AnnotationListView.m
//  DWViewer
//
//  Created by YAN on 10/19/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "AnnotationListViewController.h"
#import "DWViewerAppDelegate.h"
#import "DocumentViewController.h"
#import "PageViewManager.h"
#import "DWPageView.h"
#import "Utility.h"
#import "DWViewerGUIConst.h"
#import "PageInfo.h"
#import "DWScrollView.h"

#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

@implementation AnnotationListViewController;
@synthesize delegate;
@synthesize kindLabelRect;
@synthesize numberLabelRect;
@synthesize contentLabelRect;
@synthesize pageIndex;
// AR NO.17557 の対応 start
@synthesize leftTopX;
@synthesize leftTopY;
@synthesize rightButtomX;
@synthesize rightButtomY;
// AR NO.17557 の対応 end

- (id) initWithPageViewManager:(PageViewManager*)mgr
{
	if ((self = [super initWithStyle:UITableViewStylePlain]))
	{
		// AR NO.17557 の対応 start
		leftTopX = 0.0;
		leftTopY = 0.0;
		rightButtomX = 0.0;
		rightButtomY = 0.0;
		// AR NO.17557 の対応 end
		
		annotationCount = 0;
		pageViewMgr = mgr;
		dictionary = [[NSMutableDictionary alloc] init];
		[self loadLinkAnnotationList];
    }
    return self;
}

- (void) loadLinkAnnotationList
{	
	if (pageViewMgr.documentType == DOC_TYPE_XDW) {
		
		LinkAnnotInfoList *list = [pageViewMgr getLinkAnnotationInfoList];
        if (list == NULL) {
            return;
        }
        
		LinkAnnotInfo* annotInfo = nil;
		int annotationsCount = list->Size();		
		for (int i = 0; i < annotationsCount; i++) {
			annotInfo = list->GetLinkAnnotInfo(i);
			if (annotInfo->IsLinkAnnotation()) {
				continue;
			} else {
				annotationCount++;
				annotationIndex.push_back(i);
			}	
		}
		//delete annotInfo;
		
		NSString *colorName = nil;
		LinkAnnotInfo* lingAnnotInfo = NULL;
		//const char *linkTitle = nil;
		const wchar_t* annotationText = nil;
		
		NSString *content = nil;
		
		// Memory Leak の対応 start
		NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
		// Memory Leak の対応 end

		for (int i = 0; i < annotationIndex.size(); i++) {
			lingAnnotInfo = list->GetLinkAnnotInfo(annotationIndex[i]);
			
			annotationText = lingAnnotInfo->GetAnnotText();
			// Memory Leak の対応 start
			//content = [self wcharToNSString:annotationText];
			content = [[self wcharToNSString:annotationText] retain];
			// Memory Leak の対応 end

			long annotColor = lingAnnotInfo->GetAnnotationColor();
			colorName= [NSString stringWithFormat:@"%d",annotColor];
			
			long index = lingAnnotInfo->GetXdwPageNum();
			NSString *pageNum = [NSString stringWithFormat:@"%d", (index + 1)];
			
			NSMutableArray *annotationInfo = [[NSMutableArray alloc] init];
			// add color name.
			[annotationInfo insertObject:colorName atIndex:0];
			// add page number.
			[annotationInfo insertObject:pageNum atIndex:1];
			// add annotation content.
			[annotationInfo insertObject:content atIndex:2];
			
			NSNumber *key = [NSNumber numberWithInt:i];
			[dictionary setObject:annotationInfo forKey:key];
			
			// Memory Leak の対応 start
			[annotationInfo release];
			[content release];
			// Memory Leak の対応 end
		}
		
		// Memory Leak の対応 start
		[pool release];
		// Memory Leak の対応 end
	}	 
}

// lixin 20110813 start
// ページ編集機能の追加 
- (void) reloadLinkAnnotationList
{
	annotationCount = 0;
    annotationIndex.clear();
	[dictionary removeAllObjects];
	[self loadLinkAnnotationList];
}
// lixin 20110813 end

- (NSMutableArray*) getAnnotationInfoWithIndex:(int)index
{
	NSNumber *key = [NSNumber numberWithInt:index];
	NSMutableArray *annotationInfo = [dictionary objectForKey:key];
	return annotationInfo;
}

-(NSString*) wcharToNSString:(const wchar_t *)src
{
	// Memory Leak の対応 start
	//NSString *dest = [[[NSString alloc] init] autorelease];
	NSString *dest = nil;
	// Memory Leak の対応 start
	if (src != NULL) {
		long length = wcslen(src);
		unichar *uchar  = new unichar[length];
		for (int i = 0; i < length; i++) {
			uchar[i] = src[i];
		}
		dest = [NSString stringWithCharacters:uchar length:wcslen(src)];
		delete []uchar;
	} else {
		// Memory Leak の対応 start
		dest = [[[NSString alloc] init] autorelease];
		// Memory Leak の対応 end
	}

	return dest;
}

-(void)viewDidLoad
{
	[super viewDidLoad];
	[self.tableView setSeparatorColor:[UIColor clearColor] ];
}

- (void)viewWillAppear:(BOOL)animated
{
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

#pragma mark -
#pragma mark Table View Delegate methods
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
	return _ANNOTATION_LIST_LINE_HEIGHT_;
}


#pragma mark -
#pragma mark Table view data source methods
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return annotationCount;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	static NSString *annotationListIdentifier = @"annotationListIdentifier";
	
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:annotationListIdentifier];
	if(cell == nil)
	{
		/*
		cell = [[[UITableViewCell alloc] initWithFrame:CGRectZero 
									   reuseIdentifier:annotationListIdentifier] autorelease];
		 */
		cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
									   reuseIdentifier:annotationListIdentifier] autorelease];
#ifdef __IPHONE_3_0
		cell.accessoryType =  UITableViewCellAccessoryDisclosureIndicator;
#endif
	} else {
		if ( [cell.contentView subviews] ) {
			for (UIView *subview in [cell.contentView subviews] ) {
				[subview removeFromSuperview];
			}
		}
	}
	
	int index = [indexPath row];
	[self initTableViewCell:cell withCellIndex:index];
	
	return cell;
}

- (void) initTableViewCell:(UITableViewCell*)cell withCellIndex:(int)index
{
	//get the dictionary of annotation list,by specify the number of cell
	
	NSNumber *key = [NSNumber numberWithInt:index];
	NSMutableArray *annotationInfo = [dictionary objectForKey:key];
	
	// set annotation type .
	UILabel *kindLabel = [[UILabel alloc] initWithFrame:kindLabelRect];
	NSString *colorName = [annotationInfo objectAtIndex:0];
	//20101129
	int annotColor = [colorName intValue];
	UIColor *kindColor = [UIColor colorWithRed:(annotColor & 0xFF) / 255.0f 
										 green:((annotColor & 0xFF00) >> 8)  / 255.0f 
										  blue:((annotColor & 0xFF0000) >> 16)  / 255.0f  
										 alpha:1.0f];
	
	[kindLabel setBackgroundColor:kindColor];
	[cell.contentView addSubview:kindLabel];
	
	// set annotation page number.
	UILabel *numberLabel = [[UILabel alloc] initWithFrame:numberLabelRect];
	numberLabel.textAlignment = UITextAlignmentCenter;
	[numberLabel setBackgroundColor:[UIColor clearColor]];
	numberLabel.textColor = [UIColor whiteColor];
	numberLabel.font = [UIFont fontWithName:@"Times New Roman" size:_ANNOTATION_LIST_TEXT_FONTSIZE_];
	numberLabel.text = [annotationInfo objectAtIndex:1];
	[cell.contentView addSubview:numberLabel];
	[numberLabel release];
	
	// set annotatile content.
	UILabel *contentLabel = [[UILabel alloc] initWithFrame:contentLabelRect];
	[contentLabel setBackgroundColor:[UIColor clearColor]];
	contentLabel.textColor = [UIColor whiteColor];
	contentLabel.font = [UIFont fontWithName:@"Arial" size:_ANNOTATION_LIST_TEXT_FONTSIZE_];
	contentLabel.numberOfLines = 2;
	contentLabel.text = [annotationInfo objectAtIndex:2];
	
	// set content label size
    
    // lixin 20110708 DW_iPhoneEnhance_12 start
	// AR.17910 の対応
	
	//CGSize size = CGSizeMake(320, 2000);
	CGSize size = CGSizeMake(10000, 2000);
	
	// lixin 20110708 DW_iPhoneEnhance_12 end
    
	CGSize labelSize = [contentLabel.text sizeWithFont:contentLabel.font 
									 constrainedToSize:size
										 lineBreakMode:UILineBreakModeClip];
	CGSize annotationSize = contentLabel.frame.size;
	// lixin 20110708 DW_iPhoneEnhance_12 start
	// AR.17910 の対応
	
	/*
    if ( labelSize.width > annotationSize.width )
    {
        annotationSize.height = _ANNOTATION_LIST_TEXT_FONTSIZE_*2.4;
    }
    else 
    {
        annotationSize.height = _ANNOTATION_LIST_TEXT_FONTSIZE_*1.2;
    }
    */
	
	if ( labelSize.width > annotationSize.width )
	{
		annotationSize.height = contentLabel.font.lineHeight * 2;
	}
	else
	{
		annotationSize.height = contentLabel.font.lineHeight;
	}
	
	// lixin 20110708 DW_iPhoneEnhance_12 end

	[contentLabel setFrame:CGRectMake(80,5,annotationSize.width, 
									  annotationSize.height)];
	[cell.contentView addSubview:contentLabel];
	[contentLabel release];
	
	UIView* accessory = [[UIView alloc]init];
	cell.accessoryView = accessory;
	[accessory release];
	
	// 4.6 AR.17718 選択されている付箋の色が選択色（青色）に隠れてしまっている の対応 start 
	// change by lixin 20110607 DW_iPhoneEnhance_12
	cell.selectionStyle = UITableViewCellSelectionStyleNone;
	// 4.6 AR.17718 選択されている付箋の色が選択色（青色）に隠れてしまっている の対応 end
}
-(void)dealloc {
	annotationIndex.clear();
	//delete []linkAnnotInfos;
	[dictionary release];
    [super dealloc];
}

#pragma mark -
#pragma mark Table view delegate methods
// Jonah modified this for XCode compiler warning
#ifndef __IPHONE_3_0
-(UITableViewCellAccessoryType)tableView:(UITableView *)tableView accessoryTypeForRowWithIndexPath:(NSIndexPath *)indexPath {
	return UITableViewCellAccessoryDisclosureIndicator;
}
#endif

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSInteger selectrow = [indexPath row];
	NSMutableArray *annotationInfo = [self getAnnotationInfoWithIndex:selectrow];
	if (annotationInfo != nil) {
		pageIndex = [[annotationInfo objectAtIndex:1] intValue] - 1;

		XdwRectangle rect;
		LinkAnnotInfo *linkAnnotInfos = nil;
		LinkAnnotInfoList *list = [pageViewMgr getLinkAnnotationInfoList];
		
		int annotIndex = annotationIndex[selectrow];
		
		linkAnnotInfos = list->GetLinkAnnotInfo(annotIndex);
		
		rect = linkAnnotInfos->GetRectangle();

		if (linkAnnotInfos != nil) {
			pageIndex = [[annotationInfo objectAtIndex:1] intValue] - 1;
			
			XdwRectangle rect;
			LinkAnnotInfo *linkAnnotInfos = nil;
			LinkAnnotInfoList *list = [pageViewMgr getLinkAnnotationInfoList];
			int annotIndex = annotationIndex[selectrow];
			linkAnnotInfos = list->GetLinkAnnotInfo(annotIndex);
			
			// AR NO.17557 の対応 start
			if (linkAnnotInfos != NULL) {
				rect = linkAnnotInfos->GetRectangle();
				leftTopX = rect.LeftTopF.xF;
				leftTopY = rect.LeftTopF.yF;
				rightButtomX = rect.RightBottomF.xF;
				rightButtomY = rect.RightBottomF.yF;
			}
			// AR NO.17557 の対応 end
			
			// 4.6 AR.17718 選択されている付箋の色が選択色（青色）に隠れてしまっている の対応 start 
			// change by lixin 20110607 DW_iPhoneEnhance_12
			[tableView reloadData];
			UITableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath];
			cell.backgroundColor = [UIColor blueColor];
			// 4.6 AR.17718 選択されている付箋の色が選択色（青色）に隠れてしまっている の対応 end

			[delegate didSelectAnnotationInTable:self];
		}
	}
}

@end
