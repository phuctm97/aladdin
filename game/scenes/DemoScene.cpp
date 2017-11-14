/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "DemoScene.h"

USING_NAMESPACE_ALA;

DemoScene::DemoScene() : _ballDirectionChangedListener( 0 ), _logger( "DemoScene" ) {}

void DemoScene::onPreInitialize() {
  const auto gameManager = GameManager::get();
  const auto cameraTransform = gameManager->getMainCamera()->getTransform();
  cameraTransform->setPositionX( cameraTransform->getPositionX() + 100 );

  // create camera
  gameManager->getPrefab( "Basic Example" )->instantiate();
  gameManager->getPrefab( "Animation And State Example" )->instantiate();
  gameManager->getPrefab( "Text Example" )->instantiate();
}

void DemoScene::onPreRelease() {}
