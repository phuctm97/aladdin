/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"
#include "core/GameManager.h"

IntroScene::IntroScene(): Scene( "IntroScene" ) {}

bool IntroScene::onPreInit() {
  ala::GameManager::get()->getPrefab( "Ball" )->instantiate();
  return true;
}
