/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BallPrefab.h"
#include "../scripts/BallController.h"

ala::GameObject* BallPrefab::doInstantiate() {
  ala::GameObject* object = new ala::GameObject();

  // add components
  auto transform = new ala::Transform2( object );
  transform->setPosition( ala::Vec2() );

  new ala::SpriteRenderer( object, "ball.png" );
  new BallController( object );

  return object;
}
