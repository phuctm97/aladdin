/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallController.h"
#include "core/StringMessageArg.h"

BallController::BallController( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _state( 'R' ),
    _speed( 2 ) {}

void BallController::onUpdate( const float delta ) {
  auto transform = getGameObject()->getComponentT<ala::Transform>();
  const auto sprite = getGameObject()->getComponentT<ala::SpriteRenderer>()->getSprite();

  switch ( _state ) {
  case 'R':
    if ( transform->getPositionX() + sprite->getContentSize().getWidth() >= ala::GameManager::get()->getScreenWidth() ) {
      transform->setPositionX( ala::GameManager::get()->getScreenWidth() - sprite->getContentSize().getWidth() );
      _state = 'D';
	  ala::GameManager::get()->getGlobalMessenger()->broadcast("Ball Direction Changed", new ala::StringMessageArg("Ball going down"));
    }
    transform->setPositionX( transform->getPositionX() + _speed );
    break;
  case 'D':
    if ( transform->getPositionY() + sprite->getContentSize().getHeight() >= ala::GameManager::get()->getScreenHeight() ) {
      transform->setPositionY( ala::GameManager::get()->getScreenHeight() - sprite->getContentSize().getHeight() );
      _state = 'L';
	  ala::GameManager::get()->getGlobalMessenger()->broadcast("Ball Direction Changed", new ala::StringMessageArg("Ball going left"));
    }
    transform->setPositionY( transform->getPositionY() + _speed );
    break;
  case 'L':
    if ( transform->getPositionX() <= 0 ) {
      transform->setPositionX( 0 );
      _state = 'U';
	  ala::GameManager::get()->getGlobalMessenger()->broadcast("Ball Direction Changed", new ala::StringMessageArg("Ball going up"));
    }
    transform->setPositionX( transform->getPositionX() - _speed );
    break;
  case 'U':
    if ( transform->getPositionY() <= 0 ) {
      transform->setPositionY( 0 );
      _state = 'R';
	  ala::GameManager::get()->getGlobalMessenger()->broadcast("Ball Direction Changed", new ala::StringMessageArg("Ball going right"));
    }
    transform->setPositionY( transform->getPositionY() - _speed );
    break;
  default: break;
  }
}

void BallController::onInitialize ( )
{
	_token = getGameObject (  )->getMessenger (  )->subscribe ( "X changed", [&](ala::IMessageArg*)
	{
		OutputDebugString("X changed\n");
	});
}

void BallController::onRelease ( )
{
	getGameObject()->getMessenger()->unsubscribe("X changed", _token);
}
