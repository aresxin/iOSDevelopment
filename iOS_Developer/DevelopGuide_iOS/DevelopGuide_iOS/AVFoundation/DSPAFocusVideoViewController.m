//
//  DSPAFocusVideoViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-8-13.
//
//

#import "DSPAFocusVideoViewController.h"
#import "DSPAVideoPlayView.h"
#include <sys/sysctl.h>
#include <mach/mach.h>



@interface DSPAFocusVideoViewController ()
- (void) initFocusVideosView;
@end

@implementation DSPAFocusVideoViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (id) initFocusVideos:(NSArray *)videoList frame:(CGRect)rect
{
    self = [super init];
    if (self) {
        // Custom initialization
        self.view.frame = rect;
        videoList_      = videoList;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // 1.0
    [self initFocusVideosView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void) initFocusVideosView
{
    CGRect rect                             = self.view.bounds;
    scrollV_.frame                          = rect;
    scrollV_.showsHorizontalScrollIndicator = NO;
    scrollV_.showsVerticalScrollIndicator   = NO;
    scrollV_.alwaysBounceHorizontal         = YES;
    scrollV_.alwaysBounceVertical           = NO;
    scrollV_.scrollEnabled                  = YES;
    scrollV_.pagingEnabled                  = YES;
    
    
//    if (videoList_ == nil || [videoList_ count] == 0)
//    {
//        return;
//    }
    
    //TODO: 循环添加
    NSString *videoURLStr = [[NSBundle mainBundle] pathForResource:@"Movie" ofType:@"m4v"];
    NSURL    *videoURL    = [NSURL fileURLWithPath:videoURLStr];
    
    scrollV_.contentSize                    = CGSizeMake(2000, scrollV_.frame.size.height);
    for (int i = 0; i < 10; i++)
    {
        CGRect rect = CGRectMake(i * 120, 80, 120, 60);
        DSPAVideoPlayView *playView = [[DSPAVideoPlayView alloc] initWithFrame:rect
                                                                  withVideoURL:videoURL
                                                                       playNow:NO];
        
        [scrollV_ addSubview:playView];
        [playView release];
        
       
        
    }
    
    NSLog(@"memory is %f",[self availableMemory]);
    
}

- (double)availableMemory {
	vm_statistics_data_t vmStats;
	mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
	kern_return_t kernReturn = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmStats, &infoCount);
	
	if(kernReturn != KERN_SUCCESS) {
		return NSNotFound;
	}
	
	return ((vm_page_size * vmStats.free_count) / 1024.0) / 1024.0;
}


@end
