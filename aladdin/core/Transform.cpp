/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Transform.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Transform, ala::GameObjectComponent )

Transform::Transform( GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _rotation( 0 ) {}

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

void Transform::setPositionX( float x ) {
  _position.setX( x );
}

void Transform::setPositionY( float y ) {
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

void Transform::setRotation( float rotation ) {
  _rotation = rotation;
}
}
