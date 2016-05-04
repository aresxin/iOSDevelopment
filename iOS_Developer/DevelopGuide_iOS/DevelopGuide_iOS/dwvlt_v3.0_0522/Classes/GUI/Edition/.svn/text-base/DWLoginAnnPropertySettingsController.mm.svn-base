//
//  DWLoginAnnPropertySettingsController.m
//  DWViewer
//
//  Created by panpan wang on 12-3-27.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#import "DWLoginAnnPropertySettingsController.h"
#import "Utility.h"
#import "DWViewerGUIConst.h"

@interface DWResistAnnotationManager (FileAccess)

+ (NSString*)getLocalLoginAnntationFilePath;
+ (BOOL)	 fileExistsAtPath:(NSString*)path;
+ (UIImage*) createAnnotationImage:(MPCObject*)anncase 
						  andIndex:(int)nth 
					withImageWidth:(int)imgWidth;
+ (BOOL)     resistAnnotation:(MPCObject*)anncase 
					andObject:(MPCObject*) obj;

@end

@implementation DWResistAnnotationManager (FileAccess)

+ (NSString*) getLocalLoginAnntationFilePath
{
	NSArray  *paths		= NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *document	= [paths objectAtIndex:0]; 
	NSString *folder	= [document stringByAppendingPathComponent:LOCAL_RESIST_ANNOTATION_DIR];
	NSString *path		= [folder stringByAppendingPathComponent:LOCAL_RESIST_ANNOTATION_FILE];
	
	NSFileManager *fileManager = [NSFileManager defaultManager];
	if ([fileManager fileExistsAtPath:folder] == NO) 
	{
		[fileManager createDirectoryAtPath:folder 
			   withIntermediateDirectories:YES 
								attributes:nil 
									 error:nil];
	}
	
	return path;
}

+ (BOOL)	 fileExistsAtPath:(NSString*)path
{
	if (path == nil)
	{
		return NO;
	}
	
	NSFileManager *fileManager = [NSFileManager defaultManager];
	if ([fileManager fileExistsAtPath:path] == NO) 
	{
		return NO;
	}
	else
	{
		return YES;
	}
}


/*
+ (NSString*) getLocalLoginAnntationFilePath:(BOOL)create
{
	NSArray		*paths		= NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString	*document	= [paths objectAtIndex:0]; 
	NSString	*folder		= [document stringByAppendingPathComponent:LOCAL_RESIST_ANNOTATION_DIR];
	NSString	*path		= [folder stringByAppendingPathComponent:LOCAL_RESIST_ANNOTATION_FILE];
	
	NSFileManager *fileManager = [NSFileManager defaultManager];
	if ([fileManager fileExistsAtPath:path] == NO) 
	{
		if (create == YES)
		{
			BOOL res = [fileManager createDirectoryAtPath:folder 
							  withIntermediateDirectories:YES 
											   attributes:nil 
													error:nil];
			
			if (res == YES)
			{
				return path;
			}
			else
			{
				return nil;
			}
		}
	}
	else
	{
		return path;
	}
}
*/ 

