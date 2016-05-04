#import <Foundation/Foundation.h>


@interface NSString (Extensions) 

+ (NSString *)stringToSha1:(NSString *)str;
- (NSNumber*)stringToNSNumber;
- (BOOL)isEmpty;
- (BOOL)stringContainsSubString:(NSString *)subString;
- (NSString *)stringByReplacingStringsFromDictionary:(NSDictionary *)dict;


@end
