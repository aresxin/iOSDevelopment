//
//  CoreDataController.m
//  DevelopGuide_iOS
//
//  Created by clay on 12-8-23.
//
//

#import "CoreDataController.h"

#import "Teacher.h"
#import "Student.h"
#import "PreCusDataManager.h"

@interface CoreDataController ()
- (void) initTestData;
@end

@implementation CoreDataController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.navigationController.navigationBarHidden = YES;
    [self initTestData];
}


- (IBAction) selectAllDataOnMainThread:(id)sender
{
    // core data 多线程编程
    //NSRunLoop* runLoop = [NSRunLoop currentRunLoop];
    //sleep(10);
    
    // get kpsotre
    KPStore *storeMgr = [KPStore shareStore];
    
    //创建一个NSFetchRequest 通过老师名查出学生
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    
    //获得查询表
    NSEntityDescription *entity = [storeMgr entityForName:@"Teacher"];
    //设定数据排序规则
    NSSortDescriptor *sortDescriptor1 = [[NSSortDescriptor alloc] initWithKey:@"arge" ascending:YES];
    NSSortDescriptor *sortDescriptor2 = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES];
    NSArray *sortDescriptors = [[NSArray alloc] initWithObjects:sortDescriptor1, sortDescriptor2, nil];
    
    [fetchRequest setSortDescriptors:sortDescriptors];
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchBatchSize:20];
    
    if (selectArr != nil) {
        [selectArr release];
        selectArr = nil;
    }
    selectArr = [[storeMgr executeFetchRequestOnThread:fetchRequest
                                                 error:nil] retain];
    
    
   // isDone = YES;
    
    // 查询所有老师
    _textView.text = nil;
    for (int i = 0; i < [selectArr count]; i++)
    {
        Teacher *t = [selectArr objectAtIndex:i];
        NSLog(@"------teache student count is %d-------",[t.students count]);
        _textView.text = [_textView.text stringByAppendingFormat:@"\n%@-%d",t.name,[t.arge intValue]];
        
    }

    

}
- (IBAction) canelSelect:(id)sender
{
    isDone = YES;
    [cancelThread cancel];
    if (cancelThread != nil) {
        [cancelThread release];
        cancelThread = nil;
    }
}
- (IBAction) selectAllDataOnThread:(id)sender
{
    isDone = NO;
    //[NSThread detachNewThreadSelector:@selector(selectOnThread) toTarget:self withObject:nil];
    
    if ([cancelThread isExecuting]) {
        return;
    }
    if (cancelThread == nil)
    {
        cancelThread = [[NSThread alloc] initWithTarget:self selector:@selector(selectOnThread) object:nil];
        [cancelThread start];
    }
    else
    {
        [cancelThread  release];
        cancelThread = nil;
        cancelThread = [[NSThread alloc] initWithTarget:self selector:@selector(selectOnThread) object:nil];
        [cancelThread start];
    }

    
    while (isDone == NO)
    {
        NSLog(@"is child thread");
       [[NSRunLoop currentRunLoop] runMode:NSDefaultRunLoopMode beforeDate:[NSDate distantFuture]];
       
    }
    
    NSLog(@"-------------*****************select data on thread is***********----- %@",selectArr);
     _textView.text = nil;
    // 查询所有老师
    for (int i = 0; i < [selectArr count]; i++)
    {
        Teacher *t = [selectArr objectAtIndex:i];
        NSLog(@"------teache student count is %d-------",[t.students count]);
        _textView.text = [_textView.text stringByAppendingFormat:@"\n%@-%d",t.name,[t.arge intValue]];
        
    }

}

- (void) selectOnThread
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    
    // core data 多线程编程
    //NSRunLoop* runLoop = [NSRunLoop currentRunLoop];
    //sleep(5);
     
        // get kpsotre
    KPStore *storeMgr = [KPStore shareStore];
    
    //创建一个NSFetchRequest 通过老师名查出学生
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    
    //获得查询表
    NSEntityDescription *entity = [storeMgr entityForName:@"Teacher"];
    //设定数据排序规则
    NSSortDescriptor *sortDescriptor1 = [[NSSortDescriptor alloc] initWithKey:@"arge" ascending:YES];
    NSSortDescriptor *sortDescriptor2 = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES];
    NSArray *sortDescriptors = [[NSArray alloc] initWithObjects:sortDescriptor1, sortDescriptor2, nil];
    
    [fetchRequest setSortDescriptors:sortDescriptors];
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchBatchSize:20];
    
    if (selectArr != nil) {
        [selectArr release];
        selectArr = nil;
    }
    selectArr = [[storeMgr executeFetchRequestOnThread:fetchRequest
                                               error:nil] retain];
    
    
    isDone = YES;
    
    
        
    [pool release];
    
   // [runLoop run];

}

