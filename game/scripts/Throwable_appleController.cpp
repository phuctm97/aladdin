#include "Throwable_appleController.h"

USING_NAMESPACE_ALA;
Throwable_appleController::Throwable_appleController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name),
	_logger("Throwable_AppleController"), _collidedWithGround(false) {}


bool Throwable_appleController::isCollidedWithGround() const
{
	return _collidedWithGround;
}

void Throwable_appleController::onTriggerEnter(const ala::CollisionInfo& collision) {
	if (collision.getObjectA()->getName() == "Ground" || collision.getObjectB()->getName() == "Ground") {
		_collidedWithGround = true;
	}
}

void Throwable_appleController::resetCollidedWithGround() { _collidedWithGround = false; }







