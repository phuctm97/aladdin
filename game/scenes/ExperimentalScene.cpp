/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "ExperimentalScene.h"

ExperimentalScene::ExperimentalScene() : _logger( "ExperimentalScene" ) {}

void ExperimentalScene::onPreInitialize() {
  ala::GameManager::get()->getPrefab( "Background" )->instantiate();
  ala::GameManager::get()->getPrefab( "Foreground" )->instantiate();
}

void ExperimentalScene::onPreRelease() {}
