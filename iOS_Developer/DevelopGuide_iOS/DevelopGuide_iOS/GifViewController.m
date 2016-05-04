//
//  GifViewController.m
//  DevelopGuide_iOS
//
//  Created by lu matthew on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "GifViewController.h"
#import "FreeGifMaker.h"
#import "ANGifBitmap.h"
#import "ANGifEncoder.h"
#import "ANImageBitmapRep.h"

@implementation GifViewController
@synthesize imageArray, delayArray;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void) dealloc
{
    imageArray = nil;[imageArray release];
    delayArray = nil;[delayArray release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle
// 缓存图片路径
#define FD_IMAGE_PATH(file) [NSString stringWithFormat:@"%@/Documents/image/%@",NSHomeDirectory(),file]

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    imageArray = [[NSMutableArray alloc] init];//gif的原始图片
    delayArray = [[NSMutableArray alloc] init];//gif的播放时间间隔
    int n;
    for (n = 1; n < 4; n ++) 
    {
        UIImage  *faceImage  = nil;
        NSString *pathBuffer = [NSString stringWithFormat:@"gif%d.png", n];
        //faceImage = [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:pathBuffer 
           //                                                                          ofType:@"png"]];
        faceImage = [UIImage imageNamed:pathBuffer];
        UIImageWriteToSavedPhotosAlbum(faceImage, nil, nil, nil);
        CGSize size1 = CGSizeMake(320, 320);//图片尺寸
        UIImage *newImage = [self scaleFromImage:faceImage //调节图片尺寸的函数
                                          toSize:size1];
        UIImageWriteToSavedPhotosAlbum(newImage, nil, nil, nil);
        //注意:本程序的逻辑是先把图片保存到本地的临时文件夹,再从临时文件夹里取出,进行合成gif
        //定义图片文件名
        NSString *gifSaveString = [NSString stringWithFormat:@"%d.png",n];
        //得到想要保存的图片
        NSData  *imageData1 = UIImagePNGRepresentation(newImage);
        //保存到缓存文件夹
        [imageData1 writeToFile:FD_IMAGE_PATH(gifSaveString) 
                     atomically:YES];
        
        UIImage *image = [UIImage imageWithContentsOfFile:FD_IMAGE_PATH(gifSaveString)];//从指定索引插入元素
        [imageArray insertObject:image
                         atIndex:n - 1];//是插入到指定的索引的前
        
        NSNumber *number = [NSNumber numberWithFloat:1.5f];//数字转换成浮点数(必须转换成浮点数才能加到数组里)
        [delayArray insertObject:number
                         atIndex:n - 1];
    }
    [self saveGif];
    [self showGif];

}

- (UIImage *) scaleFromImage: (UIImage *) image 
                      toSize: (CGSize) size
{
    UIGraphicsBeginImageContext(size);
    [image drawInRect:CGRectMake(0, 0, size.width, size.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

- (void) saveGif
{
    NSString *gifName = [NSString stringWithFormat:@"temp.gif"];
    
#define USE_GIF_MAKER
#ifdef USE_GIF_MAKER
    FreeGifMaker *maker = [FreeGifMaker new];
    [maker setGifFrame:(NSArray *)imageArray
                 delay:(NSArray *)delayArray];
    [maker setGifFileName:gifName];// 设置gif文件名称
    [maker setGifFileDirectory:[NSString stringWithFormat:@"%@/Documents/image/",NSHomeDirectory()]];// 设置保存位置文件夹
    [maker saveAnimatedGif];// 保存gif文件
    [maker release];
#endif
}

- (void) showGif
{
    
    NSString *gifString = [NSString stringWithFormat:@"%@/Documents/image/temp.gif",NSHomeDirectory()];
    NSData *gif  = [NSData dataWithContentsOfFile:gifString];
    UIWebView *gifWebView;
    gifWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 40, 320, 320)];
    [gifWebView loadData:gif
                MIMEType:@"image/gif"
        textEncodingName:nil
                 baseURL:nil];
    gifWebView.scalesPageToFit = NO;
    gifWebView.opaque = 0;
    [self.view addSubview:gifWebView];
    [gifWebView release];
    
    [imageArray removeAllObjects];
    [delayArray removeAllObjects];//移除数组所有元素
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

@end
