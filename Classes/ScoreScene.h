//
//  ScoreScene.h
//
// Sophia Hannah

#ifndef __FaceRecog__ScoreScene__
#define __FaceRecog__ScoreScene__

#include "cocos2d.h"

class ScoreScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuHome(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ScoreScene);
};

#endif /* defined(__FaceRecog__ScoreScene__) */
