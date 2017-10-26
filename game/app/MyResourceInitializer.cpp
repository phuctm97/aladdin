/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/CameraPrefab.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"
#include "../prefabs/BackgroundPrefab.h"
#include "../prefabs/ForegroundPrefab.h"

void MyResourceInitializer::run() {
  auto gameManager = ala::GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "Foreground" );

  // Textures
  new ala::Sprite( "background.png", "textures/backgrounds/scene_1_0.png" );
  new ala::Sprite( "foreground.png", "textures/backgrounds/scene_1_1.png" );
  new ala::Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new ala::Sprite( "throwable_apple.png", "textures/miscellaneous/throwable_apple.png" );

  // Animations
  new ala::Animation( "aladdin.animation", "animations/playable_characters/aladdin.animation" );

  // Audio
  new ala::AudioClip( "wow.wav", "audio/sfx/wow.wav" );

  // Prefabs
  new CameraPrefab();
  new BackgroundPrefab();
  new ForegroundPrefab();
  new AladdinPrefab();
  new ThrowableApplePrefab();
}
