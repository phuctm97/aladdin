/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallController.h"
#include "core/StringMessageArgs.h"

BallController::BallController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _state( 'R' ),
    _speed( 3 ),
    _logger( "BallController" ) {}

void BallController::onInitialize() {
  auto transform = getGameObject()->getComponentT<ala::Transform>();
  transform->setScale( ala::Vec2( 2.f, 2.f ) );
  auto frameSize = getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize();
  transform->setPosition( ala::Vec2( frameSize.getWidth() / 2, frameSize.getHeight() / 2 ) );

  ala::GameObject* ball2 = new ala::GameObject( getGameObject(), "Ball2" );
  new ala::SpriteRenderer( ball2, "ball.png" );
  ball2->getTransform()->setPosition( 100, 100 );

  //transform->addChild(ball2->getTransform (  ));

  transform->setScale( 1.5f );
  ball2->getTransform()->setScale( 1.5f );

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
  switch ( _state ) {
  case 'R':
    if ( transform->getPositionX() + sprite->getFrameSize().getWidth() / 2 >= ala::GameManager::get()->getScreenWidth() ) {
      transform->setPositionX( ala::GameManager::get()->getScreenWidth() - sprite->getFrameSize().getWidth() / 2 );
      transform->setRotation( -90 );
      _state = 'D';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going down" ) );
    }
    transform->setPositionX( transform->getPositionX() + _speed );
    break;
  case 'D':
    if ( transform->getPositionY() + sprite->getFrameSize().getHeight() / 2 >= ala::GameManager::get()->getScreenHeight() ) {
      transform->setPositionY( ala::GameManager::get()->getScreenHeight() - sprite->getFrameSize().getHeight() / 2 );
      transform->setRotation( -180 );
      _state = 'L';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going left" ) );
    }
    transform->setPositionY( transform->getPositionY() + _speed );
    break;
  case 'L':
    if ( transform->getPositionX() - sprite->getFrameSize().getWidth() / 2 <= 0 ) {
      transform->setPositionX( sprite->getFrameSize().getWidth() / 2 );
      transform->setRotation( -270 );
      _state = 'U';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going up" ) );
    }
    transform->setPositionX( transform->getPositionX() - _speed );
    break;
  case 'U':
    if ( transform->getPositionY() - sprite->getFrameSize().getHeight() / 2 <= 0 ) {
      transform->setPositionY( sprite->getFrameSize().getHeight() / 2 );
      transform->setRotation( 0 );
      _state = 'R';
      ala::GameManager::get()->getGlobalMessenger()->broadcast( "Ball Direction Changed", new ala::StringMessageArgs( "Ball going right" ) );
    }
    transform->setPositionY( transform->getPositionY() - _speed );
    break;
  default: break;
  }
}

void BallController::onRelease() {}
