//
//  DWLoginAnnPropertySettingsController.h
//  DWViewer
//
//  Created by panpan wang on 12-3-27.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

#import "mpc_api.h"
#import "anncase.h"
#import "mpc_pd.h"

#define LOCAL_RESIST_ANNOTATION_DIR	  @"anncase"
#define LOCAL_RESIST_ANNOTATION_FILE  @"anncase.anc"
#define LOCAL_RESIST_ANNOTATION_COUNT 10

//// DWResistAnnotationManager
////--------------------------------------------
@interface DWResistAnnotationManager : NSObject

+ (int)      getResistAnnotationCount;
+ (NSArray*) getResistAnnotationImageListWithImageWidth:(int)width;
+ (BOOL)	 addResistAnnotationToLocal:(MPCObject*)obj 
						 withSession:(MPCSession*)session;
+ (BOOL)	 deleteResistAnnotatinWithIndex:(NSArray*)indexList;
+ (BOOL)	 getResistAnnotationWithIndex:(NSInteger)annIndex 
						   withSession:(MPCSession*)session
					  withAnnObjectRef:(MPCObject **)annObject;

@end


//// DWLoginAnnThumbnailImage
////--------------------------------------------
@interface DWLoginAnnThumbnailImage: UIButton 
{
	UIImageView* backgroundImageView_;
	BOOL         selected_;
}
@property (nonatomic, retain) UIImageView* backgroundImageView;
@property BOOL selected;

- (id)   initWithFrame:(CGRect)frame;
- (void) setThumbnailImage:(UIImage*)img;
- (void) setThumbnailImageFrame;
- (void) showSelectBorder;
- (void) hideSelectBorder;

@end


//// DWLoginAnnPropertySettingsController
////--------------------------------------------
enum LoginActionType
{
	kLoginActionRead = 0,
	kLoginActionEdit
};

@protocol DWLoginAnnotationPropertySettingsDelegate <NSObject>
@optional
- (void) didSelectLoginAnnotationWithAnnotationIndex:(int)index;
@end

@interface DWLoginAnnPropertySettingsController : UITableViewController<UIAlertViewDelegate>
{
	id<DWLoginAnnotationPropertySettingsDelegate> delegate;

	NSMutableArray			*loginAnnoArrays_;
	LoginActionType			actionType_;
	
	UIActivityIndicatorView	*activeIndicator_;
	UIInterfaceOrientation	orientation_;
	
	int						loginAnnIndex;
	BOOL					editMode;
}
@property (nonatomic,assign) id <DWLoginAnnotationPropertySettingsDelegate> delegate;
@property int loginAnnIndex;

#pragma mark - 
#pragma mark init.
- (id)initWithActionType:(LoginActionType)type 
		  andOrientation:(UIInterfaceOrientation)orientation;

- (BOOL) loadLoginAnnotationData;

#pragma mark - 
#pragma mark navigation bar items.
- (void) initNavigationbarItems;
- (void) actionOnTouchBackButtonItem;
- (void) actionOnTouchEditButtonItem:(UIBarButtonItem*)buttonItem;
- (void) actionOnTouchDoneButtonItem:(UIBarButtonItem*)buttonItem;

#pragma mark - 
#pragma mark tool bar items.
- (void) initToolbarItems;
- (void) updateToolBarStatus;
- (void) actionOnTouchDeleteButton;

#pragma mark - 
#pragma mark Indicator.
- (void) displayIndicator;
- (void) hideIndicator;

#pragma mark - 
#pragma mark init cell method.
- (void) initTableViewCell:(UITableViewCell*)cell 
			 withIndexPath:(NSIndexPath*)indexPath
			withActionType:(LoginActionType)type;
- (void) actionOnTouchLoginAnnoButton:(id)sender;

#pragma mark - 
#pragma mark common method.
- (UIBarButtonItem*) createButtonItemWithTitle:(NSString*)title 
									 andAction:(SEL)action;
- (NSString*) getDeleteButtonIcon;

@end
