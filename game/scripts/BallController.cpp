/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallController.h"

BallController::BallController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _state( 'R' ),
    _speed( 3 ),
    _logger( "BallController" ) {}

void BallController::onInitialize() {
  auto transform = getGameObject()->getComponentT<ala::Transform>();
  auto frameSize = getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize();
  transform->setPosition(
    ala::Vec2( -ala::GameManager::get()->getScreenWidth() / 2 + frameSize.getWidth() / 2,
               ala::GameManager::get()->getScreenHeight() / 2 - frameSize.getHeight() / 2 ) );

  subscribeObjectMessage(
    getGameObject(),
    "X changed",
    [=]( ala::MessageArgs* ) {
    _logger.info( "X changed\n" );
  } );
}

void BallController::onUpdate( const float delta ) {

  auto transform = getGameObject()->getComponentT<ala::Transform>();
  const auto sprite = getGameObject()->getComponentT<ala::SpriteRenderer>();
  auto audioSource = getGameObject()->getComponentT<ala::AudioSource>();

  if ( ala::Input::get()->getKeyDown( "a" ) ) {
    _logger.info( "Pressed key A" );
  }
  if ( ala::Input::get()->getKey( "a" ) ) {
    _logger.info( "Pressing key A" );
  }
  if ( ala::Input::get()->getKeyUp( "a" ) ) {
    _logger.info( "Released key A" );
  }

  switch ( _state ) {
  case 'R':
    if ( transform->getPositionX() + sprite->getFrameSize().getWidth() / 2 >= ala::GameManager::get()->getScreenWidth() ) {
      transform->setPositionX( ala::GameManager::get()->getScreenWidth() - sprite->getFrameSize().getWidth() / 2 );
      transform->setRotation( -90 );
      _state = 'D';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going down" ) );
      audioSource->playOneShot();
    }
    transform->setPositionX( transform->getPositionX() + _speed );
    break;
  case 'D':
    if ( transform->getPositionY() - sprite->getFrameSize().getHeight() / 2 <= 0 ) {
      transform->setPositionY( sprite->getFrameSize().getHeight() / 2 );
      transform->setRotation( -180 );
      _state = 'L';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going left" ) );
      audioSource->playOneShot();
    }
    transform->setPositionY( transform->getPositionY() - _speed );
    break;
  case 'L':
    if ( transform->getPositionX() - sprite->getFrameSize().getWidth() / 2 <= 0 ) {
      transform->setPositionX( sprite->getFrameSize().getWidth() / 2 );
      transform->setRotation( -270 );
      _state = 'U';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going up" ) );
      audioSource->playOneShot();
    }
    transform->setPositionX( transform->getPositionX() - _speed );
    break;
  case 'U':
    if ( transform->getPositionY() + sprite->getFrameSize().getHeight() / 2 >= ala::GameManager::get()->getScreenHeight() ) {
      transform->setPositionY( ala::GameManager::get()->getScreenHeight() - sprite->getFrameSize().getHeight() / 2 );
      transform->setRotation( 0 );
      _state = 'R';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going right" ) );
      audioSource->playOneShot();
    }
    transform->setPositionY( transform->getPositionY() + _speed );
    break;
  default: break;
  }
}

void BallController::onRelease() {}
