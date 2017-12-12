#include "EnemyExplosionPrefab.h"

USING_NAMESPACE_ALA;

void EnemyExplosionPrefab::doInstantiate( ala::GameObject* object ) const {
  new SpriteRenderer( object, "enemy_explosions.png" );
  const auto animator = new Animator( object, "1", "enemy_explosions.anm" );

  const auto stateManager = new StateManager( object, "initial" );
  new State( stateManager, "initial",
             NULL,
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             },
             NULL );

  object->setLayer( "Background" );
}
