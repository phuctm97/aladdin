#include "JafarPalaceSceneSoundPrefab.h"
#include"../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarPalaceSceneSoundPrefab, ala::PrefabV2)

void JafarPalaceSceneSoundPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  const auto sceneAudio = new AudioSource( object, "BossTune.wav", "M" );

  const auto stateManager = new StateManager( object, "static" );

  new State( stateManager, "static", [=] {
    sceneAudio->play();
  }, NULL, NULL );
}
