//
//  TrainingScene.cpp
//
//
// Sophia Hannah
//

#include "TrainingScene.h"
#include "SimpleAudioEngine.h"
#include "Config.h"
#include "MyMenuItem.h"
#include "HelloWorldScene.h"
#import <CoreImage/CoreImage.h>
#include "MyGameBride.h"
#include "ScoreScene.h"

#define LEVEL_NUM   20
#define LEVEL_TIME 30
#define INTERVAL (1/10.0f)
#define FADE_INTERVAL 1
#define HIGHLIGHT_OPACITY 170

int g_nLevelTarget[LEVEL_NUM] = {20, 50, 90, 140, 200, 270, 350};

using namespace CocosDenshion;

int g_tempInfo[5] = {0,0,0,0,0};
int g_nEye = 0;

int TrainingScene::m_totalScore = 0;

Flower* Flower::create(const char *pszFileName)
{
    Flower *pobSprite = new Flower();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        
        pobSprite->autorelease();
        
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;
}

void Flower::move()
{
    this->setOpacity(0);
    this->runAction(CCFadeIn::create(1));

//    m_ptOri = getPosition();
    m_nFrames = 0;
//    schedule(schedule_selector(Flower::animate), 1/10.0);
}
void Flower::moveSpiritWidthOrientation(int move)
{
    CCPoint pt = getPosition();
    float d = 6 * Config::getxScale();
	switch (move) {
		case GameMoveTopEnum:
			pt.y += d;
			break;
		case GameMoveBottomEnum:
			pt.y -= d;
			break;
		case GameMoveLeftEnum:
			pt.x -= d;
			break;
		case GameMoveRightEnum:
			pt.x += d;
			break;
        default:
            break;
	}
    float deltax = 60 * Config::getxScale();
    float deltay = 40 * Config::getyScale();

    CCRect rc = CCRect(m_ptOri.x - deltax, m_ptOri.y - deltay, deltax*2, deltay*2);
    if (rc.containsPoint(pt) == false) {
        if(rc.origin.x > pt.x)
        {
            m_nDirect = GameMoveRightEnum ;
            moveSpiritWidthOrientation(m_nDirect);
        }else if(rc.origin.x + rc.size.width < pt.x)
        {
            m_nDirect = GameMoveLeftEnum ;
            moveSpiritWidthOrientation(m_nDirect);
        }else if(rc.origin.y > pt.y)
        {
            m_nDirect = GameMoveTopEnum ;
            moveSpiritWidthOrientation(m_nDirect);
        }else if(rc.origin.y + rc.size.height < pt.y)
        {
            m_nDirect = GameMoveBottomEnum ;
            moveSpiritWidthOrientation(m_nDirect);
        }
//        m_nDirect = arc4random() % 4;
//        moveSpiritWidthOrientation(m_nDirect);
    }
    else
        setPosition(pt);
}

void Flower::animate()
{
    
    m_nFrames ++;
    if (m_nFrames % 3 == 0) {
        m_nDirect = arc4random() % 4 ;
    }
    moveSpiritWidthOrientation(m_nDirect);
}

void Flower::disappear()
{
    
}



CCScene* TrainingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TrainingScene *layer = TrainingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TrainingScene::init()
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
    CCSprite *background = CCSprite::create("second.png");
    Config::setScale(background);
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background);
    
