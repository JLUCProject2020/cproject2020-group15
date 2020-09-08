#include "HelpScene.h"
#include "MainScene.h"


USING_NS_CC;

Scene* HelpScene::createScene()
{
    return HelpScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label1 = Label::createWithTTF("HELP", "fonts/Marker Felt.ttf", 100);//创建label1
    label1->setPosition(Vec2(1000, 1000));
    this->addChild(label1);

    auto label2 = Label::createWithTTF("Press 'Q' to select 'Planet' and 'W' to select 'Black Hole'", "fonts/Marker Felt.ttf", 40);//创建label2
    label2->setPosition(Vec2(1000, 800));
    this->addChild(label2);

    auto label3 = Label::createWithTTF("Press '1' to reduce 'Mag' and '2' to increase.\n\nPress '3' to reduce 'Radius' and '4' to increase.", "fonts/Marker Felt.ttf", 40);//创建label3
    label3->setPosition(Vec2(1000, 600));
    this->addChild(label3);

    auto label = Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 50);//创建label
    MenuItemLabel* label1Item = MenuItemLabel::create(label, CC_CALLBACK_1(HelpScene::menuItemCallBack, this));//根据label创建MenuItem
    Menu* pMenu = Menu::create(label1Item, NULL);
    pMenu->setPosition(1800, 150);
    this->addChild(pMenu, 2);

    return true;
}

//转场
void HelpScene::menuItemCallBack(Ref* sender)
{
    Director::getInstance()->popScene();
}



