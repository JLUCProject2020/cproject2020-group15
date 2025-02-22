#include "PhysicDelegate.h"
#include "../Common/GameConfig.h"
#define PTM_RATIO 32.0

PhysicDelegate::PhysicDelegate()
{

}

PhysicDelegate::~PhysicDelegate()
{
	delete _world;
	_world = NULL;

	delete m_debugDraw;
	//delete _collisionListener;
}

void PhysicDelegate::initWorld()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	m_debugDraw = new GLESDebugDraw( PTM_RATIO );
	_world->SetDebugDraw(m_debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;

	m_debugDraw->SetFlags(flags);
}

void PhysicDelegate::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);
	_customCmd.init(_globalZOrder);
	_customCmd.func = CC_CALLBACK_0(PhysicDelegate::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void PhysicDelegate::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
	GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}