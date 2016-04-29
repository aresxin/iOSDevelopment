//
//  Dropbox.m
//  ByteClub
//
//  Created by Charlie Fulton on 7/26/13.
//  Copyright (c) 2013 Razeware. All rights reserved.
//

#import "Dropbox.h"

//#warning INSERT YOUR OWN API KEY and SECRET HERE
static NSString *apiKey = @"xz4f6k69q9p117x";
static NSString *appSecret = @"6uwkba0xthy505q";

//#warning THIS FOLDER MUST BE CREATED AT THE TOP LEVEL OF YOUR DROPBOX FOLDER, you can then share this folder with others
NSString * const appFolder = @"byteclub";

NSString * const oauthTokenKey = @"oauth_token";
NSString * const oauthTokenKeySecret = @"oauth_token_secret";
NSString * const dropboxUIDKey = @"uid";

NSString * const dropboxTokenReceivedNotification = @"have_user_request_token";

#pragma mark - saved in NSUserDefaults
NSString * const requestToken = @"requestToken";
NSString * const requestTokenSecret = @"requestTokenSecret";

NSString * const accessToken = @"accessToken";
NSString * const accessTokenSecret = @"accessTokenSecret";



@implementation Dropbox

+(void)requestTokenWithCompletionHandler:(DropboxRequestTokenCompletionHandler)completionBlock
{
    NSString *authorizationHeader = [self plainTextAuthorizationHeaderForAppKey:apiKey
                                                                      appSecret:appSecret
                                                                          token:nil
                                                                    tokenSecret:nil];
    
    NSURLSessionConfiguration *sessionConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
    [sessionConfig setHTTPAdditionalHeaders:@{@"Authorization": authorizationHeader}];
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:[NSURL URLWithString:@"https://api.dropbox.com/1/oauth/request_token"]];
    [request setHTTPMethod:@"POST"];
    
    NSURLSession *session = [NSURLSession sessionWithConfiguration:sessionConfig];
    
    [[session dataTaskWithRequest:request completionHandler:completionBlock] resume];
}

+(void)exchangeTokenForUserAccessTokenURLWithCompletionHandler:(DropboxRequestTokenCompletionHandler)completionBlock
{
    NSString *urlString = [NSString stringWithFormat:@"https://api.dropbox.com/1/oauth/access_token?"];
    NSURL *requestTokenURL = [NSURL URLWithString:urlString];
    
    NSString *reqToken = [[NSUserDefaults standardUserDefaults] valueForKey:requestToken];
    NSString *reqTokenSecret = [[NSUserDefaults standardUserDefaults] valueForKey:requestTokenSecret];
    
    NSString *authorizationHeader = [self plainTextAuthorizationHeaderForAppKey:apiKey
                                                                      appSecret:appSecret
                                                                          token:reqToken
                                                                    tokenSecret:reqTokenSecret];
    
    NSURLSessionConfiguration *sessionConfig = [NSURLSessionConfiguration defaultSessionConfiguration];
    [sessionConfig setHTTPAdditionalHeaders:@{@"Authorization": authorizationHeader}];
    
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:requestTokenURL];
    [request setHTTPMethod:@"POST"];
    
    NSURLSession *session = [NSURLSession sessionWithConfiguration:sessionConfig];
    [[session dataTaskWithRequest:request completionHandler:completionBlock] resume];
}

+(NSString*)plainTextAuthorizationHeaderForAppKey:(NSString*)appKey appSecret:(NSString*)appSecret token:(NSString*)token tokenSecret:(NSString*)tokenSecret
{
    // version, method, and oauth_consumer_key are always present
    NSString *header = [NSString stringWithFormat:@"OAuth oauth_version=\"1.0\",oauth_signature_method=\"PLAINTEXT\",oauth_consumer_key=\"%@\"",apiKey];
    
    // look for oauth_token, include if one is passed in
    if (token) {
        header = [header stringByAppendingString:[NSString stringWithFormat:@",oauth_token=\"%@\"",token]];
    }
    
    // add oauth_signature which is app_secret&token_secret , token_secret may not be there yet, just include @"" if it's not there
    if (!tokenSecret) {
        tokenSecret = @"";
    }
    header = [header stringByAppendingString:[NSString stringWithFormat:@",oauth_signature=\"%@&%@\"",appSecret,tokenSecret]];
    return header;
}


+(NSString*)apiAuthorizationHeader
{
    NSString *token = [[NSUserDefaults standardUserDefaults] valueForKey:accessToken];
    NSString *tokenSecret = [[NSUserDefaults standardUserDefaults] valueForKey:accessTokenSecret];
    return [self plainTextAuthorizationHeaderForAppKey:apiKey
                                             appSecret:appSecret
                                                 token:token
                                           tokenSecret:tokenSecret];
}


+(NSDictionary*)dictionaryFromOAuthResponseString:(NSString*)response
{
    NSArray *tokens = [response componentsSeparatedByString:@"&"];
    NSMutableDictionary *oauthDict = [[NSMutableDictionary alloc] initWithCapacity:5];
    
    for(NSString *t in tokens) {
        NSArray *entry = [t componentsSeparatedByString:@"="];
        NSString *key = entry[0];
        NSString *val = entry[1];
        [oauthDict setValue:val forKey:key];
    }
    
    return [NSDictionary dictionaryWithDictionary:oauthDict];
}


+ (NSURL*)appRootURL
{
    NSString *url = [NSString stringWithFormat:@"https://api.dropbox.com/1/metadata/dropbox/%@",appFolder];
    NSLog(@"listing files using url %@", url);
    return [NSURL URLWithString:url];
}

+ (NSURL*)uploadURLForPath:(NSString*)path
{
    NSString *urlWithParams = [NSString stringWithFormat:@"https://api-content.dropbox.com/1/files_put/dropbox/%@/%@",
                               appFolder,
                               [path stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];    
    NSURL *url = [NSURL URLWithString:urlWithParams];
    return url;
}

+ (NSURL*)createPhotoUploadURL
{
    NSString *urlWithParams = [NSString stringWithFormat:@"https://api-content.dropbox.com/1/files_put/dropbox/%@/photos/byteclub_pano_%i.jpg",appFolder,arc4random() % 1000];
    NSURL *url = [NSURL URLWithString:urlWithParams];
    return url;
}

@end
