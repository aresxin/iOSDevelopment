//
//  ScaleSpecifyViewController.m
//  DWViewer
//
//  Created by liuqw on 11-6-9.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ScaleSpecifyViewController.h"
#import "Utility.h"

#define TAG_INPUT_SCALE_ALERT 101
#define TAG_INPUT_SCALE_FIELD 102
#define TAG_INPUT_SCALE_ERROR 103

@implementation ScaleSpecifyViewController
@synthesize delegate;
@synthesize specifyScaleMode;
@synthesize fixedScale;

@synthesize fieldInputScale;
@synthesize alertInputScale;
@synthesize labelScalePercent;

#pragma mark -
#pragma mark Initialization

- (id)initWithStyle:(UITableViewStyle)style withSpecifyMode:(int)mode withFixedScale:(int)scale {
    self = [super initWithStyle:style];
    if (self) {
        specifyScaleMode = mode;
        if (mode == 0) {
            fixedScale = 100;
        } else {
            fixedScale = scale;
        }
        
        alertInputScale = nil;
    }
    return self;
}



#pragma mark -
#pragma mark View lifecycle

// liuqw 20110628 start
// AR NO.17882 の対応

- (void)viewDidLoad {
    [super viewDidLoad];
	self.title = NSLocalizedString(@"TITLE_SPECIFY_SCALE",nil);
}

// liuqw 20110628 end

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

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    if ([alertInputScale isVisible]) {
        [self setInputScaleFieldViewPositionWithOrientation:toInterfaceOrientation];
	}    
}

#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) 
    {
		return 2;
    }
	else
    {
		return 1;
    }
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:CellIdentifier] autorelease];
        
        cell.selectionStyle = UITableViewCellSelectionStyleBlue;
    }
    
	if (indexPath.section == 0) 
	{
		switch (indexPath.row) {
			case 0:
				cell.textLabel.text = NSLocalizedString(@"TITLE_INPUT_SCALE", nil);
                
				if (specifyScaleMode == 0) {
					cell.accessoryType = UITableViewCellAccessoryCheckmark;
				}
                
				break;
			case 1:
				cell.textLabel.text = NSLocalizedString(@"TITLE_FIXED_SCALE", nil);
                
				if (specifyScaleMode == 1) {
					cell.accessoryType = UITableViewCellAccessoryCheckmark;
				}
                 
				break;
			default:
				break;
		}
	}
	else 
	{
        NSString* detail = [NSString stringWithFormat:@"%d", fixedScale];
		cell.textLabel.text = NSLocalizedString(@"TITLE_SELECT_FIXED_SCALE", nil);
		//cell.textLabel.font = [UIFont fontWithName:@"Arial" size:12.0];
		cell.detailTextLabel.text = detail;
		cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        
        // liuqw 20110623 start
        // AR NO.17860 の対応
        if (cell != nil) {
            if (specifyScaleMode == 1)
            {
                cell.textLabel.textColor = [UIColor blackColor];
                cell.detailTextLabel.textColor = [UIColor blackColor];
            }
            else
            {
                cell.textLabel.textColor = [UIColor grayColor];
                cell.detailTextLabel.textColor = [UIColor grayColor];
            }
        }
        // liuqw 20110623 end
        
	}
    return cell;
}

#pragma mark -
#pragma mark Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
	if (indexPath.section == 0) {
        cell.accessoryType = UITableViewCellAccessoryCheckmark;
		specifyScaleMode = indexPath.row;
        
        // liuqw 20110623 start
        // AR NO.17860 の対応
        NSIndexPath* index = [NSIndexPath indexPathForRow:0 inSection:1];
        cell =[tableView cellForRowAtIndexPath:index];
        if (cell != nil) {
            if (specifyScaleMode == 1)
            {
                cell.textLabel.textColor = [UIColor blackColor];
                cell.detailTextLabel.textColor = [UIColor blackColor];
            }
            else
            {
                cell.textLabel.textColor = [UIColor grayColor];
                cell.detailTextLabel.textColor = [UIColor grayColor];
            }
        }
        // liuqw 20110623 end
        
        [delegate didSpecifyScaleModeChanged:self];
	} else {
        if (specifyScaleMode == 1) {
            [self showZoomScaleInputView];
        }
    }
}

