//
//  Sophia Hannah
//

#ifndef __FaceRecog__FaceMatchingScene__
#define __FaceRecog__FaceMatchingScene__

#include "cocos2d.h"
using namespace cocos2d;

class FaceMatchingScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    CCLabelTTF* m_lbScore;
    CCLabelTTF* m_lbLevel;

    CCPoint m_pt[9];
    int m_map[9];
    
    int m_nLevel;
    int m_nScore;
    int m_nRound;

    float m_fImageScale;
    int m_nShapeNum;
    
    CCSprite* m_spSolve1;
//    CCSprite* m_spSolve2;

    CCArray* m_aryFaces;

    int m_nAnswer;
    int m_nSelected;
    CCPoint m_ptSelectedOri;
    
    bool m_bSolved;
    
    void setLevel(int n);
    void setScore(int n);
    void setRound(int round);

    void success();
    void fail();
    void nextLevel();
    void retry();

    // a selector callback
    void menuHome(CCObject* pSender);
    void menuNext(CCObject* pSender);
    void menuStop(CCObject* pSender);
    
    virtual void ccTouchesBegan(cocos2d::CCSet* _touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(FaceMatchingScene);
};

#endif /* defined(__FaceRecog__FaceMatchingScene__) */
