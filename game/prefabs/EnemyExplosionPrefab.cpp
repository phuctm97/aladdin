#include "EnemyExplosionPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(EnemyExplosionPrefab, ala::PrefabV2)

void EnemyExplosionPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "enemy_explosions.png" );

  const auto animator = new Animator( object, "1", "enemy_explosions.anm" );

  const auto stateManager = new StateManager( object, "explode" );

  // states
  new State( stateManager, "explode",
             NULL,
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             },
             NULL );

  // configurations
  object->setLayer( "Foreground" );
}
