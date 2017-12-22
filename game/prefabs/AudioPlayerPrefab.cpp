#include "AudioPlayerPrefab.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(AudioPlayerPrefab, ala::PrefabV2)

void AudioPlayerPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  // args
  const auto audioName = nextLine( argsStream );

  // components
  const auto audio = new AudioSource( object, audioName );

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
