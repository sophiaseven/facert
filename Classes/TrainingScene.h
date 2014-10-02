//
//  TrainingScene.h
//  FaceRecog
//
//  Sophia Hannah
//


#ifndef __FaceRecog__TrainingScene__
#define __FaceRecog__TrainingScene__

#include "cocos2d.h"
using namespace cocos2d;

typedef enum{
	GameMoveLeftEnum,
	GameMoveTopEnum,
	GameMoveRightEnum,
	GameMoveBottomEnum
}GameMoveEnum;

class Flower : public cocos2d::CCSprite
{
public:
    static Flower* create(const char *pszFileName);

    CCPoint m_ptOri;
    int m_nFrames;
    int m_nDirect;
    void move();
    void animate();
    
    void disappear();
    
    void moveSpiritWidthOrientation(int move);
    

};




class TrainingScene : public cocos2d::CCLayer
{
private:
    void calcScore(int n);
    static int m_totalScore;
    int m_levelScore;
    float m_currentTime;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    CCLabelTTF* m_lbScore;
    CCLabelTTF* m_lbLevel;

//    CCSprite* m_spFace;
//    CCSprite* m_spMask;
    CCSprite* m_spResult;
    CCSprite* m_leftEyeHighLight;
    CCSprite* m_rightEyeHighLight;
    
    CCSprite* m_spHand;
    
    CCArray* m_aryLeftFlowers;
    CCArray* m_aryRightFlowers;
    CCLabelTTF* m_lbCongratulations;

    static int totalScore() {return TrainingScene::m_totalScore;}
    static void setTotalScore(int totalScore) { TrainingScene::m_totalScore = totalScore;}
    
    int  m_nLevel;
    int  m_nFlowerNum;
    int  m_nEatItems;
    float m_fImageScale;
    
    void setLevel(int n);
    void setScore(int n);
    void start();
    void success();

    bool m_bPaused;
    
    void createFlowers();
    void updateScene();
    
    void animateHighLight();
    bool m_bLeftEye;
    
    
    // a selector callback
    void menuHome(CCObject* pSender);
    void menuPrev(CCObject* pSender);
    void menuNext(CCObject* pSender);
    void menuStop(CCObject* pSender);
    
    virtual void ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
    //    virtual void ccTouchesMoved(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
    //    virtual void ccTouchesEnded(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(TrainingScene);
};

#endif /* defined(__FaceRecog__TrainingScene__) */
