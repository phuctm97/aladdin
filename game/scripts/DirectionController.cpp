#include "DirectionController.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(DirectionController, ala::GameObjectComponent)

DirectionController::DirectionController( ala::GameObject* gameObject, const bool positiveAsRight, const int direction,
                                          const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _positiveAsRight( positiveAsRight ),
    _direction( direction < 0 ? -1 : 1 ) {}

bool DirectionController::isLeft() const {
  return _positiveAsRight ? _direction < 0 : _direction > 0;
}

bool DirectionController::isRight() const {
  return _positiveAsRight ? _direction > 0 : _direction < 0;
}

void DirectionController::setDirection( const int direction ) {
  _direction = direction;
}

void DirectionController::setLeft() {
  setDirection( _positiveAsRight ? -1 : 1 );
}

void DirectionController::setRight() {
  setDirection( _positiveAsRight ? 1 : -1 );
}

void DirectionController::turn() {
  setDirection( -_direction );
}

void DirectionController::addReverseCase( const std::function<bool()>& c ) {
  _reverseCases.push_back( c );
}

void DirectionController::onUpdate( const float delta ) {
  bool reverse = false;

  for ( const auto& c : _reverseCases ) {
    reverse = c();
    if ( reverse ) break;
  }

  const auto transform = getGameObject()->getTransform();
  transform->setScaleX( (reverse ? -1 : 1) * _direction * ABS(transform->getScale().getX()) );

  auto coef = _direction;
  if ( !_positiveAsRight ) coef *= -1;

  const auto body = getGameObject()->getComponentT<Rigidbody>();
  if ( body != NULL ) {
    body->setVelocity( Vec2( coef * ABS(body->getVelocity().getX()), body->getVelocity().getY() ) );
  }
}
