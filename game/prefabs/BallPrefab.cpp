/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallPrefab.h"
#include "../scripts/BallController.h"

void BallPrefab::doInstantiate( ala::GameObject* object ) {
  new ala::SpriteRenderer( object, "ball.png" );
  new BallController( object );
}
