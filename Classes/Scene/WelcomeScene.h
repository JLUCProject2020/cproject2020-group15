#ifndef __WelcomeScene_H__
#define __WelcomeScene_H__

#include "cocos2d.h"

class WelcomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void EnterSecondScene(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene);
};
#endif