//    CCSprite* spLevel = CCSprite::create("btn_level.png");
//    Config::setScale(spLevel);
//    spLevel->setPosition(ccp(winSize.width*0.5, winSize.height*0.9));
//    this->addChild(spLevel);
//    
//    m_lbLevel = CCLabelTTF::create("Level 1", "Marker Felt", 80);
//    m_lbLevel->setPosition(ccp(winSize.width*0.5, winSize.height*0.9));
//    m_lbLevel->setColor(ccc3(255, 255, 255));
//    Config::setScale(m_lbLevel);
//    addChild(m_lbLevel, 11);

    
    float h = winSize.height*0.07;
    
    MyMenuItem *home = MyMenuItem::create("btn_home2.png",  this, menu_selector(TrainingScene::menuHome));
    Config::setScale(home);
    home->setPosition(ccp(winSize.width*0.1, h));
    
    MyMenuItem *prev = MyMenuItem::create("btn_prev.png", this, menu_selector(TrainingScene::menuPrev));
    Config::setScale(prev);
    prev->setPosition(ccp(winSize.width*0.7, h));
    
    MyMenuItem *next = MyMenuItem::create("btn_next.png", this, menu_selector(TrainingScene::menuNext));
    Config::setScale(next);
    next->setPosition(ccp(winSize.width*0.8, h));
    
    m_bPaused = false;
    
    CCMenuItemImage* item1 = CCMenuItemImage::create("btn_pause.png", "btn_pause.png");
    CCMenuItemImage* item2 = CCMenuItemImage::create("btn_stop.png", "btn_stop.png");
    CCMenuItemToggle* pause = CCMenuItemToggle::createWithTarget(this, menu_selector(TrainingScene::menuStop), item1, item2, NULL);
    Config::setScale(pause);
    pause->setPosition(ccp(winSize.width*0.93, h));

//    CCMenu *menu = CCMenu::create(home, prev, next, pause,  NULL);
    CCMenu *menu = CCMenu::create(home, next, pause,  NULL);
    menu->setPosition( ccp( 0, 0) );
    this->addChild(menu);
    
    
    CCSprite* spScoreboard = CCSprite::create("scoreboard.png");
    Config::setScale(spScoreboard);
    spScoreboard->setPosition(ccp(winSize.width*0.15, winSize.height*0.9));
    this->addChild(spScoreboard);
    
    m_lbScore = CCLabelTTF::create("0", "Marker Felt", 80);
    m_lbScore->setPosition(ccp(winSize.width*0.15, winSize.height*0.9));
    m_lbScore->setColor(ccc3(7, 75, 0));
    
    Config::setScale(m_lbScore);
    addChild(m_lbScore, 11);
    
    m_fImageScale = 1.5;
    
    CCSprite* spShape = CCSprite::create("shape.png");
    Config::setScale(spShape);
    spShape->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
    this->addChild(spShape, 3);
    spShape->setScaleX(spShape->getScaleX() * m_fImageScale);
    spShape->setScaleY(spShape->getScaleY() * m_fImageScale);

    m_aryLeftFlowers = new CCArray();
    m_aryRightFlowers = new CCArray();
    