- (void) changeStatue
{
    isDone = YES;
}

- (IBAction) insertDataOnThread:(id)sender
{
    if ([childThread isExecuting]) {
        return;
    }
    if (childThread == nil)
    {
        childThread = [[NSThread alloc] initWithTarget:self selector:@selector(run) object:nil];
        [childThread start];
    }
    else
    {
        [childThread  release];
        childThread = nil;
        childThread = [[NSThread alloc] initWithTarget:self selector:@selector(run) object:nil];
        [childThread start];
    }
    
}
// 在子线程中插入数据
- (void) run
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    // get kpsotre
    KPStore *storeMgr = [KPStore shareStore];
    
    Teacher *_teacher = (Teacher *)[storeMgr insertNewObjectForEntityForNameOnThread:@"Teacher"];
    
    _teacher.name = @"new teacher";
    _teacher.arge = [NSNumber numberWithInt:60];
    
    [storeMgr saveContextOnThread];
    
    [pool release];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void) initTestData
{
    // get kpsotre
    KPStore *storeMgr = [KPStore shareStore];
    storeMgr.delegate = self;
    /*
     core data 插入相同的数据，不重复添加
     */
    // 插入几条teacher数据
    for (int i = 1; i < 6; i++)
    {
        Teacher *_teacher = (Teacher *)[storeMgr insertNewObjectForEntityForName:@"Teacher"];
        NSString *teacherName = [NSString stringWithFormat:@"teacher-%d",i];
        _teacher.name = teacherName;
        _teacher.arge = [NSNumber numberWithInt:(i + 25)];
    }
    
    
    // 存储数据库
    /*
     managedObjectContext操作数据后，需要写入数据库
     [managedObjectContext save:&error]
     */
    [storeMgr saveContext];
}

