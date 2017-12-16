#include "SpringController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

SpringController::SpringController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _aladdinOnBack(false) {}

bool SpringController::isAladdinOnBack() const { return _aladdinOnBack; }

void SpringController::onUpdate(const float delta) {

	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();
	const auto distanceX = ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX());
	const auto distanceY = ABS(getGameObject()->getTransform()->getPosition().getY() - aladdin->getTransform()->getPosition().getY());
	auto bodyAladdin = aladdin->getComponentT<Rigidbody>();
	const auto velocityY = bodyAladdin->getVelocity().getY();
	if (distanceX < 20 && distanceY < 20 && distanceY >10 && velocityY < 0) {
		_aladdinOnBack = true;
	}
	else {
		_aladdinOnBack = false;
	}
}

