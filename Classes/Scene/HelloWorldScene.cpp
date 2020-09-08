#include "Scene/HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Scene/MainScene.h"

USING_NS_CC;
using namespace CocosDenshion;
Scene* HelloWorldScene::createScene()
{
    return HelloWorldScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorldScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    auto closeItem = MenuItemImage::create(
        "button_play.png",
        "button_play _s.png",
        CC_CALLBACK_1(HelloWorldScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'button_play.png' and 'button_play _s.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2 + 200;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // create and initialize a label

    auto label = Label::createWithTTF("Pocket Astrophysics", "fonts/Marker Felt.ttf", 40);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite1 = Sprite::create("BackGround.png");
    if (sprite1 == nullptr)
    {
        problemLoading("'BackGround.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite1, 0);
    }

    // add "bluestar" splash screen"
    // load the Sprite Sheet
    auto spritecache = SpriteFrameCache::getInstance();

    // the .plist file can be generated with any of the tools mentioned below
    spritecache->addSpriteFramesWithFile("bluestars.plist");
    // this is equivalent to the previous example,
// but it is created by retrieving the SpriteFrame from the cache.
    auto newspriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar01.png");
    auto newSprite = Sprite::createWithSpriteFrame(newspriteFrame);
    newSprite->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y + 60));
    // add the sprite as a child to this layer
    this->addChild(newSprite, 1);


    auto sprite4 = Sprite::create("redstar01.png");
    if (sprite4 == nullptr)
    {
        problemLoading("'redstar01.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite4->setPosition(Vec2(1700, 200));
        // add the sprite as a child to this layer
        this->addChild(sprite4, 1);
    }




    auto sprite2 = Sprite::create("bluestar05.png");
    if (sprite2 == nullptr)
    {
        problemLoading("'bluestar05.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 500));
        sprite2->setScale(0.5);
        // add the sprite as a child to this layer
        this->addChild(sprite2, 1);
    }

    CCPointArray* array = CCPointArray::create(1);
    array->addControlPoint(ccp(82 * 2, 384 * 2));
    array->addControlPoint(ccp(335 * 2, 522 * 2));
    array->addControlPoint(ccp(562 * 2, 523 * 2));
    array->addControlPoint(ccp(853 * 2, 482 * 2));
    array->addControlPoint(ccp(942 * 2, 384 * 2));
    array->addControlPoint(ccp(853 * 2, 286 * 2));
    array->addControlPoint(ccp(562 * 2, 245 * 2));
    array->addControlPoint(ccp(335 * 2, 246 * 2));
    array->addControlPoint(ccp(82 * 2, 384 * 2));

    CCActionInterval* CardinalSplineTo = CCCardinalSplineTo::create(20, array, 0);
    CCActionInterval* act = CCRepeatForever::create(CardinalSplineTo);
    sprite2->runAction(act);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bluestars.plist");
    auto pSprite1 = Sprite::create("bluestar01.png");
    pSprite1->setPosition(150, 150);
    this->addChild(pSprite1, 2);

    Vector<SpriteFrame*>list;
    list.reserve(7);
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar01.png"));
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar05.png"));
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar02.png"));
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar04.png"));
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar06.png"));
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar04.png"));
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar02.png"));
    list.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bluestar05.png"));
    //创建Animation动画，每帧间隔为0.2s，重复播放
    auto pAnimation = Animation::createWithSpriteFrames(list, 1.3333f, 100);
    auto pAnimate = Animate::create(pAnimation);
    pSprite1->runAction(pAnimate);

    auto audio = SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("Background_music.mp3");
    audio->playBackgroundMusic("Background_music.mp3", true);
    return true;
}


void HelloWorldScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(MainScene::scene());
}