+ (UIImage*) createAnnotationImage:(MPCObject*)anncase
						  andIndex:(int)nth 
					withImageWidth:(int)imgWidth
{
    if (anncase == NULL || nth < 0) 
	{
		return nil;
	}
    
    if (anncase->GetClassID() != OT_ANNOTATION_CASE) 
	{
        return nil;
    }
    
    HRESULT hres = 0;
    MPCSession* session = anncase->GetSession();
	if (session == NULL) 
	{
		return nil;
	}
    
    MPCObject* obj = anncase->GetNthChild(nth);
    if (obj == NULL) 
	{
		return nil;
	}
    
    int pixelSize = 64;
	if (imgWidth != 0)
	{
		pixelSize = imgWidth;
	}
	
    MP_Dim objdim = {0, 0};
    MP_AValue avdim;
    avdim.asize = sizeof(objdim);
    avdim.atype = MP_A_DIM;
    avdim.adata = &objdim;
    
    hres = obj->GetAttribute("#dim", &avdim);
    if (hres != MP_NOERROR) 
		return nil;
    
    if (objdim.cx == 0 || objdim.cy == 0) 
		return nil;
	
    MP_Pos pos = {0, 0};
	
    const float margin = 0.05f;
    int w = (int)(objdim.cx * (1.0f + margin * 2));
    int h = (int)(objdim.cy * (1.0f + margin * 2));
    float size = (w >= h) ? w : h;
    if (w > h) 
	{
        pos.x += w * 0.05f;
        pos.y += (w - objdim.cy) / 2.0f;
    } 
	else 
	{
        pos.y += h * 0.05f;
        pos.x += (h - objdim.cx) / 2.0f;
    }
    
    float floatdpi = pixelSize / (size / 2540.0f);
    
    MPCObject* basicpage = session->CreateScratchMPCObject(CLSID_BASICPAGE); 
    if (basicpage == NULL) 
	{
		return nil;
	}
    
    MPCObject* copyobj = obj->Duplicate(); 
    if (copyobj == NULL) 
	{
        basicpage->Destroy();
        return nil;
    }
	
    MP_Attrs attrs[] = 
	{
        {(MP_AName*)"#pos", {sizeof(MP_Pos), MP_A_POS, &pos} },
        {0},
    };
	
    hres = basicpage->LinkChild(copyobj, 0, &attrs[0]);
    if (hres != MP_NOERROR) 
	{
        basicpage->Destroy();
        copyobj->Destroy();
        return nil;
    }
	
	copyobj->Destroy();
    
    int width = pixelSize;
    int height = pixelSize;
    const int BYTES_PER_PIXEL = 4; // RGBA format
	
	/*
    size_t imageBytes = width * BYTES_PER_PIXEL * height;
    void* buff = malloc(imageBytes); 
    if (buff == NULL) {
        basicpage->Destroy();
        return nil;
    }
	
    memset(buff, 0x00, imageBytes);
	 */ 
	
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    size_t bitsPerComponent = 8;
    size_t bytesPerRow = width * BYTES_PER_PIXEL;
	
	/*
	 * `data', if non-NULL, points to a block of memory at least `bytesPerRow * height' bytes. 
	 * If `data' is NULL, the data for context is allocated automatically and freed when the context is deallocated.
	 */
    CGContextRef ctx = CGBitmapContextCreate(/*buff*/ NULL, width, height, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast);
    if (ctx == NULL) 
	{
        CGColorSpaceRelease(colorSpace);
		
		/*
        free(buff);
		 */
		
        basicpage->Destroy();
        return nil;
    }
	
    CGContextConcatCTM(ctx, CGAffineTransformMake(1, 0, 0, -1, 0, height));
    
    const int resolution = 75;
    HDC_XD hdc = MPCCreateDCPixel(session, 0, 0, resolution, &hres);
    if (hdc == NULL) 
	{
        CGContextRelease(ctx);
        CGColorSpaceRelease(colorSpace);
		
		/*
        free(buff);
		 */
		
        basicpage->Destroy();
        return nil;
    }
    
    hdc->offscreen->SetMemoryDC(ctx);
    hdc->bridge->SetOffScreen(hdc->offscreen);
    
    MP_Dim dim = {0, 0};
    MP_Canvas* pageCanvas = MPCreatePRTCanvasFloatDPI(session, hdc, floatdpi, dim, &hres);
    if (pageCanvas == NULL) 
	{
        CGContextRelease(ctx);
        CGColorSpaceRelease(colorSpace);
		
		/*
        free(buff);
		 */
		
        basicpage->Destroy();
        return nil;        
    }
	
    MP_Pos offset = {0, 0};
    pageCanvas->MoveOrigin(offset);
    
    MPCMediaAdv* mediaadv = (MPCMediaAdv*)basicpage->GetInterface(IID_MPCMediaAdv);
    mediaadv->OnDraw(pageCanvas, NULL);
	
    CGImageRef image = CGBitmapContextCreateImage(ctx);
    UIImage* uiimage = [UIImage imageWithCGImage:image];
	
    basicpage->Destroy();
    pageCanvas->Destroy();
    hdc->bridge = NULL;
    MPCDeleteDC(hdc);
    
    CGImageRelease(image);
    CGContextRelease(ctx);
    CGColorSpaceRelease(colorSpace);
	
	/*
    free(buff);
	 */
    
    return uiimage;
}

+ (BOOL)     resistAnnotation:(MPCObject*)anncase andObject:(MPCObject*)obj
{
    if (anncase == NULL || obj == NULL) 
	{
        return NO;
    }
    
    MPCObject* copyann = obj->Duplicate();
    if (copyann == NULL) 
	{
        return NO;
    }
	
    if (anncase->LinkChild(copyann, -1) != MP_NOERROR) 
	{
        copyann->Destroy();
        return NO;
    }
    
    MP_Integer nth = anncase->GetChildPosition(copyann);
    if (nth < 0)
	{
		copyann->Destroy();
        return NO;
    }
	
	copyann->Destroy();
	
    UIImage* image = [self createAnnotationImage:anncase 
										andIndex:nth 
								  withImageWidth:0];
    if (image == nil)
	{
        return NO;
    }
    
    NSData* data = UIImagePNGRepresentation(image);
    if (data == NULL) 
	{
        return NO;
    }
	
    MP_AValue avimage;
    avimage.asize = [data length];
    avimage.atype = MP_A_OCTS;
    avimage.adata = (void*)[data bytes];
    
    if (anncase->SetPartAttribute(nth, ANAME_IMAGE, &avimage) != MP_NOERROR) 
	{
        return NO;
    }
    
    return YES;
}

