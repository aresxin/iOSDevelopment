//
//  GifViewController.h
//  DevelopGuide_iOS
//
//  Created by lu matthew on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

/*
http://www.cocoachina.com/bbs/read.php?tid=98992 (源码地址)
GIF生成开源库Third Part
GIF生成(开源GIF库),播放(webView),保存(临时文件夹)   


1.配置调用开源合成gif类库
2.图片的居中裁剪(加入未使用)
3.图片尺寸的调节
4.用UIWebView来播放gif
5.保存到临时文件夹

注意事项:
配置gif的开源类库:1.如图  

2.头文件引入(见程序)

PS:由于gif不是矢量图,因此用UIWebView的播放gif的时候必须生成与UIWebView一样的尺寸,否则形状会很诡异
图片:截图1.png 
Build Settings 设置
Other Linker flags  -all_load -Objc
*/

#import <UIKit/UIKit.h>
#import "FreeGifLoader.h"

@interface GifViewController : UIViewController
@property(nonatomic, retain) NSMutableArray *imageArray;
@property(nonatomic, retain) NSMutableArray *delayArray;

- (UIImage *) scaleFromImage: (UIImage *) image 
                      toSize: (CGSize) size;//图片等比例裁剪函数
- (void) saveGif;//保存gif
- (void) showGif;//显示gif

@end
