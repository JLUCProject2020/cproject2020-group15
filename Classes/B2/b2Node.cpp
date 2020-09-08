#include "b2Node.h"
#define PTM_RATIO 32.0

using namespace cocos2d;

b2Node::b2Node()
: _ignoreBody(false)
, _body(nullptr)
{}

b2Node::~b2Node()
{
	_body = nullptr;
	_world = nullptr;
}


// this method will only get called if the sprite is batched.
// return YES if the physic's values (angles, position ) changed.
// If you return NO, then getNodeToParentTransform won't be called.
bool b2Node::isDirty() const
{
    return true;
}

bool b2Node::isIgnoreBodyRotation() const
{
    return _ignoreBody;
}

void b2Node::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
{
    _ignoreBody = bIgnoreBodyRotation;
}

b2Vec2 b2Node::getPhysicPosition()
{
	return _body->GetPosition();
}
const Vec2& b2Node::getPosition() const
{

	return Node::getPosition();
}

void b2Node::getPosition(float* x, float* y) const
{
    if (x == NULL || y == NULL) {
        return;
    }
    const Vec2& pos = getPosition();
    *x = pos.x;
    *y = pos.y;
}

float b2Node::getPositionX() const
{
    return getPosition().x;
}

float b2Node::getPositionY() const
{
    return getPosition().y;
}

void b2Node::setPosition(const Vec2 &_position)
{
	Node::setPosition(_position);
	 if (!_ignoreBody && _body)
	{
		_body->SetTransform(b2Vec2(
			_position.x / PTM_RATIO,
			_position.y/ PTM_RATIO),
			_body->GetAngle());
	}
}

float b2Node::getRotation() const
{
    return (_ignoreBody ? Node::getRotation() :
            CC_RADIANS_TO_DEGREES(_body->GetAngle()));
}

void b2Node::setRotation(float rotation)
{
    Node::setRotation(rotation);
    if (!_ignoreBody && _body)
    {
        b2Vec2 p = _body->GetPosition();
		_body->SetTransform(b2Vec2(
			_position.x / PTM_RATIO,
			_position.y/ PTM_RATIO),
			-CC_DEGREES_TO_RADIANS(rotation));
    }
}

void b2Node::setVisible(bool visible)
{
	if(_body)
	{
		if (!visible)
		{
			_body->SetLinearVelocity(b2Vec2_zero);
			_body->SetAngularVelocity(0);
			_body->SetTransform(b2Vec2_zero, 0.0);
			_body->SetActive(false);
		}
		else
		{
			_body->SetLinearVelocity(b2Vec2_zero);
			_body->SetAngularVelocity(0);
			_body->SetTransform(b2Vec2_zero, 0.0);
			_body->SetActive(true);
			_body->SetAwake(true);
		}
	}
	Node::setVisible(visible);
}

float b2Node::getMass()
{
	return _body->GetMass();
}