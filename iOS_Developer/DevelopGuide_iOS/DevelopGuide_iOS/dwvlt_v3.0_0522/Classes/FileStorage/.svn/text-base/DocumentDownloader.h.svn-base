//
//  DownloadDocument.h
//  DWViewer
//
//  Created by Neusoft on 10-10-22.
//
//

#import <Foundation/Foundation.h>

@class DocumentDownloader;

@protocol DocumentDownloaderDeleagte
- (void)downloadDidFinish:(DocumentDownloader *)download;
- (void)download:(DocumentDownloader *)download didCancelBecauseOf:(NSException *)exception;
- (void)download:(DocumentDownloader *)download didFailWithError:(NSError *)error;
@optional
- (void)download:(DocumentDownloader *)download didReceiveDataOfLength:(NSUInteger)length;
- (void)download:(DocumentDownloader *)download didReceiveResponse:(NSURLResponse *)response;

@end

// The controller which downloads a document specified by a url req.
@interface DocumentDownloader : NSObject
{
	id <DocumentDownloaderDeleagte, NSObject> delegate;
	NSString *directoryPath;
	NSString *filePath;
	NSURLRequest *request;
	NSFileHandle *file;
	NSURLConnection *con;
}
@property(nonatomic, retain) NSString *filePath;
// AR17635
@property(nonatomic, assign) BOOL needAuthen;

- (id)initWithRequest:(NSURLRequest *)req directory:(NSString *)dir delegate:(id<DocumentDownloaderDeleagte, NSObject>)dg;


- (void)dealloc;
- (void)cancel;

// NSURLConnection delegate
- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response;
- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error;
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data;
- (void)connectionDidFinishLoading:(NSURLConnection *)connection;

@end
