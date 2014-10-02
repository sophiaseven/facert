//
//  Sophia Hannah
//

#include "ScoreScene.h"
#include "HelloWorldScene.h"
#include "Config.h"
#include "MyMenuItem.h"
#include "SimpleAudioEngine.h"

#include <string>
#include <list>

#include "Scores.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* ScoreScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ScoreScene *layer = ScoreScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ScoreScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLog("WinSize : %f, %f", winSize.width, winSize.height);
    
    // Set scale ratio
    Config::setScaleFactor(winSize);
    
    // Set background
    CCSprite *background = CCSprite::create("scorebg.png");
    Config::setScale(background);
    background->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(background);
    
    CCSprite *table = CCSprite::create("scorescreen.png");
    Config::setScale(table);
    table->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(table);

    float h = winSize.height*0.07;
    
    MyMenuItem *home = MyMenuItem::create("btn_home2.png",  this, menu_selector(ScoreScene::menuHome));
    Config::setScale(home);
    home->setPosition(ccp(winSize.width*0.1, h));
    
    
    CCMenu *menu = CCMenu::create(home, NULL);
    menu->setPosition( ccp( 0, 0) );
    this->addChild(menu);
    

    int i = 0;
    for(std::list<ScoreData*>::iterator it = Score::sharedInstance()->traning()->begin(); it != Score::sharedInstance()->traning()->end(); it++ )
    {
        float y = 1125/1536.0 * winSize.height - 103/1536.0 * winSize.height * i;
        ScoreData * pScoreData = (ScoreData*)*it;
        
        CCLabelTTF* lbName = CCLabelTTF::create(pScoreData->name.c_str() , "Marker Felt", 50);
        lbName->setPosition(ccp(454/2048.0 * winSize.width, y));
        lbName->setColor(ccc3(0, 161, 236));
        Config::setScale(lbName);
        addChild(lbName, 11);

        char score[50] = {0};
        sprintf(score, "%d", pScoreData->score);
        CCLabelTTF* lbTrainig = CCLabelTTF::create(score, "Marker Felt", 50);
        lbTrainig->setPosition(ccp(826/2048.0 * winSize.width, y));
        lbTrainig->setColor(ccc3(0, 161, 236));
        Config::setScale(lbTrainig);
        addChild(lbTrainig, 11);
        i++;
    }
    
    i = 0;
    for(std::list<ScoreData*>::iterator it = Score::sharedInstance()->matching()->begin(); it != Score::sharedInstance()->matching()->end(); it++ )
    {
        float y = 1125/1536.0 * winSize.height - 103/1536.0 * winSize.height * i;
        ScoreData * pScoreData = (ScoreData*)*it;
        
        CCLabelTTF* lbName = CCLabelTTF::create(pScoreData->name.c_str() , "Marker Felt", 50);
        lbName->setPosition(ccp(1214/2048.0 * winSize.width, y));
        lbName->setColor(ccc3(0, 161, 236));
        Config::setScale(lbName);
        addChild(lbName, 11);
        
        char score[50] = {0};
        sprintf(score, "%d", pScoreData->score);
        CCLabelTTF* lbTrainig = CCLabelTTF::create(score, "Marker Felt", 50);
        lbTrainig->setPosition(ccp(1634/2048.0 * winSize.width, y));
        lbTrainig->setColor(ccc3(0, 161, 236));
        Config::setScale(lbTrainig);
        addChild(lbTrainig, 11);
        i++;
    }
    
    return true;
}

void ScoreScene::menuHome(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.5,HelloWorld::scene()));

}
