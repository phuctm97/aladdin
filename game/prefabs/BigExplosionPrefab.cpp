#include"BigExplosionPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(BigExplosionPrefab, ala::PrefabV2)

void BigExplosionPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "enemy_explosions.png" );

  const auto animator = new Animator( object, "big_explosion", "enemy_explosions.anm" );

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