@end

@implementation DWResistAnnotationManager

+ (int)      getResistAnnotationCount
{
	NSString* filePath = [self getLocalLoginAnntationFilePath];
	if ([self fileExistsAtPath:filePath] == NO)
	{
		return 0;
	}
	
	MPCSession* session = MPCCreateMPCSession();
	if (session == NULL)
	{
        return 0;
    }
	
	HRESULT hres = 0;
	MPCObject* anncase = session->OpenFile([filePath UTF8String]);
    if (anncase == NULL) 
	{
        return 0;
    }
	
	int count = anncase->GetNumberOfChildren();
	
	session->CloseFile(anncase, 0);
	MPCDestroyMPCSession(session);
	
	return count;
}

+ (NSArray*) getResistAnnotationImageListWithImageWidth:(int)width
{
	NSString* filePath = [self getLocalLoginAnntationFilePath];
	if ([self fileExistsAtPath:filePath] == NO)
	{
		return nil;
	}
	
	MPCSession* session = MPCCreateMPCSession();
	if (session == NULL)
	{
        return nil;
    }
	
	HRESULT hres = 0;
	MPCObject* anncase = session->OpenFile([filePath UTF8String]);
    if (anncase == NULL) 
	{
        return nil;
    }
	
	NSMutableArray* result = nil;
	int count = anncase->GetNumberOfChildren();
	if (count > 0)
	{
		result = [[NSMutableArray alloc]init];
		for (int i = 0; i < count; i++)
		{
			UIImage *image = [self createAnnotationImage:anncase 
												andIndex:i 
										  withImageWidth:width];
			if (image != nil)
			{
				[result addObject:image];
			}
		}
	}
	
	session->CloseFile(anncase, 0);
	MPCDestroyMPCSession(session);
	
	return [result autorelease];
}

+ (BOOL) addResistAnnotationToLocal:(MPCObject*)obj  withSession:(MPCSession*)session
{
	if (obj == NULL || session == NULL)
	{
		return NO;
	}
	
	NSString* filePath = [self getLocalLoginAnntationFilePath];
	
	HRESULT hres = 0;
	if ([self fileExistsAtPath:filePath] == NO) 
	{
		MPCObject *anncase = session->CreateScratchMPCObject(OT_ANNOTATION_CASE, &hres);
		if (hres != MP_NOERROR) 
		{
			::DestroyAnnotationCase(anncase);
			return NO;
		}
		
		if ([self resistAnnotation:anncase andObject:obj] == NO)
		{
			::DestroyAnnotationCase(anncase);
			return NO;
		}
		
		hres = session->SaveAs(anncase, [filePath UTF8String]);
		if (hres != MP_NOERROR) 
		{
			::DestroyAnnotationCase(anncase);
			return NO;
		}
		
		session->CloseFile(anncase, 0);
	}
	else
	{
		MPCObject *anncase = session->OpenFile([filePath UTF8String], &hres, MP_UPDATE);
		if (hres != MP_NOERROR) 
		{
			return NO;
		}
		
		if ([self resistAnnotation:anncase andObject:obj] == NO)
		{
			session->CloseFile(anncase, 0);
			return NO;
		}
		
		hres = session->Save(anncase);
		if (hres != MP_NOERROR) 
		{
			session->CloseFile(anncase, 0);
			return NO;
		}
		
		session->CloseFile(anncase, 0);
	}
	
	return YES;
}

