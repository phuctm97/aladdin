#include "DirectionController.h"

USING_NAMESPACE_ALA;

DirectionController::DirectionController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _direction( -1 ) {}

int DirectionController::getDirection() const {
  return _direction;
}

void DirectionController::setDirection( const int direction ) {
  _direction = direction;

  const auto transform = getGameObject()->getTransform();
  if ( _direction < 0 ) {
    transform->setScaleX( -ABS(transform->getScale().getX()) );
  }
  else {
    transform->setScaleX( ABS(transform->getScale().getX()) );
  }

  const auto body = getGameObject()->getComponentT<Rigidbody>();
  if ( body != NULL ) {
    body->setVelocity( Vec2( -ABS(body->getVelocity().getX()), body->getVelocity().getY() ) );
  }
}
