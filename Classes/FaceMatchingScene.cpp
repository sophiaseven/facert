//
//  Sophia Hannah

#include "FaceMatchingScene.h"
#include "SimpleAudioEngine.h"
#include "Config.h"
#include "MyMenuItem.h"
#include "HelloWorldScene.h"
#include "ScoreScene.h"

#define SMALL_IMAGE_NUM 20
#define FACE_LEVEL_MAX 3
int cardrandom (int i) {  std::srand(time(NULL)); return std::rand() % i;}

using namespace CocosDenshion;


CCScene* FaceMatchingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FaceMatchingScene *layer = FaceMatchingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FaceMatchingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    setTouchEnabled(true);
    SimpleAudioEngine::sharedEngine()->preloadEffect("tone4.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("pop3.mp3");

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // Set scale ratio
    Config::setScaleFactor(winSize);
    
    // Set background
    CCSprite* spBG = CCSprite::create("second.png");
    Config::setScale(spBG);
    spBG->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(spBG);
    
    float h = winSize.height*0.07;
    
    MyMenuItem *home = MyMenuItem::create("btn_home2.png",  this, menu_selector(FaceMatchingScene::menuHome));
    Config::setScale(home);
    home->setPosition(ccp(winSize.width*0.07, h));
    
    MyMenuItem *next = MyMenuItem::create("btn_arrow.png", this, menu_selector(FaceMatchingScene::menuNext));
    Config::setScale(next);
    next->setPosition(ccp(winSize.width*0.9, winSize.height*0.9));
    
    MyMenuItem *stop = MyMenuItem::create("btn_pause.png", this, menu_selector(FaceMatchingScene::menuStop));
    Config::setScale(stop);
    stop->setPosition(ccp(winSize.width*0.93, h));
    
    CCMenu *menu = CCMenu::create(home, next, stop,  NULL);
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
    
    CCSprite* spLevel = CCSprite::create("btn_level.png");
    Config::setScale(spLevel);
    spLevel->setPosition(ccp(winSize.width*0.5, winSize.height*0.9));
    this->addChild(spLevel);
    
    m_lbLevel = CCLabelTTF::create("Level 1", "Marker Felt", 80);
    m_lbLevel->setPosition(ccp(winSize.width*0.5, winSize.height*0.9));
    m_lbLevel->setColor(ccc3(255, 255, 255));
    Config::setScale(m_lbLevel);
    addChild(m_lbLevel, 11);

    m_spSolve1 = CCSprite::create("btn_rect.png");
    this->addChild(m_spSolve1, 5);

//    m_spSolve2 = CCSprite::create("btn_rect.png");
//    this->addChild(m_spSolve2, 5);

    
    m_aryFaces = new CCArray();

    setScore(0);
    m_nRound = 1;
    setLevel(1);
    
    return true;
}
void FaceMatchingScene::setLevel(int n)
{
    if (m_aryFaces) {
        for (int i = m_aryFaces->count() - 1; i >= 0; i--) {
            CCSprite* sp = (CCSprite*)m_aryFaces->objectAtIndex(i);
            removeChild(sp, true);
            m_aryFaces->removeObject(sp);
        }
    }

    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    CCShaderCache::sharedShaderCache()->purgeSharedShaderCache();
    CCDirector::sharedDirector()->purgeCachedData();
    
    m_nLevel = n;
    m_bSolved = false;
    
    char temp[20];
    sprintf(temp, "Level %d", m_nLevel);
    m_lbLevel->setString(temp);
    
    m_nShapeNum = 5;
    m_fImageScale = 0.6;
    int m_nStart, m_nEnd;
    
    if(m_nLevel == 2)
    {
        m_nStart = SMALL_IMAGE_NUM / 2 * (int)(arc4random() % 2);
        m_nEnd = m_nStart + SMALL_IMAGE_NUM / 2;
    }
    else
    {
        m_nStart = 0;
        m_nEnd = SMALL_IMAGE_NUM;
    }
    if (m_nLevel == 3) {
        m_nShapeNum = 9;
        m_fImageScale = 0.45;
    }

//    if (m_nLevel > 1) {
//        nImageNum = 10;
//    }
    int mapTemp[SMALL_IMAGE_NUM];
    std::vector<int> myvector;
    for (int i = m_nStart; i < m_nEnd; i++) {
        myvector.push_back(i);
    }
    std::random_shuffle(myvector.begin(), myvector.end());
    std::random_shuffle(myvector.begin(), myvector.end(), cardrandom);
    int index = 0;
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
        mapTemp[index] = *it; index++;
    }
    
    
    for (int i = 0; i < m_nShapeNum; i++) {
        m_map[i] = mapTemp[i];
    }
    int nRdm = arc4random() % m_nShapeNum;
    int nCenter = 4;
    if (nRdm == nCenter) {
        nRdm -= 1;
    }
    
    m_map[nRdm] = m_map[nCenter];
    
    m_nAnswer = nRdm;

    float x = 0, y = 0;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    
    for(int i = 0; i < m_nShapeNum; i++)
    {
        CCSprite* sp = CCSprite::create("shape.png");
        Config::setScale(sp);
        
        if (m_nLevel < 3) {
            if (i == 4) {
                x = winSize.width * 0.5;
                y = winSize.height * 0.45;
            }
            else if( i == 0){
                x = winSize.width * 0.2;
                y = winSize.height * 0.68;
            }
            else if( i == 1){
                x = winSize.width * 0.8;
                y = winSize.height * 0.68;
            }
            else if( i == 2){
                x = winSize.width * 0.2;
                y = winSize.height * 0.22;
            }
            else if( i == 3){
                x = winSize.width * 0.8;
                y = winSize.height * 0.22;
            }
        }
        else {
            if (i % 3 == 0)
                x = winSize.width * 0.2;
            else if(i % 3 == 1)
                x = winSize.width * 0.5;
            else if(i % 3 == 2)
                x = winSize.width * 0.8;
            
            if (i / 3 == 0)
                y = winSize.height * 0.72;
            else if (i / 3 == 1)
                y = winSize.height * 0.45;
            else if (i / 3 == 2)
                y = winSize.height * 0.18;
        }
        m_pt[i] = ccp(x, y);
        
        char temp[20] = {0};
        sprintf(temp, "%d.png", m_map[i]);
        
        CCSprite* spTemp = CCSprite::create(temp);
        Config::setScale(spTemp);
        spTemp->setAnchorPoint(ccp(1, 1));
        
        CCSprite* spMask = CCSprite::create("mask.png");
        Config::setScale(spMask);
        
        
        CCSprite* sss = maskedSpriteWithSprite(spTemp, spMask);
        this->addChild(sss, 2);
        sss->setTag(i);
        sss->setPosition(m_pt[i]);
        sss->setScaleX(sss->getScaleX() * m_fImageScale);
        sss->setScaleY(sss->getScaleY() * m_fImageScale);
        
        sp->setAnchorPoint(ccp(0.0, 0.0));
        sss->addChild(sp);
        m_aryFaces->addObject(sss);
    }

    CCSprite* sp = (CCSprite*) m_aryFaces->objectAtIndex(nCenter);
    
    Config::setScale(m_spSolve1);
    m_spSolve1->setScaleY(m_spSolve1->getScaleY() * m_fImageScale);
    m_spSolve1->setScaleX(m_spSolve1->getScaleX() * m_fImageScale);
    
