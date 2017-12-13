#include "RestartPointController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

RestartPointController::RestartPointController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _aladdinNear(false) {}

bool RestartPointController::isNearAladdin() const { return _aladdinNear; }

void RestartPointController::onUpdate(const float delta) {

	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();
	const auto distanceX = ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX());
	auto bodyAladdin = aladdin->getComponentT<Rigidbody>();
	const auto velocityY = bodyAladdin->getVelocity().getY();
	if (distanceX < 5 ) {
		_aladdinNear = true;
	}
	else {
		_aladdinNear = false;
	}
}

