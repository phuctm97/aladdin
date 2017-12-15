#include "AdorableGuardController.h"

#include "../Define.h"

USING_NAMESPACE_ALA;
AdorableGuardController::AdorableGuardController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false), _colliedWithAladdin(false), _isRunFromEnemy(false), _seeAladdin(false){}

bool AdorableGuardController::isCollidedWithGround() const { return _collidedWithGround; }

bool AdorableGuardController::isCollidedWithAladdin() const
{
	return _colliedWithAladdin;
}

bool AdorableGuardController::isSeeingWithAladdin() const
{
	return _seeAladdin;
}
bool AdorableGuardController::isInTheLeftAladdin() const
{
	return _aladdinPosition;
}

bool AdorableGuardController::isRunFromEnemy() const
{
	return _isRunFromEnemy;
}


void AdorableGuardController::onUpdate(const float delta)
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
	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < (visibleWidth*0.4))
	{
		_seeAladdin = true;
	}
	else _seeAladdin = false;
	if (aladdin->getTransform()->getPosition().getX() < getGameObject()->getTransform()->getPosition().getX())
	{
		_aladdinPosition = true; //Aladdin is in the left of enemy
	}
	else _aladdinPosition = false; //Aladdin is in the right of enemy
	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) > (visibleWidth*0.4))
	{
		_isRunFromEnemy = true;
	}
	else
	{
		_isRunFromEnemy = false;
	}
}

void AdorableGuardController::onCollisionEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getTag() == GROUND_TAG ||
		collision.getColliderB()->getTag() == GROUND_TAG) {
		_collidedWithGround = true;
	}
}

void AdorableGuardController::throwKnife(const char direction, const float directX, const float directY,
	const float impulseX, const float impulseY) const {
	const auto transform = getGameObject()->getTransform();
	const auto collider = getGameObject()->getComponentT<Collider>();

	const auto knife = GameManager::get()->getPrefab("Throwable Knife")->instantiate(
		transform->getPosition() + Vec2(-collider->getSize().getWidth() / 2 + directX,
			collider->getSize().getHeight() / 2 + directY));
	const auto knifeStateManager = static_cast<StateManager*>(knife->getComponentT<StateManager>());

	if (direction == 'L') {
		knifeStateManager->changeState("throwable_knife_left");
	}
	else {
		knifeStateManager->changeState("throwable_knife_right");
	}

	const auto knifeBody = knife->getComponentT<Rigidbody>();
	knifeBody->addImpulse(Vec2(impulseX, impulseY));
}