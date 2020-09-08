#ifndef _PAUSE_LAYER_H__
#define _PAUSE_LAYER_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;

class PauseLayer : public cocos2d::Layer
{
public:

	virtual bool init();
    static cocos2d::Layer* createLayer();

    // a selector callback
    void firstmenuItemCallBack(Ref* sender);
    void secondmenuItemCallBack(Ref* sender);
    void thirdmenuItemCallBack(Ref* sender);
    void fifthmenuItemCallBack(Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(PauseLayer);
private:
    void closeLayerTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
    void close(Node* pSender);
	
};

#endif

