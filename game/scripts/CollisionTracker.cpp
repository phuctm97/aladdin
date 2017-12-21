#include "CollisionTracker.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(CollisionTracker, ala::GameObjectComponent)

CollisionTracker::CollisionTracker( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _collidedObjectFlags( 0 ), _collidedColliderFlags( 0 ) {}

void CollisionTracker::onCollisionEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  _collidedObjects.emplace( otherObject->getId() );
  _collidedObjectTags.emplace( otherObject->getTag() );
  _collidedColliderTags.emplace( otherCollider->getTag() );
  _collidedObjectFlags |= otherObject->getFlags();
  _collidedColliderFlags |= otherCollider->getFlags();
}

void CollisionTracker::onTriggerEnter( const ala::CollisionInfo& collision ) {
  const auto otherCollider = collision.getColliderA()->getGameObject() == getGameObject()
                               ? collision.getColliderB()
                               : collision.getColliderA();
  const auto otherObject = otherCollider->getGameObject();

  _collidedObjects.emplace( otherObject->getId() );
  _collidedObjectTags.emplace( otherObject->getTag() );
  _collidedColliderTags.emplace( otherCollider->getTag() );
  _collidedObjectFlags |= otherObject->getFlags();
  _collidedColliderFlags |= otherCollider->getFlags();
}

void CollisionTracker::reset() {
  _collidedObjects.clear();
  _collidedObjectTags.clear();
  _collidedColliderTags.clear();
  _collidedObjectFlags = 0;
  _collidedColliderFlags = 0;
}

bool CollisionTracker::collidedWithObject( const int id ) const {
  return _collidedObjects.count( id ) > 0;
}

bool CollisionTracker::collidedWithObjectTag( const int tag ) const {
  return _collidedObjectTags.count( tag ) > 0;
}

bool CollisionTracker::collidedWithColliderTag( const int tag ) const {
  return _collidedColliderTags.count( tag ) > 0;
}

bool CollisionTracker::collided() const {
  return !_collidedObjects.empty();
}

bool CollisionTracker::collidedWithObjectFlag( const long flag ) const {
  return (_collidedObjectFlags & flag) != 0;
}

bool CollisionTracker::collidedWithObjectFlags( const long flags ) const {
  return (_collidedObjectFlags & flags) > flags;
}

bool CollisionTracker::collidedWithColliderFlag( const long flag ) const {
  return (_collidedColliderFlags & flag) != 0;
}

bool CollisionTracker::collidedWithColliderFlags( const long flags ) const {
  return (_collidedColliderFlags & flags) > flags;
}

long CollisionTracker::getCollidedObjectFlags() const {
  return _collidedObjectFlags;
}

long CollisionTracker::getCollidedColliderFlags() const {
  return _collidedColliderFlags;
}
