/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/BallPrefab.h"
#include "../prefabs/AnimationExamplePrefab.h"
#include "ui/Font.h"
#include "../prefabs/TextExamplePrefab.h"

void MyResourceInitializer::doRun() {
  // Textures
  new ala::Sprite( "ball.png", "textures/ball.png" );
  new ala::Sprite( "sprites.png", "textures/sprites.png" );
  new ala::Animation( "sprites.animation", "animations/sprites.animation" );

  new ala::Sprite("aladdin.png", "textures/aladdin.png");
  new ala::Animation("aladdin.animation", "animations/aladdin.animation");

  new ala::Font("Sail-Regular", "Sail-Regular.otf", "fonts");

  // Audio
  new ala::AudioClip( "wow.wav", "audio/sfx/wow.wav" );

  // Prefabs
  new AnimationExamplePrefab();
  new BallPrefab();
  new TextExamplePrefab();
}
