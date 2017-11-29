#include "FatGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;
FatGuardController::FatGuardController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false), _colliedWithAladdin(false) {}

bool FatGuardController::isCollidedWithGround() const { return _collidedWithGround; }

bool FatGuardController::isCollidedWithAladdin() const
{
	return _colliedWithAladdin;
}

bool FatGuardController::isSeeingWithAladdin() const
{
	return _seeAladdin;
}
bool FatGuardController::isInTheLeftAladdin() const
{
	return _aladdinPosition;
}


void FatGuardController::onUpdate(const float delta)
{
	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();

	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < 60)
	{
		_colliedWithAladdin = true;
	}
	else
	{
		_colliedWithAladdin = false;
	}
	if (getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX() < (visibleWidth*0.8))
	{
		_seeAladdin = true;
	}
	else if (getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX() > (visibleWidth / 2))
	{
		_seeAladdin = false;
	}
	if (aladdin->getTransform()->getPosition().getX() < getGameObject()->getTransform()->getPosition().getX())
	{
		_aladdinPosition = true; //Aladdin is in the left of enemy
	}
	else _aladdinPosition = false; //Aladdin is in the right of enemy
}

void FatGuardController::onCollisionEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getTag() == GROUND_TAG ||
		collision.getColliderB()->getTag() == GROUND_TAG) {
		_collidedWithGround = true;
	}
}