+ (BOOL) deleteResistAnnotatinWithIndex:(NSArray*)indexList
{
	if (indexList == nil || indexList.count == 0)
	{
		return NO;
	}
	
	NSString* filePath = [self getLocalLoginAnntationFilePath];
	if ([self fileExistsAtPath:filePath] == NO) 
	{
		return NO;
	}
	
	MPCSession* session = MPCCreateMPCSession();
	if (session == NULL)
	{
		return NO;
	}
	
	HRESULT hres = 0;
	MPCObject *anncase = session->OpenFile([filePath UTF8String], &hres, MP_UPDATE);
	if (hres != MP_NOERROR) 
	{
		MPCDestroyMPCSession(session);
		return NO;
	}
	
	for (int i = 0; i < indexList.count; i++)
	{
		int index = [((NSNumber*)[indexList objectAtIndex:i]) intValue];
		if (index >= 0 && index < LOCAL_RESIST_ANNOTATION_COUNT)
		{
			MPCObject* obj = anncase->UnlinkChild(index - i);
			if (obj != NULL)
			{
				obj->Destroy();
			}
		}
	}
	
	hres = session->Save(anncase);
	if (hres != MP_NOERROR) 
	{
		session->CloseFile(anncase, 0);
		MPCDestroyMPCSession(session);
		return NO;
	}
	
	session->CloseFile(anncase, 0);
	
	MPCDestroyMPCSession(session);
	
	return YES;
}

+ (BOOL)	 getResistAnnotationWithIndex:(NSInteger)annIndex 
						   withSession:(MPCSession*)session
					  withAnnObjectRef:(MPCObject **)annObject;
{
	
	if (annIndex < 0 || session == NULL || annObject == NULL)
	{
		return NO;
	}
	
	NSString* filePath = [self getLocalLoginAnntationFilePath];
	if ([self fileExistsAtPath:filePath] == NO) 
	{
		return NO;
	}
    
	HRESULT hres = 0;
	MPCObject* anncase = session->OpenFile([filePath UTF8String]);
    if (anncase == NULL) 
	{
        return NO;
    }
	
	MPCObject *obj = anncase->GetNthChild(annIndex,&hres);
    if (hres != MP_NOERROR || obj == NULL) 
	{
		return NO;
	}
    
    *annObject = obj->Duplicate();
    if (*annObject == NULL) 
	{
        return NO;
    }
    
	session->CloseFile(anncase, 0);
    
	return YES;
}

@end

#define TAG_LOGIN_ANNO_BUTTON_BASE			1000
#define TAG_LOGIN_ANNO_DELETE_ALERT			1001

#define LOGIN_ANNO_BUTTON_IPHONE_WIDTH_H	149
#define LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_H	64
#define LOGIN_ANNO_BUTTON_IPHONE_WIDTH_V	89.2
#define LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V	64

#define LOGIN_ANNO_BUTTON_IPAD_WIDTH_H		362
#define LOGIN_ANNO_BUTTON_IPAD_HEIGHT_H		128
#define LOGIN_ANNO_BUTTON_IPAD_WIDTH_V		193.2
#define LOGIN_ANNO_BUTTON_IPAD_HEIGHT_V		128

#define ROW_COUNT_H							5
#define ROW_COUNT_V							2

#define INDEX_DEL_BUTTON					1

@implementation DWLoginAnnThumbnailImage
@synthesize backgroundImageView = backgroundImageView_;
@synthesize selected = selected_;

-(id) initWithFrame:(CGRect)frame
{
	if (self = [super initWithFrame:frame])
	{
		self.adjustsImageWhenDisabled = NO;
		self.showsTouchWhenHighlighted = YES;
		
		self.layer.borderColor	= [UIColor lightGrayColor].CGColor;
		self.backgroundColor	= [UIColor whiteColor];
		self.layer.borderWidth	= 1.0f;
		self.layer.cornerRadius	= 7.0f;
		
		backgroundImageView_ = nil;
		
		selected_ = NO;
	}
	
	return self;
}

- (void) setThumbnailImage:(UIImage*)img
{
	self.backgroundImageView = [[[UIImageView alloc] initWithImage:img] autorelease];
	self.backgroundImageView.backgroundColor	= [UIColor clearColor];
	self.backgroundImageView.layer.borderColor	= [UIColor lightGrayColor].CGColor;
	[self addSubview:self.backgroundImageView];
}

- (void) setThumbnailImageFrame
{
	self.backgroundImageView.frame = CGRectMake((self.frame.size.width - backgroundImageView_.frame.size.width) / 2,
												(self.frame.size.height - backgroundImageView_.frame.size.height) / 2,
												backgroundImageView_.frame.size.width, 
												backgroundImageView_.frame.size.height);
}

- (void) showSelectBorder
{
	self.layer.borderColor	= [UIColor blueColor].CGColor;
	self.layer.borderWidth	= 4.0f;
}

- (void) hideSelectBorder
{
	self.layer.borderColor	= [UIColor lightGrayColor].CGColor;
	self.layer.borderWidth	= 1.0f;
}

- (void)dealloc
{
	self.backgroundImageView = nil;
	
	[super dealloc];
}

@end


@implementation DWLoginAnnPropertySettingsController
@synthesize delegate;
@synthesize loginAnnIndex;

