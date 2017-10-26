/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "DemoScene.h"

DemoScene::DemoScene() : _ballDirectionChangedListener( 0 ), _logger( "DemoScene" ) {}

void DemoScene::onPreInitialize() {
  // create camera
  ala::GameManager::get()->getPrefab( "Basic Example" )->instantiate();
  ala::GameManager::get()->getPrefab( "Animation And State Example" )->instantiate();
  ala::GameManager::get()->getPrefab( "Text Example" )->instantiate();
}

void DemoScene::onPreRelease() {}
