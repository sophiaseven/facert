// Sophia Hannah
//

#ifndef __MyMenuItem_h__
#define __MyMenuItem_h__

#include "cocos2d.h"


USING_NS_CC;

class MyMenuItem : public cocos2d::CCMenuItemImage
{
public:
    static MyMenuItem* create(const char *normalImage, CCObject* target, SEL_MenuHandler selector);
//    virtual bool init();
    
    virtual void selected();
    virtual void unselected();

    float _scaleX;
    float _scaleY;
    
    // Auto-generated function
    CREATE_FUNC(MyMenuItem);

};


#endif /* defined(__MyMenuItem_h__) */
