/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Transform.h"
#include "StdHelper.h"
#include "GameManager.h"
#include "IMessageArg.h"

NAMESPACE_ALA
{
// ===================================================
// Basic
// ===================================================

ALA_CLASS_SOURCE_1( ala::Transform, ala::GameObjectComponent )

Transform::Transform( GameObject* gameObject, Transform* parentTransform, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _position( 0, 0 ),
    _scale( 1, 1 ),
    _rotation( 0 ),
    _parent( parentTransform ) {
  if ( _parent != NULL ) {
    _parent->addChild( this );
  }
}

Transform::~Transform() {}

const Vec2& Transform::getPosition() const {
  return _position;
}

float Transform::getPositionX() const {
  return _position.getX();
}

float Transform::getPositionY() const {
  return _position.getY();
}

void Transform::setPosition( const Vec2& position ) {
  _position = position;
}

void Transform::setPositionX( const float x ) {
  _position.setX( x );
}

void Transform::setPositionY( const float y ) {
  _position.setY( y );
}

const Vec2& Transform::getScale() const {
  return _scale;
}

void Transform::setScale( const Vec2& scale ) {
  _scale = scale;
}

float Transform::getRotation() const {
  return _rotation;
}

void Transform::setRotation( const float rotation ) {
  _rotation = rotation;
}

// =======================================================
// Children management
// =======================================================

std::vector<Transform*> Transform::getChildren() const {
  return _children;
}

Transform* Transform::getChild( const int index ) const {
  return _children[index];
}

Transform* Transform::getParent() const {
  return _parent;
}

void Transform::addChild( Transform* child ) {
  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  if ( StdHelper::vectorContain( _children, child ) ) return;
  _children.push_back( child );
}

void Transform::removeChild( Transform* child ) {
  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  StdHelper::vectorErase( _children, child );
}

void Transform::onRelease() {
  // release child transform
  if ( _parent != NULL ) {
    _parent->removeChild( this );
  }
}

void Transform::onUpdate( const float delta ) {
  for ( auto transform : _children ) {
    transform->getGameObject()->update( delta );
  }
}

void Transform::onRender() {
  for ( auto transform : _children ) {
    transform->getGameObject()->render();
  }
}
}
