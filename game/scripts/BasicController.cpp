/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BasicController.h"

BasicController::BasicController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _state( 'R' ),
    _speed( 3 ),
    _logger( "BasicController" ) {}

void BasicController::onInitialize() {
  auto transform = getGameObject()->getComponentT<ala::Transform>();
  auto frameSize = getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize();
  auto audioSource = getGameObject()->getComponentT<ala::AudioSource>();

  // set initial position
  transform->setPosition(
    ala::Vec2( -ala::GameManager::get()->getScreenWidth() / 2 + frameSize.getWidth() / 2,
               ala::GameManager::get()->getScreenHeight() / 2 - frameSize.getHeight() / 2 ) );

  // debug message listener
  subscribeGlobalMessage(
    "Ball Direction Changed",
    [=]( ala::MessageArgs* args ) {
      auto strArgs = static_cast<ala::StringMessageArgs*>(args);

      // debug logger
      if ( strArgs != NULL ) _logger.info( strArgs->getPayload().c_str() );

      // debug audio
      audioSource->playOneShot();
    } );
}

void BasicController::onUpdate( const float delta ) {

  auto transform = getGameObject()->getComponentT<ala::Transform>();
  const auto sprite = getGameObject()->getComponentT<ala::SpriteRenderer>();
  auto audioSource = getGameObject()->getComponentT<ala::AudioSource>();

  switch ( _state ) {
  case 'R': {
    if ( transform->getPositionX() + sprite->getFrameSize().getWidth() / 2
      >= ala::GameManager::get()->getScreenWidth() / 2 ) {

      // state transform
      transform->setPositionX( ala::GameManager::get()->getScreenWidth() / 2 - sprite->getFrameSize().getWidth() / 2 );
      transform->setRotation( -90 );
      _state = 'D';

      // debug message publisher
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed",
                                                                new ala::StringMessageArgs( "Ball going down" ) );
    }
    else {
      // move
      transform->setPositionX( transform->getPositionX() + _speed );
    }
  }
    break;
  case 'D': {
    if ( transform->getPositionY() - sprite->getFrameSize().getHeight() / 2
      <= -ala::GameManager::get()->getScreenHeight() / 2 ) {

      // state transform
      transform->setPositionY(
        sprite->getFrameSize().getHeight() / 2 - ala::GameManager::get()->getScreenHeight() / 2 );
      transform->setRotation( -180 );
      _state = 'L';

      // debug message publisher
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed",
                                                                new ala::StringMessageArgs( "Ball going left" ) );
    }
    else {
      // move
      transform->setPositionY( transform->getPositionY() - _speed );
    }
  }
    break;
  case 'L': {
    if ( transform->getPositionX() - sprite->getFrameSize().getWidth() / 2
      <= -ala::GameManager::get()->getScreenWidth() / 2 ) {

      // state transform
      transform->setPositionX( sprite->getFrameSize().getWidth() / 2 - ala::GameManager::get()->getScreenWidth() / 2 );
      transform->setRotation( -270 );
      _state = 'U';

      // debug message publisher
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed",
                                                                new ala::StringMessageArgs( "Ball going up" ) );
    }
    else {
      // move
      transform->setPositionX( transform->getPositionX() - _speed );
    }
  }
    break;
  case 'U': {
    if ( transform->getPositionY() + sprite->getFrameSize().getHeight() / 2
      >= ala::GameManager::get()->getScreenHeight() / 2 ) {

      // state transform
      transform->setPositionY( ala::GameManager::get()->getScreenHeight() / 2
        - sprite->getFrameSize().getHeight() / 2 );
      transform->setRotation( 0 );
      _state = 'R';

      // debug message publisher
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed",
                                                                new ala::StringMessageArgs( "Ball going right" ) );
    }
    else {
      // move
      transform->setPositionY( transform->getPositionY() + _speed );
    }
  }
    break;
  default: break;
  }
}

void BasicController::onRelease() {}
