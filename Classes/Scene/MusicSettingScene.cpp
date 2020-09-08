#include "SettingScene.h"
#include "MusicSettingScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;//ui命名空间
using namespace CocosDenshion;

Scene* MusicSettingScene::createScene()
{
    return MusicSettingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MusicSettingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label1 = Label::createWithTTF("MUSIC", "fonts/Marker Felt.ttf", 100);//创建label1
    label1->setPosition(Vec2(1000,1000));
    this->addChild(label1);

    auto slider = Slider::create();
    slider->setScale(2.5);
    slider->loadBarTexture("Slider_Back.png"); // what the slider looks like
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    slider->setPosition(Vec2(1000,600));

    slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            break;
        default:
            break;
        }
        });

    this->addChild(slider);

    auto label = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 50);//创建label
    MenuItemLabel* label1Item = MenuItemLabel::create(label, CC_CALLBACK_1(MusicSettingScene::menuItemCallBack, this));//根据label创建MenuItem
    Menu* pMenu = Menu::create(label1Item, NULL);
    pMenu->setPosition(1800, 150);
    this->addChild(pMenu, 2);

    return true;
}

void MusicSettingScene::menuItemCallBack(Ref* sender)
{
    Director::getInstance()->popScene();
}
