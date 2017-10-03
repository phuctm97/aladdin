/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"
#include "core/GameManager.h"
#include "core/StringMessageArgs.h"
#include "2d/Camera.h"

IntroScene::IntroScene() : _ballDirectionChangedListener( 0 ), _logger( "IntroScene" ) {}

void IntroScene::onPreInitialize() {
  auto camera = new ala::GameObject(this, "Camera");

  auto cameraComponent = new ala::Camera(camera, "Camera 2d", ala::GameManager::get()->getScreenWidth(), ala::GameManager::get()->getScreenHeight(), 0, ala::Vec2(1.0f, 1.0f));
  ala::GameManager::get()->getPrefab( "Ball" )->instantiate();

  subscribeGlobalMessage(
    "Ball Direction Changed",
    [=]( ala::MessageArgs* arg ) {

    _logger.info( static_cast<ala::StringMessageArgs*>(arg)->getPayload().c_str() );

  } );
}

void IntroScene::onPreRelease() {}
