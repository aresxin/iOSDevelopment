//
//  CoreDataController.h
//  DevelopGuide_iOS
//
//  Created by clay on 12-8-23.
//
//

#import <UIKit/UIKit.h>
#import "KPStore.h"
@interface CoreDataController : UIViewController <KPStoreDelegate,UITextFieldDelegate>{
    IBOutlet  UIButton  *getTeacher;
    IBOutlet  UITextView *_textView;
    IBOutlet  UIButton   *_button;
    IBOutlet  UITextField          *_input;
    NSThread             *childThread;
    NSArray              *selectArr;
    BOOL                  isDone;
    NSThread             *cancelThread;
}
- (IBAction) getAllTeachers:(id)sender;
- (IBAction) getStudentByTeacher:(id)sender;
- (IBAction) insertDataOnThread:(id)sender;
- (IBAction) selectAllDataOnThread:(id)sender;
@end
