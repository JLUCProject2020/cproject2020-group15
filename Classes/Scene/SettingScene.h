#ifndef __SettingScene_H__
#define __SettingScene_H__

#include "cocos2d.h"

class SettingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void firstmenuItemCallBack(Ref* sender);
    void secondmenuItemCallBack(Ref* sender);
    void thirdmenuItemCallBack(Ref* sender);
    void fifthmenuItemCallBack(Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);
};
#endif

