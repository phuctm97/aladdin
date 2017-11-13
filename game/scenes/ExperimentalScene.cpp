/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"

ExperimentalScene::ExperimentalScene() : _logger( "ExperimentalScene" ) {}

void ExperimentalScene::onPreInitialize() {
  new CameraController( getMainCamera() );

  ala::GameManager::get()->getPrefab( "Background" )->instantiate( "Background" );
  ala::GameManager::get()->getPrefab( "Foreground" )->instantiate();
  ala::GameManager::get()->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
}

void ExperimentalScene::onPreRelease() {}
