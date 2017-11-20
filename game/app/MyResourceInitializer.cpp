/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/NormalTextPrefab.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/GroundPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "Foreground" );

  // Textures
  new Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new Sprite( "cutscenes.png", "textures/miscellaneous/cutscenes.png" );

  // Fonts
  new Font( "arcade.ttf", "fonts/arcade.ttf" );

  // Animations
  new Animation( "aladdin.anm", "animations/playable_characters/aladdin.anm" );
  new Animation( "cutscenes.anm", "animations/miscellaneous/cutscenes.anm" );

  // Prefabs
  new NormalTextPrefab();

  new AladdinPrefab();
  new ThrowableApplePrefab();
  new GroundPrefab();
}
