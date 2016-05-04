//
//  XMLViewController.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-9.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "XMLViewController.h"
#import "GDataXMLNode.h"
#import "XMLPackage.h"
#import "XMLParser.h"

@implementation XMLViewController

@synthesize parseButton;
@synthesize packageButton;
@synthesize xmlStrView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [packageButton release];
    [parseButton release];
    [xmlStrView release];
    [super dealloc];
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

#pragma make -
#pragma make action button

- (IBAction) actionParserButton:(id)sender
{
    // 得到资源文件路径
    NSString *path = [[NSBundle mainBundle] pathForResource:@"party" ofType:@"xml"];
    xmlStrView.text = [XMLParser parseGDataXMLPath:path];
}

- (IBAction) actionPackageButton:(id)sender
{
    XMLNode *node = [[XMLPackage getXML] retain];
    GDataXMLElement *xmlElement = [[XMLPackage PackageXMLWithXMLNode:node] retain];
    GDataXMLDocument *xmlDoc = [[XMLPackage getXMLDocument:xmlElement] retain];
    
    if (xmlDoc != nil) {
        NSData *data = xmlDoc.XMLData;
        NSString *xmlStr = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        xmlStrView.text = xmlStr;
    }
    
    //release
    [node release];
    [xmlElement release];
    [xmlDoc release];
}

@end
