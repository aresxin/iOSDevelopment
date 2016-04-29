//
//  PhotosViewController.m
//  ByteClub
//
//  Created by Charlie Fulton on 7/28/13.
//  Copyright (c) 2013 Razeware. All rights reserved.
//

#import "PhotosViewController.h"
#import "PhotoCell.h"
#import "Dropbox.h"
#import "DBFile.h"

@interface PhotosViewController ()<UITableViewDelegate, UITableViewDataSource, UIImagePickerControllerDelegate, UINavigationControllerDelegate, NSURLSessionTaskDelegate>

@property (nonatomic, strong)
NSURLSessionUploadTask *uploadTask;
@property (weak, nonatomic) IBOutlet UIProgressView *progress;
@property (weak, nonatomic) IBOutlet UIView *uploadView;
@property (weak, nonatomic) IBOutlet UITableView *tableView;

@property (nonatomic, strong) NSArray *photoThumbnails;


@property (nonatomic, strong) NSURLSession *session;



@end

@implementation PhotosViewController

- (id)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    if (self) {
        // 1
        NSURLSessionConfiguration *config = [NSURLSessionConfiguration ephemeralSessionConfiguration];
        
        // 2
        [config setHTTPAdditionalHeaders:@{@"Authorization": [Dropbox apiAuthorizationHeader]}];
        
        // 3
        _session = [NSURLSession sessionWithConfiguration:config];
    }
    return self;
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    [self refreshPhotos];
}

- (void)refreshPhotos
{
  [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
  NSString *photoDir = [NSString stringWithFormat:@"https://api.dropbox.com/1/search/dropbox/%@/photos?query=.jpg",appFolder];
  NSURL *url = [NSURL URLWithString:photoDir];
  
  [[_session dataTaskWithURL:url completionHandler:^(NSData
                                                     *data, NSURLResponse *response, NSError *error) {
    if (!error) {
      NSHTTPURLResponse *httpResp =
      (NSHTTPURLResponse*) response;
      if (httpResp.statusCode == 200) {
        
        NSError *jsonError;
        NSArray *filesJSON = [NSJSONSerialization
                              JSONObjectWithData:data
                              options:NSJSONReadingAllowFragments
                              error:&jsonError];
        NSMutableArray *dbFiles =
        [[NSMutableArray alloc] init];
        
        if (!jsonError) {
          for (NSDictionary *fileMetadata in
               filesJSON) {
            DBFile *file = [[DBFile alloc]
                            initWithJSONData:fileMetadata];
            [dbFiles addObject:file];
          }
          
          [dbFiles sortUsingComparator:^NSComparisonResult(id obj1, id obj2) {
            return [obj1 compare:obj2];
          }];
          
          _photoThumbnails = dbFiles;
          
          dispatch_async(dispatch_get_main_queue(), ^{
            [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
            [self.tableView reloadData];
          });
        }
      } else {
        // HANDLE BAD RESPONSE //
      }
    } else {
      // ALWAYS HANDLE ERRORS :-] //
    }
  }] resume];
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - UITableViewDatasource and UITableViewDelegate methods


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return [_photoThumbnails count];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
   
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"PhotoCell";
    PhotoCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    
    DBFile *photo = _photoThumbnails[indexPath.row];
    
    if (!photo.thumbNail) {
        // only download if we are moving
        if (self.tableView.dragging == NO && self.tableView.decelerating == NO)
        {
            if(photo.thumbExists) {
                NSString *urlString = [NSString stringWithFormat:@"https://api-content.dropbox.com/1/thumbnails/dropbox%@?size=xl",photo.path];
                NSString *encodedUrl = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
                NSURL *url = [NSURL URLWithString:encodedUrl];
                NSLog(@"logging this url so no warning in starter project %@",url);
                
                // GO GET THUMBNAILS //
                
              [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
              NSURLSessionDataTask *dataTask = [_session dataTaskWithURL:url
                                                       completionHandler:^(NSData *data, NSURLResponse *response,
                                                                           NSError *error) {
                                                         if (!error) {
                                                           UIImage *image = [[UIImage alloc] initWithData:data];
                                                           photo.thumbNail = image;
                                                           dispatch_async(dispatch_get_main_queue(), ^{
                                                             [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
                                                             cell.thumbnailImage.image = photo.thumbNail;
                                                           });
                                                         } else {
                                                           // HANDLE ERROR //
                                                         }
                                                       }];
              [dataTask resume];
                
            }
        }
    }
    
    // Configure the cell...
    return cell;
}

- (IBAction)choosePhoto:(UIBarButtonItem *)sender
{
    UIImagePickerController *picker = [[UIImagePickerController alloc] init];
    picker.allowsEditing = NO;
    picker.delegate = self;
    [self presentViewController:picker animated:YES completion:nil];
}

#pragma mark - UIImagePickerControllerDelegate methods
- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    UIImage *image = info[UIImagePickerControllerOriginalImage];
    [self dismissViewControllerAnimated:YES completion:nil];
    [self uploadImage:image];
}

// stop upload
- (IBAction)cancelUpload:(id)sender {
  if (_uploadTask.state == NSURLSessionTaskStateRunning) {
    [_uploadTask cancel];
  }
}

- (void)uploadImage:(UIImage*)image
{
  NSData *imageData = UIImageJPEGRepresentation(image, 0.6);
  
  // 1
  NSURLSessionConfiguration *config = [NSURLSessionConfiguration defaultSessionConfiguration];
  config.HTTPMaximumConnectionsPerHost = 1;
  [config setHTTPAdditionalHeaders:@{@"Authorization": [Dropbox apiAuthorizationHeader]}];
  
  // 2
  NSURLSession *upLoadSession = [NSURLSession sessionWithConfiguration:config delegate:self delegateQueue:nil];
  
  // for now just create a random file name, dropbox will handle it if we overwrite a file and create a new name..
  NSURL *url = [Dropbox createPhotoUploadURL];
  
  NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:url];
  [request setHTTPMethod:@"PUT"];
  
  // 3
  self.uploadTask = [upLoadSession uploadTaskWithRequest:request fromData:imageData];
  
  // 4
  self.uploadView.hidden = NO;
  [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
  
  // 5
  [_uploadTask resume];
}

#pragma mark - NSURLSessionTaskDelegate methods

- (void)URLSession:(NSURLSession *)session
              task:(NSURLSessionTask *)task
   didSendBodyData:(int64_t)bytesSent
    totalBytesSent:(int64_t)totalBytesSent
totalBytesExpectedToSend:(int64_t)totalBytesExpectedToSend
{
  dispatch_async(dispatch_get_main_queue(), ^{
    [_progress setProgress:
     (double)totalBytesSent /
     (double)totalBytesExpectedToSend animated:YES];
  });
}

- (void)URLSession:(NSURLSession *)session
              task:(NSURLSessionTask *)task
didCompleteWithError:(NSError *)error
{
  // 1
  dispatch_async(dispatch_get_main_queue(), ^{
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
    _uploadView.hidden = YES;
    [_progress setProgress:0.5];
  });
  
  if (!error) {
    // 2
    dispatch_async(dispatch_get_main_queue(), ^{
      [self refreshPhotos];
    });
  } else {
    // Alert for error
  }
}


@end
