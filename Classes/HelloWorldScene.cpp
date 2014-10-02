
// Sophia Hannah

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Config.h"
#include "MyMenuItem.h"
#include "TrainingScene.h"
#include "FaceMatchingScene.h"
#include "ScoreScene.h"
#include "MyGameBride.h"

#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       80

bool bLoggined = false;

using namespace CocosDenshion;

std::string HelloWorld::m_userName;

static CCRect getRect(CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    setTouchEnabled(true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLog("WinSize : %f, %f", winSize.width, winSize.height);
    
    // Set scale ratio
    Config::setScaleFactor(winSize);
    
    // Set background
    CCSprite *background = CCSprite::create("first.png");
    Config::setScale(background);
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background);


    MyMenuItem *training = MyMenuItem::create("btn_train.png",  this, menu_selector(HelloWorld::menuTraining));
    Config::setScale(training);
    training->setPosition(ccp(winSize.width*0.3, winSize.height*0.6));
    
    MyMenuItem *face = MyMenuItem::create("btn_face.png", this, menu_selector(HelloWorld::menuFaceMatching));
    Config::setScale(face);
    face->setPosition(ccp(winSize.width*0.65, winSize.height*0.55));

    float h = winSize.height*0.07;
    
    MyMenuItem *home = MyMenuItem::create("btn_home.png",  this, menu_selector(HelloWorld::menuHome));
    Config::setScale(home);
    home->setPosition(ccp(winSize.width*0.14, h));
    
    MyMenuItem *exit = MyMenuItem::create("btn_exit.png", this, menu_selector(HelloWorld::menuExit));
    Config::setScale(exit);
    exit->setPosition(ccp(winSize.width*0.35, h));
    
    MyMenuItem *score = MyMenuItem::create("btn_score.png", this, menu_selector(HelloWorld::menuScoreHistory));
    Config::setScale(score);
    score->setPosition(ccp(winSize.width*0.6, h));

    CCMenu *menu = CCMenu::create(training, face, home, exit, score,  NULL);
    menu->setPosition( ccp( 0, 0) );
    this->addChild(menu);

//    m_tfUsername = CCTextFieldTTF::textFieldWithPlaceHolder("please input your name.", FONT_NAME, FONT_SIZE);
//    Config::setScale(m_tfUsername);
//    m_tfUsername->setPosition(ccp(winSize.width*0.5, winSize.height*0.3));
//    m_tfUsername->setDelegate(this);
//    this->addChild(m_tfUsername);

    scheduleOnce(schedule_selector(HelloWorld::showInputName), 1);
    return true;
}
void HelloWorld::showInputName()
{
//    bool bLoggined = CCUserDefault::sharedUserDefault()->getBoolForKey("Loggined", true);

    if(bLoggined == false){
        
        Score::sharedInstance()->loadTraningScoreFromProfile();
        Score::sharedInstance()->loadMatchingScoreFromProfile();

        MyGameBride::shared()->inputUserName(&HelloWorld::setUserName);
        bLoggined = true;
//        CCUserDefault::sharedUserDefault()->setBoolForKey("Loggined", false);
    }
}

void HelloWorld::menuHome(CCObject* pSender)
{
    
}
void HelloWorld::btnExit()
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

void HelloWorld::menuExit(CCObject* pSender)
{
//    CCUserDefault::sharedUserDefault()->setBoolForKey("Loggined", true);

    Score::sharedInstance()->storeTraningScoreToProfile();
    Score::sharedInstance()->storeMatchingScoreToProfile();
    Score::deleteInstance();
    scheduleOnce(schedule_selector(HelloWorld::btnExit), 0.5);
    return;
    

}
void HelloWorld::menuScoreHistory(CCObject* pSender)
{
//    removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5,ScoreScene::scene()));
    


}
void HelloWorld::menuTraining(CCObject* pSender)
{
//    removeAllChildrenWithCleanup(true);
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5,TrainingScene::scene()));
    
}
void HelloWorld::menuFaceMatching(CCObject* pSender)
{
//    removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5,FaceMatchingScene::scene()));

}

//void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
//{
//    CCTouch* touch = (CCTouch*)( touches->anyObject() );
//    CCPoint location = touch->getLocationInView();
//    location = CCDirector::sharedDirector()->convertToGL(location);
//    
//    if (m_tfUsername->boundingBox().containsPoint(location)) {
//        m_tfUsername->attachWithIME();
//    }
//    else{
//        m_tfUsername->detachWithIME();
//    }
//    
//    
//}
//
//void HelloWorld::keyboardWillShow(CCIMEKeyboardNotificationInfo& info)
//{
//    if (! m_tfUsername)
//        return;
//    
//    CCRect rectTracked = getRect(m_tfUsername);
//    
//    // if the keyboard area doesn't intersect with the tracking node area, nothing need to do.
//    if (! rectTracked.intersectsRect(info.end))
//    {
//        return;
//    }
//    
//    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
//    adjustVert = info.end.getMaxY() - rectTracked.getMinY();
//    
//    // move all the children node of KeyboardNotificationLayer
//    CCArray * children = getChildren();
//    CCNode * node = 0;
//    int count = children->count();
//    CCPoint pos;
//    for (int i = 0; i < count; ++i)
//    {
//        node = (CCNode*)children->objectAtIndex(i);
//        pos = node->getPosition();
//        pos.y += adjustVert;
////        node->setPosition(pos);
//        node->runAction(CCMoveTo::create(0.2, pos));
//    }
//}
//void HelloWorld::keyboardWillHide(CCIMEKeyboardNotificationInfo& info)
//{
//    if (! m_tfUsername)
//        return;
//    
//    
//    // assume keyboard at the bottom of screen, calculate the vertical adjustment.
//    
//    // move all the children node of KeyboardNotificationLayer
//    CCArray * children = getChildren();
//    CCNode * node = 0;
//    int count = children->count();
//    CCPoint pos;
//    for (int i = 0; i < count; ++i)
//    {
//        node = (CCNode*)children->objectAtIndex(i);
//        pos = node->getPosition();
//        pos.y -= adjustVert;
////        node->setPosition(pos);
//        node->runAction(CCMoveTo::create(0.2, pos));
//    }
//}
