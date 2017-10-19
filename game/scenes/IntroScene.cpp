/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"
#include "core/GameManager.h"

IntroScene::IntroScene() : _ballDirectionChangedListener( 0 ), _logger( "IntroScene" ) {}

void IntroScene::onPreInitialize() {
  //create camera
  ala::GameManager::get()->getPrefab("MainCamera")->instantiate("MainCamera");

  ala::GameManager::get()->getPrefab("TextExample")->instantiate();
  ala::GameManager::get()->getPrefab("AnimationExample")->instantiate();
  ala::GameManager::get()->getPrefab("Ball")->instantiate();
}

void IntroScene::onPreRelease() {}
