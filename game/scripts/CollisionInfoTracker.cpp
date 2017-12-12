#include "CollisionInfoTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CollisionInfoChecker, ala::GameObjectComponent)

CollisionInfoChecker::CollisionInfoChecker( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

void CollisionInfoChecker::onCollisionEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  _collidedObjects.emplace( otherObject->getId() );
  _collidedObjectTags.emplace( otherObject->getTag() );
  _collidedColliderTags.emplace( otherCollider->getTag() );
}

void CollisionInfoChecker::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  _collidedObjects.emplace( otherObject->getId() );
  _collidedObjectTags.emplace( otherObject->getTag() );
  _collidedColliderTags.emplace( otherCollider->getTag() );
}

void CollisionInfoChecker::reset() {
  _collidedObjects.clear();
  _collidedObjectTags.clear();
  _collidedColliderTags.clear();
}

bool CollisionInfoChecker::collidedWithObject( const int id ) const {
  return _collidedObjects.count( id ) > 0;
}

bool CollisionInfoChecker::collidedWithObjectTag( const int tag ) const {
  return _collidedObjectTags.count( tag ) > 0;
}

bool CollisionInfoChecker::collidedWithColliderTag( const int tag ) const {
  return _collidedColliderTags.count(tag) > 0;
}

bool CollisionInfoChecker::collided() const {
  return !_collidedObjects.empty();
}

void CollisionInfoChecker::onRender() {
  reset();
}
