/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/BasicExamplePrefab.h"
#include "../prefabs/AnimationAndStateExamplePrefab.h"
#include "../prefabs/TextExamplePrefab.h"

void MyResourceInitializer::doRun() {
  auto gameManager = ala::GameManager::get();

  // Layers
  gameManager->addLayer( "Background" );
  gameManager->addLayer( "Character" );
  gameManager->addLayer( "UI" );

  // Textures
  new ala::Sprite( "ball.png", "textures/ball.png" );
  new ala::Sprite( "aladdin.png", "textures/aladdin.png" );

  // Animations
  new ala::Animation( "aladdin.animation", "animations/aladdin.animation" );

  // Fonts
  new ala::Font( "crackman.ttf", "crackman.ttf", "fonts" );

  // Audio clips
  new ala::AudioClip( "wow.wav", "audio/sfx/wow.wav" );

  // Prefabs
  new AnimationAndStateExamplePrefab();
  new BasicExamplePrefab();
  new TextExamplePrefab();
}