- (void) showZoomScaleInputView
{
    if (alertInputScale == nil) {
        // 1. init alert view.
        int minScale = 1;
        int maxScale = 200;
        NSString* tilte = [NSString stringWithFormat:NSLocalizedString(@"TITLE_ALERT_ZOOMSCALE_INPUT", nil), minScale, maxScale];
        self.alertInputScale = [[UIAlertView alloc] initWithTitle:tilte
                                                          message:@"             "
                                                         delegate:self
                                                cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
                                                otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_CANCEL", nil), 
                                (char *)nil];
        alertInputScale.tag = TAG_INPUT_SCALE_ALERT;
        
        // 2.1 init field text view.
        self.fieldInputScale = [[UITextField alloc] init];
        fieldInputScale.clearButtonMode = UITextFieldViewModeWhileEditing;
        fieldInputScale.autocorrectionType = UITextAutocorrectionTypeNo;
        fieldInputScale.borderStyle = UITextBorderStyleRoundedRect;
        fieldInputScale.keyboardType = UIKeyboardTypeNumbersAndPunctuation;
        fieldInputScale.font = [UIFont systemFontOfSize:22.0];
        fieldInputScale.adjustsFontSizeToFitWidth = YES;
        fieldInputScale.returnKeyType = UIReturnKeyDone;
        fieldInputScale.minimumFontSize = 2.0;
        fieldInputScale.tag = TAG_INPUT_SCALE_FIELD;
        fieldInputScale.delegate = self;
        [alertInputScale addSubview:fieldInputScale];
        alertInputScale.delegate = self;
        [alertInputScale show];
        
        // 2.2 init unit
        self.labelScalePercent = [[UILabel alloc]init];
        labelScalePercent.backgroundColor = [UIColor clearColor];
        labelScalePercent.textColor = [UIColor whiteColor];
        labelScalePercent.text = @"%";
        [alertInputScale addSubview:labelScalePercent];
    } else {
        fieldInputScale.text = @"";
        [alertInputScale show];
    }
        
    // 3. set frame.
    [self setInputScaleFieldViewPosition];
        
    [fieldInputScale becomeFirstResponder];
}

- (void) setInputScaleFieldViewPosition
{
    UILabel* labelTitle =  ((UILabel*)[[alertInputScale subviews]objectAtIndex:1]);
    if (labelTitle != nil) {
        float originX = 45;
        float originY = labelTitle.frame.origin.y + labelTitle.frame.size.height;   
        float width = 170;
        float height = 30;
        float offset = 3;
        float percentWidth = 30;
        
        if (Utility::UIDeviceIsiPad() == NO) {
            if ([self UIDeviceIsPortrait] == YES) {
                height = 30;
                offset = 4;
                percentWidth = 30;
            } else {
                height = 27;
                offset = 2;
                percentWidth = 27;
            }
        } else {
            if ([self UIDeviceIsPortrait] == YES) {
                height = 30;
                offset = 4;
                percentWidth = 30;
            } else {
                height = 27;
                offset = 4;
                percentWidth = 27;
            }
        }
        
        fieldInputScale.frame = CGRectMake(originX, originY + offset, width, height);
        labelScalePercent.frame = CGRectMake(originX + width + 6, originY + offset, percentWidth, percentWidth);
    }
}

- (void) setInputScaleFieldViewPositionWithOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
    if (Utility::UIDeviceIsiPad() == NO) {
        if (toInterfaceOrientation != self.interfaceOrientation) {
            float originX, originY, width, height;
            if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation)) {
                originX = fieldInputScale.frame.origin.x;
                originY = fieldInputScale.frame.origin.y - 8;    
                width = 170;
                height = 27;
            } else {
                originX = fieldInputScale.frame.origin.x;
                originY = fieldInputScale.frame.origin.y + 8;    
                width = 170;
                height = 30;
            }
            fieldInputScale.frame = CGRectMake(originX, originY, width, height);
            labelScalePercent.frame = CGRectMake(originX + width + 6, originY, height, height);
        }
    } else {
        float originX, originY, width, height;
        if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation)) {
            originX = fieldInputScale.frame.origin.x;
            originY = fieldInputScale.frame.origin.y - 8;
            width = 170;
            height = 27;
        } else {
            originX = fieldInputScale.frame.origin.x;
            originY = fieldInputScale.frame.origin.y + 8;
            width = 170;
            height = 30;
        }
        fieldInputScale.frame = CGRectMake(originX, originY, width, height);
        labelScalePercent.frame = CGRectMake(originX + width + 6, originY, height, height);
    }
}

