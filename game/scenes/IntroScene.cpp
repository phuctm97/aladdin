/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"
#include "core/GameManager.h"

IntroScene::IntroScene() {}

void IntroScene::onPreInitialize() {
  ala::GameManager::get()->getPrefab( "Ball" )->instantiate();
}