//    Config::setScale(m_spSolve2);
//    m_spSolve2->setScaleY(m_spSolve2->getScaleY() * m_fImageScale);
//    m_spSolve2->setScaleX(m_spSolve2->getScaleX() * m_fImageScale);

    m_spSolve1->setVisible(true);
//    m_spSolve2->setVisible(false);
    m_spSolve1->setPosition(sp->getPosition());

}

void FaceMatchingScene::setRound(int round)
{
    m_nAnswer = -1;
//    m_spSolve1->setVisible(false);
//    m_spSolve2->setVisible(false);
    
    if (m_nSelected >= 0 && m_nSelected < m_aryFaces->count()) {
        CCSprite* sprite = (CCSprite*)m_aryFaces->objectAtIndex(m_nSelected);
        removeChild(sprite);

    }

    CCSprite* spCenter = (CCSprite*)m_aryFaces->objectAtIndex(4);
    CCPoint ptCenter = spCenter->getPosition();
    m_aryFaces->removeObject(spCenter);
    removeChild(spCenter);

    if(m_nRound > m_nShapeNum - 1)
    {
        m_nLevel++;
        if (m_nLevel == FACE_LEVEL_MAX + 1) {
        
            Score::sharedInstance()->updateMatchingScore(HelloWorld::userName(), m_nScore);
        //        Score::sharedInstance()->storeMatchingScoreToProfile();
        
            CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,ScoreScene::scene()));
        }
        else{
            setLevel(m_nLevel);
            m_nRound = 1;
            

        }
    }
    else
    {
//        setLevel(m_nLevel);

        if (m_nLevel <= FACE_LEVEL_MAX) {
            
            while (1)
            {
                int i = arc4random() % m_nShapeNum;
                if (m_map[i] != -1 && i != 4) {
                    m_nAnswer = i;

                    char temp[20] = {0};
                    sprintf(temp, "%d.png", m_map[i]);
                    
                    CCSprite* spTemp = CCSprite::create(temp);
                    Config::setScale(spTemp);
                    spTemp->setAnchorPoint(ccp(1, 1));
                    
                    CCSprite* spMask = CCSprite::create("mask.png");
                    Config::setScale(spMask);
                    
                    
                    CCSprite* sss = maskedSpriteWithSprite(spTemp, spMask);
                    this->addChild(sss, 2);
                    sss->setTag(4);
                    sss->setPosition(ptCenter);
                    sss->setScaleX(sss->getScaleX() * m_fImageScale);
                    sss->setScaleY(sss->getScaleY() * m_fImageScale);
                    
                    CCSprite* sp = CCSprite::create("shape.png");
                    Config::setScale(sp);
                    sp->setAnchorPoint(ccp(0.0, 0.0));
                    sss->addChild(sp);
                    
                    m_aryFaces->insertObject(sss, 4);
                    break;
                }
            }

        }
        m_nSelected = -1;

    }
}
void FaceMatchingScene::menuHome(CCObject* pSender)
{
//    removeAllChildrenWithCleanup(true);
    Score::sharedInstance()->updateMatchingScore(HelloWorld::userName(), m_nScore);
//    Score::sharedInstance()->storeMatchingScoreToProfile();
    
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,HelloWorld::scene()));

}
void FaceMatchingScene::menuNext(CCObject* pSender)
{
    nextLevel();
}
void FaceMatchingScene::menuStop(CCObject* pSender)
{
    
}


void FaceMatchingScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    m_nSelected = -1;

    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    for (int i = 0; i < m_nShapeNum; i++) {
        CCSprite* sprite = (CCSprite*)m_aryFaces->objectAtIndex(i);
        if(sprite->boundingBox().containsPoint(location))
        {
            int nIdx = sprite->getTag();
            if (nIdx == 4) {
                return;
            }
            m_nSelected = nIdx;
            m_ptSelectedOri = sprite->getPosition();
            sprite->setZOrder(100);
            break;
        }
    }
}
void FaceMatchingScene::ccTouchesMoved(CCSet *touches, CCEvent *pEvent)
{
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    if (m_nSelected >= 0) {
        CCSprite* sprite = (CCSprite*)m_aryFaces->objectAtIndex(m_nSelected);
        sprite->setPosition(location);
    }
}

void FaceMatchingScene::ccTouchesEnded(CCSet *touches, CCEvent *pEvent)
{
    if (m_nSelected < 0)
        return;
    
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    CCSprite* centerFace = (CCSprite*)m_aryFaces->objectAtIndex(4);

    CCPoint pt = m_ptSelectedOri;
    CCSprite* sprite = (CCSprite*)m_aryFaces->objectAtIndex(m_nSelected);

    if (centerFace->boundingBox().containsPoint(location)) {
        if (m_nAnswer == m_nSelected) {
            m_map[m_nSelected] = -1;
            pt = centerFace->getPosition();
            
            sprite->runAction(CCMoveTo::create(0.3, pt));

            success();
        
        }
        else {
            sprite->runAction(CCMoveTo::create(0.3, pt));
            
            m_nSelected = -1;
           
            fail();
        }

    }
    else{
        sprite->runAction(CCMoveTo::create(0.3, pt));
        m_nSelected = -1;

    }
}

void FaceMatchingScene::success()
{
    if (m_nRound >= m_nShapeNum - 1) {
        SimpleAudioEngine::sharedEngine()->playEffect("complete.mp3");
    }
    else
        SimpleAudioEngine::sharedEngine()->playEffect("correct.wav");

    m_bSolved = true;
    
    if(m_nLevel == 1)
        m_nScore += 5;
    else if(m_nLevel == 2)
        m_nScore += 10;
    else if(m_nLevel == 3)
        m_nScore += 15;
    
    
    setScore(m_nScore);
    
    scheduleOnce(schedule_selector(FaceMatchingScene::nextLevel), 0.3);
}

void FaceMatchingScene::fail()
{
    SimpleAudioEngine::sharedEngine()->playEffect("incorrect.mp3");

    if(m_bSolved)
        return;
    
    scheduleOnce(schedule_selector(FaceMatchingScene::retry), 0.3);

}
void FaceMatchingScene::setScore(int n)
{
    m_nScore = n;
    char temp[20] = {0};
    sprintf(temp, "%d", n);
    m_lbScore->setString(temp);
}
void FaceMatchingScene::nextLevel()
{
    setRound(++m_nRound);
}

void FaceMatchingScene::retry()
{
//    m_spSolve2->setVisible(false);

}


