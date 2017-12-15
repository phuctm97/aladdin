#include "GenieBonusController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

GenieBonusController::GenieBonusController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _aladdinCollision(false), _orient(true){}

bool GenieBonusController::isCollisionAladdin() const { return _aladdinCollision; }

bool GenieBonusController::getOrient() const { return _orient;  }

void GenieBonusController::setOrient(bool orient) { _orient = orient; }

void GenieBonusController::onUpdate(const float delta) {

	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();
	const auto distanceX = ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX());
	auto bodyAladdin = aladdin->getComponentT<Rigidbody>();
	const auto velocityY = bodyAladdin->getVelocity().getY();
	if (distanceX < 15) {
		_aladdinCollision = true;
	}
	else {
		_aladdinCollision = false;
	}
}

void GenieBonusController::explosionEffect() const {
	const auto transform = getGameObject()->getTransform();
	const auto vase = GameManager::get()->getPrefab("explosion")->instantiate(
		transform->getPosition() );
}

