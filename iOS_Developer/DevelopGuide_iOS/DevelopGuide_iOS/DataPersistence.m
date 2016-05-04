//
//  DataPersistence.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "DataPersistence.h"
#import "PeopleObject.h"

@implementation DataPersistence

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark -
#pragma mark action 

- (IBAction)actionArchiver:(id)sender
{
    // 将对象归档并存入NSUserDefault
    NSMutableArray *arr = [NSMutableArray array];
    PeopleObject *p1 = [[[PeopleObject alloc] initWithName:@"a" Arge:24] autorelease];
    PeopleObject *p2 = [[[PeopleObject alloc] initWithName:@"b" Arge:34] autorelease];
    PeopleObject *p3 = [[[PeopleObject alloc] initWithName:@"c" Arge:64] autorelease];
    
    [arr addObject:p1];
    [arr addObject:p2];
    [arr addObject:p3];
    
    // 归档成NSData 归档arr时递归将arr中的数据进行归档
    NSData *pData = [NSKeyedArchiver archivedDataWithRootObject:arr];  
    
    // 将pData存入NSUserDefault
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults]; 
    [ud setObject:pData forKey:@"myData"];

}

- (IBAction)actionUnArchiver:(id)sender
{
    textView_.text = nil;
    // 从NSUserDefault中取出归档数据
    NSUserDefaults *ud = [NSUserDefaults standardUserDefaults]; 
    NSData *data = [ud objectForKey:@"myData"];
    NSLog(@"data is %@",data);
    // 从NSData中解档数据
    NSMutableArray *arr = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    
    // 显示解档数据
    for (int i = 0; i<[arr count]; i++) {
        PeopleObject *p = [arr objectAtIndex:i];
        textView_.text = [textView_.text stringByAppendingFormat:@"\n people %d name is %@ arge is %d \n",
                          i, p.name_, p.arge_];
    }
}

@end
