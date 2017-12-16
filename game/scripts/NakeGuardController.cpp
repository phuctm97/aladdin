#include "NakeGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

NakeGuardController::NakeGuardController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false), _couldAttackAladdin(false),
	_couldSeeAladdin(false), _onRightOfAladdin(false), _couldThrowToSky(false) {}

bool NakeGuardController::isCollidedWithGround() const { return _collidedWithGround; }

bool NakeGuardController::couldAttackAladdin() const {
	return _couldAttackAladdin;
}

bool NakeGuardController::coundSeeAladdin() const {
	return _couldSeeAladdin;
}

bool NakeGuardController::couldThrowToSky() const
{
	return _couldThrowToSky;
}

bool NakeGuardController::isOnRightOfAladdin() const {
	return _onRightOfAladdin;
}


void NakeGuardController::onUpdate(const float delta) {
	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();

	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < 60
		) {
		_couldAttackAladdin = true;
	}
	else {
		_couldAttackAladdin = false;
	}
	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) >= (visibleWidth * 0.5)
		&& ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) <= (visibleWidth * 0.6)) {
		_couldThrowToSky = true;
	}
	else _couldThrowToSky = false;
	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < (
		visibleWidth * 0.5)) {
		_couldSeeAladdin = true;
	}
	else if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) > (visibleWidth / 2)) {
		_couldSeeAladdin = false;
	}
	if (aladdin->getTransform()->getPosition().getX() < getGameObject()->getTransform()->getPosition().getX()) {
		_onRightOfAladdin = true; //Aladdin is in the left of enemy
	}
	else _onRightOfAladdin = false; //Aladdin is in the right of enemy
}

void NakeGuardController::onCollisionEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getTag() == GROUND_TAG ||
		collision.getColliderB()->getTag() == GROUND_TAG) {
		_collidedWithGround = true;
	}
}

void NakeGuardController::throwKnife(const char direction, const float directX, const float directY,
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