/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/UIKit.framework/UIKit
 */

@class <UINavigationBarDelegate>, NSArray, NSDictionary, NSMutableArray, NSString, UIColor, UIImage, UIImageView, UINavigationItem, UISwipeGestureRecognizer, UIView, _UIViewControllerTransitionContext;

@interface UINavigationBar : UIView <UIGestureRecognizerDelegate, _UIShadowedView, _UIBasicAnimationFactory, UIStatusBarTinting, _UIBarPositioningInternal, NSCoding, UIBarPositioning> {
    struct { 
        unsigned int animate : 1; 
        unsigned int animationDisabledCount : 10; 
        unsigned int transitioningBarStyle : 1; 
        unsigned int newBarStyle : 3; 
        unsigned int transitioningToTranslucent : 1; 
        unsigned int barStyle : 3; 
        unsigned int barTranslucence : 3; 
        unsigned int disableLayout : 1; 
        unsigned int backPressed : 1; 
        unsigned int animatePromptChange : 1; 
        unsigned int pendingHideBackButton : 1; 
        unsigned int titleAutosizesToFit : 1; 
        unsigned int usingNewAPI : 1; 
        unsigned int forceFullHeightInLandscape : 1; 
        unsigned int isLocked : 1; 
        unsigned int shouldUpdatePromptAfterTransition : 1; 
        unsigned int crossfadeItems : 1; 
        unsigned int autoAdjustTitle : 1; 
        unsigned int isContainedInPopover : 1; 
        unsigned int needsDrawRect : 1; 
        unsigned int animationCleanupCancelled : 1; 
        unsigned int layoutInProgress : 1; 
        unsigned int dynamicDuration : 1; 
        unsigned int isInteractive : 1; 
        unsigned int cancelledTransition : 1; 
        unsigned int animationCount : 4; 
        unsigned int backgroundLayoutNeedsUpdate : 1; 
        unsigned int backgroundImageNeedsUpdate : 1; 
    NSMutableArray *__animationIds;
    BOOL __condensed;
    UIView *_accessoryView;
    id _appearanceStorage;
    UIImageView *_backIndicatorView;
    NSString *_backdropViewLayerGroupName;
    UIView *_backgroundView;
    int _barPosition;
    UIColor *_barTintColor;
    id _currentAlert;
    id _delegate;
    NSMutableArray *_itemStack;
    NSArray *_leftViews;
    _UIViewControllerTransitionContext *_navControllerAnimatingContext;
    } _navbarFlags;
    BOOL _needsUpdateBackIndicatorImage;
    UISwipeGestureRecognizer *_popSwipeGestureRecognizer;
    UIView *_prompt;
    float _requestedMaxBackButtonWidth;
    float _rightMargin;
    NSArray *_rightViews;
    NSMutableArray *_slideTransitionClippingViews;
    unsigned int _state;
    UIView *_titleView;
    BOOL _wantsLetterpressContent;
}

@property(setter=_setAnimationIds:,retain) NSMutableArray * _animationIds;
@property(setter=_setBackIndicatorImage:,retain) UIImage * _backIndicatorImage;
@property(setter=_setBackIndicatorLeftMargin:) float _backIndicatorLeftMargin;
@property(retain,readonly) NSString * _backdropViewLayerGroupName;
@property(setter=_setBackdropViewLayerGroupName:,retain) NSString * _backdropViewLayerGroupName;
@property(setter=_setBackgroundView:,retain) UIView * _backgroundView;
@property(readonly) int _barTranslucence;
@property(getter=_isCondensed,setter=_setCondensed:) BOOL _condensed;
@property(readonly) float _heightIncludingBackground;
@property(setter=_setNeedsUpdateBackIndicatorImage:) BOOL _needsUpdateBackIndicatorImage;
@property(setter=_setRequestedMaxBackButtonWidth:) float _requestedMaxBackButtonWidth;
@property(setter=_setRequestedMaxBackButtonWidth:) float _requestedMaxBackButtonWidth;
@property(setter=_setShadowAlpha:) float _shadowAlpha;
@property(setter=_setWantsLetterpressContent:) BOOL _wantsLetterpressContent;
@property(retain) UIImage * backIndicatorImage;
@property(retain) UIImage * backIndicatorTransitionMaskImage;
@property(retain,readonly) UINavigationItem * backItem;
@property(readonly) int barPosition;
@property int barStyle;
@property(retain) UIColor * barTintColor;
@property(copy,readonly) NSString * debugDescription;
@property <UINavigationBarDelegate> * delegate;
@property(copy,readonly) NSString * description;
@property(readonly) unsigned int hash;
@property(copy) NSArray * items;
@property(retain) UIImage * shadowImage;
@property(readonly) Class superclass;
@property(retain) UIColor * tintColor;
@property(copy) NSDictionary * titleTextAttributes;
@property(retain,readonly) UINavigationItem * topItem;
@property(getter=isTranslucent) BOOL translucent;

