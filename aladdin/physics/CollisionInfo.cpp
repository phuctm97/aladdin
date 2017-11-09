#include "CollisionInfo.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_0(CollisionInfo)

CollisionInfo::CollisionInfo(GameObject* a, GameObject* b, float penetration, Vec2 normal)
{
	_objectA = a;
	_objectB = b;
	_penetration = penetration;
	_normal = normal;
}

CollisionInfo::~CollisionInfo()
{
}

void CollisionInfo::setObjectA(GameObject* objectA)
{
	_objectA = objectA;
}

void CollisionInfo::setObjectB(GameObject* objectB)
{
	_objectB = objectB;
}

void CollisionInfo::setPenetration(const float penetration)
{
	_penetration = penetration;
}

void CollisionInfo::setNormal(const Vec2& normal)
{
	_normal = normal;
}

GameObject* CollisionInfo::getObjectA() const
{
	return _objectA;
}

GameObject* CollisionInfo::getObjectB() const
{
	return _objectB;
}

float CollisionInfo::getPenetration() const
{
	return _penetration;
}

const Vec2& CollisionInfo::getNormal() const
{
	return _normal;
}
}
