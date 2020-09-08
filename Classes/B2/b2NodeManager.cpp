#include "b2NodeManager.h"
#include "../Common/GameConfig.h"
#include "../Common/ResourceDefine.h"
#include "b2PhysicObject.h"
#include "Planet.h"
#include "BlackHole.h"
#include "iostream"

#define PTM_RATIO 32.0
b2NodeManager::b2NodeManager(void)
{
	_nodes = std::make_shared<Vector<b2Node*>>();
	_planets = std::make_shared<Vector<b2Node*>>();
	_blackholes = std::make_shared<Vector<b2Node*>>();
	_deleteNodes = std::make_shared<Vector<b2Node*>>();
	_collisionListener = nullptr;
	mag = 100;
	radius = 100;
}


b2NodeManager::~b2NodeManager(void)
{
	_world = nullptr;
	_mainLayer = nullptr;
	_collisionListener = nullptr;

	_nodes->clear();
	_planets->clear();
	_blackholes->clear();
	_deleteNodes->clear();
}

static b2NodeManager *m_pInstance;

b2NodeManager* b2NodeManager::getInstance()
{
	if (m_pInstance == 0) {
		m_pInstance = new b2NodeManager();
	}
	return m_pInstance;
}

void b2NodeManager::addB2Node(b2Node *node)
{
	_nodes->pushBack(node);
	if(((b2PhysicObject *) node)->getType() == kPlanet)
	{
		_planets->pushBack(node);
	}
	
	if (((b2PhysicObject*)node)->getType() == kBlackHole)
	{
		_blackholes->pushBack(node);
	}
}

void b2NodeManager::removeB2Node(b2Node *node)
{
	_nodes->eraseObject(node,true);
	_planets->eraseObject(node,true);
	_blackholes->eraseObject(node, true);
}

void b2NodeManager::addDeleteNode(b2Node *node)
{
	_deleteNodes->pushBack(node);
}

void b2NodeManager::clearAll()
{
	_nodes->clear();
	_planets->clear();
	_blackholes->clear();
	_deleteNodes->clear();
}



void b2NodeManager::update(float dt)
{
	_world->Step(dt, 8, 1);
	int size = _nodes->size();
	b2PhysicObject * node;

	for (int i = 0; i < size; i++) {
		node = (b2PhysicObject *) _nodes->at(i);
		if (node->isVisible())
			node->update(dt);
	}

	Planet * planet;
	Planet* planetj;
	BlackHole * blackhole;
	for (int i = 0; i < _planets->size(); i++) //研究第i个星球
	{
		planet = (Planet*)_planets->at(i);
		b2Vec2 positionp = planet->getPhysicPosition();
		planet->ClearGravitationp();
		for (int j = 0; j < _planets->size(); j++)
		{
			if (j != i)
			{
				planetj = (Planet*)_planets->at(j);
				b2Vec2 distancepj = planetj->getPhysicPosition() - positionp;
				planet->AddGravitationp(distancepj, planetj->getMass());//施加其他星球产生的引力
			}
		}
		for (int k = 0; k < _blackholes->size(); k++)
		{
			blackhole = (BlackHole*)_blackholes->at(k);
			b2Vec2 distanceb = blackhole->getPhysicPosition() - positionp;
			planet->AddGravitationp(distanceb, blackhole->getMass());//施加黑洞产生的引力
			if (distanceb.LengthSquared() <= 1.1 * (planet->getRadius() + blackhole->getRadius()) 
				* (planet->getRadius() + blackhole->getRadius()))
			{
				this->addDeleteNode(planet);
			}//星球掉入黑洞被删除
		}
		planet->Processp();
	}

	//删除节点
	for (int i = 0; i < _deleteNodes->size(); i++) {
		removeB2Node(_deleteNodes->at(i));
		_world->DestroyBody(_deleteNodes->at(i)->getBody());
		_deleteNodes->at(i)->removeFromParentAndCleanup(true);
	}
	_deleteNodes->clear();
}

void b2NodeManager::deleteNode(Vec2 pos)
{
	int size = _nodes->size();
	b2PhysicObject * node;
	for (int i = 0; i < size; i++) {
		node = (b2PhysicObject *) _nodes->at(i);
		if(node->getBoundingBox().containsPoint(pos))
		{
			this->addDeleteNode(node);
		}
	}
}