#include "CamelController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

CamelController::CamelController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _aladdinOnBack(false) {}

bool CamelController::isAladdinOnBack() const { return _aladdinOnBack; }

void CamelController::onUpdate(const float delta) {

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

void CamelController::puffSaliva(const float directX, const float directY,
	const float impulseX, const float impulseY) const {
	const auto transform = getGameObject()->getTransform();
	const auto collider = getGameObject()->getComponentT<Collider>();

	const auto saliva = GameManager::get()->getPrefab("saliva")->instantiate(
		transform->getPosition() + Vec2(collider->getSize().getWidth() / 2 + directX,
			collider->getSize().getHeight() / 2 + directY));
	const auto vaseStateManager = saliva->getComponentT<StateManager>();

	/*const auto vaseBody = vase->getComponentT<Rigidbody>();
	vaseBody->addImpulse(Vec2(impulseX, impulseY));*/
}
