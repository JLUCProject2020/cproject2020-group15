#ifndef __HelpScene_H__
#define __HelpScene_H__

#include "cocos2d.h"

class HelpScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuItemCallBack(Ref* sender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelpScene);
};
#endif
