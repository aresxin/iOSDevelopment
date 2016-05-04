//
//  ViewController.m
//  CoreData
//
//  Created by yangjinxin on 13-7-30.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "ViewController.h"
#import "TeacherData.h"
#import "XXStore.h"
#import "StudentData.h"
#import "DataManager.h"


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


// 主线程，子线程同时插入数据，main moc 合并到数据库
- (IBAction) actionTest1:(id)sender
{
    TeacherData *t = [[TeacherData alloc] init];
    t.tId          = [NSNumber numberWithInt:32];
    t.tName        = @"tNamae22";
    [t insertToDB];
    
  
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        
        NSLog(@"therad 1 student");
        StudentData *t = [[StudentData alloc] init];
        t.sId          = [NSNumber numberWithInt:32];
        t.sName        = @"sNamae22";
        [t insertToDB];
        
        
        for (int i = 0; i < 10; i++)
        {
            NSLog(@"therad 1 studen ");
            StudentData *t = [[StudentData alloc] init];
            t.sId          = [NSNumber numberWithInt:i + 1000];
            t.sName        = [NSString stringWithFormat:@"%dStuden",i+ 100];
            [t insertToDB];
        }
        
        
    });
    

    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        
        NSLog(@"therad 1");
        TeacherData *t = [[TeacherData alloc] init];
        t.tId          = [NSNumber numberWithInt:32];
        t.tName        = @"tNamae22";
        [t insertToDB];
        
        
        for (int i = 0; i < 10; i++)
        {
            NSLog(@"therad 1");
            TeacherData *t = [[TeacherData alloc] init];
            t.tId          = [NSNumber numberWithInt:i + 1000];
            t.tName        = [NSString stringWithFormat:@"%dchild",i+ 100];
            [t insertToDB];
        }
        
        for (int i = 0; i < 10; i++)
        {
            NSLog(@"therad 1 studen ");
            StudentData *t = [[StudentData alloc] init];
            t.sId          = [NSNumber numberWithInt:i + 1000];
            t.sName        = [NSString stringWithFormat:@"%dStuden",i+ 100];
            [t insertToDB];
        }
        


        
    });
    
    
    for (int i = 0; i < 10; i++)
    {
        NSLog(@"main therad ");
        TeacherData *t = [[TeacherData alloc] init];
        t.tId          = [NSNumber numberWithInt:i + 100];
        t.tName        = [NSString stringWithFormat:@"%dmain",i+ 100];
        [t insertToDB];
    }
    
    
    NSMutableArray *arr = [NSMutableArray array];
    for (int i = 0; i < 10; i++)
    {
        NSLog(@"multi ------- ");
        StudentData *t = [[StudentData alloc] init];
        t.sId          = [NSNumber numberWithInt:i + 2000];
        t.sName        = [NSString stringWithFormat:@"%dMStuden",i+ 2000];
        [arr addObject:t];
    }
    [[DataManager sharedInstance] insertMultiObject:arr
                                             entity:@"Student"];
    
    NSMutableArray *arr3 = [NSMutableArray array];
    for (int i = 0; i < 10; i++)
    {
        NSLog(@"asyncInsertMultiObject ------- ");
        StudentData *t = [[StudentData alloc] init];
        t.sId          = [NSNumber numberWithInt:i + 2000];
        t.sName        = [NSString stringWithFormat:@"%dasyncInsertStuden",i+ 2000];
        [arr3 addObject:t];
    }
    [[DataManager sharedInstance] asyncInsertMultiObject:arr3
                                                  entity:@"Student"];
    
    

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        [[DataManager sharedInstance] insertMultiObject:arr
                                                 entity:@"Student"];
        
        
        NSMutableArray *arra = [NSMutableArray array];
        for (int i = 0; i < 10; i++)
        {
            NSLog(@"multi T------- ");
            TeacherData *t = [[TeacherData alloc] init];
            t.tId          = [NSNumber numberWithInt:i + 2000];
            t.tName        = [NSString stringWithFormat:@"%dMT",i+ 2000];
            [arra addObject:t];
        }
        
        [[DataManager sharedInstance] insertMultiObject:arra
                                                 entity:@"Teacher"];

    });

    
    
    for (int i = 0; i < 10; i++)
    {
        NSLog(@"therad 1 studen ");
        StudentData *t = [[StudentData alloc] init];
        t.sId          = [NSNumber numberWithInt:i + 1000];
        t.sName        = [NSString stringWithFormat:@"%dStuden",i+ 100];
        [t insertToDB];
    }
    

  
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
         NSLog(@"therad 2");
        TeacherData *t = [[TeacherData alloc] init];
        t.tId          = [NSNumber numberWithInt:33];
        t.tName        = @"tNamae33";
        [t insertToDB];
       
       
        for (int i = 0; i < 10; i++)
        {
            NSLog(@"therad 2");
           TeacherData *t = [[TeacherData alloc] init];
            t.tId          = [NSNumber numberWithInt:i + 10000];
           t.tName        = [NSString stringWithFormat:@"%dchild2",i+ 10000];
           [t insertToDB];
       }

       
   });
    
    
    
    
}

