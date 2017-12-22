#include "JafarSceneSoundPrefab.h"
#include"../Define.h"

USING_NAMESPACE_ALA;

ALA_CLASS_SOURCE_1(JafarSceneSoundPrefab, ala::PrefabV2)

void JafarSceneSoundPrefab::doInstantiate( ala::GameObject* object, std::istringstream& argsStream ) const {
  const auto sceneSound = new AudioSource( object, "BossTune.wav" );

  const auto stateManager = new StateManager( object, "static" );

  new State( stateManager, "static", [=] {
               sceneSound->setLoop( true );
               sceneSound->play();
             },
             NULL, NULL );
}
