/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"

IntroScene::IntroScene() : _logger( "IntroScene" ) {}

void IntroScene::onPreInitialize() {
  auto gameManager = ala::GameManager::get();

  gameManager->getPrefab( "Camera" )->instantiate();
  gameManager->getPrefab( "Background" )->instantiate( "Background" );
  gameManager->getPrefab( "Foreground" )->instantiate( "Foreground" );
  gameManager->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
}

void IntroScene::onPreRelease() {}
