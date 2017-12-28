#include"EnemyExplosionTwoPrefab.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(EnemyExplosionTwoPrefab, ala::PrefabV2)

void EnemyExplosionTwoPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "enemy_explosions.png" );

  const auto animator = new Animator( object, "explosion", "enemy_explosions.anm" );

  const auto genieDeathAudio = new AudioSource( object, "Genie Fumes.wav" );
  genieDeathAudio->setActive( myAppData->isSfxOn() );

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
