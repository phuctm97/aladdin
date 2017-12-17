#include "CharcoalBurnerCollisionTracker.h"
#include "../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CharcoalBurnerCollisionTracker, ala::GameObjectComponent)

CharcoalBurnerCollisionTracker::CharcoalBurnerCollisionTracker( ala::GameObject* gameObject, const std::string& name ):
  GameObjectComponent( gameObject, name ), _beingCollided( false ) {}

void CharcoalBurnerCollisionTracker::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == CHARCOAL_BURNER_TAG ) {
    _beingCollided = true;
  }
}

void CharcoalBurnerCollisionTracker::onTriggerExit( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  if ( otherObject->getTag() == CHARCOAL_BURNER_TAG ) {
    _beingCollided = false;
  }
}

bool CharcoalBurnerCollisionTracker::isBeingCollided() const {
  return _beingCollided;
}
