#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"//ui头文件
#include "PauseLayer.h"
#include "SettingScene.h"
#include "HelpScene.h"
#include "../Common/GameConfig.h"
#include "../Common/ResourceDefine.h"
#include "../B2/b2PhysicObject.h"
#include "../B2/b2NodeManager.h"

#define PTM_RATIO 32.0

using namespace cocos2d::ui;//ui命名空间
using namespace CocosDenshion;
USING_NS_CC;

MainScene::~MainScene()
{

}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* MainScene::scene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !PhysicLayer::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	{

        // add "HelloWorld" splash screen"
        auto sprite = Sprite::create("MainScene.png");
        if (sprite == nullptr)
        {
            problemLoading("'MainScene.png'");
        }
        else
        {
            // position the sprite on the center of the screen
            sprite->setPosition(Vec2(512,384));

            // add the sprite as a child to this layer
            this->addChild(sprite, -10);
        }
		this->scheduleUpdate();

        Button* pauseBtn = Button::create("button2-0.png", "button2-0.png");
        pauseBtn->setPosition(Vec2(80, 1220));
        //设置层级关系：值越大，越后渲染（默认为：1）
        pauseBtn->setLocalZOrder(2);
        this->addChild(pauseBtn);

        //恢复的创建
        Button* resumeBtn = Button::create("button2-1.png", "button2-1.png");
        resumeBtn->setPosition(Vec2(150, 1220));
        //设置层级关系：值越大，越后渲染（默认为：1）
        resumeBtn->setLocalZOrder(2);
        //设置恢复按钮可见
        resumeBtn->setVisible(true);
        this->addChild(resumeBtn);

        //给暂停按钮添加点击事件:
        pauseBtn->addClickEventListener([pauseBtn, resumeBtn, this](Ref*)
            {
                //游戏暂停
                Director::getInstance()->pause();

                //关闭音乐
                //SimpleAudioEngine::pauseAll();
                auto audio = SimpleAudioEngine::getInstance();
                audio->pauseBackgroundMusic();

                //显示恢复按钮
                resumeBtn->setVisible(true);

                //显示暂停按钮
                pauseBtn->setVisible(true);

            });

        //给继续按钮添加点击事件:
        resumeBtn->addClickEventListener([pauseBtn, resumeBtn, this](Ref*)
            {
                //游戏恢复
                Director::getInstance()->resume();

                //恢复音乐
                auto audio = SimpleAudioEngine::getInstance();
                audio->resumeBackgroundMusic();
                //显示恢复按钮
                resumeBtn->setVisible(true);

                //显示暂停按钮
                pauseBtn->setVisible(true);

            });

        Button* setBtn = Button::create("button2-7.png", "button2-7.png");
        setBtn->setPosition(Vec2(1900,80));
        //设置层级关系：值越大，越后渲染（默认为：1）
        setBtn->setLocalZOrder(2);
        this->addChild(setBtn);

        //给暂停按钮添加点击事件:
        setBtn->addClickEventListener([setBtn, this](Ref*)
            {

                //创建暂停界面
                Director::getInstance()->pushScene(SettingScene::create());

                //关闭音乐
                //SimpleAudioEngine::pauseAll();
                auto audio = SimpleAudioEngine::getInstance();
                audio->pauseBackgroundMusic();

                //显示按钮
                setBtn->setVisible(true);

            });



        Button* helpBtn = Button::create("button2-8.png", "button2-8.png");
        helpBtn->setPosition(Vec2(1820, 80));
        //设置层级关系：值越大，越后渲染（默认为：1）
        setBtn->setLocalZOrder(2);
        this->addChild(helpBtn);

        //给暂停按钮添加点击事件:
        helpBtn->addClickEventListener([helpBtn, this](Ref*)
            {
                //创建暂停界面
                Director::getInstance()->pushScene(HelpScene::create());
                //显示按钮
                helpBtn->setVisible(true);
            });

	}

	b2NodeManager::getInstance()->setCollisionListener(nullptr);
	b2NodeManager::getInstance()->setMainLayer(this);
	b2NodeManager::getInstance()->setWorld(_world);


    return true;
}

void MainScene::update(float dt)
{
	PhysicLayer::update(dt);
}

