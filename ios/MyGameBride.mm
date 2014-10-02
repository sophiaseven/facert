//
//  Sophia Hannah
//

#import "MyGameBride.h"

#import  <Social/Social.h>
#import "AppController.h"
#import "RootViewController.h"

static MyGameBride *s_gc;
MyGameBride* MyGameBride::shared(){
    if (! s_gc) {
        s_gc = new MyGameBride();
    }
    return s_gc;
}
int MyGameBride::getEyePointsWithImage(char *lpImgName, int* pt)
{
    AppController* app = (AppController*)[UIApplication sharedApplication].delegate;
    return [app getEyePointsWithImage:lpImgName points:pt];
}
void MyGameBride::inputUserName(CallBack callback)
{
    AppController* app = (AppController*)[UIApplication sharedApplication].delegate;
    [app inputUserName:callback];
}

//void MyGameBride::share(int hscore){
//    AppController* app = (AppController*)[UIApplication sharedApplication].delegate;
//    [app showShareScreen:hscore];
//    
//}
//
//void MyGameBride::iRate(){
//    AppController* app = (AppController*)[UIApplication sharedApplication].delegate;
//    [app iRate];
//}
//
//void MyGameBride::bannerVisible(bool bVisible)
//{
//    AppController * app = (AppController*)[UIApplication sharedApplication].delegate;
//    [(RootViewController*)app.viewController bannerVisible:bVisible];
//}
