#ifndef __B2_BLACKHOLE_H__
#define __B2_BLACKHOLE_H__
#include "b2PhysicObject.h"

class BlackHole : public b2PhysicObject
{
public:
	BlackHole(void);
	virtual ~BlackHole(void);
	static BlackHole* create(cocos2d::Vec2 position, b2World* world, cocos2d::Node* node);
	float _mass;
	float _radius;
	virtual float getMass() override;
	float getRadius();

private:
	void initPhysic(cocos2d::Vec2 position, b2World* world, cocos2d::Node* node);
};
#endif

