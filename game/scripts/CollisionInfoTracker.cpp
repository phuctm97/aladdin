#include "CollisionInfoTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CollisionInfoTracker, ala::GameObjectComponent)

CollisionInfoTracker::CollisionInfoTracker( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ) {}

void CollisionInfoTracker::onCollisionEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  _collidedObjects.emplace( otherObject->getId() );
  _collidedObjectTags.emplace( otherObject->getTag() );
  _collidedColliderTags.emplace( otherCollider->getTag() );
}

void CollisionInfoTracker::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  _collidedObjects.emplace( otherObject->getId() );
  _collidedObjectTags.emplace( otherObject->getTag() );
  _collidedColliderTags.emplace( otherCollider->getTag() );
}

void CollisionInfoTracker::reset() {
  _collidedObjects.clear();
  _collidedObjectTags.clear();
  _collidedColliderTags.clear();
}

bool CollisionInfoTracker::collidedWithObject( const int id ) const {
  return _collidedObjects.count( id ) > 0;
}

bool CollisionInfoTracker::collidedWithObjectTag( const int tag ) const {
  return _collidedObjectTags.count( tag ) > 0;
}

bool CollisionInfoTracker::collidedWithColliderTag( const int tag ) const {
  return _collidedColliderTags.count(tag) > 0;
}

bool CollisionInfoTracker::collided() const {
  return !_collidedObjects.empty();
}

void CollisionInfoTracker::onRender() {
  reset();
}
