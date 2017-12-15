#include "ThrowVaseController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ThrowVaseController::ThrowVaseController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false) {}

bool ThrowVaseController::isCollidedWithGround() const { return _collidedWithGround; }

bool ThrowVaseController::isAladdinNear() const { return _nearAladdin; }

void ThrowVaseController::resetCollidedWithGround() { _collidedWithGround = false; }

void ThrowVaseController::onUpdate(const float delta) {
	/*_nearAladdin = true;
	return;*/

	const auto aladdin = GameManager::get()->getObjectByName("Aladdin");
	if (aladdin == NULL) return;

	const auto visibleWidth = GameManager::get()->getVisibleWidth();

	if (ABS(getGameObject()->getTransform()->getPosition().getX() - aladdin->getTransform()->getPosition().getX()) < 40
		) {
		_nearAladdin = true;
	}
	else {
		_nearAladdin = false;
	}
}

void ThrowVaseController::onCollisionEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
		collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG) {
		_collidedWithGround = true;
	}
}

void ThrowVaseController::throwVase(const char direction, const float directX, const float directY,
	const float impulseX, const float impulseY) const {
	const auto transform = getGameObject()->getTransform();
	const auto collider = getGameObject()->getComponentT<Collider>();

	const auto vase = GameManager::get()->getPrefab("Throw Vase")->instantiate(
		transform->getPosition() + Vec2(collider->getSize().getWidth() / 2 + directX,
			collider->getSize().getHeight() / 2 + directY));
	const auto vaseStateManager = vase->getComponentT<StateManager>();

	/*const auto vaseBody = vase->getComponentT<Rigidbody>();
	vaseBody->addImpulse(Vec2(impulseX, impulseY));*/
}