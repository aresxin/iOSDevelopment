//
//  DBFile.h
//  DropShare
//
//  Created by Charles Fulton on 7/11/13.
//  Copyright (c) 2013 RayWenderlich.com. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void(^ThumbnailCompletionBlock)();

@interface DBFile : NSObject

@property (strong, nonatomic) NSString *path;
@property (strong, nonatomic) NSString *root;
@property (readwrite) BOOL thumbExists;
@property (strong, nonatomic) NSDate *modified;
@property (strong, nonatomic) NSString *contents;
@property (strong, nonatomic) NSString *mimeType;
@property (nonatomic, strong) UIImage *thumbNail;


- (id)initWithJSONData:(NSDictionary*)data;

-(NSString *)fileNameShowExtension:(BOOL)showExtension;


@end
