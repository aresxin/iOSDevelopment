//
//  AssetsLibrary.m
//  DevelopGuide_iOS
//
//  Created by lu matthew on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AssetsLibrary.h"

@implementation AssetsLibrary

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

- (IBAction)showAssetsLibray:(id)sender
{
    __block int numberOfGroups = 0;   
    __block int numberOfAssets = 0;   
    
    // Create the object to represent the library   
    ALAssetsLibrary *assetsLibrary = [[ALAssetsLibrary alloc] init];   
    
    // What kind of groups are you interested in?   
    NSUInteger groupTypes = ALAssetsGroupAll;   
    
    // Create the block to enumerate through the groups   
    // 创建遍历媒体库的回调函数
    ALAssetsLibraryGroupsEnumerationResultsBlock listGroupBlock =    
    ^(ALAssetsGroup *group, BOOL *stop) {   
        // this block will be called for every group, and ONCE MORE!   
        // so first, test if there's a real group being passed in:   
        if (group) {   
            // add to the totals   
            numberOfGroups++;   
            numberOfAssets += group.numberOfAssets;   
            // output some info about the group   
            NSLog(@"The name of the group is, %@",   
                  [group valueForProperty:ALAssetsGroupPropertyName]); 
            
         //枚举group中的Asstes   
            [group enumerateAssetsUsingBlock:^(ALAsset *result, NSUInteger index, BOOL *stop){
                NSLog(@"asset de index is %d",index);
                NSLog(@"alasset is %@",result);
                
            }];
        } else {   
            // the group object is nil, must mean we're done enumerating!   
            // create an output message.   
            NSString *message = [NSString    
                                 stringWithFormat:@"There are %d groups with %d total assets.",   
                                 numberOfGroups,numberOfAssets];   
            
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Asset Stats!"    
                                                            message:message    
                                                           delegate:nil    
                                                  cancelButtonTitle:@"Okay"    
                                                  otherButtonTitles:nil];   
            [alert show];   
            [alert release];   
            
        }   
        
    };   
    
    // create the failure block   
    ALAssetsLibraryAccessFailureBlock failBlock = ^(NSError *error) {   
        NSLog(@"Error:%@", [error localizedDescription]);    
    };   
    
    // now enumerate through the groups, using the created blocks   
    // 枚举所有的组
    [assetsLibrary enumerateGroupsWithTypes:groupTypes    
                                 usingBlock:listGroupBlock    
                               failureBlock:failBlock];   
    
    [assetsLibrary release];   

}


-(IBAction) getStats {   
    __block int numberOfGroups = 0;   
    __block int numberOfAssets = 0;   
    
    // Create the object to represent the library   
    ALAssetsLibrary *assetsLibrary = [[ALAssetsLibrary alloc] init];   
    
    // What kind of groups are you interested in?   
    NSUInteger groupTypes = ALAssetsGroupAll;   
    
    // Create the block to enumerate through the groups   
    // 创建遍历媒体库的回调函数
    ALAssetsLibraryGroupsEnumerationResultsBlock listGroupBlock =    
    ^(ALAssetsGroup *group, BOOL *stop) {   
        // this block will be called for every group, and ONCE MORE!   
        // so first, test if there's a real group being passed in:   
        if (group) {   
            // add to the totals   
            numberOfGroups++;   
            numberOfAssets += group.numberOfAssets;   
            // output some info about the group   
            NSLog(@"The name of the group is, %@",   
                  [group valueForProperty:ALAssetsGroupPropertyName]);  
//            [group enumerateAssetsUsingBlock:];
        } else {   
            // the group object is nil, must mean we're done enumerating!   
            // create an output message.   
            NSString *message = [NSString    
                                 stringWithFormat:@"There are %d groups with %d total assets.",   
                                 numberOfGroups,numberOfAssets];   
            
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Asset Stats!"    
                                                            message:message    
                                                           delegate:nil    
                                                  cancelButtonTitle:@"Okay"    
                                                  otherButtonTitles:nil];   
            [alert show];   
            [alert release];   
            
        }   
        
    };   
    
    // create the failure block   
    ALAssetsLibraryAccessFailureBlock failBlock = ^(NSError *error) {   
        NSLog(@"Error:%@", [error localizedDescription]);    
    };   
    
    // now enumerate through the groups, using the created blocks   
    // 枚举所有的组
    [assetsLibrary enumerateGroupsWithTypes:groupTypes    
                                 usingBlock:listGroupBlock    
                               failureBlock:failBlock];   
    
    [assetsLibrary release];   
}  
@end
