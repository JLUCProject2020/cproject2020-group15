#include "BlackHole.h"
#include "../Common/GameConfig.h"
#include "b2NodeManager.h"

#define PTM_RATIO 32.0
USING_NS_CC;
BlackHole::BlackHole(void)
{
}


BlackHole::~BlackHole(void)
{
}

BlackHole* BlackHole::create(cocos2d::Vec2 position, b2World* world, Node* node)
{
	BlackHole* sprite = new BlackHole();
	if (sprite) {
		sprite->initPhysic(position, world, node);
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void BlackHole::initPhysic(cocos2d::Vec2 position, b2World* world, Node* node)
{
	float radius = (b2NodeManager::getInstance()->radius) / 2 / PTM_RATIO;
	float density = 100.0f;
	_mass = density * b2_pi * radius * radius;
	_radius = radius;
	_world = world;
	_type = kBlackHole;
	this->setPosition(position);
	this->setContentSize(Size(radius * 2 * PTM_RATIO, radius * 2 * PTM_RATIO));
	node->addChild(this, _type, kObject);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
	bodyDef.userData = this;

	_body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = radius;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = density;
	_body->CreateFixture(&fixtureDef);

}

float BlackHole::getMass()
{
	return _mass;
}

float BlackHole::getRadius()
{
	return _radius;
}


