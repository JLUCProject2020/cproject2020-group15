#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"//uiͷ�ļ�
#include "PauseLayer.h"
#include "SettingScene.h"
#include "HelpScene.h"
#include "../Common/GameConfig.h"
#include "../Common/ResourceDefine.h"
#include "../B2/b2PhysicObject.h"
#include "../B2/b2NodeManager.h"

#define PTM_RATIO 32.0

using namespace cocos2d::ui;//ui�����ռ�
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
        //���ò㼶��ϵ��ֵԽ��Խ����Ⱦ��Ĭ��Ϊ��1��
        pauseBtn->setLocalZOrder(2);
        this->addChild(pauseBtn);

        //�ָ��Ĵ���
        Button* resumeBtn = Button::create("button2-1.png", "button2-1.png");
        resumeBtn->setPosition(Vec2(150, 1220));
        //���ò㼶��ϵ��ֵԽ��Խ����Ⱦ��Ĭ��Ϊ��1��
        resumeBtn->setLocalZOrder(2);
        //���ûָ���ť�ɼ�
        resumeBtn->setVisible(true);
        this->addChild(resumeBtn);

        //����ͣ��ť��ӵ���¼�:
        pauseBtn->addClickEventListener([pauseBtn, resumeBtn, this](Ref*)
            {
                //��Ϸ��ͣ
                Director::getInstance()->pause();

                //�ر�����
                //SimpleAudioEngine::pauseAll();
                auto audio = SimpleAudioEngine::getInstance();
                audio->pauseBackgroundMusic();

                //��ʾ�ָ���ť
                resumeBtn->setVisible(true);

                //��ʾ��ͣ��ť
                pauseBtn->setVisible(true);

            });

        //��������ť��ӵ���¼�:
        resumeBtn->addClickEventListener([pauseBtn, resumeBtn, this](Ref*)
            {
                //��Ϸ�ָ�
                Director::getInstance()->resume();

                //�ָ�����
                auto audio = SimpleAudioEngine::getInstance();
                audio->resumeBackgroundMusic();
                //��ʾ�ָ���ť
                resumeBtn->setVisible(true);

                //��ʾ��ͣ��ť
                pauseBtn->setVisible(true);

            });

        Button* setBtn = Button::create("button2-7.png", "button2-7.png");
        setBtn->setPosition(Vec2(1900,80));
        //���ò㼶��ϵ��ֵԽ��Խ����Ⱦ��Ĭ��Ϊ��1��
        setBtn->setLocalZOrder(2);
        this->addChild(setBtn);

        //����ͣ��ť��ӵ���¼�:
        setBtn->addClickEventListener([setBtn, this](Ref*)
            {

                //������ͣ����
                Director::getInstance()->pushScene(SettingScene::create());

                //�ر�����
                //SimpleAudioEngine::pauseAll();
                auto audio = SimpleAudioEngine::getInstance();
                audio->pauseBackgroundMusic();

                //��ʾ��ť
                setBtn->setVisible(true);

            });



        Button* helpBtn = Button::create("button2-8.png", "button2-8.png");
        helpBtn->setPosition(Vec2(1820, 80));
        //���ò㼶��ϵ��ֵԽ��Խ����Ⱦ��Ĭ��Ϊ��1��
        setBtn->setLocalZOrder(2);
        this->addChild(helpBtn);

        //����ͣ��ť��ӵ���¼�:
        helpBtn->addClickEventListener([helpBtn, this](Ref*)
            {
                //������ͣ����
                Director::getInstance()->pushScene(HelpScene::create());
                //��ʾ��ť
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