- (void) willPresentAlertView:(UIAlertView *)alertView
{
	 [self setInputScaleFieldViewPosition];
}

-(NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	NSIndexPath *oldIndexPath = nil;
	
    if (indexPath.section == 0) {
        oldIndexPath = [NSIndexPath indexPathForRow:specifyScaleMode inSection:indexPath.section];
    }

	UITableViewCell *oldCell = [tableView cellForRowAtIndexPath:oldIndexPath];
	if (oldIndexPath != indexPath) 
	{
		oldCell.accessoryType = UITableViewCellAccessoryNone;
	}
	else 
	{
		return nil;
	}
	
	return indexPath;
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
    [alertInputScale release];
    [fieldInputScale release];
    [labelScalePercent release];
    [super dealloc];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (alertView.tag == TAG_INPUT_SCALE_ALERT && buttonIndex == 0) {
        [self inputZoomScaleWithAlertView:alertView];
    } else if (alertView.tag == TAG_INPUT_SCALE_ERROR && buttonIndex == 0) {
        [self showZoomScaleInputView];
    }
}

#pragma mark -
#pragma mark UITextFieldDelegate
- (BOOL)textFieldShouldReturn:(UITextField *)theTextField 
{
    if (theTextField.tag == TAG_INPUT_SCALE_FIELD) {
        [theTextField resignFirstResponder];
        UIAlertView* superView = (UIAlertView*)[theTextField superview];
        if (superView != nil) {
            [self alertView:superView clickedButtonAtIndex:0];
            [superView dismissWithClickedButtonIndex:0 animated:YES];
        }
    } 
    
	return YES;
}

- (void) inputZoomScaleWithAlertView:(UIAlertView*)alertView
{
    if (alertView != nil) {
        UITextField* fieldInput = (UITextField*)[alertView viewWithTag:TAG_INPUT_SCALE_FIELD];
        if (fieldInput == nil)
            return;
        
        NSString *stringValue = [fieldInput text];
        int inputValue = 0;
        NSScanner *scanner = [NSScanner scannerWithString:stringValue];
        BOOL isInt = [scanner scanInt:&inputValue]&&[scanner isAtEnd];
        if (isInt == NO)
        {
            NSString* errorMessage = NSLocalizedString(@"MSG_ERROR_INPUT_NO_NUMBER", nil);
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil) 
                                                            message:errorMessage 
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
                                                  otherButtonTitles:nil];
            alert.tag = TAG_INPUT_SCALE_ERROR;
            [alert show];
            [alert release];
            return;
        }
        
        int scale = inputValue;
        int minScale = 1; 
        int maxScale = 200;
        if (scale < minScale || scale > maxScale)
        {
            NSString* errorMessage = NSLocalizedString(@"MSG_ERROR_INPUT_OUT_RANGE", nil);
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:NSLocalizedString(@"TITLE_ALERT_WARNING", nil) 
                                                            message:errorMessage 
                                                           delegate:self 
                                                  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil) 
                                                  otherButtonTitles:nil];
            alert.tag = TAG_INPUT_SCALE_ERROR;
            [alert show];
            [alert release];
        }
        else
        {
            fixedScale = scale;
            [self.tableView reloadData];
            [delegate didSpecifyScaleModeChanged:self];
        }            
    }
}

- (BOOL) UIDeviceIsPortrait
{
	if ((self.interfaceOrientation == UIInterfaceOrientationPortrait) || 
		(self.interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown))
	{
		return YES;
	} else {
		return NO;
	}
}


@end

