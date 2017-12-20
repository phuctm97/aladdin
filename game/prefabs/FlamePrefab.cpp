#include "FlamePrefab.h"

USING_NAMESPACE_ALA;

void FlamePrefab::doInstantiate( ala::GameObject* object ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );
  //audio
  const auto CoalSound = new AudioSource(object, "Fire From Coal.wav");
  const auto animator = new Animator( object, "fire", "jafar.anm" );

  const auto stateManager = new StateManager( object, "fire" );

  // states
  new State( stateManager, "fire",
	  [=] {
	  CoalSound->play();
	  },
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             },
             NULL );

  // configurations
  object->setLayer( "Second Background" );
}
