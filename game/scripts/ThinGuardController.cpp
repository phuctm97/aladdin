#include "ThinGuardController.h"


USING_NAMESPACE_ALA;
ThinGuardController::ThinGuardController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false) {}

bool ThinGuardController::isCollidedWithGround() const { return _collidedWithGround; }

void ThinGuardController::onUpdate(const float delta) {}

void ThinGuardController::onCollisionEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getGameObject()->getName() == "Ground" ||
		collision.getColliderB()->getGameObject()->getName() == "Ground") {
		_collidedWithGround = true;
	}
}