// 主线程插入数据，子线程查询数据
- (IBAction) actionTest2:(id)sender
{
     NSLog(@"%s", __FUNCTION__);
    
    NSMutableArray *arr3 = [NSMutableArray array];
    for (int i = 0; i < 10; i++)
    {
        NSLog(@"asyncInsertMultiObject ------- ");
        StudentData *t = [[StudentData alloc] init];
        t.sId          = [NSNumber numberWithInt:i + 2000];
        t.sName        = [NSString stringWithFormat:@"%dasyncInsertStuden",i+ 2000];
        [arr3 addObject:t];
    }
    
    
    for (int i = 0; i < 10; i++)
    {
        NSLog(@"main therad ");
        TeacherData *t = [[TeacherData alloc] init];
        t.tId          = [NSNumber numberWithInt:i + 100];
        t.tName        = [NSString stringWithFormat:@"%dmain",i+ 100];
        [t insertToDB];
    }

    
    [[DataManager sharedInstance] asyncInsertMultiObject:arr3
                                                  entity:@"Student"];

    
    [[DataManager sharedInstance] asyncFetchRequestEntiry:@"Student"
                                             fetchRequest:nil
                                        CompletionHandler:^(NSArray *results){
                                            NSLog(@"results is ------%@----%d",results,[results count]);
                                        }];
    
    NSArray *arrr = [[DataManager sharedInstance] fetchRequestEntiry:@"Student"
                                                        fetchRequest:nil];
    
    NSLog(@"arrr is ------%@----%d",arrr,[arrr count]);
}

// 子线程插入数据，主线程查询数据
- (IBAction) actionTest3:(id)sender
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        NSLog(@"therad 2");
        TeacherData *t = [[TeacherData alloc] init];
        t.tId          = [NSNumber numberWithInt:33];
        t.tName        = @"tNamae33";
        [t saveToDB];
        
        
        for (int i = 0; i < 10; i++)
        {
            NSLog(@"therad 2");
            TeacherData *t = [[TeacherData alloc] init];
            t.tId          = [NSNumber numberWithInt:i + 10000];
            t.tName        = [NSString stringWithFormat:@"%dchild2",i+ 10000];
            [t saveToDB];
        }
        
        
    });
    
    TeacherData *t = [[TeacherData alloc] init];
    t.tId          = [NSNumber numberWithInt:33];
    t.tName        = @"tNamae33";
    [t saveToDB];

    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^(void){
        NSLog(@"therad 2");
               
        
        for (int i = 0; i < 10; i++)
        {
            NSLog(@"therad 2");
            TeacherData *t = [[TeacherData alloc] init];
            t.tId          = [NSNumber numberWithInt:i + 10000];
            t.tName        = [NSString stringWithFormat:@"%dchild2",i+ 10000];
            [t saveToDB];
        }
        
        
    });

}
@end
