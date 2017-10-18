/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/CameraPrefab.h"
#include "../prefabs/AladdinPrefab.h"

void MyResourceInitializer::run() {
  // Textures
  new ala::Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );

  // Animations
  new ala::Animation( "aladdin.animation", "animations/playable_characters/aladdin.animation" );

  // Audio
  new ala::AudioClip( "wow.wav", "audio/sfx/wow.wav" );

  // Prefabs
  new AladdinPrefab();
  new CameraPrefab();
}