- (id)initWithActionType:(LoginActionType)type 
		  andOrientation:(UIInterfaceOrientation)orientation
{
	if (self = [super initWithStyle:UITableViewStylePlain]) 
	{
		actionType_			= type;
		orientation_		= orientation;
		editMode			= NO;
		loginAnnoArrays_	= [[NSMutableArray alloc]init];
		
		[self loadLoginAnnotationData];
	}
	
	return self;
}

- (BOOL) loadLoginAnnotationData
{
	[loginAnnoArrays_ removeAllObjects];
	
	float width  = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_H;
	float height = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_H;
	
	if (Utility::UIDeviceIsiPad() == NO)
	{
		if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
		{
			width  = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_H;
			height = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_H;
		}
		else
		{
			width  = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_V;
			height = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V;
		}
	}
	else
	{
		if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
		{
			width  = LOGIN_ANNO_BUTTON_IPAD_WIDTH_H;
			height = LOGIN_ANNO_BUTTON_IPAD_HEIGHT_H;
		}
		else
		{
			width  = LOGIN_ANNO_BUTTON_IPAD_WIDTH_V;
			height = LOGIN_ANNO_BUTTON_IPAD_HEIGHT_V;
		}
		
		if (actionType_ == kLoginActionRead)
		{
			width  = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_V;
			height = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V;
		} 
	}
	
	NSArray* annList_ = [DWResistAnnotationManager getResistAnnotationImageListWithImageWidth:height];
	if (annList_ != nil)
	{
		for (int i = 0; i < annList_.count; i++)
		{
			CGRect annoRect = CGRectMake(0, 0, width, height);
			DWLoginAnnThumbnailImage *button_ = [[DWLoginAnnThumbnailImage alloc] initWithFrame:annoRect];
			button_.tag = i + TAG_LOGIN_ANNO_BUTTON_BASE;	
			
			[button_ addTarget:self 
						action:@selector(actionOnTouchLoginAnnoButton:)
			  forControlEvents:UIControlEventTouchUpInside];
			
			[button_ setThumbnailImage:[annList_ objectAtIndex:i]];
			[loginAnnoArrays_ addObject:button_];
			[button_ release];
		}
	}
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - View lifecycle
- (void)viewDidLoad
{
    [super viewDidLoad];
	
	// 1. init tableview prop.
	self.view.backgroundColor = [UIColor lightGrayColor];
	self.tableView.separatorColor = [UIColor clearColor];
	self.tableView.scrollEnabled = NO;
    
	// 2. init navigationbar item.
	[self initNavigationbarItems];
    
	// 3. inint toolbar items.
	[self initToolbarItems];
	
	self.tableView.scrollEnabled = NO;
	
    if (actionType_ ==  kLoginActionRead && Utility::UIDeviceIsiPad() == YES) 
	{	
		float width  = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_V  * ROW_COUNT_H + 30;
		float height = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V * ROW_COUNT_V + 20;
		self.tableView.frame = CGRectMake(0, 0, width, height);
    } 
	
	// 4. init indicator.
	activeIndicator_ = [[UIActivityIndicatorView alloc]
						initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge];
	
	if (activeIndicator_ != nil)
	{
		activeIndicator_.frame = CGRectMake(0, 0, 40, 40);
		
		if ([activeIndicator_ respondsToSelector:@selector(color)])
		{
			activeIndicator_.color = [UIColor blackColor];
		}
		else
		{
			if ([[UIScreen mainScreen] scale] == 2.0)
			{
				activeIndicator_.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
			}
		}
		[self.view addSubview:activeIndicator_];
	}
}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
	
    if (actionType_ == kLoginActionEdit) 
	{
        self.navigationController.toolbarHidden = NO;
        self.navigationController.toolbar.barStyle = UIBarStyleBlack;
    }
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
	
    if (actionType_ == kLoginActionEdit) 
	{
        self.navigationController.toolbarHidden = YES;
    }
	
	[self displayIndicator];
}

- (void)viewDidDisappear:(BOOL)animated
{	
	[self hideIndicator];

	[super viewDidDisappear:animated];
}

- (void)dealloc
{
	[loginAnnoArrays_ release];
	
	if (activeIndicator_ != nil)
	{
		[activeIndicator_ removeFromSuperview];
		[activeIndicator_ release];
	}
	
	[super dealloc];
}

#pragma mark - 
#pragma mark view rotation.
- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	if (actionType_ == kLoginActionEdit) 
	{
		if (Utility::UIDeviceIsiPad() == YES) 
		{
			return YES;
		}
		else
		{
			return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
		}
	}
	else
	{
		return (orientation_ == interfaceOrientation);
	}
}

