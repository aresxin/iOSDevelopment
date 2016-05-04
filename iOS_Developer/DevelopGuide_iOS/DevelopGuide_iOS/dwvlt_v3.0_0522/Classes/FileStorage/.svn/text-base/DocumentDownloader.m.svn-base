//
//  DownloadDocument.m
//  DWViewer
//
//  Created by Neusoft on 10-10-22.
//
//

#import "DocumentDownloader.h"

@implementation DocumentDownloader
@synthesize filePath;
// AR17635
@synthesize needAuthen;
#pragma mark -
#pragma mark Init method
- (id)initWithRequest:(NSURLRequest *)req 
			directory:(NSString *)dir 
			 delegate:(id<DocumentDownloaderDeleagte, NSObject>)dg
{
	if (self = [super init])
	{
		request = [req retain];
		directoryPath = [dir retain];
		delegate = [dg retain];
		con = [[NSURLConnection alloc] initWithRequest:request delegate:self];
		
		self.needAuthen = NO;
	}
	return self;
}



#pragma mark -
#pragma mark Downloader Lifecycle
- (void)dealloc
{
	[request release];
	[directoryPath release];
	[filePath release];
	[file release];
	[delegate release];
	[con release];
	[super dealloc];
}

- (void)cancel
{
	[con cancel];
}


#pragma mark -
#pragma mark NSURLConnection delegate
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
	[filePath release];
	filePath = [[response suggestedFilename] retain];
	if ([delegate respondsToSelector:@selector(download: didReceiveResponse:)])
	{
		[delegate download:self didReceiveResponse:response];
	}
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
	if ([delegate respondsToSelector:@selector(download: didFailWithError:)])
	{
		[delegate download:self didFailWithError:error];
	}
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
	@try
	{
		if (file == nil)
		{
			NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
			
			NSFileManager *fm = [NSFileManager defaultManager];
			BOOL isDir = false;
			if (![fm fileExistsAtPath:directoryPath isDirectory:&isDir])
			{
				NSError *error;
				if (![fm createDirectoryAtPath:directoryPath 
				   withIntermediateDirectories:YES 
									attributes:nil 
										 error:&error])
				{
					[NSException raise:@"Exception"
								format:@"%@", [error localizedDescription]];
				}
			}
			else if (!isDir)
			{
				[NSException raise:@"Exception"
							format:NSLocalizedString(@"MSG_CREATEFILE_FAIL", nil), 
				 directoryPath];
			}
            
            // tongtx 20110711 start
			//AR NO.17914 の対応
			NSString *newFile = nil;
			if ([filePath hasPrefix:@"."]) {
				newFile = [@"_" stringByAppendingString:[filePath substringFromIndex:1]];
				self.filePath = newFile;
			}
			//tongtx 20110711 end
            
			// For MemoryLeak
			NSString *initFilePath = [[directoryPath stringByAppendingPathComponent:filePath] 
									 stringByStandardizingPath];
			NSString *tmpFilePath = [initFilePath copy];
			// MemoryLeak end.
			
			int suffix = 0;
			NSString *fileNameWithNOExt = nil;
			NSMutableString *appendExtFileName = nil;
			while ([fm fileExistsAtPath:tmpFilePath])
			{
				//20101201,add by yan
				/*
				NSUInteger fileFullNameLength = [filePath length];
				fileNameWithNOExt = [filePath substringWithRange:NSMakeRange(0, fileFullNameLength - 4)];
				NSString *extentName = [filePath substringWithRange:NSMakeRange(fileFullNameLength - 4, 4)];
				 */
				fileNameWithNOExt = [filePath stringByDeletingPathExtension];
				NSString* extentName = [filePath pathExtension];
				extentName = [@"." stringByAppendingString:extentName];

				
				suffix++;
				NSString* tmpFormat = [[directoryPath 
										stringByAppendingPathComponent:
										[NSString stringWithFormat:@"%@-%d", fileNameWithNOExt, suffix]] 
									   stringByStandardizingPath];
				
				appendExtFileName = [[NSMutableString alloc] initWithString:tmpFormat];
				[appendExtFileName appendString:extentName];
				// For MemoryLeak
				[tmpFilePath release];
				tmpFilePath = [appendExtFileName copy];
				[appendExtFileName release];
				// MemoryLeak end.
				
			}			
			[fm createFileAtPath:tmpFilePath contents:[NSData data] attributes:nil];
			[filePath release];
			filePath = [tmpFilePath retain];
			// For MemoryLeak
			[tmpFilePath release];
			 // MemoryLeak end.
			
			file = [[NSFileHandle fileHandleForWritingAtPath:filePath] retain];
			[pool release];
		}
		[file writeData:data];
		
		if ([delegate respondsToSelector:@selector(download: didReceiveDataOfLength:)])
		{
			[delegate download:self didReceiveDataOfLength:[data length]];
		}
	}
	@catch (NSException *e)
	{
		[connection cancel];
		[delegate download:self didCancelBecauseOf:e];
	}
}

- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
	[delegate downloadDidFinish:self];
}

- (BOOL)connection:(NSURLConnection *)connection 
canAuthenticateAgainstProtectionSpace : (NSURLProtectionSpace *)protectionSpace
{
	// AR17635 start.
	return YES;
}
- (void)connection:(NSURLConnection *)connection 
didReceiveAuthenticationChallenge:(NSURLAuthenticationChallenge *)challenge
{
	// AR17635
	// ServerTrust
	if ([challenge.protectionSpace.authenticationMethod isEqualToString:NSURLAuthenticationMethodServerTrust])
	{
		[challenge.sender useCredential:[NSURLCredential credentialForTrust:challenge.protectionSpace.serverTrust] 
			 forAuthenticationChallenge:challenge];
	} else {
		self.needAuthen = YES;
		[challenge.sender cancelAuthenticationChallenge:challenge];
	}		
	// AR17635 end.
}
@end
