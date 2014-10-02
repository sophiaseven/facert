//
// Sophia Hannah
//

#include "MyMenuItem.h"
#include "Config.h"

#define kZoomActionTag 101

MyMenuItem* MyMenuItem::create(const char *normalImage, CCObject* target, SEL_MenuHandler selector)
{
    MyMenuItem *pobSprite = new MyMenuItem();
    if (pobSprite && pobSprite->initWithNormalImage(normalImage, normalImage, normalImage, target, selector))
    {
        
        pobSprite->autorelease();
        
        
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;

}

void MyMenuItem::selected()
{
    // subclass to change the default action
    if(isEnabled()) {
        _scaleX = getScaleX();
        
        CCMenuItem::selected();
        stopActionByTag(kZoomActionTag);
        CCAction *zoomAction = CCScaleTo::create(0.1f, _scaleX * 1.2f);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}
void MyMenuItem::unselected()
{
    // subclass to change the default action
    if(isEnabled()) {
        CCMenuItem::unselected();
        stopActionByTag(kZoomActionTag+1);
        CCAction *zoomAction = CCScaleTo::create(0.1f, _scaleX * 1.0f);
        zoomAction->setTag(kZoomActionTag+1);
        this->runAction(zoomAction);
    }
}