- (void) willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation 
										 duration:(NSTimeInterval)duration
{	
    if (actionType_ == kLoginActionEdit) 
	{
        [self.tableView reloadData];
    }
}

#pragma mark - 
#pragma mark navigation bar items.
- (void)initNavigationbarItems
{
	if (actionType_ == kLoginActionEdit) 
	{
		self.title = NSLocalizedString(@"TITLE_LOGIN_ANNOTATION_SETTITLE", nil);
		
		UIBarButtonItem* item = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_EDIT", nil) 
													  andAction:@selector(actionOnTouchEditButtonItem:)];
		self.navigationItem.rightBarButtonItem = item;
	}
	else
	{
		self.navigationController.navigationBar.barStyle = UIBarStyleBlackTranslucent;
		self.title = NSLocalizedString(@"TITLE_LOGIN_ANNOTATION_PROPERTYTITLE", nil);
		
		UIButton* buttonBack = [UIButton buttonWithType:(UIButtonType)101];
		[buttonBack setTitle:NSLocalizedString(@"BUTTON_TITLE_BACK", nil) 
					forState:UIControlStateNormal];
		[buttonBack addTarget:self 
					   action:@selector(actionOnTouchBackButtonItem) 
			 forControlEvents:UIControlEventTouchDown];
		
		UIBarButtonItem* buttonBackItem = [[UIBarButtonItem alloc] initWithCustomView:buttonBack];
		self.navigationItem.leftBarButtonItem = buttonBackItem;
		[buttonBackItem release]; 
	}
}

- (void) actionOnTouchBackButtonItem
{	
	if (Utility::UIDeviceIsiPad() == NO)
	{
		[delegate didSelectLoginAnnotationWithAnnotationIndex:loginAnnIndex];
	}
    [self.parentViewController dismissModalViewControllerAnimated:YES];
}

- (void) actionOnTouchEditButtonItem:(UIBarButtonItem*)buttonItem
{
	UIBarButtonItem* item = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_DONE", nil)
												  andAction:@selector(actionOnTouchDoneButtonItem:)];
	self.navigationItem.rightBarButtonItem = item;
    self.navigationItem.rightBarButtonItem.style = UIBarButtonItemStyleDone;
	
	editMode = YES;
    [self.tableView reloadData];
}

- (void) actionOnTouchDoneButtonItem:(UIBarButtonItem*)buttonItem
{
	UIBarButtonItem* item = [self createButtonItemWithTitle:NSLocalizedString(@"TITLE_BUTTONITEM_EDIT", nil) 
												  andAction:@selector(actionOnTouchEditButtonItem:)];
	self.navigationItem.rightBarButtonItem = item;
	
	editMode = NO;	
	
	[self loadLoginAnnotationData];
	
	[self updateToolBarStatus];
    [self.tableView reloadData];
}

#pragma mark - 
#pragma mark tool bar items.
- (void) initToolbarItems
{
	if (actionType_ ==  kLoginActionRead) 
	{
		return;
    }
	
	UIBarButtonItem* flexspaceButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace 
																							 target:nil 
																							 action:nil];
	UIBarButtonItem* deleteButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:[self getDeleteButtonIcon]] 
																			 style:UIBarButtonItemStylePlain 
																			target:self 
																			action:@selector(actionOnTouchDeleteButton)];
	deleteButtonItem.enabled = NO;
	
	NSMutableArray* toolbarItems_ = [[NSMutableArray alloc] init];
	[toolbarItems_ addObject:flexspaceButtonItem];
	[toolbarItems_ addObject:deleteButtonItem];
	[toolbarItems_ addObject:flexspaceButtonItem];
		
	self.toolbarItems = toolbarItems_;
		
	[flexspaceButtonItem release];
	[deleteButtonItem release];
	[toolbarItems_ release];
}

- (void) updateToolBarStatus
{
    UIBarButtonItem *delButton = nil;
    if (INDEX_DEL_BUTTON < [self.toolbarItems count]) 
    {
        delButton = [self.toolbarItems objectAtIndex:INDEX_DEL_BUTTON];
    }
    
    if (delButton != nil) 
    {
       [delButton setEnabled:NO]; 
    }
    
    if (editMode == YES)
    {
        for (int i = 0; i < [loginAnnoArrays_ count]; i++) 
        {
            DWLoginAnnThumbnailImage *annButton = (DWLoginAnnThumbnailImage *)[loginAnnoArrays_ 
																			   objectAtIndex:i];
            if (annButton.selected) 
            {
                if (delButton != nil) 
                {
                    [delButton setEnabled:YES];
					break;
                }
            }
        }
    }
}

