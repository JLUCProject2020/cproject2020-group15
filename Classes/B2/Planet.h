#ifndef __B2_PLANET_H__
#define __B2_PLANET_H__
#include "b2PhysicObject.h"
#include "cocos2d.h"

class Planet : public b2PhysicObject
{
public:
	static cocos2d::Vec2 location1;
	static cocos2d::Vec2 location2;
	Planet(void);
	virtual ~Planet(void);
	static Planet* create(cocos2d::Vec2 position,b2World* world,cocos2d::Node *node);
	float _mass;
	float _radius;
	virtual float getMass() override;
	float getRadius();
	void ClearGravitationp();
	void AddGravitationp(b2Vec2 distance, float mass);
	float GetGravityAnglep();
	void Processp();
	
private:
	void initPhysic(cocos2d::Vec2 position,b2World* world,cocos2d::Node *node);
	b2Vec2 gravitationalForce;
};
#endif