//    m_spHand = CCSprite::create("hand.png");
//    Config::setScale(m_spHand);
//    m_spHand->setPosition(ccp(winSize.width*0.7, winSize.height * 0.5));
//    m_spHand->runAction(CCRepeatForever::create(CCSequence::create(CCFadeOut::create(0.5),
//                                                                   CCFadeIn::create(0.5),
//                                                                   NULL)));
//    addChild(m_spHand,10);

    m_lbCongratulations = CCLabelTTF::create("Level Up!", "Marker Felt", 200);
    m_lbCongratulations->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
    m_lbCongratulations->setColor(ccc3(255, 0, 255));
    Config::setScale(m_lbCongratulations);
    addChild(m_lbCongratulations, 13);
    m_lbCongratulations->setOpacity(0);

    TrainingScene::setTotalScore(0);
    
    setLevel(1);
    
    return true;
}
void TrainingScene::setLevel(int n)
{
    for (int i = m_aryLeftFlowers->count() - 1; i >= 0; i--) {
        CCSprite* sp = (CCSprite*)m_aryLeftFlowers->objectAtIndex(i);
        sp->stopAllActions();
        removeChild(sp, true);
        m_aryLeftFlowers->removeObject(sp);
        sp = NULL;
    }
    for (int i = m_aryRightFlowers->count() - 1; i >= 0; i--) {
        CCSprite* sp = (CCSprite*)m_aryRightFlowers->objectAtIndex(i);
        sp->stopAllActions();
        removeChild(sp, true);
        m_aryRightFlowers->removeObject(sp);
        sp = NULL;
    }

    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCShaderCache::sharedShaderCache()->purgeSharedShaderCache();
    CCDirector::sharedDirector()->purgeCachedData();
    
    m_nLevel = n;
//    char temp1[20];
//    sprintf(temp1, "Level %d", m_nLevel);
//    m_lbLevel->setString(temp1);

    m_nFlowerNum = 1;
    m_bLeftEye = true;
    m_currentTime = 0;
    
    m_levelScore = 0;
    
    char temp[20] = {0};
    sprintf(temp, "%d.png", n);

    g_nEye = MyGameBride::shared()->getEyePointsWithImage(temp, g_tempInfo);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* m_spFace = new CCSprite();
    m_spFace->initWithFile(temp);
    Config::setScale(m_spFace);
    m_spFace->setAnchorPoint(ccp(1, 1));

    
//    m_spMask = CCSprite::create("mask.png");
    CCSprite* m_spMask = new CCSprite();
    m_spMask->initWithFile("mask.png");
    Config::setScale(m_spMask);

    if (m_spResult) {
        removeChild(m_spResult, true);
        m_spResult = NULL;
    }
    m_spResult = maskedSpriteWithSprite(m_spFace, m_spMask);
    this->addChild(m_spResult, 2);
    m_spResult->setPosition(ccp(winSize.width*0.5, winSize.height*0.5));
    m_spResult->setScaleX(m_spResult->getScaleX() * m_fImageScale);
    m_spResult->setScaleY(m_spResult->getScaleY() * m_fImageScale);

    if (m_spFace){
        m_spFace->release();
    }
    if (m_spMask){
        m_spMask->release();
    }

    
    m_leftEyeHighLight = CCSprite::create("eyes_mask.png");
    m_rightEyeHighLight = CCSprite::create("eyes_mask.png");
    Config::setScale(m_leftEyeHighLight);
    addChild(m_leftEyeHighLight,13);
    Config::setScale(m_rightEyeHighLight);
    addChild(m_rightEyeHighLight,13);
    
    ccColor3B eyeHighLightColor;
    eyeHighLightColor.r = 161;
    eyeHighLightColor.g = 98;
    eyeHighLightColor.b = 220;
    
    m_leftEyeHighLight->setColor(eyeHighLightColor);
    m_rightEyeHighLight->setColor(eyeHighLightColor);
    
    CCPoint ptFace = m_spResult->getPosition();
    
    float x = ptFace.x - m_spResult->boundingBox().size.width/2 ;
    float y = ptFace.y - m_spResult->boundingBox().size.height/2 ;
    
    CCPoint pt1 = CCPoint(g_tempInfo[0] * Config::getxScale() * m_fImageScale + x, g_tempInfo[1] * Config::getyScale() * m_fImageScale + y);
    CCPoint pt2 = CCPoint(g_tempInfo[2] * Config::getxScale() * m_fImageScale + x, g_tempInfo[3] * Config::getyScale() * m_fImageScale + y);
    
    m_leftEyeHighLight->setPosition(pt1);
    m_leftEyeHighLight->stopAllActions();
    m_leftEyeHighLight->setVisible(false);
    m_leftEyeHighLight->setOpacity(0);
    
    m_rightEyeHighLight->setPosition(pt2);
    m_rightEyeHighLight->stopAllActions();
    m_rightEyeHighLight->setVisible(false);
    m_rightEyeHighLight->setOpacity(0);
    
    start();

}
void TrainingScene::calcScore(int n)
{
//    if(TrainingScene::totalScore() >0 || n > 0)
        TrainingScene::setTotalScore(TrainingScene::totalScore() + n);
    m_levelScore += n;
    
    if(m_levelScore == 5)
    {
        createFlowers();
    }
    
    char temp[20] = {0};
    sprintf(temp, "%d", TrainingScene::totalScore());
    m_lbScore->setString(temp);

}

