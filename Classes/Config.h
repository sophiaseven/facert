//
//  Sophia Hannah

#ifndef __Config_h__
#define __Config_h__

#include "cocos2d.h"

USING_NS_CC;

#define DESIGN_RESOLUTION_WIDTH     2048.f
#define DESIGN_RESOLUTION_HEIGHT    1536.f

CCSprite* maskedSpriteWithSprite(CCSprite* pTextureSprite, CCSprite* pMaskSprite);

class Config
{
public:
    static void setScaleFactor(CCSize size);
    static void setScale(CCNode *node);
    static void setScale(CCNode *node, float factorX, float factorY);
      
    static float getX(float x);
    static float getY(float y);
    static float getyScale();
    static float getxScale();
    
};
static float __attribute__((unused)) _scaleX;
static float __attribute__((unused)) _scaleY;

#endif /* defined(__Config_h__) */