- (void) actionOnTouchDeleteButton
{
    NSString* message_ = NSLocalizedString(@"MSG_WARING_DELETE_LOGIN_ANN", nil);
	UIAlertView* alertView = [[UIAlertView alloc] initWithTitle:nil 
														message:message_ 
													   delegate:self
											  cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_YES",nil)
											  otherButtonTitles:NSLocalizedString(@"BUTTON_TITLE_NO", nil) ,(char*)nil];
	
	alertView.tag = TAG_LOGIN_ANNO_DELETE_ALERT;
	[alertView show];
	[alertView release];
}

#pragma mark - 
#pragma mark Indicator.
- (void) displayIndicator
{	
	if (activeIndicator_ == nil)
	{
		return;
	}
	
	if (activeIndicator_.isAnimating == YES)
	{
		return;
	}
	
	activeIndicator_.center = self.view.center;
	
	[activeIndicator_ performSelectorInBackground:@selector(startAnimating)
									   withObject:nil];
}

- (void) hideIndicator
{
	if (activeIndicator_ == nil)
	{
		return;
	}
	
	[self.view bringSubviewToFront:activeIndicator_];
	
	if (activeIndicator_.isAnimating == NO)
	{
		return;
	}
	
	[activeIndicator_ stopAnimating];
}

#pragma mark - 
#pragma mark tabelview delegate method.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	if (Utility::UIDeviceIsiPad() == NO) 
	{
		if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
		{
			return ROW_COUNT_H;
		}
		else
		{
			return ROW_COUNT_V;
		}
	}
	else
	{
		if (actionType_ == kLoginActionRead)
		{
			return ROW_COUNT_V;
		}
		else
		{
			if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
			{
				return ROW_COUNT_H;
			}
			else
			{
				return ROW_COUNT_V;
			}
		}
	}
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
	if (Utility::UIDeviceIsiPad() == NO) 
	{
		if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
		{
			return (LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_H + 10);
		}
		else
		{
			return (LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V + 10);
		}
	}
	else
	{
		if (actionType_ == kLoginActionRead)
		{
			return (LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V + 10);
		}
		else
		{
			if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
			{
				return (LOGIN_ANNO_BUTTON_IPAD_HEIGHT_H + 30);
			}
			else
			{
				return (LOGIN_ANNO_BUTTON_IPAD_HEIGHT_V + 30);
			}
		}
	}
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	static NSString *CellIdentifier = nil;
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    } 

	cell.selectionStyle = UITableViewCellSelectionStyleNone;
	
	[self initTableViewCell:cell withIndexPath:indexPath withActionType:actionType_];
		
    return cell;
}

#pragma mark - 
#pragma mark init cell method.
- (void) initTableViewCell:(UITableViewCell*)cell 
			 withIndexPath:(NSIndexPath*)indexPath
			withActionType:(LoginActionType)type
{
	float rows, cols, buttonWidth, buttonHeight, offset, originY, interval;
	
	
	// iphone.
	if (Utility::UIDeviceIsiPad() == NO)
	{
		offset		= 5;
		interval	= 4;
		originY		= 5;
		
		if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
		{
			rows = ROW_COUNT_H;
			cols = ROW_COUNT_V;
			
			buttonWidth	 = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_H;
			buttonHeight = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_H;
		}
		else
		{
			rows = ROW_COUNT_V;
			cols = ROW_COUNT_H;
			
			buttonWidth	 = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_V;
			buttonHeight = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V;
		}
	}
	// ipad
	else
	{
		offset		= 10;
		interval	= 8;
		originY		= 15;
		
		if (actionType_ == kLoginActionRead)
		{
			offset		= 5;
			interval	= 4;
			originY		= 5;
			
			rows = ROW_COUNT_V;
			cols = ROW_COUNT_H;
			
			buttonWidth	 = LOGIN_ANNO_BUTTON_IPHONE_WIDTH_V;
			buttonHeight = LOGIN_ANNO_BUTTON_IPHONE_HEIGHT_V;
		}
		else
		{
			if (UIInterfaceOrientationIsPortrait(self.interfaceOrientation))
			{
				rows = ROW_COUNT_H;
				cols = ROW_COUNT_V;
				
				buttonWidth	 = LOGIN_ANNO_BUTTON_IPAD_WIDTH_H;
				buttonHeight = LOGIN_ANNO_BUTTON_IPAD_HEIGHT_H;
			}
			else
			{
				rows = ROW_COUNT_V;
				cols = ROW_COUNT_H;
				
				buttonWidth  = LOGIN_ANNO_BUTTON_IPAD_WIDTH_V;
				buttonHeight = LOGIN_ANNO_BUTTON_IPAD_HEIGHT_V;
			}
		}
	}
	
	// 3. init annotation index.
	int annoIndex = indexPath.row * cols;
	
	for (int i = 0; i < cols; i++) 
	{
		if (annoIndex >= [loginAnnoArrays_ count]) 
		{
			break;
		}
		
		float originX       = offset + interval + (buttonWidth + interval) * i;
		
		CGRect annoRect = CGRectMake(originX, originY, buttonWidth, buttonHeight);
		
		DWLoginAnnThumbnailImage *button_ = (DWLoginAnnThumbnailImage *)[loginAnnoArrays_ 
																		 objectAtIndex:annoIndex];
		button_.frame = annoRect;
		[button_ setThumbnailImageFrame];
		
		if (kLoginActionEdit == type) 
		{
			if (editMode == NO) 
			{
				[button_ setEnabled:editMode];
			}
			else
			{
				[button_ setEnabled:editMode];
				
				if (button_.selected == YES)
				{
					[button_ showSelectBorder];
				}
				else
				{
					[button_ hideSelectBorder];
				}
			}
		}
		else		
		{
			if (annoIndex == loginAnnIndex)
			{
				button_.selected = YES;
			}
			
			if (button_.selected == YES)
			{
				[button_ showSelectBorder];
			}
			else
			{
				[button_ hideSelectBorder];
			}
		}
		
		[cell.contentView addSubview:button_];

		annoIndex++;
	}
}

