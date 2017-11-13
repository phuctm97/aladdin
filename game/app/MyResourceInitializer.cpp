/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/BackgroundPrefab.h"
#include "../prefabs/ForegroundPrefab.h"

void MyResourceInitializer::doRun() {
  auto gameManager = ala::GameManager::get();

  // Layers
  gameManager->addLayer("Background");
  gameManager->addLayer("Character");
  gameManager->addLayer("Foreground");

  // Textures
  new ala::Sprite("background.png", "textures/backgrounds/scene_1_0.png");
  new ala::Sprite("foreground.png", "textures/backgrounds/scene_1_1.png");

  // Animations

  // Prefabs
  new BackgroundPrefab();
  new ForegroundPrefab();
}
