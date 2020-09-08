#include "SettingScene.h"
#include "MusicSettingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "B2/b2NodeManager.h"
#include "../Common/GameConfig.h"
#include "../Common/ResourceDefine.h"
#include "B2/b2PhysicObject.h"
#include "B2/Planet.h"
#include "B2/BlackHole.h"

USING_NS_CC;
using namespace cocos2d::ui;//ui命名空间
using namespace CocosDenshion;

Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SettingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto label1 = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 80);//创建label1
    MenuItemLabel* label1Item = MenuItemLabel::create(label1, CC_CALLBACK_1(SettingScene::firstmenuItemCallBack, this));//根据label创建MenuItem
    Menu* pMenu1 = Menu::create(label1Item, NULL);
    pMenu1->setPosition(1000, 930);
    this->addChild(pMenu1, 2);

    auto label2 = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 80);//创建label2
    MenuItemLabel* label2Item = MenuItemLabel::create(label2, CC_CALLBACK_1(SettingScene::secondmenuItemCallBack, this));//根据label创建MenuItem
    Menu* pMenu2 = Menu::create(label2Item, NULL);
    pMenu2->setPosition(1000, 730);
    this->addChild(pMenu2, 2);

    auto label3 = Label::createWithTTF("Setting", "fonts/Marker Felt.ttf", 80);//创建label3
    MenuItemLabel* label3Item = MenuItemLabel::create(label3, CC_CALLBACK_1(SettingScene::thirdmenuItemCallBack, this));//根据label创建MenuItem
    Menu* pMenu3 = Menu::create(label3Item, NULL);
    pMenu3->setPosition(1000, 530);
    this->addChild(pMenu3, 2);


    auto label5 = Label::createWithTTF("Exit to Menu", "fonts/Marker Felt.ttf", 80);//创建label3
    MenuItemLabel* label5Item = MenuItemLabel::create(label5, CC_CALLBACK_1(SettingScene::fifthmenuItemCallBack, this));//根据label创建MenuItem
    Menu* pMenu5 = Menu::create(label5Item, NULL);
    pMenu5->setPosition(1000, 330);
    this->addChild(pMenu5, 2);


    return true;
}

void SettingScene::firstmenuItemCallBack(Ref* sender)
{
    Director::getInstance()->popScene();
    //恢复音乐
    auto audio = SimpleAudioEngine::getInstance();
    audio->resumeBackgroundMusic();
}

void SettingScene::secondmenuItemCallBack(Ref* sender)
{
    Director::getInstance()->popScene();
    b2NodeManager::getInstance()->clearAll();
    b2NodeManager::getInstance()->mag = 100;
    b2NodeManager::getInstance()->radius = 100;
    Director::getInstance()->replaceScene(MainScene::scene());   
    //恢复音乐
    auto audio = SimpleAudioEngine::getInstance();
    audio->resumeBackgroundMusic();
}

void SettingScene::thirdmenuItemCallBack(Ref* sender)
{
    Director::getInstance()->pushScene(MusicSettingScene::create());
    b2NodeManager::getInstance()->clearAll();
    b2NodeManager::getInstance()->mag = 100;
    b2NodeManager::getInstance()->radius = 100;
    //恢复音乐
    auto audio = SimpleAudioEngine::getInstance();
    audio->resumeBackgroundMusic();
}


void SettingScene::fifthmenuItemCallBack(Ref* sender)
{
    Director::getInstance()->popScene();
    b2NodeManager::getInstance()->clearAll();
    b2NodeManager::getInstance()->mag = 100;
    b2NodeManager::getInstance()->radius = 100;
    //恢复音乐
    auto audio = SimpleAudioEngine::getInstance();
    audio->resumeBackgroundMusic();
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, HelloWorldScene::create()));
}