- (void) actionOnTouchLoginAnnoButton:(id)sender
{
	DWLoginAnnThumbnailImage* button_ = (DWLoginAnnThumbnailImage*)sender;
	if (button_ != nil)
	{
		if (actionType_ == kLoginActionEdit) 
		{
			if (editMode == YES)
			{
				if (button_.selected == NO)
				{
					[button_ showSelectBorder];
					button_.selected = YES;
				}
				else
				{
					[button_ hideSelectBorder];
					button_.selected = NO;
				}
			}
			
			 [self updateToolBarStatus];
		}
		else
		{
			loginAnnIndex =  button_.tag - TAG_LOGIN_ANNO_BUTTON_BASE;
			
			if (Utility::UIDeviceIsiPad() == YES) 
			{
				[delegate didSelectLoginAnnotationWithAnnotationIndex:loginAnnIndex];
				return ;
            }
			
			for (int i = 0; i < loginAnnoArrays_.count; i++)
			{
				DWLoginAnnThumbnailImage *button_ = (DWLoginAnnThumbnailImage *)[loginAnnoArrays_ 
																				 objectAtIndex:i];
				
				if (i == loginAnnIndex) 
				{
					button_.selected = YES;
				}
				else
				{
					button_.selected = NO;
				}
			}
			
			[self.tableView reloadData];
		}
	}
}

#pragma mark - 
#pragma mark common method.
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (alertView.tag == TAG_LOGIN_ANNO_DELETE_ALERT)
	{
		if (buttonIndex == 0)
		{
			NSMutableArray *delAnnotations = [NSMutableArray array];
			for (int i = 0; i < [loginAnnoArrays_ count]; i++) 
			{
				DWLoginAnnThumbnailImage *annButton = (DWLoginAnnThumbnailImage *)[loginAnnoArrays_ 
																				   objectAtIndex:i];
				
				if (annButton.selected == YES) 
				{
					int tag = annButton.tag - TAG_LOGIN_ANNO_BUTTON_BASE;
					[delAnnotations addObject:[NSNumber numberWithInt:tag]];
				}
			}
			
			if ([DWResistAnnotationManager deleteResistAnnotatinWithIndex:delAnnotations])
			{
				[self loadLoginAnnotationData];
				
				[self updateToolBarStatus];
				
				loginAnnIndex = 0;
				[delegate didSelectLoginAnnotationWithAnnotationIndex:loginAnnIndex];
				
				[self.tableView reloadData];
			}
		}
	}
}

#pragma mark - 
#pragma mark common method.
- (UIBarButtonItem*) createButtonItemWithTitle:(NSString*)title andAction:(SEL)action
{
	UIBarButtonItem* buttonItem = [[UIBarButtonItem alloc] initWithTitle:title
																   style:UIBarButtonItemStyleBordered
																  target:self
																  action:action];
	return [buttonItem autorelease];
}

- (NSString*) getDeleteButtonIcon
{
	return _ICON_DELETE_LOWSCALE_;
}
@end
