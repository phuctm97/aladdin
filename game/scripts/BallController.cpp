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
  auto frameSize = getGameObject()->getComponentT<ala::SpriteRenderer>()->getFrameSize();
  transform->setPosition( ala::Vec2( -ala::GameManager::get (  )->getScreenWidth (  )/2 + frameSize.getWidth (  )/2, ala::GameManager::get (  )->getScreenHeight (  )/2 - frameSize.getHeight (  )/2 ) );

  subscribeObjectMessage(
    getGameObject(),
    "X changed",
    [=]( ala::MessageArgs* ) {
    _logger.info( "X changed\n" );
  } );
}

void BallController::onUpdate( const float delta ) 
{

}

void BallController::onRelease() {}
