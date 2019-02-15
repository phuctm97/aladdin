#include "AudioPlayerPrefab.h"
#include "../app/MyAppData.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AudioPlayerPrefab, ala::PrefabV2)

void AudioPlayerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto audioName = nextLine( argsStream );

  // constants
  const auto gameManager = GameManager::get();
  const auto myAppData = static_cast<MyAppData*>(gameManager->getResource( "My App Data" ));

  // components
  const auto audio = new AudioSource( object, audioName );
  audio->setActive( myAppData->isSfxOn() );

  const auto stateManager = new StateManager( object, "default" );

  // states
  new State( stateManager, "default",
             [=] {
               audio->play();
             },
             [=]( float dt ) {
               if ( !audio->isPlaying() ) {
                 object->release();
               }
             }, NULL );
}
