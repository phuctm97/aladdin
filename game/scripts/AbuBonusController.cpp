#include "AbuBonusController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

AbuBonusController::AbuBonusController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _aladdinCollision(false) {}

bool AbuBonusController::isCollisionAladdin() const { return _aladdinCollision; }

void AbuBonusController::onUpdate(const float delta) {

	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();
	const auto distanceX = ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX());
	auto bodyAladdin = aladdin->getComponentT<Rigidbody>();
	const auto velocityY = bodyAladdin->getVelocity().getY();
	if (distanceX < 5) {
		_aladdinCollision = true;
	}
	else {
		_aladdinCollision = false;
	}
}

void AbuBonusController::explosionEffect() const {
	const auto transform = getGameObject()->getTransform();

	const auto vase = GameManager::get()->getPrefab("item explosion")->instantiate(
		transform->getPosition());
}

