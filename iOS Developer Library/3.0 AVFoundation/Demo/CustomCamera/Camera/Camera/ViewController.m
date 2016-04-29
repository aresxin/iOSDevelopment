//
//  ViewController.m
//  Camera
//
//  Created by yangjinxin on 15/2/28.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "ViewController.h"
#import "CameraSource.h"
@interface ViewController ()
@property (nonatomic) CameraSource *camera;
@property (nonatomic, weak) IBOutlet  CameraPreviewView *cameraPreview;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
   //_camera = [CameraSource cameraWithPosition:AVCaptureDevicePositionBack delegate:nil];
    
//    AVCaptureVideoPreviewLayer *previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:_camera.session];
//    AVCaptureConnection *connection = [previewLayer connection];
//    connection.videoOrientation = AVCaptureVideoOrientationPortrait;
//    previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
//    [previewLayer setFrame:_cameraPreview.bounds];
//    [_cameraPreview.layer  addSublayer:previewLayer];
    
    //[_camera startRunning];
    
//    _camera = [CameraSource cameraWithPosition:AVCaptureDevicePositionBack delegate:nil];
//    AVCaptureVideoPreviewLayer *previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:_camera.session];
//    AVCaptureConnection *connection = [previewLayer connection];
//    connection.videoOrientation = AVCaptureVideoOrientationPortrait;
//    previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
//    [previewLayer setFrame:_cameraPreview.bounds];
//    [_cameraPreview.layer  addSublayer:previewLayer];
//    
//    [_camera startRunning];

}

- (void)viewDidAppear:(BOOL)animated
{
//    _camera = [CameraSource cameraWithPosition:AVCaptureDevicePositionBack delegate:nil];
//    self.cameraPreview.cameraSource = self.camera;
//   
//    _cameraPreview.backgroundColor = [UIColor redColor];
//    _cameraPreview.layer.frame     = _cameraPreview.layer.bounds;
//    [_camera startRunning];
//    NSLog(@"_cameraPreview.bounds is %@",NSStringFromCGRect(_cameraPreview.bounds));
//    NSLog(@"_cameraPreview.bounds is %@",NSStringFromCGRect(_cameraPreview.layer.bounds));
    _camera = [CameraSource cameraWithPosition:AVCaptureDevicePositionBack delegate:nil];
    AVCaptureVideoPreviewLayer *previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:_camera.session];
    AVCaptureConnection *connection = [previewLayer connection];
    connection.videoOrientation = AVCaptureVideoOrientationPortrait;
    previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    [previewLayer setFrame:_cameraPreview.bounds];
    [_cameraPreview.layer  addSublayer:previewLayer];
    
    [_camera startRunning];
}

- (void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)actionBackCamera:(id)sender
{
    _camera.backCameraActive = !_camera.backCameraActive;
}


- (IBAction)actionFlash:(id)sender
{
    _camera.flashActive = !_camera.flashActive;
}

- (IBAction)actionTakePhoto:(id)sender
{
    [_camera shutterCamera];
}
@end
