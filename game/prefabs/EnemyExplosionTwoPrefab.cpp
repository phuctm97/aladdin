#include"EnemyExplosionTwoPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(EnemyExplosionTwoPrefab, ala::PrefabV2)

void EnemyExplosionTwoPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "enemy_explosions.png" );

  const auto animator = new Animator( object, "explosion", "enemy_explosions.anm" );

  const auto genieDeathAudio = new AudioSource( object, "Genie Fumes.wav" );

  const auto stateManager = new StateManager( object, "explode" );

  // states
  new State( stateManager, "explode",
             [=] {
               // audio 
               {
                 genieDeathAudio->play();
               }
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() ) {
                 object->release();
               }
             },
             NULL );

  // configurations
  object->setLayer( "Foreground" );
}