- (IBAction) getAllTeachers:(id)sender
{
    // get kpsotre
    KPStore *storeMgr = [KPStore shareStore];
    
    // 查询所有老师
    //创建一个NSFetchRequest
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    //获得查询表
    NSEntityDescription *entity = [storeMgr entityForName:@"Teacher"];
    //设定数据排序规则
    NSSortDescriptor *sortDescriptor1 = [[NSSortDescriptor alloc] initWithKey:@"arge" ascending:YES];
    NSSortDescriptor *sortDescriptor2 = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES];
    NSArray *sortDescriptors = [[NSArray alloc] initWithObjects:sortDescriptor1, sortDescriptor2, nil];
    [fetchRequest setSortDescriptors:sortDescriptors];
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchBatchSize:20];
    
     NSArray *objects = [storeMgr executeFetchRequest:fetchRequest
                                                error:nil];
    
    
    //向数据库中插入学生
    Student *_stu = (Student *)[storeMgr insertNewObjectForEntityForName:@"Student"];
    _stu.name = [NSString stringWithFormat:@"student/%d",0];
    _stu.number = [NSNumber numberWithInt:(0 + 100)];
    
    Student *_stu1 = (Student *)[storeMgr insertNewObjectForEntityForName:@"Student"];
    _stu1.name = [NSString stringWithFormat:@"student/%d",1];
    _stu1.number = [NSNumber numberWithInt:(1 + 100)];
    
    _textView.text = nil;
    //绑定老师于学生的关系
    for (int i = 1; i < [objects count]; i++)
    {
        Teacher *t = [objects objectAtIndex:i];
        
        _textView.text = [_textView.text stringByAppendingFormat:@"\n%@-%d",t.name,[t.arge intValue]];
        
        t.name = @"change";
        [[KPStore shareStore] saveContext];
        
        //绑定老师于学生的关系
        [_stu addTeachersObject:t];
        [_stu1 addTeachersObject:t];
    }

}
// 通过教师名查询学生
- (IBAction) getStudentByTeacher:(id)sender
{
    // get kpsotre
    KPStore *storeMgr = [KPStore shareStore];
    
    //创建一个NSFetchRequest 通过老师名查出学生
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    
    //获得查询表
    NSEntityDescription *entity = [storeMgr entityForName:@"Teacher"];
    //设定数据排序规则
    NSSortDescriptor *sortDescriptor1 = [[NSSortDescriptor alloc] initWithKey:@"arge" ascending:YES];
    NSSortDescriptor *sortDescriptor2 = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES];
    NSArray *sortDescriptors = [[NSArray alloc] initWithObjects:sortDescriptor1, sortDescriptor2, nil];

    [fetchRequest setSortDescriptors:sortDescriptors];
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchBatchSize:20];
    // 根据年龄查询老师
    NSInteger arge_1 = [_input.text intValue];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"arge = %d",arge_1];
    [fetchRequest setPredicate:predicate];
    
    NSArray *objects = [storeMgr executeFetchRequest:fetchRequest
                                               error:nil];
    NSLog(@"%@",objects);
    // 查询跟老师有关系的所有学生
    _textView.text = nil;
    for (int i = 0; i < [objects count]; i++)
    {
        Teacher *t = [objects objectAtIndex:i];
        NSLog(@"------teache student count is %d-------",[t.students count]);
        // 查询跟老师有关系的所有学生
        for (Student *st in t.students)
        {
            NSLog(@"student");
            
            _textView.text = [_textView.text stringByAppendingFormat:@"\n%@-%d",st.name,[st.number intValue]];
        }
    }
    
    
    //创建一个NSFetchRequest 查询所有学生
    NSFetchRequest *fetchRequest1 = [[NSFetchRequest alloc] init];
    
    //获得查询表
    NSEntityDescription *entity1 = [storeMgr entityForName:@"Student"];
    //设定数据排序规则
    NSSortDescriptor *sortDescriptor22 = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES];
    NSArray *sortDescriptors1 = [[NSArray alloc] initWithObjects:sortDescriptor22, nil];
    
    [fetchRequest1 setSortDescriptors:sortDescriptors1];
    [fetchRequest1 setEntity:entity1];
    [fetchRequest1 setFetchBatchSize:20];

    NSArray *objects1 = [storeMgr executeFetchRequest:fetchRequest1
                                               error:nil];

    NSLog(@"student %@",objects1);
}

#pragma mark KPStoreDelegate
- (void) didMergeChangesFromContextDidSaveNotification
{
    NSLog(@"start");
    // waitUntilDone 为YES阻塞其它线程，知道这个方法执行完毕，为NO，不阻塞其他线程
    [self performSelectorOnMainThread:@selector(updateUI) withObject:nil waitUntilDone:YES];
    NSLog(@"end");
   

}

- (void) updateUI
{
    NSLog(@"call back");
    //sleep(5);
    // get kpsotre
    KPStore *storeMgr = [KPStore shareStore];
    // 查询所有老师
    //创建一个NSFetchRequest
    NSFetchRequest *fetchRequest = [[NSFetchRequest alloc] init];
    //获得查询表
    NSEntityDescription *entity = [storeMgr entityForName:@"Teacher"];
    //设定数据排序规则
    NSSortDescriptor *sortDescriptor1 = [[NSSortDescriptor alloc] initWithKey:@"arge" ascending:YES];
    NSSortDescriptor *sortDescriptor2 = [[NSSortDescriptor alloc] initWithKey:@"name" ascending:YES];
    NSArray *sortDescriptors = [[NSArray alloc] initWithObjects:sortDescriptor1, sortDescriptor2, nil];
    [fetchRequest setSortDescriptors:sortDescriptors];
    [fetchRequest setEntity:entity];
    [fetchRequest setFetchBatchSize:20];
    
    NSArray *objects = [storeMgr executeFetchRequest:fetchRequest
                                               error:nil];
    _textView.text = nil;
    // 查询所有老师
    for (int i = 0; i < [objects count]; i++)
    {
        Teacher *t = [objects objectAtIndex:i];
        NSLog(@"------teache student count is %d-------",[t.students count]);
        _textView.text = [_textView.text stringByAppendingFormat:@"\n%@-%d",t.name,[t.arge intValue]];
        
    }

}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}
@end
