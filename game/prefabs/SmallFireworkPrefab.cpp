#include"SmallFireworkPrefab.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(SmallFireworkPrefab, ala::PrefabV2)

void SmallFireworkPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // constants
  const auto gameManager = GameManager::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  // components
  const auto spriteRenderer = new SpriteRenderer( object, "items.png" );

  const auto animator = new Animator( object, "small_firework", "items.anm" );

  const auto eatAppleAudio = new AudioSource( object, "Apple Collect.wav" );
  eatAppleAudio->setActive( myAppData->isSfxOn() );

  const auto stateManager = new StateManager( object, "static" );

  // configurations
  object->setLayer( "Foreground" );

  // states
  new State( stateManager, "static",
             [=] {
               // audio
               {
                 eatAppleAudio->play();
               }
             },
             [=]( float dt ) {
               if ( !animator->isPlaying() )
                 object->release();
             }, NULL );
}
