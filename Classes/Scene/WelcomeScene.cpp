#include "Scene/WelcomeScene.h"
#include "Scene/HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    return WelcomeScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool WelcomeScene::init()
{
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite1 = Sprite::create("logo.png");
    if (sprite1 == nullptr)
    {
        problemLoading("'logo.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        sprite1->setScale(0.7);
        // add the sprite as a child to this layer
        this->addChild(sprite1, 0);
    }

    auto label = Label::createWithSystemFont("JLU TAQ", "fonts/Marker Felt.ttf", 60);
    label->setPosition(Vec2(origin.x, origin.y + 500 - label->getContentSize().height));
    auto menuitem = MenuItemLabel::create(label, CC_CALLBACK_1(WelcomeScene::EnterSecondScene, this));
    //创建好了菜单条目，需要加入菜单中，下面创建菜单
    auto menu = Menu::create(menuitem, NULL);
    //把菜单添加到WelcomeScene中
    this->addChild(menu);

    return true;
}

//转场
void WelcomeScene::EnterSecondScene(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(3.0f, HelloWorldScene::create()));

}