+ (id)_bottomColorForBackgroundImage:(id)arg1 viewSize:(struct CGSize { float x1; float x2; })arg2;
+ (void)_initializeForIdiom:(int)arg1;
+ (void)_setUseCustomBackButtonAction:(BOOL)arg1;
+ (id)_statusBarBaseTintColorForStyle:(int)arg1 translucent:(BOOL)arg2 tintColor:(id)arg3 backgroundImage:(id)arg4 viewSize:(struct CGSize { float x1; float x2; })arg5;
+ (id)_statusBarBaseTintColorForStyle:(int)arg1 translucent:(BOOL)arg2 tintColor:(id)arg3;
+ (BOOL)_useCustomBackButtonAction;
+ (id)defaultPromptFont;
+ (struct CGSize { float x1; float x2; })defaultSize;
+ (struct CGSize { float x1; float x2; })defaultSizeForOrientation:(int)arg1;
+ (struct CGSize { float x1; float x2; })defaultSizeWithPrompt;
+ (struct CGSize { float x1; float x2; })defaultSizeWithPromptForOrientation:(int)arg1;
+ (void)setDefaultAnimationDuration:(double)arg1;

- (void)_accessibilityButtonShapesDidChangeNotification:(id)arg1;
- (void)_accessibilityButtonShapesParametersDidChange;
- (int)_activeBarMetrics;
- (void)_addItem:(id)arg1 withEffectiveDelegate:(id)arg2 transition:(int)arg3;
- (void)_addItems:(id)arg1 withEffectiveDelegate:(id)arg2 transition:(int)arg3;
- (id)_allViews;
- (void)_animateOldBackButtonView:(id)arg1 toNewBackButtonView:(id)arg2 duration:(float)arg3 initialFrameForIncomingView:(id)arg4 destinationFrameForOutgoingView:(id)arg5 animationCleanup:(id)arg6;
- (id)_animationIds;
- (id)_appearanceStorage;
- (void)_applySPIAppearanceToButtons;
- (float)_autolayoutSpacingAtEdge:(int)arg1 inContainer:(id)arg2;
- (float)_autolayoutSpacingAtEdge:(int)arg1 nextToNeighbor:(id)arg2;
- (float)_backIndicatorClippingMargin;
- (id)_backIndicatorImage;
- (float)_backIndicatorLeftMargin;
- (float)_backTitleWidthOverTitleWidthForMatchingBackButtonView:(id)arg1 titleView:(id)arg2 withBackButtonWidth:(float)arg3;
- (id)_backdropViewLayerGroupName;
- (int)_backgroundBackdropStyle;
- (void)_backgroundFadeDidFinish:(id)arg1 finished:(id)arg2 context:(id)arg3;
- (id)_backgroundView;
- (id)_backgroundViewForPalette:(id)arg1;
- (BOOL)_backgroundViewSuppressesAdaptiveBackdrop;
- (int)_barPosition;
- (void)_barSizeDidChangeAndSoDidHeight:(BOOL)arg1;
- (int)_barStyle:(BOOL)arg1;
- (BOOL)_barStyleSuppressesAdaptiveBackdrop;
- (int)_barTranslucence;
- (BOOL)_barTranslucenceSuppressesAdaptiveBackdrop;
- (id)_basicAnimationForView:(id)arg1 withKeyPath:(id)arg2;
- (struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })_boundsForPrompt:(id)arg1 inRect:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })arg2 withFont:(id)arg3 barStyle:(int)arg4;
- (BOOL)_canDrawContent;
- (BOOL)_canHandleStatusBarTouchAtLocation:(struct CGPoint { float x1; float x2; })arg1;
- (void)_cancelInProgressPushOrPop;
- (void)_cancelInteractiveTransition:(float)arg1 completionSpeed:(float)arg2 completionCurve:(int)arg3;
- (void)_cancelInteractiveTransition;
- (id)_commonHitTest:(struct CGPoint { float x1; float x2; })arg1 forView:(id)arg2;
- (void)_commonNavBarInit;
- (void)_configurePaletteConstraintsIfNecessary;
- (BOOL)_contentHuggingDefault_isUsuallyFixedHeight;
- (void)_crossFadeToBarBackgroundImageForItem:(id)arg1;
- (id)_currentBackButtonForNthItemFromTop:(unsigned int)arg1;
- (int)_currentBarStyle;
- (id)_currentLeftViews;
- (id)_currentRightViews;
- (BOOL)_customBackgroundImageSuppressesAdaptiveBackdrop;
- (BOOL)_customBackgroundImageSuppressesAdaptiveBackdropForPalette;
- (void)_customViewChangedForButtonItem:(id)arg1;
- (void)_decrementAnimationCountIfNecessary;
- (int)_defaultBarMetrics;
- (id)_defaultTitleFont;
- (id)_defaultTitleFontFittingHeight:(float)arg1 withScaleAdjustment:(float)arg2;
- (id)_defaultTitleFontWithScaleAdjustment:(float)arg1;
- (BOOL)_deferShadowToSearchBar;
- (void)_didChangeFromIdiom:(int)arg1 onScreen:(id)arg2 traverseHierarchy:(BOOL)arg3;
- (void)_didMoveFromWindow:(id)arg1 toWindow:(id)arg2;
- (BOOL)_didVisibleItemsChangeWithNewItems:(id)arg1 oldItems:(id)arg2;
- (id)_effectiveBackIndicatorImage;
- (float)_effectiveBackIndicatorLeftMargin;
- (id)_effectiveBackIndicatorTransitionMaskImage;
- (id)_effectiveBarTintColor;
- (void)_effectiveBarTintColorDidChangeWithPreviousColor:(id)arg1;
- (id)_effectiveDelegate;
- (void)_evaluateBackIndicatorForHilightedState:(BOOL)arg1 ofBarButtonItem:(id)arg2 inNavigationItem:(id)arg3;
- (void)_fadeAllViewsIn;
- (void)_fadeAllViewsOut;
- (void)_fadeViewOut:(id)arg1;
- (void)_fadeViewsIn:(id)arg1;
- (void)_fadeViewsOut:(id)arg1;
- (void)_finishInteractiveTransition:(float)arg1 completionSpeed:(float)arg2 completionCurve:(int)arg3;
- (BOOL)_gestureRecognizerShouldBegin:(id)arg1;
- (void)_getTitleViewFrame:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; }*)arg1 leftViewFrames:(id)arg2 rightViewFrames:(id)arg3 forItemAtIndex:(unsigned int)arg4 returnedIdealWidthOfTextContent:(float*)arg5 availableLayoutWidthForTextContent:(float*)arg6 idealBackButtonWidth:(float*)arg7;
- (void)_getTitleViewFrame:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; }*)arg1 leftViewFrames:(id)arg2 rightViewFrames:(id)arg3 forItemAtIndex:(unsigned int)arg4;
- (void)_getTitleViewFrame:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; }*)arg1 leftViewFrames:(id)arg2 rightViewFrames:(id)arg3;
- (void)_gkApplyTheme:(id)arg1 navbarStyle:(int)arg2;
- (void)_gkApplyTheme:(id)arg1;
- (void)_handleMouseDownAtPoint:(struct CGPoint { float x1; float x2; })arg1;
- (void)_handleMouseUpAtPoint:(struct CGPoint { float x1; float x2; })arg1;
- (void)_handlePopSwipe:(id)arg1;
- (BOOL)_hasBackButton;
- (BOOL)_hasCustomAutolayoutNeighborSpacing;
- (BOOL)_hasInvisibleCustomBackgroundImage;
- (float)_heightIncludingBackground;
- (void)_hideButtonsAnimationDidStop:(id)arg1 finished:(id)arg2 context:(id)arg3;
- (BOOL)_hidesShadow;
- (void)_incrementAnimationCountIfNecessary;
- (BOOL)_isCondensed;
- (BOOL)_isIncomingButtonSameAsOutgoingButtonOnLeft:(BOOL)arg1;
- (id)_itemStack;
- (int)_itemStackCount;
- (void)_layoutBackgroundViewConsideringAdaptiveBackdropAndChangedHeight:(BOOL)arg1;
- (BOOL)_legacyIsTranslucent;
- (BOOL)_modernIsTranslucent;
- (void)_navBarButtonPressed:(id)arg1;
- (void)_navigationAnimationDidFinish:(id)arg1 finished:(id)arg2 context:(id)arg3;
- (BOOL)_needsUpdateBackIndicatorImage;
- (id)_nthNavigationItemFromTop:(int)arg1;
- (void)_palette:(id)arg1 isAttaching:(BOOL)arg2 didComplete:(BOOL)arg3;
- (void)_popForTouchAtPoint:(struct CGPoint { float x1; float x2; })arg1;
- (id)_popNavigationItemWithTransition:(int)arg1;
- (void)_popNestedNavigationItem;
- (void)_populateArchivedSubviews:(id)arg1;
- (void)_prepareForPopAnimationWithNewTopItem:(id)arg1;
- (void)_prepareForPushAnimationWithItems:(id)arg1;
- (void)_propagateEffectiveBarTintColorWithPreviousColor:(id)arg1;
- (void)_pushNavigationItem:(id)arg1 transition:(int)arg2;
- (void)_pushNestedNavigationItem:(id)arg1;
- (void)_reenableUserInteraction;
- (void)_reenableUserInteractionWhenReadyWithContext:(id)arg1;
- (void)_removeAccessoryView;
- (void)_removeItemsFromSuperview:(id)arg1;
- (float)_requestedMaxBackButtonWidth;
- (void)_resetBackgroundImageAsNecessary;
- (void)_setActiveBarMetrics:(int)arg1;
- (void)_setAnimationIds:(id)arg1;
- (void)_setAutoAdjustTitle:(BOOL)arg1;
- (void)_setBackButtonBackgroundImage:(id)arg1 mini:(id)arg2 forStates:(unsigned int)arg3;
- (void)_setBackIndicatorImage:(id)arg1;
- (void)_setBackIndicatorLeftMargin:(float)arg1;
- (void)_setBackIndicatorPressed:(BOOL)arg1 initialPress:(BOOL)arg2;
- (void)_setBackdropViewLayerGroupName:(id)arg1;
- (void)_setBackgroundImage:(id)arg1 mini:(id)arg2;
- (void)_setBackgroundView:(id)arg1;
- (void)_setBarPosition:(int)arg1;
- (void)_setBarStyle:(int)arg1;
- (void)_setButtonBackgroundImage:(id)arg1 mini:(id)arg2 forStates:(unsigned int)arg3;
- (void)_setButtonItemTextColor:(id)arg1 shadowColor:(id)arg2 forState:(unsigned int)arg3;
- (void)_setButtonItemTextColor:(id)arg1 shadowColor:(id)arg2;
- (void)_setButtonTextShadowOffset:(struct CGSize { float x1; float x2; })arg1;
- (void)_setCondensed:(BOOL)arg1;
- (void)_setDefaultBarMetrics:(int)arg1;
- (void)_setDeferShadowToSearchBar:(BOOL)arg1;
- (void)_setHidesShadow:(BOOL)arg1;
- (void)_setIsContainedInPopover:(BOOL)arg1;
- (void)_setItems:(id)arg1 transition:(int)arg2 reset:(BOOL)arg3;
- (void)_setItems:(id)arg1 transition:(int)arg2;
- (void)_setItemsUpToItem:(id)arg1 transition:(id)arg2;
- (void)_setLeftView:(id)arg1 rightView:(id)arg2;
- (void)_setLeftViews:(id)arg1 rightViews:(id)arg2;
- (void)_setNeedsUpdateBackIndicatorImage:(BOOL)arg1;
- (void)_setPressedButtonItemTextColor:(id)arg1 shadowColor:(id)arg2;
- (void)_setRequestedMaxBackButtonWidth:(float)arg1;
- (void)_setReversesButtonTextShadowOffsetWhenPressed:(BOOL)arg1;
- (void)_setShadowAlpha:(float)arg1;
- (void)_setVisualAltitude:(float)arg1;
- (void)_setVisualAltitudeBias:(struct CGSize { float x1; float x2; })arg1;
- (void)_setWantsLetterpressContent:(BOOL)arg1;
- (void)_setupTopNavItem:(id)arg1 oldTopNavItem:(id)arg2;
- (float)_shadowAlpha;
- (id)_shadowView;
- (BOOL)_shouldPopForTouchAtPoint:(struct CGPoint { float x1; float x2; })arg1;
- (BOOL)_shouldShowBackButtonForNavigationItem:(id)arg1;
- (void)_showLeftRightButtonsAnimationDidStop:(id)arg1 finished:(id)arg2 context:(id)arg3;
- (void)_startBarStyleAnimation:(int)arg1 withTintColor:(id)arg2;
- (void)_startInteractiveNavigationBarTransition;
- (void)_startPopAnimationFromItems:(id)arg1 fromBarStyle:(int)arg2 toItems:(id)arg3 toBarStyle:(int)arg4;
- (void)_startPushAnimationFromItems:(id)arg1 fromBarStyle:(int)arg2;
- (int)_statusBarStyle;
- (id)_statusBarTintColor;
- (BOOL)_subclassImplementsDrawBackgroundInRect;
- (BOOL)_subclassImplementsDrawRect;
- (unsigned int)_subviewIndexAboveBackground;
- (BOOL)_suppressBackIndicator;
- (id)_timingFunctionForAnimationInView:(id)arg1 withKeyPath:(id)arg2;
- (void)_tintViewAppearanceDidChange;
- (id)_titleTextColor;
- (int)_transitionForOldItems:(id)arg1 newItems:(id)arg2;
- (void)_updateBackIndicatorImage;
- (void)_updateBackgroundColor;
- (void)_updateBackgroundImage;
- (void)_updateInteractiveStatusBarTransitionPercent:(float)arg1 isFinished:(BOOL)arg2 didComplete:(BOOL)arg3 completionSpeed:(float)arg4 completionCurve:(int)arg5;
- (void)_updateInteractiveTransition:(float)arg1;
- (void)_updateNavigationBarItem:(id)arg1 forStyle:(int)arg2 previousTintColor:(id)arg3;
- (void)_updateNavigationBarItem:(id)arg1 forStyle:(int)arg2;
- (void)_updateNavigationBarItemsForStyle:(int)arg1 previousTintColor:(id)arg2;
- (void)_updateNavigationBarItemsForStyle:(int)arg1;
- (void)_updateOpacity;
- (void)_updatePaletteBackgroundIfNecessary;
- (void)_updateTitleView;
- (BOOL)_wantsAdaptiveBackdrop;
- (BOOL)_wantsAdaptiveBackdropForPalette;
- (BOOL)_wantsAdaptiveBackdropWhenNotHidden;
- (BOOL)_wantsLetterpressContent;
- (void)_willMoveToWindow:(id)arg1;
- (void)_wrapView:(id)arg1 inClippingViewWithLeftBoundary:(float)arg2 rightBoundary:(float)arg3 leftMaskImage:(id)arg4 leftMaskIsChevron:(BOOL)arg5 rightMaskImage:(id)arg6;
- (void)addConstraint:(id)arg1;
- (unsigned int)animationDisabledCount;
- (struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })availableTitleArea;
- (id)backButtonViewAtPoint:(struct CGPoint { float x1; float x2; })arg1;
- (id)backIndicatorImage;
- (id)backIndicatorTransitionMaskImage;
- (id)backItem;
- (id)backgroundImageForBarMetrics:(int)arg1;
- (id)backgroundImageForBarPosition:(int)arg1 barMetrics:(int)arg2;
- (int)barPosition;
- (int)barStyle;
- (id)barTintColor;
- (id)buttonItemShadowColor;
- (id)buttonItemTextColor;
- (id)createButtonWithContents:(id)arg1 width:(float)arg2 barStyle:(int)arg3 buttonStyle:(int)arg4 isRight:(BOOL)arg5;
- (id)currentBackButton;
- (id)currentLeftView;
- (id)currentRightView;
- (void)dealloc;
- (float)defaultBackButtonAlignmentHeight;
- (struct CGSize { float x1; float x2; })defaultSizeForOrientation:(int)arg1;
- (id)delegate;
- (void)didAddSubview:(id)arg1;
- (void)disableAnimation;
- (void)drawBackButtonBackgroundInRect:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })arg1 withStyle:(int)arg2 pressed:(BOOL)arg3;
- (void)drawBackgroundInRect:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })arg1 withStyle:(int)arg2;
- (void)drawRect:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })arg1;
- (int)effectiveInterfaceOrientation;
- (void)enableAnimation;
- (void)encodeWithCoder:(id)arg1;
- (BOOL)forceFullHeightInLandscape;
- (BOOL)gestureRecognizerShouldBegin:(id)arg1;
- (void)hideButtons;
- (id)hitTest:(struct CGPoint { float x1; float x2; })arg1 forEvent:(struct __GSEvent { }*)arg2;
- (id)hitTest:(struct CGPoint { float x1; float x2; })arg1 withEvent:(id)arg2;
- (id)initWithCoder:(id)arg1;
- (id)initWithFrame:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })arg1;
- (struct CGSize { float x1; float x2; })intrinsicContentSize;
- (void)invalidateIntrinsicContentSize;
- (BOOL)isAnimationEnabled;
- (BOOL)isElementAccessibilityExposedToInterfaceBuilder;
- (BOOL)isLocked;
- (BOOL)isMinibar;
- (BOOL)isTranslucent;
- (id)items;
- (void)layoutSubviews;
- (id)navigationItemAtPoint:(struct CGPoint { float x1; float x2; })arg1;
- (id)navigationItems;
- (void)popNavigationItem;
- (id)popNavigationItemAnimated:(BOOL)arg1;
- (id)prompt;
- (struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })promptBounds;
- (id)promptView;
- (void)pushNavigationItem:(id)arg1 animated:(BOOL)arg2;
- (void)pushNavigationItem:(id)arg1;
- (void)removeConstraint:(id)arg1;
- (void)setAccessoryView:(id)arg1 animate:(BOOL)arg2;
- (void)setAutoresizingMask:(unsigned int)arg1;
- (void)setBackIndicatorImage:(id)arg1;
- (void)setBackIndicatorTransitionMaskImage:(id)arg1;
- (void)setBackgroundImage:(id)arg1 forBarMetrics:(int)arg2;
- (void)setBackgroundImage:(id)arg1 forBarPosition:(int)arg2 barMetrics:(int)arg3;
- (void)setBarStyle:(int)arg1;
- (void)setBarTintColor:(id)arg1;
- (void)setBounds:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })arg1;
- (void)setButton:(int)arg1 enabled:(BOOL)arg2;
- (void)setCenter:(struct CGPoint { float x1; float x2; })arg1;
- (void)setDelegate:(id)arg1;
- (void)setForceFullHeightInLandscape:(BOOL)arg1;
- (void)setFrame:(struct CGRect { struct CGPoint { float x_1_1_1; float x_1_1_2; } x1; struct CGSize { float x_2_1_1; float x_2_1_2; } x2; })arg1;
- (void)setHidden:(BOOL)arg1;
- (void)setItems:(id)arg1 animated:(BOOL)arg2;
- (void)setItems:(id)arg1;
- (void)setLocked:(BOOL)arg1;
- (void)setNavigationItems:(id)arg1;
- (void)setNeedsLayout;
- (void)setPrompt:(id)arg1;
- (void)setRightMargin:(float)arg1;
- (void)setShadowImage:(id)arg1;
- (void)setTintColor:(id)arg1;
- (void)setTitleAutoresizesToFit:(BOOL)arg1;
- (void)setTitleTextAttributes:(id)arg1;
- (void)setTitleVerticalPositionAdjustment:(float)arg1 forBarMetrics:(int)arg2;
- (void)setTitleView:(id)arg1;
- (void)setTopItemAlpha:(float)arg1;
- (void)setTranslatesAutoresizingMaskIntoConstraints:(BOOL)arg1;
- (void)setTranslucent:(BOOL)arg1;
- (id)shadowImage;
- (void)showBackButton:(BOOL)arg1 animated:(BOOL)arg2;
- (void)showButtonsWithLeft:(id)arg1 right:(id)arg2 leftBack:(BOOL)arg3;
- (void)showButtonsWithLeftTitle:(id)arg1 rightTitle:(id)arg2 leftBack:(BOOL)arg3;
- (void)showButtonsWithLeftTitle:(id)arg1 rightTitle:(id)arg2;
- (void)showHideBackButtomAnimationDidStop:(id)arg1 finished:(id)arg2 context:(id)arg3;
- (void)showLeftButton:(id)arg1 withStyle:(int)arg2 rightButton:(id)arg3 withStyle:(int)arg4;
- (struct CGSize { float x1; float x2; })sizeThatFits:(struct CGSize { float x1; float x2; })arg1;
- (int)state;
- (void)tintColorDidChange;
- (BOOL)titleAutoresizesToFit;
- (id)titleTextAttributes;
- (float)titleVerticalPositionAdjustmentForBarMetrics:(int)arg1;
- (id)topItem;
- (float)topItemAlpha;
- (void)touchesBegan:(id)arg1 withEvent:(id)arg2;
- (void)touchesCancelled:(id)arg1 withEvent:(id)arg2;
- (void)touchesEnded:(id)arg1 withEvent:(id)arg2;
- (void)touchesMoved:(id)arg1 withEvent:(id)arg2;
- (void)updatePrompt;
- (void)willRemoveSubview:(id)arg1;

@end