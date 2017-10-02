/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/BallPrefab.h"

void MyResourceInitializer::run() {
  // Textures
  new ala::Sprite( "ball.png", "textures/ball.png" );

  // Prefabs
  new BallPrefab();
}
