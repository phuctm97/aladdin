/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"
#include "../scripts/CameraController.h"

USING_NAMESPACE_ALA;

ExperimentalScene::ExperimentalScene() : _logger( "ExperimentalScene" ) {}

void ExperimentalScene::onPreInitialize() {
  // ReSharper disable CppNonReclaimedResourceAcquisition
  new CameraController( getMainCamera() );

  const auto gameManager = GameManager::get();
  gameManager->getPrefab( "Background" )->instantiate( "Background" );
  gameManager->getPrefab( "Foreground" )->instantiate();
  gameManager->getPrefab( "Aladdin" )->instantiate( "Aladdin" );
  gameManager->getPrefab( "Ground" )->instantiate( "Ground" );
}

void ExperimentalScene::onPreRelease() {}
