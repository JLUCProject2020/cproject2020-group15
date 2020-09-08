#include "Planet.h"
#include "../Common/GameConfig.h"
#include "b2NodeManager.h"
#include "BlackHole.h"
#include <math.h>
#define PTM_RATIO 32.0
USING_NS_CC;
#define G 67.0

cocos2d::Vec2 Planet::location1;
cocos2d::Vec2 Planet::location2;
Planet::Planet(void)
{
}


Planet::~Planet(void)
{
}

Planet* Planet::create(cocos2d::Vec2 position,b2World* world,Node *node)
{
	Planet * sprite = new Planet();
	if (sprite) {
		sprite->initPhysic(position,world,node);
		sprite->autorelease();
		return sprite;
		
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Planet::initPhysic(cocos2d::Vec2 position,b2World* world,Node *node)
{
	float radius = (b2NodeManager::getInstance()->radius) / 2 / PTM_RATIO;
	float density = 0.8f;
	_mass = density * b2_pi * radius * radius;
	_radius = radius;
	_world = world;
	_type = kPlanet;
	this->setPosition(position);
	this->setContentSize(Size(radius * 2 * PTM_RATIO,radius * 2 * PTM_RATIO));
	node->addChild(this,_type,kObject);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
	bodyDef.userData = this;
	
	_body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = radius;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;    
	fixtureDef.density = density;
	_body->CreateFixture(&fixtureDef); 

	b2Vec2 force = b2Vec2 (0, 0);
	float fx, fy, sum;
	fx = Planet::location2.x - Planet::location1.x;
	fy = Planet::location2.y - Planet::location1.y;
	sum = sqrt(fx * fx + fy * fy);
	//防止sum过小产生数值爆炸
	if (sum >= 3)
	{
		fx = fx / sum;
		fy = fy / sum;
		force = b2Vec2 (-fx, -fy);
	}
	else 
	{
		force = b2Vec2 (0, -1);
	}
	//以冲量方式实现初速度
	force.Normalize();
	float mag = b2NodeManager::getInstance()->mag;
	force = mag * _body->GetMass() * force;
	_body->ApplyForceToCenter(force, true);
}

float Planet::getMass()
{
	return _mass;
}

void Planet::ClearGravitationp()
{
	gravitationalForce.SetZero();
}

void Planet::AddGravitationp(b2Vec2 distance, float mass)
{
	
	float length = distance.LengthSquared();
	distance.Normalize();
	gravitationalForce += (G * mass * _body->GetMass()) / length * distance;
}

float Planet::GetGravityAnglep()
{
	return (atan2(-gravitationalForce.x, gravitationalForce.y));
}

void Planet::Processp()
{
	// Apply gravity
	_body->ApplyForce(gravitationalForce, _body->GetPosition(), true);
	_body->SetTransform(_body->GetWorldCenter(), atan2(-gravitationalForce.x, gravitationalForce.y));
}

float Planet::getRadius()
{
	return _radius;
}
