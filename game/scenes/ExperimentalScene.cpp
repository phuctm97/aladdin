/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"

USING_NAMESPACE_ALA;

ExperimentalScene::ExperimentalScene() : _logger( "ExperimentalScene" ) {}

void ExperimentalScene::onPreInitialize() {
  // constants
  const auto gameManager = GameManager::get();

  // configurations
  enablePhysics( Vec2( 0, -500.0f ) );

  new CameraController( getMainCamera() );

  // initial objects
  gameManager->getPrefab( "Background" )->instantiate( "Background" );
  gameManager->getPrefab( "Foreground" )->instantiate();
  gameManager->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
  gameManager->getPrefab( "Ground" )->instantiate( "Ground" );
}

void ExperimentalScene::onPreRelease() {}