void TrainingScene::animateHighLight()
{
    if(m_currentTime >= LEVEL_TIME)
    {
        CCFadeTo *leftfadeIn = CCFadeTo::create(FADE_INTERVAL, 0);
        CCFadeTo *leftfadeOut = CCFadeTo::create(FADE_INTERVAL ,HIGHLIGHT_OPACITY);
        CCFadeTo *rightfadeIn = CCFadeTo::create(FADE_INTERVAL, 0);
        CCFadeTo *rightfadeOut = CCFadeTo::create(FADE_INTERVAL ,HIGHLIGHT_OPACITY);
        
        CCSequence *leftpulseSequence = CCSequence::create(leftfadeIn, leftfadeOut,NULL);
        CCSequence *rightpulseSequence = CCSequence::create(rightfadeIn, rightfadeOut,NULL);
        
        m_leftEyeHighLight->setVisible(true);
        m_rightEyeHighLight->setVisible(true);
        m_leftEyeHighLight->runAction(leftpulseSequence);
        m_rightEyeHighLight->runAction(rightpulseSequence);
        scheduleOnce(schedule_selector(TrainingScene::menuNext), FADE_INTERVAL * 2);
    }
    else
    {
        CCFadeTo *fadeOut = CCFadeTo::create(FADE_INTERVAL ,HIGHLIGHT_OPACITY);
        CCFadeTo *fadeIn = CCFadeTo::create(FADE_INTERVAL, 0);
        
        CCSequence *pulseSequence = CCSequence::create(fadeOut,fadeIn,NULL);
        if(m_bLeftEye)
        {
            m_leftEyeHighLight->setVisible(true);
            m_rightEyeHighLight->setVisible(false);
            m_leftEyeHighLight->stopAllActions();
            m_leftEyeHighLight->runAction(pulseSequence);
        }
        else
        {
            m_rightEyeHighLight->setVisible(true);
            m_leftEyeHighLight->setVisible(false);
            m_rightEyeHighLight->stopAllActions();
            m_rightEyeHighLight->runAction(pulseSequence);
        }
        
        m_bLeftEye = !m_bLeftEye;
    }
}

