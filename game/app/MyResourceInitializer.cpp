/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/BackgroundPrefab.h"
#include "../prefabs/ForegroundPrefab.h"
#include "../prefabs/DebugRectPrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "Foreground" );

  // Textures
  new Sprite("debug_red.png", "textures/debug/1pixel_red.png");

  new Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );

  // Animations
  new Animation( "aladdin.anm", "animations/playable_characters/aladdin.anm" );

  // Prefabs
  new DebugRectPrefab();

  new BackgroundPrefab();
  new ForegroundPrefab();
  new AladdinPrefab();
}
