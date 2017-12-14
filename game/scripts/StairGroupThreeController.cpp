#include "StairGroupThreeController.h"
#include "../Define.h"
USING_NAMESPACE_ALA;


void StairGroupThreeController::setStairActive(bool active)
{
	_isStairActive = active;
}

void StairGroupThreeController::onTriggerEnter(const ala::CollisionInfo & collision)
{
	getCollisionObject(collision);
	if (_other->getTag() != ALADDIN_TAG) return;

	if (collision.getNormal() == Vec2(-1, 0))
	{
		_isStairActive = !_isStairActive;
		const auto obj = getGameObject()->getAllComponents("Static");
		for each (Collider* stair in obj)
		{
			stair->setActive(_isStairActive);
		}
	}
}


void StairGroupThreeController::getCollisionObject(const ala::CollisionInfo & collision)
{
	_other = collision.getColliderA()->getGameObject() == getGameObject() ?
		collision.getColliderB()->getGameObject() :
		collision.getColliderA()->getGameObject();
}
