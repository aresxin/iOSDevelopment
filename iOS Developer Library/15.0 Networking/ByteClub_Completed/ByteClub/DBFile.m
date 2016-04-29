//
//  DBFile.m
//  DropShare
//
//  Created by Charles Fulton on 7/11/13.
//  Copyright (c) 2013 RayWenderlich.com. All rights reserved.
//

#import "DBFile.h"
#import "Dropbox.h"

typedef void(^DBFileUpdateCompletionBlock)(DBFile* updatedFile);

@implementation DBFile

- (id)initWithJSONData:(NSDictionary*)data
{
    self = [super init];
    if (self) {
        self.path = data[@"path"];
        self.root = data[@"root"];
        self.thumbExists = [data[@"thumb_exists"] boolValue];        
        NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
        formatter.dateFormat = @"EEE, dd MMM yyyy HH:mm:ss Z";
        NSDate *date = [formatter dateFromString:data[@"modified"]];
        if (date) {
            self.modified = date;
        }
        self.mimeType = data[@"mime_type"];
    }
    return self;
}

-(NSString *)fileNameShowExtension:(BOOL)showExtension
{
    NSString *path = self.path;
    NSString *filePath = [[path componentsSeparatedByString:@"/"] lastObject];
    if (!showExtension) {
        filePath = [[filePath componentsSeparatedByString:@"."] firstObject];
    }
    return filePath;
}


// sort by level, then acheivement points
- (NSComparisonResult)compare:(DBFile *)other
{
    NSComparisonResult order;
    
    // first compare modified
    order = [other.modified compare:self.modified];
    
    // if same modified alpha by path
    if (order == NSOrderedSame) {
        order = [other.path compare:self.path];
    }
    return order;
}

-(NSString *)description
{
    return [NSString stringWithFormat:@"File from %@ %@", self.root, self.path];
}
@end
