/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"

IntroScene::IntroScene() : _ballDirectionChangedListener( 0 ), _logger( "IntroScene" ) {}

void IntroScene::onPreInitialize() {
  ala::GameManager::get()->getPrefab( "Camera" )->instantiate();
  ala::GameManager::get()->getPrefab( "AnimationExample" )->instantiate();
	ala::GameManager::get()->getPrefab("Ball")->instantiate();
}

void IntroScene::onPreRelease() {}
