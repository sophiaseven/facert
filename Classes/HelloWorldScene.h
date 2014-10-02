// Sophia Hannah

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <string>

#include "Scores.h"

using namespace cocos2d;


class HelloWorld : public cocos2d::CCLayer //, public cocos2d::CCTextFieldDelegate, public CCIMEDelegate
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
//    CCTextFieldTTF* m_tfUsername;
//    float adjustVert;
    
    // a selector callback
    void menuHome(CCObject* pSender);
    void menuExit(CCObject* pSender);
    void menuScoreHistory(CCObject* pSender);
    void menuTraining(CCObject* pSender);
    void menuFaceMatching(CCObject* pSender);
    void btnExit();
    void showInputName();
    
    static void setUserName(const char * userName)
    {
        HelloWorld::m_userName = userName;
    }
    
    static std::string userName() { return m_userName;}
    
private:
    static std::string m_userName;
    
//    virtual void ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
//
//    virtual void keyboardWillShow(CCIMEKeyboardNotificationInfo& info) ;
//    virtual void keyboardWillHide(CCIMEKeyboardNotificationInfo& info) ;

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
