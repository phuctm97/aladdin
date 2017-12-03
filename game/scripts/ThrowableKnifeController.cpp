#include "ThrowableKnifeController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ThrowableKnifeController::ThrowableKnifeController(ala::GameObject* gameObject, const std::string& name)
	: GameObjectComponent(gameObject, name), _collidedWithGround(false), _colliedWithEnemy(false) {}

bool ThrowableKnifeController::isCollidedWithGround() const {
	return _collidedWithGround;
}

void ThrowableKnifeController::onTriggerEnter(const ala::CollisionInfo& collision) {
	if (collision.getColliderA()->getTag() == GROUND_TAG ||
		collision.getColliderB()->getTag() == GROUND_TAG) {
		_collidedWithGround = true;
	}

	if (collision.getColliderA()->getTag() == ENEMY_TAG ||
		collision.getColliderB()->getTag() == ENEMY_TAG) {
		_colliedWithEnemy = true;
	}
}

bool ThrowableKnifeController::isCollidedWithEnemy() const
{
	return _colliedWithEnemy;
}
