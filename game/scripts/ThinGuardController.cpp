#include "ThinGuardController.h"
#include "../Define.h"


USING_NAMESPACE_ALA;
ThinGuardController::ThinGuardController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false), _colliedWithAladdin (false){}

bool ThinGuardController::isCollidedWithGround() const { return _collidedWithGround; }

bool ThinGuardController::isCollidedWithAladdin() const
{
	return _colliedWithAladdin;
}

bool ThinGuardController::isSeeingWithAladdin() const
{
	return _seeAladdin;
}
bool ThinGuardController::isInTheLeftAladdin() const
{
	return _aladdinPosition;
}


void ThinGuardController::onUpdate(const float delta)
{
	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();

	if(ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < 60)
	{
		_colliedWithAladdin = true;
	}
	else
	{
		_colliedWithAladdin = false;
	}
	if(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX() < (visibleWidth*0.3))
	{
		_seeAladdin = true;
	}
	else if (getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX() > (visibleWidth/2))
	{
		_seeAladdin = false;
	}
	if (aladdin->getTransform()->getPosition().getX() < getGameObject()->getTransform()->getPosition().getX())
	{
		_aladdinPosition = true; //Aladdin is in the left of enemy
	}
	else _aladdinPosition = false; //Aladdin is in the right of enemy
}

void ThinGuardController::onCollisionEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getTag() == GROUND_TAG ||
		collision.getColliderB()->getTag() == GROUND_TAG) {
		_collidedWithGround = true;
	}
}