/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BasicExamplePrefab.h"
#include "../scripts/BasicController.h"

void BasicExamplePrefab::doInstantiate( ala::GameObject* object ) const {
  // layers
  object->setLayer( "Background" );

  new ala::SpriteRenderer( object, "ball.png" );
  new ala::AudioSource( object, "wow.wav" );
  new BasicController( object );
}
