/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Transform2.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1( ala::Transform2, "ala::Transform2", ala::GameObjectComponent )

Transform2::Transform2( GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _rotation( 0 ) {}

const Vec2& Transform2::getPosition() const {
  return _position;
}

float Transform2::getPositionX() const {
  return _position.getX();
}

float Transform2::getPositionY() const {
  return _position.getY();
}

void Transform2::setPosition( const Vec2& position ) {
  _position = position;
}

void Transform2::setPositionX( float x ) {
  _position.setX( x );
}

void Transform2::setPositionY( float y ) {
  _position.setY( y );
}

const Vec2& Transform2::getScale() const {
  return _scale;
}

void Transform2::setScale( const Vec2& scale ) {
  _scale = scale;
}

float Transform2::getRotation() const {
  return _rotation;
}

void Transform2::setRotation( float rotation ) {
  _rotation = rotation;
}
}
