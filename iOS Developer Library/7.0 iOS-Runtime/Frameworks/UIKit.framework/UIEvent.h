/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/UIKit.framework/UIKit
 */

@interface UIEvent : NSObject {
    double _timestamp;
}

@property(readonly) int subtype;
@property(readonly) double timestamp;
@property(readonly) int type;

- (id)_allPhysicalButtons;
- (struct __GSEvent { }*)_gsEvent;
- (struct __IOHIDEvent { }*)_hidEvent;
- (id)_init;
- (id)_initWithEvent:(struct __GSEvent { }*)arg1 touches:(id)arg2;
- (BOOL)_isKeyDown;
- (id)_modifiedInput;
- (int)_modifierFlags;
- (int)_moveDirection;
- (id)_physicalButtonsForGestureRecognizer:(id)arg1;
- (id)_physicalButtonsForResponder:(id)arg1;
- (id)_physicalButtonsForWindow:(id)arg1;
- (id)_screen;
- (void)_sendEventToResponder:(id)arg1;
- (void)_setTimestamp:(double)arg1;
- (int)_shakeState;
- (id)_touchesForGestureRecognizer:(id)arg1;
- (id)_triggeringPhysicalButton;
- (id)_unmodifiedInput;
- (float)_wheelVelocity;
- (id)_windows;
- (id)allTouches;
- (BOOL)isKeyDown;
- (int)subtype;
- (double)timestamp;
- (id)touchesForGestureRecognizer:(id)arg1;
- (id)touchesForView:(id)arg1;
- (id)touchesForWindow:(id)arg1;
- (int)type;

@end