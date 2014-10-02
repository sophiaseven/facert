//
//  FaceRecogAppController.mm
//  By Sophia Hannah
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"

#import "RootViewController.h"

extern char* g_strUserName;

@implementation AppController

@synthesize window;
@synthesize viewController;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];

    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden: YES];

    cocos2d::CCApplication::sharedApplication()->run();
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

-(int)getEyePointsWithImage:(char *)lpImgName points:(int*) pt;
{
    int nEye = 0;
    NSString* strImage = [NSString stringWithFormat:@"%s", lpImgName];
    UIImage* img = [UIImage imageNamed:strImage];
    // draw a CI image with the previously loaded face detection picture
    CIImage* image = [CIImage imageWithCGImage:img.CGImage];
    
    // create a face detector - since speed is not an issue we'll use a high accuracy
    // detector
    CIDetector* detector = [CIDetector detectorOfType:CIDetectorTypeFace
                                              context:nil options:[NSDictionary dictionaryWithObject:CIDetectorAccuracyHigh forKey:CIDetectorAccuracy]];
    
    // create an array containing all the detected faces from the detector
    NSArray* features = [detector featuresInImage:image];
    
    // we'll iterate through every detected face.  CIFaceFeature provides us
    // with the width for the entire face, and the coordinates of each eye
    // and the mouth if detected.  Also provided are BOOL's for the eye's and
    // mouth so we can check if they already exist.
    for(CIFaceFeature* faceFeature in features)
    {
        // get the width of the face
        CGFloat faceWidth = faceFeature.bounds.size.width;
        pt[4] = faceWidth;
//        // create a UIView using the bounds of the face
//        UIView* faceView = [[UIView alloc] initWithFrame:faceFeature.bounds];
//        
//        // add a border around the newly created UIView
//        faceView.layer.borderWidth = 1;
//        faceView.layer.borderColor = [[UIColor redColor] CGColor];
//        
//        // add the new view to create a box around the face
//        [self.window addSubview:faceView];
//        
        if(faceFeature.hasLeftEyePosition)
        {
            nEye ++;
            pt[0] = faceFeature.leftEyePosition.x;
            pt[1] = faceFeature.leftEyePosition.y;

//            // create a UIView with a size based on the width of the face
//            UIView* leftEyeView = [[UIView alloc] initWithFrame:CGRectMake(faceFeature.leftEyePosition.x-faceWidth*0.15, faceFeature.leftEyePosition.y-faceWidth*0.15, faceWidth*0.3, faceWidth*0.3)];
//            // change the background color of the eye view
//            [leftEyeView setBackgroundColor:[[UIColor blueColor] colorWithAlphaComponent:0.3]];
//            // set the position of the leftEyeView based on the face
//            [leftEyeView setCenter:faceFeature.leftEyePosition];
//            // round the corners
//            leftEyeView.layer.cornerRadius = faceWidth*0.15;
//            // add the view to the window
//            [self.window addSubview:leftEyeView];
        }
        
        if(faceFeature.hasRightEyePosition)
        {
            nEye ++;
            pt[2] = faceFeature.rightEyePosition.x;
            pt[3] = faceFeature.rightEyePosition.y;
            

//            // create a UIView with a size based on the width of the face
//            UIView* leftEye = [[UIView alloc] initWithFrame:CGRectMake(faceFeature.rightEyePosition.x-faceWidth*0.15, faceFeature.rightEyePosition.y-faceWidth*0.15, faceWidth*0.3, faceWidth*0.3)];
//            // change the background color of the eye view
//            [leftEye setBackgroundColor:[[UIColor blueColor] colorWithAlphaComponent:0.3]];
//            // set the position of the rightEyeView based on the face
//            [leftEye setCenter:faceFeature.rightEyePosition];
//            // round the corners
//            leftEye.layer.cornerRadius = faceWidth*0.15;
//            // add the new view to the window
//            [self.window addSubview:leftEye];
        }
        
//        if(faceFeature.hasMouthPosition)
//        {
//            // create a UIView with a size based on the width of the face
//            UIView* mouth = [[UIView alloc] initWithFrame:CGRectMake(faceFeature.mouthPosition.x-faceWidth*0.2, faceFeature.mouthPosition.y-faceWidth*0.2, faceWidth*0.4, faceWidth*0.4)];
//            // change the background color for the mouth to green
//            [mouth setBackgroundColor:[[UIColor greenColor] colorWithAlphaComponent:0.3]];
//            // set the position of the mouthView based on the face
//            [mouth setCenter:faceFeature.mouthPosition];
//            // round the corners
//            mouth.layer.cornerRadius = faceWidth*0.2;
//            // add the new view to the window
//            [self.window addSubview:mouth];
//        }
    }
    return nEye;
}
- (void) inputUserName:(CallBack)callback{
    setUserName = callback;
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Please input your name."
                                                    message:nil
                                                   delegate:self
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
	alert.alertViewStyle = UIAlertViewStylePlainTextInput;
    alert.delegate = self;
    [alert show];

}
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    NSString* str = [[alertView textFieldAtIndex:0] text];
    char* lpStr = (char*)[str UTF8String];
    
    if (str.length > 0) {
        g_strUserName = lpStr;
        setUserName(lpStr);
    }
    else{
        [self inputUserName:setUserName];
    }
}
#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}


@end

