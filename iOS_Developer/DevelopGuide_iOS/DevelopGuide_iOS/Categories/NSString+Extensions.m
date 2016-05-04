#import "NSString+Extensions.h"
#import <CommonCrypto/CommonDigest.h>


@implementation NSString (Extensions)

+ (NSString*)stringToSha1:(NSString*)str {
  const char *s = [str cStringUsingEncoding:NSUTF8StringEncoding];
    NSData *keyData = [NSData dataWithBytes:s length:strlen(s)];

    // This is the destination
    uint8_t digest[CC_SHA1_DIGEST_LENGTH] = {0};
    // This one function does an unkeyed SHA1 hash of your hash data
    CC_SHA1(keyData.bytes, keyData.length, digest);
	
    // Now convert to NSData structure to make it usable again
    NSData *out = [NSData dataWithBytes:digest length:CC_SHA1_DIGEST_LENGTH];
    NSString *hash = [out description];
	
	NSCharacterSet *doNotWants = [NSCharacterSet characterSetWithCharactersInString:@"<> "];
	hash = [[hash componentsSeparatedByCharactersInSet:doNotWants] componentsJoinedByString:@""];
	
    return hash;
}

- (NSNumber*)stringToNSNumber {
	NSNumberFormatter* tmpFormatter = [[NSNumberFormatter alloc] init];
	[tmpFormatter setNumberStyle:NSNumberFormatterDecimalStyle];
	NSNumber* theNumber = [tmpFormatter numberFromString:self];
	return theNumber;
}

- (BOOL)isEmpty {
    if ([self length] <= 0 || self == (id)[NSNull null] || self == nil) {
        return YES;
    } 
    return NO;
}

- (BOOL)stringContainsSubString:(NSString *)subString {
    NSRange aRange = [self rangeOfString:subString];
    if (aRange.location == NSNotFound) {
        return NO;
    }
    
    return YES;
}

- (NSString*)stringByReplacingStringsFromDictionary:(NSDictionary*)dict {
    NSMutableString* string = [self mutableCopy];
    for (NSString* target in dict) {
        [string replaceOccurrencesOfString:target withString:[dict objectForKey:target] options:0 range:NSMakeRange(0, [string length])];
    }
    return string;
}

@end
