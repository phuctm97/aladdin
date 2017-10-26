#include "LimitedGravityAffectedVelocityBasedMovement.h"

USING_NAMESPACE_ALA;

LimitedGravityAffectedVelocityBasedMovement::LimitedGravityAffectedVelocityBasedMovement(
  ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _velocity( 0, 0 ), _gravity( 700 ), _limit( 58 ) {}

void LimitedGravityAffectedVelocityBasedMovement::setVelocity( const ala::Vec2& vector ) {
  _velocity = vector;
}

void LimitedGravityAffectedVelocityBasedMovement::setVelocityX( const float x ) {
  _velocity.setX( x );
}

void LimitedGravityAffectedVelocityBasedMovement::setVelocityY( const float y ) {
  _velocity.setY( y );
}

void LimitedGravityAffectedVelocityBasedMovement::addVelocity( const ala::Vec2& vector ) {
  _velocity = _velocity + vector;
}

void LimitedGravityAffectedVelocityBasedMovement::addVelocityX( const float x ) {
  _velocity.setX( _velocity.getX() + x );
}

void LimitedGravityAffectedVelocityBasedMovement::addVelocityY( const float y ) {
  _velocity.setY( _velocity.getY() + y );
}

const ala::Vec2& LimitedGravityAffectedVelocityBasedMovement::getVelocity() const {
  return _velocity;
}

float LimitedGravityAffectedVelocityBasedMovement::getGravity() const {
  return _gravity;
}

float LimitedGravityAffectedVelocityBasedMovement::getLimit() const {
  return _limit;
}

void LimitedGravityAffectedVelocityBasedMovement::onUpdate( const float delta ) {
  auto transform = getGameObject()->getTransform();
  auto spriteRenderer = getGameObject()->getComponentT<ala::SpriteRenderer>();
  auto haftHeight = spriteRenderer == NULL ? 0 : spriteRenderer->getFrameSize().getHeight() / 2;

  // update vector(acceleration)
  const auto newVelocityY = _velocity.getY() - _gravity * delta;
  _velocity.setY( newVelocityY );

  // update position(vector)
  const auto newPosition = transform->getPosition() + _velocity * delta;
  transform->setPosition( newPosition );

  if ( newPosition.getY() - haftHeight <= _limit ) {
    transform->setPositionY( _limit + haftHeight );
    _velocity.setY( 0 );
  }
}
