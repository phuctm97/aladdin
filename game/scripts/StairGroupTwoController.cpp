#include "StairGroupTwoController.h"
#include "StairGroupThreeController.h"
#include "../Define.h"
USING_NAMESPACE_ALA;

void StairGroupTwoController::setStairActive(bool active)
{
	_isStairActive = active;
}

void StairGroupTwoController::onTriggerEnter(const ala::CollisionInfo & collision)
{
	getCollisionObject(collision);
	if (_other->getTag() != ALADDIN_TAG) return;

	GameManager::get()->getObjectByName("StairGroupThree")->getComponent("Triggerer")->setActive(true);
	if (collision.getNormal() == Vec2(1, 0))
	{
		_isStairActive = !_isStairActive;
		const auto obj = getGameObject()->getAllComponents("Static");
		for each (Collider* stair in obj)
		{
			stair->setActive(_isStairActive);
		}
	}
	if (collision.getNormal() == Vec2(-1, 0))
	{
		const auto obj = GameManager::get()->getObjectByName("StairGroupThree")->getAllComponents("Static");
		for each (Collider* stair in obj)
		{
			stair->setActive(false);
		}
		const auto controller = GameManager::get()->getObjectByName("StairGroupThree")->getComponent("Controller");
		static_cast<StairGroupThreeController*>(controller)->setStairActive(false);
	}
}


void StairGroupTwoController::getCollisionObject(const ala::CollisionInfo & collision)
{
	_other = collision.getColliderA()->getGameObject() == getGameObject() ?
		collision.getColliderB()->getGameObject() :
		collision.getColliderA()->getGameObject();

}
