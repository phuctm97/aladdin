#include "ThrowableAppleController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ThrowableAppleController::ThrowableAppleController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _collidedWithGround( false ), _colliedWithEnemy (false){}


bool ThrowableAppleController::isCollidedWithGround() const {
  return _collidedWithGround;
}

void ThrowableAppleController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getTag() == GROUND_TAG ||
    collision.getColliderB()->getGameObject()->getTag() == GROUND_TAG ) {
    _collidedWithGround = true;
  }

  if (collision.getColliderA()->getGameObject()->getTag() == ENEMY_TAG ||
	  collision.getColliderB()->getGameObject()->getTag() == ENEMY_TAG) {
	  _colliedWithEnemy = true;
  }
}

bool ThrowableAppleController::isCollidedWithEnemy() const
{
	return _colliedWithEnemy;
}
