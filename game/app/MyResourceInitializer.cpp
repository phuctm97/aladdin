/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/BallPrefab.h"
#include "../prefabs/CameraPrefab.h"
#include "2d/Animation.h"
#include "../prefabs/AnimationExamplePrefab.h"

void MyResourceInitializer::run() {
  // Textures
  new ala::Sprite( "sprites.png", "textures/sprites.png" );
  new ala::Animation("sprites.animation", "animations/sprites.animation");
  // Prefabs
  new AnimationExamplePrefab();
  new BallPrefab();
  new CameraPrefab();
}
