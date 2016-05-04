//
//  DocumentEditController.h
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DWAnnotationInfo.h"
#import "AnnotationManager.h"
#import "DWAnnGhostView.h"
#import "DWFreehandAnnPropertySettingsController.h"
#import "DWTextNotepadAnnPropertySettingsController.h"
#import "DWViewerGUIConst.h"
#import "DWViewerAppDelegate.h"
#import "Utility.h"

// wangpp 2012.4.13 start
#import "DWLoginAnnPropertySettingsController.h"
// wangpp 2012.4.13 end

typedef unsigned long	COLORREF;

enum EDIT_MODE
{
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
//	kEditMode = 0,
	kTopMenu = 0,
	kSelAnnote,
	// 2012.02.01(Ver2.1 New) M.Chikyu
    kAddFreehand,
    kAddNotepad,
    
    // yangjx 2012.3.28 start
    kAddLogin
    // yangjx 2012.3.28 end
};

enum MENU_BAR_TYPE
{
    kAnnotationBar = 0,
    kPropertyBar,
};

// DWBorderView
// --------------------------------------
@interface DWBorderView : UIView
{
	UIColor* contentColor_;
	UIColor* frameColor_;
}

@property (nonatomic, retain) UIColor* contentColor;
@property (nonatomic, retain) UIColor* frameColor;

- (id)initWithColor:(UIColor*)color;
- (void)addAction:(SEL)action target:(id)target;
@end

@interface DWSizeButton : UIButton
{
}

- (void)addAction:(SEL)action target:(id)target;
- (void)setTextColor:(UIColor*)color;
- (void)setSize:(int)size;
@end

// DocumentEditController
// --------------------------------------
@class PageViewManager;
@class PageEditManager;
@class DWEditScrollView;
@class DWAnnotationInfo;
@class DWColorSettingsViewController;
class XdwRectangle;

@interface DocumentEditController : UIViewController<DWAnnotationEditDelegate, 
                                                     UITextViewDelegate, 
                                                     UIScrollViewDelegate, 
                                                     UIPopoverControllerDelegate, 
                                                     // lixin 2011/09/15 start 
                                                     // NS-AR1007 の対応
                                                     UIAlertViewDelegate,
                                                     // lixin 2011/09/15 end 
                                                     DWAnnotationEditDelegate, 
                                                     DWFreeHandAnnotationEditDelegate,
                                                     DWFreeHandAnnPropertySettingsDelegate, 
                                                     DWTextNotepadAnnPropertySettingsDelegate,
                                                     // wangpp 2012.4.13 start
                                                     // login
                                                     DWLoginAnnotationPropertySettingsDelegate
                                                     // wangpp 2012.4.13 end
													>
{
	DWViewerAppDelegate*                applicationDelegate_;
    
    // recognizer.
    UITapGestureRecognizer*             singleTapGestureRecognizer;
    UITapGestureRecognizer*             doubleTapGestureRecognizer;
	UITapGestureRecognizer*             twoFingerTapGestureRecognizer;
	UILongPressGestureRecognizer*       longPressTapGestureRecognizer;
	UIPanGestureRecognizer*             panGestureRecognizer;
	// add pinchgesture by yangjx 20110901 start
    UIPinchGestureRecognizer*           pinchGestureRecognizer;
	// add pinchgesture by yangjx 20110901 end
	
    // menu bar.
    UIToolbar*              annotationbar_;
    UIToolbar*              propertybar_;
    UIScrollView*           bgViewMenubar_;
    NSMutableArray*         annotationbarItem_;
    NSMutableArray*         propertybarItemNormal_;
    NSMutableArray*         propertybarItemNotepad_;
    NSMutableArray*         propertybarItemFreehand_;
    
    // yangjx 2012.3.28 start
    NSMutableArray*         propertybarItemLogin_;
    // yangjx 2012.3.28 end
    
    PageViewManager*        pageViewManager_;
    PageEditManager*        pageEditManager_;
    
    DWEditScrollView*       pageView_;
    int                     pageIndex_;
    float                   pageScale;
    CGPoint                 pageOffset;
    
    EDIT_MODE               editMode;
    
    DWAnnotationInfo*       dwAnnoInfo_;
    
    // annotation property value..
	UIColor*                freehandColor_;
	int                     freehandLineSize_;
	
	// wangpp 2012.2.28 start
    // freehand transparent
    BOOL                   freehandTransparent_;
    // wangpp 2012.2.28 end
	
	UIColor*                textNotepadColor_;
	UIColor*                textNotepadFontColor_;
	int                     textNotepadFontSize_;
    BOOL                    isCanSetTextProp;
    
	// edit notepad annotation.
    UIToolbar*              dwInputToolbar_;
    UITextView*             dwInputField_;
	UIToolbar *             dwFinishToolbar_;
    
    CGPoint					notepadPosition;
	BOOL					isKeyboardShowed;
	int						annotationIndex;
	CGSize                  keyboardSize;
	
	// wangpp 2012.4.13 start
	// login
	int                     loginAnnoIndex_;
	int						loginAnnoCount_;
	// wangpp 2012.4.13 end

    // property page view.
    UIPopoverController*    dwAnnPropertyPopController;
    UINavigationController* dwAnnPropertyNavController;
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	COLORREF				dwSizeButtonColor;
	// 2012.02.01(Ver2.1 New) M.Chikyu
     
	DWFreeHandAnnGhostView* dwFreehandGhostView;
    BOOL                    isDrawFreehandLine;
    
    int                     popIndex;
	
	// zhaijie 2011/09/08 Start
	// NS - AR015
	float fontSizeLabelWidth;
	// zhaijie 2011/09/08 End
	
	// iPadのツールバーの上部に境界線を入れる の対応
	float                 menubarStartPositionY;
    BOOL                  isDeviceIsiPad;
	
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	UIActivityIndicatorView*	activeIndicator_;
	BOOL						isIndicatorAnimating;
	// 2012.02.01(Ver2.1 New) M.Chikyu

	// AR19008
	// 2012.02.20 M.Chikyu start.
	UIInterfaceOrientation orientation_;
	// 2012.02.20 M.Chikyu end.
}
@property (nonatomic, retain) DWAnnotationInfo* dwAnnoInfo;
@property (nonatomic, retain) UIToolbar* dwInputToolbar;
@property (nonatomic, retain) UITextView* dwInputField;
@property (nonatomic, retain) DWFreeHandAnnGhostView *dwFreehandGhostView;
@property (nonatomic, retain) UIColor* freehandColor;
@property (nonatomic) int     freehandLineSize;

