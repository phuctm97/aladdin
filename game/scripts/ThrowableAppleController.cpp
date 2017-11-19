#include "ThrowableAppleController.h"

USING_NAMESPACE_ALA;

ThrowableAppleController::ThrowableAppleController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _collidedWithGround( false ) {}


bool ThrowableAppleController::isCollidedWithGround() const {
  return _collidedWithGround;
}

void ThrowableAppleController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  if ( collision.getColliderA()->getGameObject()->getName() == "Ground" ||
    collision.getColliderB()->getGameObject()->getName() == "Ground" ) {
    _collidedWithGround = true;
  }
}

void ThrowableAppleController::resetCollidedWithGround() { _collidedWithGround = false; }