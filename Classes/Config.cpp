//
//  Sophia Hannah
#include "Config.h"
CCSprite* maskedSpriteWithSprite(CCSprite* pTextureSprite, CCSprite* pMaskSprite)
{
    // store the original positions of both sprites
    CCPoint textureSpriteOrigPosition = pTextureSprite->getPosition();
    CCPoint maskSpriteOrigPosition = pMaskSprite->getPosition();
    
    float fTextureWidth = pTextureSprite->getContentSize().width * pTextureSprite->getScaleX();
    float fTextureHeight = pTextureSprite->getContentSize().height * pTextureSprite->getScaleY();
    
    float fMaskWidth = pMaskSprite->getContentSize().width * pMaskSprite->getScaleX();
    float fMaskHeight = pMaskSprite->getContentSize().height * pMaskSprite->getScaleY();
    
    
    // convert the texture sprite position into mask sprite coordinate system
    pTextureSprite->setPosition(ccp(fTextureWidth/2 - pMaskSprite->getPosition().x + fMaskWidth/2, fTextureHeight/2 - pMaskSprite->getPosition().y + fMaskHeight/2));
    
    // position the mask sprite so that the bottom left corner lies on the (o,o) coordinates
    pMaskSprite->setPosition(ccp(fMaskWidth/2, fMaskHeight/2));
    
    CCRenderTexture* rt = CCRenderTexture::create((int)fMaskWidth, (int)fMaskHeight);
    
    ccBlendFunc bfMask = ccBlendFunc();
    bfMask.src = GL_ONE;
    bfMask.dst = GL_ZERO;
    pMaskSprite->setBlendFunc(bfMask);
    
    // turn off anti-aliasing around the mask sprite
    pMaskSprite->getTexture()->setAliasTexParameters();
    
    ccBlendFunc bfTexture = ccBlendFunc();
    bfTexture.src = GL_DST_ALPHA;
    bfTexture.dst = GL_ZERO;
    pTextureSprite->setBlendFunc(bfTexture);
    
    rt->begin();
    pMaskSprite->visit();
    pTextureSprite->visit();
    rt->end();
    
    // generate the resulting sprite
    CCSprite* pOutcome = CCSprite::createWithTexture(rt->getSprite()->getTexture());
    pOutcome->setFlipY(true);
    
    // restore the original sprite positions
    pTextureSprite->setPosition(textureSpriteOrigPosition);
    pMaskSprite->setPosition(maskSpriteOrigPosition);
    pOutcome->setPosition(maskSpriteOrigPosition);
    

    return pOutcome;
}

void Config::setScaleFactor(CCSize size)
{
    _scaleX = size.width / DESIGN_RESOLUTION_WIDTH;
    _scaleY = size.height / DESIGN_RESOLUTION_HEIGHT;
}

void Config::setScale(CCNode *node)
{
    //node->setContentSize(CCSize(node->getContentSize().width*_scaleX, node->getContentSize().height*_scaleY));
    node->setScaleX(_scaleX);
    node->setScaleY(_scaleY);
}

void Config::setScale(CCNode *node, float factorX, float factorY)
{
    node->setScaleX(_scaleX * factorX);
    node->setScaleY(_scaleY * factorY);
}

float Config::getX(float x)
{
    return _scaleX * x;
}

float Config::getyScale()
{
    return _scaleY;
}

float Config::getxScale()
{
    return _scaleX;
}

float Config::getY(float y)
{
    return _scaleY * y;
}
