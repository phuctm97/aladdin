#include "ThrowableAppleController.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ThrowableAppleController::ThrowableAppleController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _collided( false ) {}

void ThrowableAppleController::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();
  const auto otherTag = otherObject->getTag();

  if ( otherTag == GROUND_TAG || otherTag == ENEMY_TAG ) {
    _collided = true;
  }
}

bool ThrowableAppleController::isCollided() const {
  return _collided;
}
