#include "FirePrefab.h"

USING_NAMESPACE_ALA;

void FirePrefab::doInstantiate( ala::GameObject* object ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "jafar.png" );

  const auto animator = new Animator( object, "fire", "jafar.anm" );

  const auto stateManager = new StateManager( object, "fire" );

  // states
  new State( stateManager, "fire",
             NULL,
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             },
             NULL );

  // configurations
  object->setLayer( "Background" );
}
