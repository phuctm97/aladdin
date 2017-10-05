/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallPrefab.h"
#include "../scripts/BallController.h"
#include "core/StateManager.h"
#include "../states/GoRightState.h"

void BallPrefab::doInstantiate( ala::GameObject* object ) {
  new ala::SpriteRenderer( object, "ball.png" );
  new BallController( object );
  new ala::StateManager(object, new GoRightState(object));
}
