#include "EnemyExplosionOnePrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(EnemyExplosionOnePrefab, ala::PrefabV2)

void EnemyExplosionOnePrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // components
  const auto spriteRenderer = new SpriteRenderer( object, "enemy_explosions.png" );
  //audio 
  const auto DeathSound = new AudioSource(object, "Cloud Poof.wav");
  const auto animator = new Animator( object, "1", "enemy_explosions.anm" );

  const auto stateManager = new StateManager( object, "explode" );

  // states
  new State( stateManager, "explode",
	  [=] {
	  //audio
		  {
			  DeathSound->play();
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
