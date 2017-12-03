/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/NormalTextPrefab.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/GroundPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"
#include "../prefabs/ThinGuardPrefab.h"
#include "../prefabs/BigTextPrefab.h"
#include "../prefabs/FatGuardPrefab.h"
#include "../prefabs/AdorableGuardPrefab.h"
#include "../prefabs/ThrowableKnifePrefab.h"

USING_NAMESPACE_ALA;

void MyResourceInitializer::doRun() {
  auto gameManager = GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "Foreground" );
  gameManager->addLayer( "Apple");
  gameManager->addLayer( "Enemy");
  gameManager->addLayer( "Knife");

  // Textures
  new Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new Sprite( "cutscenes.png", "textures/miscellaneous/cutscenes.png" );
  new Sprite( "guards.png", "textures/enemies/guards.png");

  // Fonts
  new Font( "aladdin.ttf", "aladdin.ttf", "fonts" );
  new Font( "arcade.ttf", "arcade.ttf", "fonts" );

  // Animations
  new Animation( "aladdin.anm", "animations/playable_characters/aladdin.anm" );
  new Animation( "cutscenes.anm", "animations/miscellaneous/cutscenes.anm" );
  new Animation( "guards.anm", "animations/enemies/guards.anm");

  // Prefabs
  new NormalTextPrefab();
  new BigTextPrefab();

  new AladdinPrefab();
  new ThrowableApplePrefab();
  new GroundPrefab();
  new ThinGuardPrefab();
  new FatGuardPrefab();
  new AdorableGuardPrefab();
  new ThrowableKnifePrefab();
}
