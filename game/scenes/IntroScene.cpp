/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"

IntroScene::IntroScene() : _ballDirectionChangedListener( 0 ), _logger( "IntroScene" ) {}

void IntroScene::onPreInitialize() {
  ala::GameManager::get()->getPrefab( "Camera" )->instantiate();
  ala::GameManager::get()->getPrefab( "Ball" )->instantiate();

  subscribeGlobalMessage(
    "Ball Direction Changed",
    [=]( ala::MessageArgs* arg ) {

    _logger.info( static_cast<ala::StringMessageArgs*>(arg)->getPayload().c_str() );

  } );
}

void IntroScene::onPreRelease() {}
