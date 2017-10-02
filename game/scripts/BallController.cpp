/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallController.h"

BallController::BallController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _state( 'R' ),
    _speed( 2 )
{
}

void BallController::onInitialize ( )
{
  auto transform = getGameObject()->getComponentT<ala::Transform>();
  transform->setScale( ala::Vec2(2.f, 2.f));
  auto frameSize = getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize();
  transform->setPosition(ala::Vec2(frameSize.getWidth (  )/2, frameSize.getHeight (  )/2));
}

void BallController::onUpdate( const float delta ) {

  auto transform = getGameObject()->getComponentT<ala::Transform>();
  const auto sprite = getGameObject()->getComponentT<ala::SpriteRenderer>();
  switch ( _state ) {
  case 'R':
    if ( transform->getPositionX() + sprite->getFrameSize (  ).getWidth (  )/2 >= ala::GameManager::get()->getScreenWidth() ) {
      transform->setPositionX( ala::GameManager::get()->getScreenWidth() - sprite->getFrameSize().getWidth()/2);
      transform->setRotation(-90);
      _state = 'D';
    }
    transform->setPositionX( transform->getPositionX() + _speed );
    //transform->setScale(ala::Vec2(2.f, 2.f));
    break;
  case 'D':
    if ( transform->getPositionY() + sprite->getFrameSize().getHeight (  )/2 >= ala::GameManager::get()->getScreenHeight() ) {
      transform->setPositionY(ala::GameManager::get()->getScreenHeight() - sprite->getFrameSize().getHeight()/2);
      transform->setRotation(-180);
      _state = 'L';
    }
    transform->setPositionY( transform->getPositionY() + _speed );
    //transform->setScale(ala::Vec2(2.f, 2.f));
    break;
  case 'L':
    if ( transform->getPositionX() - sprite->getFrameSize (  ).getWidth (  )/2 <= 0 ) {
      transform->setPositionX(sprite->getFrameSize().getWidth() / 2);
      transform->setRotation(-270);
      _state = 'U';
    }
    transform->setPositionX( transform->getPositionX() - _speed );
    //transform->setScale(ala::Vec2(0.5f, 0.5f));
    break;
  case 'U':
    if (transform->getPositionY() - sprite->getFrameSize().getHeight() / 2 <= 0 ) {
      transform->setPositionY(sprite->getFrameSize().getHeight() / 2);
      transform->setRotation(0);
      _state = 'R';
    }
    transform->setPositionY( transform->getPositionY() - _speed );
    //transform->setScale(ala::Vec2(0.5f, 0.5f));
    break;
  default: break;
  }
}
