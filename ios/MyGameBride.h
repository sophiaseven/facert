//
// 
//
//  Sophia Hannah
//
//

#ifndef MYGAMEBRIDG_H
#define MYGAMEBRIDG_H

#include "../type_func.h"

class MyGameBride
{
public:
    MyGameBride(){};
    ~MyGameBride(){};
    
    
    static MyGameBride* shared();
    
//    void iRate();
//    
//    void share(int gameScore);
//    
//    void bannerVisible(bool bVisible);
    int getEyePointsWithImage(char *lpImgName, int* pt);
    
    void inputUserName(CallBack callback);

};

#endif