void TrainingScene::createFlowers()
{
    if(m_levelScore >= 5 || m_currentTime >= LEVEL_TIME / 3)
    {
        unschedule(schedule_selector(TrainingScene::createFlowers));
        for (int i = m_aryLeftFlowers->count() - 1; i >= 0; i--) {
            Flower* sp = (Flower*)m_aryLeftFlowers->objectAtIndex(i);
            sp->stopAllActions();
            removeChild(sp, true);
            m_aryLeftFlowers->removeObject(sp);
        }
        m_aryLeftFlowers->removeAllObjects();
        for (int i = m_aryRightFlowers->count() - 1; i >= 0; i--) {
            Flower* sp = (Flower*)m_aryRightFlowers->objectAtIndex(i);
            sp->stopAllActions();
            removeChild(sp, true);
            m_aryRightFlowers->removeObject(sp);
        }
        m_aryRightFlowers->removeAllObjects();
        schedule(schedule_selector(TrainingScene::animateHighLight), FADE_INTERVAL * 2);
        return;
    }
    
    
    float deltax = 60 * Config::getxScale();
    float deltay = 40 * Config::getyScale();

    CCPoint ptFace = m_spResult->getPosition();
    float x = ptFace.x - m_spResult->boundingBox().size.width/2 ;
    float y = ptFace.y - m_spResult->boundingBox().size.height/2 ;

    CCPoint pt1 = CCPoint(g_tempInfo[0] * Config::getxScale() * m_fImageScale + x, g_tempInfo[1] * Config::getyScale() * m_fImageScale + y);

    CCPoint pt2 = CCPoint(g_tempInfo[2] * Config::getxScale() * m_fImageScale + x, g_tempInfo[3] * Config::getyScale() * m_fImageScale + y);
    
    float faceWidth = g_tempInfo[4] * Config::getxScale();
    float delta = 0;//faceWidth * 0.15;
    
    if (g_nEye >= 2) {
        
        int nCurNum = m_aryLeftFlowers->count();
        
        int nAddNum = m_nFlowerNum - nCurNum;
        
        
        if (nCurNum == m_nFlowerNum)
            nAddNum = 0;
        else if (nCurNum > 0)
            nAddNum = 1;
        
        Flower* spSmallFlower;
        
        for (int i = 0; i < nAddNum; i++) {
            
            float x = pt1.x - delta / 2 + (delta / 5) * (arc4random() % 6);
            float y = pt1.y - delta / 2 + (delta / 5) * (arc4random() % 6);
            
//            if(arc4random() % 2 == 0)
//                spSmallFlower = Flower::create("flower.png");
//            else
                spSmallFlower = Flower::create("star.png");
            spSmallFlower->m_ptOri.x = x;
            spSmallFlower->m_ptOri.y = y;

            Config::setScale(spSmallFlower);
            
            x += pow(-1, arc4random() %2) * (int)(arc4random() % (int)deltax);
            y += pow(-1, arc4random() %2) * (int)(arc4random() % (int)deltay);
            
            spSmallFlower->setPosition(ccp(x, y));
            spSmallFlower->move();
            m_aryLeftFlowers->addObject(spSmallFlower);
            this->addChild(spSmallFlower, 14);
        }
        
        nCurNum = m_aryRightFlowers->count();
        nAddNum = m_nFlowerNum - nCurNum;

        if (nCurNum == m_nFlowerNum)
            nAddNum = 0;
        else if (nCurNum > 0)
            nAddNum = 1;
        
        for (int i = 0; i < nAddNum; i++) {

            float x = pt2.x - delta / 2 + (delta / 5) * (arc4random() % 6);
            float y = pt2.y - delta / 2 + (delta / 5) * (arc4random() % 6);
            
//            if(arc4random() % 2 == 0)
//                spSmallFlower = Flower::create("flower.png");
//            else
                spSmallFlower = Flower::create("star.png");
            spSmallFlower->m_ptOri.x = x;
            spSmallFlower->m_ptOri.y = y;
            
            Config::setScale(spSmallFlower);
            x += pow(-1, arc4random() %2) * (int)(arc4random() % (int)deltax);
            y += pow(-1, arc4random() %2) * (int)(arc4random() % (int)deltay);
            spSmallFlower->setPosition(ccp(x, y));
            spSmallFlower->move();
            m_aryRightFlowers->addObject(spSmallFlower);
            this->addChild(spSmallFlower, 14);
            
        }
    }
    

}
void TrainingScene::start()
{

    createFlowers();
    
    schedule(schedule_selector(TrainingScene::createFlowers), m_nFlowerNum * 4);

//    schedule(schedule_selector(TrainingScene::menuNext), LEVEL_TIME);

    
    schedule(schedule_selector(TrainingScene::updateScene), INTERVAL);


}
void TrainingScene::updateScene()
{
    m_currentTime += INTERVAL;
    
    for (int i = m_aryLeftFlowers->count() - 1; i >= 0; i--) {
        Flower* sp = (Flower*)m_aryLeftFlowers->objectAtIndex(i);
        sp->animate();
    }
    for (int i = m_aryRightFlowers->count() - 1; i >= 0; i--) {
        Flower* sp = (Flower*)m_aryRightFlowers->objectAtIndex(i);
        sp->animate();
    }

    
}