// wangpp 2012.2.28 start
// freehand transparent
@property  BOOL freehandTransparent;
// wangpp 2012.2.28 end

@property (nonatomic, retain) UIColor* textNotepadColor;
@property (nonatomic, retain) UIColor* textNotepadFontColor;
@property (nonatomic) int     textNotepadFontSize;
@property (nonatomic, retain) DWEditScrollView* pageView_;
@property (nonatomic, retain) UIToolbar *dwFinishToolbar;

// wangpp 2012.4.13 start
// login
@property int  loginAnnoIndex;
// wangpp 2012.4.13 end

@property (nonatomic, retain) UIPopoverController* dwAnnPropertyPopController;
@property (nonatomic, retain) UINavigationController* dwAnnPropertyNavController;
@property (nonatomic, readonly) EDIT_MODE editMode;

// AR19008
// 2012.02.20 M.Chikyu start.
/*
- (id) initWithPageViewManager:(PageViewManager*)mgr
                 withPageIndex:(int)pageIndex 
                 withPageScale:(long)scale
                withPageOffset:(CGPoint)offset;
 */

- (id) initWithPageViewManager:(PageViewManager*)mgr
                 withPageIndex:(int)pageIndex 
                 withPageScale:(long)scale
                withPageOffset:(CGPoint)offset
			   withOrientation:(UIInterfaceOrientation)orientation;
// 2012.02.20 M.Chikyu end.

// init bar items.
- (void) initMenubarControls;
- (void) initAnnotationBarItem;
- (void) initNormalPropertyBarItem;
- (void) initNotepadPropertyBarItem;
- (void) initFreehandPropertyBarItem;
- (void) inheritPageViewStatus;

// yangjx 2012.3.28 start
- (void) initLoginAnnotPropertyBarItem;
// yangjx 2012.3.28 end



// --------------------------------
// action........
// tool bar item.
- (void) actionOnTouchDoneButton;
// lixin 2011/09/15 start
// NS-AR1007 の対応
- (void) returnToDisplayModeWithSucceed:(BOOL)succeed;
// lixin 2011/09/15 end

- (void) actionOnTouchFreeHandButton;
- (void) actionOnTouchNotepadButton;

// yangjx 2012.3.28 start
- (void) actionOnTouchLoginAnnButton;
// yangjx 2012.3.28 end

// property bar item.
// common item.
- (void) actionOnTouchBackButton;
- (void) actionOnTouchDeleteButton;

// wangpp 2012.4.12 start
// login
- (void) actionOnTouchLoginAnnoationButton;
- (void) actionOnTouchSelectLoginAnnButton;
// wangpp 2012.4.12 end

// freehand item.
- (void) actionOnTouchFreehandColorButton;
- (void) actionOnTouchFreehandLineButton;

// wangpp 2012.2.28 start
// freehand transparent
- (void) actionOnTouchFreeHandTransparentButton;
// wangpp 2012.2.28 end

// notepad item.
- (void) actionOnTouchNotepadBGColorButton;
- (void) actionOnTouchNotepadFontSizeButton;
- (void) actionOnTouchNotepadFontColorButton;

- (DWAnnotationInfo*) isTappedOnAnnotationWithTouchPoint:(CGPoint)point;
- (void) OpenFreehandAnnotationPropertySettingsView:(Utility::PROPERTY_TYPE)type;
- (void) OpenTextNotepadAnnotationPropertySettingsView:(Utility::PROPERTY_TYPE)type;

// select annotation.
- (void) selectAnnotation:(DWAnnotationInfo*)dwInfo;
- (void) enterSelectStatusWithAnnotationInfo:(DWAnnotationInfo*)dwAnnoInfo;
- (void) exitSelectStatus;

