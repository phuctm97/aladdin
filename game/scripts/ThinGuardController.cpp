#include "ThinGuardController.h"
#include "../Define.h"


USING_NAMESPACE_ALA;

ThinGuardController::ThinGuardController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name),
	_couldAttackAladdin(false), _couldSeeAladdin(false), _onRightOfAladdin(false), _tooFarFromAladdin(true),
	_minX(0), _maxX(0) {}

bool ThinGuardController::couldAttackAladdin() const {
	return _couldAttackAladdin;
}

bool ThinGuardController::couldSeeAladdin() const {
	return _couldSeeAladdin;
}

bool ThinGuardController::isOnRightOfAladdin() const {
	return _onRightOfAladdin;
}

bool ThinGuardController::isTooFarFromAladdin() const {
	return _tooFarFromAladdin;
}

void ThinGuardController::onUpdate(const float delta) {
	const auto aladdin = GameManager::get()->getObjectByTag(ALADDIN_TAG);
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();
	const auto guardPosition = getGameObject()->getTransform()->getPosition();
	const auto aladdinPosition = aladdin->getTransform()->getPosition();

	const auto distanceToAladdin = ABS(guardPosition.getX() - aladdinPosition.getX());
	_couldSeeAladdin = distanceToAladdin < visibleWidth * 0.6f;
	_tooFarFromAladdin = distanceToAladdin > visibleWidth * 0.7f;
	_couldAttackAladdin = distanceToAladdin < 70;
	_onRightOfAladdin = aladdinPosition.getX() < guardPosition.getX();
}

float ThinGuardController::getMinX() const { return _minX; }

void ThinGuardController::setMinX(const float minX) { _minX = minX; }

float ThinGuardController::getMaxX() const { return _maxX; }

void ThinGuardController::setMaxX(const float maxX) { _maxX = maxX; }

void ThinGuardController::set(const float minX, const float maxX) {
	setMinX(minX);
	setMaxX(maxX);
}
