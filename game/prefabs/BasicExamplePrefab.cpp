/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "BasicExamplePrefab.h"
#include "../scripts/BasicController.h"

USING_NAMESPACE_ALA;

void BasicExamplePrefab::doInstantiate( ala::GameObject* object ) const {
  // layers
  object->setLayer( "Background" );

  new SpriteRenderer( object, "ball.png" );
  new AudioSource( object, "wow.wav" );
  new BasicController( object );
}