void TrainingScene::menuHome(CCObject* pSender)
{
//    removeAllChildrenWithCleanup(true);

    Score::sharedInstance()->updateTraningScore(HelloWorld::userName(), TrainingScene::totalScore());
//    Score::sharedInstance()->storeTraningScoreToProfile();

    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,HelloWorld::scene()));

}
void TrainingScene::menuPrev(CCObject* pSender)
{
    if (m_nLevel > 1) {
        m_nLevel--;
        setLevel(m_nLevel);
    }
}
void TrainingScene::menuNext(CCObject* pSender)
{
    unschedule(schedule_selector(TrainingScene::menuNext));
    Score::sharedInstance()->updateTraningScore(HelloWorld::userName(), TrainingScene::totalScore());
//    Score::sharedInstance()->storeTraningScoreToProfile();
    
//    unschedule(schedule_selector(TrainingScene::menuNext));
    m_leftEyeHighLight->stopAllActions();
    removeChild(m_leftEyeHighLight);
    m_rightEyeHighLight->stopAllActions();
    removeChild(m_rightEyeHighLight);
    
    unschedule(schedule_selector(TrainingScene::animateHighLight));
    
    if (m_nLevel < LEVEL_NUM - 1) {
        m_nLevel++;
        setLevel(m_nLevel);
    }
    else{
        
        CCUserDefault::sharedUserDefault()->setBoolForKey("Loggined", false);

//        removeAllChildrenWithCleanup(true);
        unschedule(schedule_selector(TrainingScene::animateHighLight));
         unschedule(schedule_selector(TrainingScene::updateScene));
        CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,ScoreScene::scene()));
    }
}
void TrainingScene::menuStop(CCObject* pSender)
{
    if (m_bPaused) {
        m_bPaused = false;
        if(m_currentTime >= LEVEL_TIME / 2)
            schedule(schedule_selector(TrainingScene::animateHighLight), FADE_INTERVAL * 2);
        else
            schedule(schedule_selector(TrainingScene::createFlowers), m_nFlowerNum * 4);
        schedule(schedule_selector(TrainingScene::updateScene), INTERVAL);

    }
    else{
        if(m_currentTime >= LEVEL_TIME / 2 )
            unschedule(schedule_selector(TrainingScene::animateHighLight));
        else
            unschedule(schedule_selector(TrainingScene::createFlowers));
        unschedule(schedule_selector(TrainingScene::updateScene));
        m_bPaused = true;
    }
}

void TrainingScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
//    if (m_spHand != NULL) {
//        removeChild(m_spHand, true);
//        m_spHand = NULL;
//
//    }
    
    bool bHit = false;
    for (int i = m_aryLeftFlowers->count() - 1; i >= 0; i--) {
        Flower* sprite = (Flower*)m_aryLeftFlowers->objectAtIndex(i);
        if(sprite->boundingBox().containsPoint(location))
        {
            
            CCScaleTo* act = CCScaleTo::create(0.2, sprite->getScaleX() * 3);
            CCFadeOut* act2 = CCFadeOut::create(0.1);
            sprite->runAction(CCSequence::create(act, act2, NULL));
            
            removeChild(sprite);
            m_aryLeftFlowers->removeObject(sprite);
            
            bHit = true;
            calcScore(1);
            break;
        }
    }
    
    if(!bHit){
        for (int i = m_aryRightFlowers->count() - 1; i >= 0; i--) {
            Flower* sprite = (Flower*)m_aryRightFlowers->objectAtIndex(i);
            if(sprite->boundingBox().containsPoint(location))
            {
                
                CCScaleTo* act = CCScaleTo::create(0.2, sprite->getScaleX() * 3);
                CCFadeOut* act2 = CCFadeOut::create(0.1);
                sprite->runAction(CCSequence::create(act, act2, NULL));
                
                removeChild(sprite);
                m_aryRightFlowers->removeObject(sprite);
                
                bHit = true;
                calcScore(1);
                break;
            }
        }
    }
    
    if (m_leftEyeHighLight->boundingBox().containsPoint(location) && m_leftEyeHighLight->isVisible()) {
        m_leftEyeHighLight->setVisible(false);
        calcScore(1);
    }
    else if (m_rightEyeHighLight->isVisible() && m_rightEyeHighLight->boundingBox().containsPoint(location)) {
        m_rightEyeHighLight->setVisible(false);
        calcScore(1);
    }
    
    
//    if(!bHit)
//        calcScore(-1);
//    else{
//        m_nEatItems++;
//        if (m_nEatItems == g_nLevelTarget[m_nLevel-1]) {
//            success();
//        }
//    }

}

void TrainingScene::success()
{
    unschedule(schedule_selector(TrainingScene::createFlowers));
    unschedule(schedule_selector(TrainingScene::updateScene));

    m_lbCongratulations->runAction(CCSequence::create(CCFadeIn::create(0.5),
                                                      CCFadeOut::create(0.5),
                                                      CCFadeIn::create(0.5),
                                                      CCFadeOut::create(0.5),
                                                      NULL));
    
    scheduleOnce(schedule_selector(TrainingScene::menuNext), 2);
}
