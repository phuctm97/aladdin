/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallPrefab.h"
#include "../scripts/BallController.h"

void BallPrefab::doInstantiate( ala::GameObject* object ) {
  auto sr = new ala::SpriteRenderer( object, "ball.png" );
  new ala::AudioSource( object, "wow.wav" );

  sr->setZOrder(0);
}
