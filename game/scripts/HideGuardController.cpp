#include "HideGuardController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

HideGuardController::HideGuardController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false), _couldAttackAladdin(false),
	_couldSeeAladdin(false), _onRightOfAladdin(false) {}

bool HideGuardController::isCollidedWithGround() const { return _collidedWithGround; }

bool HideGuardController::couldAttackAladdin() const {
	return _couldAttackAladdin;
}

bool HideGuardController::coundSeeAladdin() const {
	return _couldSeeAladdin;
}

bool HideGuardController::isOnRightOfAladdin() const {
	return _onRightOfAladdin;
}


void HideGuardController::onUpdate(const float delta) {
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
	if (getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX() < (
		visibleWidth * 0.3)) {
		_couldSeeAladdin = true;
	}
	else if (getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX() > (
		visibleWidth / 2)) {
		_couldSeeAladdin = false;
	}
	if (aladdin->getTransform()->getPosition().getX() < getGameObject()->getTransform()->getPosition().getX()) {
		_onRightOfAladdin = true; //Aladdin is in the left of enemy
	}
	else _onRightOfAladdin = false; //Aladdin is in the right of enemy
}

void HideGuardController::onCollisionEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getTag() == GROUND_TAG ||
		collision.getColliderB()->getTag() == GROUND_TAG) {
		_collidedWithGround = true;
	}
}