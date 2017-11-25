#include "Collider.h"
#include "PhysicsManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Collider, ala::GameObjectComponent)

Collider::Collider( GameObject* gameObject, const bool isTrigger, const Vec2& offset, const Size& size,
                    const int tag, const int physicsLayer,
                    const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _offset( offset ),
    _size( size ),
    _isTrigger( isTrigger ),
    _tag( tag ),
    _physicsLayer( physicsLayer ) {}

Rect Collider::getBoundingRect() const {
  Rect rect;

  const auto transform = getGameObject()->getTransform();

  rect.setTopLeft( transform->getWorldPosition() + _offset + Vec2( -_size.getWidth() / 2, -_size.getHeight() / 2 ) );
  rect.setSize( _size );

  return rect;
}

void Collider::onInitialize() {
  PhysicsManager::get()->attach( this );
}

void Collider::onRelease() {
  PhysicsManager::get()->detach( this );
}

Collider::~Collider() {}

void Collider::setOffset( const Vec2& offset ) {
  _offset = offset;
}

void Collider::setSize( const Size& size ) {
  _size = size;
}

void Collider::setTrigger( const bool trigger ) {
  _isTrigger = trigger;
}

void Collider::setPhysicsLayer( const int physicsLayer ) {
  _physicsLayer = physicsLayer;
}

void Collider::ignoreTag( const int tag ) {
  _ignoredTags.emplace( tag );
}

int Collider::getPhysicsLayer() const {
  return _physicsLayer;
}

const std::unordered_set<int>& Collider::getIgnoredTags() const {
  return _ignoredTags;
}

bool Collider::isIgnoredBy( Collider* other ) const {
  return _ignoredTags.count( other->getTag() ) > 0;
}

const Vec2& Collider::getOffset() const {
  return _offset;
}

const Size& Collider::getSize() const {
  return _size;
}

bool Collider::isTrigger() const {
  return _isTrigger;
}
}
