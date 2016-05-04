//
//  GCDViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-6-28.
//
//

#import "GCDViewController.h"

@interface GCDViewController ()

@end

@implementation GCDViewController

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
	// Do any additional setup after loading the view.
    queue = dispatch_queue_create("creath quere", NULL);
    //[self runQuene];
    
    //[self ruaquenebing];
    
    [self ruaWaitDonede];
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void) dealloc
{
    dispatch_release(queue);  
    [super dealloc];
}

- (void) test001
{
   
    NSLog(@"---------------test001-------------");
    
    // sleep(13);
}

- (void) test002
{
     //sleep(5);
     NSLog(@"---------test002------------");
}

- (void) test003
{
    //sleep(1);
     NSLog(@"-------------test003---------------");
}

// 串行
- (void) runQuene
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
      
        [self test001];
        [self test002];
        [self test003];
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            NSLog(@"dispatch_get_main_queue");
            
        });
        
    });

}

- (void) ruaquenebing //并发
{
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        
        [self test001];
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            NSLog(@"dispatch_get_main_queue1");
            
        });
        
    });
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        
        [self test002];
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            NSLog(@"dispatch_get_main_queue2");
            
        });
        
    });
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        
        [self test003];
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            NSLog(@"dispatch_get_main_queue3");
            
        });
        
    });



}


- (void) ruaCreateQueue //串行
{
    dispatch_sync(queue, ^(void){
        
        [self test001];
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            NSLog(@"dispatch_get_main_queue 1");
            
        });
        
    });
    
    dispatch_sync(queue, ^(void){
        
        [self test002];
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            NSLog(@"dispatch_get_main_queue 2");
            
        });
        
    });
    
    dispatch_sync(queue, ^(void){
        
        [self test003];
        
        dispatch_async(dispatch_get_main_queue(), ^(void) {
            NSLog(@"dispatch_get_main_queue 3");
            
        });
        
    });

}





- (void) ruaWaitDone 
{
    dispatch_sync(queue, ^(void){
        
                
        for (int i = 0 ; i < 10000; i++)
        {
            NSLog(@"1");
        }
        
    });
    
    dispatch_sync(queue, ^(void){
        
        for (int i = 0 ; i < 2; i++)
        {
            NSLog(@"2");
        }
        
                
    });
    
    dispatch_sync(queue, ^(void){
        
       
        for (int i = 0 ; i < 10; i++)
        {
            NSLog(@"3");
        }
        
    });
    
}

- (void) ruaWaitDonede
{
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        
        for (int i = 0 ; i < 10000; i++)
        {
            NSLog(@"1");
        }

    });
    
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        for (int i = 0 ; i < 2; i++)
        {
            NSLog(@"2");
        }

               
    });

    
    dispatch_sync(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_LOW, 0), ^(void){
        for (int i = 0 ; i < 10; i++)
        {
            NSLog(@"3");
        }

               
    });
    
}


@end
