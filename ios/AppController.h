//
//  FaceRecogAppController.h
//  FaceRecog
//
//  Sophia Hannah
//

@class RootViewController;

#include "../type_func.h"

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    CallBack setUserName;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

-(int)getEyePointsWithImage:(char *)lpImgName points:(int*) pt;
- (void) inputUserName:(CallBack)callback;
@end

