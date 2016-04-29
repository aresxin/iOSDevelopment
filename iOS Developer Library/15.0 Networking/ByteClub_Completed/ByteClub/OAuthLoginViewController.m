
#import "OAuthLoginViewController.h"
#import "Dropbox.h"

@interface OAuthLoginViewController ()
@property (weak, nonatomic) IBOutlet UITextView *loginView;
@property (weak, nonatomic) IBOutlet UIButton *loginButton;
@property (nonatomic, strong) UIAlertView *tokenAlert;

@end

@implementation OAuthLoginViewController


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
}


- (IBAction)signIn:(id)sender
{
    // show alert view saying we are getting token
    _tokenAlert = [[UIAlertView alloc] initWithTitle:@"Getting token"
                                                            message:@"Logging into Dropbox"
                                                           delegate:nil
                                                  cancelButtonTitle:@"Cancel"
                                                  otherButtonTitles:nil];
    [_tokenAlert show];

    // move on to step 2 of oauth token acquisation
    [self getOAuthRequestToken];
}

# pragma mark - OAUTH 1.0a STEP 1
-(void)getOAuthRequestToken
{
    // OAUTH Step 1. Get request token.
    [Dropbox requestTokenWithCompletionHandler:^(NSData *data, NSURLResponse *response, NSError *error) {
        if (!error) {
            NSHTTPURLResponse *httpResp = (NSHTTPURLResponse*) response;
            if (httpResp.statusCode == 200) {
                
                NSString *responseStr = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
                
                /*
                 oauth_token The request token that was just authorized. The request token secret isn't sent back.
                 If the user chooses not to authorize the application,
                 they will get redirected to the oauth_callback URL with the additional URL query parameter not_approved=true.
                 */
                NSDictionary *oauthDict = [Dropbox dictionaryFromOAuthResponseString:responseStr];
                // save the REQUEST token and secret to use for normal api calls
                [[NSUserDefaults standardUserDefaults] setObject:oauthDict[oauthTokenKey] forKey:requestToken];
                [[NSUserDefaults standardUserDefaults] setObject:oauthDict[oauthTokenKeySecret] forKey:requestTokenSecret];
                [[NSUserDefaults standardUserDefaults] synchronize];
               
                
                NSString *authorizationURLWithParams = [NSString stringWithFormat:@"https://www.dropbox.com/1/oauth/authorize?oauth_token=%@&oauth_callback=byteclub://userauthorization",oauthDict[oauthTokenKey]];
                
                // escape codes
                NSString *escapedURL = [authorizationURLWithParams stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
                                
                [_tokenAlert dismissWithClickedButtonIndex:0 animated:NO];
                
                // opens to user auth page in safari
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:escapedURL]];

            } else {
                // HANDLE BAD RESPONSE //
                NSLog(@"unexpected response getting token %@",[NSHTTPURLResponse localizedStringForStatusCode:httpResp.statusCode]);
            }
        } else {
            // ALWAYS HANDLE ERRORS :-] //
        }
    }];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end