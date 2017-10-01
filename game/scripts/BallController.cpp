/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallController.h"

BallController::BallController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _state( 'R' ),
    _speed( 2 ) {}

void BallController::onUpdate( float delta ) {
  auto transform = getGameObject()->getComponentT<ala::Transform>();
  const auto sprite = getGameObject()->getComponentT<ala::SpriteRenderer>()->getSprite();

  switch ( _state ) {
  case 'R':
    if ( transform->getPositionX() + sprite->getContentSize().getWidth() >= ala::GameManager::get()->getScreenWidth() ) {
      transform->setPositionX( ala::GameManager::get()->getScreenWidth() - sprite->getContentSize().getWidth() );
      _state = 'D';
    }
    transform->setPositionX( transform->getPositionX() + _speed );
    break;
  case 'D':
    if ( transform->getPositionY() + sprite->getContentSize().getHeight() >= ala::GameManager::get()->getScreenHeight() ) {
      transform->setPositionY( ala::GameManager::get()->getScreenHeight() - sprite->getContentSize().getHeight() );
      _state = 'L';
    }
    transform->setPositionY( transform->getPositionY() + _speed );
    break;
  case 'L':
    if ( transform->getPositionX() <= 0 ) {
      transform->setPositionX( 0 );
      _state = 'U';
    }
    transform->setPositionX( transform->getPositionX() - _speed );
    break;
  case 'U':
    if ( transform->getPositionY() <= 0 ) {
      transform->setPositionY( 0 );
      _state = 'R';
    }
    transform->setPositionY( transform->getPositionY() - _speed );
    break;
  default: break;
  }
}