// edit freehand annotation.
- (void) enterAddFreehandAnnotationStatus;
- (void) exitAddFreehandAnnotationStatus;
- (void) addNewFreehandAnnotationWithPointArray:(NSMutableArray *)points;
- (void) setLineWidthToFreehandGhostView;

// edit text notepad annotation.
- (void) showTextNotepadAnnotationInputView;
// liuqw 2011/09/22 start
// NS-AR1011 の対応
- (void) closeTextNotepadAnnotationInputView;
// liuqw 2011/09/22 end

- (void) actionOnKeyboardDidShow:(NSNotification *)notification;
- (void) didEndEditingTextNotepadAnnotationWithPoint:(CGPoint)point;
- (void) enterAddTextNotePadAnnotationWithFrame:(CGRect)frame;
- (void) exitAddTextNotepadAnnotation:(id)sender;
- (void) exitTextNotePadEdit:(id)sender;
- (CGRect) getNotepadAnnotationRect:(DWAnnotationInfo*)info;
- (CGRect) getNewTextNotepadAnnotationRectWithTouchPoint:(CGPoint)point;
- (NSString*) formatTextAnnotationContentWithTextOutput:(NSString *)text;
- (NSString*) formatTextAnnotationContentWithTextInput:(NSString *)text;
- (NSString*) formatTextForEditingWithTextInput:(NSString *)text;
- (int) getLineCountWithInputText:(NSString *)text;
- (int) getTextCountWithInputText:(NSString *)text;
// liuqw 2011/10/21 start
// NS-AR2004 の対応
- (int) getOutputTextCountWithInputText:(NSString *)text;
// liuqw 2011/10/21 end
- (CGSize) getCurrentPageSize;
- (CGSize) getTextAnnotationCustomSize:(DWTextNotepadAnnotationInfo *)info;

////*******
- (void) updateAnnotationPropertyWithAnnotationType:(int)type 
                                      withIsRefresh:(BOOL)refresh;
- (void) updateBorderViewRectForUpdateAnnotationSize;
- (void) udpateDeleteButtonEnabledPropertyWithAnnotationType:(int)type;
- (void) updateAnnotatinPropertyValueWithPropertyType:(Utility::PROPERTY_TYPE)type;
- (void) updateMenubarFrameForRotation;
- (BOOL) updateAnnotationProperty;

- (void) processEventWithTouchPoint:(CGPoint)touchPoint;
// 2012.02.01(Ver2.1 New) M.Chikyu
/*
- (void) zoomPageViewToPagefit:(DWEditScrollView*)pageView;
 */
- (void) resizePageView;
- (void) refreshPageView;
// 2012.02.01(Ver2.1 New) M.Chikyu

// 2012.02.14 M.Chikyu start.
- (void) rotatePageView;
// 2012.02.14 M.Chikyu end.

- (void) removeAllGhostViews;
- (BOOL) isAnnotationOutPageEdgeWithAnnotationInfo:(DWAnnotationInfo *)info;

//--------------------
// private method.
- (void) transformMenubar:(MENU_BAR_TYPE)type;
- (CGRect) getDeviceScreenRect;
- (CGSize) getDeviceKeyboardSize:(NSDictionary*)dic;
- (float) getToolbarHeight;
- (BOOL) UIDeviceIsPortrait;

//--------------------
// get button icon
- (NSString*) getFreehandButtonIcon;
- (NSString*) getTextNotepadButtonIcon;
- (NSString*) getFreehandColorButtonIcon;
- (NSString*) getFreehandLineSizeButtonIcon;
// wangpp 2012.2.28 start
// freehand transparent
- (NSString*) getFreehandTransparentButtonIcon:(BOOL)trans;
// wangpp 2012.2.28 end
- (NSString*) getTextNotepadBackgroundColorButtonIcon;
- (NSString*) getTextNotepadFontColorButtonIcon;
- (NSString*) getTextNotepadFontSizeButtonIcon;
- (NSString*) getDeleteButtonIcon;

// wangpp 2012.4.13 start
// login
- (NSString*) getLoginButtonIcon;
- (NSString*) getRegistLoginButtonIcon;
- (NSString*) getSelectLoginAnnButtonIcon;
// wangpp 2012.4.13 end


// lixin 2011/09/28 start
// NS-AR1018 の対応
/*
// lixin 2011/09/14 start
// NS-AR1002 の対応
- (NSString*) getSelectFreehandButtonIcon;
- (NSString*) getSelectTextNotepadButtonIcon;
// lixin 2011/09/14 end
*/ 
// lixin 2011/09/28 end
- (NSString*) getFileFullName;
- (CGPoint) getPageOffset;

// 2012.02.01(Ver2.1 New) M.Chikyu
- (void) actionOnDoubleTap:(DWAnnotationInfo *)dwInfo;

- (float) getCurrentZoomScale;

- (void) displayIndicator;
- (void) hideIndicator;
// 2012.02.01(Ver2.1 New) M.Chikyu

@end
